/****************************************************************************

COPYRIGHT (C) $Date: Sept 1, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_wdt.c  $

$Author: Leonte Alexandru $

$Purpose: Provide common watchdog module routines

****************************************************************************/

#include "MCU_drivers/Int/io_int_cnf.h"

#include "io_wdt.h"

void Io_Wdt_Init(void)
{
	 SIM_COPC = SIM_COPC_COPT(IO_WDT_COP_BUS_CLOCK_CYCLE_3)		/* COP timeout after 2^10 LPO cycles or 2^18 bus clock cycles */
	  			| SIM_COPC_COPW_MASK							/* Windowed mode */
				| SIM_COPC_COPCLKS_MASK ;						/* Bus clock is source to COP */

}

/* FUNCTION NAME: Io_Wdt_Service
 * DESCRIPTION: Watchdog timer service routine. Writing 0x55 followed by 0xAA
 * 				will unlock the write once registers in the WDOG so they are
 * 				writable within the WCT period.
 */
void Io_Wdt_Service(void)
{
	Io_Int_DisableInterrupts();
	SIM->SRVCOP =	0x55;
	SIM->SRVCOP =	0xAA;
	Io_Int_EnableInterrupts();

   /* Reset WDT timer */
   //__asm__ volatile ("clrwdt");
}

void Io_Wdt_Shutdown(void)
{
	/* Shutdowns the watchdog timer */

}

void Io_Wdt_Clear(void)
{
	 /* Clears the watchdog timer (it makes the timer restart from zero) */

}
