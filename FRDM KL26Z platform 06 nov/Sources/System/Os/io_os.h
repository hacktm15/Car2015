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

$Log: io_os.h $

$Author: PES contribution $

 ****************************************************************************/

#ifndef IO_OS_H
#define IO_OS_H


#include "MKL26Z4.h"
#include "Platform_Types/std_types.h"
#include "Platform_Types/powersar_addon_types.h"
#include "Platform_Types/platform_types.h"

#include "io_os_cnf.h"

/** Defines **/

/** end of Defines **/


/** Type Definitions **/

/* Type of the function associated to tasks */
typedef void (* Io_Os_FuncType)(uint32 Param);

typedef struct Io_Os_PriorityTaskStruct_tag Io_Os_PriorityTaskStruct;

typedef struct Io_Os_PeriodicTaskStruct_tag Io_Os_PeriodicTaskStruct;

typedef struct Io_Os_PriorityQueueStruct_tag Io_Os_PriorityQueueStruct;

/** Nested Structures **/

/* The structure is used to keep the task parameters: function and function parameter */
struct Io_Os_PriorityTaskStruct_tag
{
	Io_Os_FuncType Func;                             /**< task function */
	uint32 Param;                                    /**< function parameter */
};

/* Typedef for periodic functions */
struct Io_Os_PeriodicTaskStruct_tag
{
	Io_Os_FuncType Func;     	 /* Periodic task function */
	uint32 Param;                 /* Function parameter */
	uint32 Period;          	     /* Recurrence/period of the task */
	uint32 Time;                  /* Remaining time till execution (decremented at each millisecond) */
	uint8  Priority;              /* Task priority */
};

/* Typedef for priority queue */
struct Io_Os_PriorityQueueStruct_tag
{
	Io_Os_PriorityTaskStruct PriorityTask[IO_OS_MAX_PRIORITY_TASK];   		/* Task fifo memory for one priority */
	uint8 Head;                  											/* Head of the queue index */
	uint8 Tail;                  											/* Tail of the queue index */
};

/** end of Type Definitions **/


/** Variables and Constants **/

/** end of Variables and Constants **/


/** Public operations **/

extern void Io_Os_Init(void);
extern void Io_Os_InsertTask(Io_Os_FuncType Func, uint32 Param, uint8 Priority);
extern void Io_Os_RemoveTask(Io_Os_FuncType Func, uint32 Param);
extern void Io_Os_InsertPeriodicTask(Io_Os_FuncType Func, uint32 Param, uint32 Period, uint32 Offset, uint8 Priority);
extern void Io_Os_RemovePeriodicTask(Io_Os_FuncType Func, uint32 Param);
extern void Io_Os_PriorityHandler(void);
extern void Io_Os_PeriodicHandler(void);

/** end of Public operations **/


#endif /* IO_OS_H */
