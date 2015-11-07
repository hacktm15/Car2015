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

$Log: FX0S8700.c  $

$Author: Leonte Alexandru $

 ****************************************************************************/

#include "stdlib.h"

#include "MCU_drivers/I2c/io_i2c_cnf.h"

#include "FX0S8700.h"

uint8 accel_read(void);
uint16 ReadAccelMagnData(FXOS8700_data_struct *pAccelData, FXOS8700_data_struct *pMagnData);

uint8 initialise_fxos8700 ()
{
	uint8 tmp_byte = 0;

	/*************************************************************************************************/
	// write 0000 0000 = 0x00 to accelerometer control register 1 to place FXOS8700CQ
	// into
	// standby
	// [7-1] = 0000 000
	// [0]: active=0

	tmp_byte = 0x00;
	if(Io_I2c_RegWrite(I2C0,FXOS8700_I2C_ADDRESS,FXOS8700_CTRL_REG1,&tmp_byte) != 0)
	{
		return I2C_ERROR;
	}

	// write 0001 1111 = 0x1F to magnetometer control register 1
	// [7]: m_acal=0: auto calibration disabled
	// [6]: m_rst=0: no one-shot magnetic reset
	// [5]: m_ost=0: no one-shot magnetic measurement
	// [4-2]: m_os=111=7: 8x oversampling (for 200Hz) to reduce magnetometer noise
	// [1-0]: m_hms=11=3: select hybrid mode with accel and magnetometer active

	tmp_byte = 0x1F;
	if (Io_I2c_RegWrite(I2C0, FXOS8700_I2C_ADDRESS, FXOS8700_M_CTRL_REG1, &tmp_byte) != 0)
	{
		return (I2C_ERROR);
	}
	//	tmp_byte = 0x0;
	// Io_I2c_RegRead(I2C0, FXOS8700_I2C_ADDRESS,FXOS8700_M_CTRL_REG1,&tmp_byte);


	// write 0010 0000 = 0x20 to magnetometer control register 2
	// [7]: reserved
	// [6]: reserved
	// [5]: hyb_autoinc_mode=1 to map the magnetometer registers to follow the
	// accelerometer registers
	// [4]: m_maxmin_dis=0 to retain default min/max latching even though not used
	// [3]: m_maxmin_dis_ths=0
	// [2]: m_maxmin_rst=0
	// [1-0]: m_rst_cnt=00 to enable magnetic reset each cycle

	tmp_byte = 0x20;
	if (Io_I2c_RegWrite(I2C0, FXOS8700_I2C_ADDRESS, FXOS8700_M_CTRL_REG2, &tmp_byte) != 0)
	{
		return (I2C_ERROR);
	}
	//	tmp_byte = 0x0;

	// Io_I2c_RegRead(I2C0, FXOS8700_I2C_ADDRESS,FXOS8700_M_CTRL_REG2,&tmp_byte);

	// write 0000 0001= 0x01 to XYZ_DATA_CFG register
	// [7]: reserved
	// [6]: reserved
	// [5]: reserved
	// [4]: hpf_out=0
	// [3]: reserved
	// [2]: reserved
	// [1-0]: fs=01 for accelerometer range of +/-4g range with 0.488mg/LSB

	tmp_byte = 0x01;
	if (Io_I2c_RegWrite(I2C0, FXOS8700_I2C_ADDRESS, FXOS8700_XYZ_DATA_CFG, &tmp_byte) != 0)
	{
		return (I2C_ERROR);
	}
	//	tmp_byte = 0x0;

	// Io_I2c_RegRead(I2C0, FXOS8700_I2C_ADDRESS,FXOS8700_XYZ_DATA_CFG,&tmp_byte);

	// write 0000 1101 = 0x0D to accelerometer control register 1
	// [7-6]: aslp_rate=00
	// [5-3]: dr=001 for 200Hz data rate (when in hybrid mode)
	// [2]: lnoise=1 for low noise mode
	// [1]: f_read=0 for normal 16 bit reads
	// [0]: active=1 to take the part out of standby and enable sampling

	tmp_byte = 0x0D;

	if (Io_I2c_RegWrite(I2C0, FXOS8700_I2C_ADDRESS, FXOS8700_CTRL_REG1, &tmp_byte) != 0)
	{
		return (I2C_ERROR);
	}
	//	tmp_byte = 0x0;

	//	 Io_I2c_RegRead(I2C0, FXOS8700_I2C_ADDRESS,FXOS8700_CTRL_REG1,&tmp_byte);





	return OK_ERROR;
}

