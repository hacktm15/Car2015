/*~-1*/
/*~XSF_LANGUAGE: C/C++*/
/*~I:1*/
#ifndef IO_LCD_H
/*~T*/
#define IO_LCD_H
/*~A:2*/
/*~+:Module Header*/
/*~T*/
/* ## Module Header Start [328f418b-489c-4745-80e2-b2a3fbf9452a] */
/****************************************************************************

COPYRIGHT (C) $Date: 2012/05/09 17:46:33CEST $
$CompanyInfo:  $
ALL RIGHTS RESERVED.                                                 

The reproduction, transmission or use of this document or its contents is  
not permitted without express written authority.                           
Offenders will be liable for damages. All rights, including rights created 
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$Log: io_lcd.h  $

 ****************************************************************************/
/* ## Module Header End [328f418b-489c-4745-80e2-b2a3fbf9452a] */
/*~E:A2*/
/*~A:3*/
/*~+:Includes*/
/*~T*/
#include "MKL26Z4.h"
#include "PLATFORM_TYPES/std_types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "PLATFORM_TYPES/platform_types.h"
#include "SYSTEM/io_sys.h"
/*~E:A3*/
/*~A:4*/
/*~+:Macro Defines*/
/*~T*/
/* Defines */
/*~T*/
/**
 *  @name Definitions for LCD command instructions
 *  The constants define the various LCD controller instructions which can be passed to the 
 *  function lcd_command(), see HD44780 data sheet for a complete description.
 */
/* instruction register bit positions, see HD44780U data sheet */
#define IO_LCD_CLR               0      /* DB0: clear display                  */
#define IO_LCD_HOME              1      /* DB1: return to home position        */
#define IO_LCD_ENTRY_MODE        2      /* DB2: set entry mode                 */
#define IO_LCD_ENTRY_INC         1      /*   DB1: 1=increment, 0=decrement     */
#define IO_LCD_ENTRY_SHIFT       0      /*   DB2: 1=display shift on           */
#define IO_LCD_ON                3      /* DB3: turn lcd/cursor on             */
#define IO_LCD_ON_DISPLAY        2      /*   DB2: turn display on              */
#define IO_LCD_ON_CURSOR         1      /*   DB1: turn cursor on               */
#define IO_LCD_ON_BLINK          0      /*     DB0: blinking cursor ?          */
#define IO_LCD_MOVE              4      /* DB4: move cursor/display            */
#define IO_LCD_MOVE_DISP         3      /*   DB3: move display (0-> cursor) ?  */
#define IO_LCD_MOVE_RIGHT        2      /*   DB2: move right (0-> left) ?      */
#define IO_LCD_FUNCTION          5      /* DB5: function set                   */
#define IO_LCD_FUNCTION_8BIT     4      /*   DB4: set 8BIT mode (0->4BIT mode) */
#define IO_LCD_FUNCTION_2LINES   3      /*   DB3: two lines (0->one line)      */
#define IO_LCD_FUNCTION_10DOTS   2      /*   DB2: 5x10 font (0->5x7 font)      */
#define IO_LCD_CGRAM             6      /* DB6: set CG RAM address             */
#define IO_LCD_DDRAM             7      /* DB7: set DD RAM address             */
#define IO_LCD_BUSY              7      /* DB7: LCD is busy                    */

/*~T*/
/* set entry mode: display shift on/off, dec/inc cursor move direction */
#define IO_LCD_ENTRY_DEC            0x04   /* display shift off, dec cursor move dir */
#define IO_LCD_ENTRY_DEC_SHIFT      0x05   /* display shift on,  dec cursor move dir */
#define IO_LCD_ENTRY_INC_           0x06   /* display shift off, inc cursor move dir */
#define IO_LCD_ENTRY_INC_SHIFT      0x07   /* display shift on,  inc cursor move dir */

/*~T*/

/* display on/off, cursor on/off, blinking char at cursor position */
#define IO_LCD_DISP_OFF             0x08   /* display off                            */
#define IO_LCD_DISP_ON              0x0C   /* display on, cursor off                 */
#define IO_LCD_DISP_ON_BLINK        0x0D   /* display on, cursor off, blink char     */
#define IO_LCD_DISP_ON_CURSOR       0x0E   /* display on, cursor on                  */
#define IO_LCD_DISP_ON_CURSOR_BLINK 0x0F   /* display on, cursor on, blink char      */

