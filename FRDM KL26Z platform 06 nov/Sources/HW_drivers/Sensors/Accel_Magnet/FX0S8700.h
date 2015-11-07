/****************************************************************************

COPYRIGHT (C) $Date: Nov 6, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: FX0S8700.h  $

$Author: Leonte Alexandru $

****************************************************************************/

#ifndef FXOS8700_H
#define FXOS8700_H


#define I2C_ERROR						0x20
#define OK_ERROR						0x00

#define FXOS8700_I2C_ADDRESS	        (0x1D<<1)		 // FXOS8700 I2C address

//FXOS8700 useful mask
#define FXOS8700_CTRL2_RESET_MASK		 (1UL<<6)
#define FXOS8700CQ_WHOAMI_VAL 				0xC7		// Device ID


//FXOS8700 Memory map

#define FXOS8700_STATUS_REG					0x00		/*Real-time data-ready status or FIFO status*/
#define FXOS8700CQ_WHOAMI_REG 				0x00
#define FXOS8700_XYZ_DATA_CFG				0x0E		/*Acceleration dynamic range and filter
															enable settings */
#define FXOS8700_CTRL_REG1					0x2A		/*System ODR, accelerometer OSR, operating mode*/
#define FXOS8700_CTRL_REG2					0x2B		/*Self-Test, Reset, accelerometer OSR and
														Sleep mode settings */
#define FXOS8700_CTRL_REG3					0x2C		/*Sleep mode interrupt wake enable, interrupt
														polarity, push-pull/opendrain configuration */
#define FXOS8700_CTRL_REG4					0x2D		/*Interrupt enable register */
#define FXOS8700_CTRL_REG5					0x2E		/*Interrupt pin (INT1/INT2) map */

#define FXOS8700_M_CTRL_REG1				0x5B		/*Control for magnetic sensor functions*/
#define FXOS8700_M_CTRL_REG2				0x5C		/*Control for magnetic sensor functions*/
#define FXOS8700_M_CTRL_REG3				0x5D		/*Control for magnetic sensor functions*/

#define FXOS8700CQ_READ_LEN 13		// status plus 6 channels = 13 bytes

#define X 0
#define Y 1
#define Z 2

typedef struct FXOS8700_data_tag FXOS8700_data_struct;


// Sensor data structure
struct FXOS8700_data_tag
{
uint16 x;
uint16 y;
uint16 z;
};

extern void Accel_ISR(void);

extern uint8 initialise_fxos8700 ();
extern uint8 Io_FXOS8700CQ_Reset();
extern uint8 Io_FX0S8700CQ_Check();

#endif /* FXOS8700_H */
