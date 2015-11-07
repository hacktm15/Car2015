/*
 * io_adc.c
 *
 *  Created on: Jul 28, 2015
 *      Author: UIDK9016
 */

#include "MCU_DRIVERS/ADC/io_adc_cnf.h"
#include "MCU_DRIVERS/DIO/io_dio.h"
#include "MCU_DRIVERS/INT/io_int_cnf.h"
#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"

#include "TEST_FUNCTIONS/io_adc_test.h"

#include "io_adc_cnf.h"

Io_Adc_data Io_Adc_Data_var;
Io_Adc_data *Io_Adc_Data;
const Io_Adc_config_device *Io_Adc_ConfigPtr;

#define ADC_CFG1_DEFAULT  (IO_ADC_NORM_POWER)
#define ADC_CFG2_DEFAULT  (IO_ADC_MUXA_SELECT | IO_ADC_ASYNC_CLK_DIS)

#define VALID       1
#define INVALID     0

void Io_Adc_Initialization(const Io_Adc_config_device  *cnf_adc_ptr)
{
	uint8 i;

	/* Copy the values from the channel configuration structure */
	Io_Adc_ConfigPtr = cnf_adc_ptr;

	/* Initialize channels values */
	Io_Adc_Data = &Io_Adc_Data_var;

	/* Current conversion channel set  */
	Io_Adc_Data->current_cnv_channel=0;

	/* Conversion ongoing set  */
	Io_Adc_Data->conversion_ongoing=0;

	/* Set buffer */
	for (i=0; i< Io_Adc_ConfigPtr->adc_number_of_channels; i++)
	{
		Io_Adc_Data->adc_ch_data[i].adc_channel_value = 0;
		Io_Adc_Data->adc_ch_data[i].valid = INVALID;
		Io_Adc_Data->current_cnv_channel++;
	}

	/* Enable the Clock Gate Control for ADC */
	SIM_SCGC6 |= SIM_SCGC6_ADC0(1);

	/* Status and control register2 contains the conversion active, hardware/software trigger select, compare function and voltage reference select of the ADC module
	 * |-------|-------|-------|-------|-------|-------|-------|
	 * | ADACT | ADTRG | ACFE  | ACFGT | ACREN | DMAEN | REFSEL|
	 * |_______|_______|_______|_______|_______|_______|_______|
	 * Voltage reference.				Possible values:
	 * 										VREFH & VREFL->IO_ADC_SC2_VOLT_REFSEL_DEFAULT,
	 * 										VALTH & VALTL->IO_ADC_SC2_VOLD_REFSEL_ALT
	 * DMA.								Possible values:
	 * 										Disable->IO_ADC_SC2_DMA_DIS,
	 * 										Enable->IO_ADC_SC2_DMA_EN
	 * Compare function range.			Possible values:
	 * 										Range function disabled. Only CV1 is compared.->IO_ADC_SC2_RANGE_DIS,
	 * 										Range function enabled. Both CV1 and CV2 are compared.->IO_ADC_SC2_RANGE_EN
	 * Comp. func. greater than. 		Possible values:
	 * 										Configures less than threshold, outside range not inclusive and inside range not inclusive; functionality based on the values placed in CV1 and CV2.->IO_ADC_SC2_COMP_FUNC_LES_THAN,
	 * 										Configures greater than or equal to threshold, outside and inside ranges inclusive; functionality based on the values placed in CV1 and CV2.->IO_ADC_SC2_COMP_FUNC_GR_THAN,
	 * Comp. func. 						Possible values:
	 * 										Compare function disabled->IO_ADC_SC2_EN_COMP_FUNC,
	 * 										Compare function enabled.->IO_ADC_SC2_DIS_COMP_FUNC
	 * Conversion trigger.				Possible values:
	 * 										Software trigger selected.When software trigger is selected, a conversion is initiated following a write to SC1A.->IO_ADC_SC2_SOFT_TRIGGER,
	 * 										Hardware trigger selected.->IO_ADC_SC2_HARD_TRIGGER
	 * Conversion active.				Possible values:
	 * 										Conversion not in progress.->IO_ADC_SC2_CONV_NOT_PROGRESS,
	 * 										Conversion in progress.->IO_ADC_SC2_CONV_IN_PROGRESS */

	/* Select software trigger */
	ADC_SC2_REG(ADC0) = IO_ADC_SC2_VOLT_REFSEL_DEFAULT | IO_ADC_SC2_DMA_DIS | IO_ADC_SC2_RANGE_DIS | IO_ADC_SC2_COMP_FUNC_LESS_THAN | IO_ADC_SC2_EN_COMP_FUNC | IO_ADC_SC2_SOFT_TRIGGER | IO_ADC_SC2_CONV_NOT_PROGRESS;

}

