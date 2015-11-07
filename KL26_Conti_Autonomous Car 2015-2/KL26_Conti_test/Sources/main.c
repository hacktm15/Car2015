/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL26Z4.h"
#include "PLATFORM_TYPES/std_types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "PLATFORM_TYPES/platform_types.h"

#include "SYSTEM/OS/io_os.h"
#include "SYSTEM/SCHEDULER/io_sch_cnf.h"

#include "MCU_DRIVERS/ADC/io_adc_cnf.h"
#include "MCU_DRIVERS/DIO/io_dio.h"
#include "MCU_DRIVERS/INT/io_int_cnf.h"
#include "MCU_DRIVERS/PCS/io_pcs_cnf.h"
#include "MCU_DRIVERS/TIMER/io_tim.h"
#include "MCU_DRIVERS/TPM/io_tpm_cnf.h"
#include "MCU_DRIVERS/ASY/io_asy.h"

#include "HW_INTERFACES/H_BRIDGE/io_hbr_cnf.h"

#include "HW_INTERFACES/SENSORS/sensors.h"
#include "HW_INTERFACES/STEPPER_MOTOR/io_smc_cnf.h"

#include "APPLICATION/ALGO/CAR_MOVEMENT/app_robo_car_movement.h"
#include "APPLICATION/ALGO/DISTANCE_CALC/app_dist_calc.h"
#include "APPLICATION/ALGO/PATH_PLANNER/app_path_planner.h"
#include "APPLICATION/ALGO/SPEED_CALC/app_robo_speed_calc.h"

#include "OTHER_FUNCTIONS/io_func.h"

int main(void)
{
	Io_Int_DisableInterrupts();

	/* Call the initialization interfaces for INT (Interrupts) driver */
	Io_Int_Initialization(Io_Int_Cnf);

/** Initialization calls for MCU Drivers **/

	/* Call the initialization interfaces for PCS (Port Control) driver */
	Io_Pcs_Initialization(Io_Pcs_Cnf);

	/* Call the initialization interfaces for ADC driver */
	Io_Adc_Initialization(config_adc_ptr);

	/* Call the initialization interfaces for DIO driver */
	// none so far

	/* Call the initialization interfaces for TPM (Timer PWM) driver */
	Io_Tpm_Initialization(Io_Tpm_Cnf);
	/* Call the initialization interfaces for ASY driver*/

	Io_Asy_Initialization(&config_asy_device);

/** end of Initialization calls for MCU Drivers **/

/** Initialization calls for HW Interfaces **/

	/* Call the initialization interfaces for HBR (H-Bridge) driver */
	Io_Hbr_Initialization(Io_Hbr_Cnf);

	/* Call the initialization interfaces for LCD driver */
	// none so far

	/* Call the initialization interfaces for SENSORS driver */
	Sens_Initialization();

	/* Call the initialization interfaces for SMC (Stepper Motor Control) driver */
	// none so far

	/* Call the initialization interfaces for TSI (Touch Slider) driver */
	// none so far

/** end of Initialization calls for HW Interfaces **/

/** Initialization calls for Application interfaces **/

	/* Call the initialization interfaces for Car Movement module */
	Algo_Robo_Cm_InitializeCarMovement();

	/* Call the initialization interfaces for Distance Calculation module */
	// none so far

	/* Call the initialization interfaces for Path Planner module */
	Algo_Robo_Pp_InitializePathPlanner();

	/* Call the initialization interfaces for Speed Calculation module */
	Algo_Robo_Sc_InitializeSpeedCalc();

/** end of Initialization calls for Application interfaces **/

/** Initialization calls for OS & Interrupts Interfaces **/

	/* Call the initialization interfaces for OS functionality */
	Io_Os_Init();
	Io_Int_EnableInterrupts(); /* called after all driver initialization */
	Io_Sch_StartOs(0, &Io_Sch_OsConfig[0]);

/** end of Initialization calls for OS & Interrupts Interfaces **/

	return 0;
}
