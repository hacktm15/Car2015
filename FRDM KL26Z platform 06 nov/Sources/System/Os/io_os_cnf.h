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

$Log: io_os_cnf.h  $

$Author: PES contribution $

 ****************************************************************************/

#ifndef IO_OS_CNF_H
#define IO_OS_CNF_H


/** Defines **/

/* Maximum number of periodic tasks at a time */
#define IO_OS_MAX_PERIODIC_TASK   30

/* Maximum number of the tasks on one priority at a time (power of 2) */
#define IO_OS_MAX_PRIORITY_TASK   20

/* The priority number in the system */
#define IO_OS_PRIORITY_NUMBER     4

/* Priority macros (if more it can be added VERY_LOW and VERY_HIGH, OS_PRIO_HIGH becomes 1) */
#define IO_OS_PRIORITY_HIGH       0
#define IO_OS_PRIORITY_MEDIUM     1
#define IO_OS_PRIORITY_LOW        2
#define IO_OS_PRIORITY_VERY_LOW   3

/** end of Defines **/

#endif /* IO_OS_CNF_H */