uint8 Io_FXOS8700CQ_Reset()
{
	uint8 tmp_byte;

	tmp_byte = FXOS8700_CTRL2_RESET_MASK;

	if(Io_I2c_RegWrite(I2C0,FXOS8700_I2C_ADDRESS,FXOS8700_CTRL_REG2, &tmp_byte) != 0)
	{
		return -1;
		//error occurred
	}

	/*
	 * Reset the FXOS8700 so we reconfigure it from a known state
	   	          This also places it into standby mode
	 * Write 0100 0000 = 0x40 to accelerometer control register 2
	 *[7]
	 *[6] rst = 1 .The rst bit is used to initiate a software reset.
	 *[5]
	 *[4]
	 *[3]
	 *[2]
	 *[1]
	 *[0]
	 */
	return OK_ERROR;
}

// read status and the three channels of accelerometer and magnetometer data from
// FXOS8700CQ (13 bytes)

uint16 ReadAccelMagnData(FXOS8700_data_struct *pAccelData, FXOS8700_data_struct *pMagnData)
{
	uint8 Buffer[FXOS8700CQ_READ_LEN];
	// read FXOS8700CQ_READ_LEN=13 bytes (status byte and the six channels of data)
	Io_I2c_RegReadN(I2C0,FXOS8700_I2C_ADDRESS,FXOS8700_STATUS_REG,FXOS8700CQ_READ_LEN, Buffer);


	pAccelData->x = (int16_t)(((Buffer[1] << 8) | Buffer[2]))>> 2;
	pAccelData->y = (int16_t)(((Buffer[3] << 8) | Buffer[4]))>> 2;
	pAccelData->z = (int16_t)(((Buffer[5] << 8) | Buffer[6]))>> 2;



	// copy the magnetometer byte data into 16 bit words
	pMagnData->x = (Buffer[7] << 8) | Buffer[8];
	pMagnData->y = (Buffer[9] << 8) | Buffer[10];
	pMagnData->z = (Buffer[11] << 8) | Buffer[12];


	return OK_ERROR;
}

uint8 Io_FX0S8700CQ_Check(){


	FXOS8700_data_struct accel_data;
	FXOS8700_data_struct  magnet_data;


	ReadAccelMagnData(&accel_data, &magnet_data);
	if( (magnet_data.x > 70) && (magnet_data.x < 130))
	{
		if(magnet_data.y < 300)
		{
			Io_Dio_SetPinLevel(SET_LED_GREEN,LED_ON);
			Io_Dio_SetPinLevel(SET_LED_RED,LED_OFF);
			Io_Dio_SetPinLevel(SET_LED_BLUE,LED_OFF);

		}
		else
		{
			Io_Dio_SetPinLevel(SET_LED_GREEN,LED_OFF);
			Io_Dio_SetPinLevel(SET_LED_RED,LED_OFF);
			Io_Dio_SetPinLevel(SET_LED_BLUE,LED_ON);
		}
	}
	else
	{
		Io_Dio_SetPinLevel(SET_LED_GREEN,LED_OFF);
		Io_Dio_SetPinLevel(SET_LED_RED,LED_ON);
		Io_Dio_SetPinLevel(SET_LED_BLUE,LED_OFF);
	}

	return 0;
}



void Accel_ISR()
{

}
