/****************************************************************************

COPYRIGHT (C) $Date: Jul 15, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_tpm.c $

$Author: Flueran Gabriel, Leonte Alexandru $

 ****************************************************************************/

/** Includes **/

#include "stdlib.h"

#include "MCU_drivers/Dio/io_dio.h"
#include "MCU_drivers/Int/io_int_cnf.h"
#include "MCU_drivers/Pcs/io_pcs_cnf.h"

#include "io_tpm_cnf.h"

/** end of Includes **/

/** Local Functions prototypes **/

static TPM_Type* Io_Tpm_getTpm(uint8 tpmDevice);
static uint16 Io_Tpm_LimitDutycycle(uint16 newDutycycle);
static uint16 Io_Tpm_LimitPeriod(uint16 newPeriod);
static uint32 Io_Tpm_ProcessDutyCycle(uint32 state1, uint32 state2, uint32 state3);
static uint32 Io_Tpm_ProcessPeriod(TPM_Type *tpm, uint32 tiks);
/** end of Local Functions prototypes **/

/** Global variables and constants **/

const Io_Tpm_CnfStruct *Io_Tpm_Cnf_Ptr;

uint16 *Io_Tpm_PwmChLastDutycycle;

uint8 Io_Tpm_Initialized;
uint8 Io_Tpm_Tpm0Used;
uint8 Io_Tpm_Tpm1Used;
uint8 Io_Tpm_Tpm2Used;

Io_Tpm_ChannelStatusStruct *Io_Tpm_Dcm_Channels[3][6];

/** end of Global variables and constants **/

/** Functions implementation **/

/** External Interfaces implementation **/

/* FUNCTION NAME: Io_Tpm_Initialization
 * RETURN TYPE: void
 * PARAMETERS: const Io_Tpm_CnfStruct *Io_Tpm_Cnf
 * DESCRIPTION: Initializes the TPM timers for PWM & DCM/PIM functionalities.
 * OBSERVATIONS: -
 */
