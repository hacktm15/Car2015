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

$Log: io_smc.h $

$Author: Bogdan Corina $

 ****************************************************************************/

#ifndef IO_SMC_H
#define IO_SMC_H


#include "MKL26Z4.h"
#include "Platform_Types/std_types.h"
#include "Platform_Types/powersar_addon_types.h"
#include "Platform_Types/platform_types.h"

typedef struct Io_Smc_Port_Struct_tag Io_Smc_Port_Struct;
typedef struct Io_Smc_Cnf_Struct_tag Io_Smc_Cnf_Struct;

#define	IO_SMC_STATE_UNDEFINED 0xFF
#define	IO_SMC_STATE_STEPPING_FORWARD 1
#define	IO_SMC_STATE_STEPPING_BACKWARD 2
#define IO_SMC_STATE_STOP 3
#define	IO_SMC_STATE_IDLE 4
#define	IO_SMC_STATE_SLEEP 5

#define	IO_SMC_WAVE_DRIVE 1
#define	IO_SMC_FULLSTEP_DRIVE 2

#define IO_SMC_STEP_0 0
#define IO_SMC_STEP_1 1
#define IO_SMC_STEP_2 2
#define IO_SMC_STEP_3 3
#define IO_SMC_STEP_4 4
#define IO_SMC_STEP_5 5
#define IO_SMC_STEP_6 6
#define IO_SMC_STEP_7 7

struct Io_Smc_Port_Struct_tag
{  uint16 smc_in1;
   uint16 smc_in2;
   uint16 smc_in3;
   uint16 smc_in4;
   uint16 smc_sleep;
   uint8 drive_mode;
   uint16 step_time;


};
struct Io_Smc_Cnf_Struct_tag
{
	uint8_t nr_of_sms;//number of stepper motors
	const Io_Smc_Port_Struct *smc_pin_ptr;
} ;
//this interface initializes all outputs related to HBR control for all stepper motors configured (can be more than one)
//allocates memory and clears the counters needed for moving the motor step by step
extern void Io_Smc_Initialize(const Io_Smc_Cnf_Struct *smc_conf);

extern void Io_Smc_Shutdown(void);
/*This interface shall be used to set specific HBR IC direction
 * and number of steps that are required by user.
 * The steps will be generated with drive pattern configured by user (initialization configuration).
 * @smotor_nr : number of motor for which you want to change the direction and number of steps
 * @direction : possible values 0,1
 *  0 ->IO_SMC_STATE_STEPPING_FORWARD
 *  1 ->IO_SMC_STATE_STEPPING_BACKWARD
 * @step_nr :number of steps which you want the motor to do, max value : 65535
 * */
extern void Io_Smc_Update(uint8 smotor_nr,uint8 direction, uint16 step_nr);

/*
 * this method creates the condition for moving the motor 1,2,3 or 4 steps
 * the method get the number of the stepper motor as a parameter and sets its inputs
 *
 */
 extern void Io_Smc_Step_Manager(uint8 smotor_nr);
/*this interface sets the mode in which the  specified stepper motor will work
@smotor_nr - is the number of the stepper motor you want to change the state for
@state -possible working modes
2-> IO_SMC_STATE_STOP
3-> IO_SMC_STATE_IDLE
4-> IO_SMC_STATE_SLEEP
 */
extern void Io_Smc_Set_State(uint8 smotor_nr,uint8 state);
/*
 * this interface returns the  mode in which the specified stepper motor  work
 *the returned values are between 0 and 4 :
 * 0 ->IO_SMC_STATE_STEPPING_FORWARD
 * 1 ->IO_SMC_STATE_STEPPING_BACKWARD
   2 ->IO_SMC_STATE_STOP
   3 ->IO_SMC_STATE_IDLE
   4 ->IO_SMC_STATE_SLEEP
 *
 */
extern uint8 Io_Smc_Get_State(uint8 smotor_nr);
extern void stepper_function_test(uint8 motor_nr,uint8 step);
extern  void Io_Smc_Switch_Steps_FSD(uint8 step,uint8 motor_nr);

#endif /* IO_SMC_H */
