/*
 * io_adc_test.c
 *
 *  Created on: Aug 7, 2015
 *      Author: UIDK9016
 */

#include "MCU_DRIVERS/ADC/io_adc_cnf.h"

#include "io_adc_test.h"

uint16 io_adc_test_results[5];
uint8 io_adc_test_valid[5];
//uint8 io_test_adc_shutdown;

void Io_Adc_Test(void)
{
	Io_Adc_Autoscan();

	// io_adc_test_results[0] = Io_Adc_GetResult(ADC_CH_ADC00);
	//io_adc_test_results[1] = Io_Adc_GetResult(ADC_CH_ADC03);
	io_adc_test_results[2] = Io_Adc_GetResult(ADC_CH_ADC08);
	// io_adc_test_results[3] = Io_Adc_GetResult(ADC_CH_ADC09);
	// io_adc_test_results[4] = Io_Adc_GetResult(ADC_CH_ADC12);

	//io_adc_test_valid[0] = Io_Adc_GetValid(ADC_CH_ADC00);
	//io_adc_test_valid[1] = Io_Adc_GetValid(ADC_CH_ADC03);
	io_adc_test_valid[2] = Io_Adc_GetValid(ADC_CH_ADC08);
	// io_adc_test_valid[3] = Io_Adc_GetValid(ADC_CH_ADC09);
	// io_adc_test_valid[4] = Io_Adc_GetValid(ADC_CH_ADC12);
}

/*void Io_Adc_TestShutDown(void)
{
	if (io_test_adc_shutdown==1 )
			{
				Io_Adc_ShutDown();
				io_test_adc_shutdown=0;
			}

}*/
