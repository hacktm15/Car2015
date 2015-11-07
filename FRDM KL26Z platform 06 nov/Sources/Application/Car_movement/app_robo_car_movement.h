/**************************************************************************

COPYRIGHT (C) $Date: Sep 4, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: app_robo_car_movement.h $

$Author: Flueran Gabriel $

 ****************************************************************************/

#ifndef APP_ROBO_CAR_MOVEMENT_H
#define APP_ROBO_CAR_MOVEMENT_H


#include "MKL26Z4.h"
#include "Platform_Types/std_types.h"
#include "Platform_Types/powersar_addon_types.h"
#include "Platform_Types/platform_types.h"

/** Defines **/

#define ALGO_ROBO_CM_MIN_DUTYCYCLE		15
#define ALGO_ROBO_CM_MAX_DUTYCYCLE		70

/** end of Defines **/

/** External Global variables and constants **/

extern uint32 Algo_Robo_Cm_TimerRotateLeft;
extern uint32 Algo_Robo_Cm_TimerRotateRight;
extern uint32 Algo_Robo_Cm_TimerMoveForward;
extern uint32 Algo_Robo_Cm_TimerMoveBackward;

/** end of External Global variables and constants **/

/** External Interfaces prototypes **/

/* FUNCTION NAME: Algo_Robo_Cm_InitializeCarMovement
 * DESCRIPTION: Initializes the variables used by the Car Movement module.
 * @ void
 */
extern void Algo_Robo_Cm_InitializeCarMovement(void);

/* FUNCTION NAME: Algo_Robo_Cm_UpdateCarSpeed
 * DESCRIPTION: Abruptly changes the car speed to the desired dutycycle, in the specified direction.
 * @ direction -
 * @ dutycycle -
 */
extern void Algo_Robo_Cm_UpdateCarSpeed(uint8 direction,uint16 dutycycle);

/* FUNCTION NAME: Algo_Robo_Cm_MoveCarForward
 * DESCRIPTION: Moves the car forward, incrementing the speed up to the specified dutycycle.
 * @ dutycycle -
 */
extern void Algo_Robo_Cm_MoveCarForward(uint16 dutycycle);

/* FUNCTION NAME: Algo_Robo_Cm_MoveCarBackward
 * DESCRIPTION: Moves the car backward, incrementing the speed up to the specified dutycycle.
 * @ dutycycle -
 */
extern void Algo_Robo_Cm_MoveCarBackward(uint16 dutycycle);

/* FUNCTION NAME: Algo_Robo_Cm_RotateCarLeft
 * DESCRIPTION: Moves the car to the left, updating the speed to the set dutycycle.
 * @ dutycycle -
 */
extern void Algo_Robo_Cm_RotateCarLeft(uint16 dutycycle);

/* FUNCTION NAME: Algo_Robo_Cm_RotateCarRight
 * DESCRIPTION: Moves the car to the right, updating the speed to the set dutycycle.
 * @ dutycycle -
 */
extern void Algo_Robo_Cm_RotateCarRight(uint16 dutycycle);

/* FUNCTION NAME: Algo_Robo_Cm_BreakCar
 * DESCRIPTION: Car shortbrake is performed.
 * @ void
 */
extern void Algo_Robo_Cm_BreakCar(void);

/* FUNCTION NAME: Algo_Robo_Cm_StopCar
 * DESCRIPTION: Car is stopped.
 * @ void
 */
extern void Algo_Robo_Cm_StopCar(void);

/** end of External Interfaces prototypes **/

#endif /* SOURCES_APPLICATION_ALGO_CAR_MOVEMENT_APP_ROBO_CAR_MOVEMENT_H_ */

