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

$Log: io_int_cnf.h  $

$Author: Leonte Alexandru $

****************************************************************************/

#ifndef IO_INT_CNF_H
#define IO_INT_CNF_H


/** Includes **/

#include "io_int.h"

/** end of Includes **/

 /* Core interrupts [-16,-1] (<0) */
#define IO_INT_NMI_IRQ_NUMBER							NonMaskableInt_IRQn			/* Non Maskable Interrupt */
#define IO_INT_HARDFAULT_IRQ_NUMBER						HardFault_IRQn				/* Cortex-M0 SV Hard Fault Interrupt */
#define IO_INT_SVCALL_IRQ_NUMBER						SVCall_IRQn					/* Cortex-M0 SV Call Interrupt */
#define IO_INT_PENDSV_IRQ_NUMBER						PendSV_IRQn					/* Cortex-M0 Pend SV Interrupt */
#define IO_INT_SYSTICK_IRQ_NUMBER						SysTick_IRQn				/* Cortex-M0 System Tick Interrupt */

  /* Device specific interrupts [0,31] ( >= 0) */
#define IO_INT_DMA0_IRQ_NUMBER							DMA0_IRQn					/* DMA channel 0 transfer complete and error interrupt IRQ number*/
#define IO_INT_DMA1_IRQ_NUMBER							DMA1_IRQn					/* DMA channel 1 transfer complete and error interrupt IRQ number*/
#define IO_INT_DMA2_IRQ_NUMBER							DMA2_IRQn					/* DMA channel 2 transfer complete and error interrupt IRQ number*/
#define IO_INT_DMA3_IRQ_NUMBER							DMA3_IRQn					/* DMA channel 3 transfer complete and error interrupt IRQ number*/
 /* Reserved interrupt 									Reserved20_IRQn																				*/
#define IO_INT_FTFA_IRQ_NUMBER							FTFA_IRQn					/* FTFA command complete and read collision IRQ number */
#define IO_INT_PMC_IRQ_NUMBER							LVD_LVW_IRQn				/* Low-voltage detect, low-voltage warning IRQ number */
#define IO_INT_LLWU_IRQ_NUMBER							LLW_IRQn					/* Low Leakage Wakeup IRQ number */
#define IO_INT_I2C0_IRQ_NUMBER							I2C0_IRQn					/* I2C0 interrupt IRQ number */
#define IO_INT_I2C1_IRQ_NUMBER							I2C1_IRQn					/* I2C1 interrupt IRQ number */
#define IO_INT_SPI0_IRQ_NUMBER							SPI0_IRQn					/* SPI0 single interrupt vector for all sources IRQ number */
#define IO_INT_SPI1_IRQ_NUMBER							SPI1_IRQn					/* SPI1 single interrupt vector for all sources IRQ number */
#define IO_INT_UART0_IRQ_NUMBER							UART0_IRQn					/* UART0 status and error IRQ number*/
#define IO_INT_UART1_IRQ_NUMBER							UART1_IRQn					/* UART1 status and error IRQ number */
#define IO_INT_UART2_IRQ_NUMBER							UART2_IRQn					/* UART2 status and error IRQ number*/
#define IO_INT_ADC0_IRQ_NUMBER							ADC0_IRQn 					/* ADC0 interrupt IRQ number*/
#define IO_INT_CMP0_IRQ_NUMBER							CMP0_IRQn					/* CMP0 interrupt IRQ number */
#define IO_INT_TPM0_IRQ_NUMBER							TPM0_IRQn					/* TPM0 single interrupt vector for all sources IRQ number*/
#define IO_INT_TPM1_IRQ_NUMBER							TPM1_IRQn					/* TPM1 single interrupt vector for all sources IRQ number*/
#define IO_INT_TPM2_IRQ_NUMBER 							TPM2_IRQn					/* TPM2 single interrupt vector for all sources IRQ number*/
#define IO_INT_RTC_ALARM_IRQ_NUMBER 					RTC_IRQn					/* RTC alarm interrupt IRQ number */
#define IO_INT_RTC_SECONDS_IRQ_NUMBER					RTC_Seconds_IRQn			/* RTC seconds interrupt IRQ number*/
#define IO_INT_PIT_IRQ_NUMBER							PIT_IRQn					/* PIT single interrupt vector for all channels IRQ number */
#define IO_INT_I2S0_IRQ_NUMBER							I2S0_IRQn					/* I2S0 Single interrupt vector for all sources IRQ number */
#define IO_INT_USB_OTG_IRQ_NUMBER						USB0_IRQn					/* USB0 OTG IRQ number*/
#define IO_INT_DAC0_IRQ_NUMBER							DAC0_IRQn					/* DAC0 interrupt IRQ number*/
#define IO_INT_TSI0_IRQ_NUMBER							TSI0_IRQn					/* TSI0 interrupt IRQ number*/
#define IO_INT_MCG_IRQ_NUMBER							MCG_IRQn					/* MCG interrupt IRQ number*/
#define IO_INT_LPTMR0_IRQ_NUMBER						LPTMR0_IRQn					/* LPTMR0 interrupt IRQ number*/
/* Reserved interrupt 									Reserved45_IRQn												*/
#define IO_INT_PORT_CONTROL_MODULE1_IRQ_NUMBER			PORTA_IRQn					/* PORTA pin detect IRQ number */
#define IO_INT_PORT_CONTROL_MODULE2_IRQ_NUMBER			PORTC_PORTD_IRQn			/* Single interrupt vector for PORTC and PORTD pin detect IRQ number */

#define IO_INT_PRIO_00                           	  	0  							/*  priority level for peripheral devices  (0 priority is the highest) */
#define IO_INT_PRIO_01                             	    1   							/*  priority level for peripheral devices  (0 priority is the highest) */
#define IO_INT_PRIO_02                                  2   							/*  priority level for peripheral devices  (0 priority is the highest) */
#define IO_INT_PRIO_03                                	3   							/*  priority level for peripheral devices  (0 priority is the highest) */

extern const Io_Int_CnfTypeStruct Io_Int_Cnf[];
extern const Io_Int_InterruptTypeStruct Io_Int_InterruptCnf[];

#endif /* IO_INT_CNF_H */

