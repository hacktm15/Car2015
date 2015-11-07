/****************************************************************************

COPYRIGHT (C) $Date: Jul 21, 2015 $
$CompanyInfo:  $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_tpm_cnf.c $

$Author: Flueran Gabriel $

 ****************************************************************************/

/** Includes **/

#include "io_tpm_cnf.h"

/** end of Includes **/

/*** -- GUIDELINE FOR CORRECT TPMx DEVICES CONFIGURATION ON FRDM-KL26Z DEVELOPMENT BOARD --
 *** 	1) Determine which TPM channels you want to configure for PWM & DCM functionalities, based on the pins available
 *** 	   (see Pinouts manual of FRDM-KL26Z board for reference).
 *** 	2) Configure the pin functions in "io_pcs_cnf.c".
 *** 	3) Configure the TPMs to be used in the Io_Tpm_Dev_Cnf[] array in "io_tpm_cnf.c".
 *** 	4) Configure the PWM channels in the Io_Tpm_Pwm_Ch_Cnf[] array in "io_tpm_cnf.c".
 *** 	5) Configure the DCM channels in the Io_Tpm_Dcm_Ch_Cnf[] array in "io_tpm_cnf.c".
 *** 	6) Set the indexes of the PWM & DCM channels, in the order written at points 4 & 5 above,
 *** 	   for the #defines CNF_TPMx_CHANNELn in "io_tpm_cnf.h".
 *** 	   NOTE: Channel indexes of Io_Tpm_Pwm_Ch_Cnf[] & Io_Tpm_Dcm_Ch_Cnf[] should both start with IO_TPM_CHANNEL_INDEX0.
 *** 	         Values for channel indexes can be found in "io_tpm.h".
 *** 	         If not configured, a channel should be given the index value IO_TPM_CHANNEL_INDEX_NOT_CONF.
 ***/

/** External Configuration structures **/

	/* NAME: PWM channels configuration structure array */
const Io_Tpm_PwmChannelCnfStruct Io_Tpm_Pwm_Ch_Cnf[]=
{
		/* DESCRIPTION OF STRUCTURE ELEMENTS:
		 * 1: Channel.			Possible values: CNF_TPM0_CHANNEL0, CNF_TPM0_CHANNEL1, CNF_TPM0_CHANNEL2, CNF_TPM0_CHANNEL3,
		 * 										 CNF_TPM0_CHANNEL4, CNF_TPM0_CHANNEL5, CNF_TPM1_CHANNEL0, CNF_TPM1_CHANNEL1,
		 * 										 CNF_TPM2_CHANNEL0, CNF_TPM2_CHANNEL1
		 * 2: Enable on init.	Possible values: IO_TPM_INIT_ENABLE_ON, IO_TPM_INIT_ENABLE_OFF
		 * 3: PWM Type.			Possible values: IO_PWM_TYPE_A, IO_PWM_TYPE_B
		 * 4: Initial Level.	Possible values: IO_TPM_INIT_LEVEL_LOW, IO_TPM_INIT_LEVEL_HIGH
		 * 5: Dutycycle.  		Possible values: 0x0000 -> 0x4000.
		 *						Please DO NOT enter values outside this range, as they will be limited to 0x0000 - 0x4000.
		 */
		/*	Channel				Enable on init			PWM Type		Initial Level			Initial Dutycycle	*/

		{ 	CNF_TPM0_CHANNEL1,	IO_TPM_INIT_ENABLE_ON,	IO_PWM_TYPE_A,	IO_TPM_INIT_LEVEL_LOW,  IO_TPM_PERCENT_TO_4000HEX(50) },
		{ 	CNF_TPM0_CHANNEL2,  IO_TPM_INIT_ENABLE_ON,  IO_PWM_TYPE_A,	IO_TPM_INIT_LEVEL_LOW,  IO_TPM_PERCENT_TO_4000HEX(50) },
		{ 	CNF_TPM2_CHANNEL1,  IO_TPM_INIT_ENABLE_ON,  IO_PWM_TYPE_A,	IO_TPM_INIT_LEVEL_LOW,  IO_TPM_PERCENT_TO_4000HEX(50) },

};
	/* end of PWM channels configuration structure array */

	/* NAME: DCM channels configuration structure array */
const Io_Tpm_DcmChannelCnfStruct Io_Tpm_Dcm_Ch_Cnf[]=
{
		/* DESCRIPTION OF STRUCTURE ELEMENTS:
		 *
		 */

};
	/* end of DCM channels configuration structure array */

	/* NAME: TPM devices configuration structure array */
