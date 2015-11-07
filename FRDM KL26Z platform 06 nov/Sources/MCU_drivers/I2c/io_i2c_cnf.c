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

$Log: io_i2c_cnf.c  $

$Author: Leonte Alexandru $

****************************************************************************/

#include "io_i2c.h"

const Io_I2c_CnfDeviceStruct Io_I2c_CnfDevice[]=
{
	/*		I2C				ICR 			MULT */
		{	I2C0,			0x14,			0		},

};



const Io_I2c_CnfTypeStruct Io_I2c_Cnf[]=
{
		{
		sizeof(Io_I2c_CnfDevice)/sizeof(Io_I2c_CnfDeviceStruct),
		(const Io_I2c_CnfDeviceStruct*) Io_I2c_CnfDevice
		}
};
