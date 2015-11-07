
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/****************************************************************************
 * COPYRIGHT (C) CONTINENTAL AUTOMOTIVE GMBH 2010
 * ALL RIGHTS RESERVED.
 * 
 * The reproduction, transmission or use of this document or its
 * contents is not permitted without express written authority.
 * Offenders will be liable for damages. All rights, including rights
 * created by patent grant or registration of a utility model or design,
 * are reserved.
 *---------------------------------------------------------------------------
 * Purpose:    XXXXXX
 * 
 * Processor:  independent
 * Tool chain: independent
 * Filename:   $Workfile:   Platform_Types.h  $
 * Revision:   $Revision:   1.2  $
 * Author:     $Author:   uidm3647  $
 * Date:       $Date:   Jul 13 2010 16:29:36  $
 * Changes:    $Log:   K:/LIB01/0_GEN/PI/TC1/code/Platform_Types.h_v  $
 * 
 *    Rev 1.2   Jul 13 2010 16:29:36   uidm3647
 * TC1-SWCN-18: Update in AutoSAR headers for Tricore (Platform_Types.h)
 * 
 ****************************************************************************/

/** The standard AUTOSAR type boolean shall only be used in conjunction with the standard symbols TRUE and FALSE. For value assignments of variables of type boolean no arithmetic or logical operators (+, ++, -, --, *, /, \, <<, 
>>, !, ~) must be used. The only allowed form of assignment is
boolean var;
.
var = TRUE;
var = FALSE; */
//typedef unsigned char boolean;

typedef signed char sint8;

/** 8bit number 0..255 */
typedef unsigned char uint8;

typedef signed short sint16;

typedef unsigned short uint16;

typedef signed long sint32;

typedef unsigned long uint32;

typedef unsigned long uint8_least;

typedef unsigned long uint16_least;

typedef unsigned long uint32_least;

typedef signed long sint8_least;

typedef signed long sint16_least;

typedef signed long sint32_least;

typedef float float32;

typedef double float64;

/** Defines **/

#define CPU_TYPE_8                                       8            /**< Indicates a 8 bit processor */
#define CPU_TYPE_16                                      16           /**< Indicates a 16 bit processor */
#define CPU_TYPE_32                                      32           /**< Indicates a 32 bit processor */
#define MSB_FIRST                                        0            /**< The most significant bit is the first bit of the bit sequence. */
#define LSB_FIRST                                        1            /**< The least significant bit is the first bit of the bit sequence. */
#define HIGH_BYTE_FIRST                                  0            /**< Within a uint16, the high byte is located before the low byte. */
#define LOW_BYTE_FIRST                                   1            /**< Within a uint16, the low byte is located before the high byte. */
#define CPU_TYPE                                         CPU_TYPE_32  /**<  */
#define CPU_BIT_ORDER                                    LSB_FIRST    /**<  */
#define CPU_BYTE_ORDER                                   LOW_BYTE_FIRST /**<  */

/** end of Defines **/

/* Macro Type Name: BOOLEAN_STATES */
/** In case of in-built compiler support of the symbols, redefinitions shall be avoided using a conditional check
The symbols TRUE and FALSE shall be defined as follows:
These symbols shall only be used in conjunction with the boolean type defined in Platform_Types.h(This header file) */
/* ## Macro Type Declaration Start [fada20d0-0055-4a42-a5df-f5f8dfd30960] */
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
/* ## Macro Type Declaration End [fada20d0-0055-4a42-a5df-f5f8dfd30960] */

#endif