void Io_Tpm_Initialization(const Io_Tpm_CnfStruct *Io_Tpm_Cnf)
{
	/* Dummy variables */

	uint8 i;
	uint32 channelDummy;
	uint8 tpmDevice;
	uint16 currentPeriod;
	uint16 *tmpPointer;

	/* end of Dummy variables */

	/* TPM structure variables */

	const Io_Tpm_DeviceCnfStruct *tpm_dev_tmp_ptr;
	const Io_Tpm_PwmChannelCnfStruct *pwm_tmp_ptr;
	const Io_Tpm_DcmChannelCnfStruct *dcm_tmp_ptr;
	TPM_Type *tpm;
	uint8 clockType;
	uint8 prescaler;
	uint8 countingMode;
	uint8 tofInterrupt;
	uint16 tpmPeriod;

	/* end of TPM structure variables */

	/* PWM structure variables */

	uint8 pwmChannel;
	uint8 enableOnInit;
	uint8 pwmType;
	uint8 initLevel;
	uint16 initDutycycle;

	/* end of PWM structure variables */

	/* DCM structure variables */

	uint8 dcmChannel;
	uint8 dcmInterrupt;
	uint8 dcmDma;
	uint8 dcmMode;
	uint32 channel_status;

	/*end of DCM structure variables */

	Io_Tpm_Cnf_Ptr = Io_Tpm_Cnf;

	Io_Tpm_Initialized = FALSE;
	Io_Tpm_Tpm0Used = FALSE;
	Io_Tpm_Tpm1Used = FALSE;
	Io_Tpm_Tpm2Used = FALSE;

	/* Memory allocation for array of "last dutycycle values" */
	tmpPointer = calloc(Io_Tpm_Cnf_Ptr->noOfPwmChannels, sizeof(*tmpPointer));

	if(tmpPointer)
	{
		Io_Tpm_PwmChLastDutycycle = tmpPointer;
	}
	else {} // Memory not available for the requested allocation.
	/* end of Memory allocation for array of "last dutycycle values" */

	/* SIM configuration */

	/* Select the TPM clock source */
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(IO_TPM_CLK_SRC_MCGFLLPLL); /* Predefined clock source = IO_TPM_CLK_SRC_MCGFLLPLL */

	/* end of SIM configuration */

	/* TPM devices configuration */

	/* Iterate through each element of the TPM configuration structure */
	tpm_dev_tmp_ptr = Io_Tpm_Cnf_Ptr->tpm_config_ptr;
	for(i = 0; i < Io_Tpm_Cnf_Ptr->noOfTpms; i++)
	{

		/* TPMx device configuration */
		tpm = tpm_dev_tmp_ptr->tpm;
		clockType = tpm_dev_tmp_ptr->clockType;
		prescaler = tpm_dev_tmp_ptr->prescaler;
		countingMode = tpm_dev_tmp_ptr->countingMode;
		tofInterrupt = tpm_dev_tmp_ptr->tofInterrupt;
		tpmPeriod = tpm_dev_tmp_ptr->period;

		/* Make sure the inserted value is not out of bounds */
		tpmPeriod = Io_Tpm_LimitPeriod(tpmPeriod);

		if(tpm == TPM0)
		{
			if(Io_Tpm_Tpm0Used == FALSE)
			{
				/* Enable the clock for TPM0 clock gate control */
				SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;

				Io_Tpm_Tpm0Used = TRUE;
			}
			else {}
		}
		else
		{
			if(tpm == TPM1)
			{
				if(Io_Tpm_Tpm1Used == FALSE)
				{
					/* Enable the clock for TPM1 clock gate control */
					SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;

					Io_Tpm_Tpm1Used = TRUE;
				}
				else {}
			}
			else
			{
				if(tpm == TPM2)
				{
					if(Io_Tpm_Tpm2Used == FALSE)
					{
						/* Enable the clock for TPM2 clock gate control */
						SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;

						Io_Tpm_Tpm2Used = TRUE;
					}
					else {}
				}
				else {}
			}
		}

		/* Enable the Timer Overflow Interrupt, set counting mode, set prescaler */
		TPM_SC_REG(tpm) = TPM_SC_TOIE(tofInterrupt) | TPM_SC_CPWMS(countingMode) | TPM_SC_PS(prescaler);
		/* TPM counter continues in debug mode */
		TPM_CONF_REG(tpm) = TPM_CONF_DBGMODE(IO_TPM_DEBUG_MODE_ON);
		/* Set the counter starting value */
		TPM_CNT_REG(tpm) = IO_TPM_COUNTER_START_VALUE;
		/* Set the TPM period */
		TPM_MOD_REG(tpm) = tpmPeriod;
		/* Set the clock source for the TPM module */
		TPM_SC_REG(tpm) |= TPM_SC_CMOD(clockType);

		tpm_dev_tmp_ptr++;
	}

	/* end of TPM devices configuration */

	/* PWM channels configuration */

	/* Iterate through each element of the PWM configuration structure */
	pwm_tmp_ptr = Io_Tpm_Cnf_Ptr->pwm_config_ptr;
	for (i = 0; i < Io_Tpm_Cnf_Ptr->noOfPwmChannels; i++)
	{
		channelDummy = pwm_tmp_ptr->channel;
		enableOnInit = pwm_tmp_ptr->enableOnInit;
		pwmType = pwm_tmp_ptr->pwmType;
		initLevel = pwm_tmp_ptr->initLevel;

		pwmChannel = IO_TPM_GET_CHANNEL(channelDummy);
		tpmDevice = IO_TPM_GET_DEVICE(channelDummy);
		tpm = Io_Tpm_getTpm(tpmDevice);

		currentPeriod = (uint16)TPM_MOD_REG(tpm);

		/* Set PWM type */
		TPM_CnSC_REG(tpm,pwmChannel) = TPM_CnSC_MSB_MASK | pwmType;

		/* Set dutycycle based on the value of enableOnInit */
		if(enableOnInit == IO_TPM_INIT_ENABLE_ON)			/* Channel is enabled on initialization */
		{
			/* Make sure the inserted value is not out of bounds */
			initDutycycle = Io_Tpm_LimitDutycycle(pwm_tmp_ptr->initDutycycle);
		}
		else
		{
			if(enableOnInit == IO_TPM_INIT_ENABLE_OFF)		/* Channel is not enabled on initialization */
			{
				/* Set initial dutycycle based on init level */
				if(initLevel == IO_TPM_INIT_LEVEL_LOW)
				{
					if(pwmType == IO_PWM_TYPE_A)
					{
						initDutycycle = IO_TPM_0PERCENT_DUTYCYCLE;
					}
					else
					{
						if(pwmType == IO_PWM_TYPE_B)
						{
							initDutycycle = IO_TPM_100PERCENT_DUTYCYCLE;
						}
						else {}
					}
				}
				else
				{
					if(initLevel == IO_TPM_INIT_LEVEL_HIGH)
					{
						if(pwmType == IO_PWM_TYPE_A)
						{
							initDutycycle = IO_TPM_100PERCENT_DUTYCYCLE;
						}
						else
						{
							if(pwmType == IO_PWM_TYPE_B)
							{
								initDutycycle = IO_TPM_0PERCENT_DUTYCYCLE;
							}
							else {}
						}
					}
					else {}
				}
			}
			else {}
		}
		/* Hold the last value of dutycycle for the current PWM channel */
		(Io_Tpm_PwmChLastDutycycle[i]) = initDutycycle;

		/* Extend the value of the dutycycle to the range 0 - MOD */
		TPM_CnV_REG(tpm,pwmChannel) = IO_TPM_4000HEX_TO_MODHEX(initDutycycle,currentPeriod);
		/* end of Set PWM type */

		pwm_tmp_ptr++;
	}

	/* end of PWM channels configuration */

	/* DCM channels configuration */

	/* Iterate through each element of DCM configuration structure */
	dcm_tmp_ptr = Io_Tpm_Cnf_Ptr->dcm_config_ptr;
	for(i = 0; i < Io_Tpm_Cnf_Ptr->noOfDcmChannels; i++)
	{
		channelDummy = dcm_tmp_ptr->channel;
		dcmChannel = IO_TPM_GET_CHANNEL(channelDummy);
		tpmDevice = IO_TPM_GET_DEVICE(channelDummy);

		dcmDma = dcm_tmp_ptr->dma_request;
		dcmMode = dcm_tmp_ptr->mode;
		dcmInterrupt = dcm_tmp_ptr->interrupt_request;										/* unused in inititalization */
		tpm = Io_Tpm_getTpm(tpmDevice);

		if(dcmDma == 1)								/* DMA REQUEST */
		{
			channel_status = TPM_CnSC_DMA_MASK;
		}else
		{
			channel_status = 0;
		}

		switch(dcmMode)						/*CHANNEL MODE */
		{
		case 0:

			break;
		case 1:
			channel_status |= TPM_CnSC_ELSA_MASK;							/* Input capture Capture on Rising Edge Only*/
			break;
		case 2:
			channel_status |= TPM_CnSC_ELSB_MASK;							/* Input capture Capture on Falling Edge Only */
			break;
		case 3:
			channel_status |= TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK; 		/* Input capture Capture on Rising or Falling Edge */
			break;
		}

		if(dcmInterrupt == 1)
		{
			channel_status |= TPM_CnSC_CHIE_MASK;
		}

		/* Memory allocation for array of all dcm channels */
		Io_Tpm_Dcm_Channels[tpmDevice][dcmChannel] = calloc(1, sizeof(*Io_Tpm_Dcm_Channels));

		Io_Tpm_Dcm_Channels[tpmDevice][dcmChannel]->ch_number = dcmChannel;
		Io_Tpm_Dcm_Channels[tpmDevice][dcmChannel]->duty_cycle = 0;
		Io_Tpm_Dcm_Channels[tpmDevice][dcmChannel]->overflow_counter = 0;
		Io_Tpm_Dcm_Channels[tpmDevice][dcmChannel]->period = 0;
		Io_Tpm_Dcm_Channels[tpmDevice][dcmChannel]->port_pin = dcm_tmp_ptr->port_pin;
		Io_Tpm_Dcm_Channels[tpmDevice][dcmChannel]->state = 0;
		Io_Tpm_Dcm_Channels[tpmDevice][dcmChannel]->state1 = 0;
		Io_Tpm_Dcm_Channels[tpmDevice][dcmChannel]->state2 = 0;
		Io_Tpm_Dcm_Channels[tpmDevice][dcmChannel]->state3 = 0;
		Io_Tpm_Dcm_Channels[tpmDevice][dcmChannel]->active_level = dcm_tmp_ptr->active_level;
		TPM_CnSC_REG(tpm,dcmChannel) = 0UL;									/* Clear Channel Status and Control */
		TPM_CnSC_REG(tpm,dcmChannel) = channel_status;

		dcm_tmp_ptr++;
	}

	/* end of DCM channels configuration */

	Io_Tpm_Initialized = TRUE;
}

