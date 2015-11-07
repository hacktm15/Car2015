/*~-1*/
/*~XSF_LANGUAGE: C/C++*/
/*~T*/
#include "TSIDrv.h"

uint8 total_electrode = TOTAL_ELECTRODE;
uint8 elec_array[16]={ELECTRODE0,ELECTRODE1,ELECTRODE2,ELECTRODE3,ELECTRODE4,ELECTRODE5,
		ELECTRODE6,ELECTRODE7,ELECTRODE8,ELECTRODE9,ELECTRODE10,ELECTRODE11,
		ELECTRODE12,ELECTRODE13,ELECTRODE14,ELECTRODE15};
uint16 gu16TSICount[16];
uint16 gu16Baseline[16];
uint16 gu16Threshold[16]={THRESHOLD0,THRESHOLD1,THRESHOLD2,THRESHOLD3,THRESHOLD4,THRESHOLD5,
		THRESHOLD6,THRESHOLD7,THRESHOLD8,THRESHOLD9,THRESHOLD10,THRESHOLD11,
		THRESHOLD12,THRESHOLD13,THRESHOLD14,THRESHOLD15};
uint16 gu16Delta[16];
uint8 ongoing_elec;

uint8 end_flag = TRUE;

uint8 SliderPercentegePosition[2] = {NO_TOUCH,NO_TOUCH};
uint8 SliderDistancePosition[2] = {NO_TOUCH,NO_TOUCH};


uint8 AbsolutePercentegePosition = NO_TOUCH;
uint8 AbsoluteDistancePosition = NO_TOUCH;

/*~A:1*/
/*~+:void TSI_SelfCalibration*/
/*~F:2*/
void TSI_SelfCalibration(void)

/*~-1*/
{
	/*~T*/
	unsigned char cnt;
	unsigned char trigger_backup;


	TSI0_GENCS |= TSI_GENCS_EOSF_MASK;      // Clear End of Scan Flag
	TSI0_GENCS &= ~TSI_GENCS_TSIEN_MASK;    // Disable TSI module

	/*~I:3*/

	if(TSI0_GENCS & TSI_GENCS_STM_MASK)     // Back-up TSI Trigger mode from Application

		/*~-1*/
	{
		/*~T*/
		trigger_backup = TRUE;

		/*~-1*/
	}
	/*~O:I3*/
	/*~-2*/
	else
	{
		/*~T*/
		trigger_backup = FALSE;

		/*~-1*/
	}
	/*~E:I3*/
	/*~T*/

	TSI0_GENCS &= ~TSI_GENCS_STM_MASK;      // Use SW trigger
	TSI0_GENCS &= ~TSI_GENCS_TSIIEN_MASK;    // Enable TSI interrupts

	TSI0_GENCS |= TSI_GENCS_TSIEN_MASK;     // Enable TSI module

	/*~L:4*/

	for(cnt=0; cnt < total_electrode; cnt++)  // Get Counts when Electrode not pressed

		/*~-1*/
	{
		/*~T*/
		TSI0_DATA = ((elec_array[cnt] << TSI_DATA_TSICH_SHIFT) );
		TSI0_DATA |= TSI_DATA_SWTS_MASK;

		/*~L:5*/
		while(!(TSI0_GENCS & TSI_GENCS_EOSF_MASK))
			/*~-1*/
		{
			/*~T*/
			;

			/*~-1*/
		}
		/*~E:L5*/
		/*~T*/
		TSI0_GENCS |= TSI_GENCS_EOSF_MASK;
		gu16Baseline[cnt] = (TSI0_DATA & TSI_DATA_TSICNT_MASK);

		/*~-1*/
	}
	/*~E:L4*/
	/*~T*/

	TSI0_GENCS &= ~TSI_GENCS_TSIEN_MASK;    // Disable TSI module
	TSI0_GENCS |= TSI_GENCS_TSIIEN_MASK;     // Enale TSI interrupt

	/*~I:6*/
	if(trigger_backup)                      // Restore trigger mode

		/*~-1*/
	{
		/*~T*/
		TSI0_GENCS |= TSI_GENCS_STM_MASK;

		/*~-1*/
	}
	/*~O:I6*/
	/*~-2*/
	else
	{
		/*~T*/
		TSI0_GENCS &= ~TSI_GENCS_STM_MASK;

		/*~-1*/
	}
	/*~E:I6*/
	/*~T*/

	TSI0_GENCS |= TSI_GENCS_TSIEN_MASK;     // Enable TSI module

	TSI0_DATA = ((elec_array[0]<<TSI_DATA_TSICH_SHIFT) );
	TSI0_DATA |= TSI_DATA_SWTS_MASK;

	/*~-1*/
}
/*~E:F2*/
/*~E:A1*/
/*~A:7*/
/*~+:void TSI_Init*/
/*~F:8*/
void TSI_Init (void)

