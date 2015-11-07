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

$Log: io_lcd_main.c  $


 ****************************************************************************/
/* ## Module Header End [3ce14364-ad6b-4ef1-b8a6-97440054e01b] */
/*~E:A1*/
/*~A:2*/
/*~+:Includes*/
/*~T*/
#include "SYSTEM/OS/io_os.h"
#include "SYSTEM/SCHEDULER/io_sch_cnf.h"

#include "MCU_DRIVERS/ADC/io_adc_cnf.h"
#include "MCU_DRIVERS/DIO/io_dio.h"
#include "MCU_DRIVERS/INT/io_int_cnf.h"
#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"
#include "MCU_DRIVERS/TIMER/io_tim.h"
#include "MCU_DRIVERS/TPM/io_tpm_cnf.h"

#include "OTHER_FUNCTIONS/io_func.h"

#include "io_lcd_cnf.h"
/*~E:A2*/
/*~A:3*/
/*~+:Macro Defines*/
/*~T*/
/* Defines */
/*~T*/
#define Io_Lcd_EHigh()           Io_Dio_SetPinLevel(IO_LCD_E_PIN, IO_LCD_LEVEL_HIGH)
#define Io_Lcd_ELow()            Io_Dio_SetPinLevel(IO_LCD_E_PIN, IO_LCD_LEVEL_LOW)

/*~T*/
#define Io_Lcd_RwHigh()          Io_Dio_SetPinLevel(IO_LCD_RW_PIN, IO_LCD_LEVEL_HIGH)
#define Io_Lcd_RwLow()           Io_Dio_SetPinLevel(IO_LCD_RW_PIN, IO_LCD_LEVEL_LOW)

/*~T*/
#define Io_Lcd_RsHigh()          Io_Dio_SetPinLevel(IO_LCD_RS_PIN, IO_LCD_LEVEL_HIGH)
#define Io_Lcd_RsLow()           Io_Dio_SetPinLevel(IO_LCD_RS_PIN, IO_LCD_LEVEL_LOW)
/*~E:A3*/
/*~A:4*/
/*~+:Operation prototypes*/
/*~T*/
static void Io_Lcd_PutStringTask(uint32 StringAddr);
/*~E:A4*/
/*~A:5*/
/*~+:Attributes*/
/*~A:6*/
/*~+:Variables and Constants*/
/*~T*/
/* Variables and Constants */
/*~T*/
volatile uint8 Io_Lcd_Semaphore;
/*~E:A6*/
/*~E:A5*/
/*~A:7*/
/*~+:Operations*/
/*~A:8*/
/*~+:Private operations*/
/*~T*/
/* Private operations */
/*~A:9*/
/*~+:Io_Lcd_EDelay*/
/*~F:10*/
void Io_Lcd_EDelay(void)
/*~-1*/
{
	/*~T*/
	Io_Tim_DelayUs(100);  // 100us
	/*~-1*/
}
/*~E:F10*/
/*~E:A9*/
/*~A:11*/
/*~+:Io_Lcd_Write*/
/*~T*/
/*************************************************************************
Low-level function to write byte to LCD controller
Input:    byte_data   byte to write to LCD
          type        LCD_WRITE_DATA: write data    
                      LCD_WRITE_INSTR: write instruction
Returns:  none
 *************************************************************************/

/*~T*/

/*~F:12*/
void Io_Lcd_Write(uint8 ByteData, uint8 Type) 
/*~-1*/
{
	/*~I:13*/
	if (Type == IO_LCD_WRITE_DATA)
		/*~-1*/
	{
		/*~T*/
		Io_Lcd_RsHigh(); /* write data        (RS=1, RW=0) */
		/*~-1*/
	}
	/*~O:I13*/
	/*~-2*/
	else
	{
		/*~T*/
		Io_Lcd_RsLow(); /* write instruction (RS=0, RW=0) */
		/*~-1*/
	}
	/*~E:I13*/
	/*~T*/
	Io_Lcd_RwLow();
	/*~A:14*/
	/*~+: output high part first */
	/*~T*/
	/* output high part first */
	Io_Dio_SetPinLevel(IO_LCD_DATA3_PIN, IO_LCD_LEVEL_LOW);
	Io_Dio_SetPinLevel(IO_LCD_DATA2_PIN, IO_LCD_LEVEL_LOW);
	Io_Dio_SetPinLevel(IO_LCD_DATA1_PIN, IO_LCD_LEVEL_LOW);
	Io_Dio_SetPinLevel(IO_LCD_DATA0_PIN, IO_LCD_LEVEL_LOW);

	/*~I:15*/
	if (ByteData & 0x80)
		/*~-1*/
	{
		/*~T*/
		Io_Dio_SetPinLevel(IO_LCD_DATA3_PIN, IO_LCD_LEVEL_HIGH);

		/*~-1*/
	}
	/*~E:I15*/
	/*~I:16*/
	if (ByteData & 0x40)
		/*~-1*/
	{
		/*~T*/
		Io_Dio_SetPinLevel(IO_LCD_DATA2_PIN, IO_LCD_LEVEL_HIGH);

		/*~-1*/
	}
	/*~E:I16*/
	/*~I:17*/
	if (ByteData & 0x20)
		/*~-1*/
	{
		/*~T*/
		Io_Dio_SetPinLevel(IO_LCD_DATA1_PIN, IO_LCD_LEVEL_HIGH);

		/*~-1*/
	}
	/*~E:I17*/
	/*~I:18*/
	if (ByteData & 0x10)
		/*~-1*/
	{
		/*~T*/
		Io_Dio_SetPinLevel(IO_LCD_DATA0_PIN, IO_LCD_LEVEL_HIGH);

		/*~-1*/
	}
	/*~E:I18*/
	/*~T*/

	/*~E:A14*/
	/*~T*/
	Io_Lcd_EHigh();
	Io_Lcd_EDelay();
	Io_Lcd_ELow();

	/*~A:19*/
	/*~+: output low part second */
	/*~T*/
	/* output high part first */
	Io_Dio_SetPinLevel(IO_LCD_DATA3_PIN, IO_LCD_LEVEL_LOW);
	Io_Dio_SetPinLevel(IO_LCD_DATA2_PIN, IO_LCD_LEVEL_LOW);
	Io_Dio_SetPinLevel(IO_LCD_DATA1_PIN, IO_LCD_LEVEL_LOW);
	Io_Dio_SetPinLevel(IO_LCD_DATA0_PIN, IO_LCD_LEVEL_LOW);

	/*~I:20*/
	if (ByteData & 0x08)
		/*~-1*/
	{
		/*~T*/
		Io_Dio_SetPinLevel(IO_LCD_DATA3_PIN, IO_LCD_LEVEL_HIGH);

		/*~-1*/
	}
	/*~E:I20*/
	/*~I:21*/
	if (ByteData & 0x04)
		/*~-1*/
	{
		/*~T*/
		Io_Dio_SetPinLevel(IO_LCD_DATA2_PIN, IO_LCD_LEVEL_HIGH);

		/*~-1*/
	}
	/*~E:I21*/
	/*~I:22*/
	if (ByteData & 0x02)
		/*~-1*/
	{
		/*~T*/
		Io_Dio_SetPinLevel(IO_LCD_DATA1_PIN, IO_LCD_LEVEL_HIGH);

		/*~-1*/
	}
	/*~E:I22*/
	/*~I:23*/
	if (ByteData & 0x01)
		/*~-1*/
	{
		/*~T*/
		Io_Dio_SetPinLevel(IO_LCD_DATA0_PIN, IO_LCD_LEVEL_HIGH);

		/*~-1*/
	}
	/*~E:I23*/
	/*~T*/

	/*~E:A19*/
	/*~T*/
	Io_Lcd_EHigh();
	Io_Lcd_EDelay();
	Io_Lcd_ELow();

	/*~A:24*/
	/*~+: All data pins to INACTIVE*/
	/*~T*/
	Io_Dio_SetPinLevel(IO_LCD_DATA3_PIN, IO_LCD_LEVEL_HIGH);
	Io_Dio_SetPinLevel(IO_LCD_DATA2_PIN, IO_LCD_LEVEL_HIGH);
	Io_Dio_SetPinLevel(IO_LCD_DATA1_PIN, IO_LCD_LEVEL_HIGH);
	Io_Dio_SetPinLevel(IO_LCD_DATA0_PIN, IO_LCD_LEVEL_HIGH);

	/*~E:A24*/
	/*~-1*/
}
/*~E:F12*/
/*~T*/

