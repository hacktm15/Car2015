/****************************************************************************

COPYRIGHT (C) $Date: Aug 12, 2015 $
$CompanyInfo:  $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_int_main.c  $

$Author: Leonte Alexandru $

****************************************************************************/

/** Includes **/

#include "io_int_cnf.h"

/** end of Includes **/

const Io_Int_CnfTypeStruct *Io_Int_CnfPtr;
Io_Int_Isr_Define array_of_handlers[48];

/*
 * Initializes the NVIC peripheral registers and  System (Cortex m0+) exception registers depending on configuration.
 *
 * Peripheral
 * - Enable all configured Interrupt (32 IRQ interrupt sources - NVIC )
 * - Clear all Pending configured Interrupts (32 IRQ interrupt source )
 * - Set all configured Interrupt Priorities (32 IRQ interrupt source)
 *
 * Set all configured System exception
 * - SysTick , PENDSV, SVCALL , NMI
 *
 * Parameters:
 * *PtrCnf 				Pointer to configuration structure (declared in io_int_cnf)
 *
 */
void Io_Int_EnableInterrupts(void)
{
	IO_INT_ENABLE_INTERRUPTS;
}

void Io_Int_DisableInterrupts(void)
{
	IO_INT_DISABLE_INTERRUPTS;
}

void Io_Int_Initialization(const Io_Int_CnfTypeStruct *PtrCnf)
{
	int i=0;
	sint8 IRQ_Number;
	const Io_Int_InterruptTypeStruct *tmp_ptr;
	Io_Int_CnfPtr = PtrCnf;
	tmp_ptr = Io_Int_CnfPtr->Io_Int_InterruptPtr;

	for(i=0;i<Io_Int_CnfPtr->Nr_Of_Configurations;i++)
	{
		IRQ_Number = tmp_ptr->irq_number;
		if(IRQ_Number<0)
		{
			/*System exceptions -14 to -1*/
			switch(IRQ_Number)
			{
				case IO_INT_SYSTICK_IRQ_NUMBER:
					  array_of_handlers[IRQ_Number+IO_INT_IRQ_TO_VECTOR] = tmp_ptr->Io_Int_Isr_Adress;
					  SysTick->LOAD  = IO_INT_CORE_FREQ/IO_INT_SYSTICK_1MS - 1;            		/* Set reload register - tick every 1 ms */
					  Io_Int_SetPriority(IO_INT_SYSTICK_IRQ_NUMBER, tmp_ptr->priority);  					/* Set priority for Systick Interrupt */
					  SysTick->VAL   = 0;                                          						/* Load the SysTick Counter Value */
					  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk );   									/* Configure clock source - 1 : CPU clock */
					  Io_Int_Enable_Systick_Interrupt();
					  break;
			}
			tmp_ptr++;
		}
		else
		{
			/*Device-specific interrupt 0 to 31*/
			Io_Int_NVIC_ClearPending(IRQ_Number);
			Io_Int_SetPriority(IRQ_Number,tmp_ptr->priority);									/* Set priority (default 0 - highest , 3 - lowest)*/
			if(tmp_ptr->Io_Int_Isr_Adress != NULL_PTR)
			{
				array_of_handlers[IRQ_Number+IO_INT_IRQ_TO_VECTOR] = tmp_ptr->Io_Int_Isr_Adress;
			}
			Io_Int_NVIC_Enable(IRQ_Number);
			tmp_ptr++;
		}
	}
}

/*
 * De-initializes the NVIC peripheral registers and  System (Cortex m0+) exception registers to their default reset values.
 *
 * Peripheral
 * - Disable all configured Interrupt (32 IRQ interrupt sources )
 * - Clear all Pending configured Interrupts (32 IRQ interrupt source )
 * - Clear all configured Interrupt Priorities (32 IRQ interrupt source)
 * System
 * - SysTick , PENDSV, SVCALL , NMI (if were configured)
 *
 * This function shall reset all used resource to the default value (reset value) and release all used peripherals.
 * Upon completion of this function, the INT driver should be ready for a new initialization request.
 *
*/

