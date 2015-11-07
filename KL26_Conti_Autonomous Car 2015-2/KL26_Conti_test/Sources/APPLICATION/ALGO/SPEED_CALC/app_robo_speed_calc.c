/*
 * app_robo_speed_calc.c
 *
 *  Created on: Sep 27, 2015
 *      Author: Gabi
 */


/** Includes **/

#include "MCU_DRIVERS/TPM/io_tpm_cnf.h"

#include "APPLICATION/ALGO/PATH_PLANNER/app_path_planner.h"

#include "app_robo_speed_calc.h"

/** end of Includes **/

/** Global variables and constants **/

Algo_Robo_Sc_EncodersDataStruct Algo_Robo_Sc_LeftEncoder;
Algo_Robo_Sc_EncodersDataStruct Algo_Robo_Sc_RightEncoder;

/** end of Global variables and constants **/

/** Functions implementation **/

/* FUNCTION NAME: Algo_Robo_Sc_InitializeSpeedCalc
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Initializes the variables used by the Speed Calculation module.
 * OBSERVATIONS: -
 */
void Algo_Robo_Sc_InitializeSpeedCalc(void)
{
	Algo_Robo_Sc_LeftEncoder.FallingEdgesCounter = 0;
	Algo_Robo_Sc_LeftEncoder.RisingEdgesCounter = 0;
	Algo_Robo_Sc_LeftEncoder.TicksCounter = 0;
	Algo_Robo_Sc_LeftEncoder.DistanceCm = 0;
	Algo_Robo_Sc_LeftEncoder.SpeedCmperS = 0;

	Algo_Robo_Sc_RightEncoder.FallingEdgesCounter = 0;
	Algo_Robo_Sc_RightEncoder.RisingEdgesCounter = 0;
	Algo_Robo_Sc_RightEncoder.TicksCounter = 0;
	Algo_Robo_Sc_RightEncoder.DistanceCm = 0;
	Algo_Robo_Sc_RightEncoder.SpeedCmperS = 0;
}

/* FUNCTION NAME: Algo_Robo_Sc_CalculateSideSpeed
 * RETURN TYPE: void
 * PARAMETERS: Algo_Robo_Sc_EncodersDataStruct *carSide, uint16 timerMultiplierMs
 * DESCRIPTION: Calculates the speed of the side of the car given as parameter.
 * 				Each side can have a different speed because of (possibly) different surface friction.
 * OBSERVATIONS: -
 */
void Algo_Robo_Sc_CalculateSideSpeed(Algo_Robo_Sc_EncodersDataStruct *carSide, uint16 timerMultiplierMs)
{
	carSide->SpeedCmperS = (uint16)((uint32)(carSide->DistanceCm * 1000) / timerMultiplierMs);
}

/* FUNCTION NAME: Algo_Robo_Sc_CalculateCarSpeed
 * RETURN TYPE: void
 * PARAMETERS: uint16 timerMultiplierMs
 * DESCRIPTION: Calculates the speed of the car.
 * OBSERVATIONS: -
 */
void Algo_Robo_Sc_CalculateCarSpeed(uint16 timerMultiplierMs)
{
	Algo_Robo_Sc_CalculateSideSpeed(&Algo_Robo_Sc_LeftEncoder,timerMultiplierMs);
	Algo_Robo_Sc_CalculateSideSpeed(&Algo_Robo_Sc_RightEncoder,timerMultiplierMs);

	Algo_Robo_Pp_CarCurrentSpeedCmPerS = Algo_Robo_Sc_LeftEncoder.SpeedCmperS;
}

/* FUNCTION NAME: Algo_Robo_Sc_CarSpeedCompensation
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Compensates the possible speed differences between the sides of the car.
 * OBSERVATIONS: -
 */
void Algo_Robo_Sc_CarSpeedCompensation(uint16 speedTolerance, uint32 pwmChannelLeft, uint32 pwmChannelRight)
{
	uint16 LeftSpeed = Algo_Robo_Sc_LeftEncoder.SpeedCmperS;
	uint16 RightSpeed = Algo_Robo_Sc_RightEncoder.SpeedCmperS;
	uint16 LeftDutycycle = 0;
	uint16 RightDutycycle = 0;
	uint8 ch1Index = 0;
	uint8 ch2Index = 0;

	ch1Index = IO_TPM_GET_INDEX(pwmChannelLeft);
	ch2Index = IO_TPM_GET_INDEX(pwmChannelRight);

	LeftDutycycle = Io_Tpm_PwmChLastDutycycle[ch1Index];
	RightDutycycle = Io_Tpm_PwmChLastDutycycle[ch2Index];

	if(LeftSpeed != RightSpeed)
	{
		if(LeftSpeed < (RightSpeed - speedTolerance))
		{
			LeftDutycycle = LeftDutycycle + ALGO_ROBO_SC_SPEED_TO_DUTYCYCLE(RightSpeed,LeftSpeed);
			Io_Tpm_PwmChangeDutycycle(pwmChannelLeft, LeftDutycycle);
		}
		else
		{
			if(LeftSpeed > (RightSpeed + speedTolerance))
			{
				RightDutycycle = RightDutycycle + ALGO_ROBO_SC_SPEED_TO_DUTYCYCLE(LeftSpeed,RightSpeed);
				Io_Tpm_PwmChangeDutycycle(pwmChannelRight, RightDutycycle);
			}
			else {}
		}
	}
	else {}
}

/** end of Functions implementation **/