/* FUNCTION NAME: Io_Tpm_PwmEnable
 * RETURN TYPE: void
 * PARAMETERS: uint32 channel
 * DESCRIPTION: Enables the selected PWM channel.
 * OBSERVATIONS: -
 */
void Io_Tpm_PwmEnable(uint32 channel)
{
	uint16 currentPeriod;
	uint8 pwmChannel;
	uint8 tpmDevice;
	TPM_Type *tpm;
	uint8 chIndex;
	uint16 initDutycycle;

	if(Io_Tpm_Initialized == TRUE)
	{
		pwmChannel  = IO_TPM_GET_CHANNEL(channel);
		tpmDevice = IO_TPM_GET_DEVICE(channel);
		tpm = Io_Tpm_getTpm(tpmDevice);
		chIndex = IO_TPM_GET_INDEX(channel);

		if(tpm)
		{
			currentPeriod = (uint16)TPM_MOD_REG(tpm);

			/* Make sure the inserted value is not out of bounds */
			initDutycycle = Io_Tpm_LimitDutycycle(Io_Tpm_Pwm_Ch_Cnf[chIndex].initDutycycle);

			/* Hold the last value of dutycycle for the selected channel */
			Io_Tpm_PwmChLastDutycycle[chIndex] = initDutycycle;

			/* Set the configured dutycycle for the selected PWM channel */
			TPM_CnV_REG(tpm,pwmChannel) = IO_TPM_4000HEX_TO_MODHEX(initDutycycle,currentPeriod);
		}
		else {}
	}
	else {}
}

/* FUNCTION NAME: Io_Tpm_PwmChangeDutycycle
 * RETURN TYPE: void
 * PARAMETERS: uint32 channel, uint16 newDutycycle
 * DESCRIPTION: Feeds the selected PWM channel a new dutycycle, starting from the next period.
 * OBSERVATIONS: 1) Is done coherently (supported by HW)
 * 				 2) The Io_Tpm_PwmChangeDutycycle waits for the end of the
 * 				 current period in order to change the Dutycycle register value
 * FURTHER
 * IMPROVEMENTS: 1) It may be improved by doing the change coherently by SW,
 * 				 using end-of-period interrupts for each channel:
 * 			  		- current & new dutycycle kept in an array
 * 		  			- flag for interrupt processing
 */