void Io_Adc_Autoscan(void)
{
	Io_Adc_Data -> current_cnv_channel = 0;

	Io_Int_DisableInterrupts();

	/*Read the configuration from the configuration structure of the current channel*/
	ADC_CFG2_REG(ADC0) = ADC_CFG2_DEFAULT | Io_Adc_ConfigPtr->adc_config_channel[Io_Adc_Data->current_cnv_channel].adc_channel_config2;
	ADC_CFG1_REG(ADC0) = ADC_CFG1_DEFAULT | Io_Adc_ConfigPtr->adc_config_channel[Io_Adc_Data->current_cnv_channel].adc_channel_config1;

	/*If software trigger is selected, conversion begins after SC1A is written */
	ADC_SC1_REG(ADC0,S1A) = IO_ADC_SC1_INTERRUPT_ENABLE_MASK | IO_ADC_SC1_SE_CONVERSION | Io_Adc_ConfigPtr->adc_config_channel[Io_Adc_Data->current_cnv_channel].adc_channel_ID;

	Io_Adc_Data->conversion_ongoing = 1;

	/* Re-enable interrupts */
	Io_Int_EnableInterrupts();
}

void Io_Adc_Isr(void)
{
	uint16 result;

	Io_Adc_Data->conversion_ongoing = 0;

	Io_Int_DisableInterrupts();

	/* Store the value of the last conversion  */
	result =  ADC_R_REG(ADC0,S1A);

	/* Conversion value is written in the specific adc_channel_value */
	Io_Adc_Data->adc_ch_data[Io_Adc_Data->current_cnv_channel].adc_channel_value = result;
	Io_Adc_Data->adc_ch_data[Io_Adc_Data->current_cnv_channel].valid = VALID;

	/* Increment the channel */
	Io_Adc_Data->current_cnv_channel++;

	/* Check if current channel is not the last one */
	if (Io_Adc_Data->current_cnv_channel<Io_Adc_ConfigPtr->adc_number_of_channels)
	{
		/*Read the configuration from the configuration structure of the current channel*/
		ADC_CFG2_REG(ADC0) = ADC_CFG2_DEFAULT | Io_Adc_ConfigPtr->adc_config_channel[Io_Adc_Data->current_cnv_channel].adc_channel_config2;
		ADC_CFG1_REG(ADC0) = ADC_CFG1_DEFAULT | Io_Adc_ConfigPtr->adc_config_channel[Io_Adc_Data->current_cnv_channel].adc_channel_config1;

		/* Restart the conversion for next channel */
		ADC_SC1_REG(ADC0,S1A) = IO_ADC_SC1_INTERRUPT_ENABLE_MASK | IO_ADC_SC1_SE_CONVERSION | Io_Adc_ConfigPtr->adc_config_channel[Io_Adc_Data->current_cnv_channel].adc_channel_ID;;

		/* Conversion ongoing is set */
		Io_Adc_Data->conversion_ongoing = 1;
	}

	/* Re-enable interrupts */
	Io_Int_EnableInterrupts();

}

uint16 Io_Adc_GetResult(uint8 channel)
{
	uint16 tmp_adc_cnv_value;
	uint8 tmp_channel_cfg_mode;

	tmp_channel_cfg_mode = Io_Adc_ConfigPtr->adc_config_channel[channel].adc_channel_config1 & ADC_CFG1_MODE_MASK;
	tmp_adc_cnv_value = Io_Adc_Data->adc_ch_data[channel].adc_channel_value;
	/* ADC resolution mode single-ended 8-bit conversion */
	if (tmp_channel_cfg_mode==0)
	{
		tmp_adc_cnv_value = tmp_adc_cnv_value<<7;
	}
	/* ADC resolution mode single-ended 12-bit conversion */
	else if	(tmp_channel_cfg_mode==4)
	{
		tmp_adc_cnv_value = tmp_adc_cnv_value<<3;
	}
	/* ADC resolution mode single-ended 10-bit conversion */
	else
	{
		tmp_adc_cnv_value = tmp_adc_cnv_value<<5;
	}
	return tmp_adc_cnv_value;
}

uint16 Io_Adc_GetResultmV(uint8 channel)
{
	uint16 adc_hex_result;
	uint16 adc_mv_result;

	adc_hex_result = Io_Adc_GetResult(channel);
	adc_mv_result = ((uint32)(adc_hex_result * IO_ADC_VREFH) / (1 << IO_ADC_RESULT_NR_BIT));

	return adc_mv_result;
}

uint8 Io_Adc_GetValid(uint8 channel)
{
	uint8 tmp_adc_cnv_validation;

	tmp_adc_cnv_validation=Io_Adc_Data->adc_ch_data[channel].valid;

	return tmp_adc_cnv_validation;
}