void Io_Int_ShutDown(void)
{
	int i=0;
	sint8 IRQ_Number;
	const Io_Int_InterruptTypeStruct *tmp_ptr;

	IO_INT_DISABLE_INTERRUPTS;

	tmp_ptr = Io_Int_CnfPtr->Io_Int_InterruptPtr;

	for(i=0;i<Io_Int_CnfPtr->Nr_Of_Configurations;i++){
		IRQ_Number = tmp_ptr->irq_number;
		array_of_handlers[IRQ_Number + IO_INT_IRQ_TO_VECTOR] = NULL_PTR;

		if(IRQ_Number<0)
		{
			/*System exceptions -14 to -1*/
			switch(IRQ_Number){
				case IO_INT_SYSTICK_IRQ_NUMBER:
					//!!!! CLEAR PENDING ?IS NECESSARILY ?
					SysTick->CTRL &= ~(SysTick_CTRL_CLKSOURCE_Msk); /* Disable clock source */
					SysTick->VAL   = 0;
					Io_Int_Disable_Systick_Interrupt();
				//	SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk;													/* removes the pending state from the SysTick exception*/
					break;
				case IO_INT_PENDSV_IRQ_NUMBER:
					//SCB->ICSR |= SCB_ICSR_PENDSVCLR_Msk;													/*removes the pending state from the PendSV exception.*/
					break;
				case IO_INT_SVCALL_IRQ_NUMBER:
					break;
				case IO_INT_NMI_IRQ_NUMBER:
					break;
				}
			Io_Int_SetPriority(IRQ_Number, HIGHEST_PRIORITY);
			tmp_ptr++;
		}
		else
		{
			/*Device-specific interrupt 0 to 31*/
			Io_Int_NVIC_Disable(IRQ_Number);
			Io_Int_NVIC_ClearPending(IRQ_Number);
			Io_Int_SetPriority(IRQ_Number, HIGHEST_PRIORITY);
			Io_Int_NVIC_ClearPending(IRQ_Number);
			tmp_ptr++;
		}
	}
}

/*
 * This function enable a device-specific interrupt in the NVIC(Nested Vectored Interrupt Controller).
 *
 * If a pending interrupt is enabled, the NVIC activates the interrupt based on its priority. If an
 * interrupt is not enabled, asserting its interrupt signal changes the interrupt state to pending, but
 * the NVIC never activates the interrupt, regardless of its priority.
 *
 * Parameters
 * irq_number 	External interrupt number. Value cannot be negative , see io_int_cnf.h for more information.
 *
 *
 */

void Io_Int_NVIC_Enable(uint8 irq_number)
{
	NVIC->ISER[0] = 1UL << irq_number ;
}


/*
 * This function forces interrupts into the pending state (external interrupts).
 *
 * Parameters
 * irq_number External interrupt number. Value cannot be negative , see io_int_cnf.h for more information.
 *
 */

void Io_Int_NVIC_SetPending(uint8 irq_number)
{
	NVIC->ISPR[0] = 1UL << irq_number;
}

/*
 * Set Interrupt priority
 *
 * The function sets the priority of an interrupt (Peripheral or System ).
 *
 * Parameters
 * irq_number 	Interrupt number (Peripheral or System).
 * priority 	Priority to set (0 highest - 3 lowest)
 *
 */

