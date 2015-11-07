


#include "PLATFORM_TYPES/Std_Types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "MCU_DRIVERS/ASY/io_bluetooth.h"
#include "MCU_DRIVERS/ASY/io_asy.h"
#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"
#include "MCU_DRIVERS/DIO/io_dio.h"
#include "APPLICATION\ALGO\CAR_MOVEMENT\app_robo_car_movement.h"
#include "APPLICATION\ALGO\PATH_PLANNER\app_path_planner.h"
#include "HW_INTERFACES/SENSORS/sensors.h"



/*#define GREEN 2
#define RED 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define YELLOW 7
#define WHITE 8
#define ERASE 9*/


/*#define IO_PCS_P0E_31 IO_PCS_P0E_31
#define IO_PCS_P0D_05 IO_PCS_P0D_05
#define IO_PCS_P0E_29 IO_PCS_P0E_29*/
int state=SLEEP_CAR;
int dutycycle=0;
int wait=0;
int delaysend=0;
char sensor;

#define delay_send 10

char mask(char mod,uint8 value)
{
	if(mod=='F')
	{
		sensor|=0x20;
		sensor|=value;
	}
	if(mod=='B')
	{
		sensor|=0x40;
		sensor|=value;
	}
	if(mod=='L')
	{
		sensor|=0x60;
		sensor|=value;
	}
	if(mod=='R')
	{
		sensor|=0x80;
		sensor|=value;
	}

	if(mod=='D')
	{
		sensor|=0xC0;
		sensor|=value;
	}
	return sensor;
}


