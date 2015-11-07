#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"


#include "io_smc_cnf.h"

const Io_Smc_Port_Struct Io_Smc_PortCnf[]={
		/*in1*/       		 /*in2*/              /*in3*/        	  /*in4*/      		 /*sleep*/     		/*drive_mode*/  			   /*step_time*/
		{ CNF_IO_PCS_P0C_08, CNF_IO_PCS_P0C_09,   CNF_IO_PCS_P0A_12,  CNF_IO_PCS_P0A_13, CNF_IO_PCS_P0D_04, IO_SMC_STATE_STEPPING_FORWARD, 40 },

};
const Io_Smc_Cnf_Struct Io_Smc_Cnf[]={
		{
				sizeof(Io_Smc_PortCnf)/sizeof(Io_Smc_Port_Struct),
				(const Io_Smc_Port_Struct*)Io_Smc_PortCnf
		}
};