/*~-1*/
{
	/*~T*/
	SIM_SCGC5 |= SIM_SCGC5_TSI_MASK;  // Enable clock gating for TSI

	/* Enable proper GPIO as TSI channels */
	PORTB_PCR16 = PORT_PCR_MUX(0);   // PTB16 as TSI channel 9
	PORTB_PCR17 =  PORT_PCR_MUX(0);   // PTB17 as TSI channel 10

	//enable_irq(TSI_irq_no);
	NVIC->ISER[0] |= (uint32_t)(1 << 26);

	TSI0_GENCS |= (TSI_GENCS_ESOR_MASK
			| TSI_GENCS_MODE(0)
			| TSI_GENCS_REFCHRG(4)
			| TSI_GENCS_DVOLT(0)
			| TSI_GENCS_EXTCHRG(7)
			| TSI_GENCS_PS(4)
			| TSI_GENCS_NSCN(11)
			| TSI_GENCS_TSIIEN_MASK
			| TSI_GENCS_STPE_MASK
			//| TSI_GENCS_STM_MASK     //Trigger for the module 0=Sofware
	);

	TSI0_GENCS |= TSI_GENCS_TSIEN_MASK;

	TSI_SelfCalibration();

	/*~-1*/
}
/*~E:F8*/
/*~E:A7*/
/*~A:9*/
/*~+:void change_electrode*/
/*~F:10*/
void change_electrode(void)

/*~-1*/
{
	/*~T*/
	int16_t u16temp_delta;

	gu16TSICount[ongoing_elec] = (TSI0_DATA & TSI_DATA_TSICNT_MASK);          // Save Counts for current electrode
	u16temp_delta = gu16TSICount[ongoing_elec] - gu16Baseline[ongoing_elec];  // Obtains Counts Delta from callibration reference

	/*~I:11*/
	if( u16temp_delta < 0)

		/*~-1*/
	{
		/*~T*/
		gu16Delta[ongoing_elec] = 0;

		/*~-1*/
	}
	/*~O:I11*/
	/*~-2*/
	else
	{
		/*~T*/
		gu16Delta[ongoing_elec] = u16temp_delta;

		/*~-1*/
	}
	/*~E:I11*/
	/*~I:12*/

	if(total_electrode > 1)  //Change Electrode to Scan

		/*~-1*/
	{
		/*~I:13*/
		if((total_electrode-1) > ongoing_elec)
			/*~-1*/
		{
			/*~T*/
			ongoing_elec++;

			/*~-1*/
		}
		/*~O:I13*/
		/*~-2*/
		else
		{
			/*~T*/
			ongoing_elec = 0;

			/*~-1*/
		}
		/*~E:I13*/
		/*~T*/

		TSI0_DATA = ((elec_array[ongoing_elec]<<TSI_DATA_TSICH_SHIFT) );
		TSI0_DATA |= TSI_DATA_SWTS_MASK;

		/*~-1*/
	}
	/*~E:I12*/
	/*~-1*/
}
/*~E:F10*/
/*~E:A9*/
/*~A:14*/
/*~+:void TSI_SimpleApp*/
/*~F:15*/
void TSI_SimpleApp (void)

/*~-1*/
{
	/*~L:16*/
	while(1)

		/*~-1*/
	{
		/*~I:17*/
		if(end_flag)

			/*~-1*/
		{
			/*~T*/
			end_flag = FALSE;

			/*~I:18*/
			if(gu16Delta[0] > gu16Threshold[0])

				/*~-1*/
			{
				/*~T*/
				__asm__ ("NOP"); // Toggle LED1

				/*~-1*/
			}
			/*~E:I18*/
			/*~I:19*/


			if(gu16Delta[1] > gu16Threshold[1])

				/*~-1*/
			{
				/*~T*/
				__asm__ ("NOP"); // Toggle LED2

				/*~-1*/
			}
			/*~E:I19*/
			/*~-1*/
		}
		/*~E:I17*/
		/*~-1*/
	}
	/*~E:L16*/
	/*~-1*/
}
/*~E:F15*/
/*~E:A14*/
/*~A:20*/
/*~+:void TSI_SliderApp*/
/*~F:21*/
void TSI_SliderApp (void)

