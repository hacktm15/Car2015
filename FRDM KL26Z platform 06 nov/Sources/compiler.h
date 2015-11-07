/**************************************************************************

COPYRIGHT (C) $Date: Nov 3, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: compiler.h $

$Author: PES contribution $

 ****************************************************************************/

#ifndef COMPILER_H
#define COMPILER_H


/** Includes **/

#include "MKL26Z4.h"

/** end of Includes **/

/** Defines **/

#define _TASKING_C_TRICORE_      /*For tricore */

#define AUTOMATIC  /*The memory class AUTOMATIC shall be provided as empty definition, used for the declaration of local pointers.*/

#define TYPEDEF  /*COMPILER059*/

#define NULL_PTR ((void *)0) /*The compiler abstraction shall provide the NULL_PTR define with a void pointer to zero definition.*/

#define INLINE inline /*The compiler abstraction shall provide the INLINE define for abstraction of the keyword inline.*/

#define LOCAL_INLINE static inline /*The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the keyword inline in functions with "static" scope*/

#define FUNC(rettype, memclass) rettype /*COMPILER001 & COMPILER058*/

#define P2VAR(ptrtype, memclass, ptrclass) ptrtype* /*The compiler abstraction shall define the P2VAR macro for the declaration and definition of pointers in RAM, pointing to variables*/

#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype * /*The compiler abstraction shall define the P2CONST macro for the declaration and definition of pointers in RAM pointing to constants*/

#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const /*The compiler abstraction shall define the CONSTP2VAR macro for the declaration and definition of constant pointers accessing variables.*/

#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const /*The compiler abstraction shall define the CONSTP2CONST macro for the declaration and definition of constant pointers accessing constants*/

#define P2FUNC(rettype, ptrclass, fctname) rettype (*fctname) /*The compiler abstraction shall define the P2FUNC macro for the type definition of pointers to functions.*/

#define CONST(consttype, memclass) const consttype /*The compiler abstraction shall define the CONST macro for the declaration and definition of constants.*/

#define VAR(vartype, memclass) vartype /*The compiler abstraction shall define the VAR macro for the declaration and definition of variables.*/

/** end of Defines **/

#endif /* COMPILER_H */