void Io_Tpm_PwmChangeDutycycle(uint32 channel, uint16 newDutycycle)
{
	uint16 currentPeriod;
	uint8 pwmChannel;
	uint8 tpmDevice;
	TPM_Type *tpm;
	uint8 chIndex;

	if(Io_Tpm_Initialized == TRUE)
	{
		pwmChannel  = IO_TPM_GET_CHANNEL(channel);
		tpmDevice = IO_TPM_GET_DEVICE(channel);
		tpm = Io_Tpm_getTpm(tpmDevice);
		chIndex = IO_TPM_GET_INDEX(channel);

		if(tpm)
		{
			currentPeriod = (uint16)TPM_MOD_REG(tpm);

			/* Make sure the inserted value is not out of bounds */
			newDutycycle = Io_Tpm_LimitDutycycle(newDutycycle);

			/* Hold the last value of dutycycle for the selected channel */
			Io_Tpm_PwmChLastDutycycle[chIndex] = newDutycycle;

			/* Set the new dutycycle for the selected channel */
			TPM_CnV_REG(tpm,pwmChannel) = IO_TPM_4000HEX_TO_MODHEX(newDutycycle,currentPeriod);
		}
		else {}
	}
	else {}
}

/* FUNCTION NAME: Io_Tpm_PwmChangePeriod
 * RETURN TYPE: void
 * PARAMETERS: uint32 channel, uint16 newPeriod
 * DESCRIPTION: Feeds the selected PWM channel a new period, starting from the next period.
 * OBSERVATIONS: 1) Is done coherently (supported by HW)
 *  		  	 2) Dutycycle must be updated together with the Period, in order to
 *  		  	 retain the percentage of the Dutycycle w.r.t. the Period
 * 		     	 3) The Io_Tpm_PwmChangePeriod function waits for the end of the
 * 				 current period in order to change the period register value
 * FURTHER
 * IMPROVEMENTS: 1) It may be improved by doing the change coherently by SW,
 * 				 using end-of-period interrupts for each channel:
 * 			  		- current & new period kept in an array
 * 		  			- flag for interrupt processing
 */
void Io_Tpm_PwmChangePeriod(uint32 channel, uint16 newPeriod)
{
	uint16 currentDutycycle;
	uint8 pwmChannel;
	uint8 tpmDevice;
	TPM_Type *tpm;
	uint8 chIndex;

	if(Io_Tpm_Initialized == TRUE)
	{
		pwmChannel  = IO_TPM_GET_CHANNEL(channel);
		tpmDevice = IO_TPM_GET_DEVICE(channel);
		tpm = Io_Tpm_getTpm(tpmDevice);
		chIndex = IO_TPM_GET_INDEX(channel);

		if(tpm)
		{
			currentDutycycle = Io_Tpm_LimitDutycycle(Io_Tpm_PwmChLastDutycycle[chIndex]);

			/* Make sure the inserted value is not out of bounds */
			newPeriod = Io_Tpm_LimitPeriod(newPeriod);

			/* Set the new period for the selected channel */
			TPM_MOD_REG(tpm) = newPeriod;
			/* Set the new dutycycle for the selected channel */
			TPM_CnV_REG(tpm,pwmChannel) = IO_TPM_4000HEX_TO_MODHEX(currentDutycycle,newPeriod);
		}
		else {}
	}
	else {}
}

/* FUNCTION NAME: Io_Tpm_PeriodToTicks
 * RETURN TYPE: uint16
 * PARAMETERS: uint32 channel
 * DESCRIPTION: Converts the given period [us] into the value to be written in MOD register.
 * OBSERVATIONS: 1) Private to "io_pwm_main.c"
 * 				 2) Prescaler is taken directly from the register
 */
uint16 Io_Tpm_PeriodToTicks(uint32 channel, uint32 usPeriod)
{
	uint16 ticks;
	uint8 prescaler;
	uint8 tpmDevice;
	TPM_Type *tpm;

	tpmDevice = IO_TPM_GET_DEVICE(channel);
	tpm = Io_Tpm_getTpm(tpmDevice);

	if(tpm)
	{
		/* Find the prescaler of the selected TPM */
		prescaler = (uint8)(TPM_SC_REG(tpm) & TPM_SC_PS_MASK);

		ticks = IO_TPM_PERIOD_TO_TICKS(usPeriod,prescaler);
	}

	return ticks;
}

/* FUNCTION NAME: Io_Tpm_FrequencyToTicks
 * RETURN TYPE: uint16
 * PARAMETERS: uint32 channel
 * DESCRIPTION: Converts the given frequency [Hz] into the value to be written in MOD register.
 * OBSERVATIONS: 1) Private to "io_pwm_main.c"
 * 				 2) Prescaler is taken directly from the register
 */
uint16 Io_Tpm_FrequencyToTicks(uint32 channel, uint32 hzFrequency)
{
	uint16 ticks;
	uint8 prescaler;
	uint8 tpmDevice;
	TPM_Type *tpm;

	tpmDevice = IO_TPM_GET_DEVICE(channel);
	tpm = Io_Tpm_getTpm(tpmDevice);

	if(tpm)
	{
		/* Find the prescaler of the selected TPM */
		prescaler = (uint8)(1 << (TPM_SC_REG(tpm) & TPM_SC_PS_MASK));

		/* prescaler = pow(2,prescaler) */

		ticks = IO_TPM_FREQUENCY_TO_TICKS(hzFrequency,prescaler);
	}

	return ticks;
}

