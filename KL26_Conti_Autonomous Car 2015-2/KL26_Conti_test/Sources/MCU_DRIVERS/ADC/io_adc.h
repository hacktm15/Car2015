/*
 * io_adc.h
 *
 *  Created on: Jul 28, 2015
 *      Author: UIDK9016
 */

#ifndef IO_ADC_H
#define IO_ADC_H


#include "MKL26Z4.h"
#include "PLATFORM_TYPES/std_types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "PLATFORM_TYPES/platform_types.h"

typedef struct Io_Adc_config_channel_tag Io_Adc_config_channel;
typedef struct Io_Adc_config_device_tag  Io_Adc_config_device;

#define ADC_NO_OF_CHANNELS 	5


struct Io_Adc_config_channel_tag
{
	uint8 adc_channel_ID;
	uint8 adc_channel_config1;
	uint8 adc_channel_config2;
};

struct Io_Adc_config_device_tag
{
	uint8 adc_number_of_channels; /*number of active channels*/
	const Io_Adc_config_channel *adc_config_channel; /*channel configuration pointer*/
};

typedef struct{
	uint16 adc_channel_value;
	uint8 valid;
}Io_Adc_channel_data;

typedef struct{
	Io_Adc_channel_data adc_ch_data[ADC_NO_OF_CHANNELS];
	uint8 current_cnv_channel;
	uint8 conversion_ongoing;
}Io_Adc_data;

extern void Io_Adc_Initialization(const Io_Adc_config_device *cnf_adc_ptr );
extern void Io_Adc_Autoscan(void);
extern void Io_Adc_Isr(void);
extern uint16 Io_Adc_GetResult(uint8 channel);
extern uint16 Io_Adc_GetResultmV(uint8 channel);
extern uint8 Io_Adc_GetValid(uint8 channel);
//extern void Io_Adc_ShutDown(void);

#endif /* SOURCES_IO_ADC_H_ */