void Io_Int_SetPriority(sint8 irq_number, uint8 priority)
{
	if(irq_number < 0)
	{
		SCB->SHP[_SHP_IDX(irq_number)] = (SCB->SHP[_SHP_IDX(irq_number)] & ~(0xFF << _BIT_SHIFT(irq_number))) |
	        (((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF) << _BIT_SHIFT(irq_number));
	}
	else
	{
	NVIC->IP[_IP_IDX(irq_number)] = (NVIC->IP[_IP_IDX(irq_number)] & ~(0xFF << _BIT_SHIFT(irq_number))) |
		(((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF) << _BIT_SHIFT(irq_number));
	}
}

/*
 * Enable SysTick
 *
 * This function enable SysTick counter and exception request.
 *
 */

void Io_Int_Enable_Systick_Interrupt(void)
{
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;														/* Enable systick interrupt and SysTick Timer*/
}

/*
 * This function disable a device-specific interrupt in the NVIC(Nested Vectored Interrupt Controller).
 *
 * If a pending interrupt is enabled, the NVIC activates the interrupt based on its priority. If an
 * interrupt is not enabled, asserting its interrupt signal changes the interrupt state to pending, but
 * the NVIC never activates the interrupt, regardless of its priority.
 *
 * Parameters
 * irq_number	 External interrupt number. Value cannot be negative , see io_int_cnf.h for more information.
 *
 */

void Io_Int_NVIC_Disable(uint8 irq_number)
{
	NVIC->ICER[0] =  (uint32)1<< irq_number;
}

/*
 * This function removes the pending state from interrupts.
 *
 * Parameters
 * irq_number	 External interrupt number. Value cannot be negative , see io_int_cnf.h for more information.
 *
 */

void Io_Int_NVIC_ClearPending(uint8 irq_number)
{
	NVIC->ICPR[0] = 1UL<<irq_number;
}

/*
 * Disable SysTick
 *
 * This funcion Disable Systick counter and exception request.
 *
 */

void Io_Int_Disable_Systick_Interrupt(void)
{
	SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);													/*Disable SysTick interrupt and SysTick Timer*/
}

/*
 * Call ISR functions
 *
 * This function call ISR function depending on vector_number from array_of_handler - an array of 48 elements, each one representing an interrupt (vector numbers).
 *
 * Parameters
 * vector_number	 External interrupt number, see io_int_cnf.h for more information.
 *
 */

void Io_Int_ProcessHandler(sint8 vector_number)
{
	if(array_of_handlers[vector_number+IO_INT_IRQ_TO_VECTOR] != NULL_PTR)									/* Check if exists ISR*/
	{
		Io_Int_Isr_Define Io_Int_Isr_Ptr = array_of_handlers[vector_number+IO_INT_IRQ_TO_VECTOR];
		Io_Int_Isr_Ptr();																				/* call ISR */
	}
	else
	{
		if(vector_number == -13)					/* Hard fault */
		{
			//ISR HARDFAULT
			/* TODO LEONTE: LIGHT RED LED WHEN NO WDT / WHILE(1) + WDT */
			while(1) {}
		}
		else
		{
		Io_Int_Dummy();								/* No configuration found - ISR == NULL */
		}
	}
}

void Io_Int_Dummy(void)
{

}

/* System handlers - ARM CORTEX M0+ */


void NMI_Handler(void)
{
	Io_Int_ProcessHandler(IO_INT_NMI_IRQ_NUMBER);

}

void HardFault_Handler(void)
{
	Io_Int_ProcessHandler(IO_INT_HARDFAULT_IRQ_NUMBER);

}

void SVC_Handler(void)
{
	Io_Int_ProcessHandler(IO_INT_SVCALL_IRQ_NUMBER);
}

void PendSV_Handler(void)
{
	Io_Int_ProcessHandler(IO_INT_PENDSV_IRQ_NUMBER);
}

void SysTick_Handler()
{
	/*The SysTick periodic interrupt will be the only example of an automatic acknowledgement*/
	Io_Int_ProcessHandler(IO_INT_SYSTICK_IRQ_NUMBER);
}


/* Devices handlers */


void DMA0_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_DMA0_IRQ_NUMBER);
}

void DMA1_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_DMA1_IRQ_NUMBER);
}

void DMA2_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_DMA2_IRQ_NUMBER);
}

void DMA3_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_DMA3_IRQ_NUMBER);
}

void FTFA_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_FTFA_IRQ_NUMBER);
}

void LVD_LVW_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_PMC_IRQ_NUMBER);
}

void LLWU_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_LLWU_IRQ_NUMBER);
}

void I2C0_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_I2C0_IRQ_NUMBER);
}

void I2C1_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_I2C1_IRQ_NUMBER);
}

void SPI0_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_SPI0_IRQ_NUMBER);
}

void SPI1_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_SPI1_IRQ_NUMBER);
}

void UART0_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_UART0_IRQ_NUMBER);
}

void UART1_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_UART1_IRQ_NUMBER);
}

void UART2_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_UART2_IRQ_NUMBER);
}

void ADC0_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_ADC0_IRQ_NUMBER);
}

void CMP0_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_CMP0_IRQ_NUMBER);
}

void TPM0_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_TPM0_IRQ_NUMBER);
}

void TPM1_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_TPM1_IRQ_NUMBER);
}

void TPM2_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_TPM2_IRQ_NUMBER);
}

void RTC_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_RTC_ALARM_IRQ_NUMBER);
}

void RTC_Seconds_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_RTC_SECONDS_IRQ_NUMBER);
}

void PIT_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_PIT_IRQ_NUMBER);
}

void I2S0_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_I2S0_IRQ_NUMBER);
}

void USB0_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_USB_OTG_IRQ_NUMBER);
}

void DAC0_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_DAC0_IRQ_NUMBER);
}

void TSI0_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_TSI0_IRQ_NUMBER);
}

void MCG_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_MCG_IRQ_NUMBER);
}

void LPTMR0_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_LPTMR0_IRQ_NUMBER);
}

void PORTA_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_PORT_CONTROL_MODULE1_IRQ_NUMBER);
}
void PORTC_PORTD_IRQHandler(void)
{
	Io_Int_ProcessHandler(IO_INT_PORT_CONTROL_MODULE2_IRQ_NUMBER);
}


