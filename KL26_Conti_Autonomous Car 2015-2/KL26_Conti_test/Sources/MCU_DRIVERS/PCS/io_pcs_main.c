/*~-1*/
/*~XSF_LANGUAGE: C/C++*/
/*~A:1*/
/*~+:Module Header*/
/*~T*/
/* ## Module Header Start [3ce14364-ad6b-4ef1-b8a6-97440054e01b] */
/****************************************************************************

COPYRIGHT (C) $Date: 2012/05/10 14:20:43CEST $
$CompanyInfo:  $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

Spec Reference:
Purpose: <description>

$ProjectName:  $

$Log: io_pcs_main.c  $


 ****************************************************************************/
/* ## Module Header End [3ce14364-ad6b-4ef1-b8a6-97440054e01b] */

#include "MCU_DRIVERS/DIO/io_dio.h"
#include "MCU_DRIVERS/INT/io_int_cnf.h"
#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"

#include "OTHER_FUNCTIONS/io_func.h"

#include "io_pcs_cnf.h"

uint16 Io_Pcs_CnPortValPrev, Io_Pcs_CnPortVal;
const Io_Pcs_CnfTypeStruct *Io_Pcs_CnfPtr ;
const PORT_MemMapPtr Io_Pcs_PortTab[5] = PORT_BASE_PTRS;

void Io_Pcs_ChangeNotificationInit(void)
/*~-1*/
{
	/*~T*/
	/* CN4/RB0 **/
	//TRISBbits.TRISB0 = 1;	// make the port as input
	//CNEN1bits.CN4IE = 1;	// enable interrupt
	//CNPU1bits.CN4PUE = 0;	// disable pull-up resistor
	//CNPD1bits.CN4PDE = 0;	// disable pull-down resistor
	/*~T*/
	/* CN5/RB1 **/
	//TRISBbits.TRISB1 = 1;	// make the port as input
	//CNEN1bits.CN5IE = 1;	// enable interrupt
	//CNPU1bits.CN5PUE = 0;	// disable pull-up resistor
	//CNPD1bits.CN5PDE = 0;	// disable pull-down resistor
	/*~T*/
	/* CN6/RB2 **/
	//TRISBbits.TRISB2 = 1;	// make the port as input
	//CNEN1bits.CN6IE = 1;	// enable interrupt
	//CNPU1bits.CN6PUE = 0;	// disable pull-up resistor
	//CNPD1bits.CN6PDE = 0;	// disable pull-down resistor
	/*~T*/
	//IFS1bits.CNIF = 0;		// clear IF
	//IPC4bits.CNIP = 7;		// set IP as 7
	//IEC1bits.CNIE = 1;		// enable CN
	/*~T*/
	Io_Pcs_CnPortValPrev = Io_Pcs_CnPortVal = 0;
}

void Io_Pcs_Init(const Io_Pcs_CnfTypeStruct *PtrCnf)
{
	uint32_t i;
	uint8_t Port;
	uint8_t Pin;
	uint8_t Dir;
	uint32_t Config;
	const Io_Pcs_PortTypeStruct *tmp_ptr;
	Io_Pcs_CnfPtr  = PtrCnf;
	tmp_ptr = Io_Pcs_CnfPtr ->Io_Pcs_PinPtr;
	const FGPIO_MemMapPtr Io_Pcs_FGPIO[5] = FGPIO_BASE_PTRS;

	for (i = 0; i < Io_Pcs_CnfPtr ->Nr_Of_Pins; i++)
	{
		Port = tmp_ptr->Port;
		Pin = tmp_ptr->Pin;
		Config = tmp_ptr->Cfg;
		Dir= tmp_ptr->Dir;
		FGPIO_PDDR_REG(Io_Pcs_FGPIO[Port]) |= (Dir&1UL)<<Pin;

		/*if (Dir == IO_PCS_OUTPUT){
          FGPIO_PDDR_REG(Io_Dio_PortTab[Port]) = FGPIO_PDDR_REG(Io_Dio_PortTab[Port]) | (1 << Pin);
      }
      else
      {
          FGPIO_PDDR_REG(Io_Dio_PortTab[Port]) = FGPIO_PDDR_REG(Io_Dio_PortTab[Port]) & ~(1 << Pin);
      }*/
		SIM_SCGC5 |= (1 << Port) << 9;
		PORT_PCR_REG(Io_Pcs_PortTab[Port], Pin) = Config;
		tmp_ptr++;

	}
}

