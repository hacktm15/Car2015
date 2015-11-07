/*
 * app_robo_speed_calc.h
 *
 *  Created on: Sep 27, 2015
 *      Author: Gabi
 */

#ifndef APP_ROBO_SPEED_CALC_H
#define APP_ROBO_SPEED_CALC_H


#include "MKL26Z4.h"
#include "PLATFORM_TYPES/std_types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "PLATFORM_TYPES/platform_types.h"

/** Defines **/

	/* Macros */

#define ALGO_ROBO_SC_CALCULATE_CAR_SPEED(dutycycle)			(uint16)((uint32)(dutycycle * ALGO_ROBO_SC_RPS_5V * ALGO_ROBO_SC_WHEEL_LENGTH_MM * ALGO_ROBO_SC_WEIGHT_FACTOR1) / (ALGO_ROBO_SC_WEIGHT_FACTOR2 * 100))
#define ALGO_ROBO_SC_CALCULATE_CAR_SPEED_CM(dutycycle)		(uint8)(((uint32)(dutycycle * 2527) / 1000) - 5)
#define ALGO_ROBO_SC_SPEED_TO_DUTYCYCLE(maxSpeed,minSpeed)	(uint16)(maxSpeed - minSpeed)

	/* end of Macros */

/* Defines for rough car speed calculation */
#define ALGO_ROBO_SC_MAX_RPS_5V					3
#define ALGO_ROBO_SC_WEIGHT_FACTOR				3

#define ALGO_ROBO_SC_RPS_5V						(uint8)(ALGO_ROBO_SC_MAX_RPS_5V / ALGO_ROBO_SC_WEIGHT_FACTOR)

#define ALGO_ROBO_SC_WEIGHT_FACTOR1				1
#define ALGO_ROBO_SC_WEIGHT_FACTOR2				1
/* end of Defines for rough car speed calculation */

#define ALGO_ROBO_SC_WHEEL_LENGTH_CM			40
#define ALGO_ROBO_SC_WHEEL_LENGTH_MM			400

#define ALGO_ROBO_SC_TASK_DIVIDER 				10

#define ALGO_ROBO_SC_SPEED_TOLERANCE 			1

/** end of Defines **/

/** Structure Typedefs and Nested Structures **/

typedef struct Algo_Robo_Sc_EncodersDataStruct_tag Algo_Robo_Sc_EncodersDataStruct;

struct Algo_Robo_Sc_EncodersDataStruct_tag
{
	uint32 RisingEdgesCounter;
	uint32 FallingEdgesCounter;
	uint32 TicksCounter;
	uint32 DistanceCm;
	uint16 SpeedCmperS;
};

/** end of Structure Typedefs and Nested Structures **/

/** External Global variables and constants **/

extern Algo_Robo_Sc_EncodersDataStruct Algo_Robo_Sc_LeftEncoder;
extern Algo_Robo_Sc_EncodersDataStruct Algo_Robo_Sc_RightEncoder;

/** end of External Global variables and constants **/

/** External Interfaces prototypes **/

/* FUNCTION NAME: Algo_Robo_Sc_InitializeSpeedCalc
 * DESCRIPTION: Initializes the variables used by the Speed Calculation module.
 * @ void
 */
extern void Algo_Robo_Sc_InitializeSpeedCalc(void);

/* FUNCTION NAME: Algo_Robo_Sc_CalculateSideSpeed
 * DESCRIPTION: Calculates the speed of the side of the car given as parameter.
 * 				Each side can have a different speed because of (possibly) different surface friction.
 * @*carSide:
 * @timerMultiplierMs:
 */
extern void Algo_Robo_Sc_CalculateSideSpeed(Algo_Robo_Sc_EncodersDataStruct *carSide, uint16 timerMultiplierMs);

/* FUNCTION NAME: Algo_Robo_Sc_CalculateCarSpeed
 * DESCRIPTION: Calculates the speed of the car.
 * @timerMultiplierMs:
 */
extern void Algo_Robo_Sc_CalculateCarSpeed(uint16 timerMultiplierMs);

/* FUNCTION NAME: Algo_Robo_Sc_CarSpeedCompensation
 * DESCRIPTION: Compensates the possible speed differences between the sides of the car.
 * @ void
 */
extern void Algo_Robo_Sc_CarSpeedCompensation(uint16 speedTolerance, uint32 pwmChannelLeft, uint32 pwmChannelRight);

/** end of External Interfaces prototypes **/

#endif /* APP_ROBO_SPEED_CALC_H */
