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

$Log: io_sens_ir.h $

$Author: Flueran Gabriel $

 ****************************************************************************/

#ifndef IO_SENS_IR_H
#define IO_SENS_IR_H


#include "MKL26Z4.h"
#include "Platform_Types/std_types.h"
#include "Platform_Types/powersar_addon_types.h"
#include "Platform_Types/platform_types.h"

/** Defines **/

#define SENS_IR_SHARP_0A41SK				0
#define SENS_IR_SHARP_0A41SK_25PERC_ERROR	1
#define SENS_USONIC_HRSC04                  2

#define SENS_IR_SHARP_0A41SK_MIN_DISTCM		3
#define SENS_IR_SHARP_0A41SK_MAX_DISTCM		30
#define SENS_USONIC_HRSC04_MIN_DISTCM		2
#define SENS_USONIC_HRSC04_MAX_DISTCM		400

#define SENS_IR_SHARP_0A41SK_MIN_DISTMM		30
#define SENS_IR_SHARP_0A41SK_MAX_DISTMM		300
#define SENS_USONIC_HRSC04_MIN_DISTMM		20
#define SENS_USONIC_HRSC04_MAX_DISTMM		4000

#define SENS_IR_SHARP_0A41SK_MIN_VOLTAGE_MV 400
#define SENS_IR_SHARP_0A41SK_MAX_VOLTAGE_MV 3000
#define SENS_USONIC_HRSC04_MIN_uS 			150
#define SENS_USONIC_HRSC04_MAX_uS 			25000

#define SENS_NO_OF_MEASUREMENTS	 			10
#define SENS_USONIC_NO_OF_MEASUREMENTS	 	3

/** end of Defines **/

/** External Global variables and constants **/

extern uint16 Io_Sens_sensorSamplesVectorFront[SENS_NO_OF_MEASUREMENTS];
extern uint16 Io_Sens_sensorSamplesVectorRight[SENS_NO_OF_MEASUREMENTS];
extern uint16 Io_Sens_sensorSamplesVectorLeft[SENS_NO_OF_MEASUREMENTS];
extern uint16 Io_Sens_sensorSamplesVectorRear[SENS_NO_OF_MEASUREMENTS];
extern uint16 Io_Sens_USONIC_sensorSamplesVectorFront[SENS_USONIC_NO_OF_MEASUREMENTS];
extern uint16 Io_Sens_USONIC_sensorSamplesVectorRight[SENS_USONIC_NO_OF_MEASUREMENTS];
extern uint16 Io_Sens_USONIC_sensorSamplesVectorLeft[SENS_USONIC_NO_OF_MEASUREMENTS];
extern uint16 Io_Sens_USONIC_sensorSamplesVectorRear[SENS_USONIC_NO_OF_MEASUREMENTS];

extern uint16 Io_Sens_measurementmV;
extern uint16 Io_Sens_measurementuS;

extern uint8 Io_Sens_sensorFrontDistanceCm;
extern uint8 Io_Sens_sensorRightDistanceCm;
extern uint8 Io_Sens_sensorLeftDistanceCm;
extern uint8 Io_Sens_sensorRearDistanceCm;
extern uint8 Io_Sens_USONIC_sensorFrontDistanceCm;
extern uint8 Io_Sens_USONIC_sensorRightDistanceCm;
extern uint8 Io_Sens_USONIC_sensorLeftDistanceCm;
extern uint8 Io_Sens_USONIC_sensorRearDistanceCm;

extern uint16 Io_Sens_sensorFrontDistanceMm;
extern uint16 Io_Sens_sensorRightDistanceMm;
extern uint16 Io_Sens_sensorLeftDistanceMm;
extern uint16 Io_Sens_sensorRearDistanceMm;

extern uint8 Io_Sens_sensorSamplesCounter;
extern uint8 Io_Sens_USONIC_sensorSamplesCounter;

/** end of External Global variables and constants **/

/** External Interfaces prototypes **/

/* FUNCTION NAME: Io_Sens_Initialization
 * DESCRIPTION: Initializes the sensors sample vectors.
 * @ void
 */
extern void Io_Sens_Initialization(void);

/* FUNCTION NAME: Io_Sens_Usonic_TriggerPulse
 * DESCRIPTION: Short pulse to the Trigger to start the ranging and stores the value of Echo's pulse width [uS] in the sensor sample vector given.
 * @ void
 */

extern void Io_Sens_Usonic_TriggerPulse(uint16 PortPin, uint32 channel, uint16 *sampleVector);

/* FUNCTION NAME: Io_Sens_GetSensorSample
 * DESCRIPTION: Get a sample from the ADC channel given and puts it in the sensor sample vector given.
 * @
 */
extern void Io_Sens_GetSensorSample(uint8 adcChannel, uint16 *sampleVector);

/* FUNCTION NAME: Io_Sens_CalculateSamplesMean
 * DESCRIPTION: Calculates the mean of the given number of samples ( for the given sample vector.
 * @
 */
extern uint16 Io_Sens_CalculateSamplesMean(uint16 *sampleVector, uint8 sensorNoOfMeasurements);

/* FUNCTION NAME: Io_Sens_GetSensorMeasurementmV
 * DESCRIPTION: Gets a measurement [mV] from the ADC channel selected.
 * @
 */
extern uint16 Io_Sens_GetSensorMeasurementmV(uint8 adcChannel);

/* FUNCTION NAME: Io_Sens_CalculateDistanceCm
 * DESCRIPTION: Calculates the distance [cm] (function of voltage [mV]) seen by
 * 				the proximity sensor, based on the sensor-specific formula.
 * @
 */
extern uint8 Io_Sens_CalculateDistanceCm(uint8 sensorType, uint16 Measurement);

/* FUNCTION NAME: Io_Sens_CalculateDistanceMm
 * DESCRIPTION: Calculates the distance [mm] (function of voltage [mV]) seen by
 * 				the proximity sensor, based on the sensor-specific formula.
 * @
 */
extern uint16 Io_Sens_CalculateDistanceMm(uint8 sensorType, uint16 Measurement);

/** end of External Interfaces prototypes **/

#endif /* IO_SENS_IR_H */
