/*
 * sensors.h
 *
 *  Created on: Aug 26, 2015
 *      Author: Flueran Gabriel
 */

#ifndef SENSORS_H
#define SENSORS_H


#include "MKL26Z4.h"
#include "PLATFORM_TYPES/std_types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "PLATFORM_TYPES/platform_types.h"

/** Defines **/

#define SENS_IR_SHARP_0A41SK				0
#define SENS_IR_SHARP_0A41SK_25PERC_ERROR	1

#define SENS_IR_SHARP_0A41SK_MIN_DISTCM		3
#define SENS_IR_SHARP_0A41SK_MAX_DISTCM		30

#define SENS_IR_SHARP_0A41SK_MIN_DISTMM		30
#define SENS_IR_SHARP_0A41SK_MAX_DISTMM		300

#define SENS_IR_SHARP_0A41SK_MIN_VOLTAGE_MV 400
#define SENS_IR_SHARP_0A41SK_MAX_VOLTAGE_MV 3000

#define SENS_NO_OF_MEASUREMENTS	 			10

/*** TODO FLUERAN: not used in this release Sept 25, 2015
#define SENS_MIN_TOLERANCE_PERC				90
#define SENS_MAX_TOLERANCE_PERC				110
***/

/** end of Defines **/

/** External Global variables and constants **/

extern uint16 Sens_sensorSamplesVectorFront[SENS_NO_OF_MEASUREMENTS];
extern uint16 Sens_sensorSamplesVectorRight[SENS_NO_OF_MEASUREMENTS];
extern uint16 Sens_sensorSamplesVectorLeft[SENS_NO_OF_MEASUREMENTS];
extern uint16 Sens_sensorSamplesVectorRear[SENS_NO_OF_MEASUREMENTS];

extern uint16 Sens_measurementmV;

extern uint8 Sens_sensorFrontDistanceCm;
extern uint8 Sens_sensorRightDistanceCm;
extern uint8 Sens_sensorLeftDistanceCm;
extern uint8 Sens_sensorRearDistanceCm;

/*** TODO FLUERAN: Not used in this release Sept 25, 2015
extern uint16 Sens_sensorFrontDistanceMm;
extern uint16 Sens_sensorRightDistanceMm;
extern uint16 Sens_sensorLeftDistanceMm;
extern uint16 Sens_sensorRearDistanceMm;
***/

extern uint8 Sens_sensorSamplesCounter;

/** end of External Global variables and constants **/

/** External Interfaces prototypes **/

/* FUNCTION NAME: Sens_Initialization
 * DESCRIPTION: Initializes the sensors sample vectors.
 * @ void
 */
extern void Sens_Initialization(void);

/* FUNCTION NAME: Sens_GetSensorSample
 * DESCRIPTION: Get a sample from the ADC channel given and puts it in the sensor sample vector given.
 * @
 */
extern void Sens_GetSensorSample(uint8 adcChannel, uint16 *sampleVector);

/* FUNCTION NAME: Sens_CalculateSamplesMean
 * DESCRIPTION: Calculates the mean of the SENS_NO_OF_MEASUREMENTS samples for the given sample vector.
 * @
 */
extern uint16 Sens_CalculateSamplesMean(uint16 *sampleVector);

/* FUNCTION NAME: Sens_GetSensorMeasurementmV
 * DESCRIPTION: Gets a measurement [mV] from the ADC channel selected.
 * @
 */
extern uint16 Sens_GetSensorMeasurementmV(uint8 adcChannel);

/* FUNCTION NAME: Sens_CalculateDistanceCm
 * DESCRIPTION: Calculates the distance [cm] (function of voltage [mV]) seen by
 * 				the proximity sensor, based on the sensor-specific formula.
 * @
 */
extern uint8 Sens_CalculateDistanceCm(uint16 adcMeasurementmV, uint8 sensorType);

/* FUNCTION NAME: Sens_CalculateDistanceMm
 * DESCRIPTION: Calculates the distance [mm] (function of voltage [mV]) seen by
 * 				the proximity sensor, based on the sensor-specific formula.
 * @
 */
extern uint16 Sens_CalculateDistanceMm(uint16 adcMeasurementmV, uint8 sensorType);

/** end of External Interfaces prototypes **/

#endif /* SENSORS_H */
