#include"io_cnfasy.h"
#include"io_asy.h"


/* Private Declarations / Definitions / Prototypes */


void ASY_TX_Signal(uint16 io_ch)
{

}

void ASY_RX_Signal(uint16 io_ch)
{

}

void ASY_ERR_Signal(uint16 io_ch)
{

}


/* Private Type Definitions */
/* Private Constant Definitions */

/*
SIG_DEFINE(BIOS_ASY_SIG_INT0, (SIG_func_t)Io_Asy_Asy0_Isr, NULL_PTR);
SIG_DEFINE(BIOS_ASY_SIG_INT1, (SIG_func_t)Io_Asy_Asy1_Isr, NULL_PTR);
SIG_DEFINE(BIOS_ASY_SIG_INT2, (SIG_func_t)Io_Asy_Asy2_Isr, NULL_PTR);
*/
SIG_DEFINE_WRP_CHTRG(asy_tx_sig0,ASY_TX_Signal,0);
SIG_DEFINE_WRP_CHTRG(asy_rx_sig0,ASY_RX_Signal, 0);
SIG_DEFINE_WRP_CHTRG(asy_err_sig0,ASY_ERR_Signal,0);

SIG_DEFINE_WRP_CHTRG(asy_tx_sig1,ASY_TX_Signal,1);
SIG_DEFINE_WRP_CHTRG(asy_rx_sig1,ASY_RX_Signal, 1);
SIG_DEFINE_WRP_CHTRG(asy_err_sig1,ASY_ERR_Signal,1);

/*BIOS_ASY_config_channel*/



const BIOS_ASY_config_channel  asy_channels[] =
{
		{
				1                                                                      /*ASY channel */
				,BIOS_ASY_HALFDUPLEX                                                            /* Full or Half Duplex */
				,BIOS_ASY_MODE_8N1                           /*ASY Frame Format */
				,9600                                                    /* Initial Baudrate */
				,&asy_tx_sig0                           /* Signal after completed tranmission */                                      ,&asy_rx_sig0                               /* Signal after completed reception */                                    ,&asy_err_sig0                                  /* Signal after rx/tx failure */
		}
		,
		{
				2/*ASY channel */
				,BIOS_ASY_HALFDUPLEX                                                            /* Full or Half Duplex */
				,BIOS_ASY_MODE_8N1                                                     /*ASY Frame Format */
				,9600                                                   /* Initial Baudrate */
				,&asy_tx_sig1                                   /* Signal after completed tranmission */                              ,&asy_rx_sig1                               /* Signal after completed reception */                                    ,&asy_err_sig1                                /* Signal after rx/tx failure */
		}

};

/* BIOS_ASY_config_device*/
const BIOS_ASY_config_device config_asy_device =
{

				2,
				&asy_channels[0]


};


/*BIOS_ASY_config_peripheral */
/*const BIOS_ASY_config_peripheral asy_peripherals[] =
{
		{
				&config_asy_device[0]

								   ,Io_Asy_Initialization
								   ,Io_Asy_Ch_Initialization
								   ,Io_Asy_Start
								   ,Io_Asy_TxData
								   ,Io_Asy_RxData
								   ,Io_Asy_ChannelStatus
								   ,Io_Asy_Enable_RxSignal
								   ,Io_Asy_Enable_ErrSignal
								   ,BIOS_ASY_IntEnable_TxSignal
								   ,BIOS_ASY_IntRxLength
								   ,BIOS_ASY_IntStop
								   ,Io_Asy_SetBaudrate
								   ,Io_Asy_CalculateBaudrate
								   ,BIOS_ASY_IntSendBreak
								   ,BIOS_ASY_IntShutDown
								   ,BIOS_ASY_IntCh_ShutDown
		},
};


/*BIOS_ASY_config */
/*const BIOS_ASY_config   config_asy[] =
{
		{
				(sizeof(asy_peripherals)/sizeof(asy_peripherals[0])),
				asy_peripherals
		}
};*/

