/**************************************************************************

COPYRIGHT (C) $Date: Sept 1, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_bluetooth.h $

$Author: Iovescu Raul $

 ****************************************************************************/

#ifndef IO_BLUETOOTH_H
#define IO_BLUETOOTH_H


#include "MKL26Z4.h"
#include "Platform_Types/std_types.h"
#include "Platform_Types/powersar_addon_types.h"
#include "Platform_Types/platform_types.h"

#define RIGHT 6
#define LEFT 4
#define FW 8
#define BW 2
#define WAIT 5
#define SLEEP_CAR 0
#define PARK 9
#define RECEIVE -1
#define OBSTACLE 10
#define PLUS 11
#define MINUS 12

#define delay_send 10

/*** TODO IOVESCU: not used in this release; Oct 30, 2015
#define GREEN 2
#define RED 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define YELLOW 7
#define WHITE 8
#define ERASE 9
***/

extern void Io_Bluetooth_State(void);
extern  int state;
extern  int wait;
extern int dutycycle;
extern char sensor;

#endif /* IO_BLUETOOTH_H */

