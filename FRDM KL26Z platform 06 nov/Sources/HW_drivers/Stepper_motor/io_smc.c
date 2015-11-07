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

$Log: io_smc.c $

$Author: Bogdan Corina $

 ****************************************************************************/

#include <stdlib.h>

#include "MCU_drivers/Pcs/io_pcs_cnf.h"
#include "MCU_drivers/Dio/io_dio.h"

#include "io_smc_cnf.h"

const Io_Smc_Cnf_Struct *smc_config;
uint8 *io_smc_dir,*last_step_array,*stop_flag,*io_smc_drive_mode,* smc_last_step;
//the stop_flag will be set if one of the connected stepper motors  is in stop mode
uint16 *io_smc_step_count,*io_smc_step_nr,*io_smc_delay_count;
uint8 io_step_var_nr;

void Io_Smc_Initialize(const Io_Smc_Cnf_Struct *smc_conf)
{
	//this function allocates memory  for all arrays needed to  move the stepper motors, depending on the number of motors
	uint8 i;

	  smc_config=smc_conf;
	  io_smc_drive_mode=malloc((smc_config->nr_of_sms) * sizeof(uint8));
	  io_smc_dir=malloc((smc_config->nr_of_sms) * sizeof(uint8));
	  io_smc_step_nr=malloc((smc_config->nr_of_sms) * sizeof(uint16));
	  io_smc_delay_count= malloc((smc_config->nr_of_sms) * sizeof(uint16));
	  io_smc_step_count=malloc((smc_config->nr_of_sms) * sizeof(uint16));
	  last_step_array=malloc((smc_config->nr_of_sms) * sizeof(uint8));
	  stop_flag= malloc((smc_config->nr_of_sms) * sizeof(uint8));
	  smc_last_step= malloc((smc_config->nr_of_sms) * sizeof(uint8));

	  for(i=0;i<smc_config->nr_of_sms;i++)
	  {
		  io_smc_drive_mode[i]=smc_config->smc_pin_ptr[i].drive_mode;
		  io_smc_dir[i]=IO_SMC_STATE_STEPPING_FORWARD;
		  io_smc_step_nr[i]=0;
		  //io_smc_delay_count gets the value of the step_time field from the configuration structure
		  //the  value of io_smc_delay_count represents the period of time in milliseconds that must pass  before a new step can be made
		  io_smc_delay_count[i]=smc_config->smc_pin_ptr[i].step_time;
		  io_smc_step_count[i]=0;
		  last_step_array[i]=0;
		  //after the initialization the stop_fags for all stepper motors are zero
		  stop_flag[i]=0;
		  smc_last_step[i] = IO_SMC_STEP_0;
	  }
}

void Io_Smc_Shutdown()
{
	uint8 i;

		for(i=0;i<smc_config->nr_of_sms;i++)
			{
               //Every stepper motor is controlled by h_bridge
			         // this function disables all h_bridges by setting their sleep_pin level low.
					Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_sleep,IO_PCS_LEVEL_LOW);
			}
}