/*~T*/

/* move cursor/shift display */
#define IO_LCD_MOVE_CURSOR_LEFT     0x10   /* move cursor left  (decrement)          */
#define IO_LCD_MOVE_CURSOR_RIGHT    0x14   /* move cursor right (increment)          */
#define IO_LCD_MOVE_DISP_LEFT       0x18   /* shift display left                     */
#define IO_LCD_MOVE_DISP_RIGHT      0x1C   /* shift display right                    */


/*~T*/
/* function set: set interface data length and number of display lines */
#define IO_LCD_FUNCTION_4BIT_1LINE  0x20   /* 4-bit interface, single line, 5x7 dots */
#define IO_LCD_FUNCTION_4BIT_2LINES 0x28   /* 4-bit interface, dual line,   5x7 dots */
#define IO_LCD_FUNCTION_8BIT_1LINE  0x30   /* 8-bit interface, single line, 5x7 dots */
#define IO_LCD_FUNCTION_8BIT_2LINES 0x38   /* 8-bit interface, dual line,   5x7 dots */

/*~T*/
#define IO_LCD_LEVEL_LOW            0x0    /* PIN LEVEL LOW */
#define IO_LCD_LEVEL_HIGH           0x1    /* PIN LEVEL HIGH*/ 
/*~T*/
#define IO_LCD_WRITE_INSTR          0x0    /* write instr to LCD controller */
#define IO_LCD_WRITE_DATA           0x1    /* write data to LCD controller */
/*~T*/
#define IO_LCD_READ_ADDR            0x0    /* read busy / addr.counter from LCD controller */
#define IO_LCD_READ_DATA            0x1    /* read data from LCD controller */
/*~T*/

/*~I:5*/
#if IO_LCD_LINES==1
/*~T*/
#define IO_LCD_FUNCTION_DEFAULT    IO_LCD_FUNCTION_4BIT_1LINE
/*~O:I5*/
/*~-1*/
#else
/*~T*/
#define IO_LCD_FUNCTION_DEFAULT    IO_LCD_FUNCTION_4BIT_2LINES 
/*~-1*/
#endif
/*~E:I5*/
/*~I:6*/
#if IO_LCD_CONTROLLER_KS0073
/*~I:7*/
#if IO_LCD_LINES==4
/*~T*/
#define IO_LCD_KS0073_EXTENDED_FUNCTION_REGISTER_ON  0x24   /* |0|010|0100 4-bit mode extension-bit RE = 1 */
#define IO_LCD_KS0073_EXTENDED_FUNCTION_REGISTER_OFF 0x20   /* |0|000|1001 4 lines mode */
#define IO_LCD_KS0073_4LINES_MODE                    0x09   /* |0|001|0000 4-bit mode, extension-bit RE = 0 */

/*~-1*/
#endif
/*~E:I7*/
/*~-1*/
#endif
/*~E:I6*/
/*~T*/

#define IO_LCD_MODE_DEFAULT         ((1<<IO_LCD_ENTRY_MODE) | (1<<IO_LCD_ENTRY_INC) )

/*~T*/

/*~E:A4*/
/*~A:8*/
/*~+:Structure Typedefs*/
/*~T*/

/*~E:A8*/
/*~A:9*/
/*~+:Type definitions*/
/*~T*/

/*~E:A9*/
/*~A:10*/
/*~+:Nested structures*/
/*~T*/
/* Nested Structures */
/*~E:A10*/
/*~A:11*/
/*~+:Attributes*/
/*~A:12*/
/*~+:Variables and Constants*/
/*~T*/
/* Variables and Constants */
/*~T*/

/*~E:A12*/
/*~E:A11*/
/*~A:13*/
/*~+:Operations*/
/*~A:14*/
/*~+:Public operations*/
/*~T*/
/* Public operations */
/*~A:15*/
/*~+:Io_Lcd_Init                               Initialize display and select type of cursor*/
/*~T*/
/**
 @brief    Initialize display and select type of cursor
 @param    dispAttr \b LCD_DISP_OFF display off\n
                    \b LCD_DISP_ON display on, cursor off\n
                    \b LCD_DISP_ON_CURSOR display on, cursor on\n
                    \b LCD_DISP_ON_CURSOR_BLINK display on, cursor on flashing             
 @return  none
 */
