/*
 * io_adc_cnf.c
 *
 *  Created on: Jul 28, 2015
 *      Author: UIDK9016
 */

#include "io_adc_cnf.h"

/* Channel configuration */
const Io_Adc_config_channel config_adc_autoscan_channels[] =
{

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
