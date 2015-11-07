/****************************************************************************

COPYRIGHT (C) $Date: 2012/05/10 14:20:43CEST $
$CompanyInfo:  $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_sch_main.c  $

 ****************************************************************************/

#include "io_sch_cnf.h"

/** Variables and Constants **/

const Io_Sch_OsConfigStruct *Io_Sch_OsConfigPtr;
uint16 Io_Sch_OsCounter[IO_SCH_MAX_TASKS];

/** end of  Variables and Constants **/

/* Private operations */

/* Public operations */

/* Calls the OS, which is in this case an endless loop.
 *  @param  stu_call_from Indicates from which subsystem the function was called
 *  @param  *OS_config Task list
 *  @return   -
 */
void Io_Sch_StartOs(uint16 SchCallFrom, const Io_Sch_OsConfigStruct *OsConfig)
{
	int Index;                                 /* Loop variable */

	Io_Sch_OsConfigPtr = OsConfig;

	/* Initialize counters */
	for (Index=0; Index < Io_Sch_OsConfigPtr->NumberOfTasks; Index++)
	{
		Io_Sch_OsCounter[Index] = Io_Sch_OsConfigPtr->OsConfigTask[Index].Period;    /* Init counter values */
	}

	/* Do "forever" */
	while (1)
	{
		/* Handle tasks */
		for (Index=0; Index < Io_Sch_OsConfigPtr->NumberOfTasks; Index++)
		{
			if (Io_Sch_OsCounter[Index] == 0)
			{
				/* Timer period is expired, execute task */

				/* Reload period */
				Io_Sch_OsCounter[Index] = Io_Sch_OsConfigPtr->OsConfigTask[Index].Period;

				/* Execute task */
				Io_Sch_OsConfigPtr->OsConfigTask[Index].OsTask();
			}
		}
	}
}

void Io_Sch_PeriodicTask(void)
{
	int Index;                                 /* Loop variable */

	/* Clear Service Request Flag */
	//  PIT_TFLG0 = 0x00000001; //Reset Timer0 interrupt flag and Return from ISR
	//  PIT_TCTRL0;

	/* Decrement counters */
	for (Index=0; Index < Io_Sch_OsConfigPtr->NumberOfTasks; Index++)
	{
		if (Io_Sch_OsCounter[Index] == 0)
		{
			/* Do not decrement a counter that is already 0, avoid counter underflow */
		}
		else
		{
			/* Decrement counter */
			Io_Sch_OsCounter[Index]--;
		}
	}

}
