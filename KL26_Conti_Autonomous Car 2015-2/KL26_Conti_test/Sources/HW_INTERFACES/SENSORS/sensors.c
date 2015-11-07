/*
 * sensors.c
 *
 *  Created on: Aug 26, 2015
 *      Author: Flueran Gabriel
 */

#include "MCU_DRIVERS/ADC/io_adc_cnf.h"

#include "sensors.h"

/** Global variables and constants **/

uint16 Sens_sensorSamplesVectorFront[SENS_NO_OF_MEASUREMENTS];
uint16 Sens_sensorSamplesVectorRight[SENS_NO_OF_MEASUREMENTS];
uint16 Sens_sensorSamplesVectorLeft[SENS_NO_OF_MEASUREMENTS];
uint16 Sens_sensorSamplesVectorRear[SENS_NO_OF_MEASUREMENTS];

uint16 Sens_measurementmV;

uint8 Sens_sensorFrontDistanceCm;
uint8 Sens_sensorRightDistanceCm;
uint8 Sens_sensorLeftDistanceCm;
uint8 Sens_sensorRearDistanceCm;

/*** Not used in this release Sept 25, 2015
uint16 Sens_sensorFrontDistanceMm;
uint16 Sens_sensorRightDistanceMm;
uint16 Sens_sensorLeftDistanceMm;
uint16 Sens_sensorRearDistanceMm;
***/

uint8 Sens_sensorSamplesCounter;

/** end of Global variables and constants **/

/** Functions implementation **/

/* FUNCTION NAME: Sens_Initialization
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Initializes the variables used by the Sensors module.
 * OBSERVATIONS: -
 */
void Sens_Initialization(void)
{
	uint8 tempIndex;

	Sens_measurementmV = 0;

	Sens_sensorFrontDistanceCm = 0;
	Sens_sensorRightDistanceCm = 0;
	Sens_sensorLeftDistanceCm = 0;
	Sens_sensorRearDistanceCm = 0;

/*** TODO FLUERAN: Not used in this release Sept 25, 2015
Sens_sensorFrontDistanceMm = 0;
Sens_sensorRightDistanceMm = 0;
Sens_sensorLeftDistanceMm = 0;
Sens_sensorRearDistanceMm = 0;
***/

	Sens_sensorSamplesCounter = 0;

	for(tempIndex = 0; tempIndex < SENS_NO_OF_MEASUREMENTS; tempIndex++)
	{
		Sens_sensorSamplesVectorFront[tempIndex] = 0;
		Sens_sensorSamplesVectorRight[tempIndex] = 0;
		Sens_sensorSamplesVectorLeft[tempIndex] = 0;
		Sens_sensorSamplesVectorRear[tempIndex] = 0;
	}
}

/* FUNCTION NAME: Sens_GetSensorSample
 * RETURN TYPE: void
 * PARAMETERS: uint8 adcChannel, uint16 *sampleVector
 * DESCRIPTION: Get a sample from the ADC channel given and puts it in the sensor sample vector given.
 * OBSERVATIONS: -
 */
void Sens_GetSensorSample(uint8 adcChannel, uint16 *sampleVector)
{
	uint16 adcMeasurementmV;

	adcMeasurementmV = Io_Adc_GetResultmV(adcChannel);
	sampleVector[Sens_sensorSamplesCounter] = adcMeasurementmV;
}

/* FUNCTION NAME: Sens_CalculateSamplesMean
 * RETURN TYPE: uint16
 * PARAMETERS: uint16 *sampleVector
 * DESCRIPTION: Calculates the mean of the SENS_NO_OF_MEASUREMENTS samples for the given sample vector.
 * OBSERVATIONS: -
 */
uint16 Sens_CalculateSamplesMean(uint16 *sampleVector)
{
	uint8 tempIndex;
	uint16 tempSum = 0;

	for(tempIndex = 0; tempIndex < SENS_NO_OF_MEASUREMENTS; tempIndex++)
	{
		tempSum += sampleVector[tempIndex];
	}

	return (uint16)(tempSum / SENS_NO_OF_MEASUREMENTS);
}

/* FUNCTION NAME: Sens_GetSensorMeasurementmV
 * RETURN TYPE: uint16
 * PARAMETERS: uint8 channel
 * DESCRIPTION: Gets a measurement [mV] from the ADC channel selected.
 * OBSERVATIONS: -
 */
uint16 Sens_GetSensorMeasurementmV(uint8 adcChannel)
{
	uint16 adcMeasurementmV;

	adcMeasurementmV = Io_Adc_GetResultmV(adcChannel);

	return adcMeasurementmV;
}

