#include "MCU_DRIVERS/ADC/io_adc_cnf.h"
#include "MCU_DRIVERS/DIO/io_dio.h"
#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"
#include "MCU_DRIVERS/TIMER/io_tim.h"
#include "MCU_DRIVERS/TPM/io_tpm_cnf.h"

#include "io_hbr_cnf.h"

const Io_Hbr_Port_Struct Io_Hbr_PortCnf[]={
		/*pwm*/               /*in1*/         	  /*in2*/         	   /*stby*/
		{  CNF_TPM0_CHANNEL1, CNF_IO_PCS_P0C_06,  CNF_IO_PCS_P0C_07,   CNF_IO_PCS_P0C_00},
		{  CNF_TPM0_CHANNEL2, CNF_IO_PCS_P0B_18,  CNF_IO_PCS_P0B_19 ,  CNF_IO_PCS_P0C_00}

};
const Io_Hbr_Cnf_Struct Io_Hbr_Cnf[]={
		{
				sizeof(Io_Hbr_PortCnf)/sizeof(Io_Hbr_Port_Struct),
				(const Io_Hbr_Port_Struct*)Io_Hbr_PortCnf
		}
};
