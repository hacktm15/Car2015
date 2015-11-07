/****************************************************************************

COPYRIGHT (C) $Date: Aug 1, 2015
$CompanyInfo:  $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_dio.c $

$Author: Jivulescu Razvan $

 ****************************************************************************/

/** Includes **/

#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"

#include "OTHER_FUNCTIONS/io_func.h"

#include "io_dio.h"

/** end of Includes **/

/** Local Functions prototypes **/

	// None so far.

/** end of Local Functions prototypes **/

/** Global variables and constants **/

/* TODO FLUERAN: Initialization of all global variables should be done in the Initialization function of the module */
const FGPIO_MemMapPtr Io_Dio_PortTab[5] = FGPIO_BASE_PTRS;

/** end of Global variables and constants **/

/** Functions implementation **/

	/** External Interfaces implementation **/

uint8 Io_Dio_GetPinLevel(uint16 PortPin)
{
	uint8 test_dir;
	uint8 Level;
	uint8 Port;
	uint8 Pin;

	Port = IO_PCS_GET_PORT(PortPin);
	Pin  = IO_PCS_GET_PIN(PortPin);

	test_dir = Io_Pcs_GetInfo(PortPin, IO_PCS_DIRECTION_INFO); /*pin direction*/
	if(test_dir)
	{
		/* Get pin level for output */
		Level = (uint8)( Io_Func_ShrU32((FGPIO_PDOR_REG(Io_Dio_PortTab[Port]) & Io_Func_ShlU32(1, Pin)), Pin));
	}
	else
	{
		/* Get pin level for input */
		Level = (uint8)( Io_Func_ShrU32((FGPIO_PDIR_REG(Io_Dio_PortTab[Port]) & Io_Func_ShlU32(1, Pin)), Pin));
	}
	return (Level);
}

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
	/** end of External Interfaces implementation **/

/** Local Functions implementation **/

		// None so far.

	/** end of Local Functions implementation **/

	/** Interrupts Handlers implementation **/

		// None so far.

	/** end of Interrupts Handlers implementation **/

/** end of Functions implementation **/


