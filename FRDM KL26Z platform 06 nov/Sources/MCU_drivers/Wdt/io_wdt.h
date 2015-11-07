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

$Log: io_wdt.h  $

$Author: Leonte Alexandru $

$Purpose: Provide common watchdog module routines

****************************************************************************/

#ifndef IO_WDT_H
#define IO_WDT_H


#include "MKL26Z4.h"
#include "Platform_Types/std_types.h"
#include "Platform_Types/powersar_addon_types.h"
#include "Platform_Types/platform_types.h"

#define IO_WDT_COP_DISABLED 								0
#define IO_WDT_COP_BUS_CLOCK_CYCLE_1						1
#define IO_WDT_COP_BUS_CLOCK_CYCLE_2						2
#define IO_WDT_COP_BUS_CLOCK_CYCLE_3						3

extern void Io_Wdt_Init(void);
extern void Io_Wdt_Service(void);
extern void Io_Wdt_Shutdown(void);
extern void Io_Wdt_Clear(void);

#endif /* IO_WDT_H */