/* FUNCTION NAME: Sens_CalculateDistanceCm
 * RETURN TYPE: uint8
 * PARAMETERS: uint16 adcMeasurementmV, uint8 sensorType
 * DESCRIPTION: Calculates the distance [cm] (function of voltage [mV]) seen by
 * 				the proximity sensor, based on the sensor-specific formula.
 * OBSERVATIONS: It may return the value with an error of approx. (+/-) 2cm
 */
uint8 Sens_CalculateDistanceCm(uint16 adcMeasurementmV, uint8 sensorType)
{
	uint8 distanceCm = 0;

	switch(sensorType)
	{
	case SENS_IR_SHARP_0A41SK:
	{
		if (adcMeasurementmV < SENS_IR_SHARP_0A41SK_MIN_VOLTAGE_MV)
		{
			distanceCm = SENS_IR_SHARP_0A41SK_MAX_DISTCM;
		}
		else
		{
			if (adcMeasurementmV > SENS_IR_SHARP_0A41SK_MAX_VOLTAGE_MV)
			{
				distanceCm = SENS_IR_SHARP_0A41SK_MIN_DISTCM;
			}
			else
			{
				distanceCm = ((uint32)(1173900 / (adcMeasurementmV - 7)) - 42) / 100;
			}
		}
		break;
	}
	case SENS_IR_SHARP_0A41SK_25PERC_ERROR:
	{
		if (adcMeasurementmV < SENS_IR_SHARP_0A41SK_MIN_VOLTAGE_MV)
		{
			distanceCm = SENS_IR_SHARP_0A41SK_MAX_DISTCM;
		}
		else
		{
			if (adcMeasurementmV > SENS_IR_SHARP_0A41SK_MAX_VOLTAGE_MV)
			{
				distanceCm = SENS_IR_SHARP_0A41SK_MIN_DISTCM;
			}
			else
			{
				distanceCm = ((uint32)(1173900 / (adcMeasurementmV - 7)) - 42) / 100;
				/* Add a 25% error to the calculated distance, because of sensor measurement errors */
				distanceCm += (uint16)(distanceCm * 25) / 100;

				if (distanceCm > SENS_IR_SHARP_0A41SK_MAX_DISTCM)
				{
					distanceCm = SENS_IR_SHARP_0A41SK_MAX_DISTCM;
				}
				else {}
			}
		}
		break;
	}
	default: { distanceCm = 0; break; }
	}

	return distanceCm;
}

/* FUNCTION NAME: Sens_CalculateDistanceMm
 * RETURN TYPE: uint8
 * PARAMETERS: uint16 adcMeasurementmV, uint8 sensorType
 * DESCRIPTION: Calculates the distance [mm] (function of voltage [mV]) seen by
 * 				the proximity sensor, based on the sensor-specific formula.
 * OBSERVATIONS: It may return the value with an error of approx. (+/-) 10mm
 */
uint16 Sens_CalculateDistanceMm(uint16 adcMeasurementmV, uint8 sensorType)
{
	uint16 distanceMm = 0;

	switch(sensorType)
	{
	case SENS_IR_SHARP_0A41SK:
	{
		if (adcMeasurementmV < SENS_IR_SHARP_0A41SK_MIN_VOLTAGE_MV)
		{
			distanceMm = SENS_IR_SHARP_0A41SK_MAX_DISTMM;
		}
		else
		{
			if (adcMeasurementmV > SENS_IR_SHARP_0A41SK_MAX_VOLTAGE_MV)
			{
				distanceMm = SENS_IR_SHARP_0A41SK_MIN_DISTMM;
			}
			else
			{
				distanceMm = ((uint32)(1173900 / (adcMeasurementmV - 7)) - 42) / 10;
			}
		}
		break;
	}
	case SENS_IR_SHARP_0A41SK_25PERC_ERROR:
	{
		if (adcMeasurementmV < SENS_IR_SHARP_0A41SK_MIN_VOLTAGE_MV)
		{
			distanceMm = SENS_IR_SHARP_0A41SK_MAX_DISTMM;
		}
		else
		{
			if (adcMeasurementmV > SENS_IR_SHARP_0A41SK_MAX_VOLTAGE_MV)
			{
				distanceMm = SENS_IR_SHARP_0A41SK_MIN_DISTMM;
			}
			else
			{
				distanceMm = ((uint32)(1173900 / (adcMeasurementmV - 7)) - 42) / 10;
				/* Add a 25% error to the calculated distance, because of sensor measurement errors */
				distanceMm += (uint16)(distanceMm * 25) / 100;

				if (distanceMm > SENS_IR_SHARP_0A41SK_MAX_DISTMM)
				{
					distanceMm = SENS_IR_SHARP_0A41SK_MAX_DISTMM;
				}
				else {}
			}
		}
		break;
	}
	default: { distanceMm = 0; break; }
	}

	return distanceMm;
}

/** end of Functions implementation **/

