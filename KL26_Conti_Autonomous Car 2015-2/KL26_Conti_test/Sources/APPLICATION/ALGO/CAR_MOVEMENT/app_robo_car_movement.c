/*
 * app_robo_car_movement.c
 *
 *  Created on: Sep 4, 2015
 *      Author: uidn9990
 */

#include "MCU_DRIVERS/TPM/io_tpm_cnf.h"

#include "HW_INTERFACES/H_BRIDGE/io_hbr_cnf.h"
#include "HW_INTERFACES/SENSORS/sensors.h"
#include "HW_INTERFACES/STEPPER_MOTOR/io_smc_cnf.h"


#include "APPLICATION/ALGO/DISTANCE_CALC/app_dist_calc.h"
#include "APPLICATION/ALGO/PATH_PLANNER/app_path_planner.h"
#include "APPLICATION/ALGO/SPEED_CALC/app_robo_speed_calc.h"

#include "app_robo_car_movement.h"

/** Global variables and constants **/

uint32 Algo_Robo_Cm_TimerRotateLeft;
uint32 Algo_Robo_Cm_TimerRotateRight;
uint32 Algo_Robo_Cm_TimerMoveForward;
uint32 Algo_Robo_Cm_TimerMoveBackward;

/** end of Global variables and constants **/

/** Local Functions prototypes **/

static uint16 Algo_Robo_Cm_LimitDutycycle(uint16 dutycycle);

/** end of Local Functions prototypes **/

/** Functions implementation **/

/* FUNCTION NAME: Algo_Robo_Cm_InitializeCarMovement
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Initializes the variables used by the Car Movement module.
 * OBSERVATIONS: -
 */
void Algo_Robo_Cm_InitializeCarMovement(void)
{
	Algo_Robo_Cm_TimerRotateLeft = 0;
	Algo_Robo_Cm_TimerRotateRight = 0;
	Algo_Robo_Cm_TimerMoveForward = 0;
	Algo_Robo_Cm_TimerMoveBackward = 0;
}

/* FUNCTION NAME: Algo_Robo_Cm_UpdateCarSpeed
 * RETURN TYPE: void
 * PARAMETERS: uint8 direction,uint16 dutycycle
 * DESCRIPTION: Abruptly changes the car speed to the desired dutycycle, in the specified direction.
 * OBSERVATIONS: -
 */
void Algo_Robo_Cm_UpdateCarSpeed(uint8 direction,uint16 dutycycle)
{
	Io_Hbr_Update(direction,dutycycle,IO_MOTORS_LEFT);
	Io_Hbr_Update(direction,dutycycle,IO_MOTORS_RIGHT);

	Algo_Robo_Pp_CarCurrentSpeedCmPerS = ALGO_ROBO_SC_CALCULATE_CAR_SPEED(dutycycle);
}

/* FUNCTION NAME: Algo_Robo_Cm_MoveCarForward
 * RETURN TYPE: void
 * PARAMETERS: uint16 dutycycle
 * DESCRIPTION: Moves the car forward, incrementing the speed up to the specified dutycycle.
 * OBSERVATIONS: -
 */
void Algo_Robo_Cm_MoveCarForward(uint16 dutycycle)
{
	dutycycle = Algo_Robo_Cm_LimitDutycycle(dutycycle);

	Algo_Robo_Cm_UpdateCarSpeed(HBR_STATE_FORWARD,dutycycle);
	Algo_Robo_Pp_CarMovement = ALGO_ROBO_PP_CAR_MOVING_FORWARD;
}

/* FUNCTION NAME: Algo_Robo_Cm_MoveCarBackward
 * RETURN TYPE: void
 * PARAMETERS: uint16 dutycycle
 * DESCRIPTION: Moves the car backward, incrementing the speed up to the specified dutycycle.
 * OBSERVATIONS: -
 */
void Algo_Robo_Cm_MoveCarBackward(uint16 dutycycle)
{
	dutycycle = Algo_Robo_Cm_LimitDutycycle(dutycycle);

	Algo_Robo_Cm_UpdateCarSpeed(HBR_STATE_BACKWARD,dutycycle);
	Algo_Robo_Pp_CarMovement = ALGO_ROBO_PP_CAR_MOVING_BACKWARD;
}