void Io_Bluetooth_State()
{

	switch(state)
	{

	/* Wait for 2,5 seconds for the system to start up*/
	case SLEEP_CAR:
		if(wait<50)
			wait++;
		if(wait==50)
		{
			wait=0;
			state=WAIT;
		}
		break;
	case RECEIVE:
		if(Algo_Robo_Pp_CarState==ALGO_ROBO_PP_CAR_STATE_CAR_PARKED)
			state=WAIT;
		/*if(delaysend%delay_send!=0){
			delaysend++;
		}else {
			switch(delaysend){
			case 0*delay_send:
			UART1_sendchar('F');
			break;
			case 1*delay_send:
			if(Sens_sensorFrontDistanceCm<1)
				Sens_sensorFrontDistanceCm=1;
			UART1_sendchar(Sens_sensorFrontDistanceCm);
			break;
			case 2*delay_send:
			UART1_sendchar('R');
			break;
			case 3*delay_send:
			if(Sens_sensorRightDistanceCm<1)
				Sens_sensorRightDistanceCm=1;
			UART1_sendchar(Sens_sensorRightDistanceCm);
			break;
			case 4*delay_send:
			UART1_sendchar('L');
			break;
			case 5*delay_send:
			if(Sens_sensorLeftDistanceCm<1)
				Sens_sensorLeftDistanceCm=1;
			UART1_sendchar(Sens_sensorLeftDistanceCm);
			break;
			case 6*delay_send:
			UART1_sendchar('B');
			break;
			case 7*delay_send:
			if(Sens_sensorRearDistanceCm<1)
				Sens_sensorRearDistanceCm=1;
			UART1_sendchar(Sens_sensorRearDistanceCm);
			break;
			case 8*delay_send:
			UART1_sendchar('D');
			break;
			case 9*delay_send:
			UART1_sendchar(dutycycle);
			break;
			default:
				UART1_sendchar('Z');
				delaysend=-1;
			}
			delaysend++;

		}*/
		if(delaysend==0)
		{
			sensor=mask('F',Sens_sensorFrontDistanceCm);
			UART1_sendchar(sensor);
			sensor=0;
		}
		if(delaysend==1)
		{
			sensor=mask('B',Sens_sensorRearDistanceCm);
			UART1_sendchar(sensor);

		}
		if(delaysend==2)
		{
			sensor=mask('L',Sens_sensorLeftDistanceCm);
			UART1_sendchar(sensor);
			sensor=0;
		}
		if(delaysend==3)
		{
			sensor=mask('R',Sens_sensorRightDistanceCm);
			UART1_sendchar(sensor);
			sensor=0;
		}
		if(delaysend==4)
		{
			sensor=mask('D',dutycycle/10);
			UART1_sendchar(sensor);
			sensor=0;
		}
		delaysend++;
		if(delaysend==5)
			delaysend=0;


		switch(reception[0])
		{
		case '8':
			//go forward
			state=FW;
			break;
		case '2':
			//go backward
			state=BW;
			break;
		case '4':
			state=LEFT;
			break;
		case '6':
			state=RIGHT;
			break;
		case '5':
			state=WAIT;
			break;
		case '9':
			state=PARK;
			break;
		case '+':
			state=PLUS;
			break;
		case '-':
			state=MINUS;
			break;

		}
		reception[0]='0';
		break;
		case WAIT:
			Io_Dio_SetPinLevel(SET_LED_GREEN, 0);
			Io_Dio_SetPinLevel(SET_LED_BLUE, 1);
			Io_Dio_SetPinLevel(SET_LED_RED, 0);
			Algo_Robo_Cm_StopCar();
			Algo_Robo_Pp_InitializePathPlanner();
			dutycycle=0;
			state=RECEIVE;
			break;

		case FW:
			if(Sens_sensorFrontDistanceCm>13)
			{
				Io_Dio_SetPinLevel(SET_LED_GREEN, 0);
				Io_Dio_SetPinLevel(SET_LED_BLUE, 1);
				Io_Dio_SetPinLevel(SET_LED_RED, 1);
				dutycycle=50;
				Algo_Robo_Cm_MoveCarForward(dutycycle);

			}
			else
			{
				Io_Dio_SetPinLevel(SET_LED_GREEN, 1);
				Io_Dio_SetPinLevel(SET_LED_BLUE, 1);
				Io_Dio_SetPinLevel(SET_LED_RED, 0);
				Algo_Robo_Cm_StopCar();
			}
			state=RECEIVE;
			break;

		case BW:
			if(Sens_sensorRearDistanceCm>13)
			{
				Io_Dio_SetPinLevel(SET_LED_GREEN, 0);
				Io_Dio_SetPinLevel(SET_LED_BLUE, 1);
				Io_Dio_SetPinLevel(SET_LED_RED, 1);
				dutycycle=50;
				Algo_Robo_Cm_MoveCarBackward(dutycycle);
			}
			else
			{
				Io_Dio_SetPinLevel(SET_LED_GREEN, 1);
				Io_Dio_SetPinLevel(SET_LED_BLUE, 1);
				Io_Dio_SetPinLevel(SET_LED_RED, 0);
				Algo_Robo_Cm_StopCar();
			}
			state=RECEIVE;
			break;

		case PARK:
			Io_Dio_SetPinLevel(SET_LED_GREEN, 1);
			Io_Dio_SetPinLevel(SET_LED_BLUE, 0);
			Io_Dio_SetPinLevel(SET_LED_RED, 1);
			Algo_Robo_Pp_StartParallelParking();
			dutycycle=0;
			state=RECEIVE;
			break;

		case OBSTACLE:
			Io_Dio_SetPinLevel(SET_LED_GREEN, 1);
			Io_Dio_SetPinLevel(SET_LED_BLUE, 0);
			Io_Dio_SetPinLevel(SET_LED_RED, 0);
			state=RECEIVE;
			dutycycle=0;
			break;

		case LEFT:
			Io_Dio_SetPinLevel(SET_LED_GREEN, 0);
			Io_Dio_SetPinLevel(SET_LED_BLUE, 0);
			Io_Dio_SetPinLevel(SET_LED_RED, 1);
			dutycycle=50;
			Algo_Robo_Cm_RotateCarLeft(dutycycle);
			state=RECEIVE;
			break;

		case RIGHT:
			Io_Dio_SetPinLevel(SET_LED_GREEN, 0);
			Io_Dio_SetPinLevel(SET_LED_BLUE, 0);
			Io_Dio_SetPinLevel(SET_LED_RED, 1);
			dutycycle=50;
			Algo_Robo_Cm_RotateCarRight(dutycycle);
			state=RECEIVE;
			break;

		case PLUS:
			dutycycle+=10;
			if(dutycycle>=70)
				dutycycle=70;
			Io_Dio_SetPinLevel(SET_LED_GREEN, 1);
			Io_Dio_SetPinLevel(SET_LED_BLUE, 0);
			Io_Dio_SetPinLevel(SET_LED_RED, 0);
			state=RECEIVE;
			if(dutycycle>0)
				Algo_Robo_Cm_MoveCarForward(dutycycle);
			else if(dutycycle==0)
			{
				Algo_Robo_Cm_StopCar();
				state=WAIT;
			}
			else if(dutycycle<0)
				Algo_Robo_Cm_MoveCarBackward(-dutycycle);

			break;

		case MINUS:
			dutycycle-=10;
			if(dutycycle<=-70)
				dutycycle=-70;
			Io_Dio_SetPinLevel(SET_LED_GREEN, 1);
			Io_Dio_SetPinLevel(SET_LED_BLUE, 0);
			Io_Dio_SetPinLevel(SET_LED_RED, 0);
			state=RECEIVE;

			if(dutycycle>0)
				Algo_Robo_Cm_MoveCarForward(dutycycle);
			else if(dutycycle==0)
			{
				Algo_Robo_Cm_StopCar();
				state=WAIT;
			}
			else if(dutycycle<0)
				Algo_Robo_Cm_MoveCarBackward(-dutycycle);
			break;


	}
}