const uint32 BIOS_ASY_Dev_Addr[3] = {
		/*lint -e(923)*/(uint32)(void *)&/*lint -e(923)*/UART0_C1, /* Device0. SCI1 Control reg0 */
		/*lint -e(923)*/(uint32)(void *)&/*lint -e(923)*/UART1_C1, /* Device1. SCI2 Control reg0 */
		/*lint -e(923)*/((uint32)(void *)&/*lint -e(923)*/UART1_C1+0x4000)  /* Device2. SCI3 Control reg0 */
}
;
void BIOS_ASY_IntSendBreak(uint16 ch)
{
	volatile uint16 dummy_read;
	BIOS_ASY_DeviceStruct* asy_devptr;      /* pointer to register structure*/
	/* point to either SCI0 or SCI1 depending upon channel */
	asy_devptr = /*lint -e(923) : cast from unsigned long to pointer The array BIOS_ASY_Dev_Addr acts as a store for the register address, they are defined as unsigned long in the array*/(BIOS_ASY_DeviceStruct *)
			BIOS_ASY_Dev_Addr[bios_asy_config_device_int->asy_config_channel[ch].asy_channel];
	basy_ch_info_ptr_int[ch].txn_status = BIOS_ASY_STAT_TX_BUSY|BIOS_ASY_STAT_RX_BUSY|BIOS_ASY_STAT_BREAK_ONGOING; /* indicate break ongoing and tx rx busy */
	basy_ch_info_ptr_int[ch].rx_err = 0;       /* reset recieve err while sending break */
	dummy_read = asy_devptr -> DR;         /* To avoid the OR error */
	dummy_read = bios_asy_config_device_int->asy_config_channel[ch].asy_channel;
	BASY_ClearStatus((uint8)dummy_read);    /* Clear all the status register */
	//Io_Int_DisableInterrupts();
	asy_devptr->CR1 |=  ((uint32)0x08); /* Activate the device TE */
	asy_devptr -> CR2 |= 0x200;    /* Transmit 13bit break frame */
	asy_devptr -> CR1 |= 0x1;     /*  Send Break frame assumed the SCI receiver and rx-interrupt are enabled which is important for receiving the send break */
	asy_devptr -> CR1 &= ~0x1;     /* The SBK bit should be toggled to generate the Break frame */
	//Io_Int_EnableInterrupts();

}


void BIOS_ASY_IntCh_ShutDown(uint16 ch)

{

	uint8 object;
	BIOS_ASY_DeviceStruct* asy_devptr;  /* pointer to register structure*/

	object = bios_asy_config_device_int->asy_config_channel[ch].asy_channel;

	/* point to either SCI0 or SCI1 depending upon channel */
	asy_devptr = /*lint -e(923) : cast from unsigned long to pointer The array BIOS_ASY_Dev_Addr acts as a store for the register address, they are defined as unsigned long in the array*/(BIOS_ASY_DeviceStruct *)
		BIOS_ASY_Dev_Addr[object];

	//asy_devptr -> CR1 = 0x0;
	//asy_devptr -> CR2 = 0x0;

	//BIOS_INT_EnableTrigger(BIOS_INT_ASY_RDRF_CH(object), 0);

	//BIOS_INT_EnableTrigger(BIOS_INT_ASY_TC_CH(object), 0);

}

void BIOS_ASY_IntShutDown(void)

{

	int n;

	for (n = 0; n < bios_asy_config_device_int->asy_number_of_channels; n++)

	{

		BIOS_ASY_IntCh_ShutDown((uint16)n);

	}

	basy_ch_info_ptr_int = NULL_PTR;

	bios_asy_config_device_int = NULL_PTR;

}

inline void BASY_ClearStatus(uint16 channel)

{

	uint8 dummy;

	BIOS_ASY_DeviceStruct* asy_devptr;  /* pointer to register structure*/


	/* point to either of the  ASC devices depending upon channel */
	asy_devptr = /*lint -e(923) : cast from unsigned long to pointer The array acts as a store for the register address*/(BIOS_ASY_DeviceStruct *) BIOS_ASY_Dev_Addr[channel];
	if(channel==0)
	{
		dummy=UART0_S1;
		UART0_S1=dummy;

		dummy=UART0_S2;
		UART0_S2=dummy;

	}
	/*dummy = asy_devptr -> SR;
	asy_devptr -> SR = dummy;*/
	else if(channel==1)
	{


			dummy=UART1_S2;
			UART1_S2=dummy;

		}
	else if(channel==2)
	{


			dummy=UART2_S2;
			UART2_S2=dummy;

		}

}

