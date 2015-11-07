
#ifndef STD_TYPES_H
#define STD_TYPES_H

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
 * Filename:   $Workfile:   Std_Types.h  $
 * Revision:   $Revision:   1.2  $
 * Author:     $Author:   uidm3647  $
 * Date:       $Date:   Jul 13 2010 16:33:26  $
 * Changes:    $Log:   K:/LIB01/0_GEN/PI/TCX/code/Std_Types.h_v  $
 * 
 *    Rev 1.2   Jul 13 2010 16:33:26   uidm3647
 * TCX-SWCN-5: Update in generic AutoSAR headers (Compiler_Cfg.h and Std_Types.h)
 * 
 ****************************************************************************/

#include "compiler.h"
#include "Platform_Types.h"

typedef struct Std_VersionInfoType_tag Std_VersionInfoType;

/** The Std_ReturnType shall normally be used with value E_OK or E_NOT_OK. If those return values are not sufficient user specific values can be defined by using the 6 least specific bits. Bit 7 and Bit 8 are reserved and defined by the RTE specification. */
typedef uint8 Std_ReturnType;

/** This type shall be used to request the version of a BSW module using the <Module name>_GetVersionInfo()function */
struct Std_VersionInfoType_tag
{
	uint16 vendorID;
	uint16 moduleID;
	uint8 sw_major_version;
	uint8 sw_minor_version;
	uint8 sw_patch_version;
};

/** Defines **/

#define STD_HIGH                                         0x01         /**< Physical state 5V or 3.3V */
#define STD_LOW                                          0x00         /**< Physical state 0V */
#define STD_ACTIVE                                       0x01         /**< Logical state active */
#define STD_IDLE                                         0x00         /**< Logical state idle */
#define STD_ON                                           0x01         /**<  */
#define STD_OFF                                          0x00         /**<  */

/** end of Defines **/

/* Macro Types */

/* Macro Type Name: STATUSTYPEDEFINED */
/**  */
/* ## Macro Type Declaration Start [1b5f0946-57d1-451c-83c3-e0a6fa6f0717] */

#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
#define E_OK 0x00
typedef unsigned char StatusType; /* OSEK compliance */
#endif
#define E_NOT_OK 0x01
/* ## Macro Type Declaration End [1b5f0946-57d1-451c-83c3-e0a6fa6f0717] */

#endif
