/****************************************************************************

COPYRIGHT (C) $Date: Nov 3, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_sch.h $

$Author: PES contribution $

 ****************************************************************************/

#ifndef IO_SCH_H
#define IO_SCH_H


#include "MKL26Z4.h"
#include "Platform_Types/std_types.h"
#include "Platform_Types/powersar_addon_types.h"
#include "Platform_Types/platform_types.h"

/** Defines **/

/** Maximum number of tasks */
#define IO_SCH_MAX_TASKS        		7

/** end of Defines **/


typedef struct Io_Sch_OsConfigTaskStruct_tag Io_Sch_OsConfigTaskStruct;

typedef struct Io_Sch_OsConfigStruct_tag Io_Sch_OsConfigStruct;

/* A task consists of the time period after which it is executed and the function which is executed */
struct Io_Sch_OsConfigTaskStruct_tag
{
	uint16 Period;           /**< Time period in multiples of 1ms */
	void (*OsTask)(void);    /**< Function which has to be executed */
};

/* The whole configuration consists of the number of different tasks to execute repeatedly and an array of these tasks */
struct Io_Sch_OsConfigStruct_tag
{
	uint8 NumberOfTasks;                                   /**< Number of tasks */
	const Io_Sch_OsConfigTaskStruct *OsConfigTask;         /**< Array of all these tasks */
};


/** Variables and Constants **/

/** end of Variables and Constants **/


/** Public operations **/

	/* Basic STU functions */

	/* Initialization of Boot OS */
extern void Io_Sch_InitOs(uint16 SchCallFrom);
extern void Io_Sch_StartOs(uint16 SchCallFrom, const Io_Sch_OsConfigStruct *OsConfig);

	/* Scheduler tasks */
extern void Io_Sch_PeriodicTask(void);
extern uint32 Io_Sch_GetTimeStamp(void);
extern uint8 Io_Sch_CheckDelayPassed(uint32 TimeStamp, uint32 Delay);

/** end of Public operations **/


#endif /* IO_SCH_H */
