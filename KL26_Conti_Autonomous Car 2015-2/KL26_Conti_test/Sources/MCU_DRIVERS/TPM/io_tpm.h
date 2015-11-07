/****************************************************************************

COPYRIGHT (C) $Date: Jul 15, 2015 $
$CompanyInfo:  $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_tpm.h $

$Author: Flueran Gabriel $

 ****************************************************************************/

#ifndef IO_TPM_H
#define IO_TPM_H


/** Includes **/

#include "MKL26Z4.h"
#include "PLATFORM_TYPES/std_types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "PLATFORM_TYPES/platform_types.h"

/** end of Includes **/

/** Defines **/

	/* Macros */
#define IO_TPM_4000HEX_TO_PERCENT(x) 				(uint8)((uint32)(IO_TPM_100PERCENT * x) / IO_TPM_100PERCENT_DUTYCYCLE)
#define IO_TPM_PERCENT_TO_4000HEX(x) 				(uint16)((uint32)(IO_TPM_100PERCENT_DUTYCYCLE * x) / IO_TPM_100PERCENT)
#define IO_TPM_4000HEX_TO_FFFFHEX(x) 				(uint16)((uint32)(IO_TPM_MAX_16BIT * x) / IO_TPM_100PERCENT_DUTYCYCLE)
#define IO_TPM_PERCENT_TO_FFFFHEX(x) 				(uint16)((uint32)(IO_TPM_MAX_16BIT * x) / IO_TPM_100PERCENT)
#define IO_TPM_4000HEX_TO_MODHEX(DUTY,PERIOD)		(uint16)((uint32)(DUTY * PERIOD) / IO_TPM_100PERCENT_DUTYCYCLE)

/* This way of calculating the dutycycle from the current value of dutycycle & period is faulty,
 * since calculation errors arise and they can not be predicted for every value of the period and
 * every period translation case.
 * NOTE: Should not be used in code.
 * #define IO_PWM_MODHEX_TO_4000HEX(DUTY,PERIOD)		(uint16)((uint32)((DUTY * IO_TPM_100PERCENT_DUTYCYCLE) / PERIOD) + 1)  // +1 for compensation
*/

#define IO_TPM_PERIOD_TO_TICKS(US_PERIOD,TPM_PRESCALER)	 (uint16)(((uint32)((uint32)(IO_TPM_BUS_FREQ / IO_TPM_MICROSEC_DIV) * US_PERIOD) / (1 << TPM_PRESCALER)) - 1)
#define IO_TPM_FREQUENCY_TO_TICKS(HZ_FREQ,TPM_PRESCALER) (uint16)((IO_TPM_BUS_FREQ / (uint32)(HZ_FREQ * (1 << TPM_PRESCALER))) - 1)

#define IO_TPM_GENERATE_CHANNEL(tpm,channel,cfgType,index)	(uint32)(((cfgType << 24) & IO_TPM_GET_CFGTYPE_MASK) | ((tpm << 16) & IO_TPM_GET_DEVICE_MASK) | ((channel << 8) & IO_TPM_GET_CHANNEL_MASK)  | (index & IO_TPM_GET_INDEX_MASK))

#define IO_TPM_GET_CFGTYPE(channel)					(uint8)((channel & IO_TPM_GET_CFGTYPE_MASK) >> 24)
#define IO_TPM_GET_DEVICE(channel)					(uint8)((channel & IO_TPM_GET_DEVICE_MASK) >> 16)
#define IO_TPM_GET_CHANNEL(channel)					(uint8)((channel & IO_TPM_GET_CHANNEL_MASK) >> 8)
#define IO_TPM_GET_INDEX(channel)					(uint8)(channel & IO_TPM_GET_INDEX_MASK)
	/* end of Macros */

#define IO_TPM_BUS_FREQ				24000000U
#define IO_TPM_MICROSEC_DIV			1000000U

#define IO_TPM_GET_CFGTYPE_MASK		0xFF000000
#define IO_TPM_GET_DEVICE_MASK		0x00FF0000
#define IO_TPM_GET_CHANNEL_MASK		0x0000FF00
#define IO_TPM_GET_INDEX_MASK		0x000000FF

#define IO_TPM_CLK_SRC_DISABLED		0
#define IO_TPM_CLK_SRC_MCGFLLPLL	1
#define IO_TPM_CLK_SRC_OSCER		2
#define IO_TPM_CLK_SRC_MCGIR		3

#define IO_TPM_CLK_DISABLED			0
#define IO_TPM_MODULE_CLOCK	    	1
#define IO_TPM_EXT_CLOCK			2

#define IO_TPM_PRESCALER1 			0
#define IO_TPM_PRESCALER2 			1
#define IO_TPM_PRESCALER4 			2
#define IO_TPM_PRESCALER8 			3
#define IO_TPM_PRESCALER16 			4
#define IO_TPM_PRESCALER32 			5
#define IO_TPM_PRESCALER64			6
#define IO_TPM_PRESCALER128 		7

#define IO_TPM_COUNT_UP 			0
#define IO_TPM_COUNT_UP_DOWN		1

