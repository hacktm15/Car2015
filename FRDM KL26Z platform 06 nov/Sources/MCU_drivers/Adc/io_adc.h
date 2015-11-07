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

$Log: io_adc.h $

$Author: Abos Roxana $

 ****************************************************************************/

#ifndef IO_ADC_H
#define IO_ADC_H


/** Includes **/

#include "MKL26Z4.h"
#include "Platform_Types/std_types.h"
#include "Platform_Types/powersar_addon_types.h"
#include "Platform_Types/platform_types.h"

#include "Other_functions/io_func.h"

/** end of Includes **/

/** Defines **/

#define ADC_NO_OF_CHANNELS 	5

/** end of Defines **/


typedef struct Io_Adc_config_channel_tag Io_Adc_config_channel;
typedef struct Io_Adc_config_device_tag  Io_Adc_config_device;

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

typedef struct
{
	uint16 adc_channel_value;
	uint8 valid;
}Io_Adc_channel_data;

typedef struct
{
	Io_Adc_channel_data adc_ch_data[ADC_NO_OF_CHANNELS];
	uint8 current_cnv_channel;
	uint8 conversion_ongoing;
}Io_Adc_data;

/** External Interfaces prototypes **/

/* FUNCTION NAME: Io_Adc_Initialization
 * DESCRIPTION: Initialize the configured ADC channels.
 * @
 */
extern void Io_Adc_Initialization(const Io_Adc_config_device *cnf_adc_ptr);

/* FUNCTION NAME: Io_Adc_Autoscan
 * DESCRIPTION: Initializes the ADC Autoscan functionalities.
 * OBSERVATIONS: You need to place this interface into the 10ms task in order to use the ADC functionalities.
 */
extern void Io_Adc_Autoscan(void);

/* FUNCTION NAME: Io_Adc_Isr
 * DESCRIPTION: Uses the interrupt driver in order to write the converted values into the result buffer.
 * @
 */
extern void Io_Adc_Isr(void);

/* FUNCTION NAME: Io_Adc_GetResult
 * DESCRIPTION: Gets the result of the ADC for a specific channel, the conversion result will be returned
only on request to upper layer, and unified to 15 bits.
 * @
 */
extern uint16 Io_Adc_GetResult(uint8 channel);

/* FUNCTION NAME: Io_Adc_GetResultmV
 * DESCRIPTION: This interface uses the conversion result returned by the Io_Adc_GetResult interface and converts it to mV;
 * @
 */
extern uint16 Io_Adc_GetResultmV(uint8 channel);

/* FUNCTION NAME: Io_Adc_GetValid
 * DESCRIPTION: Validates if the conversion was done correctly;
 * @
 */
extern uint8 Io_Adc_GetValid(uint8 channel);

/** end of External Interfaces prototypes **/

#endif /* IO_ADC_H */
