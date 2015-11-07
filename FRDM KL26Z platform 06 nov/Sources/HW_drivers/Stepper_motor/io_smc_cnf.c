/**************************************************************************

COPYRIGHT (C) $Date: Sept 1, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_smc_cnf.c $

$Author: Bogdan Corina $

 ****************************************************************************/

#include "MCU_drivers/Pcs/io_pcs_cnf.h"

#include "io_smc_cnf.h"

const Io_Smc_Port_Struct Io_Smc_PortCnf[]={
		         /*in1*/         /*in2*/             /*in3*/             /*in4*/             /*sleep*/          /*drive_mode*/         /*step_time*/
		    { CNF_IO_PCS_P0C_08, CNF_IO_PCS_P0C_09,  CNF_IO_PCS_P0A_12,  CNF_IO_PCS_P0A_13,  CNF_IO_PCS_P0D_04, IO_SMC_FULLSTEP_DRIVE, 20},

};
const Io_Smc_Cnf_Struct Io_Smc_Cnf[]={
            {
				sizeof(Io_Smc_PortCnf)/sizeof(Io_Smc_Port_Struct),
				(const Io_Smc_Port_Struct*)Io_Smc_PortCnf
			}
};




