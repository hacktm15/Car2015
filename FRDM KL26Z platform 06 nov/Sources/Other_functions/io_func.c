/****************************************************************************

COPYRIGHT (C) $Date: Nov 3, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_func_main.c $

$Author: PES contribution $

 ****************************************************************************/

/** Includes **/

#include "io_func.h"

/** end of Includes **/

/** Local Functions prototypes **/

	// None so far.

/** end Local Functions prototypes **/

/** Global variables and constants **/

	// None so far.

/** end of Global variables and constants **/

/** Functions implementation **/

	/** External Interfaces implementation **/

/* This operation shall perform a bitwise shift by <cnt> bits towards MSB.
 * @param In input
 * @param Cnt number of counts to rotate:
 * 0..7
 * @return return shift<in>
 */
#ifdef NOT_USED

uint8 Io_Func_ShlU8(uint8 In, uint8 Cnt)
{
	return ( (uint8)(In << Cnt) );
}

#endif

/* This operation shall perform a bitwise shift by <cnt> bits towards MSB.
 * @param In input
 * @param Cnt number of counts to rotate:
 * 0..15
 * @return return shift<in>
 */
uint16 Io_Func_ShlU16(uint16 In, uint8 Cnt)
{
	return ( (uint16)(In << Cnt) );
}

/* This operation shall perform a bitwise shift by <cnt> bits towards MSB.
 * @param In input
 * @param Cnt number of counts to rotate:
 * 0..31
 * @return return shift<in>
 */
uint32 Io_Func_ShlU32(uint32 In, uint8 Cnt)
{
	return ( (uint32)(In << Cnt) );
}

/* This operation shall perform a bitwise shift by <cnt> bits towards MSB.
 * @param In input
 * @param Cnt number of counts to rotate:
 * 0..63
 * @return return shift<in>
 */
#ifdef NOT_USED

uint64 Io_Func_ShlU64(uint64 In, uint8 Cnt)
{
	return ( (uint64)(In << Cnt) );
}

#endif

/* This operation shall perform a bitwise shift by <cnt> bits towards LSB.
 * @param In input
 * @param Cnt number of counts to rotate:
 * 0..7
 * @return return shift<in>
 */
#ifdef NOT_USED

uint8 Io_Func_ShrU8(uint8 In, uint8 Cnt)
{
	return ( (uint8)(In >> Cnt) );
}

#endif

/* This operation shall perform a bitwise shift by <cnt> bits towards LSB.
 * @param In input
 * @param Cnt number of counts to rotate:
 * 0..15
 * @return return shift<in>
 */
uint16 Io_Func_ShrU16(uint16 In, uint8 Cnt)
{
	return ( (uint16)(In >> Cnt) );
}

/* This operation shall perform a bitwise shift by <cnt> bits towards LSB.
 * @param In input
 * @param Cnt number of counts to rotate:
 * 0..31
 * @return return shift<in>
 */
uint32 Io_Func_ShrU32(uint32 In, uint8 Cnt)
{
	return ( (uint32)(In >> Cnt) );
}

/* This operation shall perform a bitwise shift by <cnt> bits towards LSB.
 * @param In input
 * @param Cnt number of counts to rotate:
 * 0..63
 * @return return shift<in>
 */
#ifdef NOT_USED

uint64 Io_Func_ShrU64(uint64 In, uint8 Cnt)
{
	return ( (uint64)(In >> Cnt) );
}

#endif

/* This operation shall return the bitwise complement of the passed parameter.
 * @param In input
 * @return return invert<in>
 */
#ifdef NOT_USED

uint8 Io_Func_InvU8(uint8 In)
{
	In = ~In;

	return (uint8)In;
}

#endif

/* This operation shall return the bitwise complement of the passed parameter.
 * @param In input
 * @return return invert<in>
 */
#ifdef NOT_USED

uint16 Io_Func_InvU16(uint16 In)
{
	In = ~In;

	return (uint16)In;
}

#endif

/* This operation shall return the bitwise complement of the passed parameter.
 * @param In input
 * @return return invert<in>
 */
#ifdef NOT_USED

uint32 Io_Func_InvU32(uint32 In)
{
	In = ~In;

	return (uint32)In;
}

#endif

float32 Io_Func_MinF32(float32 Param1, float32 Param2)
{
	float32 LocRet;

	if (Param1 < Param2)
	{
		LocRet = Param1;
	}
	else
	{
		LocRet = Param2;
	}

	return LocRet;
}

float32 Io_Func_MaxF32(float32 Param1, float32 Param2)
{
	float32 LocRet;

	if (Param1 > Param2)
	{
		LocRet = Param1;
	}
	else
	{
		LocRet = Param2;
	}

	return LocRet;
}

	/** end of External Interfaces implementation **/

	/** Local Functions implementation **/

		// None so far.

	/** end of Local Functions implementation **/

	/** Interrupts Handlers implementation **/

		// None so far.

	/** end of Interrupts Handlers implementation **/

/** end of Functions implementation **/