#ifdef NOT_USED

void Io_Pcs_WriteIocr(uint8 PortPin, uint8 Level)
{
	uint8 Port;
	uint8 Pin;

	Port = IO_PCS_GET_PORT(PortPin);
	Pin  = IO_PCS_GET_PIN(PortPin);

	if (Level)
	{
		*(uint16*)(TRISA + (Port * IO_PCS_INTER_REG_ADDR_SIZE)) |= (Level << Pin);
	}
	else
	{
		*(uint16*)(TRISA + (Port * IO_PCS_INTER_REG_ADDR_SIZE)) &= ~(Level << Pin);

	}
}

#endif

#ifdef NOT_USED

uint8 Io_Pcs_ReadIocr(uint8 PortPin)
{
	uint8 Port;
	uint8 Pin;
	uint8 Level;

	Port = IO_PCS_GET_PORT(PortPin);
	Pin  = IO_PCS_GET_PIN(PortPin);
	Level = ((uint8)((*(uint16*)(TRISA + (Port * IO_PCS_INTER_REG_ADDR_SIZE)) & (1 << Pin)) >> Pin));

	return (Level);
}

#endif

void Io_Pcs_ChangeNotificationIsr(void)
{
	/* Disable interrupts until CN will be treated */
	Io_Int_DisableInterrupts();

	/* Enable interrupts until CN will be treated */
	Io_Int_EnableInterrupts();

}

void Io_Pcs_PinDir(uint16 PortPin, uint8 dir)
{
	uint8 Port,Pin;
	/* Get the Port */
	Port = IO_PCS_GET_PORT(PortPin);
	/* Get the Pin */
	Pin  = IO_PCS_GET_PIN(PortPin);

	if (dir)

	{
		FGPIO_PDDR_REG(Io_Dio_PortTab[Port]) = FGPIO_PDDR_REG(Io_Dio_PortTab[Port]) | (1 << Pin);
	}

	else
	{
		FGPIO_PDDR_REG(Io_Dio_PortTab[Port]) = FGPIO_PDDR_REG(Io_Dio_PortTab[Port]) & ~(1 << Pin);
	}
}
uint32 Io_Pcs_GetInfo(uint16 PortPin, uint8 detail)
{
	uint32 info;
	uint8 Port;
	uint8 Pin;
	uint32_t i;
	const Io_Pcs_PortTypeStruct *tmp_ptr;
	tmp_ptr = Io_Pcs_CnfPtr->Io_Pcs_PinPtr;

	Port = IO_PCS_GET_PORT(PortPin);
	Pin  = IO_PCS_GET_PIN(PortPin);

	for (i=0; i <= Io_Pcs_CnfPtr->Nr_Of_Pins; i++){
		if (Port==tmp_ptr->Port && Pin==tmp_ptr->Pin)
		{
			if(detail)
				return tmp_ptr->Dir;
			else
				return tmp_ptr->Cfg;
		}
		tmp_ptr++;
	}
	//return U32_MAX;

}

uint8 Io_Pcs_GetGpioDirection(uint16 PortPin)
{
	uint8 direction;
	uint8 Port;
	uint8 Pin;

	Port = IO_PCS_GET_PORT(PortPin);
	Pin  = IO_PCS_GET_PIN(PortPin);

	direction = (uint8)( Io_Func_ShrU16((FGPIO_PDDR_REG(Io_Dio_PortTab[Port]) & Io_Func_ShlU32(1, Pin)), Pin));
	return direction;

}