/** end of External Interfaces implementation **/

/** Local Functions implementation **/

/* FUNCTION NAME: Io_Tpm_getTpm
 * RETURN TYPE: TPM_Type *
 * PARAMETERS: uint8 tpmDevice
 * DESCRIPTION: Returns the TPM device pointer.
 * OBSERVATIONS: 1) Private to "io_pwm_main.c"
 */
TPM_Type* Io_Tpm_getTpm(uint8 tpmDevice)
{
	TPM_Type *temp = NULL_PTR;
	if(tpmDevice == IO_TPM_DEVICE0)
	{
		temp = TPM0;
	}
	else
	{
		if(tpmDevice == IO_TPM_DEVICE1)
		{
			temp = TPM1;
		}
		else
		{
			if(tpmDevice == IO_TPM_DEVICE2)
			{
				temp = TPM2;
			}
			else {}

		}
	}
	return temp;
}

/* FUNCTION NAME: Io_Tpm_LimitDutycycle
 * RETURN TYPE: uint16
 * PARAMETERS: uint16 newDutycycle
 * DESCRIPTION: Returns the dutycycle limited to the range IO_TPM_0PERCENT_DUTYCYCLE - IO_TPM_100PERCENT_DUTYCYCLE.
 * OBSERVATIONS: 1) Private to "io_pwm_main.c"
 */
uint16 Io_Tpm_LimitDutycycle(uint16 newDutycycle)
{
	uint16 limitedDutycycle = newDutycycle;

	if(limitedDutycycle > IO_TPM_100PERCENT_DUTYCYCLE)
	{
		limitedDutycycle = IO_TPM_100PERCENT_DUTYCYCLE;
	}
	else
	{
		if(limitedDutycycle < IO_TPM_0PERCENT_DUTYCYCLE)
		{
			limitedDutycycle = IO_TPM_0PERCENT_DUTYCYCLE;
		}
		else {}
	}

	return limitedDutycycle;
}

/* FUNCTION NAME: Io_Tpm_LimitPeriod
 * RETURN TYPE: uint16
 * PARAMETERS: uint16 newPeriod
 * DESCRIPTION: Returns the period limited to the range IO_TPM_MIN_PERIOD - IO_TPM_MAX_PERIOD.
 * OBSERVATIONS: 1) Private to "io_pwm_main.c"
 */
uint16 Io_Tpm_LimitPeriod(uint16 newPeriod)
{
	uint16 limitedPeriod = newPeriod;

	if(limitedPeriod > IO_TPM_MAX_PERIOD)
	{
		limitedPeriod = IO_TPM_MAX_PERIOD;
	}
	else
	{
		if(limitedPeriod < IO_TPM_MIN_PERIOD)
		{
			limitedPeriod = IO_TPM_MIN_PERIOD;
		}
		else {}
	}

	return limitedPeriod;
}

/* FUNCTION NAME: Io_Tpm_DcmEnableInputCapture
 * RETURN TYPE: uint8  		ERR_OK = 0; ERR_X !=0;
 * PARAMETERS: uint32 channel
 * 			   uint8 mode - possible values :0 (waiting for raising edge), 1(period), 2(width)
 * DESCRIPTION: Enable interrupt request for the selected TPM channel(start capture).
 * OBSERVATIONS: -
 */
uint8 Io_Tpm_DcmEnableInputCapture(uint32 channel)
{
	uint8 dcmChannel;
	uint8 tpmDevice;
	TPM_Type *tpm;

	if(Io_Tpm_Initialized == TRUE)
	{
		dcmChannel  = IO_TPM_GET_CHANNEL(channel);
		tpmDevice = IO_TPM_GET_DEVICE(channel);
		tpm = Io_Tpm_getTpm(tpmDevice);

		TPM_CnSC_REG(tpm,dcmChannel) |= 0UL;
		TPM_CnSC_REG(tpm,dcmChannel) |= TPM_CnSC_CHIE_MASK ;				/* Enables Interrupt request */

	}else {
		//initialize first
		}

	return ERR_OK;
}

/* FUNCTION NAME: Io_Tpm_DcmDisableInputCapture
 * RETURN TYPE: uint8  		ERR_OK = 0; ERR_X !=0;
 * PARAMETERS: uint32 channel
 * DESCRIPTION: Disable interrupt request for the selected TPM channel(start capture).
 * OBSERVATIONS: -
 */
uint8 Io_Tpm_DcmDisableInputCapture(uint32 channel)
{
	uint8 dcmChannel;
	uint8 tpmDevice;
	TPM_Type *tpm;
	/*** TODO LEONTE: not used Oct 30, 2015
	 uint8 chIndex;
	 ***/

	if(Io_Tpm_Initialized == TRUE)
	{
		dcmChannel  = IO_TPM_GET_CHANNEL(channel);
		tpmDevice = IO_TPM_GET_DEVICE(channel);
		tpm = Io_Tpm_getTpm(tpmDevice);

		TPM_CnSC_REG(tpm,dcmChannel) &= ~(1UL << TPM_CnSC_CHIE_SHIFT);				/* Disable Interrupt request */

	}else {
		//initialize first
		}
	return ERR_OK;

}

