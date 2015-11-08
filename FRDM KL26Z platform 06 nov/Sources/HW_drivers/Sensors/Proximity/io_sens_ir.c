/**************************************************************************

COPYRIGHT (C) $Date: Aug 26, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_sens_ir.c $

$Author: Flueran Gabriel $

 ****************************************************************************/

#include "MCU_drivers/Adc/io_adc_cnf.h"
#include "MCU_drivers/Pcs/io_pcs_cnf.h"
#include "MCU_drivers/Tpm/io_tpm_cnf.h"
#include "MCU_drivers/Dio/io_dio.h"

#include "io_sens_ir.h"

/** Global variables and constants **/

uint16 Io_Sens_sensorSamplesVectorFront[SENS_NO_OF_MEASUREMENTS];
uint16 Io_Sens_sensorSamplesVectorRight[SENS_NO_OF_MEASUREMENTS];
uint16 Io_Sens_sensorSamplesVectorLeft[SENS_NO_OF_MEASUREMENTS];
uint16 Io_Sens_sensorSamplesVectorRear[SENS_NO_OF_MEASUREMENTS];
uint16 Io_Sens_USONIC_sensorSamplesVectorFront[SENS_USONIC_NO_OF_MEASUREMENTS];
uint16 Io_Sens_USONIC_sensorSamplesVectorRight[SENS_USONIC_NO_OF_MEASUREMENTS];
uint16 Io_Sens_USONIC_sensorSamplesVectorLeft[SENS_USONIC_NO_OF_MEASUREMENTS];
uint16 Io_Sens_USONIC_sensorSamplesVectorRear[SENS_USONIC_NO_OF_MEASUREMENTS];

uint16 Io_Sens_measurementmV;
uint16 Io_Sens_measurementuS;

uint8 Io_Sens_sensorFrontDistanceCm;
uint8 Io_Sens_sensorRightDistanceCm;
uint8 Io_Sens_sensorLeftDistanceCm;
uint8 Io_Sens_sensorRearDistanceCm;
uint8 Io_Sens_USONIC_sensorFrontDistanceCm;
uint8 Io_Sens_USONIC_sensorRightDistanceCm;
uint8 Io_Sens_USONIC_sensorLeftDistanceCm;
uint8 Io_Sens_USONIC_sensorRearDistanceCm;

uint16 Io_Sens_sensorFrontDistanceMm;
uint16 Io_Sens_sensorRightDistanceMm;
uint16 Io_Sens_sensorLeftDistanceMm;
uint16 Io_Sens_sensorRearDistanceMm;

uint8 delay[4];

uint8 Io_Sens_sensorSamplesCounter;
uint8 Io_Sens_USONIC_sensorSamplesCounter;

/** end of Global variables and constants **/

/** Functions implementation **/

/* FUNCTION NAME: Io_Sens_Initialization
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Initializes the variables used by the Sensors module.
 * OBSERVATIONS: -
 */
void Io_Sens_Initialization(void)
{
	uint8 tempIndex;
	uint8 i;

	for (i=0; i<4; i++)
	{
		delay[i]=0;
	}

	Io_Sens_measurementmV = 0;
	Io_Sens_measurementuS = 0;

	Io_Sens_sensorFrontDistanceCm = 0;
	Io_Sens_sensorRightDistanceCm = 0;
	Io_Sens_sensorLeftDistanceCm = 0;
	Io_Sens_sensorRearDistanceCm = 0;

	Io_Sens_sensorFrontDistanceMm = 0;
	Io_Sens_sensorRightDistanceMm = 0;
	Io_Sens_sensorLeftDistanceMm = 0;
	Io_Sens_sensorRearDistanceMm = 0;

	Io_Sens_sensorSamplesCounter = 0;
	Io_Sens_USONIC_sensorSamplesCounter = 0;

	for(tempIndex = 0; tempIndex < SENS_NO_OF_MEASUREMENTS; tempIndex++)
	{
		Io_Sens_sensorSamplesVectorFront[tempIndex] = 0;
		Io_Sens_sensorSamplesVectorRight[tempIndex] = 0;
		Io_Sens_sensorSamplesVectorLeft[tempIndex] = 0;
		Io_Sens_sensorSamplesVectorRear[tempIndex] = 0;
	}
	for(tempIndex = 0; tempIndex < SENS_USONIC_NO_OF_MEASUREMENTS; tempIndex++)
		{
			Io_Sens_USONIC_sensorSamplesVectorFront[tempIndex] = 0;
			Io_Sens_USONIC_sensorSamplesVectorRight[tempIndex] = 0;
			Io_Sens_USONIC_sensorSamplesVectorLeft[tempIndex] = 0;
			Io_Sens_USONIC_sensorSamplesVectorRear[tempIndex] = 0;
		}
}

