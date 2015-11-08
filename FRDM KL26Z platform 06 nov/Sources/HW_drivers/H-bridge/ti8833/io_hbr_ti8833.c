/**************************************************************************

COPYRIGHT (C) $Date: Sept 1, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_hbr_ti8833.c $

$Author: Bogdan Corina $

 ****************************************************************************/

#include <stdlib.h>

#include "MCU_drivers/Adc/io_adc_cnf.h"
#include "MCU_drivers/Dio/io_dio.h"
#include "MCU_drivers/Int/io_int_cnf.h"
#include "MCU_drivers/Pcs/io_pcs_cnf.h"
#include "MCU_drivers/Timer/io_tim.h"
#include "MCU_drivers/Tpm/io_tpm_cnf.h"

#include "io_hbr_cnf_ti8833.h"

const Io_Hbr_Drv8833_Cnf_Struct *hbr_drv8833_config;
uint8 *hbr_drv8833_state;

void Io_Hbr_Drv8833_Initialization(const Io_Hbr_Drv8833_Cnf_Struct *ptr_cfg)
{
	uint8 i;
	uint16 temp_stby;

	hbr_drv8833_config = ptr_cfg;
	hbr_drv8833_state = malloc((hbr_drv8833_config->nr_of_drv8833_hbrs) * sizeof(hbr_drv8833_state));
	for(i = 0; i < hbr_drv8833_config->nr_of_drv8833_hbrs; i++)
	{

		temp_stby = ((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_stby);
		Io_Dio_SetPinLevel(temp_stby,IO_PCS_LEVEL_LOW);
		hbr_drv8833_state[i] = IO_HBR_DRV8833_STATE_SLEEP;
	}

}

void Io_Hbr_Drv8833_Update(uint8 direction,uint16 dutycycle,uint8 hbr_nr)
{
	uint8 i;
	for(i=0;i<hbr_drv8833_config-> nr_of_drv8833_hbrs;i++)
	{

		if(hbr_nr==i)
		{
			if((dutycycle==0x4000)&&(direction==IO_HBR_DRV8833_STATE_REVERSE))
			{
				Io_Hbr_Drv8833_Set_State(hbr_nr,IO_HBR_DRV8833_STATE_BRAKE);
			}
			if(Io_Hbr_Drv8833_Get_State(hbr_nr)==direction)
			{

				Io_Tpm_PwmChangeDutycycle((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_in1,dutycycle);
			}
			else
			{

				if(direction==IO_HBR_DRV8833_STATE_FORWARD)
				{
					Io_Dio_SetPinLevel((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_in2,IO_PCS_LEVEL_LOW);
					hbr_drv8833_state[i]=IO_HBR_DRV8833_STATE_FORWARD;
				}


				else if(direction==IO_HBR_DRV8833_STATE_REVERSE)
				{
					Io_Dio_SetPinLevel((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_in2,IO_PCS_LEVEL_HIGH);
					hbr_drv8833_state[i]=IO_HBR_DRV8833_STATE_REVERSE;

				}
				Io_Tpm_PwmChangeDutycycle((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_in1,dutycycle);
			}
			Io_Dio_SetPinLevel((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_stby,IO_PCS_LEVEL_HIGH);
		}
	}
}
void Io_Hbr_Drv8833_Set_State(uint8 hbr_nr, uint8 hbr_state)
{
	uint8 i;

	for(i=0;i<hbr_drv8833_config-> nr_of_drv8833_hbrs;i++)
	{

		if(i==hbr_nr)
		{
			switch(hbr_state)
			{
			case IO_HBR_DRV8833_STATE_SLEEP:
				Io_Dio_SetPinLevel((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_stby,IO_PCS_LEVEL_LOW);
				hbr_drv8833_state[i] = IO_HBR_DRV8833_STATE_SLEEP;
				break;
			case IO_HBR_DRV8833_STATE_FORWARD:
				Io_Dio_SetPinLevel((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_stby,IO_PCS_LEVEL_HIGH);
				Io_Dio_SetPinLevel((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_in2,IO_PCS_LEVEL_LOW);
				hbr_drv8833_state[i] = IO_HBR_DRV8833_STATE_FORWARD;
				break;
			case IO_HBR_DRV8833_STATE_REVERSE:
				Io_Dio_SetPinLevel((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_stby,IO_PCS_LEVEL_HIGH);
				Io_Dio_SetPinLevel((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_in2,IO_PCS_LEVEL_HIGH);
				hbr_drv8833_state[i]=IO_HBR_DRV8833_STATE_REVERSE;
				break;
			case IO_HBR_DRV8833_STATE_HIGHZ:
				Io_Dio_SetPinLevel((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_stby,IO_PCS_LEVEL_HIGH);
				Io_Dio_SetPinLevel((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_in2,IO_PCS_LEVEL_LOW);
				Io_Tpm_PwmChangeDutycycle((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_in1,0x0000);

				hbr_drv8833_state[i]=IO_HBR_DRV8833_STATE_HIGHZ;
				break;
			case IO_HBR_DRV8833_STATE_BRAKE:
				Io_Dio_SetPinLevel((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_stby,IO_PCS_LEVEL_HIGH);
				Io_Tpm_PwmChangeDutycycle((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_in1,0x4000);
				Io_Dio_SetPinLevel((hbr_drv8833_config->hbr_drv8833_pin_ptr[i]).hbr_in2,IO_PCS_LEVEL_HIGH);
				hbr_drv8833_state[i]=IO_HBR_DRV8833_STATE_BRAKE;

				break;
			default: break;
			}

		}
	}
}
uint8 Io_Hbr_Drv8833_Get_State(uint8 hbr_nr)
{
	int i;
	for(i=0;i<hbr_drv8833_config->nr_of_drv8833_hbrs;i++)
	{
		if(i==hbr_nr)
			return 	hbr_drv8833_state[i];
	}

}