/*~E:A11*/
/*~A:25*/
/*~+:Io_Lcd_Read*/
/*~T*/
/*************************************************************************
Low-level function to read byte to LCD controller
Input:    type        LCD_READ_DATA: read data    
                      LCD_READ_INSTR: read instruction
Returns:  byte read from LCD controller
 *************************************************************************/

/*~T*/

/*~F:26*/
uint8  Io_Lcd_Read(uint8 Type) 
/*~-1*/
{
	/*~T*/
	uint8 Data;
	/*~I:27*/
	if (Type == IO_LCD_READ_DATA)
		/*~-1*/
	{
		/*~T*/
		Io_Lcd_RsHigh(); /* read data        (RS=1) */
		/*~-1*/
	}
	/*~O:I27*/
	/*~-2*/
	else
	{
		/*~T*/
		Io_Lcd_RsLow(); /* read instruction (RS=0 read busy flag) */
		/*~-1*/
	}
	/*~E:I27*/
	/*~T*/
	Io_Lcd_RwHigh(); /* RW=1  read mode      */
	/*~T*/
	Io_Lcd_EHigh();
	Io_Lcd_EDelay();
	Data = 0;

	/*~A:28*/
	/*~+: read high part first */
	/*~I:29*/
	if (Io_Dio_GetPinState(IO_LCD_DATA0_PIN) & IO_LCD_LEVEL_HIGH)
		/*~-1*/
	{
		/*~T*/
		Data |= 0x10;

		/*~-1*/
	}
	/*~E:I29*/
	/*~I:30*/
	if (Io_Dio_GetPinState(IO_LCD_DATA1_PIN) & IO_LCD_LEVEL_HIGH)
		/*~-1*/
	{
		/*~T*/
		Data |= 0x20;

		/*~-1*/
	}
	/*~E:I30*/
	/*~I:31*/
	if (Io_Dio_GetPinState(IO_LCD_DATA2_PIN) & IO_LCD_LEVEL_HIGH)
		/*~-1*/
	{
		/*~T*/
		Data |= 0x40;

		/*~-1*/
	}
	/*~E:I31*/
	/*~I:32*/
	if (Io_Dio_GetPinState(IO_LCD_DATA3_PIN) & IO_LCD_LEVEL_HIGH)
		/*~-1*/
	{
		/*~T*/
		Data |= 0x80;

		/*~-1*/
	}
	/*~E:I32*/
	/*~T*/

	/*~E:A28*/
	/*~T*/
	Io_Lcd_ELow();
	Io_Lcd_EDelay();
	Io_Lcd_EHigh();
	Io_Lcd_EDelay();

	/*~A:33*/
	/*~+: read low part second */
	/*~I:34*/
	if (Io_Dio_GetPinState(IO_LCD_DATA0_PIN) & IO_LCD_LEVEL_HIGH)
		/*~-1*/
	{
		/*~T*/
		Data |= 0x01;

		/*~-1*/
	}
	/*~E:I34*/
	/*~I:35*/
	if (Io_Dio_GetPinState(IO_LCD_DATA1_PIN) & IO_LCD_LEVEL_HIGH)
		/*~-1*/
	{
		/*~T*/
		Data |= 0x02;

		/*~-1*/
	}
	/*~E:I35*/
	/*~I:36*/
	if (Io_Dio_GetPinState(IO_LCD_DATA2_PIN) & IO_LCD_LEVEL_HIGH)
		/*~-1*/
	{
		/*~T*/
		Data |= 0x04;

		/*~-1*/
	}
	/*~E:I36*/
	/*~I:37*/
	if (Io_Dio_GetPinState(IO_LCD_DATA3_PIN) & IO_LCD_LEVEL_HIGH)
		/*~-1*/
	{
		/*~T*/
		Data |= 0x08;

		/*~-1*/
	}
	/*~E:I37*/
	/*~E:A33*/
	/*~T*/
	Io_Lcd_ELow();

	/*~T*/
	return Data;
	/*~-1*/
}
/*~E:F26*/
/*~E:A25*/
/*~A:38*/
/*~+:Io_Lcd_WaitBusy*/
/*~T*/
/*************************************************************************
loops while lcd is busy, returns address counter
 *************************************************************************/

