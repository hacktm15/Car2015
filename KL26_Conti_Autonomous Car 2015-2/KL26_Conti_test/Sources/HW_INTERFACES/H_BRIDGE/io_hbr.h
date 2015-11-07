
#ifndef IO_HBR_H
#define IO_HBR_H


#include "MKL26Z4.h"
#include "PLATFORM_TYPES/std_types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "PLATFORM_TYPES/platform_types.h"

#define IO_HBR_PWM_DuCy_TO_HEX(x) ((0x4000*x)/100)

#define IO_HBR_1 			 0
#define IO_HBR_2			 1

#define IO_HBR_1_A 			 0
#define IO_HBR_2_A 			 1
#define IO_HBR_1_B 			 2
#define IO_HBR_2_B 			 3

//H-bridge modes definition

#define HBR_STATE_BACKWARD	 0 // CW
#define HBR_STATE_FORWARD 	 1 // CCW
#define HBR_STATE_SHORTBRAKE 2
#define HBR_STATE_STOP 		 3
#define HBR_STATE_STANDBY 	 4

#define BACKWARD 			 0
#define FORWARD 			 1

//
#define IO_MOTOR_FRONT_LEFT  0
#define IO_MOTOR_FRONT_RIGHT 1
#define IO_MOTOR_BACK_LEFT   2
#define IO_MOTOR_BACK_RIGHT  3

#define IO_MOTORS_LEFT		 0
#define IO_MOTORS_RIGHT		 1


typedef struct Io_Hbr_Port_Struct_tag Io_Hbr_Port_Struct;
typedef struct Io_Hbr_Cnf_Struct_tag Io_Hbr_Cnf_Struct;



struct Io_Hbr_Port_Struct_tag
{
	uint32 hbr_pwm;//pwm channel configuration
	uint16 hbr_in1;
	uint16 hbr_in2;
	uint16 hbr_stby;
};
struct Io_Hbr_Cnf_Struct_tag
{
	uint8_t nr_of_hbrs;
	const Io_Hbr_Port_Struct *hbr_pin_ptr;
} ;

extern void Io_Hbr_Initialization(const Io_Hbr_Cnf_Struct *ptr_cfg);

/* this interface puts in STANDBY mode the h-bridge specified as argument(@hbr_nr)
 * @hbr_nr
 *  IO_HBR_1_A 0
 *  IO_HBR_2_A 1
    IO_HBR_1_B 2
    IO_HBR_2_B 3
 */
extern void Io_Hbr_Standby(uint8 hbr_nr);

/* this interface stops all the active H-bridges
 * creates the stop condition for all H-bridges
 */
extern void Io_Hbr_Shutdown();

/* this interface sets the mode in which the  specified h-bridge will work
 * @hbr_nr is the number of the H-bridge you want to control
 * @hbr_state indicates the H-bridge state
 * @hbr_state can get values from 0 to 255 but only the values 0,1,2,3,4 represent correct modes
 *
 * 0 -> HBR_STATE_BACKWARD 		//backward
   1 -> HBR_STATE_FORWARD		//forward
   2 -> HBR_STATE_SHORTBRAKE
   3 -> HBR_STATE_STOP
   4 -> HBR_STATE_STANDBY
 */
extern void Io_Hbr_Set_State(uint8 hbr_state,uint8 hbr_nr);

/* this interface returns the  mode in which the specified H-bridge works
 * the returned values are between 0 and 4 :
 *
 * 0 -> HBR_STATE_BACKWARD //backward
   1 -> HBR_STATE_FORWARD  //forward
   2 -> HBR_STATE_SHORTBRAKE
   3 -> HBR_STATE_STOP
   4 -> HBR_STATE_STANDBY
   @hbr_nr is the name/number of the h-bridge
 */
extern uint8 Io_Hbr_Get_State(uint8 hbr_nr);

/* this interface controls the direction and the speed for the motor specified as an argument
 * @direction -0 - BACKWARD
 * 			  -1 - FORWARD
 *
 * @dutycycle:physical values 0->100% , hex limits 0000h-4000h
 * @motor_nr :
 *  IO_MOTOR_FRONT_LEFT  0
 *  IO_MOTOR_FRONT_RIGHT 1
    IO_MOTOR_BACK_LEFT   2
    IO_MOTOR_BACK_RIGHT  3
 */
extern void Io_Hbr_Update(uint8 direction,uint16 dutycycle,uint8 motor_nr);

#endif