extern void Io_Lcd_Init(uint8 DispAttr);

/*~E:A15*/
/*~A:16*/
/*~+:Io_Lcd_ClrScr                             Set cursor to home position*/
/*~T*/
/**
 @brief    Clear display and set cursor to home position
 @param    void                                        
 @return   none
 */
extern void Io_Lcd_ClrScr(void);

/*~E:A16*/
/*~A:17*/
/*~+:Io_Lcd_ClrScrOs                           Set cursor to home position by using OS*/
/*~T*/
/**
 @brief    Clear display and set cursor to home position
 @param    void                                        
 @return   none
 */
extern void Io_Lcd_ClrScrOs(void);

/*~E:A17*/
/*~A:18*/
/*~+:Io_Lcd_Home                               Set cursor to home position*/
/*~T*/
/**
 @brief    Set cursor to home position
 @param    void                                        
 @return   none
 */
extern void Io_Lcd_Home(void);

/*~E:A18*/
/*~A:19*/
/*~+:Io_Lcd_HomeOs                             Set cursor to home position by using OS*/
/*~T*/
/**
 @brief    Set cursor to home position
 @param    void                                        
 @return   none
 */
extern void Io_Lcd_HomeOs(void);

/*~E:A19*/
/*~A:20*/
/*~+:Io_Lcd_GoToXy                             Set cursor to specified position					-	NOT_USED*/
/*~T*/
/**
 @brief    Set cursor to specified position

 @param    x horizontal position\n (0: left most position)
 @param    y vertical position\n   (0: first line)
 @return   none
 */
//extern void Io_Lcd_GoToXy(uint8 X, uint8 Y);

/*~E:A20*/
/*~A:21*/
/*~+:Io_Lcd_PutChar                            Display character at current cursor position*/
/*~T*/
/**
 @brief    Display character at current cursor position
 @param    c character to be displayed                                       
 @return   none
 */
extern void Io_Lcd_PutChar(uint32 Char);

/*~E:A21*/
/*~A:22*/
/*~+:Io_Lcd_PutString                          Display string without auto linefeed*/
/*~T*/
/**
 @brief    Display string without auto linefeed
 @param    s string to be displayed                                        
 @return   none
 */
extern void Io_Lcd_PutString(const uint8 *StringPtr);

/*~E:A22*/
/*~A:23*/
/*~+:Io_Lcd_PutStringOs                        Display string without auto linefeed by using OS*/
/*~T*/
/**
 @brief    Display string without auto linefeed
 @param    s string to be displayed                                        
 @return   none
 */
extern void Io_Lcd_PutStringOs(const uint8 *StringPtr);

/*~E:A23*/
/*~A:24*/
/*~+:Io_Lcd_Command                            Send LCD controller instruction command*/
/*~T*/
/**
 @brief    Send LCD controller instruction command
 @param    cmd instruction to send to LCD controller, see HD44780 data sheet
 @return   none
 */
extern void Io_Lcd_Command (uint8 Cmd);

/*~E:A24*/
/*~A:25*/
/*~+:Io_Lcd_Data                               Send data byte to LCD controller					-	NOT_USED*/
/*~T*/
/**
 @brief    Send data byte to LCD controller 

 Similar to lcd_putc(), but without interpreting LF
 @param    data byte to send to LCD controller, see HD44780 data sheet
 @return   none
 */
//extern void Io_Lcd_Data (uint8 Data);

/*~E:A25*/
/*~A:26*/
/*~+:Io_Lcd_Delay                              Perform a delay of XX us                */
/*~T*/
extern void Io_Lcd_Delay(uint16 Us);
/*~E:A26*/
/*~A:27*/
/*~+:Io_Lcd_GetStatus						  Returns Semaphore/Busy status flag*/
/*~T*/
extern uint8 Io_Lcd_GetStatus(void);
/*~E:A27*/
/*~T*/
extern uint8 Io_Lcd_DisplayOnTask(uint8* StringAddr, uint8 line);
extern uint8 Io_Lcd_Display_Task(void);

/*~E:A14*/
/*~E:A13*/
/*~-1*/
#endif
/*~E:I1*/