/*~T*/

/*~F:39*/
uint8 Io_Lcd_WaitBusy(void)
/*~-1*/
{
	/*~T*/
	/* the address counter is updated 4us after the busy flag is cleared */
	//Io_Tim_DelayUs(900);
	Io_Tim_DelayUs(700);

	/*~T*/
	//return (Io_Lcd_Read(IO_LCD_READ_ADDR));  // return address counter
	return (0);
	/*~-1*/
}
/*~E:F39*/
/*~E:A38*/
/*~A:40*/
/*~+:Io_Lcd_NewLine*/
/*~T*/
/*************************************************************************
Move cursor to the start of next line or to the first line if the cursor 
is already on the last line.
 *************************************************************************/

/*~T*/

/*~F:41*/
void Io_Lcd_NewLine(uint8 Pos)
/*~-1*/
{
	/*~T*/
	volatile uint8 AddressCounter;
	/*~A:42*/
	/*~+:1 LINE*/
	/*~I:43*/
#if IO_LCD_LINES == 1
	/*~T*/
	AddressCounter = 0;
	/*~-1*/
#endif
	/*~E:I43*/
	/*~E:A42*/
	/*~A:44*/
	/*~+:2 LINES*/
	/*~I:45*/
#if IO_LCD_LINES == 2
	/*~I:46*/
	if ( Pos <  IO_LCD_START_LINE2 )
		/*~-1*/
	{
		/*~T*/
		AddressCounter = IO_LCD_START_LINE2;
		/*~-1*/
	}
	/*~O:I46*/
	/*~-2*/
	else
	{
		/*~T*/
		AddressCounter = IO_LCD_START_LINE1;
		/*~-1*/
	}
	/*~E:I46*/
	/*~-1*/
#endif
	/*~E:I45*/
	/*~E:A44*/
	/*~A:47*/
	/*~+:4 LINES*/
	/*~I:48*/
#if IO_LCD_LINES == 4
	/*~A:49*/
	/*~+:KS0073_4LINES_MODE*/
	/*~I:50*/
#if IO_LCD_KS0073_4LINES_MODE 
	/*~A:51*/
	/*~+:*/
	/*~I:52*/
	if (Pos < IO_LCD_START_LINE2 )
		/*~-1*/
	{
		/*~T*/
		AddressCounter = LCD_START_LINE2;
		/*~-1*/
	}
	/*~O:I52*/
	/*~-2*/
	else
	{
		/*~I:53*/
		if ((Pos >= IO_LCD_START_LINE2) && (Pos < IO_LCD_START_LINE3) )
			/*~-1*/
		{
			/*~T*/
			AddressCounter = IO_LCD_START_LINE3;
			/*~-1*/
		}
		/*~O:I53*/
		/*~-2*/
		else
		{
			/*~I:54*/
			if ((Pos >= IO_LCD_START_LINE3) && (Pos < IO_LCD_START_LINE4))
				/*~-1*/
			{
				/*~T*/
				AddressCounter = IO_LCD_START_LINE4;
				/*~-1*/
			}
			/*~O:I54*/
			/*~-2*/
			else
			{
				/*~T*/
				AddressCounter = IO_LCD_START_LINE1;

				/*~-1*/
			}
			/*~E:I54*/
			/*~-1*/
		}
		/*~E:I53*/
		/*~-1*/
	}
	/*~E:I52*/
	/*~E:A51*/
	/*~O:I50*/
	/*~-1*/
#else
	/*~A:55*/
	/*~+:OTHER*/
	/*~I:56*/
	if (Pos < IO_LCD_START_LINE3 )
		/*~-1*/
	{
		/*~T*/
		AddressCounter = IO_LCD_START_LINE2;
		/*~-1*/
	}
	/*~O:I56*/
	/*~-2*/
	else
	{
		/*~I:57*/
		if ((Pos >= IO_LCD_START_LINE2) && (Pos < IO_LCD_START_LINE4) )
			/*~-1*/
		{
			/*~T*/
			AddressCounter = IO_LCD_START_LINE3;
			/*~-1*/
		}
		/*~O:I57*/
		/*~-2*/
		else
		{
			/*~I:58*/
			if ( (Pos >= IO_LCD_START_LINE3) && (Pos < IO_LCD_START_LINE2))
				/*~-1*/
			{
				/*~T*/
				AddressCounter = IO_LCD_START_LINE4;
				/*~-1*/
			}
			/*~O:I58*/
			/*~-2*/
			else
			{
				/*~T*/
				AddressCounter = IO_LCD_START_LINE1;

				/*~-1*/
			}
			/*~E:I58*/
			/*~-1*/
		}
		/*~E:I57*/
		/*~-1*/
	}
	/*~E:I56*/
	/*~E:A55*/
	/*~-1*/
#endif
	/*~E:I50*/
	/*~E:A49*/
	/*~-1*/
#endif
	/*~E:I48*/
	/*~E:A47*/
	/*~T*/
	Io_Lcd_Command((1<<IO_LCD_DDRAM)+AddressCounter);
	/*~-1*/
}
/*~E:F41*/
/*~E:A40*/
/*~E:A8*/
/*~A:59*/
/*~+:Public operations*/
/*~T*/
/* Public operations */
/*~A:60*/
/*~+:Io_Lcd_Command*/
/*~T*/
/*************************************************************************
Send LCD controller instruction command
Input:   instruction to send to LCD controller, see HD44780 data sheet
Returns: none
 *************************************************************************/

