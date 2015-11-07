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

$Log: io_traps_main.c $

 ****************************************************************************/

#include "MKL26Z4.h"
#include "PLATFORM_TYPES/std_types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "PLATFORM_TYPES/platform_types.h"


void __attribute__((__interrupt__)) _OscillatorFail(void);
void __attribute__((__interrupt__)) _AddressError(void);
void __attribute__((__interrupt__)) _StackError(void);
void __attribute__((__interrupt__)) _MathError(void);

void __attribute__((__interrupt__)) _AltOscillatorFail(void);
void __attribute__((__interrupt__)) _AltAddressError(void);
void __attribute__((__interrupt__)) _AltStackError(void);
void __attribute__((__interrupt__)) _AltMathError(void);

/* Primary Exception Vector handlers:
 * These routines are used if INTCON2bits.ALTIVT = 0.
 * All trap service routines in this file simply ensure that device
 * continuously executes code within the trap service routine. Users
 * may modify the basic framework provided here to suit to the needs
 * of their application.
 */

void __attribute__ ((interrupt)) _OscillatorFail(void)
{
	//INTCON1bits.OSCFAIL = 0;        //Clear the trap flag

	while (1)
	{
		;
	}

}

void __attribute__ ((interrupt)) _AddressError(void)
{
	//INTCON1bits.ADDRERR = 0; //Clear the trap flag

	while (1)
	{
		;
	}

}

void __attribute__ ((interrupt)) _StackError(void)
{
	//INTCON1bits.STKERR = 0;         //Clear the trap flag

	while (1)
	{
		;
	}

}

void __attribute__ ((interrupt)) _MathError(void)
{
	//INTCON1bits.MATHERR = 0; //Clear the trap flag

	while (1)
	{
		;
	}

}

/* Alternate Exception Vector handlers:
 * These routines are used if INTCON2bits.ALTIVT = 1.
 * All trap service routines in this file simply ensure that device
 * continuously executes code within the trap service routine. Users
 * may modify the basic framework provided here to suit to the needs
 * of their application.
 */

void __attribute__ ((interrupt)) _AltOscillatorFail(void)
{
	//INTCON1bits.OSCFAIL = 0;

	while (1)
	{
		;
	}

}

void __attribute__ ((interrupt)) _AltAddressError(void)
{
	//INTCON1bits.ADDRERR = 0;

	while (1)
	{
		;
	}

}

void __attribute__ ((interrupt)) _AltStackError(void)
{
	//INTCON1bits.STKERR = 0;

	while (1)
	{
		;
	}

}

void __attribute__ ((interrupt)) _AltMathError(void)
{
	//INTCON1bits.MATHERR = 0;

	while (1)
	{
		;
	}

}