uint32 Io_Tpm_ProcessPeriod(TPM_Type *tpm, uint32 tiks)
{
	 double period = (double)((double)tiks * (double)1000000) / (double)(24000000/(1<< (tpm->SC & TPM_SC_PS_MASK)));	/* micro seconds */
	 return (uint32)period;
}

uint32 Io_Tpm_ProcessDutyCycle(uint32 state1, uint32 state2, uint32 state3)
{
	uint32 dc0 = ((state2 -state1)* 100000)/(state3 - state1);
	//double dc = ((double)(state2 -state1)* 100000)/(state3 - state1);
	return (uint32)dc0;
}

void Io_Tpm_GetPeriod(uint32 channel , uint32 *address)
{
	 *address = (Io_Tpm_Dcm_Channels[IO_TPM_GET_DEVICE(channel)][IO_TPM_GET_CHANNEL(channel)])->period;

}

void Io_Tpm_GetDutyCycle(uint32 channel, uint32 *address)
{
	*address = (Io_Tpm_Dcm_Channels[IO_TPM_GET_DEVICE(channel)][IO_TPM_GET_CHANNEL(channel)])->duty_cycle;

}

uint32 Io_Tpm_GetPulseWidth(uint32 channel)
{
	return (uint32)  (Io_Tpm_Dcm_Channels[IO_TPM_GET_DEVICE(channel)][IO_TPM_GET_CHANNEL(channel)]->duty_cycle *
						Io_Tpm_Dcm_Channels[IO_TPM_GET_DEVICE(channel)][IO_TPM_GET_CHANNEL(channel)]->period)/100;
}

void Io_Tpm_Porcess_InputCapture(Io_Tpm_ChannelStatusStruct *channel_status,TPM_Type *tpm)
{
	switch(channel_status->state){

				case 0:
					if(Io_Dio_GetPinLevel(channel_status->port_pin) == channel_status->active_level)				/*check for rising */
					{
						channel_status->state1 = TPM_CnV_REG(tpm,channel_status->ch_number);
						channel_status->overflow_counter = 0;
						channel_status->state++;
					}
					break;

				case 1:
					channel_status->state2 = TPM_CnV_REG(tpm,channel_status->ch_number) + (TPM_MOD_REG(tpm) * channel_status->overflow_counter);
					channel_status->state++;
					break;
				case 2:
					channel_status->state3 = TPM_CnV_REG(tpm,channel_status->ch_number) + (TPM_MOD_REG(tpm)*channel_status->overflow_counter);
					channel_status->period = Io_Tpm_ProcessPeriod(tpm, channel_status->state3 - channel_status->state1);
					channel_status->duty_cycle = Io_Tpm_ProcessDutyCycle(channel_status->state1, channel_status->state2, channel_status->state3);
					channel_status->state1 = 0;
					channel_status->state2 = 0;
					channel_status->overflow_counter = 0;
					channel_status->state = 0;
					break;
				}
}
	/** end of  Local Functions implementation **/

	/** Interrupts handlers implementation **/

/* FUNCTION NAME: Io_Tpm_Tpm0Isr
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Handles the interrupts generated by the TPM0 module.
 * OBSERVATIONS: -
 */