/*~T*/

/*~F:61*/
void Io_Lcd_Command (uint8 Cmd)

/*~-1*/
{
	/*~T*/
	Io_Lcd_WaitBusy();
	Io_Lcd_Write(Cmd,IO_LCD_WRITE_INSTR);
	/*~-1*/
}
/*~E:F61*/
/*~E:A60*/
/*~A:62*/
/*~+:Io_Lcd_Data			-	NOT_USED*/
/*~T*/
/*************************************************************************
Send data byte to LCD controller 
Input:   data to send to LCD controller, see HD44780 data sheet
Returns: none
 *************************************************************************/

/*~I:63*/
#ifdef NOT_USED
/*~F:64*/
void Io_Lcd_Data (uint8 Data)

/*~-1*/
{
	/*~T*/
	Io_Lcd_WaitBusy();
	Io_Lcd_Write(Data,IO_LCD_WRITE_DATA);

	/*~-1*/
}
/*~E:F64*/
/*~-1*/
#endif
/*~E:I63*/
/*~T*/

/*~E:A62*/
/*~A:65*/
/*~+:Io_Lcd_GoToXy		-	 NOT_USED*/
/*~T*/
/*************************************************************************
Send data byte to LCD controller 
Input:   data to send to LCD controller, see HD44780 data sheet
Returns: none
 *************************************************************************/

/*~I:66*/
#ifdef NOT_USED
/*~F:67*/
void Io_Lcd_GoToXy(uint8 X, uint8 Y)