const Io_Tpm_DeviceCnfStruct Io_Tpm_Dev_Cnf[]=
{
		/* DESCRIPTION OF STRUCTURE ELEMENTS:
		 * 1: TPM to configure.  Possible values: TPM0, TPM1, TPM2.
		 * 2: Clock source.		 Possible values: (recommended) IO_TPM_MODULE_CLOCK, IO_TPM_EXT_CLOCK.
		 * 3: Prescaler value.	 Possible values: IO_TPM_PRESCALER1, IO_TPM_PRESCALER2, IO_TPM_PRESCALER4, ... , IO_TPM_PRESCALER128.
		 * 4: Counting mode. 	 Possible values: (recommended) IO_TPM_COUNT_UP, IO_TPM_COUNT_UP_DOWN
		 * 5: TOF interrupt.     Possible values: IO_TPM_TOF_INTERRUPT_OFF, IO_TPM_TOF_INTERRUPT_ON
		 * 6: Period of TPM		 Possible values: 0x0000 -> 0xFFFF
		 *    channel. (value
		 *    to be put in		 How to calculate:       	  PRESCALER * (MOD + 1)
		 *    MOD register)	 	 (Fclk = Bus clock)	  Ttpm = ----------------------- for UP COUNTING.
		 *   									  				     Fclk
		 *
		 *   									  		  	  PRESCALER * MOD * 2
		 *   									  	  Ttpm = ---------------------  for UP-DOWN COUNTING.
		 *															 Fclk
		 */
		/*  TABLE 1: Ranges for the period depending on the PRESCALER setting with a fixed Fclk = 24 MHz
		 *  ------------------------------------------------------------------------------------------------
		 * 	|	PRESCALER   |		 Ttpm (min) 		|	 Ttpm (min, MOD = 1)  	|   	Ttpm (max)		|
		 * 	|				|   -> dutycycle = 100 % 	|							|						|
		 * 	------------------------------------------------------------------------------------------------
		 * 	|		1		|		41   ns				|		83   ns				|  2730   us = 2.7  ms	|
		 * 	|		2		|		83   ns				|		167  ns				|  5460   us = 5.5  ms	|
		 * 	|		4		|		166  ns				|		333  ns				|  10920  us = 10.9 ms	|
		 * 	|		8		|		333  ns				|		666  ns				|  21850  us = 21.9 ms	|
		 * 	|		16		|		666  ns				|		1330 ns ~= 1 us		|  47690  us = 47.7 ms	|
		 * 	|		32		|		1330 ns	~= 1 us		|		2670 ns	~= 2 us		|  87380  us = 87.4 ms	|
		 * 	|		64		|		2670 ns	~= 2 us		|		4330 ns	~= 4 us		|  174760 us = 174.8 ms	|
		 * 	|		128		|		4330 ns	~= 4 us		|		8670 ns ~= 8 us		|  349520 us = 349.5 ms	|
		 *  ------------------------------------------------------------------------------------------------
		 *
		 *  INPUT CAPTURE MODE:
		 *  NOTE: The maximum frequency for the channel input signal to be detected correctly is counter clock divided by 4.
		 */
		{
				/*1*/ TPM0,
				/*2*/ IO_TPM_MODULE_CLOCK,
				/*3*/ IO_TPM_PRESCALER4,
				/*4*/ IO_TPM_COUNT_UP,
				/*5*/ IO_TPM_TOF_INTERRUPT_OFF,
				/*6*/ IO_TPM_PERIOD_TO_TICKS(1000,IO_TPM_PRESCALER4)
				/* Tpwm = 1 ms, Fpwm = 1 kHz */
		},
		{
				/*1*/ TPM1,
				/*2*/ IO_TPM_MODULE_CLOCK,
				/*3*/ IO_TPM_PRESCALER4,
				/*4*/ IO_TPM_COUNT_UP,
				/*6*/ IO_TPM_TOF_INTERRUPT_OFF,
				/*6*/ IO_TPM_PERIOD_TO_TICKS(4000,IO_TPM_PRESCALER4)
				/* Tpwm = 4 ms, Fpwm = 250 Hz */
		},
		{
				/*1*/ TPM2,
				/*2*/ IO_TPM_MODULE_CLOCK,
				/*3*/ IO_TPM_PRESCALER128,
				/*4*/ IO_TPM_COUNT_UP,
				/*5*/ IO_TPM_TOF_INTERRUPT_OFF,
				/*6*/ IO_TPM_PERIOD_TO_TICKS(200000,IO_TPM_PRESCALER128)
				/* Tpwm = 200 ms, Fpwm = 5 Hz */
		}

};
	/* end of TPM devices configuration structure array */

	/* NAME: TPMx configuration structure array
	 * DESCRPTION: Array to be passed as parameter to the Io_Tpm_Initialization() interface.
	 * NOTE: If configuration arrays names are kept the same, please do not alter the content of the following structure !
	 */
const Io_Tpm_CnfStruct Io_Tpm_Cnf[]=
{
		{
				sizeof(Io_Tpm_Dev_Cnf)/sizeof(Io_Tpm_DeviceCnfStruct),
				(const Io_Tpm_DeviceCnfStruct *)Io_Tpm_Dev_Cnf,
				sizeof(Io_Tpm_Pwm_Ch_Cnf)/sizeof(Io_Tpm_PwmChannelCnfStruct),
				(const Io_Tpm_PwmChannelCnfStruct *)Io_Tpm_Pwm_Ch_Cnf,
				sizeof(Io_Tpm_Dcm_Ch_Cnf)/sizeof(Io_Tpm_DcmChannelCnfStruct),
				(const Io_Tpm_DcmChannelCnfStruct *)Io_Tpm_Dcm_Ch_Cnf
		}
};
	/* end of TPMx configuration structure array */

/** end of External Configuration structures **/


