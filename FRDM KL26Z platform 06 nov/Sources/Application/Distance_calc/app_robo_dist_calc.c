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

$Log: app_robo_dist_calc.c $

$Author: Flueran Gabriel $

 ****************************************************************************/

#include "MCU_drivers/Adc/io_adc_cnf.h"
#include "MCU_drivers/Dio/io_dio.h"
#include "MCU_drivers/Pcs/io_pcs_cnf.h"

#include "HW_drivers/H-bridge/ti8833/io_hbr_cnf_ti8833.h"
#include "HW_drivers/Sensors/Proximity/io_sens_ir.h"

#include "Application/Bluetooth/io_bluetooth.h"
#include "Application/Car_movement/app_robo_car_movement.h"
#include "Application/Distance_calc/app_robo_dist_calc.h"
#include "Application/Speed_calc/app_robo_speed_calc.h"
#include "Application/Path_planner/app_robo_path_planner.h"

#include "app_robo_dist_calc.h"

/** Global variables and constants **/

/** end of Global variables and constants **/

/** Functions implementation **/

/* FUNCTION NAME: Algo_Robo_Dc_CalculateSideDistanceCovered
 * RETURN TYPE: void
 * PARAMETERS: Algo_Robo_Sc_EncodersDataStruct *carSide
 * DESCRIPTION: Calculates the distance covered by a side of the car.
 * OBSERVATIONS: -
 */
void Algo_Robo_Dc_CalculateSideDistanceCovered(Algo_Robo_Sc_EncodersDataStruct *carSide)
{
	if(Algo_Robo_Pp_LastCarMovement == ALGO_ROBO_PP_CAR_STOPPED && Algo_Robo_Pp_CarMovement == ALGO_ROBO_PP_CAR_STOPPED)
	{
		carSide->DistanceCm = 0;
	}
	else
	{
		carSide->DistanceCm = (carSide->EdgesCounter * ALGO_ROBO_SC_WHEEL_LENGTH_CM)/ APP_ROBO_DC_ENC_NO_OF_EDGES;
	}

	carSide->EdgesCounter = 0;
}

/* FUNCTION NAME: Algo_Robo_Dc_CalculateCarDistanceCovered
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Calculates the distance covered by the car.
 * OBSERVATIONS: -
 */
void Algo_Robo_Dc_CalculateCarDistanceCovered(void)
{
	Algo_Robo_Dc_CalculateSideDistanceCovered(&Algo_Robo_Sc_LeftEncoder);
	Algo_Robo_Dc_CalculateSideDistanceCovered(&Algo_Robo_Sc_RightEncoder);

	Algo_Robo_Pp_CoveredDistanceCm = (Algo_Robo_Sc_LeftEncoder->DistanceCm + Algo_Robo_Sc_RightEncoder->DistanceCm) / 2;
}



/* FUNCTION NAME: Algo_Dc_GetAllSensorsSample
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Gets the samples for all sensors used.
 * OBSERVATIONS: -
 */
void Algo_Dc_GetAllSensorsSample(void)
{
	Io_Sens_GetSensorSample(ADC_CH_ADC08,Io_Sens_sensorSamplesVectorFront);
	Io_Sens_GetSensorSample(ADC_CH_ADC09,Io_Sens_sensorSamplesVectorRight);
	Io_Sens_GetSensorSample(ADC_CH_ADC12,Io_Sens_sensorSamplesVectorLeft);
	Io_Sens_GetSensorSample(ADC_CH_ADC13,Io_Sens_sensorSamplesVectorRear);
}

/* FUNCTION NAME: Algo_Dc_CalculateSensorsDistances
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Calculation of mean of all sensors samples and calculation of distances [cm].
 * OBSERVATIONS: -
 */
void Algo_Dc_CalculateSensorsDistances(void)
{
	/* Get measurement from Front sensor */
	Io_Sens_measurementmV = Io_Sens_CalculateSamplesMean(Io_Sens_sensorSamplesVectorFront,SENS_NO_OF_MEASUREMENTS);
	Io_Sens_sensorFrontDistanceCm = Io_Sens_CalculateDistanceCm(SENS_IR_SHARP_0A41SK,Io_Sens_measurementmV);

	/* Get measurement from Right sensor */
	Io_Sens_measurementmV = Io_Sens_CalculateSamplesMean(Io_Sens_sensorSamplesVectorRight,SENS_NO_OF_MEASUREMENTS);
	Io_Sens_sensorRightDistanceCm = Io_Sens_CalculateDistanceCm(SENS_IR_SHARP_0A41SK,Io_Sens_measurementmV);

	/* Get measurement from Left sensor */
	Io_Sens_measurementmV = Io_Sens_CalculateSamplesMean(Io_Sens_sensorSamplesVectorLeft,SENS_NO_OF_MEASUREMENTS);
	Io_Sens_sensorLeftDistanceCm = Io_Sens_CalculateDistanceCm(SENS_IR_SHARP_0A41SK,Io_Sens_measurementmV);

	/* Get measurement from Back sensor */
	Io_Sens_measurementmV = Io_Sens_CalculateSamplesMean(Io_Sens_sensorSamplesVectorRear,SENS_NO_OF_MEASUREMENTS);
	Io_Sens_sensorRearDistanceCm = Io_Sens_CalculateDistanceCm(SENS_IR_SHARP_0A41SK,Io_Sens_measurementmV);
}

/* FUNCTION NAME: Algo_Dc_ConsecutiveReadSensors
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Consecutive reading of sensors data and calculation of distances [cm].
 * OBSERVATIONS: -
 */
void Algo_Dc_ConsecutiveReadSensors(void)
{
	/* Get measurement from Front sensor - ADC_CH_ADC08 */
	Io_Sens_measurementmV = Io_Sens_GetSensorMeasurementmV(ADC_CH_ADC08);
	Io_Sens_sensorFrontDistanceCm = Io_Sens_CalculateDistanceCm(SENS_IR_SHARP_0A41SK,Io_Sens_measurementmV);

	/* Get measurement from Right sensor - ADC_CH_ADC09 */
	Io_Sens_measurementmV = Io_Sens_GetSensorMeasurementmV(ADC_CH_ADC09);
	Io_Sens_sensorRightDistanceCm = Io_Sens_CalculateDistanceCm(SENS_IR_SHARP_0A41SK,Io_Sens_measurementmV);

	/* Get measurement from Left sensor - ADC_CH_ADC12 */
	Io_Sens_measurementmV = Io_Sens_GetSensorMeasurementmV(ADC_CH_ADC12);
	Io_Sens_sensorLeftDistanceCm = Io_Sens_CalculateDistanceCm(SENS_IR_SHARP_0A41SK,Io_Sens_measurementmV);

	/* Get measurement from Back sensor - ADC_CH_ADC13 */
	Io_Sens_measurementmV = Io_Sens_GetSensorMeasurementmV(ADC_CH_ADC13);
	Io_Sens_sensorRearDistanceCm = Io_Sens_CalculateDistanceCm(SENS_IR_SHARP_0A41SK,Io_Sens_measurementmV);
}

/** end of Functions implementation **/




