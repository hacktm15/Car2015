/*
 * io_tpm_test.h
 *
 *  Created on: Aug 5, 2015
 *      Author: Flueran Gabriel
 */

#ifndef SOURCES_IO_TPM_TEST_H_
#define SOURCES_IO_TPM_TEST_H_


#include "MKL26Z4.h"
#include "PLATFORM_TYPES/std_types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "PLATFORM_TYPES/platform_types.h"

/** Defines for test **/

#define TEST_PERIOD_200MS_PRESC128 		0x927B
#define TEST_PERIOD_50MS_PRESC128		0x249E

/** end of Defines for test **/

/** External Global variables and constants **/

extern volatile uint8 Io_Tpm_TestDutycycle10ms;
extern volatile uint8 Io_Tpm_TestDutycycle1s;
extern volatile uint16 Io_Tpm_TestPeriod10ms;
extern volatile uint16 Io_Tpm_TestPeriod1s;

/** end of External Global variables and constants **/

/** External Test Functions prototypes **/

extern void Test_Io_Pwm_ChangeDutycycle10ms(void);
extern void Test_Io_Pwm_ChangeDutycycle1s(void);
extern void Test_Io_Pwm_ChangePeriod10ms(void);
extern void Test_Io_Pwm_ChangePeriod1s(void);
extern void Test_Io_Pwm_Override1s(void);
extern void Test_Io_Pwm_Task(void);

/** end of External Test Functions prototypes **/

#endif /* SOURCES_IO_TPM_TEST_H_ */
