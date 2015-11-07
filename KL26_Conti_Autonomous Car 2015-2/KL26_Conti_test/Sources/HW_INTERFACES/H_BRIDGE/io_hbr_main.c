#include "MCU_DRIVERS/ADC/io_adc_cnf.h"
#include "MCU_DRIVERS/DIO/io_dio.h"
#include "MCU_DRIVERS/INT/io_int_cnf.h"
#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"
#include "MCU_DRIVERS/TIMER/io_tim.h"
#include "MCU_DRIVERS/TPM/io_tpm_cnf.h"

#include "io_hbr_cnf.h"

/**<  pointer to H-bridge configuration structure */
const Io_Hbr_Cnf_Struct *hbr_config;

void Io_Hbr_Initialization(const Io_Hbr_Cnf_Struct*ptr_cfg)
{

	uint8 i;
	uint16 temp_stby;

	hbr_config=ptr_cfg;

	for(i=0;i<hbr_config->nr_of_hbrs;i++)
	{

		temp_stby=((hbr_config->hbr_pin_ptr[i]).hbr_stby);
		Io_Dio_SetPinLevel(temp_stby,IO_PCS_LEVEL_LOW);

	}

}

void Io_Hbr_Standby(uint8 hbr_nr)
{
	uint8 i;
	for(i=0;i<hbr_config->nr_of_hbrs;i++)
	{
		if(hbr_nr==i)
		{
			Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_stby,IO_PCS_LEVEL_LOW);
		}
	}

}

void Io_Hbr_Shutdown()
{
	uint8 i;
	for(i=0;i<hbr_config->nr_of_hbrs;i++)
	{
		Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in1,IO_PCS_LEVEL_LOW);
		Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in2,IO_PCS_LEVEL_LOW);
		Io_Tpm_PwmChangeDutycycle((hbr_config->hbr_pin_ptr[i]).hbr_pwm,0x0000);
		Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_stby,IO_PCS_LEVEL_HIGH);
	}
}

void Io_Hbr_Set_State(uint8 hbr_nr, uint8 hbr_state)
{uint8 i;
uint16 temp;
for(i=0;i<hbr_config->nr_of_hbrs;i++)
{

	if(i==hbr_nr)
	{
		switch(hbr_state)
		{
		case HBR_STATE_SHORTBRAKE:
			Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_stby,IO_PCS_LEVEL_HIGH);
			Io_Tpm_PwmChangeDutycycle((hbr_config->hbr_pin_ptr[i]).hbr_pwm,0x0000);
			break;
		case HBR_STATE_FORWARD:
			Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_stby,IO_PCS_LEVEL_HIGH);
			Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in1,IO_PCS_LEVEL_LOW);
			Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in2,IO_PCS_LEVEL_HIGH);
			break;
		case HBR_STATE_BACKWARD:
			Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_stby,IO_PCS_LEVEL_HIGH);

			Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in1,IO_PCS_LEVEL_HIGH);
			Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in2,IO_PCS_LEVEL_LOW);

			break;
		case HBR_STATE_STOP:
			Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_stby,IO_PCS_LEVEL_HIGH);
			Io_Tpm_PwmChangeDutycycle((hbr_config->hbr_pin_ptr[i]).hbr_pwm,0x4000);
			Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in1,IO_PCS_LEVEL_LOW);
			Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in2,IO_PCS_LEVEL_LOW);

			break;
		case HBR_STATE_STANDBY:

			Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_stby,IO_PCS_LEVEL_LOW);

			break;
		default: break;
		}

	}
}
}

uint8 Io_Hbr_Get_State(uint8 hbr_nr)
{
	uint8 temp_in1=0, temp_in2=0,temp_stby=0;
	uint8 hbr_state, i;
	for(i=0;i<hbr_config->nr_of_hbrs;i++)
	{
		if(i==hbr_nr)
		{
			temp_in1=Io_Dio_GetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in1);
			temp_in2=Io_Dio_GetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in2);
			temp_stby=Io_Dio_GetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_stby);
			if(temp_stby==IO_PCS_LEVEL_LOW)
			{
				hbr_state=HBR_STATE_STANDBY;
			}
			else
			{
				if((hbr_config->hbr_pin_ptr[i]).hbr_pwm>0)
				{
					if((temp_in1==IO_PCS_LEVEL_LOW)&&( temp_in2==IO_PCS_LEVEL_LOW))
					{
						hbr_state=HBR_STATE_STOP;
					}
					else if((temp_in1==IO_PCS_LEVEL_HIGH)&&( temp_in2==IO_PCS_LEVEL_LOW))
					{
						hbr_state=HBR_STATE_BACKWARD;
					}
					else if((temp_in1==IO_PCS_LEVEL_LOW)&&( temp_in2==IO_PCS_LEVEL_HIGH))
					{
						hbr_state=HBR_STATE_FORWARD;
					}
				}
				else
				{
					hbr_state=HBR_STATE_SHORTBRAKE;
				}
				if((temp_in1==IO_PCS_LEVEL_HIGH)&&(Io_Dio_GetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in2)==IO_PCS_LEVEL_HIGH))
				{
					hbr_state=HBR_STATE_SHORTBRAKE;
				}
			}
		}
	}

	return hbr_state;

}

void Io_Hbr_Update(uint8 direction,uint16 dutycycle,uint8 motor_nr)
{
	uint8 i;
	uint16 temp_ducy=IO_HBR_PWM_DuCy_TO_HEX(dutycycle);
	for(i=0;i<hbr_config->nr_of_hbrs;i++)
	{

		if(motor_nr==i)
		{
			if(Io_Hbr_Get_State(motor_nr)==direction)
			{

				Io_Tpm_PwmChangeDutycycle((hbr_config->hbr_pin_ptr[i]).hbr_pwm,temp_ducy);
			}
			else
			{

				if(direction==HBR_STATE_FORWARD)
				{
					Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in1,IO_PCS_LEVEL_LOW);
					Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in2,IO_PCS_LEVEL_HIGH);
				}
				else if(direction==HBR_STATE_BACKWARD)
				{
					Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in1,IO_PCS_LEVEL_HIGH);
					Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_in2,IO_PCS_LEVEL_LOW);
				}
				Io_Tpm_PwmChangeDutycycle((hbr_config->hbr_pin_ptr[i]).hbr_pwm,temp_ducy);
			}
			Io_Dio_SetPinLevel((hbr_config->hbr_pin_ptr[i]).hbr_stby,IO_PCS_LEVEL_HIGH);
		}
	}
}