/* FUNCTION NAME: Io_Sens_Usonic_TriggerPulse
 * RETURN TYPE: void
 * PARAMETERS: uint16 PortPin, uint32 channel, uint16 *sampleVector
 * DESCRIPTION: Short pulse to the Trigger to start the ranging
 * 				and stores the value of Echo's pulse width [uS] in the sensor sample vector given.
 * OBSERVATIONS: Must run in the 10ms task
 * */

void Io_Sens_Usonic_TriggerPulse(uint16 PortPin, uint32 channel, uint16 *sampleVector)
{
	uint32 Measurement = 0;
	uint8 i = 0;

	i = ((channel & 0x00000F00) >> 8) - 1;

	if (delay[i] == 0)
	{
		Io_Dio_SetPinLevel(PortPin, IO_PCS_LEVEL_LOW);
		aux = Io_Dio_GetPinLevel(PortPin);
	} else if (delay[i] == 1)
	{
		Io_Dio_SetPinLevel(PortPin, IO_PCS_LEVEL_HIGH);
		aux = Io_Dio_GetPinLevel(PortPin);
	} else if (delay[i] == 2)
	{
		Io_Dio_SetPinLevel(PortPin, IO_PCS_LEVEL_LOW);
		aux = Io_Dio_GetPinLevel(PortPin);
	} else if (delay[i] == 3)
	{
		Measurement = Io_Tpm_GetPulseWidth(channel);
		Measurement /= 1000;
		sampleVector[Io_Sens_USONIC_sensorSamplesCounter] = Measurement; //uS
		Io_Sens_USONIC_sensorSamplesCounter++;
		if (Io_Sens_USONIC_sensorSamplesCounter == SENS_USONIC_NO_OF_MEASUREMENTS)
		{
			Io_Sens_USONIC_sensorSamplesCounter = 0;
		}
	} else if (delay[i] == 10)
	{
		delay[i] = 0;
	}
	delay[i] ++;
}

/* FUNCTION NAME: Io_Sens_GetSensorMeasurementmV
 * RETURN TYPE: uint16
 * PARAMETERS: uint8 channel
 * DESCRIPTION: Gets a measurement [mV] from the ADC channel selected.
 * OBSERVATIONS: -
 */
uint16 Io_Sens_GetSensorMeasurementmV(uint8 adcChannel)
{
	uint16 adcMeasurementmV;

	adcMeasurementmV = Io_Adc_GetResultmV(adcChannel);

	return adcMeasurementmV;
}

/* FUNCTION NAME: Io_Sens_GetSensorSample
 * RETURN TYPE: void
 * PARAMETERS: uint8 adcChannel, uint16 *sampleVector
 * DESCRIPTION: Get a sample from the ADC channel given and puts it in the sensor sample vector given.
 * OBSERVATIONS: -
 */
void Io_Sens_GetSensorSample(uint8 adcChannel, uint16 *sampleVector)
{
	uint16 adcMeasurementmV;

	adcMeasurementmV = Io_Adc_GetResultmV(adcChannel);
	sampleVector[Io_Sens_sensorSamplesCounter] = adcMeasurementmV;
}

/* FUNCTION NAME: Io_Sens_CalculateSamplesMean
 * RETURN TYPE: uint16
 * PARAMETERS: uint16 *sampleVector, uint8 sensorNoOfMeasurements
 * DESCRIPTION: Calculates the mean of the SENS_NO_OF_MEASUREMENTS samples for the given sample vector.
 * OBSERVATIONS: -
 */
uint16 Io_Sens_CalculateSamplesMean(uint16 *sampleVector, uint8 sensorNoOfMeasurements)
{
	uint8 tempIndex;
	uint16 tempSum = 0;

	for(tempIndex = 0; tempIndex < sensorNoOfMeasurements; tempIndex++)
	{
		tempSum += sampleVector[tempIndex];
	}

	return (uint16)(tempSum / sensorNoOfMeasurements);
}

/* FUNCTION NAME: Io_Sens_CalculateDistanceCm
 * RETURN TYPE: uint8
 * PARAMETERS: uint8 sensorType, uint16 Measurement
 * DESCRIPTION: Calculates the distance [cm] (function of voltage [mV]) seen by
 * 				the proximity sensor, based on the sensor-specific formula.
 * OBSERVATIONS: It may return the value with an error of approx. (+/-) 2cm
 */