void Io_Tpm_Tpm0Isr(void)
{
	/*TODO FLUERAN: IRQ can be generated by any of the TPM's channels. Overflow or Channel interrupt. */
	uint8 i;
	if(TPM_STATUS_REG(TPM0) & TPM_STATUS_TOF_MASK){									/* check if TOF is set */
		for(i=0;i<6;i++)
		{
			if(Io_Tpm_Dcm_Channels[0][i] != NULL)
			{
				Io_Tpm_Dcm_Channels[0][i]->overflow_counter++;
			}
		}
		TPM_SC_REG(TPM0) |= TPM_SC_TOF_MASK;										/* Delete the TOF flag such that the IRQ ends */
	}

	if( TPM_STATUS_REG(TPM0) & TPM_STATUS_CH0F_MASK )						/* CHANNEL 0*/
	{
		switch(IO_TPM_GET_CFGTYPE(CNF_TPM0_CHANNEL0))
		{
			case IO_TPM_CH_CONFIG_PWM:
			break;
			case IO_TPM_CH_CONFIG_DCM:
				Io_Tpm_Porcess_InputCapture((Io_Tpm_ChannelStatusStruct *)Io_Tpm_Dcm_Channels[0][0], TPM0);
			break;
		}
		TPM_CnSC_REG(TPM0,IO_TPM_CHANNEL0) |=  TPM_CnSC_CHF_MASK;						/*Clear CHF  - event occurred */

	}else if(TPM_STATUS_REG(TPM0) & TPM_STATUS_CH1F_MASK)					/* CHANNEL 1*/
	{
		switch(IO_TPM_GET_CFGTYPE(CNF_TPM0_CHANNEL1))
		{
			case IO_TPM_CH_CONFIG_PWM:
			break;
			case IO_TPM_CH_CONFIG_DCM:
				Io_Tpm_Porcess_InputCapture((Io_Tpm_ChannelStatusStruct *)Io_Tpm_Dcm_Channels[0][1], TPM0);
			break;
		}
		TPM_CnSC_REG(TPM0,IO_TPM_CHANNEL1) |=  TPM_CnSC_CHF_MASK;						/*Clear CHF  - event occurred */

	}else if(TPM_STATUS_REG(TPM0) & TPM_STATUS_CH2F_MASK)									/* CHANNEL 2*/
	{
		switch(IO_TPM_GET_CFGTYPE(CNF_TPM0_CHANNEL2))
		{
			case IO_TPM_CH_CONFIG_PWM:
			break;
			case IO_TPM_CH_CONFIG_DCM:
				Io_Tpm_Porcess_InputCapture((Io_Tpm_ChannelStatusStruct *)Io_Tpm_Dcm_Channels[0][2], TPM0);
			break;
		}

		TPM_CnSC_REG(TPM0,IO_TPM_CHANNEL2) |=  TPM_CnSC_CHF_MASK;						/*Clear CHF  - event occurred */

	}else if(TPM_STATUS_REG(TPM0) & TPM_STATUS_CH3F_MASK)									/* CHANNEL 3*/
	{
		switch(IO_TPM_GET_CFGTYPE(CNF_TPM0_CHANNEL3))
				{
					case IO_TPM_CH_CONFIG_PWM:
					break;
					case IO_TPM_CH_CONFIG_DCM:
						Io_Tpm_Porcess_InputCapture((Io_Tpm_ChannelStatusStruct *)Io_Tpm_Dcm_Channels[0][3], TPM0);
					break;
				}
		TPM_CnSC_REG(TPM0,IO_TPM_CHANNEL3) |=  TPM_CnSC_CHF_MASK;						/*Clear CHF  - event occurred */

	}else if(TPM_STATUS_REG(TPM0) & TPM_STATUS_CH4F_MASK)								/* CHANNEL 4*/
	{
		switch(IO_TPM_GET_CFGTYPE(CNF_TPM0_CHANNEL4))
		{
			case IO_TPM_CH_CONFIG_PWM:
			break;
			case IO_TPM_CH_CONFIG_DCM:
				Io_Tpm_Porcess_InputCapture((Io_Tpm_ChannelStatusStruct *)Io_Tpm_Dcm_Channels[0][4], TPM0);
			break;
		}
		TPM_CnSC_REG(TPM0,IO_TPM_CHANNEL4) |=  TPM_CnSC_CHF_MASK;						/*Clear CHF  - event occurred */
	}else if(TPM_STATUS_REG(TPM0) & TPM_STATUS_CH5F_MASK)								/* CHANNEL 5*/
	{
		switch(IO_TPM_GET_CFGTYPE(CNF_TPM0_CHANNEL5))
				{
					case IO_TPM_CH_CONFIG_PWM:
					break;
					case IO_TPM_CH_CONFIG_DCM:
						Io_Tpm_Porcess_InputCapture((Io_Tpm_ChannelStatusStruct *)Io_Tpm_Dcm_Channels[0][5], TPM0);
					break;
				}
		TPM_CnSC_REG(TPM0,IO_TPM_CHANNEL5) |=  TPM_CnSC_CHF_MASK;						/*Clear CHF  - event occurred */
	}
}

/* FUNCTION NAME: Io_Tpm_Tpm1Isr
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Handles the interrupts generated by the TPM1 module.
 * OBSERVATIONS: -
 */
void Io_Tpm_Tpm1Isr(void)
{
	/*TODO FLUERAN: IRQ can be generated by any of the TPM's channels. Overflow or Channel interrupt. */
	uint8 i;
	if(TPM_STATUS_REG(TPM1) & TPM_STATUS_TOF_MASK){											/* check if TOF is set */
		for(i=0;i<2;i++)
		{
			if(Io_Tpm_Dcm_Channels[1][i] != NULL)
			{
				Io_Tpm_Dcm_Channels[1][i]->overflow_counter++;
			}
		}
		TPM1_SC |= TPM_SC_TOF_MASK;	/* Delete the TOF flag such that the IRQ ends */
	}

	if( TPM_STATUS_REG(TPM1) & TPM_STATUS_CH0F_MASK )										/* CHANNEL 0*/
	{
		switch(IO_TPM_GET_CFGTYPE(CNF_TPM1_CHANNEL0))
		{
			case IO_TPM_CH_CONFIG_PWM:
			break;
			case IO_TPM_CH_CONFIG_DCM:
				Io_Tpm_Porcess_InputCapture((Io_Tpm_ChannelStatusStruct *)Io_Tpm_Dcm_Channels[1][0], TPM1);
			break;
		}
		TPM_CnSC_REG(TPM1,IO_TPM_CHANNEL0) |=  TPM_CnSC_CHF_MASK;							/*Clear CHF  - event occurred */

	}else if(TPM_STATUS_REG(TPM1) & TPM_STATUS_CH1F_MASK)									/* CHANNEL 1*/
	{
		switch(IO_TPM_GET_CFGTYPE(CNF_TPM1_CHANNEL1))
			{
				case IO_TPM_CH_CONFIG_PWM:
				break;
				case IO_TPM_CH_CONFIG_DCM:
					Io_Tpm_Porcess_InputCapture((Io_Tpm_ChannelStatusStruct *)Io_Tpm_Dcm_Channels[1][1], TPM1);
				break;
			}
		TPM_CnSC_REG(TPM1,IO_TPM_CHANNEL1) |=  TPM_CnSC_CHF_MASK;							/*Clear CHF  - event occurred */
	}
}

