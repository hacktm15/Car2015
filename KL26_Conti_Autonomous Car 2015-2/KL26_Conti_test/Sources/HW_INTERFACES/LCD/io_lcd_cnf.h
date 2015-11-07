/*~-1*/
/*~XSF_LANGUAGE: C/C++*/
/*~I:1*/
#ifndef IO_LCD_CNF_H
/*~T*/
#define IO_LCD_CNF_H
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

$Log: io_lcd_cnf.h  $

 ****************************************************************************/
/* ## Module Header End [328f418b-489c-4745-80e2-b2a3fbf9452a] */
/*~E:A2*/
/*~A:3*/
/*~+:Includes*/
/*~T*/
#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"

#include "io_lcd.h"
/*~E:A3*/
/*~A:4*/
/*~+:Macro Defines*/
/*~T*/
/* Defines */
/*~A:5*/
/*~+:Definitions for MCU Clock Frequency*/
/*~T*/
/** 
 *  @name  Definitions for MCU Clock Frequency
 *  Adapt the MCU clock frequency in Hz to your target. 
 */

/*~T*/
/* #define IO_LCD_CONTROLLER_IS_TRICORE    0  //use TRICORE controller */
/*~T*/

/*~T*/
#define IO_LCD_CONTROLLER_IS_PIC    1  //use PIC controller
/*~E:A5*/
/*~A:6*/
/*~+:Definition for LCD controller type*/
/*~T*/
/**
 * @name  Definition for LCD controller type
 * Use 0 for HD44780 controller, change to 1 for displays with KS0073 controller.
 */
#define IO_LCD_CONTROLLER_KS0073 0  /**< Use 0 for HD44780 controller, 1 for KS0073 controller */


/*~T*/
/** 
 *  @name  Definitions for Display Size 
 *  Change these definitions to adapt setting to your display
 */
#define IO_LCD_LINES           2     /**< number of visible lines of the display */
#define IO_LCD_LINE_LENGTH  0x40     /**< internal line length of the display    */
#define IO_LCD_START_LINE1  0x80     /**< DDRAM address of first char of line 1 */
#define IO_LCD_START_LINE2  0xC0     /**< DDRAM address of first char of line 2 */

#define IO_LCD_START_LINE3  0x10     /**< DDRAM address of first char of line 3 */
#define IO_LCD_START_LINE4  0x50     /**< DDRAM address of first char of line 4 */


/*~T*/
#define IO_LCD_WRAP_LINES      0     /**< 0: no wrap, 1: wrap at end of visibile line */
#define IO_LCD_DISP_LENGTH    16     /**< visibles characters per line of the display */

/*~E:A6*/
/*~A:7*/
/*~+:Definitions for 4-bit IO mode*/
/*~T*/
/**
 *  @name Definitions for 4-bit IO mode
 *  The four LCD data lines and the three control lines RS, RW, E can be on the 
 *  same port or on different ports. 
 *  Normally the four data lines should be mapped to bit 0..3 on one port, but it
 */

/*~T*/
#define IO_LCD_DATA0_PIN    IO_PCS_P0E_02            /**< port-pin for 4bit data bit 0  */
#define IO_LCD_DATA1_PIN    IO_PCS_P0E_03            /**< port-pin for 4bit data bit 1  */
#define IO_LCD_DATA2_PIN    IO_PCS_P0E_04            /**< port-pin for 4bit data bit 2  */
#define IO_LCD_DATA3_PIN    IO_PCS_P0E_05            /**< port-pin for 4bit data bit 3  */

/*~T*/
#define IO_LCD_RS_PIN       IO_PCS_P0B_08            /**< port-pin  for RS line         */

/*~T*/
#define IO_LCD_RW_PIN       IO_PCS_P0B_09            /**< port-pin  for RW line         */

/*~T*/
#define IO_LCD_E_PIN        IO_PCS_P0B_10            /**< port-pin  for Enable line     */

/*~E:A7*/
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
/*~T*/

/*~E:A14*/
/*~E:A13*/
/*~-1*/
#endif
/*~E:I1*/
