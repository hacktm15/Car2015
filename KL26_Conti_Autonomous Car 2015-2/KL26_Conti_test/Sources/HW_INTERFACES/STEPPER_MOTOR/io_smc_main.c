
#include <stdlib.h>

#include "MCU_DRIVERS/ADC/io_adc_cnf.h"
#include "MCU_DRIVERS/DIO/io_dio.h"
#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"
#include "MCU_DRIVERS/TIMER/io_tim.h"
#include "MCU_DRIVERS/TPM/io_tpm_cnf.h"

#include "io_smc_cnf.h"

const Io_Smc_Cnf_Struct *smc_config;
uint8 *io_smc_dir,*io_smc_delay_count,*last_step_array,*stop_flag;
//the stop_flag will be set if one of the connected stepper motors  is in stop mode
uint16 *io_smc_step_count,*io_smc_step_nr;

void Io_Smc_Initialize( Io_Smc_Cnf_Struct *smc_conf)
{
	uint8 i;
	smc_config=smc_conf;
	io_smc_dir=malloc((smc_config->nr_of_sms) * sizeof(uint8));
	io_smc_step_nr=malloc((smc_config->nr_of_sms) * sizeof(uint16));
	io_smc_delay_count= malloc((smc_config->nr_of_sms) * sizeof(uint8));
	io_smc_step_count=malloc((smc_config->nr_of_sms) * sizeof(uint16));
	last_step_array=malloc((smc_config->nr_of_sms) * sizeof(uint8));
	stop_flag= malloc((smc_config->nr_of_sms) * sizeof(uint8));

	for(i=0;i<smc_config->nr_of_sms;i++)
	{
		io_smc_dir[i]=smc_config->smc_pin_ptr[i].drive_mode;
		io_smc_step_nr[i]=0;
		io_smc_delay_count[i]=smc_config->smc_pin_ptr[i].step_time;
		io_smc_step_count[i]=0;
		last_step_array[i]=0;
		stop_flag[i]=0;
	}

}

void Io_Smc_Shutdown()
{
	uint8 i;
	for(i=0;i<smc_config->nr_of_sms;i++)
	{

		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_sleep,IO_PCS_LEVEL_LOW);
	}
}

void Io_Smc_Update(uint8 smotor_nr,uint8 direction, uint16 step_nr)
{

	uint8 i,j,var;
	for(i=0;i<smc_config->nr_of_sms;i++)
	{
		if(i==smotor_nr)
		{

			io_smc_step_nr[i]=0;
			io_smc_dir[i]=direction;
			if(stop_flag[i]==1)
			{
				last_step_array[i]=(io_smc_step_nr[i]+1)%4;
			}
			else
			{

				last_step_array[i]=(last_step_array[i]+io_smc_step_count[i])%4;
			}

			io_smc_step_count[i]=step_nr;

		}
	}

}
void Io_Smc_Switch_Steps(uint8 step,uint8 motor_nr)
{
	switch(step)
	{
	case 0:

		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_LOW);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);
		break;
	case 1:
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_LOW);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);
		break;
	case 2:
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_LOW);
		break;
	case 3:
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_LOW);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);
		break;
	default : break;
	}
}

void Io_Smc_Step_Counter(uint8 smotor_nr)
{
	uint8  temp,count,i,var=1;
	for(i=0;i<smc_config->nr_of_sms;i++)
	{
		if(i==smotor_nr)
		{
			io_smc_delay_count[i]--;
			if(io_smc_delay_count[i]==0)
			{

				io_smc_delay_count[i]= (smc_config->smc_pin_ptr[i]).step_time;
				if(io_smc_dir[i]==IO_SMC_STATE_STEPPING_FORWARD)
				{
					if(io_smc_step_nr[i]<io_smc_step_count[i])
					{

						temp=(last_step_array[i]+io_smc_step_nr[i])%4;
						io_smc_step_nr[i]++;

						Io_Smc_Switch_Steps(temp,i);
					}
				}

				else if(io_smc_dir[i]==IO_SMC_STATE_STEPPING_BACKWARD)
				{
					if(io_smc_step_nr[i]<io_smc_step_count[i])
					{

						temp=(3-((last_step_array[i]+io_smc_step_nr[i]+1)%4));
						io_smc_step_nr[i]++;


						Io_Smc_Switch_Steps(temp,i);

					}
				}
			}


		}

	}

}
void Io_Smc_Set_State(uint8 smotor_nr,uint8 state)
{
	uint8 i;
	for(i=0;i<smc_config->nr_of_sms;i++)
	{
		if(i==smotor_nr)
		{
			switch(state)
			{

			case IO_SMC_STATE_STOP:
				Io_Smc_Update(i, io_smc_dir[i],0);
				stop_flag[i]=1;
				break;
			case IO_SMC_STATE_IDLE :
				Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_sleep,IO_PCS_LEVEL_HIGH);
				Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_in1,IO_PCS_LEVEL_LOW);
				Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_in2,IO_PCS_LEVEL_LOW);
				Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_in3,IO_PCS_LEVEL_LOW);
				Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_in4,IO_PCS_LEVEL_LOW);
				break;
			case IO_SMC_STATE_SLEEP :
				Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_sleep,IO_PCS_LEVEL_LOW);
				break;
			default: break;
			}
		}
	}
}

uint8 Io_Smc_Get_State(uint8 smotor_nr)
{
	uint8 state,in1,in2,in3,in4,i;

	for(i=0;i<smc_config->nr_of_sms;i++)
	{
		if(i==smotor_nr)
		{
			in1=Io_Dio_GetPinLevel((smc_config->smc_pin_ptr[i]).smc_in1);
			in2=Io_Dio_GetPinLevel((smc_config->smc_pin_ptr[i]).smc_in2);
			in3=Io_Dio_GetPinLevel((smc_config->smc_pin_ptr[i]).smc_in3);
			in4=Io_Dio_GetPinLevel((smc_config->smc_pin_ptr[i]).smc_in4);
			if( io_smc_dir[i]==IO_SMC_STATE_STEPPING_FORWARD)
			{
				state=IO_SMC_STATE_STEPPING_FORWARD;
			}
			else if(io_smc_dir[i]== IO_SMC_STATE_STEPPING_BACKWARD)
			{
				state=IO_SMC_STATE_STEPPING_BACKWARD;
			}
			else if(Io_Dio_GetPinLevel((smc_config->smc_pin_ptr[i]).smc_sleep)==IO_PCS_LEVEL_LOW)
			{

				state=IO_SMC_STATE_SLEEP;

			}
			else if((in1==IO_PCS_LEVEL_LOW)&&
					(in2==IO_PCS_LEVEL_LOW)&&
					(in3==IO_PCS_LEVEL_LOW)&&
					(in4==IO_PCS_LEVEL_LOW))
			{
				state=IO_SMC_STATE_IDLE;

			}


		}
	}
}