void Io_Smc_Update(uint8 smotor_nr,uint8 direction, uint16 step_nr)
{
  uint8 i;

	for(i=0;i<smc_config->nr_of_sms;i++)
    {
         if(i==smotor_nr)
         {

           //for every Io_Smc_Update call the io_smc_step_nr is initialized with 0
        	 io_smc_step_nr[i]=0;

        	 //the stop_flag is set when  the stepper is in stop mode
        	 //if the stop_flag is 1 the last_step for the connected stepper motors will be calculated otherwise than for last_step is 0
        	 if(stop_flag[i]==1)
        	 {
             //calculate last step if stop_flag is 1 for the stepper motor which number is given as a parameter to the update function
        		 last_step_array[i]=smc_last_step[i];//(io_smc_step_nr[i]+1)%4;
        		 // last_step_array[i]=io_smc_step_nr[i];
        	 }
        	 else
        	 {
        		 //if the io_smc_step_count is 0 it means that the update function wasn't called and no steps are made
        		 //the last_step value is calculated different for a step_count lower or equal 1 than for a step_count greater than 1
        		 //the direction is also a factor on which the last_step depends
        		 //the last_step is calculated with the values from the last update ....
        		 // if the direction for the stepper is FORWARD to the last_step value will be added the step_count
             //if the direction for the stepper is BACKWARD from last_step value will be subtract the step_count
        		 //the new value for the last step is the result modulo four
        		 if(io_smc_step_count[i]<=1)
               {
            	   if( io_smc_dir[i]==IO_SMC_STATE_STEPPING_FORWARD)
            	      {
            		       last_step_array[i]=(last_step_array[i]+io_smc_step_count[i]-1)%4;
            	      }
            	      else //IO_SMC_STATE_STEPPING_BACKWARD
            	      {
            	         last_step_array[i]=(abs(last_step_array[i]-io_smc_step_count[i])-1)%4;
            	      }
               }
               else
               {
            	   //for a step count greater than 1 depending on the last direction the result will be increased or decreased with 1

            	   if( io_smc_dir[i]==IO_SMC_STATE_STEPPING_FORWARD)
            	   {
            		   //if direction is FORWARD the result of the sum between the last_step and the step_count will decreased with 1
            	     last_step_array[i]=(last_step_array[i]+io_smc_step_count[i]-1)%4;
            	   }
            	   else //IO_SMC_STATE_STEPPING_BACKWARD
            		 {
            		 	 //if direction is FORWARD the result of the difference between the last_step and the step_count will increased with 1
            		   last_step_array[i]=(abs(last_step_array[i]-io_smc_step_count[i])+1)%4;
								 }
               }
        	 }

          //tests if it is not the first update and adds 1 to the step_number with which are called the next updates
          if(io_smc_step_count[i]!=0)
          {
        	 io_smc_step_count[i]=step_nr;
          }
          else
          {
        	 //if the io_smc_step_count is 0 it means that the update interface wasn't called before  => the stepper motor hasn't made any steps
        	 //in this case the io_smc_step_count gets the value of step_nr
        	 io_smc_step_count[i]=step_nr;
          }
          //changes the  direction for the selected stepper motor
                    io_smc_dir[i]=direction;
         }
    }
}
//depending on the step parameter ...will be chosen how the four input pins will be configured so that the stepper motor make step 1,2 ,3,..4
//this driver has implemented two drive modes for the stepper motor
//the first one is the wave drive mode
//switch steps in wave drive mode
void Io_Smc_Switch_Steps_WD(uint8 step,uint8 motor_nr)
{
	switch(step)
		  {
		     case IO_SMC_STEP_0:
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		       	Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_LOW);
		     	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
  		    	Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);

  		    	smc_last_step[motor_nr]=IO_SMC_STEP_0;
		     break;

		    case IO_SMC_STEP_1:
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_LOW);
		        Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
		        Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
		        Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);

  		    	smc_last_step[motor_nr]=IO_SMC_STEP_1;
		     break;

		    case IO_SMC_STEP_2:
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		        Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
  		      Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_LOW);

  		    	smc_last_step[motor_nr]=IO_SMC_STEP_2;
		     break;

		    case IO_SMC_STEP_3:
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		        Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
		        Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_LOW);
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);

  		    	smc_last_step[motor_nr]=IO_SMC_STEP_3;
		     break;

		    default : break;
		  }
  if(io_smc_dir[motor_nr]==IO_SMC_STATE_STEPPING_FORWARD)
	    {
	      smc_last_step[motor_nr]++;

	     }
         else //IO_SMC_STATE_STEPPING_BACKWARD
         {
  	          if(smc_last_step[motor_nr]==0)
                  {
	                  smc_last_step[motor_nr]=3;
                    }
  	              else
  	              {
  	            	   smc_last_step[motor_nr]--;
  	              }

  	       }
}

