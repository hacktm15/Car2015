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

$Log: io_adc.c $

$Author: Abos Roxana $

 ****************************************************************************/

#include "MCU_drivers/Adc/io_adc_cnf.h"
#include "MCU_drivers/Dio/io_dio.h"
#include "MCU_drivers/Int/io_int_cnf.h"
#include "MCU_drivers/Pcs/io_pcs_cnf.h"

#include "io_adc_cnf.h"

Io_Adc_data Io_Adc_Data_var;
Io_Adc_data *Io_Adc_Data;
const Io_Adc_config_device *Io_Adc_ConfigPtr;

#define ADC_CFG1_DEFAULT  (IO_ADC_NORM_POWER)
#define ADC_CFG2_DEFAULT  (IO_ADC_MUXA_SELECT | IO_ADC_ASYNC_CLK_DIS)

#define VALID       1
#define INVALID     0

/* FUNCTION NAME: Io_Adc_Initialization
 * RETURN TYPE: void
 * PARAMETERS: const Io_Adc_config_device  *cnf_adc_ptr
 * DESCRIPTION: Initialize the configured ADC channels.
 * OBSERVATIONS: -
 */
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

/* FUNCTION NAME: Io_Adc_Autoscan
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Initializes the ADC Autoscan functionalities.
 * OBSERVATIONS: You need to place this interface into the 10ms task in order to use the ADC functionalities
 */
void Io_Adc_Autoscan(void)
{
	Io_Adc_Data -> current_cnv_channel = 0;

	Io_Int_DisableInterrupts();

	/*Read the configuration from the structure config of the current channel*/

		/* ADC Configuration Register 2 :
			 * |--------|-------|-------|--------|
			 * | MUXSEL |ADACKEN| ADHSC | ADLSTS |
			 * |________|_______|_______|________|
			 * ADC Mux Select.						Possible values:
			 * 											DEFAULT: ADxxa channels are selected -> IO_ADC_MUXA_SELECT
			 *											ADxxb channels are selected
			 * Asynchronous Clock Output Enable. 	Possible values:
			 * 											DEFAULT: Asynchronous clock output disabled; Asynchronous clock is enabled only if selected by ADICLK and a conversion is active -> IO_ADC_ASYNC_CLK_DIS
			 *											Asynchronous clock and clock output is enabled regardless of the state of the ADC.
			 * High-Speed Configuration. 			Possible values:
			 * 											Normal conversion sequence selected -> IO_ADC_CONV_SPEED_NORMAL
			 *											High-speed conversion sequence selected with 2 additional ADCK cycles to total conversion time -> IO_ADC_CONV_SPEED_HIGH
			 * Long Sample Time Select.				Possible values:
			 * 											Default longest sample time; 20 extra ADCK cycles; 24 ADCK cycles total -> IO_ADC_SAMPLE_TIME_24CYCL
			 *											12 extra ADCK cycles; 16 ADCK cycles total sample time -> IO_ADC_SAMPLE_TIME_16CYCL
			 *											6 extra ADCK cycles; 10 ADCK cycles total sample time -> IO_ADC_SAMPLE_TIME_10CYCL
			 *											2 extra ADCK cycles; 6 ADCK cycles total sample time -> IO_ADC_SAMPLE_TIME_6CYCL*/
	ADC_CFG2_REG(ADC0) = ADC_CFG2_DEFAULT | Io_Adc_ConfigPtr->adc_config_channel[Io_Adc_Data->current_cnv_channel].adc_channel_config2;

	/* ADC Configuration Register 1 :
				 * |-------|-------|--------|------|--------|
				 * | ADLPC | ADIV  | ADLSMP | MODE | ADICLK |
				 * |_______|_______|________|______|________|
				 * Low-	Power Configuration.			Possible values:
				 * 											Normal power configuration -> IO_ADC_NORM_POWER
				 *											Low-power configuration. The power is reduced at the expense of maximum clock speed.
				 * Clock Divide Select.					Possible values:
				 *											DEFAULT. The divide ratio is 1 and the clock rate is input clock -> IO_ADC_INPUT_CLOCK_ACT (IO_ADC_INPUT_CLOCK_1)
				 *											The divide ratio is 2 and the clock rate is (input clock)/2 -> IO_ADC_INPUT_CLOCK_2
				 *											The divide ratio is 4 and the clock rate is (input clock)/4 -> IO_ADC_INPUT_CLOCK_4
				 *											The divide ratio is 8 and the clock rate is (input clock)/8 -> IO_ADC_INPUT_CLOCK_8
				 * Sample Time Configuration.			Possible values:
				 * 											Short sample time -> IO_ADC_SAMPLE_TIME_SHORT
				 * 											Long sample time -> IO_ADC_SAMPLE_TIME_LONG
				 * Selects the ADC resolution mode.		Possible values:
				 * 											When DIFF=0:It is single-ended 8-bit conversion; when DIFF=1, it is differential 9-bit conversion with 2's complement output -> IO_ADC_CNV_MODE_8BIT
				 *											When DIFF=0:It is single-ended 12-bit conversion ; when DIFF=1, it is differential 13-bit conversion with 2's complement output -> IO_ADC_CNV_MODE_12BIT
				 *											When DIFF=0:It is single-ended 10-bit conversion. ; when DIFF=1, it is differential 11-bit conversion with 2's complement output -> IO_ADC_CNV_MODE_10BIT
				 * Input Clock Select.					Possible values:
				 * 											DEFAULT. Bus clock -> IO_ADC_INPUT_CLK_ACT (IO_ADC_INPUT_CLK_BUS)
				 *											Alternate clock 2 (ALTCLK2) -> IO_ADC_INPUT_CLK_ALT2
				 *											Alternate clock (ALTCLK) -> IO_ADC_INPUT_CLK_ALT									*/
	ADC_CFG1_REG(ADC0) = ADC_CFG1_DEFAULT | Io_Adc_ConfigPtr->adc_config_channel[Io_Adc_Data->current_cnv_channel].adc_channel_config1;

	/*If software trigger is selected, conversion begins after SC1A is written */
		/* Status and control register1 :
			 * |------|------|------|------|
			 * | COCO | AIEN | DIFF | ADCH |
			 * |______|______|______|______|
			 * Conversion Complete Flag 							Read_Only values:
			 * 															0 Conversion is not completed.
			 *															1 Conversion is completed.
			 * Interrupt Enable.									Possible values:
			 * 															Conversion complete interrupt is disabled -> IO_ADC_SC1_INTERRUPT_DISABLE_MASK
			 *															Conversion complete interrupt is enabled -> IO_ADC_SC1_INTERRUPT_ENABLE_MASK
			 * Differential Mode Enable.							Possible values:
			 * 															Single-ended conversions and input channels are selected -> IO_ADC_SC1_SE_CONVERSION
			 *															Differential conversions and input channels are selected -> IO_ADC_SC1_DIFF_CONVERSION
			 * Input channel select.								Possible values:
			 * 															Selects one of the input channels. The input channel decode depends on the value of DIFF -> IO_ADC_SC1_INPUT_CHANNEL(ch)   */
	ADC_SC1_REG(ADC0,S1A) = IO_ADC_SC1_INTERRUPT_ENABLE_MASK | IO_ADC_SC1_SE_CONVERSION | Io_Adc_ConfigPtr->adc_config_channel[Io_Adc_Data->current_cnv_channel].adc_channel_ID;

	Io_Adc_Data->conversion_ongoing = 1;

	/* Re-enable interrupts */
	Io_Int_EnableInterrupts();
}

