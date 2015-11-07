/****************************************************************************

COPYRIGHT (C) $Date: Nov 3, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_tim_main.c  $

$Author: PES contribution $

 ****************************************************************************/

#include "MCU_drivers/Dio/io_dio.h"
#include "MCU_drivers/Pcs/io_pcs_cnf.h"

#include "io_tim.h"

/** Public operations **/

void Io_Tim_Initialization(void)
/*~-1*/
{
	/* SIM_SCGC6: PIT=1 */
	SIM_SCGC6 |= (uint32_t)0x00800000UL;

	/*	PIT_MCR:=0, MDIS=0,FRZ=0
		PIT_MCR = (uint32_t)0x00UL;          // Enable device clock
		PIT_TCTRL0: ??=0,,CHN=0,TIE=0,TEN=0
		PIT_TCTRL0 = (uint32_t)0x00UL;       // Clear control register
		PIT_TFLG0: ??=0,TIF=1
		PIT_TFLG0 = (uint32_t)0x01UL;        // Clear timer flag register
		PIT_LDVAL0: TSV=0x000927BF
		PIT_LDVAL0 = (uint32_t)0x0005DC4FUL; //Set up load register
		NVIC_IPR5: PRI_22=0x40
		NVIC_IPR5 = (uint32_t)((NVIC_IPR5 & (uint32_t)~~0x00BF0000UL) | (uint32_t)0x00400000UL);
		NVIC_ISER: SETENA|=0x00400000
		NVIC_ISER |= (uint32_t)0x00400000UL;
		PIT_TCTRL0: ??=0, TIE=1,TEN=1
		PIT_TCTRL0 = (uint32_t)0x03UL;       // Set up control register

		PIT_MCR = 0x00;  					// MDIS = 0  enables timer
		PIT_TCTRL0 = 0x00; 					// disable PIT0
		PIT_LDVAL0 = 48000;
		PIT_TCTRL0 = PIT_TCTRL_TIE_MASK; 	// enable PIT0 and interrupt
		PIT_TFLG0 = 0x01; 					// clear flag
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
	*/
	/*	NVIC_IPR5 = (uint32_t)((NVIC_IPR5 & (uint32_t)~~0x00BF0000UL) | (uint32_t)0x00400000UL); */
	/* PIT_MCR:=0, MDIS=0,FRZ=0 */
	PIT_MCR = (uint32_t)0x00UL;          /* Enable device clock */
	/* PIT_TCTRL0: ??=0,,CHN=0,TIE=0,TEN=0 */
	PIT_TCTRL0 = (uint32_t)0x00UL;       /* Clear control register */
	/* PIT_TFLG0: ??=0,TIF=1 */
	PIT_TFLG0 = (uint32_t)0x01UL;        /* Clear timer flag register */
	/* PIT_LDVAL0: TSV=0x000927BF */
	PIT_LDVAL0 = (uint32_t)24004; /* Set up load register : 1000000/41,66ns*/
	/* NVIC_IPR5: PRI_22=0x40 */
	// NVIC_IPR5 = (uint32_t)((NVIC_IPR5 & (uint32_t)~0x00BF0000UL) | (uint32_t)0x00400000UL);   - leonte
	NVIC->IP[5] = (uint32_t)((NVIC->IP[5] & (uint32_t)~0x00BF0000UL) | (uint32_t)0x00400000UL);
	/* NVIC_ISER: SETENA|=0x00400000 */
	//NVIC_ISER |= (uint32_t)0x00400000UL;  - leonte
	NVIC->ISER[0] |= (uint32_t)0x00400000UL;
	/* PIT_TCTRL0: ??=0, TIE=1,TEN=1 */
	PIT_TCTRL0 = (uint32_t)0x03UL;       /* Set up control register */

}

void SysTick_Init(void)
{
	/* SYST_CSR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COUNTFLAG=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CLKSOURCE=0,TICKINT=0,ENABLE=0 */
	//    SYST_CSR = 0x00U;
	/* SYST_RVR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,RELOAD=0x82 */

	/* SYST_CVR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CURRENT=0 */
	//    SYST_CVR = SysTick_CVR_CURRENT(0x00);
	/* SYST_CSR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COUNTFLAG=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CLKSOURCE=0,TICKINT=1,ENABLE=1 */
	//    SYST_CSR = (SysTick_CSR_TICKINT_MASK | SysTick_CSR_ENABLE_MASK);
	SysTick_Config (SystemCoreClock/1000);    // Configure the SYSTICK

}

void Io_Tim_ConfigIntTimer1(uint16 Config)
{
	//IFS0bits.T1IF = 0;                   	/* clear TMR1 interrupt status flag */
	//IPC0bits.T1IP = (Config &0x0007);    	/* assigning Interrupt Priority */
	//IEC0bits.T1IE = (Config &0x0008)>>3; 	/* Interrupt Enable /Disable */
}

void Io_Tim_OpenTimer0(uint32 Config, uint16 Period)
{
	PIT_TCTRL0 = Config;					/* Configure timer control reg */
	PIT_LDVAL0 = Period;					/* assigning Period to Timer period register */
}

void Io_Tim_CloseTimer0(void)
{
	PIT_TCTRL0 = 0x80000000;     			/* Disable the Timer1 interrupt / stop time */
}

void Io_Tim_ConfigIntTimer2(uint16 Config)
{
	//IFS0bits.T2IF = 0;                   	/* clear IF bit */
	//IPC1bits.T2IP = (Config &0x0007);    	/* assigning Interrupt Priority */
	//IEC0bits.T2IE = (Config &0x0008)>>3; 	/* Interrupt Enable /Disable */
}

void Io_Tim_OpenTimer1(uint32 Config, uint16 Period)
{
	PIT_TCTRL1 = Config;					/* Configure timer control reg */
	PIT_LDVAL1 = Period;					/* Assigning Period to Timer period register */
}

void Io_Tim_CloseTimer1(void)
{
	PIT_TCTRL1 = 0x80000000;      			/* Disable the Timer1 interrupt / stop time */
}

uint16 Io_Tim_ReadTimer16(void)
{
	return Io_Tim_ReadTimer1();  			//controller is ARM
}

#ifdef DOIT

void Io_Tim_DelayUs (uint16 Us)
{
	uint32 RelVal;
	uint8 TmpU81, TmpU82, LvOverflow;

	/* Calculate the reload value for the System Timer */
	RelVal = Io_Tim_ReadTimer16() + (uint32)(IO_SYS_PLL_FREQ / 1000000) * Us;

	if (RelVal > U16_MAX)
	{
		RelVal = RelVal - U16_MAX + 1;

		LvOverflow = 1;
	}
	else
	{
		LvOverflow = 0;
	}

	TmpU81 = (Io_Tim_ReadTimer16() < (uint16)RelVal) && (LvOverflow == 0);
	TmpU82 = (Io_Tim_ReadTimer16() > (uint16)RelVal) && (LvOverflow == 1);

	while ( TmpU81 || TmpU82 )
	{
		TmpU81 = (Io_Tim_ReadTimer16() < (uint16)RelVal) && (LvOverflow == 0);
		TmpU82 = (Io_Tim_ReadTimer16() > (uint16)RelVal) && (LvOverflow == 1);

		/* wait until time elapsed - then return */
	}
}

#endif

void Io_Tim_DelayUs (uint16 Us)
{
	unsigned short  i, cnt;

	cnt = Us*20;

	for (i = 0; i < cnt; i++)
	{
		__asm__("nop");

	}
}

void Io_Tim_DelayMs (uint16 Ms)
{
	Io_Tim_DelayUs(Ms * 1000);
}

/** end of Public operations **/
