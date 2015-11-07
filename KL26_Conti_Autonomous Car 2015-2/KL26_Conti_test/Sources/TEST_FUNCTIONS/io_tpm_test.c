/*
 * io_tpm_test.c
 *
 *  Created on: Aug 5, 2015
 *      Author: Flueran Gabriel
 */

#include "MCU_DRIVERS/ADC/io_adc_cnf.h"
#include "MCU_DRIVERS/DIO/io_dio.h"
#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"
#include "MCU_DRIVERS/TIMER/io_tim.h"
#include "MCU_DRIVERS/TPM/io_tpm_cnf.h"

#include "io_tpm_test.h"

/** Global variables and constants **/

volatile uint8 Io_Tpm_TestDutycycle10ms = 0;
volatile uint8 Io_Tpm_TestDutycycle1s = 0;
volatile uint16 Io_Tpm_TestPeriod10ms = 0;
volatile uint16 Io_Tpm_TestPeriod1s = 0;
volatile uint8 Io_Tpm_OverrideDone = FALSE;
volatile uint8 Io_Tpm_testValue1 = 0;

/** end of Global variables and constants **/

/** Test Functions implementation **/

/* FUNCTION NAME: Test_Io_Pwm_ChangeDutycycle10ms
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: TEST function to verify "Io_Tpm_PwmChangeDutycycle" functionality
 * OBSERVATIONS: -
 */
void Test_Io_Pwm_ChangeDutycycle10ms(void)
{
	if(Io_Tpm_Initialized)
	{
		Io_Tpm_TestDutycycle10ms += 10;

		if(Io_Tpm_TestDutycycle10ms > IO_TPM_100PERCENT)
		{
			Io_Tpm_TestDutycycle10ms = 0;
		}
		else {}

		Io_Tpm_PwmChangeDutycycle(CNF_TPM1_CHANNEL0,IO_TPM_PERCENT_TO_4000HEX(Io_Tpm_TestDutycycle10ms));
		Io_Tpm_PwmChangeDutycycle(CNF_TPM0_CHANNEL1,IO_TPM_PERCENT_TO_4000HEX(Io_Tpm_TestDutycycle10ms));
		Io_Tpm_PwmChangeDutycycle(CNF_TPM2_CHANNEL0,IO_TPM_PERCENT_TO_4000HEX(Io_Tpm_TestDutycycle10ms));

	}
	else {}
}

/* FUNCTION NAME: Test_Io_Pwm_ChangeDutycycle1s
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: TEST function to verify "Io_Tpm_PwmChangeDutycycle" functionality
 * OBSERVATIONS: -
 */
void Test_Io_Pwm_ChangeDutycycle1s(void)
{
	if(Io_Tpm_Initialized)
	{
		Io_Tpm_TestDutycycle1s += 10;

		if(Io_Tpm_TestDutycycle1s > IO_TPM_100PERCENT)
		{
			Io_Tpm_TestDutycycle1s = 0;
		}
		else {}

		Io_Tpm_PwmChangeDutycycle(CNF_TPM2_CHANNEL0,IO_TPM_PERCENT_TO_4000HEX(Io_Tpm_TestDutycycle1s));

	}
	else {}
}

/* FUNCTION NAME: Test_Io_Pwm_ChangePeriod10ms
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: TEST function to verify "Io_Tpm_PwmChangePeriod" functionality
 * OBSERVATIONS: -
 */
void Test_Io_Pwm_ChangePeriod10ms(void)
{
	if(Io_Tpm_Initialized && Io_Tpm_OverrideDone == FALSE)
	{
		Io_Tpm_TestPeriod10ms += 0x1000;

		if(Io_Tpm_TestPeriod10ms > IO_TPM_MAX_16BIT)
		{
			Io_Tpm_TestPeriod10ms = 0;
		}
		else {}

		Io_Tpm_PwmChangePeriod(CNF_TPM1_CHANNEL0,Io_Tpm_TestPeriod10ms);
		//TODO FLUERAN: Io_Tpm_PwmChangePeriod(CNF_TPM2_CHANNEL0,Io_Tpm_TestPeriod10ms);
	}
	else {}
}

/* FUNCTION NAME: Test_Io_Pwm_ChangePeriod1s
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: TEST function to verify "Io_Tpm_PwmChangePeriod" functionality
 * OBSERVATIONS: -
 */
void Test_Io_Pwm_ChangePeriod1s(void)
{
	if(Io_Tpm_Initialized)
	{
		switch(Io_Tpm_testValue1)
		{
		case 0: {Io_Tpm_testValue1 = 1; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,100); break;}
		case 1: {Io_Tpm_testValue1 = 2; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,500); break;}
		case 2: {Io_Tpm_testValue1 = 3; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,700); break;}
		case 3: {Io_Tpm_testValue1 = 4; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,1400); break;}
		case 4: {Io_Tpm_testValue1 = 5; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,5000); break;}
		case 5: {Io_Tpm_testValue1 = 6; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,6300); break;}
		case 6: {Io_Tpm_testValue1 = 7; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,10000); break;}
		case 7: {Io_Tpm_testValue1 = 8; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,34500); break;}
		case 8: {Io_Tpm_testValue1 = 9; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,50000); break;}
		case 9: {Io_Tpm_testValue1 = 10; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,100000); break;}
		case 10: {Io_Tpm_testValue1 = 11; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,125200); break;}
		case 11: {Io_Tpm_testValue1 = 12; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,210500); break;}
		case 12: {Io_Tpm_testValue1 = 13; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,322000); break;}
		case 13: {Io_Tpm_testValue1 = 14; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,349000); break;}
		case 14: {Io_Tpm_testValue1 = 0; Io_Tpm_TestPeriod1s = Io_Tpm_PeriodToTicks(CNF_TPM2_CHANNEL0,349400); break;}
		}

		Io_Tpm_PwmChangePeriod(CNF_TPM2_CHANNEL0,Io_Tpm_TestPeriod1s);
	}
	else {}
}

/* FUNCTION NAME: Test_Io_Pwm_Override1s
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: TEST function to verify "Io_Tpm_PwmOverride" functionality
 * OBSERVATIONS: -
 */
void Test_Io_Pwm_Override1s(void)
{
	if(Io_Tpm_Initialized)
	{
		Io_Tpm_TestDutycycle1s += 10;

		if(Io_Tpm_TestDutycycle1s > IO_TPM_100PERCENT)
		{
			Io_Tpm_TestDutycycle1s = 0;
		}
		else {}

		Io_Tpm_TestPeriod1s += 0x1000;

		if(Io_Tpm_TestPeriod1s > IO_TPM_MAX_16BIT)
		{
			Io_Tpm_TestPeriod1s = 0;
		}
		else {}

		Io_Tpm_PwmOverride(CNF_TPM1_CHANNEL0,Io_Tpm_TestDutycycle1s,Io_Tpm_TestPeriod1s);

		Io_Tpm_OverrideDone = TRUE;
	}
	else {}
}

/* FUNCTION NAME: Test_Io_Pwm_Task
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: TEST function to generate a dummy PWM
 * OBSERVATIONS: none
 */
/*void Test_Io_Pwm_Task()
{
	static uint8 counter = 0;
	static uint8 variableDuty = 100;

	counter++;

	if(counter == variableDuty)
	{
		Io_Dio_SetPinLevel(IO_PCS_P0E_20, 0);
	}
	else
		if(counter == 200)
		{
			counter = 0;
			Io_Dio_SetPinLevel(IO_PCS_P0E_20, 1);
		}
}*/
/* end of to do */

/** end of Test Functions implementation **/


