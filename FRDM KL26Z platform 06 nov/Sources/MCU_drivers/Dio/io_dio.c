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

$Log: io_dio.c $

$Author: Flueran Gabriel $

 ****************************************************************************/

/** Includes **/

#include "MCU_drivers/Pcs/io_pcs_cnf.h"

#include "Other_functions/io_func.h"

#include "io_dio.h"

/** end of Includes **/

/** Local Functions prototypes **/

	// None so far.

/** end of Local Functions prototypes **/

/** Global variables and constants **/

const FGPIO_MemMapPtr Io_Dio_PortTab[5] = FGPIO_BASE_PTRS;

/** end of Global variables and constants **/

/** Functions implementation **/

	/** External Interfaces implementation **/

void Io_Dio_SetPinLevel(uint16 PortPin, uint8 Level)
{
	uint8 Port;
	uint8 Pin;

	/* Get the Port */
	Port = IO_PCS_GET_PORT(PortPin);
	/* Get the Pin */
	Pin  = IO_PCS_GET_PIN(PortPin);

	if(Level == IO_PCS_LEVEL_HIGH)
	{
		FGPIO_PSOR_REG(Io_Dio_PortTab[Port]) = FGPIO_PDOR_REG(Io_Dio_PortTab[Port]) | (1 << Pin);
	}
	else
	{
		FGPIO_PCOR_REG(Io_Dio_PortTab[Port]) = FGPIO_PCOR_REG(Io_Dio_PortTab[Port]) | (1 << Pin);
	}
}

uint8 Io_Dio_GetPinLevel(uint16 PortPin)
{
	uint8 test_dir;
	uint8 Level;
	uint8 Port;
	uint8 Pin;

	Port = IO_PCS_GET_PORT(PortPin);
	Pin  = IO_PCS_GET_PIN(PortPin);

	test_dir = Io_Pcs_GetPinInfo(PortPin, IO_PCS_DIRECTION_INFO); /*pin direction*/
	if(test_dir == IO_PCS_OUTPUT)
	{
		/* Get pin level for output */
		Level = (uint8)( Io_Func_ShrU32((FGPIO_PDOR_REG(Io_Dio_PortTab[Port]) & Io_Func_ShlU32(1, Pin)), Pin));
	}
	else
	{
		if(test_dir == IO_PCS_INPUT)
		{
			/* Get pin level for input */
			Level = (uint8)( Io_Func_ShrU32((FGPIO_PDIR_REG(Io_Dio_PortTab[Port]) & Io_Func_ShlU32(1, Pin)), Pin));
		}
		else {}
	}
	return Level;
}

/* FUNCTION NAME: Io_Dio_TurnOnRgb
 * DESCRIPTION: This interface turns on all the LEDs of the RGB.
 */
void Io_Dio_TurnOnRgb(void)
{
	/* Turn off the LEDs of the RGB */
	Io_Dio_SetPinLevel(SET_LED_GREEN,LED_ON);
	Io_Dio_SetPinLevel(SET_LED_RED,LED_ON);
	Io_Dio_SetPinLevel(SET_LED_BLUE,LED_ON);
}

/* FUNCTION NAME: Io_Dio_TurnOffRgb
 * DESCRIPTION: This interface turns off all the LEDs of the RGB.
 */
void Io_Dio_TurnOffRgb(void)
{
	/* Turn off the LEDs of the RGB */
	Io_Dio_SetPinLevel(SET_LED_GREEN,LED_OFF);
	Io_Dio_SetPinLevel(SET_LED_RED,LED_OFF);
	Io_Dio_SetPinLevel(SET_LED_BLUE,LED_OFF);
}

	/** end of External Interfaces implementation **/

	/** Local Functions implementation **/

		// None so far.

	/** end of Local Functions implementation **/

	/** Interrupts Handlers implementation **/

		// None so far.

	/** end of Interrupts Handlers implementation **/

/** end of Functions implementation **/


