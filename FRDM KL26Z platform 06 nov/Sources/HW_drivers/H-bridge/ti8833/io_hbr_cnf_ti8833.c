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

$Log: io_hbr_cnf_ti8833.c $

$Author: Bogdan Corina $

 ****************************************************************************/

#include "MCU_drivers/Adc/io_adc_cnf.h"
#include "MCU_drivers/Dio/io_dio.h"
#include "MCU_drivers/Pcs/io_pcs_cnf.h"
#include "MCU_drivers/Timer/io_tim.h"
#include "MCU_drivers/Tpm/io_tpm_cnf.h"

#include "io_hbr_cnf_ti8833.h"

const Io_Hbr_Drv8833_Port_Struct Io_Hbr_Drv8833_PortCnf[]={
		/*in1*/               /*in2*/             /*stby*/
		{  CNF_TPM2_CHANNEL0, CNF_IO_PCS_P0C_08,  CNF_IO_PCS_P0C_00},
		{  CNF_TPM2_CHANNEL1, CNF_IO_PCS_P0C_09,  CNF_IO_PCS_P0C_00}

};
const Io_Hbr_Drv8833_Cnf_Struct Io_Hbr_Drv8833_Cnf[]={
		{
				sizeof(Io_Hbr_Drv8833_PortCnf)/sizeof(Io_Hbr_Drv8833_Port_Struct),
				(const Io_Hbr_Drv8833_Port_Struct*)Io_Hbr_Drv8833_PortCnf
		}
};





