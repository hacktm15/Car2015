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

$Log: io_adc_cnf.h $

$Author: Abos Roxana $

 ****************************************************************************/

#ifndef IO_ADC_CNF_H
#define IO_ADC_CNF_H


#include "io_adc.h"

/** Defines **/

#define ADC_CH_ADC03						0
#define ADC_CH_ADC08						1
#define ADC_CH_ADC09						2
#define ADC_CH_ADC12						3
#define ADC_CH_ADC13						4

#define IO_ADC_VREFH						3300
#define IO_ADC_RESULT_NR_BIT				15

/*ADC Reg*/

/*CFG1 Bit Fields*/
#define IO_ADC_INPUT_CLK_BUS				0<<0
#define IO_ADC_INPUT_CLK_ALT2				1<<0
#define IO_ADC_INPUT_CLK_ALT				2<<0

#define IO_ADC_INPUT_CLK_ACT				IO_ADC_INPUT_CLK_BUS

#define IO_ADC_CNV_MODE_8BIT				0<<2
#define IO_ADC_CNV_MODE_12BIT				1<<2
#define IO_ADC_CNV_MODE_10BIT				2<<2

#define IO_ADC_SAMPLE_TIME_SHORT			0<<4
#define IO_ADC_SAMPLE_TIME_LONG				1<<4

#define IO_ADC_INPUT_CLOCK_1				0<<5
#define IO_ADC_INPUT_CLOCK_2				1<<5
#define IO_ADC_INPUT_CLOCK_4				2<<5
#define IO_ADC_INPUT_CLOCK_8				3<<5

#define IO_ADC_INPUT_CLOCK_ACT              IO_ADC_INPUT_CLOCK_1

#define IO_ADC_NORM_POWER					0<<7

/*CFG2 Bit Fields */
#define IO_ADC_SAMPLE_TIME_24CYCL			0<<0
#define IO_ADC_SAMPLE_TIME_16CYCL			1<<0
#define IO_ADC_SAMPLE_TIME_10CYCL			2<<0
#define IO_ADC_SAMPLE_TIME_6CYCL			3<<0

#define IO_ADC_CONV_SPEED_NORMAL			0<<2
#define IO_ADC_CONV_SPEED_HOGH				1<<2

#define IO_ADC_ASYNC_CLK_DIS				0<<3

#define IO_ADC_MUXA_SELECT					0<<4

/*SC1 Bit Fields */
#define S1A									0
#define S1B									1

#define IO_ADC_SC1_INPUT_CHANNEL(ch)		(ch | 0x1F)

#define IO_ADC_SC1_SE_CONVERSION			0<<5
#define IO_ADC_SC1_DIFF_CONVERSION			1<<5

#define IO_ADC_SC1_INTERRUPT_DISABLE_MASK	0<<6
#define IO_ADC_SC1_INTERRUPT_ENABLE_MASK	1<<6

/*SC2 Bit Fields */
#define IO_ADC_SC2_VOLT_REFSEL_DEFAULT		0<<0
#define IO_ADC_SC2_VOLD_REFSEL_ALT			1<<0

#define IO_ADC_SC2_DMA_DIS					0<<2
#define IO_ADC_SC2_DMA_EN					1<<2

#define IO_ADC_SC2_RANGE_DIS				0<<3
#define IO_ADC_SC2_RANGE_EN					1<<3

#define IO_ADC_SC2_COMP_FUNC_LESS_THAN		0<<4
#define IO_ADC_SC2_COMP_FUNC_GR_THAN		1<<4

#define IO_ADC_SC2_EN_COMP_FUNC				0<<5
#define IO_ADC_SC2_DIS_COMP_FUNC			1<<5

#define IO_ADC_SC2_SOFT_TRIGGER				0<<6
#define IO_ADC_SC2_HARD_TRIGGER				1<<6

#define IO_ADC_SC2_CONV_NOT_PROGRESS		0<<7
#define IO_ADC_SC2_CONV_IN_PROGRESS			1<<7

/** end of Defines **/

extern const Io_Adc_config_device config_adc_ptr[]; /*  */

#endif /* IO_ADC_CNF_H */
