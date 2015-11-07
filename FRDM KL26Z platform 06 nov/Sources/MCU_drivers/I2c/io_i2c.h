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

$Log: io_i2c.h  $

$Author: Leonte Alexandru $

****************************************************************************/

#ifndef IO_I2C_H
#define IO_I2C_H


#include "MKL26Z4.h"
#include "Platform_Types/std_types.h"
#include "Platform_Types/powersar_addon_types.h"
#include "Platform_Types/platform_types.h"

#include "MCU_drivers/Int/io_int.h"

#define I2C_READ           							 1
#define I2C_WRITE          							 0
#define I2C_MAX_TIMEOUT								1000

static inline void i2c_Start(I2C_Type * i2c)
{
	i2c->C1 |= I2C_C1_MST_MASK;					//set master mode
}


static inline void i2c_Wait(I2C_Type * i2c)
{
	while((i2c->S & I2C_S_IICIF_MASK)==0) {};
	i2c->S |= I2C_S_IICIF_MASK;
}


static inline void i2c_EnterRxMode(I2C_Type * i2c)
{
	i2c->C1 &= ~I2C_C1_TX_MASK;
	i2c->C1 &= ~I2C_C1_TXAK_MASK;
}

static inline void i2c_StartCondition(I2C_Type * i2c)
{
	i2c->C1 |= I2C_C1_TX_MASK;
	i2c->C1 |= I2C_C1_MST_MASK;
}

static inline void i2c_RepeatedStart(I2C_Type * i2c)
{
	i2c->C1 |= I2C_C1_RSTA_MASK;
}

static inline void i2c_DisableAck(I2C_Type * i2c)
{
	i2c->C1 |= I2C_C1_TXAK_MASK;
}

static inline void i2c_write_byte(I2C_Type * i2c,uint8 data)
{
	i2c->D = data;
}

static inline uint16 i2c_get_ack(I2C_Type * i2c)
{
    if((i2c->S & I2C_S_RXAK_MASK) == 0)
        return TRUE;
    else
        return FALSE;
}

static inline void i2c_set_rx_mode(I2C_Type * i2c)
{
    i2c->C1 &= ~I2C_C1_TX_MASK;
}



static inline void i2c_give_nack(I2C_Type * i2c)
{
    i2c->C1 |= I2C_C1_TXAK_MASK;
}

static inline uint8 i2c_read_byte(I2C_Type * i2c)
{
    return i2c->D;
}

static inline void i2c_set_slave_mode(I2C_Type * i2c)
{
    i2c->C1  &= ~I2C_C1_MST_MASK;
}

static inline void i2c_Stop(I2C_Type * i2c)
{
	i2c_set_slave_mode(i2c);
	i2c_set_rx_mode(i2c);
}


typedef struct Io_I2c_CnfTypeStruct_Tag Io_I2c_CnfTypeStruct;
typedef struct Io_I2c_DeviceStruct_tag Io_I2c_CnfDeviceStruct;



struct Io_I2c_DeviceStruct_tag
{
	I2C_Type * i2c;
	uint8 i2c_icr;
	uint8 i2c_mult;
};

struct Io_I2c_CnfTypeStruct_Tag
{
	uint8 noOfI2c;
	const Io_I2c_CnfDeviceStruct *Io_I2c_CnfPtr;

};

extern void Io_I2c_Init(const Io_I2c_CnfTypeStruct *Io_I2c_Cnf);
extern void Io_I2c_Deinit(I2C_Type * i2c);
extern void Io_I2c_ShutDown();

extern uint8 Io_I2c_RegWrite(I2C_Type * i2c,uint8 address, uint8 reg, uint8 *data);
extern uint8 Io_I2c_RegRead (I2C_Type * i2c, uint8 address, uint8 reg,  uint8 * resut_address);
extern uint8 Io_I2c_RegReadN (I2C_Type * i2c, uint8 SlaveAddress,uint8 RegisterAddress, uint8 N, uint8 *array);


extern void Io_I2C0_Isr(void);

#endif /* IO_I2C_H */
