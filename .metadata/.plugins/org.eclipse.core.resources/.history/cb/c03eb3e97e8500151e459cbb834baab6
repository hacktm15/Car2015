/**************************************************************************

COPYRIGHT (C) $Date: Aug 31, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: app_robo_path_planner.h $

$Author: Flueran Gabriel $

 ****************************************************************************/

#ifndef APP_ROBO_PATH_PLANNER_H
#define APP_ROBO_PATH_PLANNER_H


#include "MKL26Z4.h"
#include "Platform_Types/std_types.h"
#include "Platform_Types/powersar_addon_types.h"
#include "Platform_Types/platform_types.h"

/** Defines **/

	/* Macros */

/* TODO FLUERAN: to be made independent of surface on which car is running. */
#define ALGO_ROBO_PP_CALCULATE_ROTATION_TIME(dutycycle)		(uint32)(31)

	/* end of Macros */

#define ALGO_ROBO_PP_CAR_STATE_DEFAULT 			0
#define ALGO_ROBO_PP_CAR_STATE_INITIAL			1
#define ALGO_ROBO_PP_CAR_STATE_SPOT_DETECTION 	2
#define ALGO_ROBO_PP_CAR_STATE_SPOT_CALC		3
#define ALGO_ROBO_PP_CAR_STATE_SPOT_DETECTED 	4
#define ALGO_ROBO_PP_CAR_STATE_PARALLEL_PARK 	5
#define ALGO_ROBO_PP_CAR_STATE_CAR_PARKED		6
#define ALGO_ROBO_PP_CAR_STATE_PENDING 			100

#define ALGO_ROBO_PP_CAR_PENDING_TIMER_100MS_MAX	100 // 100 ms * 100 = 10 s
#define ALGO_ROBO_PP_CAR_PENDING_TIMER_200MS_MAX	50 	// 200 ms * 50 = 10 s

#define ALGO_ROBO_PP_CAR_PENDING_TIMER_MAX		ALGO_ROBO_PP_CAR_PENDING_TIMER_100MS_MAX

#define ALGO_ROBO_PP_CAR_STOPPED				0
#define ALGO_ROBO_PP_CAR_MOVING_FORWARD			1
#define ALGO_ROBO_PP_CAR_MOVING_BACKWARD		2
#define ALGO_ROBO_PP_CAR_ROTATING_LEFT			3
#define ALGO_ROBO_PP_CAR_ROTATING_RIGHT			4

#define ALGO_ROBO_PP_CAR_TASK_DEFAULT			0
#define ALGO_ROBO_PP_CAR_TASK_PARALLEL_PARK		1
#define ALGO_ROBO_PP_CAR_TASK_TESTCASE1			10

#define ALGO_ROBO_PP_CAR_LENGTH_CM				20
#define ALGO_ROBO_PP_CAR_WIDTH_CM				18

#define ALGO_ROBO_PP_SENSOR_PLACEMENT_ERROR_CM	0
#define ALGO_ROBO_PP_SENSOR_PLACEMENT_ERROR_MM	0

#define ALGO_ROBO_PP_FRONT_REAR_DIST_THOLD_CM	10
#define ALGO_ROBO_PP_RIGHT_LEFT_DIST_THOLD_CM	5

/*** Not used in this release Sept 3, 2015
#define ALGO_ROBO_PP_LENGTH_THRESHOLD_CM		22
#define ALGO_ROBO_PP_WIDTH_THRESHOLD_CM			20
#define ALGO_ROBO_PP_LENGTH_THRESHOLD_MM		220
#define ALGO_ROBO_PP_WIDTH_THRESHOLD_MM			200
***/

#define ALGO_ROBO_PP_CAR_LENGTH_MM				200
#define ALGO_ROBO_PP_CAR_WIDTH_MM				180

#define ALGO_ROBO_PP_FRONT_REAR_DIST_THOLD_MM	100
#define ALGO_ROBO_PP_RIGHT_LEFT_DIST_THOLD_MM	50

