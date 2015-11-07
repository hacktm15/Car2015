/*
 * app_dist_calc.c
 *
 *  Created on: Aug 31, 2015
 *      Author: uidn9990
 */

#include "MCU_DRIVERS/ADC/io_adc_cnf.h"
#include "MCU_DRIVERS/DIO/io_dio.h"
#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"

#include "HW_INTERFACES/SENSORS/sensors.h"

#include "APPLICATION/ALGO/CAR_MOVEMENT/app_robo_car_movement.h"
#include "APPLICATION/ALGO/PATH_PLANNER/app_path_planner.h"
#include "APPLICATION/ALGO/SPEED_CALC/app_robo_speed_calc.h"

#include "app_dist_calc.h"

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
		carSide->TicksCounter = 0;
		carSide->DistanceCm = 0;
	}
	else
	{
		carSide->TicksCounter = (ALGO_ROBO_DC_RISING_EDGE_CONTRIBUTION * carSide->RisingEdgesCounter) + (ALGO_ROBO_DC_FALLING_EDGE_CONTRIBUTION * carSide->FallingEdgesCounter);
		carSide->DistanceCm = (carSide->TicksCounter * ALGO_ROBO_SC_WHEEL_LENGTH_MM)/ APP_ROBO_DC_ENC_NO_OF_EDGES;
	}

	carSide->RisingEdgesCounter = 0;
	carSide->FallingEdgesCounter = 0;
}

/* FUNCTION NAME: Algo_Robo_Dc_CalculateCarDistanceCovered
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Calculates the distance covered by the car.
 * OBSERVATIONS: -
 */
void Algo_Robo_Dc_CalculateCarDistanceCovered(void)
{
	Algo_Robo_Dc_CalculateSideDistanceCovered(&Algo_Robo_Sc_RightEncoder);
	Algo_Robo_Dc_CalculateSideDistanceCovered(&Algo_Robo_Sc_LeftEncoder);
}

/* FUNCTION NAME: Algo_Dc_GetAllSensorsSample
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Gets the samples for all sensors used.
 * OBSERVATIONS: -
 */
void Algo_Dc_GetAllSensorsSample(void)
{
	Sens_GetSensorSample(ADC_CH_ADC08,Sens_sensorSamplesVectorFront);
	Sens_GetSensorSample(ADC_CH_ADC09,Sens_sensorSamplesVectorRight);
	Sens_GetSensorSample(ADC_CH_ADC12,Sens_sensorSamplesVectorLeft);
	Sens_GetSensorSample(ADC_CH_ADC13,Sens_sensorSamplesVectorRear);
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
	Sens_measurementmV = Sens_CalculateSamplesMean(Sens_sensorSamplesVectorFront);
	Sens_sensorFrontDistanceCm = Sens_CalculateDistanceCm(Sens_measurementmV,SENS_IR_SHARP_0A41SK);

	/* Get measurement from Right sensor */
	Sens_measurementmV = Sens_CalculateSamplesMean(Sens_sensorSamplesVectorRight);
	Sens_sensorRightDistanceCm = Sens_CalculateDistanceCm(Sens_measurementmV,SENS_IR_SHARP_0A41SK);

	/* Get measurement from Left sensor */
	Sens_measurementmV = Sens_CalculateSamplesMean(Sens_sensorSamplesVectorLeft);
	Sens_sensorLeftDistanceCm = Sens_CalculateDistanceCm(Sens_measurementmV,SENS_IR_SHARP_0A41SK);

	/* Get measurement from Back sensor */
	Sens_measurementmV = Sens_CalculateSamplesMean(Sens_sensorSamplesVectorRear);
	Sens_sensorRearDistanceCm = Sens_CalculateDistanceCm(Sens_measurementmV,SENS_IR_SHARP_0A41SK);
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
	Sens_measurementmV = Sens_GetSensorMeasurementmV(ADC_CH_ADC08);
	Sens_sensorFrontDistanceCm = Sens_CalculateDistanceCm(Sens_measurementmV,SENS_IR_SHARP_0A41SK);

	/* Get measurement from Right sensor - ADC_CH_ADC09 */
	Sens_measurementmV = Sens_GetSensorMeasurementmV(ADC_CH_ADC09);
	Sens_sensorRightDistanceCm = Sens_CalculateDistanceCm(Sens_measurementmV,SENS_IR_SHARP_0A41SK);

	/* Get measurement from Left sensor - ADC_CH_ADC12 */
	Sens_measurementmV = Sens_GetSensorMeasurementmV(ADC_CH_ADC12);
	Sens_sensorLeftDistanceCm = Sens_CalculateDistanceCm(Sens_measurementmV,SENS_IR_SHARP_0A41SK);

	/* Get measurement from Back sensor - ADC_CH_ADC13 */
	Sens_measurementmV = Sens_GetSensorMeasurementmV(ADC_CH_ADC13);
	Sens_sensorRearDistanceCm = Sens_CalculateDistanceCm(Sens_measurementmV,SENS_IR_SHARP_0A41SK);
}

/** end of Functions implementation **/
