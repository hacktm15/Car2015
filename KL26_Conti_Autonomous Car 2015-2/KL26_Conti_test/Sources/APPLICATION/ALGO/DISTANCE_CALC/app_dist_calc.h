/*
 * app_dist_calc.h
 *
 *  Created on: Aug 31, 2015
 *      Author: uidn9990
 */

#ifndef APP_DIST_CALC_H
#define APP_DIST_CALC_H


/** Includes **/

#include "MKL26Z4.h"
#include "PLATFORM_TYPES/std_types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "PLATFORM_TYPES/platform_types.h"

#include "APPLICATION/ALGO/SPEED_CALC/app_robo_speed_calc.h"

/** end of Includes **/

/** Defines **/

#define ALGO_ROBO_DC_RISING_EDGE_CONTRIBUTION 	1
#define ALGO_ROBO_DC_FALLING_EDGE_CONTRIBUTION 	2

#define APP_ROBO_DC_ENC_NO_OF_EDGES				30

/** end of Defines **/

/** External Global variables and constants **/

/** end of External Global variables and constants **/

/** External Interfaces prototypes **/

/* FUNCTION NAME: Algo_Robo_Dc_CalculateSideDistanceCovered
 * DESCRIPTION: Calculates the distance covered by a side of the car.
 * @*carSide:
 */
extern void Algo_Robo_Dc_CalculateSideDistanceCovered(Algo_Robo_Sc_EncodersDataStruct *carSide);

/* FUNCTION NAME: Algo_Robo_Dc_CalculateCarDistanceCovered
 * DESCRIPTION: Calculates the distance covered by the car.
 * @ void
 */
extern void Algo_Robo_Dc_CalculateCarDistanceCovered(void);

/* FUNCTION NAME: Algo_Dc_GetAllSensorsSample
 * DESCRIPTION: Gets the samples for all sensors used.
 * @ void
 */
extern void Algo_Dc_GetAllSensorsSample(void);

/* FUNCTION NAME: Algo_Dc_CalculateSensorsDistances
 * DESCRIPTION: Calculation of mean of all sensors samples and calculation of distances [cm].
 * @ void
 */
extern void Algo_Dc_CalculateSensorsDistances(void);

/* FUNCTION NAME: Algo_Dc_ConsecutiveReadSensors
 * DESCRIPTION: Consecutive reading of sensors data.
 * @ void
 */
extern void Algo_Dc_ConsecutiveReadSensors(void);

/** end of External Interfaces prototypes **/

#endif /* SOURCES_APPLICATION_ALGO_DISTANCE_CALC_APP_DIST_CALC_H_ */