#define IO_TPM_TOF_INTERRUPT_OFF	0
#define IO_TPM_TOF_INTERRUPT_ON		1

#define IO_TPM_CH_CONFIG_NOT_CONF	0
#define IO_TPM_CH_CONFIG_PWM		1
#define IO_TPM_CH_CONFIG_DCM		2

#define IO_TPM_DEVICE0				0
#define IO_TPM_DEVICE1				1
#define IO_TPM_DEVICE2				2

#define IO_TPM_CHANNEL0 			0
#define IO_TPM_CHANNEL1 			1
#define IO_TPM_CHANNEL2 			2
#define IO_TPM_CHANNEL3 			3
#define IO_TPM_CHANNEL4 			4
#define IO_TPM_CHANNEL5 			5

#define IO_TPM_CHANNEL_INDEX0 		0
#define IO_TPM_CHANNEL_INDEX1 		1
#define IO_TPM_CHANNEL_INDEX2 		2
#define IO_TPM_CHANNEL_INDEX3 		3
#define IO_TPM_CHANNEL_INDEX4 		4
#define IO_TPM_CHANNEL_INDEX5 		5
#define IO_TPM_CHANNEL_INDEX6 		6
#define IO_TPM_CHANNEL_INDEX7 		7
#define IO_TPM_CHANNEL_INDEX8 		8
#define IO_TPM_CHANNEL_INDEX9 		9
#define IO_TPM_CHANNEL_INDEX10		10
#define IO_TPM_CHANNEL_INDEX_NOT_CONF	0xFF

#define IO_TPM_INIT_ENABLE_OFF		0
#define IO_TPM_INIT_ENABLE_ON		1

#define IO_TPM_INIT_LEVEL_LOW		0
#define IO_TPM_INIT_LEVEL_HIGH		1

#define IO_PWM_TYPE_A 				TPM_CnSC_ELSB_MASK
#define IO_PWM_TYPE_B 				TPM_CnSC_ELSA_MASK

#define IO_TPM_0PERCENT_DUTYCYCLE	0x0000
#define IO_TPM_15PERCENT_DUTYCYCLE 	0x0999
#define IO_TPM_95PERCENT_DUTYCYCLE 	0x3CCC
#define IO_TPM_100PERCENT_DUTYCYCLE	0x4000

#define IO_TPM_MIN_PERIOD			IO_TPM_MIN_16BIT
#define IO_TPM_MAX_PERIOD			IO_TPM_MAX_16BIT

#define IO_TPM_MIN_16BIT			0x0000
#define IO_TPM_MAX_16BIT			0xFFFF
#define IO_TPM_0PERCENT				0
#define IO_TPM_100PERCENT			100

#define IO_TPM_DEBUG_MODE_OFF      	0
#define IO_TPM_DEBUG_MODE_ON 		3

#define IO_TPM_CH_INTERRUPT_OFF		0
#define IO_TPM_CH_INTERRUPT_ON		1

#define IO_TPM_COUNTER_START_VALUE 	0

/** end of Defines **/

/** Structure Typedefs and Nested Structures **/

typedef struct Io_Tpm_PwmChannelCnfStruct_tag Io_Tpm_PwmChannelCnfStruct;
typedef struct Io_Tpm_DcmChannelCnfStruct_tag Io_Tpm_DcmChannelCnfStruct;
typedef struct Io_Tpm_DeviceCnfStruct_tag Io_Tpm_DeviceCnfStruct;
typedef struct Io_Tpm_CnfStruct_tag Io_Tpm_CnfStruct;

/* DESCRIPTION: this structure contains the configuration elements for a PWM channel. */
struct Io_Tpm_PwmChannelCnfStruct_tag
{
	uint32 channel;
	uint8 enableOnInit;
	uint8 pwmType;
	uint8 initLevel;
	uint16 initDutycycle;
};

/* DESCRIPTION: this structure contains the configuration elements for a DCM/PIM channel. */
struct Io_Tpm_DcmChannelCnfStruct_tag
{
	uint8 channel;
};

/* DESCRIPTION: this structure contains the configuration elements for a TPM device. */
struct Io_Tpm_DeviceCnfStruct_tag
{
	TPM_Type *tpm;
	uint8 clockType;
	uint8 prescaler;
	uint8 countingMode;
	uint8 tofInterrupt;
	uint16 period;
};

/* DESCRIPTION: This structure contains the configuration elements for all the TPM devices. */
struct Io_Tpm_CnfStruct_tag
{
	uint8 noOfTpms;
	const Io_Tpm_DeviceCnfStruct *tpm_config_ptr;
	uint8 noOfPwmChannels;
	const Io_Tpm_PwmChannelCnfStruct *pwm_config_ptr;
	uint8 noOfDcmChannels;
	const Io_Tpm_DcmChannelCnfStruct *dcm_config_ptr;
};

/** end of Structure Typedefs and Nested Structures **/

/** External Global Variables and Constants **/

