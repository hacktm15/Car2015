/****************************************************************************

COPYRIGHT (C) $Date: Jul 21, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_tpm_cnf.h $

$Author: Flueran Gabriel, Leonte Alexandru $

 ****************************************************************************/

#ifndef IO_TPM_CNF_H
#define IO_TPM_CNF_H


/** Includes **/

#include "io_tpm.h"

/** end of Includes **/

/** Defines **/

	/* TPM channels configuration defines:			   |     tpm      |     channel    |	   config type   	  |       pwm channel index          | */
#define CNF_TPM0_CHANNEL0 		IO_TPM_GENERATE_CHANNEL(IO_TPM_DEVICE0, IO_TPM_CHANNEL0, IO_TPM_CH_CONFIG_NOT_CONF, IO_TPM_PWM_CHANNEL_INDEX_NOT_CONF)
#define CNF_TPM0_CHANNEL1 		IO_TPM_GENERATE_CHANNEL(IO_TPM_DEVICE0, IO_TPM_CHANNEL1, IO_TPM_CH_CONFIG_DCM, 		IO_TPM_PWM_CHANNEL_INDEX_NOT_CONF)
#define CNF_TPM0_CHANNEL2 		IO_TPM_GENERATE_CHANNEL(IO_TPM_DEVICE0, IO_TPM_CHANNEL2, IO_TPM_CH_CONFIG_DCM, 		IO_TPM_PWM_CHANNEL_INDEX_NOT_CONF)
#define CNF_TPM0_CHANNEL3 		IO_TPM_GENERATE_CHANNEL(IO_TPM_DEVICE0, IO_TPM_CHANNEL3, IO_TPM_CH_CONFIG_DCM, 		IO_TPM_PWM_CHANNEL_INDEX_NOT_CONF)
#define CNF_TPM0_CHANNEL4 		IO_TPM_GENERATE_CHANNEL(IO_TPM_DEVICE0, IO_TPM_CHANNEL4, IO_TPM_CH_CONFIG_DCM, 		IO_TPM_PWM_CHANNEL_INDEX_NOT_CONF)
#define CNF_TPM0_CHANNEL5 		IO_TPM_GENERATE_CHANNEL(IO_TPM_DEVICE0, IO_TPM_CHANNEL5, IO_TPM_CH_CONFIG_NOT_CONF, IO_TPM_PWM_CHANNEL_INDEX_NOT_CONF)

#define CNF_TPM1_CHANNEL0		IO_TPM_GENERATE_CHANNEL(IO_TPM_DEVICE1, IO_TPM_CHANNEL0, IO_TPM_CH_CONFIG_NOT_CONF, IO_TPM_PWM_CHANNEL_INDEX_NOT_CONF)
#define CNF_TPM1_CHANNEL1		IO_TPM_GENERATE_CHANNEL(IO_TPM_DEVICE1, IO_TPM_CHANNEL1, IO_TPM_CH_CONFIG_NOT_CONF, IO_TPM_PWM_CHANNEL_INDEX_NOT_CONF)

#define CNF_TPM2_CHANNEL0 		IO_TPM_GENERATE_CHANNEL(IO_TPM_DEVICE2, IO_TPM_CHANNEL0, IO_TPM_CH_CONFIG_PWM, 		IO_TPM_PWM_CHANNEL_INDEX0)
#define CNF_TPM2_CHANNEL1		IO_TPM_GENERATE_CHANNEL(IO_TPM_DEVICE2, IO_TPM_CHANNEL1, IO_TPM_CH_CONFIG_PWM, 		IO_TPM_PWM_CHANNEL_INDEX1)
	/* end of Configuration */

/** end of Defines **/

/** External Configuration structures **/

extern const Io_Tpm_PwmChannelCnfStruct Io_Tpm_Pwm_Ch_Cnf[];
extern const Io_Tpm_DcmChannelCnfStruct Io_Tpm_Dcm_Ch_Cnf[];
extern const Io_Tpm_DeviceCnfStruct Io_Tpm_Dev_Cnf[];
extern const Io_Tpm_CnfStruct Io_Tpm_Cnf[];

/** end of External Configuration structures **/

#endif /* IO_TPM_CNF_H */
