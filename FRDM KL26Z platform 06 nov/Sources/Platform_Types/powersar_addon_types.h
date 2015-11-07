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

$Log: powersar_addon_types.h $

$Author: PES contribution $

 ****************************************************************************/

#ifndef POWERSAR_ADDON_TYPES_H
#define POWERSAR_ADDON_TYPES_H


/** Standard definition for 64 bit signed int symbol. */
typedef signed long long sint64;

/** Standard definition for 64 bit unsigned int symbol. */
typedef unsigned long long uint64;


/** Defines **/

#define F32_EPSILON                                      ((float32) 1.19209290E-07F) /**< The epsilon value of data type float32. */
#define F32_MAX                                          ((float32) 3.40282347E+38F) /**< MAX value of data type float32. */
#define F32_MIN                                          ((float32) 1.17549435E-38F) /**< MIN value of data type float32. */
#define S16_MAX                                          ((sint16) 0x7FFF) /**< MAX value of data type sint16. */
#define S16_MIN                                          ((sint16) 0x8000) /**< MIN value of data type sint16. */
#define S32_MAX                                          ((sint32) 0x7FFFFFFFL) /**< MAX value of data type sint32. */
#define S32_MIN                                          ((sint32) 0x80000000L) /**< MIN value of data type sint32. */
#define S64_MAX                                          ((sint64) 0x7FFFFFFFFFFFFFFFLL) /**< MAX value of data type sint64. */
#define S64_MIN                                          ((sint64) 0x8000000000000000LL) /**< MIN value of data type sint64. */
#define S8_MAX                                           ((sint8)  0x7F) /**< MAX value of data type sint8. */
#define S8_MIN                                           ((sint8)  0x80) /**< MIN value of data type sint8. */
#define U16_MAX                                          ((uint16) 0xFFFFU) /**< MAX value of data type uint16. */
#define U16_MIN                                          ((uint16) 0x0U) /**< MIN value of data type uint16. */
#define U32_MAX                                          ((unit32) 0xFFFFFFFFUL) /**< MAX value of data type uint32. */
#define U32_MIN                                          ((uint32) 0x0UL) /**< MIN value of data type uint32. */
#define U64_MAX                                          ((uint64) 0xFFFFFFFFFFFFFFFFULL) /**< MAX value of data type uint64. */
#define U64_MIN                                          ((uint64) 0x0ULL) /**< MIN value of data type uint64. */
#define U8_MAX                                           ((uint8)  0xFFU) /**< MAX value of data type uint8. */
#define U8_MIN                                           ((uint8)  0x0U) /**< MIN value of data type uint8. */

/** end of Defines **/


/* Macro operation name: MAKE_VOLATILE
 * @param type
 * @param var
 */
/* ## Macro operation start [24684dfc-7ed8-4dc7-8b40-5d60518df711] */
#define MAKE_VOLATILE(type, var)  (*(volatile type *) (&(var)))
/* ## Macro operation end [24684dfc-7ed8-4dc7-8b40-5d60518df711] */

#endif /* POWERSAR_ADDON_TYPES_H */
