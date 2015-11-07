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

$Log: io_hbr_ti8833.h $

$Author: Bogdan Corina $

 ****************************************************************************/

#ifndef IO_HBR_TI8833_H
#define IO_HBR_TI8833_H


#include "MKL26Z4.h"
#include "Platform_Types/std_types.h"
#include "Platform_Types/powersar_addon_types.h"
#include "Platform_Types/platform_types.h"

//H-bridge modes definition

#define IO_HBR_DRV8833_STATE_FORWARD	1
#define IO_HBR_DRV8833_STATE_REVERSE	2
#define IO_HBR_DRV8833_STATE_BRAKE      3
#define IO_HBR_DRV8833_STATE_HIGHZ 		4
#define IO_HBR_DRV8833_STATE_SLEEP 	    5

#define IO_HBR_MOTORS_LEFT				0
#define IO_HBR_MOTORS_RIGHT				1

typedef struct Io_Hbr_Drv8833_Port_Struct_tag Io_Hbr_Drv8833_Port_Struct;
typedef struct Io_Hbr_Drv8833_Cnf_Struct_tag Io_Hbr_Drv8833_Cnf_Struct;



struct Io_Hbr_Drv8833_Port_Struct_tag
{
	uint32 hbr_in1; //pwm input
	uint16 hbr_in2;
	uint16 hbr_stby;
};
struct Io_Hbr_Drv8833_Cnf_Struct_tag
{
	uint8 nr_of_drv8833_hbrs;
	const Io_Hbr_Drv8833_Port_Struct *hbr_drv8833_pin_ptr;
} ;

extern void Io_Hbr_Drv8833_Initialization(const Io_Hbr_Drv8833_Cnf_Struct *ptr_cfg);


/* this interface sets the mode in which the  specified h-bridge will work
 * @hbr_nr is the number of the H-bridge you want to control
 * @hbr_state indicates the H-bridge state
 * @hbr_state can get values from 0 to 255 but only the values 1,2,3,4,5 represent correct modes
 *
 * 1 -> IO_HBR_DRV8833_STATE_REVERSE	//backward
   2 -> IO_HBR_DRV8833_STATE_FORWARD	//forward
   3 -> IO_HBR_DRV8833_STATE_BRAKE
   4 ->  IO_HBR_DRV8833_STATE_HIGHZ //coast state
   5 -> IO_HBR_DRV8833_STATE_SLEEP

 */
extern void Io_Hbr_Drv8833_Set_State(uint8 hbr_nr, uint8 hbr_state);

/* this interface returns the  mode in which the specified H-bridge works
 * the returned values are between 1 and 4 :
 *
 *  1-> IO_HBR_DRV8833_STATE_REVERSE	//backward
   2 -> IO_HBR_DRV8833_STATE_FORWARD	//forward
   3 -> IO_HBR_DRV8833_STATE_BRAKE
   4 ->  IO_HBR_DRV8833_STATE_HIGHZ //coast state
   5 -> IO_HBR_DRV8833_STATE_SLEEP
   @hbr_nr is the name/number of the h-bridge
 */
extern uint8 Io_Hbr_Drv8833_Get_State(uint8 hbr_nr);

/* this interface controls the direction and the speed for the motor specified as an argument
 * @direction -0 - BACKWARD
 * 			  -1 - FORWARD
 *
 * @dutycycle:physical values 0->100% , hex limits 0000h-4000h

 */
extern void Io_Hbr_Drv8833_Update(uint8 direction,uint16 dutycycle,uint8 hbr_nr);

#endif /* IO_HBR_TI8833_H */
