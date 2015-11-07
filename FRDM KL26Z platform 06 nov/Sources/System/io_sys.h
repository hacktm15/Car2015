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

$Log: io_sys.h $

$Author: PES contribution $

 ****************************************************************************/

#ifndef IO_SYS_H
#define IO_SYS_H


#include "MKL26Z4.h"
#include "Platform_Types/std_types.h"
#include "Platform_Types/powersar_addon_types.h"
#include "Platform_Types/platform_types.h"

/** Defines **/

#define IO_SYS_FRC_OSC_CLK    			(uint32)(8000000 / 2) /* Nominal FRC oscilator frequency */

#define IO_SYS_LPRC_OSC_CLK   			(uint32)(31000 / 2) /* Nominal FRC oscilator frequency */

#define IO_SYS_XT_OSC_CLK     			(uint32)(8000000 / 2) /* Nominal XT oscilator frequency */

#define IO_SYS_CLKDIV_RCDIV_8MHZ      	1
#define IO_SYS_CLKDIV_RCDIV_4MHZ      	2
#define IO_SYS_CLKDIV_RCDIV_2MHZ      	4
#define IO_SYS_CLKDIV_RCDIV_1MHZ      	8
#define IO_SYS_CLKDIV_RCDIV_500KHZ    	16
#define IO_SYS_CLKDIV_RCDIV_250KHZ    	32
#define IO_SYS_CLKDIV_RCDIV_125KHZ    	64
#define IO_SYS_CLKDIV_RCDIV_31P25KHZ 	256

#define IO_SYS_CLKDIV_DOZE_1P1      	1
#define IO_SYS_CLKDIV_DOZE_1P2      	2
#define IO_SYS_CLKDIV_DOZE_1P4      	4
#define IO_SYS_CLKDIV_DOZE_1P8      	8
#define IO_SYS_CLKDIV_DOZE_1P16 	    16
#define IO_SYS_CLKDIV_DOZE_1P32  		32
#define IO_SYS_CLKDIV_DOZE_1P64  	  	64
#define IO_SYS_CLKDIV_DOZE_1P128  		128

#define IO_SYS_CLKDIV_RCDIV    			IO_SYS_CLKDIV_RCDIV_8MHZ /* Prescaler for CPU:  */
#define IO_SYS_CLKDIV_DOZE     			IO_SYS_CLKDIV_DOZE_1P1   /* Postscaler for CPU and Periferals */

/* define the CPU frequency - in Hz */
#define IO_SYS_CPU_FREQ 				(IO_SYS_FRC_OSC_CLK / IO_SYS_CLKDIV_RCDIV / IO_SYS_CLKDIV_DOZE)

/* define the system frequency - in Hz */
#define IO_SYS_FREQ 					IO_SYS_CPU_FREQ

/* T1CON bit 15 */
/* TON: Timer1 On bit
1 = Starts 16-bit Timer1
0 = Stops 16-bit Timer1 */
#define IO_SYS_TON_ON 					(1 << 15)
#define IO_SYS_TON_OFF 					(0 << 15)

/* T1CON bit 13 */
/* TSIDL: Stop in Idle Mode bit
1 = Discontinue module operation when device enters Idle mode
0 = Continue module operation in Idle mode */
#define IO_SYS_TSIDL  					(0 << 13)

/* T1CON bit 6 */
/* TGATE: Timer1 Gated Time Accumulation Enable bit
When TCS = 1:
This bit is ignored.
When TCS = 0:
1 = Gated time accumulation enabled
0 = Gated time accumulation disabled */
#define IO_SYS_TGATE  					(0 << 6)

/* T1CON bits 5:4 */
/* TCKPS: Timer1 Input Clock Prescale Select bits
11 = 1:256
10 = 1:64
01 = 1:8
00 = 1:1 */
#define IO_SYS_TCKPS_PRESCALER_1_1      (0)
#define IO_SYS_TCKPS_PRESCALER_1_8      (1)
#define IO_SYS_TCKPS_PRESCALER_1_64     (2)
#define IO_SYS_TCKPS_PRESCALER_1_256    (3)

