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

$Log: io_os_main.c $


 ****************************************************************************/

#include "MCU_DRIVERS/INT/io_int_cnf.h"

#include "io_os_cnf.h"
#include "io_os.h"

static void Io_Os_ForceReset(void);

/* Depth of periodic queue */
volatile int Io_Os_PeriodicQueueDepth;

/* Queue of periodic tasks */
Io_Os_PeriodicTaskStruct Io_Os_PeriodicQueue[IO_OS_MAX_PERIODIC_TASK];

/* Queues configuration for all priorities */
Io_Os_PriorityQueueStruct Io_Os_PriorityQueues[IO_OS_PRIORITY_NUMBER];

/* Software-forced reset */
static void Io_Os_ForceReset(void)
{

	Io_Int_DisableInterrupts();

	/* Generate SW Reset */
	//Io_Eeh_ForceReset();
}

/* Initialization function */
void Io_Os_Init(void)
{
	int i;

	/* Reset periodic tasks queue depth */
	Io_Os_PeriodicQueueDepth = 0;

	/* Reset head and tail for all priority queues */
	for (i=0; i < IO_OS_PRIORITY_NUMBER; i++)
	{
		Io_Os_PriorityQueues[i].Head = 0;
		Io_Os_PriorityQueues[i].Tail = 0;
	}
}

/* Insert task in priorities queues
 * @param Func task function
 * @param Param function parameter
 * @param Priority task priority
 */
void Io_Os_InsertTask(Io_Os_FuncType Func, uint32 Param, uint8 Priority)
{
	uint8 Idx;

	Io_Int_DisableInterrupts();

	/* Get index of the tail */
	Idx = Io_Os_PriorityQueues[Priority].Tail;

	/* Store the task function in the queue */
	Io_Os_PriorityQueues[Priority].PriorityTask[Idx].Func = Func;
	Io_Os_PriorityQueues[Priority].PriorityTask[Idx].Param = Param;

	/* Compute the next index of the tail and store it back */
	Io_Os_PriorityQueues[Priority].Tail = (Idx + 1) % IO_OS_MAX_PRIORITY_TASK;

	/* Check if OS FIFO is full */
	if (Io_Os_PriorityQueues[Priority].Tail == Io_Os_PriorityQueues[Priority].Head)
	{
		Io_Os_ForceReset();
	}
	else
	{

	}
	Io_Int_EnableInterrupts();
}

/* Remove task from all priorities queues
 * @param Func task function
 * @param Param function parameter
 */
void Io_Os_RemoveTask(Io_Os_FuncType Func, uint32 Param)
{
	int i,j;

	/* Search the task (function and parameter) */
	for (i = 0; i < IO_OS_PRIORITY_NUMBER; i++)
	{
		for (j = Io_Os_PriorityQueues[i].Head;
				j != Io_Os_PriorityQueues[i].Tail;
				j = (j + 1) % IO_OS_MAX_PRIORITY_TASK)
		{
			if ((Func == Io_Os_PriorityQueues[i].PriorityTask[j].Func) &&
					(Param == Io_Os_PriorityQueues[i].PriorityTask[j].Param))
			{
				/* Simply store NULL_PTR in all the the queues where this task is found */
				Io_Os_PriorityQueues[i].PriorityTask[j].Func = NULL_PTR;
			}
		}
	}
}

/* Insert periodic task
 * @param Func task function
 * @param Param function parameter
 * @param Period task recurrence
 * @param Offset task start offset
 * @param Priority task priority
 */
void Io_Os_InsertPeriodicTask(Io_Os_FuncType Func, uint32 Param, uint32 Period, uint32 Offset, uint8 Priority)
{
	/* Make atomic the append of the periodic task */
	Io_Int_DisableInterrupts();

	/* Store the periodic function */
	Io_Os_PeriodicQueue[Io_Os_PeriodicQueueDepth].Func = Func;
	/* Store the parameter of the function */
	Io_Os_PeriodicQueue[Io_Os_PeriodicQueueDepth].Param = Param;
	/* Store the period in memory */
	Io_Os_PeriodicQueue[Io_Os_PeriodicQueueDepth].Period = Period;
	/* Set offset of period task (+1 because is decremented first, after checked) */
	Io_Os_PeriodicQueue[Io_Os_PeriodicQueueDepth].Time = Offset;
	/* Store the priority number */
	Io_Os_PeriodicQueue[Io_Os_PeriodicQueueDepth].Priority = Priority;
	/* Increment the queue depth */
	Io_Os_PeriodicQueueDepth++;
	/* Re-enable interrupts */
	Io_Int_EnableInterrupts();

}

