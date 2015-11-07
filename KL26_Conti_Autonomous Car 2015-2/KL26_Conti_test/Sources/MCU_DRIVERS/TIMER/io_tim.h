
#ifndef IO_TIM_H
#define IO_TIM_H

/****************************************************************************

COPYRIGHT (C) $Date: 2012/05/09 17:46:33CEST $
$CompanyInfo:  $
ALL RIGHTS RESERVED.                                                 

The reproduction, transmission or use of this document or its contents is  
not permitted without express written authority.                           
Offenders will be liable for damages. All rights, including rights created 
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_tim.h  $

 ****************************************************************************/

#include "MKL26Z4.h"
#include "PLATFORM_TYPES/std_types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "PLATFORM_TYPES/platform_types.h"

#include "SYSTEM/io_sys.h"

/** Defines **/

#define IO_TIM_TCKPS 2
#define IO_TIM_PRESCALE 8
#define IO_TIM_TICK ((float32)IO_TIM_PRESCALE / IO_SYS_FREQ)

#define Io_Tim_GetTicksUs(Time) ((uint16)((float32)Time / IO_TIM_TICK / 1000000))
#define Io_Tim_GetTicksMs(Time) ((uint16)((float32)Time / IO_TIM_TICK / 1000))

#define IO_SYS_PLL_FREQ         IO_SYS_FREQ_TMR2

/** end of Defines **/

static inline uint16 Io_Tim_ReadTimer0(void)

{
	return (PIT_CVAL0);  /* Return the Timer1 register */
}

static inline void Io_Tim_WriteTimer0(uint16 Timer)
{
	PIT_LDVAL0 = Timer;   /* assign timer value to Timer1 Register */
}

static inline uint16 Io_Tim_ReadTimer1(void)
{
	return (PIT_CVAL1);  /* Return the Timer1 register */
}

static inline void Io_Tim_WriteTimer1(uint16 Timer)
{
	PIT_LDVAL1 = Timer;   /* assign timer value to Timer1 Register */
}

static inline uint16 Io_Tim_GetTimeStamp(void)
{
	return (Io_Tim_ReadTimer1());
}

static inline uint8 Io_Tim_CheckDelayPassed(uint16 TimeStamp, uint16 Delay)
{
	uint8 Status;
	Status = 0;

	if ((Io_Tim_GetTimeStamp() - TimeStamp) >= Delay)
	{
		Status = 1;
	}

	return (Status);
}

extern void Io_Tim_ConfigIntTimer0(uint16 Config);
extern void Io_Tim_OpenTimer0(uint32 Config, uint16 Period);
extern void Io_Tim_CloseTimer0(void);

extern void Io_Tim_ConfigIntTimer1(uint16 Config);
extern void Io_Tim_OpenTimer1(uint32 Config, uint16 Period);
void Io_Tim_CloseTimer1(void);

extern uint16 Io_Tim_ReadTimer16(void);
extern void Io_Tim_DelayUs (uint16 Us);
extern void Io_Tim_DelayMs (uint16 Ms);

extern void Io_Tim_Initialization(void);
extern void SysTick_Init();

/** end of Public operations **/

#endif