/* FUNCTION NAME: Algo_Robo_Cm_RotateCarLeft
 * RETURN TYPE: void
 * PARAMETERS: uint16 dutycycle
 * DESCRIPTION: Moves the car to the left, updating the speed to the set dutycycle.
 * OBSERVATIONS: -
 */
void Algo_Robo_Cm_RotateCarLeft(uint16 dutycycle)
{
	dutycycle = Algo_Robo_Cm_LimitDutycycle(dutycycle);

	Io_Hbr_Update(HBR_STATE_BACKWARD,dutycycle,IO_MOTORS_LEFT);
	Io_Hbr_Update(HBR_STATE_FORWARD,dutycycle,IO_MOTORS_RIGHT);
	Algo_Robo_Pp_CarMovement = ALGO_ROBO_PP_CAR_ROTATING_LEFT;

	Algo_Robo_Pp_CarCurrentSpeedCmPerS = 0;
}

/* FUNCTION NAME: Algo_Robo_Cm_RotateCarRight
 * RETURN TYPE: void
 * PARAMETERS: uint16 dutycycle
 * DESCRIPTION: Moves the car to the right, updating the speed to the set dutycycle.
 * OBSERVATIONS: -
 */
void Algo_Robo_Cm_RotateCarRight(uint16 dutycycle)
{
	dutycycle = Algo_Robo_Cm_LimitDutycycle(dutycycle);

	Io_Hbr_Update(HBR_STATE_FORWARD,dutycycle,IO_MOTORS_LEFT);
	Io_Hbr_Update(HBR_STATE_BACKWARD,dutycycle,IO_MOTORS_RIGHT);
	Algo_Robo_Pp_CarMovement = ALGO_ROBO_PP_CAR_ROTATING_RIGHT;

	Algo_Robo_Pp_CarCurrentSpeedCmPerS = 0;
}

/* FUNCTION NAME: Algo_Robo_Cm_BreakCar
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Car shortbrake is performed.
 * OBSERVATIONS: -
 */
void Algo_Robo_Cm_BreakCar(void)
{
	Io_Hbr_Set_State(IO_HBR_1,HBR_STATE_SHORTBRAKE);
	Io_Hbr_Set_State(IO_HBR_2,HBR_STATE_SHORTBRAKE);
	Algo_Robo_Pp_CarMovement = ALGO_ROBO_PP_CAR_STOPPED;

	Algo_Robo_Pp_CarCurrentSpeedCmPerS = 0;
}

/* FUNCTION NAME: Algo_Robo_Cm_StopCar
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Car is stopped.
 * OBSERVATIONS: -
 */
void Algo_Robo_Cm_StopCar(void)
{
	Io_Hbr_Set_State(IO_HBR_1,HBR_STATE_STOP);
	Io_Hbr_Set_State(IO_HBR_2,HBR_STATE_STOP);
	Algo_Robo_Pp_CarMovement = ALGO_ROBO_PP_CAR_STOPPED;

	Algo_Robo_Pp_CarCurrentSpeedCmPerS = 0;
}

/* FUNCTION NAME: Algo_Robo_Cm_LimitDutycycle
 * RETURN TYPE: void
 * PARAMETERS: uint16 dutycycle
 * DESCRIPTION: Limits the dutycycle so that calculated speed is approx. accurate.
 * OBSERVATIONS: private to "app_robo_car_movement.c"
 */
uint16 Algo_Robo_Cm_LimitDutycycle(uint16 dutycycle)
{
	uint16 limitedDutycycle = dutycycle;

	if(limitedDutycycle < ALGO_ROBO_CM_MIN_DUTYCYCLE)
	{
		limitedDutycycle = ALGO_ROBO_CM_MIN_DUTYCYCLE;
	}
	else
	{
		if(limitedDutycycle > ALGO_ROBO_CM_MAX_DUTYCYCLE)
		{
			limitedDutycycle = ALGO_ROBO_CM_MAX_DUTYCYCLE;
		}
		else {}
	}
	return limitedDutycycle;
}
/** end of Functions implementation **/