/* Remove periodic task
 * @param Func task function
 * @param Param function parameter
 */
void Io_Os_RemovePeriodicTask(Io_Os_FuncType Func, uint32 Param)
{
	int i;

	/* Make atomic the removal of periodic task */
	Io_Int_DisableInterrupts();

	/* Search the function in periodic tasks */
	for (i = 0;  i < Io_Os_PeriodicQueueDepth; i++)
	{
		if ((Io_Os_PeriodicQueue[i].Func == Func) && (Io_Os_PeriodicQueue[i].Param == Param))
		{
			/* Remove it also from priority task queues */
			Io_Os_RemoveTask(Io_Os_PeriodicQueue[i].Func, Io_Os_PeriodicQueue[i].Param);

			/* Decrement queue depth */
			Io_Os_PeriodicQueueDepth--;

			/* Move last periodic task on the deleted periodic task position */
			Io_Os_PeriodicQueue[i] = Io_Os_PeriodicQueue[Io_Os_PeriodicQueueDepth];

			/* Task found and removed, exit search */
			break;
		}
		else
		{
			/* nothing */
		}
	}

	/* Re-enable interrupts */
	Io_Int_EnableInterrupts();
}


void Io_Os_PriorityHandler(void)
{

	int i;
	int Found;
	uint8 Head;
	uint8 HeadCurr;

	/* Mark the task not found */
	Found = 0;
	for (i = 0; (i < IO_OS_PRIORITY_NUMBER) && (Found == 0); i++)
	{
		/* Get the head of actual queue */
		Head = Io_Os_PriorityQueues[i].Head;

		/* Check if the queue is not empty */
		while ((Head != Io_Os_PriorityQueues[i].Tail) && (Found == 0))
		{
			/* Store the current head */
			HeadCurr = Head;

			/* Increment index of the head */
			Head = (Head + 1) % IO_OS_MAX_PRIORITY_TASK;
			Io_Os_PriorityQueues[i].Head = Head;

			/* Check if task was deleted */
			if (Io_Os_PriorityQueues[i].PriorityTask[HeadCurr].Func != NULL_PTR)
			{
				/* Execute task function */
				Io_Os_PriorityQueues[i].PriorityTask[HeadCurr].Func(Io_Os_PriorityQueues[i].PriorityTask[HeadCurr].Param);

				/* Mark task found to exit from for loop */
				Found = 1;
			}
		}
	}
}

/* Periodic handler (it shall be called at 1ms).
 * It manages the moment when periodic tasks are inserted in priority queues.
 */
void Io_Os_PeriodicHandler(void)
{
	int i;

	/* Make atomic the periodic check of the periodic tasks */
	Io_Int_DisableInterrupts();

	/* For all periodic tasks */
	for (i = 0; i < Io_Os_PeriodicQueueDepth; i++)
	{
		/* Time elapsed? */
		if (Io_Os_PeriodicQueue[i].Time == 0)
		{
			/* Update the remaining time with period */
			Io_Os_PeriodicQueue[i].Time = Io_Os_PeriodicQueue[i].Period;
			/* Insert task in priority queues */
			Io_Os_InsertTask(Io_Os_PeriodicQueue[i].Func,
					Io_Os_PeriodicQueue[i].Param,
					Io_Os_PeriodicQueue[i].Priority);
		}
		else
		{

		}

		/* Decrement time for the task with 1ms */
		Io_Os_PeriodicQueue[i].Time--;
	}

	/* Re-enable interrupts */
	Io_Int_EnableInterrupts();
}

