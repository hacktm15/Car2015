/*~-1*/
/*~XSF_LANGUAGE: C/C++*/
/*~I:1*/
#ifndef IO_INT_H
/*~T*/
#define IO_INT_H
/*~A:2*/
/*~+:Module Header*/
/*~T*/
/* ## Module Header Start [328f418b-489c-4745-80e2-b2a3fbf9452a] */
/****************************************************************************

COPYRIGHT (C) $Date: 2012/05/09 17:46:33CEST $
$CompanyInfo:  $
ALL RIGHTS RESERVED.                                                 
                                                                           
The reproduction, transmission or use of this document or its contents is  
not permitted without express written authority.                           
Offenders will be liable for damages. All rights, including rights created 
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$Log: template.h  $

****************************************************************************/
/* ## Module Header End [328f418b-489c-4745-80e2-b2a3fbf9452a] */
#include "PLATFORM_TYPES/Std_Types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "SYSTEM/SCHEDULER/io_sch.h"
//#include "io_vdd.h"
#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"
#include "MCU_DRIVERS/DIO/io_dio.h"
#include "MCU_DRIVERS/ADC/io_adc.h"
#include "MCU_DRIVERS/TPM/io_tpm.h"
#include "MCU_DRIVERS/ASY/io_asy.h"

#define BUILD_ISR(ISR_name) void __attribute__ ((interrupt)) ISR_name(void)

#define HIGHEST_PRIORITY 								0

#define IO_INT_SYSTICK_1MS								1000								/*used in systick initialization*/
#define IO_INT_CORE_FREQ 								48000000							/*used in systick initialization*/

#define IO_INT_IRQ_TO_VECTOR							16									/*used to convert irq number to vector table position - for array_of_isr */


#define IO_INT_ENABLE_INTERRUPTS {__asm(" CPSIE i");__asm( "isb");}						    /*Enable Interrupts by clearing PRIMASK register, Allow pended interrupts to be recognized*/
#define IO_INT_DISABLE_INTERRUPTS {__asm(" CPSID i");}										/*Disable interrupts by setting PRIMASK register */

typedef struct Io_Int_CnfTypeStruct_tag Io_Int_CnfTypeStruct;
typedef struct Io_Int_InterruptTypeStruct_tag Io_Int_InterruptTypeStruct;
typedef void (* Io_Int_Isr_Define)(void ) ;													/* Point to IRQ  Handler */

struct Io_Int_InterruptTypeStruct_tag
{
	void (* Io_Int_Isr_Adress)(void);
	sint8 irq_number;
	uint8 priority;

};

struct Io_Int_CnfTypeStruct_tag
{
	uint8 Nr_Of_Configurations;
	const Io_Int_InterruptTypeStruct *Io_Int_InterruptPtr;
};

extern uint8 Io_Int_Interrupts_Status;


extern void Io_Int_Initialization(const Io_Int_CnfTypeStruct *PtrCnf);
extern void Io_Int_ShutDown(void);

extern void Io_Int_EnableInterrupts(void);
extern void Io_Int_DisableInterrupts(void);

extern void Io_Int_NVIC_Enable(uint8 irq_number);
extern void Io_Int_NVIC_Disable(uint8 irq_number);

extern void Io_Int_NVIC_SetPending(uint8 irq_number);
extern void Io_Int_NVIC_ClearPending(uint8 irq_number);

extern void Io_Int_Enable_Systick_Interrupt(void);
extern void Io_Int_Disable_Systick_Interrupt();

extern void Io_Int_SetPriority(sint8 irq_number, uint8 priority);
extern void Io_Int_ProcessHandler(sint8 vector_number);
extern void Io_Int_Dummy(void);

BUILD_ISR(NMI_Handler);													/* Non Maskable Interrupt */
BUILD_ISR(HardFault_Handler);											/* Cortex-M0 SV Hard Fault Interrupt */
BUILD_ISR(SVC_Handler);													/* Cortex-M0 SV Call Interrupt */
BUILD_ISR(PendSV_Handler);												/* Cortex-M0 Pend SV Interrupt */
BUILD_ISR(SysTick_Handler);												/* Cortex-M0 System Tick Interrupt */
BUILD_ISR(DMA0_IRQHandler);
BUILD_ISR(DMA1_IRQHandler);
BUILD_ISR(DMA2_IRQHandler);
BUILD_ISR(DMA3_IRQHandler);
BUILD_ISR(FTFA_IRQHandler);
BUILD_ISR(LVD_LVW_IRQHandler);
BUILD_ISR(LLWU_IRQHandler);
BUILD_ISR(I2C0_IRQHandler);
BUILD_ISR(I2C1_IRQHandler);
BUILD_ISR(SPI0_IRQHandler);
BUILD_ISR(SPI1_IRQHandler);
BUILD_ISR(UART0_IRQHandler);
BUILD_ISR(UART1_IRQHandler);
BUILD_ISR(UART2_IRQHandler);
BUILD_ISR(ADC0_IRQHandler);
BUILD_ISR(CMP0_IRQHandler);
BUILD_ISR(TPM0_IRQHandler);
BUILD_ISR(TPM1_IRQHandler);
BUILD_ISR(TPM2_IRQHandler);
BUILD_ISR(RTC_IRQHandler);
BUILD_ISR(RTC_Seconds_IRQHandler);
BUILD_ISR(PIT_IRQHandler);
BUILD_ISR(I2S0_IRQHandler);
BUILD_ISR(USB0_IRQHandler);
BUILD_ISR(DAC0_IRQHandler);
BUILD_ISR(TSI0_IRQHandler);
BUILD_ISR(MCG_IRQHandler);
BUILD_ISR(LPTMR0_IRQHandler);
BUILD_ISR(PORTA_IRQHandler);
BUILD_ISR(PORTC_PORTD_IRQHandler);

#endif /* IO_INT_H */