/*~-1*/
{
	/*~L:22*/
	while(1)

		/*~-1*/
	{
		/*~I:23*/
		if(end_flag)

			/*~-1*/
		{
			/*~T*/
			printf(" Percentage = %d %           Distance = %d mm          \r", AbsolutePercentegePosition, AbsoluteDistancePosition );

			end_flag = FALSE;

			/*~I:24*/


			if((gu16Delta[0] > gu16Threshold[0])||(gu16Delta[1] > gu16Threshold[1]))

				/*~-1*/
			{
				/*~T*/
				SliderPercentegePosition[0] = (gu16Delta[0]*100)/(gu16Delta[0]+gu16Delta[1]);

				SliderPercentegePosition[1] = (gu16Delta[1]*100)/(gu16Delta[0]+gu16Delta[1]);

				SliderDistancePosition[0] = (SliderPercentegePosition[0]* SLIDER_LENGTH)/100;

				SliderDistancePosition[1] = (SliderPercentegePosition[1]* SLIDER_LENGTH)/100;

				AbsolutePercentegePosition = ((100 - SliderPercentegePosition[0]) + SliderPercentegePosition[1])/2;
				AbsoluteDistancePosition = ((SLIDER_LENGTH - SliderDistancePosition[0]) + SliderDistancePosition[1])/2;

				/*~-1*/
			}
			/*~O:I24*/
			/*~-2*/
			else
			{
				/*~T*/
				SliderPercentegePosition[0] = NO_TOUCH;
				SliderPercentegePosition[1] = NO_TOUCH;
				SliderDistancePosition[0] = NO_TOUCH;
				SliderDistancePosition[1] = NO_TOUCH;
				AbsolutePercentegePosition = NO_TOUCH;
				AbsoluteDistancePosition = NO_TOUCH;

				/*~-1*/
			}
			/*~E:I24*/
			/*~-1*/
		}
		/*~E:I23*/
		/*~-1*/
	}
	/*~E:L22*/
	/*~-1*/
}
/*~E:F21*/
/*~E:A20*/
/*~A:25*/
/*~+:void TSI_SliderRead*/
/*~F:26*/
/*
 TSI_Sliderread
   return  AbsolutePercentegePosition  0-100  or if not 
          AbsoluteDistancePosition

 */

void TSI_SliderRead(void )

/*~-1*/
{
	/*~I:27*/
	if(end_flag)

		/*~-1*/
	{
		/*~T*/
		// printf(" Percentage = %d %           Distance = %d mm          \r", AbsolutePercentegePosition, AbsoluteDistancePosition );
		end_flag = FALSE;

		/*~I:28*/
		if((gu16Delta[0] > gu16Threshold[0])||(gu16Delta[1] > gu16Threshold[1]))

			/*~-1*/
		{
			/*~T*/
			SliderPercentegePosition[0] = (gu16Delta[0]*100)/(gu16Delta[0]+gu16Delta[1]);

			SliderPercentegePosition[1] = (gu16Delta[1]*100)/(gu16Delta[0]+gu16Delta[1]);

			SliderDistancePosition[0] = (SliderPercentegePosition[0]* SLIDER_LENGTH)/100;

			SliderDistancePosition[1] = (SliderPercentegePosition[1]* SLIDER_LENGTH)/100;

			AbsolutePercentegePosition = ((100 - SliderPercentegePosition[0]) + SliderPercentegePosition[1])/2;
			AbsoluteDistancePosition = ((SLIDER_LENGTH - SliderDistancePosition[0]) + SliderDistancePosition[1])/2;

			/*~-1*/
		}
		/*~O:I28*/
		/*~-2*/
		else
		{
			/*~T*/
			SliderPercentegePosition[0] = NO_TOUCH;
			SliderPercentegePosition[1] = NO_TOUCH;
			SliderDistancePosition[0] = NO_TOUCH;
			SliderDistancePosition[1] = NO_TOUCH;
			AbsolutePercentegePosition = NO_TOUCH;
			AbsoluteDistancePosition = NO_TOUCH;

			/*~-1*/
		}
		/*~E:I28*/
		/*~-1*/
	}
	/*~E:I27*/
	/*~-1*/
}
/*~E:F26*/
/*~E:A25*/
/*~A:29*/
/*~+:void TSI_ISR*/
/*~F:30*/
void TSI_ISR(void)

/*~-1*/
{
	/*~T*/
	end_flag = TRUE;
	TSI0_GENCS |= TSI_GENCS_EOSF_MASK; // Clear End of Scan Flag
	change_electrode();

	/*~-1*/
}
/*~E:F30*/
/*~E:A29*/