#define IO_SYS_TCKPS 					(IO_SYS_TCKPS_PRESCALER_1_8 << 4)

/* T1CON bit 2 */
/* TSYNC: Timer1 External Clock Input Synchronization Select bit
When TCS = 1:
1 = Synchronize external clock input
0 = Do not synchronize external clock input */
#define  IO_SYS_TSYNC 					(0 << 2)

/* T1CON bit 1 */
/* TCS: Timer1 Clock Source Select bit
1 = External clock from T1CK pin (on the rising edge)
0 = Internal clock (FOSC/2)*/
#define  IO_SYS_TCS   					(0 << 1)

/* T1CON bit 15 */
/* TON: Timer1 On bit
1 = Starts 16-bit Timer1
0 = Stops 16-bit Timer1 */
#define IO_SYS_TON_ON 					(1 << 15)
#define IO_SYS_TON_OFF 					(0 << 15)

/* T1CON bit 13 */
/* TSIDL: Stop in Idle Mode bit
1 = Discontinue module operation when device enters Idle mode
0 = Continue module operation in Idle mode */
#define IO_SYS_TSIDL  					(0 << 13)

/* T1CON bit 6 */
/* TGATE: Timer1 Gated Time Accumulation Enable bit
When TCS = 1:
This bit is ignored.
When TCS = 0:
1 = Gated time accumulation enabled
0 = Gated time accumulation disabled */
#define IO_SYS_TGATE  					(0 << 6)

/* T1CON bits 5:4 */
/* TCKPS: Timer1 Input Clock Prescale Select bits
11 = 1:256
10 = 1:64
01 = 1:8
00 = 1:1 */
#define IO_SYS_TCKPS_PRESCALER_1_1      (0)
#define IO_SYS_TCKPS_PRESCALER_1_8      (1)
#define IO_SYS_TCKPS_PRESCALER_1_64   	(2)
#define IO_SYS_TCKPS_PRESCALER_1_256  	(3)

#define IO_SYS_TCKPS_2 					(IO_SYS_TCKPS_PRESCALER_1_1 << 4)

/* T1CON bit 2 */
/* TSYNC: Timer1 External Clock Input Synchronization Select bit
When TCS = 1:
1 = Synchronize external clock input
0 = Do not synchronize external clock input */
#define  IO_SYS_TSYNC 					(0 << 2)

/* T1CON bit 1 */
/* TCS: Timer1 Clock Source Select bit
1 = External clock from T1CK pin (on the rising edge)
0 = Internal clock (FOSC/2)*/
#define  IO_SYS_TCS   					(0 << 1)

#define IO_SYS_T1CON_ON 	(IO_SYS_TON_ON | IO_SYS_TSIDL | IO_SYS_TGATE | IO_SYS_TCKPS | IO_SYS_TSYNC | IO_SYS_TCS)
#define IO_SYS_T1CON_OFF 	(IO_SYS_TON_OFF | IO_SYS_TSIDL | IO_SYS_TGATE | IO_SYS_TCKPS | IO_SYS_TSYNC | IO_SYS_TCS)

#define IO_SYS_T2CON_ON 	(IO_SYS_TON_ON | IO_SYS_TSIDL | IO_SYS_TGATE | IO_SYS_TCKPS_2 | IO_SYS_TSYNC | IO_SYS_TCS)
#define IO_SYS_T2CON_OFF 	(IO_SYS_TON_OFF | IO_SYS_TSIDL | IO_SYS_TGATE | IO_SYS_TCKPS_2 | IO_SYS_TSYNC | IO_SYS_TCS)

/* define the Timer 2 frequency - in Hz */
#define IO_SYS_FREQ_TMR2 				(IO_SYS_CPU_FREQ / (2 ^ (IO_SYS_TCKPS_2 >> 4)))

/** end of Defines **/

#endif /* IO_SYS_H */