/* FUNCTION NAME: Io_Adc_Isr
 * RETURN TYPE: void
 * PARAMETERS: void
 * DESCRIPTION: Uses the interrupt driver in order to write the converted values into the result buffer
 * OBSERVATIONS: -
 */
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

/* FUNCTION NAME: Io_Adc_GetResult
 * RETURN TYPE: uint16
 * PARAMETERS: uint8 channel
 * DESCRIPTION: Gets the result of the ADC for a specific channel, the conversion result will be returned
only on request to upper layer, and unified to 15 bits ;
 * OBSERVATIONS: -
 */
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

/* FUNCTION NAME: Io_Adc_GetResultmV
 * RETURN TYPE: uint16
 * PARAMETERS: uint8 channel
 * DESCRIPTION: This interface uses the conversion result returned by the Io_Adc_GetResult interface and converts it to mV;
 * OBSERVATIONS: -
 */
uint16 Io_Adc_GetResultmV(uint8 channel)
{
	uint16 adc_hex_result;
	uint16 adc_mv_result;

	adc_hex_result = Io_Adc_GetResult(channel);
	adc_mv_result = ((uint32)(adc_hex_result * IO_ADC_VREFH) / (1 << IO_ADC_RESULT_NR_BIT));

	return adc_mv_result;
}

/* FUNCTION NAME: Io_Adc_GetValid
 * RETURN TYPE: uint8
 * PARAMETERS: uint8 channel
 * DESCRIPTION: Validates if the conversion was done correctly;
 * OBSERVATIONS: -
 */
uint8 Io_Adc_GetValid(uint8 channel)
{
	uint8 tmp_adc_cnv_validation;

	tmp_adc_cnv_validation=Io_Adc_Data->adc_ch_data[channel].valid;

	return tmp_adc_cnv_validation;
}