#define ALGO_ROBO_PP_PARKING_DUTYCYCLE			70

/** end of Defines **/

/** External Global variables and constants **/

extern uint8 Algo_Robo_Pp_CarTask;

extern uint8 Algo_Robo_Pp_CarState;
extern uint8 Algo_Robo_Pp_LastCarState;

extern uint8 Algo_Robo_Pp_CarMovement;
extern uint8 Algo_Robo_Pp_LastCarMovement;

extern uint16 Algo_Robo_Pp_CoveredDistanceCm;
extern uint16 Algo_Robo_Pp_CarCurrentSpeedCmPerS;

extern uint16 Algo_Robo_Pp_SpotLengthMm;
extern uint16 Algo_Robo_Pp_MoveBackMm;
extern uint16 Algo_Robo_Pp_MoveForwardMm;
extern uint8 Algo_Robo_Pp_DistanceLastObstacleRightCm;

extern uint32 Algo_Robo_Pp_TimerCarStopped;
extern uint32 Algo_Robo_Pp_TimerCarMoveForward;
extern uint32 Algo_Robo_Pp_TimerCarMoveBackward;
extern uint32 Algo_Robo_Pp_TimerCarRotateLeft;
extern uint32 Algo_Robo_Pp_TimerCarRotateRight;

extern uint32 Algo_Robo_Pp_TimerPendingState;
extern uint32 Algo_Robo_Pp_TimerDefaultState;
extern uint32 Algo_Robo_Pp_TimerInitialState;
extern uint32 Algo_Robo_Pp_TimerSpotDetectionState;
extern uint32 Algo_Robo_Pp_TimerSpotCalcState;
extern uint32 Algo_Robo_Pp_TimerSpotDetectedState;
extern uint32 Algo_Robo_Pp_TimerParallelParkState;
extern uint32 Algo_Robo_Pp_TimerCarParkedState;

extern uint8 Algo_Robo_Pp_ParallelParkFlag;

/** end of External Global variables and constants **/

/** External Interfaces prototypes **/

extern void Algo_Robo_Pp_IncrementalCarAcceleration(uint16 finalDutycycle, uint8 step);

/* FUNCTION NAME: Algo_Robo_Pp_InitializePathPlanner
 * DESCRIPTION: Initializes the variables used by this module.
 * @ void
 */
extern void Algo_Robo_Pp_InitializePathPlanner(void);

/* FUNCTION NAME: Algo_Robo_Pp_StartParallelParking
 * DESCRIPTION: Starts the Parallel Parking algorithm.
 * @ void
 */
extern void Algo_Robo_Pp_StartParallelParking(void);

/* FUNCTION NAME: Algo_Robo_Pp_ParallelParkingAlgorithm
 * DESCRIPTION: The algorithm to park the car when free parking place is spotted.
 * @ void
 */
extern void Algo_Robo_Pp_ParallelParkingAlgorithm(void);

/* FUNCTION NAME: Algo_Robo_Pp_CarDecisionScheduler
 * DESCRIPTION:
 * @ void
 */
extern void Algo_Robo_Pp_CarDecisionScheduler(void);

/* FUNCTION NAME: Algo_Robo_Pp_CarDecisionParallelPark
 * DESCRIPTION:
 * @ void
 */
extern void Algo_Robo_Pp_CarDecisionParallelPark(void);

/* FUNCTION NAME: Algo_Robo_Pp_DetermineNextCarState
 * DESCRIPTION:
 * @ void
 */
extern void Algo_Robo_Pp_DetermineNextCarState(void);

/* FUNCTION NAME: Algo_Robo_Pp_CalculateRotationTime
 * DESCRIPTION:
 * @dutycycle:
 */
extern uint32 Algo_Robo_Pp_CalculateRotationTime(uint16 dutycycle);

/** end of External Interfaces prototypes **/

#endif /* APP_ROBO_PATH_PLANNER_H */