extern const Io_Tpm_CnfStruct *Io_Tpm_Cnf_Ptr;
extern uint16 *Io_Tpm_PwmChLastDutycycle;
extern uint8 Io_Tpm_Initialized;
extern uint8 Io_Tpm_Tpm0Used;
extern uint8 Io_Tpm_Tpm1Used;
extern uint8 Io_Tpm_Tpm2Used;

/** end of External Global Variables and Constants **/

/** External Interfaces prototypes **/

/* FUNCTION NAME: Io_Tpm_Initialization
 * DESCRIPTION: Initializes the TPM timers for PWM & DCM/PIM functionalities.
 * @*Io_Tpm_Cnf: pointer to the configuration structure for the TPM modules.
 *  -> possible values: Io_Tpm_Cnf_Ptr
 */
extern void Io_Tpm_Initialization(const Io_Tpm_CnfStruct *Io_Tpm_Cnf);

/* FUNCTION NAME: Io_Tpm_PwmEnable
 * DESCRIPTION: This function "Enables the selected PWM channel.
 * @channel: PWM channel to be enabled
 * 	-> possible values: CNF_TPM0_CHANNEL0
 * 						CNF_TPM0_CHANNEL1
 * 						CNF_TPM0_CHANNEL2
 * 						CNF_TPM0_CHANNEL3
 * 						CNF_TPM0_CHANNEL4
 * 						CNF_TPM0_CHANNEL5
 * 						CNF_TPM1_CHANNEL0
 * 						CNF_TPM1_CHANNEL1
 * 						CNF_TPM2_CHANNEL0
 * 						CNF_TPM2_CHANNEL1
 */
extern void Io_Tpm_PwmEnable(uint32 channel);

/* FUNCTION NAME: Io_Tpm_PwmChangeDutycycle
 * DESCRIPTION: Feeds the selected PWM channel a new dutycycle, starting from the next period.
 * @channel: PWM channel
 *  -> possible values: see DESCRIPTION of Io_Tpm_PwmEnable
 * @newDutycycle: new Dutycycle value for given pwm channel
 *  -> possible values: 0x0000 - 0x4000
 */
extern void Io_Tpm_PwmChangeDutycycle(uint32 channel, uint16 newDutycycle);

/* FUNCTION NAME: Io_Tpm_PwmChangePeriod
 * DESCRIPTION: Feeds the selected PWM channel a new period, starting from the next period.
 * @channel: PWM channel
 *  -> possible values: see DESCRIPTION of Io_Tpm_PwmEnable
 * @newPeriod: new Period value for given pwm channel
 *  -> possible values: 0x0000 - 0xFFFF
 */
extern void Io_Tpm_PwmChangePeriod(uint32 channel, uint16 newPeriod);

/* FUNCTION NAME: Io_Tpm_PwmOverride
 * DESCRIPTION: Feeds the selected PWM channel new dutycycle & period, starting from the current period.
 * @channel: PWM channel
 *  -> possible values: see DESCRIPTION of Io_Tpm_PwmEnable
 * @newDutycycle: new Dutycycle value for given pwm channel
 *  -> possible values: 0x0000 - 0x4000
 * @newPeriod: new Period value for given pwm channel
 *  -> possible values: 0x0000 - 0xFFFF
 */
extern void Io_Tpm_PwmOverride(uint32 channel, uint16 newDutycycle, uint16 newPeriod);

/* FUNCTION NAME: Io_Tpm_PeriodToTicks
 * DESCRIPTION: Converts the given period [us] into the value to be written in MOD register.
 * @channel: PWM channel
 *  -> possible values: see DESCRIPTION of Io_Tpm_PwmEnable
 * @usPeriod: value of Period in microseconds [us] to be transformed in timer ticks
 *  -> possible values: range given by tpm period settings (see configuration structure TABLE 1)
 */
extern uint16 Io_Tpm_PeriodToTicks(uint32 channel, uint32 usPeriod);

/* FUNCTION NAME: Io_Tpm_FrequencyToTicks
 * DESCRIPTION: Converts the given frequency [Hz] into the value to be written in MOD register.
 * @channel: PWM channel
 *  -> possible values: see DESCRIPTION of Io_Tpm_PwmEnable
 * @hzFrequency: value of Frequency in hertz [Hz] to be transformed in timer ticks
 *  -> possible values: range given by inverse of tpm period settings (see configuration structure TABLE 1)
 */
extern uint16 Io_Tpm_FrequencyToTicks(uint32 channel, uint32 hzFrequency);

/* FUNCTION NAME: Io_Tpm_Tpm0Isr
 * DESCRIPTION: Handles the interrupts generated by the TPM0 module.
 * @ void
 */
extern void Io_Tpm_Tpm0Isr(void);

/* FUNCTION NAME: Io_Tpm_Tpm1Isr
 * DESCRIPTION: Handles the interrupts generated by the TPM1 module.
 * @void
 */
extern void Io_Tpm_Tpm1Isr(void);

/* FUNCTION NAME: Io_Tpm_Tpm2Isr
 * DESCRIPTION: Handles the interrupts generated by the TPM2 module.
 * @void
 */
extern void Io_Tpm_Tpm2Isr(void);

/** end of External Interfaces prototypes **/

#endif /* IO_TPM_H */
