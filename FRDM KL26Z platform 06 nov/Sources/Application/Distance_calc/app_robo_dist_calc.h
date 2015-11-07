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

$Log: app_robo_dist_calc.h $

$Author: Flueran Gabriel $

 ****************************************************************************/

#ifndef APP_ROBO_DIST_CALC_H
#define APP_ROBO_DIST_CALC_H


/** Includes **/

#include "MKL26Z4.h"
#include "Platform_Types/std_types.h"
#include "Platform_Types/powersar_addon_types.h"
#include "Platform_Types/platform_types.h"

#include "Application/Speed_calc/app_robo_speed_calc.h"

/** end of Includes **/

/** Defines **/

#define APP_ROBO_DC_ENC_NO_OF_EDGES				10

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

#endif /* APP_ROBO_DIST_CALC_H */

