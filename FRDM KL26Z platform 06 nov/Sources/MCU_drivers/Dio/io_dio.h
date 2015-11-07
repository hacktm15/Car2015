/****************************************************************************

COPYRIGHT (C) $Date: Aug 1, 2015
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_dio.h $

$Author: Flueran Gabriel $

 ****************************************************************************/

#ifndef DIO_H
#define DIO_H


/** Includes **/

#include "MKL26Z4.h"
#include "Platform_Types/std_types.h"
#include "Platform_Types/powersar_addon_types.h"
#include "Platform_Types/platform_types.h"

/** end of Includes **/


/** Defines **/

	// None so far.

/** Defines **/


/** Structure Typedefs and Nested Structures **/

	// None so far.

/** end of Structure Typedefs and Nested Structures **/


/** External Global variables and constants **/

extern const FGPIO_MemMapPtr Io_Dio_PortTab[5];

/** end of External Global variables and constants **/


/** External Interfaces prototypes **/

/* FUNCTION NAME: Io_Dio_SetPinLevel
 * DESCRIPTION: This interface set the pin level of the respective channel
 * @PortPin - indicates port and pin
 *    - bits 0-7 are used to code Pin information
 *    - bits 8-15 are used to code Port information
 * @Level - the level of pin
 *    - 0 low level
 *    - 1 high level
 */
extern void Io_Dio_SetPinLevel(uint16 PortPin, uint8 Level);

/* FUNCTION NAME: Io_Dio_GetPinLevel
 * DESCRIPTION: This interface returns the current level of a specific channel
 * @PortPin - indicates port and pin
 *    - bits 0-7 are used to code Pin information
 *    - bits 8-15 are used to code Port information
 *    -> @return the pin Level (LOW / HIGH)
 */
extern uint8 Io_Dio_GetPinLevel(uint16 PortPin);

/* FUNCTION NAME: Io_Dio_TurnOnRgb
 * DESCRIPTION: This interface turns on all the LEDs of the RGB.
 */
extern void Io_Dio_TurnOnRgb(void);

/* FUNCTION NAME: Io_Dio_TurnOffRgb
 * DESCRIPTION: This interface turns off all the LEDs of the RGB
 */
extern void Io_Dio_TurnOffRgb(void);

/** end of External Interfaces prototypes **/


#endif
