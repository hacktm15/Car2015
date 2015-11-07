/****************************************************************************

COPYRIGHT (C) $Date: Aug 12, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_int_cnf.c  $

$Author: Leonte Alexandru $

****************************************************************************/

/** Includes **/

#include "io_int_cnf.h"

/** Includes **/

const Io_Int_InterruptTypeStruct Io_Int_InterruptCnf[]=
{
	/*  Function Pointer ISR						 	IRQ_Number										Priority 		    																			*/
		{	&Io_Sch_PeriodicTask,							IO_INT_SYSTICK_IRQ_NUMBER,						IO_INT_PRIO_02		},			/* SysTick timer - interrupt */
		{	&Io_Adc_Isr,									IO_INT_ADC0_IRQ_NUMBER,							IO_INT_PRIO_02		},			/* ADC0 - interrupt */
		//{   &Io_Pcs_Portc_Portd_Isr,						IO_INT_PORT_CONTROL_MODULE2_IRQ_NUMBER,			IO_INT_PRIO_02		},			/* PORTC, PORTD - interrupt */
		{   &Io_Asy_Asy0_Isr,                               IO_INT_UART0_IRQ_NUMBER,                        IO_INT_PRIO_02      },			/* UART0 - interrupt */
		{   &Io_Asy_Asy1_Isr,                               IO_INT_UART1_IRQ_NUMBER,                        IO_INT_PRIO_02      },			/* UART1 - interrupt */
		{   &Io_Asy_Asy2_Isr,                               IO_INT_UART2_IRQ_NUMBER,                        IO_INT_PRIO_02      },			/* UART2 - interrupt */
		//{	&Io_Tpm_Tpm0Isr,								IO_INT_TPM0_IRQ_NUMBER,							IO_INT_PRIO_02		},			/* TPM0 - interrupt */
		//{	&Io_Tpm_Tpm1Isr,								IO_INT_TPM1_IRQ_NUMBER,							IO_INT_PRIO_02		},			/* TPM1 - interrupt */
		//{	&Io_Tpm_Tpm2Isr,								IO_INT_TPM2_IRQ_NUMBER,							IO_INT_PRIO_02		},			/* TPM2 - interrupt */
		//{	&Io_I2C0_Isr,									IO_INT_I2C0_IRQ_NUMBER,							IO_INT_PRIO_02		},			/* I2C0 - interrupt */
		//{	&Io_I2C1_Isr,									IO_INT_I2C1_IRQ_NUMBER,							IO_INT_PRIO_02		}			/* I2C1 - interrupt */
};


const Io_Int_CnfTypeStruct Io_Int_Cnf[]=
{
		{
				sizeof(Io_Int_InterruptCnf)/sizeof(Io_Int_InterruptTypeStruct),
				(const Io_Int_InterruptTypeStruct*) Io_Int_InterruptCnf
		}
};






