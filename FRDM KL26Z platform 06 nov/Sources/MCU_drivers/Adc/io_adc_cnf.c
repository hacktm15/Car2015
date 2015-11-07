/****************************************************************************

COPYRIGHT (C) $Date: Jul 28, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_adc_cnf.c $

$Author: Abos Roxana $

 ****************************************************************************/

#include "io_adc_cnf.h"

/* Channel configuration */
const Io_Adc_config_channel config_adc_autoscan_channels[] =
{
		{
				3		, /* CH ID */
				IO_ADC_INPUT_CLK_ACT | IO_ADC_CNV_MODE_8BIT | IO_ADC_SAMPLE_TIME_LONG | IO_ADC_INPUT_CLOCK_ACT,	/* CFG1 */
				IO_ADC_SAMPLE_TIME_6CYCL | IO_ADC_CONV_SPEED_NORMAL   /* CFG2 */

		},
		{
				8		, /* CH ID*/
				IO_ADC_INPUT_CLK_ACT | IO_ADC_CNV_MODE_10BIT | IO_ADC_SAMPLE_TIME_LONG | IO_ADC_INPUT_CLOCK_ACT, /*CFG1*/
				IO_ADC_SAMPLE_TIME_10CYCL | IO_ADC_CONV_SPEED_NORMAL   /* CFG2*/
		},
		{
				9		, /* CH ID*/
				IO_ADC_INPUT_CLK_ACT | IO_ADC_CNV_MODE_10BIT | IO_ADC_SAMPLE_TIME_LONG | IO_ADC_INPUT_CLOCK_ACT, /*CFG1*/
				IO_ADC_SAMPLE_TIME_10CYCL | IO_ADC_CONV_SPEED_NORMAL   /* CFG2*/
		},
		{
				12		, /* CH ID*/
				IO_ADC_INPUT_CLK_ACT | IO_ADC_CNV_MODE_10BIT | IO_ADC_SAMPLE_TIME_LONG | IO_ADC_INPUT_CLOCK_ACT, /*CFG1*/
				IO_ADC_SAMPLE_TIME_10CYCL | IO_ADC_CONV_SPEED_NORMAL   /* CFG2*/
		},
		{
				13		, /* CH ID*/
				IO_ADC_INPUT_CLK_ACT | IO_ADC_CNV_MODE_10BIT | IO_ADC_SAMPLE_TIME_LONG | IO_ADC_INPUT_CLOCK_ACT, /*CFG1*/
				IO_ADC_SAMPLE_TIME_10CYCL | IO_ADC_CONV_SPEED_NORMAL   /* CFG2*/
		}
};

/* Device configuration */
const 	Io_Adc_config_device config_adc_ptr[] =
{
		{
		sizeof(config_adc_autoscan_channels)/sizeof(Io_Adc_config_channel),
		config_adc_autoscan_channels
		}
};
