/****************************************************************************

COPYRIGHT (C) $Date: 2012/05/10 14:20:43CEST $
$CompanyInfo:  $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_func.h $

$Author: unknown $

 ****************************************************************************/

#ifndef IO_FUNC_H
#define IO_FUNC_H


/** Incldues **/

#include "MKL26Z4.h"
#include "PLATFORM_TYPES/std_types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "PLATFORM_TYPES/platform_types.h"

/** end of Incldues **/

/** Defines **/

#define IO_FUNC_PARITY_EVEN                            ((uint8)(0x00)) /**< selected parity is even */
#define IO_FUNC_PARITY_ODD                             ((uint8)(0x01)) /**< selected parity is odd */

/** end of Defines **/

/** Structure Typedefs and Nested Structures **/

typedef struct Io_Func_RamBuffer_tag Io_Func_RamBuffer;

/* DESCRIPTION: This class shall represent the allocation buffer descriptor structure.
 * This structure is meant to be in ROM memory, therefore consider that
 * the allocation pointer must be provided from each user (e.g.: bss, dma ...)
 */
struct Io_Func_RamBuffer_tag
{
	uint32 * PtrStart;                               /**< This attribute contains a pointer to the buffer start address aligned to 4byte. */
	uint32 ** PtrPtrAlloc;                           /**< This attribute contains a pointer to the allocation pointer which finally points to an address which is aligned to 4byte. */
	uint32 Size;                                     /**< This attribute shall carry the size information of the current buffer. The unit shall be 4bytes, means a value of 1 = 4bytes, 8 = 32bytes. */
};

/** end of Structure Typedefs and Nested Structures **/

/** External Interfaces prototypes **/

/* FUNCTION NAME: Io_Func_ShlU8
 * DESCRIPTION: Shifts left an uint8 number with the no. of bits given.
 */
//extern uint8 	Io_Func_ShlU8(uint8 In, uint8 Cnt);

/* FUNCTION NAME: Io_Func_ShlU16
 * DESCRIPTION: Shifts left an uint16 number with the no. of bits given.
 */
extern uint16 	Io_Func_ShlU16(uint16 In, uint8 Cnt);

/* FUNCTION NAME: Io_Func_ShlU32
 * DESCRIPTION: Shifts left an uint32 number with the no. of bits given.
 */
extern uint32 	Io_Func_ShlU32(uint32 In, uint8 Cnt);

/* FUNCTION NAME: Io_Func_ShlU64
 * DESCRIPTION: Shifts left an uint64 number with the no. of bits given.
 */
//extern uint64 Io_Func_ShlU64(uint64 In, uint8 Cnt);

/* FUNCTION NAME: Io_Func_ShrU8
 * DESCRIPTION: Shifts right an uint8 number with the no. of bits given.
 */
//extern uint8 	Io_Func_ShrU8(uint8 In, uint8 Cnt);

/* FUNCTION NAME: Io_Func_ShrU16
 * DESCRIPTION: Shifts right an uint16 number with the no. of bits given.
 */
extern uint16 	Io_Func_ShrU16(uint16 In, uint8 Cnt);

/* FUNCTION NAME: Io_Func_ShrU32
 * DESCRIPTION: Shifts right an uint32 number with the no. of bits given.
 */
extern uint32	Io_Func_ShrU32(uint32 In, uint8 Cnt);

/* FUNCTION NAME: Io_Func_ShrU64
 * DESCRIPTION: Shifts right an uint64 number with the no. of bits given.
 */
//extern uint64	Io_Func_ShrU64(uint64 In, uint8 Cnt);

/* FUNCTION NAME: Io_Func_InvU8
 * DESCRIPTION: Returns the uint8 complement (always positive) of an uint8 parameter.
 */
//extern uint8 	Io_Func_InvU8(uint8 In);

/* FUNCTION NAME: Io_Func_InvU16
 * DESCRIPTION: Returns the uint16 complement (always positive) of an uint16 parameter.
 */
//extern uint16 Io_Func_InvU16(uint16 In);

/* FUNCTION NAME: Io_Func_InvU32
 * DESCRIPTION: Returns the uint32 complement (always positive) of an uint32 parameter.
 */
//extern uint32 Io_Func_InvU32(uint32 In);

/* FUNCTION NAME: Io_Func_MinF32
 * DESCRIPTION: Returns the minimum between two given float numbers.
 */
extern float32 	Io_Func_MinF32(float32 Param1, float32 Param2);

/* FUNCTION NAME: Io_Func_MaxF32
 * DESCRIPTION: Returns the maximum between two given float numbers.
 */
extern float32 	Io_Func_MaxF32(float32 Param1, float32 Param2);

/** end of External Interfaces prototypes **/

#endif