void Io_Tpm_Tpm2Isr(void)
{
	/*TODO FLUERAN: IRQ can be generated by any of the TPM's channels. Overflow or Channel interrupt. */
	uint8 i;
	if(TPM_STATUS_REG(TPM2) & TPM_STATUS_TOF_MASK){												/* check if TOF is set */
		for(i=0;i<6;i++)
		{
			if(Io_Tpm_Dcm_Channels[2][i] != NULL)
			{
				Io_Tpm_Dcm_Channels[2][i]->overflow_counter++;
			}
		}
		TPM2_SC |= TPM_SC_TOF_MASK;																/* Delete the TOF flag such that the IRQ ends */
	}

	if( TPM_STATUS_REG(TPM2) & TPM_STATUS_CH0F_MASK )											/* CHANNEL 0*/
	{
		switch(IO_TPM_GET_CFGTYPE(CNF_TPM2_CHANNEL0))
		{
			case IO_TPM_CH_CONFIG_PWM:
			break;
			case IO_TPM_CH_CONFIG_DCM:
				Io_Tpm_Porcess_InputCapture((Io_Tpm_ChannelStatusStruct *)Io_Tpm_Dcm_Channels[2][0], TPM2);
			break;
		}
		TPM_CnSC_REG(TPM2,IO_TPM_CHANNEL0) |=  TPM_CnSC_CHF_MASK;								/*Clear CHF  - event occurred */

	}else if(TPM_STATUS_REG(TPM2) & TPM_STATUS_CH1F_MASK){										/* CHANNEL 1*/
		switch(IO_TPM_GET_CFGTYPE(CNF_TPM2_CHANNEL1))
			{
				case IO_TPM_CH_CONFIG_PWM:
				break;
				case IO_TPM_CH_CONFIG_DCM:
					Io_Tpm_Porcess_InputCapture((Io_Tpm_ChannelStatusStruct *)Io_Tpm_Dcm_Channels[2][1], TPM2);
				break;
			}
		TPM_CnSC_REG(TPM2,IO_TPM_CHANNEL1) |=  TPM_CnSC_CHF_MASK;								/*Clear CHF  - event occurred */

	}
}

	/** end of Interrupts handlers implementation **/

/** end of Functions implementation **/

/** Functions to be implemented **/

/* FUNCTION NAME: Io_Tpm_PwmOverride
 * RETURN TYPE: void
 * PARAMETERS: uint32 channel, uint16 newDutycycle, uint16 newPeriod
 * DESCRIPTION: Feeds the selected PWM channel a dutycycle & a new period, starting from the current period.
 * OBSERVATIONS: 1) Change takes place immediately
 * 				 2) The Io_Tpm_PwmOverride function disables the entire TPM and introduces
 * 				 a delay in the output of the other channels of that TPM;
 * 				 the function must be tested to see if the delay introduced is considerable.
 */
/*
void Io_Tpm_PwmOverride(uint32 channel, uint16 newDutycycle, uint16 newPeriod)
{
	// Disable, change period & dutycycle, enable.
	uint8 i;
	uint8 tpmDevice;
	uint8 pwmChannel;
	//uint8 chIndex;
	TPM_Type *tpm;
	uint16 clockType;
	const Io_Tpm_DeviceCnfStruct *tpm_dev_tmp_ptr;

	if(Io_Tpm_Initialized == TRUE)
	{
		pwmChannel  = IO_TPM_GET_CHANNEL(channel);
		tpmDevice = IO_TPM_GET_DEVICE(channel);
		tpm = Io_Tpm_getTpm(tpmDevice);

		if(tpm)
		{
			tpm_dev_tmp_ptr = Io_Tpm_Cnf->tpm_config_ptr;

			for(i = 0; i < Io_Tpm_Cnf_Ptr->noOfTpms; i++)
			{
				if(tpm_dev_tmp_ptr->tpm == tpm)
				{
					clockType = tpm_dev_tmp_ptr->clockType;
					break;
				}
				else {}

				tpm_dev_tmp_ptr++;
			}

			// Make sure the inserted value is not out of bounds
			newPeriod = Io_Tpm_LimitPeriod(newPeriod);
			// Make sure the inserted value is not out of bounds
			newDutycycle = Io_Tpm_LimitDutycycle(newDutycycle);

			// Disable the TPM module
			TPM_SC_REG(tpm) |= TPM_SC_CMOD(IO_TPM_CLK_DISABLED);

			// Reset the counter
			TPM_CNT_REG(tpm) = IO_TPM_COUNTER_START_VALUE;
			// Set the new period for the selected channel
			TPM_MOD_REG(tpm) = newPeriod;
			// Set the new dutycycle for the selected channel
			TPM_CnV_REG(tpm,pwmChannel) = IO_TPM_4000HEX_TO_MODHEX(newDutycycle,newPeriod);

			// Enable the TPM module with the configured clock
			TPM_SC_REG(tpm) |= TPM_SC_CMOD(clockType);
		}
		else {}
	}
	else {}
}
 */

/** end of Functions to be implemented **/