//switch steps in full step drive mode
void Io_Smc_Switch_Steps_FSD(uint8 step,uint8 motor_nr)
{
	switch(step)
		  {
		     case IO_SMC_STEP_0:
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_LOW);
		       	Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_LOW);
		       	Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
		       	Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);

		       	smc_last_step[motor_nr]=IO_SMC_STEP_0;
		       	break;

		    case IO_SMC_STEP_1:
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_LOW);
		        Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_LOW);
		        Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);

		    	  smc_last_step[motor_nr]=IO_SMC_STEP_1;
		        break;

		    case IO_SMC_STEP_2:
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_LOW);
		        Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_LOW);

		    	  smc_last_step[motor_nr]=IO_SMC_STEP_2;
		        break;

		    case IO_SMC_STEP_3:
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_LOW);
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
  		      Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
  		      Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_LOW);

  		      smc_last_step[motor_nr]=IO_SMC_STEP_3;
  		      break;

   		    default : break;
		  }
	 if(io_smc_dir[motor_nr]==IO_SMC_STATE_STEPPING_FORWARD)
		    {
		      smc_last_step[motor_nr]++;

		     }
	         else //IO_SMC_STATE_STEPPING_BACKWARD
	         {
	  	          if(smc_last_step[motor_nr]==0)
	                  {
		                  smc_last_step[motor_nr]=3;
	                    }
	  	              else
	  	              {
	  	            	   smc_last_step[motor_nr]--;
	  	              }

	  	       }

}
void Io_Smc_Switch_Steps_FSD_2(uint8 step,uint8 motor_nr)
{
	switch(step)
		  {
		     case IO_SMC_STEP_0:
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		       	Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_LOW);
		       	Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_LOW);
		       	Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);

		       	smc_last_step[motor_nr]=IO_SMC_STEP_0;
		       	break;

		    case IO_SMC_STEP_1:
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_LOW);
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_LOW);
		        Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
		        Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);

		    	  smc_last_step[motor_nr]=IO_SMC_STEP_1;
		        break;

		    case IO_SMC_STEP_2:
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_LOW);
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
		        Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_LOW);

		    	  smc_last_step[motor_nr]=IO_SMC_STEP_2;
		        break;

		    case IO_SMC_STEP_3:
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
  		      Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_LOW);
  		      Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_LOW);

  		      smc_last_step[motor_nr]=IO_SMC_STEP_3;
  		      break;

   		    default : break;
		  }
	 if(io_smc_dir[motor_nr]==IO_SMC_STATE_STEPPING_FORWARD)
		    {
		      smc_last_step[motor_nr]++;

		     }
	         else //IO_SMC_STATE_STEPPING_BACKWARD
	         {
	  	          if(smc_last_step[motor_nr]==0)
	                  {
		                  smc_last_step[motor_nr]=3;
	                    }
	  	              else
	  	              {
	  	            	   smc_last_step[motor_nr]--;
	  	              }

	  	       }

}