uint8 Io_Sens_CalculateDistanceCm(uint8 sensorType, uint16 Measurement)
{
	uint16 distanceCm = 0;

	switch(sensorType)
	{
	case SENS_IR_SHARP_0A41SK:
	{
		if (Measurement < SENS_IR_SHARP_0A41SK_MIN_VOLTAGE_MV)
		{
			distanceCm = SENS_IR_SHARP_0A41SK_MAX_DISTCM;
		}
		else
		{
			if (Measurement > SENS_IR_SHARP_0A41SK_MAX_VOLTAGE_MV)
			{
				distanceCm = SENS_IR_SHARP_0A41SK_MIN_DISTCM;
			}
			else
			{
				distanceCm = ((uint32)(1173900 / (Measurement - 7)) - 42) / 100;
			}
		}
		break;
	}
	case SENS_IR_SHARP_0A41SK_25PERC_ERROR:
	{
		if (Measurement < SENS_IR_SHARP_0A41SK_MIN_VOLTAGE_MV)
		{
			distanceCm = SENS_IR_SHARP_0A41SK_MAX_DISTCM;
		}
		else
		{
			if (Measurement > SENS_IR_SHARP_0A41SK_MAX_VOLTAGE_MV)
			{
				distanceCm = SENS_IR_SHARP_0A41SK_MIN_DISTCM;
			}
			else
			{
				distanceCm = ((uint32)(1173900 / (Measurement - 7)) - 42) / 100;
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
	case SENS_USONIC_HRSC04:
	{
		if (Measurement < SENS_USONIC_HRSC04_MIN_uS)
		{
			distanceCm = SENS_USONIC_HRSC04_MIN_DISTCM;
		}
		else
		{
			if (Measurement > SENS_USONIC_HRSC04_MAX_uS)
			{
				distanceCm = SENS_USONIC_HRSC04_MAX_DISTCM;
			}
			else
			{
				distanceCm = Measurement / 58;
			}
		}
		break;
	}
	default: { distanceCm = 0; break; }
	}

	return distanceCm;
}

/* FUNCTION NAME: Io_Sens_CalculateDistanceMm
 * RETURN TYPE: uint8
 * PARAMETERS: uint16 adcMeasurementmV, uint8 sensorType
 * DESCRIPTION: Calculates the distance [mm] (function of voltage [mV]) seen by
 * 				the proximity sensor, based on the sensor-specific formula.
 * OBSERVATIONS: It may return the value with an error of approx. (+/-) 10mm
 */
uint16 Io_Sens_CalculateDistanceMm(uint8 sensorType, uint16 Measurement)
{
	uint16 distanceMm = 0;

	switch(sensorType)
	{
	case SENS_IR_SHARP_0A41SK:
	{
		if (Measurement < SENS_IR_SHARP_0A41SK_MIN_VOLTAGE_MV)
		{
			distanceMm = SENS_IR_SHARP_0A41SK_MAX_DISTMM;
		}
		else
		{
			if (Measurement > SENS_IR_SHARP_0A41SK_MAX_VOLTAGE_MV)
			{
				distanceMm = SENS_IR_SHARP_0A41SK_MIN_DISTMM;
			}
			else
			{
				distanceMm = ((uint32)(1173900 / (Measurement - 7)) - 42) / 10;
			}
		}
		break;
	}
	case SENS_IR_SHARP_0A41SK_25PERC_ERROR:
	{
		if (Measurement < SENS_IR_SHARP_0A41SK_MIN_VOLTAGE_MV)
		{
			distanceMm = SENS_IR_SHARP_0A41SK_MAX_DISTMM;
		}
		else
		{
			if (Measurement > SENS_IR_SHARP_0A41SK_MAX_VOLTAGE_MV)
			{
				distanceMm = SENS_IR_SHARP_0A41SK_MIN_DISTMM;
			}
			else
			{
				distanceMm = ((uint32)(1173900 / (Measurement - 7)) - 42) / 10;
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
	case SENS_USONIC_HRSC04:
		{
			if (Measurement < SENS_USONIC_HRSC04_MIN_uS)
			{
				distanceMm = SENS_USONIC_HRSC04_MIN_DISTMM;
			}
			else
			{
				if (Measurement > SENS_USONIC_HRSC04_MAX_uS)
				{
					distanceMm = SENS_USONIC_HRSC04_MAX_DISTMM;
				}
				else
				{
					distanceMm = (Measurement * 10) / 58;
				}
			}
			break;
		}
	default: { distanceMm = 0; break; }
	}

	return distanceMm;
}

/** end of Functions implementation **/

