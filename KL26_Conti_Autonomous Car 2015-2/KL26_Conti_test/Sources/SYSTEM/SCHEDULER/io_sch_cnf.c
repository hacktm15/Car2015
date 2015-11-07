/****************************************************************************

COPYRIGHT (C) $Date: 2012/05/10 14:20:43CEST $
$CompanyInfo:  $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_sch_cnf.c  $

 ****************************************************************************/

#include "SYSTEM/OS/io_os.h"
#include "SYSTEM/SCHEDULER/io_sch_cnf.h"

#include "MCU_DRIVERS/ADC/io_adc_cnf.h"
#include "MCU_DRIVERS/DIO/io_dio.h"
#include "MCU_DRIVERS/INT/io_int_cnf.h"
#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"
#include "MCU_DRIVERS/TIMER/io_tim.h"
#include "MCU_DRIVERS/TPM/io_tpm_cnf.h"
#include "MCU_DRIVERS/ASY/io_bluetooth.h"


#include "HW_INTERFACES/H_BRIDGE/io_hbr_cnf.h"
#include "HW_INTERFACES/SENSORS/sensors.h"
#include "HW_INTERFACES/STEPPER_MOTOR/io_smc_cnf.h"

#include "APPLICATION/ALGO/DISTANCE_CALC/app_dist_calc.h"
#include "APPLICATION/ALGO/PATH_PLANNER/app_path_planner.h"
#include "APPLICATION/ALGO/CAR_MOVEMENT/app_robo_car_movement.h"
#include "APPLICATION/ALGO/SPEED_CALC/app_robo_speed_calc.h"

#include "TEST_FUNCTIONS/io_tpm_test.h"

#include "io_sch_cnf.h"

static void Io_Sch_PrjHookTaskBackground(void);
static void Io_Sch_PrjHookTask1ms(void);
static void Io_Sch_PrjHookTask10ms(void);
static void Io_Sch_PrjHookTask100ms(void);
static void Io_Sch_PrjHookTask50ms(void);
static void Io_Sch_PrjHookTask1000ms(void);

/** For debugging purposes: to see how often the tasks were called */
uint32 Io_Sch_TaskCounter0ms;
uint32 Io_Sch_TaskCounter1ms;
uint32 Io_Sch_TaskCounter10ms;
uint32 Io_Sch_TaskCounter100ms;
uint32 Io_Sch_TaskCounter50ms;
uint32 Io_Sch_TaskCounter1000ms;

uint8 s = 0, m = 0, h = 0;

const Io_Sch_OsConfigTaskStruct Io_Sch_OsTasks[]=
{
		/*  Period         Function           */
		{    0, Io_Sch_PrjHookTaskBackground},
		{    1, Io_Sch_PrjHookTask1ms},
		{   10, Io_Sch_PrjHookTask10ms},
		{   50, Io_Sch_PrjHookTask50ms},
		{  100, Io_Sch_PrjHookTask100ms},
		{ 1000, Io_Sch_PrjHookTask1000ms}
};

const Io_Sch_OsConfigStruct Io_Sch_OsConfig[] =
{
		{
				sizeof(Io_Sch_OsTasks)/sizeof(Io_Sch_OsConfigTaskStruct),
				(Io_Sch_OsConfigTaskStruct *) Io_Sch_OsTasks
		}
};


void Io_Sch_PrjHookTaskBackground(void)
{
	Io_Sch_TaskCounter0ms++;
	Io_Os_PriorityHandler();

}

void Io_Sch_PrjHookTask1ms(void)
{
	Io_Sch_TaskCounter1ms++;
	Io_Os_PeriodicHandler();

	if(Io_Dio_GetPinLevel(CNF_IO_PCS_P0E_20) == IO_PCS_LEVEL_HIGH)
	{
		Io_Dio_SetPinLevel(CNF_IO_PCS_P0E_20,IO_PCS_LEVEL_LOW);
	}
	else
	{
		Io_Dio_SetPinLevel(CNF_IO_PCS_P0E_20,IO_PCS_LEVEL_HIGH);
	}

}

void Io_Sch_PrjHookTask10ms(void)  
{
	Io_Sch_TaskCounter10ms++;

	/* Read data from all the ADC channels */
	Io_Adc_Autoscan();

	/* Operations for sensors data */
	if(Sens_sensorSamplesCounter == SENS_NO_OF_MEASUREMENTS)
	{
		Sens_sensorSamplesCounter = 0;
	}
	else
	{
		// Do nothing; value is ok.
	}
	Algo_Dc_GetAllSensorsSample();

	Sens_sensorSamplesCounter++;

}

void Io_Sch_PrjHookTask50ms(void)
{
	Io_Sch_TaskCounter50ms++;
	Io_Bluetooth_State();

}

void Io_Sch_PrjHookTask100ms(void)
{
	Io_Sch_TaskCounter100ms++;

	/* Get distance values from the sensors. */
	Algo_Dc_CalculateSensorsDistances();

	if(Algo_Robo_Pp_CarTask == ALGO_ROBO_PP_CAR_TASK_PARALLEL_PARK)
	{
		/* Increase timers, calculate covered distances. */
		Algo_Robo_Pp_CarDecisionScheduler();
		/* Determine the next state of the car based on the previously calculated values. */
		Algo_Robo_Pp_DetermineNextCarState();
	}
	else {}
}


void Io_Sch_PrjHookTask1000ms(void)
{

	Io_Sch_TaskCounter1000ms++;

	s++;
	if(s == 60)
	{
		m++;
		s = 0;
	}
	if(m == 60)
	{
		h++;
		m = 0;
	}
	if(h == 24)
	{
		h = 0;
	}

	/* Calculate distance covered by car & car speed. */
	//Algo_Robo_Dc_CalculateCarDistanceCovered();
	//Algo_Robo_Sc_CalculateCarSpeed(1000);

/*** TODO FLUERAN: not used in this release; Sept 29, 2015
	Algo_Robo_Sc_CarSpeedCompensation(ALGO_ROBO_SC_SPEED_TOLERANCE,CNF_TPM0_CHANNEL1,CNF_TPM0_CHANNEL2);

	if(Algo_Robo_Pp_CarTask == ALGO_ROBO_PP_CAR_TASK_TESTCASE1)
	{
		if(Algo_Robo_Pp_ParallelParkFlag == TRUE)
		{
			Algo_Robo_Cm_MoveCarForward(TestVariableDuty);
			Algo_Robo_Pp_ParallelParkFlag = FALSE;
		}
		else
		{
			Algo_Robo_Cm_StopCar();
			Algo_Robo_Dc_CalculateCarDistanceCovered();
			Algo_Robo_Sc_CalculateCarSpeed(1000);
			Algo_Robo_Pp_CarTask = ALGO_ROBO_PP_CAR_TASK_DEFAULT;
		}


// TODO FLUERAN: to be removed when code is in final form.
		if(Io_Sch_TaskCounter1000ms % 2 == 1)
		{
			Algo_Robo_Cm_MoveCarForward(ALGO_ROBO_PP_PARKING_DUTYCYCLE);
		}
		else
		{
			Algo_Robo_Cm_StopCar();
		}
	}
***/
}