/*~-1*/
{
	/*~I:68*/
#if IO_LCD_LINES == 1 
	/*~T*/
	Io_Lcd_Command((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE1+X);

	/*~-1*/
#endif
	/*~E:I68*/
	/*~I:69*/
#if IO_LCD_LINES==2 
	/*~I:70*/
	if (Y==0)
		/*~-1*/
	{
		/*~T*/
		Io_Lcd_Command((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE1+X);
		/*~-1*/
	}
	/*~O:I70*/
	/*~-2*/
	else
	{
		/*~T*/
		Io_Lcd_Command((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE2+X);
		/*~-1*/
	}
	/*~E:I70*/
	/*~-1*/
#endif
	/*~E:I69*/
	/*~I:71*/
#if IO_LCD_LINES==4
	/*~I:72*/
	if (Y==0)
		/*~-1*/
	{
		/*~T*/
		Io_Lcd_Command((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE1+X);
		/*~-1*/
	}
	/*~O:I72*/
	/*~-2*/
	else
	{
		/*~I:73*/
		if (Y==1)
			/*~-1*/
		{
			/*~T*/
			Io_Lcd_Command((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE2+X);
			/*~-1*/
		}
		/*~O:I73*/
		/*~-2*/
		else
		{
			/*~I:74*/
			if (Y==2)
				/*~-1*/
			{
				/*~T*/
				Io_Lcd_Command((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE3+X);
				/*~-1*/
			}
			/*~O:I74*/
			/*~-2*/
			else
			{
				/*~T*/
				Io_Lcd_Command((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE4+X);
				/*~-1*/
			}
			/*~E:I74*/
			/*~-1*/
		}
		/*~E:I73*/
		/*~-1*/
	}
	/*~E:I72*/
	/*~-1*/
#endif
	/*~E:I71*/
	/*~-1*/
}
/*~E:F67*/
/*~-1*/
#endif
/*~E:I66*/
/*~T*/

/*~E:A65*/
/*~A:75*/
/*~+:Io_Lcd_GoToXyOs		-	 NOT_USED*/
/*~T*/
/*************************************************************************
Send data byte to LCD controller 
Input:   data to send to LCD controller, see HD44780 data sheet
Returns: none
 *************************************************************************/

/*~T*/

/*~I:76*/
#ifdef  NOT_USED
/*~F:77*/
void Io_Lcd_GoToXyTask(uint32 Xy)
/*~-1*/
{
	/*~T*/
	uint8 X, Y;
	/*~I:78*/
	if (Io_Lcd_Semaphore == 0)
		/*~-1*/
	{
		/*~A:79*/
		/*~+:Set LCD semaphore*/
		/*~T*/
		Io_Int_DisableInterrupts();
		/*~T*/
		/* Set LCD is busy */
		Io_Lcd_Semaphore = 1;
		/*~T*/
		Io_Int_EnableInterrupts();
		/*~E:A79*/
		/*~T*/
		X = (uint8)Io_Func_ShrU32(Xy,8);
		Y = (uint8)Xy;
		/*~A:80*/
		/*~+:GO TO functionality*/
		/*~I:81*/
#if IO_LCD_LINES == 1 
		/*~T*/
		Io_Lcd_Command((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE1+X);

		/*~-1*/
#endif
		/*~E:I81*/
		/*~I:82*/
#if IO_LCD_LINES==2 
		/*~I:83*/
		if (Y==0)
			/*~-1*/
		{
			/*~T*/
			Io_Lcd_Command((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE1+X);
			/*~-1*/
		}
		/*~O:I83*/
		/*~-2*/
		else
		{
			/*~T*/
			Io_Lcd_Command((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE2+X);
			/*~-1*/
		}
		/*~E:I83*/
		/*~-1*/
#endif
		/*~E:I82*/
		/*~I:84*/
#if IO_LCD_LINES==4
		/*~I:85*/
		if (Y==0)
			/*~-1*/
		{
			/*~T*/
			Io_Lcd_Command((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE1+X);
			/*~-1*/
		}
		/*~O:I85*/
		/*~-2*/
		else
		{
			/*~I:86*/
			if (Y==1)
				/*~-1*/
			{
				/*~T*/
				Io_Lcd_Command((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE2+X);
				/*~-1*/
			}
			/*~O:I86*/
			/*~-2*/
			else
			{
				/*~I:87*/
				if (Y==2)
					/*~-1*/
				{
					/*~T*/
					Io_Lcd_Command((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE3+X);
					/*~-1*/
				}
				/*~O:I87*/
				/*~-2*/
				else
				{
					/*~T*/
					Io_Lcd_Command((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE4+X);
					/*~-1*/
				}
				/*~E:I87*/
				/*~-1*/
			}
			/*~E:I86*/
			/*~-1*/
		}
		/*~E:I85*/
		/*~-1*/
#endif
		/*~E:I84*/
		/*~E:A80*/
		/*~A:88*/
		/*~+:Reset LCD semaphore*/
		/*~T*/
		Io_Int_DisableInterrupts();
		/*~T*/
		/* Set LCD is free */
		Io_Lcd_Semaphore = 0;
		/*~T*/
		Io_Int_EnableInterrupts();
		/*~E:A88*/
		/*~T*/
		Io_Os_RemovePeriodicTask((Io_Os_FuncType) Io_Lcd_GoToXyTask, Xy);
		/*~-1*/
	}
	/*~O:I78*/
	/*~-2*/
	else
	{
		/*~T*/
		/* LCD is busy. */
		/*~-1*/
	}
	/*~E:I78*/
	/*~-1*/
}
/*~E:F77*/
/*~F:89*/
void Io_Lcd_GoToXyOs(uint8 X, uint8 Y)

/*~-1*/
{
	/*~T*/
	uint32 Xy;
	/*~T*/
	Xy = Io_Func_ShlU32((uint32)X,8) + (uint32)Y;
	/*~T*/
	/* Display Char by Char by inserting Io_Lcd_PutChar function in OS in order to avoid Delay function  */
	Io_Os_InsertPeriodicTask((Io_Os_FuncType)Io_Lcd_GoToXyTask, Xy, 1, 0, IO_OS_PRIORITY_LOW);
	/*~-1*/
}
/*~E:F89*/
/*~-1*/
#endif
/*~E:I76*/
/*~T*/

/*~E:A75*/
/*~A:90*/
/*~+:Io_Lcd_GetXy		-	 NOT_USED*/
/*~I:91*/
#ifdef  NOT_USED
/*~F:92*/
uint16 Io_Lcd_GetXy(void)
/*~-1*/
{
	/*~T*/
	return Io_Lcd_WaitBusy();
	/*~-1*/
}
/*~E:F92*/
/*~-1*/
#endif
/*~E:I91*/
/*~T*/

/*~T*/

/*~E:A90*/
/*~A:93*/
/*~+:Io_Lcd_ClrScr*/
/*~T*/
/*************************************************************************
Clear display and set cursor to home position
 *************************************************************************/

/*~T*/

/*~F:94*/
void Io_Lcd_ClrScr(void)
/*~-1*/
{
	/*~T*/
	Io_Lcd_Command(1<<IO_LCD_CLR);
	/*~-1*/
}
/*~E:F94*/
/*~T*/

/*~E:A93*/
/*~A:95*/
/*~+:Io_Lcd_ClrScrOs*/
/*~T*/
/*************************************************************************
Clear display and set cursor to home position
 *************************************************************************/

/*~F:96*/
void Io_Lcd_ClrScrTask(uint32 Cmd)
/*~-1*/
{
	/*~I:97*/
	if (Io_Lcd_Semaphore == 0)
		/*~-1*/
	{
		/*~A:98*/
		/*~+:Set LCD semaphore*/
		/*~T*/
		Io_Int_DisableInterrupts();
		/*~T*/
		/* Set LCD is busy */
		Io_Lcd_Semaphore = 1;
		/*~T*/
		Io_Int_EnableInterrupts();
		/*~E:A98*/
		/*~T*/
		/* Execute ClrScr command. */
		Io_Lcd_Command((uint8)Cmd);
		/*~A:99*/
		/*~+:Reset LCD semaphore*/
		/*~T*/
		Io_Int_DisableInterrupts();
		/*~T*/
		/* Set LCD is free */
		Io_Lcd_Semaphore = 0;
		/*~T*/
		Io_Int_EnableInterrupts();
		/*~E:A99*/
		/*~T*/
		Io_Os_RemovePeriodicTask((Io_Os_FuncType) Io_Lcd_ClrScrTask, Cmd);
		/*~-1*/
	}
	/*~O:I97*/
	/*~-2*/
	else
	{
		/*~T*/
		/* LCD is busy. */
		/*~-1*/
	}
	/*~E:I97*/
	/*~-1*/
}
/*~E:F96*/
/*~T*/

/*~F:100*/
void Io_Lcd_ClrScrOs(void)
/*~-1*/
{
	/*~T*/
	uint32 Cmd;
	/*~T*/
	Cmd= (uint32)(1<<IO_LCD_CLR);
	/*~T*/
	/* Display Char by Char by inserting Io_Lcd_PutChar function in OS in order to avoid Delay function  */
	Io_Os_InsertPeriodicTask((Io_Os_FuncType)Io_Lcd_ClrScrTask, Cmd, 1, 0, IO_OS_PRIORITY_MEDIUM);
	/*~T*/

	/*~-1*/
}
/*~E:F100*/
/*~T*/

/*~E:A95*/
/*~A:101*/
/*~+:Io_Lcd_Home*/
/*~T*/
/*************************************************************************
Set cursor to home position
 *************************************************************************/

/*~T*/

/*~F:102*/
void Io_Lcd_Home(void)
/*~-1*/
{
	/*~T*/
	Io_Lcd_Command(1<<IO_LCD_HOME);
	/*~-1*/
}
/*~E:F102*/
/*~T*/

/*~E:A101*/
/*~A:103*/
/*~+:Io_Lcd_HomeOs*/
/*~T*/
/*************************************************************************
Set cursor to home position
 *************************************************************************/

/*~F:104*/
void Io_Lcd_HomeTask(uint32 Cmd)
/*~-1*/
{
	/*~I:105*/
	if (Io_Lcd_Semaphore == 0)
		/*~-1*/
	{
		/*~A:106*/
		/*~+:Set LCD semaphore*/
		/*~T*/
		Io_Int_DisableInterrupts();
		/*~T*/
		/* Set LCD is busy */
		Io_Lcd_Semaphore = 1;
		/*~T*/
		Io_Int_EnableInterrupts();
		/*~E:A106*/
		/*~T*/
		/* Execute ClrScr command. */
		Io_Lcd_Command((uint8)Cmd);
		/*~A:107*/
		/*~+:Reset LCD semaphore*/
		/*~T*/
		Io_Int_DisableInterrupts();
		/*~T*/
		/* Set LCD is free */
		Io_Lcd_Semaphore = 0;
		/*~T*/
		Io_Int_EnableInterrupts();
		/*~E:A107*/
		/*~T*/
		Io_Os_RemovePeriodicTask((Io_Os_FuncType) Io_Lcd_HomeTask, Cmd);
		/*~-1*/
	}
	/*~O:I105*/
	/*~-2*/
	else
	{
		/*~T*/
		/* LCD is busy. */
		/*~-1*/
	}
	/*~E:I105*/
	/*~-1*/
}
/*~E:F104*/
/*~T*/

/*~F:108*/
void Io_Lcd_HomeOs(void)
/*~-1*/
{
	/*~T*/
	uint32 Cmd;
	/*~T*/
	Cmd= (uint32)(1<<IO_LCD_HOME);
	/*~T*/
	/* Display Char by Char by inserting Io_Lcd_PutChar function in OS in order to avoid Delay function  */
	Io_Os_InsertPeriodicTask((Io_Os_FuncType)Io_Lcd_HomeTask, Cmd, 1, 0, IO_OS_PRIORITY_MEDIUM);
	/*~-1*/
}
/*~E:F108*/
/*~T*/

/*~E:A103*/
/*~A:109*/
/*~+:Io_Lcd_PutChar*/
/*~T*/
/*************************************************************************
Display character at current cursor position 
Input:    character to be displayed                                       
Returns:  none
 *************************************************************************/

/*~T*/

/*~F:110*/
void Io_Lcd_PutChar(uint32 Char)
/*~-1*/
{
	/*~T*/
	uint8 Pos, LocChar;
	/*~T*/
	LocChar = (uint8) Char;
	/*~T*/
	//Pos = Io_Lcd_WaitBusy();   // read busy-flag and address counter
	Pos=IO_LCD_START_LINE1;
	/*~I:111*/
	if (LocChar=='\n')
		/*~-1*/
	{
		/*~T*/
		Io_Lcd_NewLine(Pos);
		/*~-1*/
	}
	/*~O:I111*/
	/*~-2*/
	else
	{
		/*~A:112*/
		/*~+:Wrap Line ( ussualy not used)*/
		/*~T*/
#if IO_LCD_WRAP_LINES==1
#if IO_LCD_LINES==1
		if ( Pos == IO_LCD_START_LINE1+IO_LCD_DISP_LENGTH ) {
			Io_Lcd_Write((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE1,IO_LCD_WRITE_INSTR);
		}
#elif IO_LCD_LINES==2
		if ( Pos == IO_LCD_START_LINE1+IO_LCD_DISP_LENGTH ) {
			Io_Lcd_Write((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE2,IO_LCD_WRITE_INSTR);
		}else if ( Pos == IO_LCD_START_LINE2+IO_LCD_DISP_LENGTH ){
			Io_Lcd_Write((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE1,IO_LCD_WRITE_INSTR);
		}
#elif IO_LCD_LINES==4
		if ( Pos == IO_LCD_START_LINE1+IO_LCD_DISP_LENGTH ) {
			Io_Lcd_Write((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE2,IO_LCD_WRITE_INSTR);
		}else if ( Pos == IO_LCD_START_LINE2+IO_LCD_DISP_LENGTH ) {
			Io_Lcd_Write((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE3,IO_LCD_WRITE_INSTR);
		}else if ( Pos == IO_LCD_START_LINE3+IO_LCD_DISP_LENGTH ) {
			Io_Lcd_Write((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE4,IO_LCD_WRITE_INSTR);
		}else if ( Pos == IO_LCD_START_LINE4+IO_LCD_DISP_LENGTH ) {
			Io_Lcd_Write((1<<IO_LCD_DDRAM)+IO_LCD_START_LINE1,IO_LCD_WRITE_INSTR);
		}
#endif
Io_Lcd_WaitBusy();
#endif

/*~E:A112*/
/*~T*/
Io_Lcd_Write(LocChar, 1);

/*~-1*/
	}
	/*~E:I111*/
	/*~-1*/
}
/*~E:F110*/
/*~E:A109*/
/*~A:113*/
/*~+:Io_Lcd_PutString*/
/*~T*/
/*************************************************************************
Display string without auto linefeed 
Input:    string to be displayed
Returns:  none
 *************************************************************************/

/*~T*/

/*~F:114*/
void Io_Lcd_PutString(const uint8 *StringPtr)

/*~-1*/
{
	/*~T*/
	volatile uint8 Char;
	/*~L:115*/
	while ((*StringPtr != '\0') || (*(StringPtr) == '\n'))
		/*~-1*/
	{
		/*~T*/
		Char = *StringPtr++;
		/*~T*/
		Io_Lcd_PutChar(Char);
		/*~-1*/
	}
	/*~E:L115*/
	/*~-1*/
}
/*~E:F114*/
/*~E:A113*/
/*~A:116*/
/*~+:Io_Lcd_PutStringOs*/
/*~T*/
/*************************************************************************
Display string without auto linefeed 
Input:    string to be displayed
Returns:  none
 *************************************************************************/

/*~T*/
const uint8 *LcdStringPtr;
/*~T*/

/*~F:117*/
void Io_Lcd_PutStringTask(uint32 StringAddr)
/*~-1*/
{
	/*~T*/
	volatile uint8 Char;
	/*~T*/
	Io_Os_RemovePeriodicTask((Io_Os_FuncType) Io_Lcd_PutStringTask, 0);
	/*~T*/

	/*~I:118*/
	if ((*LcdStringPtr != '\0') || (*(LcdStringPtr) == '\n'))
		/*~-1*/
	{
		/*~T*/
		Char = *LcdStringPtr++;
		/*~T*/
		/* print string on lcd (no auto linefeed)*/
		Io_Lcd_PutChar(Char);
		/*~T*/
		/* Display Char by Char by inserting Io_Lcd_PutChar function in OS in order to avoid Delay function  */
		Io_Os_InsertPeriodicTask((Io_Os_FuncType)Io_Lcd_PutStringTask, 0, 1, 1, IO_OS_PRIORITY_HIGH);
		/*~-1*/
	}
	/*~O:I118*/
	/*~-2*/
	else
	{
		/*~A:119*/
		/*~+:Reset LCD semaphore*/
		/*~T*/
		Io_Int_DisableInterrupts();
		/*~T*/
		/* Set LCD is free */
		Io_Lcd_Semaphore = 0;
		/*~T*/
		Io_Int_EnableInterrupts();
		/*~E:A119*/
		/*~-1*/
	}
	/*~E:I118*/
	/*~-1*/
}
/*~E:F117*/
/*~T*/

/*~F:120*/
void Io_Lcd_PutStringOs(const uint8 *StringPtr)

/*~-1*/
{
	/*~I:121*/
	if (Io_Lcd_Semaphore == 0)
		/*~-1*/
	{
		/*~A:122*/
		/*~+:Set LCD semaphore*/
		/*~T*/
		Io_Int_DisableInterrupts();
		/*~T*/
		/* Set LCD is busy */
		Io_Lcd_Semaphore = 1;
		/*~T*/
		Io_Int_EnableInterrupts();
		/*~E:A122*/
		/*~T*/
		LcdStringPtr = StringPtr;
		/*~T*/
		/* Display Char by Char by inserting Io_Lcd_PutChar function in OS in order to avoid Delay function  */
		Io_Os_InsertPeriodicTask((Io_Os_FuncType)Io_Lcd_PutStringTask, 0, 1, 0, IO_OS_PRIORITY_HIGH);
		/*~-1*/
	}
	/*~O:I121*/
	/*~-2*/
	else
	{
		/*~T*/
		/* LCD is busy. Insert an OS task to wait for availability. */
		/*~-1*/
	}
	/*~E:I121*/
	/*~-1*/
}
/*~E:F120*/
/*~T*/

/*~E:A116*/
/*~A:123*/
/*~+:Io_Lcd_Init*/
/*~T*/
/*************************************************************************
Initialize display and select type of cursor 
Input:    dispAttr LCD_DISP_OFF            display off
                   LCD_DISP_ON             display on, cursor off
                   LCD_DISP_ON_CURSOR      display on, cursor on
                   LCD_DISP_CURSOR_BLINK   display on, cursor on flashing
Returns:  none
 *************************************************************************/

/*~T*/

/*~F:124*/
void Io_Lcd_Init(uint8 DispAttr)
/*~-1*/
{
	/*~T*/
	/* Initialize LCD to 4 bit I/O mode    */
	/*~A:125*/
	/*~+:Reset LCD semaphore*/
	/*~T*/
	Io_Int_DisableInterrupts();
	/*~T*/
	/* Set LCD is free */
	Io_Lcd_Semaphore = 0;
	/*~T*/
	Io_Int_EnableInterrupts();
	/*~E:A125*/
	/*~T*/
	Io_Dio_SetPinLevel(IO_LCD_E_PIN, IO_LCD_LEVEL_LOW);

	Io_Dio_SetPinLevel(IO_LCD_RW_PIN, IO_LCD_LEVEL_LOW);
	Io_Dio_SetPinLevel(IO_LCD_RS_PIN, IO_LCD_LEVEL_LOW);

	Io_Dio_SetPinLevel(IO_LCD_DATA3_PIN, IO_LCD_LEVEL_LOW);
	Io_Dio_SetPinLevel(IO_LCD_DATA2_PIN, IO_LCD_LEVEL_LOW);

	Io_Dio_SetPinLevel(IO_LCD_DATA1_PIN, IO_LCD_LEVEL_LOW);
	Io_Dio_SetPinLevel(IO_LCD_DATA0_PIN, IO_LCD_LEVEL_LOW);

	/*~T*/
	//Io_Tim_DelayUs(10000);
	//Io_Tim_DelayUs(10000);
	//Io_Tim_DelayUs(10000);
	//Io_Tim_DelayUs(10000);
	//Io_Tim_DelayUs(10000);
	//Io_Tim_DelayUs(10000);
	Io_Tim_DelayUs(50000);        /* wait 50ms or more after power-on       */
	/* initial write to lcd is 8bit */
	Io_Dio_SetPinLevel(IO_LCD_DATA1_PIN, IO_LCD_LEVEL_HIGH);
	Io_Dio_SetPinLevel(IO_LCD_DATA0_PIN, IO_LCD_LEVEL_HIGH);

	/*~T*/
	Io_Lcd_EHigh();
	Io_Lcd_EDelay();
	Io_Lcd_ELow();

	/*~T*/
	Io_Tim_DelayUs(5000);         /* delay, busy flag can't be checked here */

	/*~T*/
	Io_Lcd_EHigh();
	Io_Lcd_EDelay();
	Io_Lcd_ELow();

	/*~T*/
	Io_Tim_DelayUs(64);           /* delay, busy flag can't be checked here */

	/*~T*/
	Io_Lcd_EHigh();
	Io_Lcd_EDelay();
	Io_Lcd_ELow();

	/*~T*/
	Io_Tim_DelayUs(64);           /* delay, busy flag can't be checked here */

	/*~T*/
	/* now configure for 4bit mode */
	Io_Dio_SetPinLevel(IO_LCD_DATA0_PIN, IO_LCD_LEVEL_LOW);

	/*~T*/
	Io_Lcd_EHigh();
	Io_Lcd_EDelay();
	Io_Lcd_ELow();

	/*~T*/
	Io_Tim_DelayUs(64);           /* some displays need this additional delay */

	/*~A:126*/
	/*~+:4 LINES MODE*/
	/*~I:127*/
#if IO_LCD_KS0073_4LINES_MODE
	/*~T*/
	/* Display with KS0073 controller requires special commands for enabling 4 line mode */
	Io_Lcd_Command(IO_LCD_KS0073_EXTENDED_FUNCTION_REGISTER_ON);
	Io_Lcd_Command(IO_LCD_KS0073_4LINES_MODE);
	Io_Lcd_Command(IO_LCD_KS0073_EXTENDED_FUNCTION_REGISTER_OFF);

	/*~O:I127*/
	/*~-1*/
#else
	/*~T*/
	/* function set: display lines  */
	Io_Lcd_Command(IO_LCD_FUNCTION_DEFAULT);
	/*~-1*/
#endif
	/*~E:I127*/
	/*~E:A126*/
	/*~T*/
	Io_Lcd_Command(IO_LCD_DISP_OFF);           /* display off                  */
	Io_Lcd_ClrScr();                           /* display clear                */
	Io_Lcd_Command(IO_LCD_MODE_DEFAULT);       /* set entry mode               */
	Io_Lcd_Command(DispAttr);                  /* display/cursor control       */

	/*~-1*/
}
/*~E:F124*/
/*~E:A123*/
/*~A:128*/
/*~+:Io_Lcd_GetStatus*/
/*~F:129*/
uint8 Io_Lcd_GetStatus(void)
/*~-1*/
{
	/*~T*/
	return Io_Lcd_Semaphore;
	/*~-1*/
}
/*~E:F129*/
/*~E:A128*/
/*~A:130*/
/*~+:Io_Lcd_DisplayOnTask*/
/*~T*/
const uint8 *LcdDsplayStringPtr;
uint8 LcdDisplayLine;
uint8 LcdDisplayState = 0;

/*~F:131*/
uint8 Io_Lcd_DisplayOnTask(uint8* StringAddr, uint8 line)
/*~-1*/
{
	/*~I:132*/
	if (LcdDisplayState == 0)
		/*~-1*/
	{
		/*~T*/
		Io_Os_RemovePeriodicTask((Io_Os_FuncType) Io_Lcd_Display_Task, 0);
		/*~T*/
		LcdDsplayStringPtr = StringAddr;
		/*~T*/
		LcdDisplayLine = line;
		/*~T*/
		LcdDisplayState = 1;
		/*~T*/
		Io_Os_InsertPeriodicTask((Io_Os_FuncType)Io_Lcd_Display_Task, 0, 1, 1, IO_OS_PRIORITY_HIGH);
		/*~-1*/
	}
	/*~E:I132*/
	/*~-1*/
}
/*~E:F131*/
/*~F:133*/
uint8 Io_Lcd_Display_Task(void)
/*~-1*/
{
	/*~T*/
	uint8 Char;
	/*~T*/
	Io_Os_RemovePeriodicTask((Io_Os_FuncType) Io_Lcd_Display_Task, 0);
	/*~C:134*/
	switch (LcdDisplayState)
	/*~-1*/
	{
	/*~F:135*/
	case 1:
		/*~-1*/
	{
		/*~I:136*/
		if (LcdDisplayLine == IO_LCD_START_LINE1)
			/*~-1*/
		{
			/*~T*/
			Io_Lcd_Command (0x80);
			/*~-1*/
		}
		/*~O:I136*/
		/*~-2*/
		else
		{
			/*~T*/
			Io_Lcd_Command (0xC0);
			/*~-1*/
		}
		/*~E:I136*/
		/*~T*/
		LcdDisplayState = 2;
		/*~T*/
		Io_Os_InsertPeriodicTask((Io_Os_FuncType)Io_Lcd_Display_Task, 0, 1, 1, IO_OS_PRIORITY_HIGH);
		/*~T*/
		break;
		/*~-1*/
	}
	/*~E:F135*/
	/*~F:137*/
	case 2:
		/*~-1*/
	{
		/*~T*/
		Char = *LcdDsplayStringPtr++;
		/*~I:138*/
		if (Char== '\n')
			/*~-1*/
		{
			/*~T*/
			Io_Lcd_Command (0xC0);
			/*~-1*/
		}
		/*~O:I138*/
		/*~-2*/
		else
		{
			/*~I:139*/
			if (Char == 0xFF)
				/*~-1*/
			{
				/*~T*/
				LcdDisplayState = 0;
				/*~-1*/
			}
			/*~O:I139*/
			/*~-2*/
			else
			{
				/*~T*/
				Io_Lcd_PutChar(Char);
				/*~T*/
				Io_Os_InsertPeriodicTask((Io_Os_FuncType)Io_Lcd_Display_Task, 0, 1, 1, IO_OS_PRIORITY_HIGH);
				/*~-1*/
			}
			/*~E:I139*/
			/*~-1*/
		}
		/*~E:I138*/
		/*~T*/
		break;
		/*~-1*/
	}
	/*~E:F137*/
	/*~T*/
	return LcdDisplayState;
	/*~-1*/
	}
	/*~E:C134*/
	/*~T*/

	/*~-1*/
}
/*~E:F133*/
/*~E:A130*/
/*~T*/

/*~E:A59*/
/*~E:A7*/