void Io_Smc_Switch_Steps_HSD(uint8 step,uint8 motor_nr)
{
	switch(step)
  {
	case IO_SMC_STEP_0:
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_LOW);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);

		smc_last_step[motor_nr]=IO_SMC_STEP_0;
		break;
	case IO_SMC_STEP_1:
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_LOW);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_LOW);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);

		smc_last_step[motor_nr]=IO_SMC_STEP_1;
		break;
	case IO_SMC_STEP_2:
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_LOW);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);

		smc_last_step[motor_nr]=IO_SMC_STEP_2;
		break;
	case IO_SMC_STEP_3:
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_LOW);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_LOW);

		smc_last_step[motor_nr]=IO_SMC_STEP_3;
		break;
	case IO_SMC_STEP_4:
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_LOW);

		smc_last_step[motor_nr]=IO_SMC_STEP_4;
		break;
	case IO_SMC_STEP_5:
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_LOW);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_LOW);

		smc_last_step[motor_nr]=IO_SMC_STEP_5;
		break;
	case IO_SMC_STEP_6:
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_LOW);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);

		smc_last_step[motor_nr]=IO_SMC_STEP_6;
		break;

	case IO_SMC_STEP_7:
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in1,IO_PCS_LEVEL_HIGH);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in2,IO_PCS_LEVEL_LOW);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in3,IO_PCS_LEVEL_LOW);
		Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[motor_nr]).smc_in4,IO_PCS_LEVEL_HIGH);

		smc_last_step[motor_nr]=IO_SMC_STEP_7;
		break;

  }
	if(io_smc_dir[motor_nr]==IO_SMC_STATE_STEPPING_FORWARD)
			    {
			      smc_last_step[motor_nr]++;

			     }
		         else //IO_SMC_STATE_STEPPING_BACKWARD
		         {
		  	          if(smc_last_step[motor_nr]==0)
		                  {
			                  smc_last_step[motor_nr]=7;
		                    }
		  	              else
		  	              {
		  	            	   smc_last_step[motor_nr]--;
		  	              }

		  	       }

}
void Io_Smc_Step_Manager(uint8 smotor_nr)
{
  uint8 temp;
  uint8 i;
  /*** TODO BOGDAN C: not used Oct 30, 2015
   uint8 count;
   ***/

	for(i=0;i<smc_config->nr_of_sms;i++)
	   {
	    if(i==smotor_nr)
	   	{
	   	   io_smc_delay_count[i]--;

	   	   if(io_smc_delay_count[i]==0)
	   	   {//time to start the next step.
	   	   	//Reload step duration counter
	   	    io_smc_delay_count[i]= (smc_config->smc_pin_ptr[i]).step_time;

	   	    if(io_smc_step_nr[i]<io_smc_step_count[i])
	   	    {

	   	     temp = smc_last_step[i]-8*(smc_last_step[i]/8);



	          		if(io_smc_drive_mode[i] == IO_SMC_FULLSTEP_DRIVE)
	          		{
	   	         // 	Io_Smc_Switch_Steps_FSD(temp,i);
  	   	              Io_Smc_Switch_Steps_HSD(temp,i);
	          		}
	   	          	else/*IO_SMC_WAVE_DRIVE*/
	   	          	{
	   	          		Io_Smc_Switch_Steps_WD(temp,i);
	   	          	}
	          		 io_smc_step_nr[i]++;
	   	    }
	   	    else
	   	    //after all steps are made the level of the h_bridge input pins is set high
	   	    //this means h_bridge all h_bridge output pins connected to the stepper motor are set low(IDLE State)
	   	    {
	   	     if (io_smc_step_nr[i]==io_smc_step_count[i])
	   	     {
	   	    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_in1,IO_PCS_LEVEL_HIGH);
	   	    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_in2,IO_PCS_LEVEL_HIGH);
	   	    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_in3,IO_PCS_LEVEL_HIGH);
	   	    	  Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_in4,IO_PCS_LEVEL_HIGH);
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
			    		  {
			    	     //in case IC is in sleep mode, need to activate IC
			    	     Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_sleep,IO_PCS_LEVEL_HIGH);
			    	     //Send one update with 0 steps to do. This will lock the IC pins in the curent state
			    	     stop_flag[i]=1;
			    		   Io_Smc_Update(i, io_smc_dir[i],0);

								}
			    		  break;

			    	    case IO_SMC_STATE_IDLE:
			    	    {
			    	     //next step should have correct duration
			    	     io_smc_delay_count[i]= (smc_config->smc_pin_ptr[i]).step_time;
			    	     //in case IC is in sleep mode, need to activate IC
			    	     Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_sleep,IO_PCS_LEVEL_HIGH);

			    	    Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_in1,IO_PCS_LEVEL_HIGH);
			    	    Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_in2,IO_PCS_LEVEL_HIGH);
			    	    Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_in3,IO_PCS_LEVEL_HIGH);
			    	    Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_in4,IO_PCS_LEVEL_HIGH);
			    	    }
			    	      break;
			    	     case IO_SMC_STATE_SLEEP:
			    	    {
			    	     Io_Dio_SetPinLevel((smc_config->smc_pin_ptr[i]).smc_sleep,IO_PCS_LEVEL_LOW);
			    	    }
									break;

			    	     default: break;
			    	   }
			       }
          }
}

uint8 Io_Smc_Get_State(uint8 smotor_nr)
{
	uint8 state,in1,in2,in3,in4,i;
  state = IO_SMC_STATE_UNDEFINED;
	for(i=0;i<smc_config->nr_of_sms;i++)
		    {
		       if(i==smotor_nr)
		       {
		    		 in1=Io_Dio_GetPinLevel((smc_config->smc_pin_ptr[i]).smc_in1);
		    		 in2=Io_Dio_GetPinLevel((smc_config->smc_pin_ptr[i]).smc_in2);
		    		 in3=Io_Dio_GetPinLevel((smc_config->smc_pin_ptr[i]).smc_in3);
		    		 in4=Io_Dio_GetPinLevel((smc_config->smc_pin_ptr[i]).smc_in4);
		    		 if((in1==in2)&&(in2==in3)&&(in3==in4))
		    			state=IO_SMC_STATE_IDLE;

		    	  else
		    		{
		    			if( io_smc_dir[i]==IO_SMC_STATE_STEPPING_FORWARD)
		    		   state=IO_SMC_STATE_STEPPING_FORWARD;

		    	    else
		    	    {
		    	   	 if(io_smc_dir[i]== IO_SMC_STATE_STEPPING_BACKWARD)
		    	      state=IO_SMC_STATE_STEPPING_BACKWARD;

		    	      else
		    	      {
		    	      	if(Io_Dio_GetPinLevel((smc_config->smc_pin_ptr[i]).smc_sleep)==IO_PCS_LEVEL_LOW)
		    		       state=IO_SMC_STATE_SLEEP;

		    	      }
		    	    }
		    	  }

		       }
        }
	return state;
}
