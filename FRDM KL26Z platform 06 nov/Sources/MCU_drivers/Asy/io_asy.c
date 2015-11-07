/****************************************************************************

COPYRIGHT (C) $Date: Sept 1, 2015 $
$CompanyInfo: CONTINENTAL AUTOMOTIVE GMBH $
ALL RIGHTS RESERVED.

The reproduction, transmission or use of this document or its contents is
not permitted without express written authority.
Offenders will be liable for damages. All rights, including rights created
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_asy.c  $

$Author: Iovescu Raul $

 ****************************************************************************/

#include"MCU_DRIVERS/DIO/io_dio.h"
#include"MCU_DRIVERS/PCS/io_pcs_cnf.h"

#include "io_asy.h"
#include "io_asy_cnf.h"

#define UARTLP_C2_RE_MASK 0x4u
#define UARTLP_C2_TE_MASK 0x8u
#define UARTLP_C2_RIE_MASK 0x20u

char c;
char reception[]={3,3,3,3,3,3,3,3};
int length=3,pozition=0;
const char transmission[]={'$','$','$',};

#define Io_Asy_PROC_BAUDRATE_CALCULATION(baudrate) ( (24000000/16 + baudrate/2) / baudrate )
#define LIB_PRC_Shluint32(a,b) a<<b

uint8 tx_table[16];
uint8 rx_table[16];
Io_Asy_Chan_Struct Io_Asy_channel_table[3];
uint8 basy_phy_to_log_ch[3];

const Io_Asy_config_device *io_asy_config_device_int;   /**<  INT device configuration structure , pointer */


Io_Asy_Chan_Struct *Io_Asy_ch_info_ptr_int;   /**<  INT channel, information pointer  */


void Io_Asy_Initialization(const Io_Asy_config_device *asy_config_device)
{

	int n ;
	uint8 chan_num;
	io_asy_config_device_int = asy_config_device;     /* saves the config structure address to global pointer */
	chan_num = asy_config_device->asy_number_of_channels;  /* get the number of configured channels */
	n = chan_num * sizeof(Io_Asy_Chan_Struct);/* total size of the channel structure required */
	Io_Asy_ch_info_ptr_int = &Io_Asy_channel_table[0]; /* dynamic memory allocation */
	for (n = 0; n < chan_num; n++)
	{
		Io_Asy_Ch_Initialization((uint16)n);/* initialize each channel configured */
	}

}


void Io_Asy_Ch_Initialization(uint16 ch)
{

	uint32 baudrate,baud,tmp;
	uint16 mode,low,high;
	uint32 control_reg1 = 0x00000000U;
	uint32 control_reg3 = 0x00000000U;
	uint16 member = 0xFF; /* default as 8N1 */
	uint8 basy_phy_to_log_ch[3],l,h;
	//Io_Asy_DeviceStruct* asy_devptr;  /* pointer to register structure*/
	Io_Asy_ch_info_ptr_int[ch].tx_buf = &tx_table[0];
	Io_Asy_ch_info_ptr_int[ch].rx_buf = &rx_table[0];


	control_reg1=Io_Asy_CalculateBaudrate(1,19200);
	baudrate = io_asy_config_device_int->asy_config_channel[ch].asy_baudrate;

	/* point to either of the  SCI devices depending upon channel */
	//asy_devptr = /*lint -e(923) : cast from unsigned long to pointer The array Io_Asy_Dev_Addr acts as a store for the register address, they are defined as unsigned long in the array*/(Io_Asy_DeviceStruct *)
	//		Io_Asy_Dev_Addr[io_asy_config_device_int->asy_config_channel[ch].asy_channel];

	basy_phy_to_log_ch[io_asy_config_device_int->asy_config_channel[ch].asy_channel]=(uint8)ch;



	Io_Asy_ch_info_ptr_int[ch].rx_length = 1;
	Io_Asy_ch_info_ptr_int[ch].txn_status = 0;

	tmp=Io_Asy_CalculateBaudrate(0,baudrate);

	switch(io_asy_config_device_int->asy_config_channel[ch].asy_channel)
	{
	case 0:
	{
		SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);    /* UART0 clock source select as MCGFLLCLK/MCGPLLCLK/2*/
		SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; /* UART0 clock source select as MCGPLLCLK/2*/
		SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;     /* UART0 clock enabled*/
		UART0_C2 &= ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
		UART0_C1 = 0x00;
		UART0_C3 = 0x00;
		UART0->C4 = UART0_C4_OSR(16 - 1);
		UART0_C5 = 0x00;
		UART0->S2 |= 0xC0;
		UART0->MA1 = 0x00;
		Io_Asy_SetBaudrate(0, tmp);
		UART0_C2 |=UARTLP_C2_RIE_MASK;
		UART0_C2 |= UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK;
		switch(io_asy_config_device_int->asy_config_channel[ch].asy_mode)
		{
		case Io_Asy_MODE_7Y1:
			UART0_C1|=UART0_C1_PE_MASK;
			break;
		case Io_Asy_MODE_8Y1:
			UART0_C1|=UART0_C1_PE_MASK;
			UART0_C1|=UART0_C1_M_MASK;
			break;
		default:
			break;
		}
		break;
	}
	case 1:
	{
		SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
		SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
		SIM_SOPT5 &= ~SIM_SOPT5_UART1TXSRC_MASK;
		SIM_SOPT5 |= SIM_SOPT5_UART1TXSRC(0);
		UART1_C2 &= ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
		UART1_C1 = 0x00;
		UART1_C3 = 0x00;
		UART1_C4 |= 0x00;
		UART1->S2 |= 0xC0;
		Io_Asy_SetBaudrate(1, tmp);
		UART1_C2 |=UARTLP_C2_RIE_MASK;
		UART1_C2 |= UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK;
		switch(io_asy_config_device_int->asy_config_channel[ch].asy_mode)
		{
		case Io_Asy_MODE_7Y1:
			UART1_C1|=UART0_C1_PE_MASK;
			break;
		case Io_Asy_MODE_8Y1:
			UART1_C1|=UART0_C1_PE_MASK;
			UART1_C1|=UART0_C1_M_MASK;
			break;
		default:
			break;
		}
		break;
	}
	case 2:
	{
		SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
		SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
		UART2_C2 &= ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
		UART2_C1 = 0x00;
		UART2_C3 = 0x00;
		UART2_C4 |= 0x00;
		UART2->S2 |= 0xC0;
		Io_Asy_SetBaudrate(2, tmp);
		UART2_C2 |=UARTLP_C2_RIE_MASK;
		UART2_C2 |= UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK;
		switch(io_asy_config_device_int->asy_config_channel[ch].asy_mode)
		{
		case Io_Asy_MODE_7Y1:
			UART2_C1|=UART0_C1_PE_MASK;
			break;
		case Io_Asy_MODE_8Y1:
			UART2_C1|=UART0_C1_PE_MASK;
			UART2_C1|=UART0_C1_M_MASK;
			break;
		default:
			break;
		}
		break;

	}
	}
	//Io_Int_EnableInterrupts();



}

void Io_Asy_Start(uint16 ch)

{

	uint8 object;


	Io_Asy_ch_info_ptr_int[ch].rx_number = 0;
	Io_Asy_ch_info_ptr_int[ch].tx_number = 0;
	Io_Asy_ch_info_ptr_int[ch].txdata_opr_called_twice = 0;
	Io_Asy_ch_info_ptr_int[ch].tx_length = 0;
	Io_Asy_ch_info_ptr_int[ch].txn_status = 0;
	Io_Asy_ch_info_ptr_int[ch].data_mismatch = 0; /* Reset the flag */

	object = io_asy_config_device_int->asy_config_channel[ch].asy_channel;

	Io_Asy_ch_info_ptr_int[ch].rx_err = 0;


	Io_Asy_ch_info_ptr_int[ch].tx_number ++ ;

	if(object==0 && (UART0_S1 & UART_S1_TDRE_MASK)!=0)
	{
		UART0_D= (uint8)Io_Asy_ch_info_ptr_int[ch].tx_buf[0];
	}
	else if(object==1 && (UART1_S1 & UART_S1_TDRE_MASK)!=0)
	{
		UART1_D= (uint8)Io_Asy_ch_info_ptr_int[ch].tx_buf[0];
	}
	else if(object==2 && (UART1_S1 & UART_S1_TDRE_MASK)!=0)
	{
		UART2_D=  (uint8)Io_Asy_ch_info_ptr_int[ch].tx_buf[0];
	}





}

void Io_Asy_TxData(uint16 ch, uint8 tx_length, uint8 *transmit_buffer)
/*~-*/
{

	uint8 object;
	int i;


	object = io_asy_config_device_int->asy_config_channel[ch].asy_channel;

	if (Io_Asy_ch_info_ptr_int[ch].txn_status & 0x04)

	{
		Io_Asy_ch_info_ptr_int[ch].txdata_opr_called_twice = 0x01;/* Flag Which inform the ISR that it has entered TXdata routine and came back */


		Io_Asy_ch_info_ptr_int[ch].txn_status = 0; /* reset all software managed states */


	}

	if (tx_length > 1)

	{

		Io_Asy_ch_info_ptr_int[ch].txn_status = Io_Asy_STAT_FRAME_ONGOING;

	}

	if (io_asy_config_device_int->asy_config_channel[ch].asy_type_of_communication == Io_Asy_HALFDUPLEX)

	{

		Io_Asy_ch_info_ptr_int[ch].txn_status |= Io_Asy_STAT_TX_BUSY|Io_Asy_STAT_RX_BUSY;

	}

	else
	{

		Io_Asy_ch_info_ptr_int[ch].txn_status |= Io_Asy_STAT_TX_BUSY;

	}

	for (i = 0; i < tx_length ; i++)
	{

		Io_Asy_ch_info_ptr_int[ch].tx_buf[i] = transmit_buffer[i];

	}

	Io_Asy_ch_info_ptr_int[ch].rx_number = 0;    /* Reset back to zero for fresh reception */
	Io_Asy_ch_info_ptr_int[ch].tx_number = 0;



	Io_Asy_ch_info_ptr_int[ch].tx_length = tx_length;

	Io_Asy_ch_info_ptr_int[ch].rx_err = 0;


}

void Io_Asy_RxData(uint16 ch, uint8 *receive_buffer)

{
	uint8 object;
	object=io_asy_config_device_int->asy_config_channel[ch].asy_channel;



	if (object==0 && (UART0_S1 & UART_S1_RDRF_MASK) != 0 )
	{
		*Io_Asy_ch_info_ptr_int[ch].rx_buf=UART0_D;
	}
	if (object==1 && (UART1_S1 & UART_S1_RDRF_MASK) != 0 )
	{
		*Io_Asy_ch_info_ptr_int[ch].rx_buf=UART1_D;
	}

	if (object==2 && (UART2_S1 & UART_S1_RDRF_MASK) != 0 )
	{
		*Io_Asy_ch_info_ptr_int[ch].rx_buf=UART2_D;
	}

	receive_buffer[0]=Io_Asy_ch_info_ptr_int[ch].rx_buf[0];


}

uint32 Io_Asy_ChannelStatus(uint16 ch)

{

	uint32 status_val = 0;
	uint32 status_info;

	if(ch==0)
	{
		status_val = UART0_S1;

	}
	else if(ch==1)
	{
		status_val = UART1_S1;

	}
	else if(ch==2)
	{
		status_val = UART2_S1;

	}
	//status_val = asy_devptr -> SR;


	Io_Asy_ClearStatus(io_asy_config_device_int->asy_config_channel[ch].asy_channel);      /* Clear all the status register */

	Io_Int_DisableInterrupts();

	status_info = status_val & 0xF000000;  /* OE, RX_ERR(NF), FE , PE */

	status_info |= Io_Asy_ch_info_ptr_int[ch].txn_status; /* Break,Frame,Rx,Tx */

	{

		status_info |= Io_Asy_STAT_DEV_ACTIVE;

	}

	if ( Io_Asy_ch_info_ptr_int[ch].rx_err)

	{

		status_info |= Io_Asy_STAT_RX_ERR;

		Io_Asy_ch_info_ptr_int[ch].rx_err = 0;  /* clear the rx err  after reading the rx err status */

	}

	if (Io_Asy_ch_info_ptr_int[ch].data_mismatch)

	{

		status_info |= Io_Asy_STAT_RX_TX_NOT_EQUAL;

		Io_Asy_ch_info_ptr_int[ch].data_mismatch = 0; /*  Reset the read back data error mismatch occured in the last reception after reporting to the higher layer */

	}

	Io_Int_EnableInterrupts();

	return (status_info);

}

void Io_Asy_Enable_RxSignal(uint16 ch, uint8 enable)

{

	Io_Asy_ch_info_ptr_int[ch].rx_sig_en = enable; /* clear or enable the RIE bit */

}

void Io_Asy_Enable_ErrSignal(uint16 ch, uint8 enable)

{

	Io_Asy_ch_info_ptr_int[ch].err_sig_en = enable;

}

void Io_Asy_IntEnable_TxSignal(uint16 ch, uint8 enable)

{

	Io_Asy_ch_info_ptr_int[ch].tx_sig_en = enable;

}

void Io_Asy_IntRxLength(uint16 ch, uint8 rx_length)

{

	Io_Asy_ch_info_ptr_int[ch].rx_length = rx_length;


}

void Io_Asy_IntStop(uint16 ch)

{

	Io_Asy_DeviceStruct* asy_devptr;  /* pointer to register structure*/

	/* point to either of ASY devices depending upon channel */
	asy_devptr = /*lint -e(923) : cast from unsigned long to pointer The array Io_Asy_Dev_Addr acts as a store for the register address, they are defined as unsigned long in the array*/(Io_Asy_DeviceStruct *)
																																																																																				Io_Asy_Dev_Addr[io_asy_config_device_int->asy_config_channel[ch].asy_channel];

	Io_Asy_ch_info_ptr_int[ch].txn_status = 0; /* reset all software managed states */

	Io_Int_DisableInterrupts();

	if(io_asy_config_device_int->asy_config_channel[ch].asy_channel==0)
	{
		UART0_C2&=  ~((uint32)0x0C);
	}
	else if(io_asy_config_device_int->asy_config_channel[ch].asy_channel==1)
	{
		UART1_C2&=  ~((uint32)0x0C);
	}
	else if(io_asy_config_device_int->asy_config_channel[ch].asy_channel==2)
	{
		UART2_C2&=  ~((uint32)0x0C);
	}
	//asy_devptr -> CR1 &=  ~((uint32)0x0C); /* Disable the Tx and Rx */

	Io_Int_EnableInterrupts();

}

void Io_Asy_SetBaudrate(uint16 ch, uint32 baudrate)

{
	uint16 low,high;
	uint16 baud_reload;
	uint16 *baud_reg;


	low=0x00FF&baudrate;
	high=0x00FF&(baudrate>>8);


	if(ch==0)
	{

		UART0_BDH &= ~UART_BDH_SBR_MASK;
		UART0_BDH |= (uint8)high;
		UART0_BDL &= ~UART_BDL_SBR_MASK;
		UART0_BDL |=(uint8)low;
	}
	else if(ch==1)
	{

		UART1_BDH &= ~UART_BDH_SBR_MASK;
		UART1_BDH |= (uint8)high;
		UART1_BDL &= ~UART_BDL_SBR_MASK;
		UART1_BDL |=(uint8)low;
	}
	else if(ch==2)
	{

		UART2_BDH &= ~UART_BDH_SBR_MASK;
		UART2_BDH |= (uint8)high;
		UART2_BDL &= ~UART_BDL_SBR_MASK;
		UART2_BDL |=(uint8)low;
	}


}

uint32 Io_Asy_CalculateBaudrate(uint16 ch, uint32 baudrate)

{
	uint32 tmp;

	tmp=Io_Asy_PROC_BAUDRATE_CALCULATION(baudrate);

	return tmp;
}

void Io_Asy_Asy0_Isr()
{
	Io_Asy_RxData(0,reception);

}

void Io_Asy_Asy1_Isr()
{
	Io_Asy_RxData(0,reception);
}

void Io_Asy_Asy2_Isr()
{

	Io_Asy_RxData(0,reception);

}

void Io_Asy_IntFdTxIsr(uint8 object)

{

	uint8 channel;
	Io_Asy_DeviceStruct* asy_devptr;  /* pointer to register structure*/

	channel = basy_phy_to_log_ch[object];

	/* point to either of the  SCI devices depending upon channel */
	asy_devptr = /*lint -e(923) : cast from unsigned long to pointer The array Io_Asy_Dev_Addr acts as a store for the register address, they are defined as unsigned long in the array*/(Io_Asy_DeviceStruct *)
																																																																																				Io_Asy_Dev_Addr[object];

	if (Io_Asy_ch_info_ptr_int[channel].tx_length > 1)

	{

		//Io_Int_DisableInterrupts();

		if (Io_Asy_ch_info_ptr_int[channel].txdata_opr_called_twice)

		{

			Io_Asy_ch_info_ptr_int[channel].txdata_opr_called_twice = 0;

		}

		else
		{

			/*Transmit data operation was not called twice,so Transfer the data from the buffer to the DR  */

			if(channel==0)
			{
				UART0_D=  Io_Asy_ch_info_ptr_int[channel].tx_buf[Io_Asy_ch_info_ptr_int[channel].tx_number ];
			}
			else if(channel==1)
			{
				UART1_D=  Io_Asy_ch_info_ptr_int[channel].tx_buf[Io_Asy_ch_info_ptr_int[channel].tx_number ];
			}
			else if(channel==2)
			{
				UART2_D=   Io_Asy_ch_info_ptr_int[channel].tx_buf[Io_Asy_ch_info_ptr_int[channel].tx_number ];
			}
			if(channel==0)

				//asy_devptr -> DR  = Io_Asy_ch_info_ptr_int[channel].tx_buf[Io_Asy_ch_info_ptr_int[channel].tx_number ];
				Io_Asy_ch_info_ptr_int[channel].tx_number ++ ;

			Io_Asy_ch_info_ptr_int[channel].tx_length--;

		}

		//Io_Int_EnableInterrupts();

	}

	else
	{

		/* All the data in the previous frame are transmitted out*/

		//Io_Int_DisableInterrupts();

		Io_Asy_ch_info_ptr_int[channel].txn_status &= (uint8)(~(uint8)Io_Asy_STAT_TX_BUSY); /* indicate tx as idle */
		Io_Asy_ch_info_ptr_int[channel].txn_status &= (uint8)(~(uint8)Io_Asy_STAT_FRAME_ONGOING); /* indicate frame complete */

		//Io_Int_EnableInterrupts();

		if (Io_Asy_ch_info_ptr_int[channel].tx_sig_en)
			/*~-*/
		{
			/*~T*/
			SIG_RaiseFunc(io_asy_config_device_int->asy_config_channel[channel].asy_sig_tx);
			/*~-*/
		}


	}
}

void Io_Asy_IntFdRxIsr(uint8 object, uint32 status_info)
/*~-*/
{

	uint8 channel;
	const Io_Asy_DeviceStruct* asy_devptr;  /* pointer to register structure*/
	uint32 status_reg;

	/*~T*/
	channel = basy_phy_to_log_ch[object];
	/*~T*/
	/* point to either of the  SCI devices depending upon channel */
	asy_devptr = /*lint -e(923) : cast from unsigned long to pointer The array Io_Asy_Dev_Addr acts as a store for the register address, they are defined as unsigned long in the array*/(Io_Asy_DeviceStruct *)
																																																																																				Io_Asy_Dev_Addr[object];

	/*~T*/
	if(channel==0)
	{
		status_reg=UART0_S1;
	}
	else if(channel==1)
	{
		status_reg=UART1_S1;
	}
	else if(channel==2)
	{
		status_reg=UART2_S1;
	}
	//status_reg = asy_devptr -> SR; /* read processor status flags */
	/*~I*/
	if (status_reg & 0xF000000)
		/*~-*/
	{

		Io_Asy_ch_info_ptr_int[channel].rx_err = 1;
		/*~T*/
		Io_Asy_ch_info_ptr_int[channel].txn_status  = 0; /* reset all states */

		/*~I*/
		if ((Io_Asy_ch_info_ptr_int[channel].err_sig_en))
			/*~-*/
		{
			/*~T*/
			SIG_RaiseFunc(io_asy_config_device_int->asy_config_channel[channel].asy_sig_err);
			/*~-*/
		}

	}

	else
	{
		/*~I*/
		if (status_info & 0x20000000)/* RDRF set */
			/*~-*/
		{

			/*~+:Data received successfully*/
			/*~I*/
			if (Io_Asy_ch_info_ptr_int[channel].rx_number < Io_Asy_ch_info_ptr_int[channel].rx_length)
				/*~-*/
			{
				/*~T*/
				/* Reception of data not yet over */
				/*~T*/
				//Io_Int_EnableInterrupts();

				/*~T*/
				Io_Asy_ch_info_ptr_int[channel].txn_status |= Io_Asy_STAT_RX_BUSY;/* change Receiver state to busy */
				/*~T*/

				//Io_Asy_ch_info_ptr_int[channel].rx_buf[Io_Asy_ch_info_ptr_int[channel].rx_number] = (asy_devptr -> DR);

				Io_Asy_ch_info_ptr_int[channel].rx_number++; /* increment number of bytes received */
				/*~T*/
				//Io_Int_EnableInterrupts();

				/*~I*/
				if (Io_Asy_ch_info_ptr_int[channel].rx_number == Io_Asy_ch_info_ptr_int[channel].rx_length)
					/*~-*/
				{
					/*~T*/
					/*Received number of data is equal to the intended rx_length configured by rx_length operation,So change the status to Rx idle*/
					/*~T*/
					//Io_Int_DisableInterrupts();
					/*~T*/
					Io_Asy_ch_info_ptr_int[channel].txn_status &= (uint8)(~(uint8)Io_Asy_STAT_RX_BUSY); /* Make it Rx Idle */
					/*~T*/
					//Io_Int_EnableInterrupts();

					/*~I*/
					if ((Io_Asy_ch_info_ptr_int[channel].rx_sig_en))
						/*~-*/
					{
						/*~T*/
						SIG_RaiseFunc(io_asy_config_device_int->asy_config_channel[channel].asy_sig_rx);
						/*~-*/
					}
					/*~E*/
					/*~-*/
				}
				/*~E*/
				/*~-*/
			}
			/*~O*/
			/*~-2*/
			else
			{
				/*~T*/
				/*Reception of data exceeds the rx_length ,So dont move the data from the TBUF to the local buffer */
				/*~-*/
			}

		}

	}

}

void Io_Asy_IntIsr(uint8 object, uint32 status_info)/*lint -e{715} : Symbol 'status_info' not referenced */
/*~-*/
{

	uint8 channel;
	uint32 status_reg;
	volatile uint16 dummy_read;  /* to avoid compiler optimization for dummy reads */
	Io_Asy_DeviceStruct* asy_devptr;  /* pointer to register structure*/
	uint8 temp_tx_number;
	uint8 temp_rx_number;
	uint8 mismatch = 0;
	uint16 truncate;

	/*~T*/
	channel = basy_phy_to_log_ch[object];
	/*~T*/
	/* point to either of the  SCI devices depending upon channel */
	asy_devptr = /*lint -e(923) : cast from unsigned long to pointer The array Io_Asy_Dev_Addr acts as a store for the register address, they are defined as unsigned long in the array*/(Io_Asy_DeviceStruct *)
																																																																																				Io_Asy_Dev_Addr[object];

	/*~T*/
	if(channel==0)
	{
		status_reg=UART0_S1;
	}
	else if(channel==1)
	{
		status_reg=UART1_S1;
	}
	else if(channel==2)
	{
		status_reg=UART2_S1;
	}
	//status_reg = asy_devptr -> SR; /* read processor status flags */
	/*~C*/
	switch (Io_Asy_ch_info_ptr_int[channel].txn_status)
	/*~-*/
	{
	/*~F*/
	case 0x0: /* non frame handling*/
	case 0x03: /* tx and rx busy */
	case 0x06: /* frame is ongoing but tx is idle */
	case 0x07: /* frame is ongoing and both rx and tx are busy */
		/*~-*/
	{
		/*~A*/
		/*~+:Frame Handling*/
		/*~I*/
		if (Io_Asy_ch_info_ptr_int[channel].rx_number < Io_Asy_ch_info_ptr_int[channel].rx_length)
			/*~-*/
		{
			/*~T*/
			//	Io_Int_DisableInterrupts();
			/*~T*/
			if(channel==0)
			{
				Io_Asy_ch_info_ptr_int[channel].rx_buf[Io_Asy_ch_info_ptr_int[channel].rx_number] =UART0_D;
			}
			else if(channel==1)
			{
				Io_Asy_ch_info_ptr_int[channel].rx_buf[Io_Asy_ch_info_ptr_int[channel].rx_number] =UART1_D;
			}
			else if(channel==2)
			{
				Io_Asy_ch_info_ptr_int[channel].rx_buf[Io_Asy_ch_info_ptr_int[channel].rx_number] =UART2_D;
			}
			//Io_Asy_ch_info_ptr_int[channel].rx_buf[Io_Asy_ch_info_ptr_int[channel].rx_number] = (asy_devptr -> DR);
			/*~T*/
			Io_Asy_ch_info_ptr_int[channel].rx_number++; /* increment number of bytes received */

			/*~T*/
			//Io_Int_EnableInterrupts();

			/*~I*/
			if (status_reg & 0xF000000) /* Looks for error bit */
				/*~-*/
			{

				Io_Asy_ch_info_ptr_int[channel].rx_err = 1;
				/*~T*/
				Io_Asy_ch_info_ptr_int[channel].txn_status = 0; /* reset all states */;
				/*~I*/
				if ((Io_Asy_ch_info_ptr_int[channel].err_sig_en))
					/*~-*/
				{
					/*~T*/
					SIG_RaiseFunc(io_asy_config_device_int->asy_config_channel[channel].asy_sig_err);

					/*~-*/
				}

			}

			else
			{
				/*~A*/
				/*~+:Read back data mismatch check*/
				/*~I*/
				if (Io_Asy_ch_info_ptr_int[channel].txn_status & 0x01)/* Check the received byte is from slave or is it the transmitted byte from master? */
					/*~-*/
				{
					/*~K*/
					/*~+:Check the transmitted and readback data is matching*/
					/*~T*/
					truncate = Io_Asy_ch_info_ptr_int[channel].data_format;
					/*~T*/
					temp_tx_number = Io_Asy_ch_info_ptr_int[channel].tx_number - 1;
					/*~T*/
					temp_rx_number = Io_Asy_ch_info_ptr_int[channel].rx_number - 1;
					/*~T*/
					truncate = Io_Asy_ch_info_ptr_int[channel].rx_buf[temp_rx_number] & truncate;
					/*~I*/
					if (Io_Asy_ch_info_ptr_int[channel].tx_buf[temp_tx_number] == truncate)
						/*~-*/
					{
						/*~K*/
						/*~+:Received byte match with the transmitted byte*/
						/*~-*/
					}
					/*~O*/
					/*~-2*/
					else
					{
						/*~K*/
						/*~+:Received byte does not match with the transmitted byte*/
						/*~T*/
						mismatch = 1;

						/*~T*/
						//	Io_Int_DisableInterrupts();
						/*~T*/
						Io_Asy_ch_info_ptr_int[channel].data_mismatch = 1;
						/*~T*/
						Io_Asy_ch_info_ptr_int[channel].txn_status = 0;
						/*~T*/
						//Io_Int_EnableInterrupts();

						/*~-*/
					}
					/*~E*/
					/*~-*/
				}
				/*~E*/
				/*~E*/
				/*~I*/
				if (mismatch == 0)
					/*~-*/
				{
					/*~T*/
					//Io_Int_DisableInterrupts();
					/*~T*/
					Io_Asy_ch_info_ptr_int[channel].txn_status |= (uint8)Io_Asy_STAT_RX_BUSY;
					Io_Asy_ch_info_ptr_int[channel].txn_status |= (uint8)Io_Asy_STAT_FRAME_ONGOING;
					/* indicate frame ongoing */
					/*~T*/
					//	Io_Int_EnableInterrupts();

					/*~I*/
					if (Io_Asy_ch_info_ptr_int[channel].tx_number < Io_Asy_ch_info_ptr_int[channel].tx_length)
						/*~-*/
					{
						/*~I*/
						if (Io_Asy_ch_info_ptr_int[channel].txdata_opr_called_twice)
							/*~-*/
						{
							/*~T*/
							/* Txdata operation  has called twice,so dont transmit the next data */
							/*~T*/
							Io_Asy_ch_info_ptr_int[channel].tx_number = 0;
							/*~T*/
							Io_Asy_ch_info_ptr_int[channel].txdata_opr_called_twice = 0;/* Reset the flag */
							/*~-*/
						}
						/*~O*/
						/*~-2*/
						else
						{
							/*~T*/
							if(channel==0)
							{
								UART0_D = Io_Asy_ch_info_ptr_int[channel].tx_buf[Io_Asy_ch_info_ptr_int[channel].tx_number ];
							}
							else if(channel==1)
							{
								UART1_D = Io_Asy_ch_info_ptr_int[channel].tx_buf[Io_Asy_ch_info_ptr_int[channel].tx_number ];
							}
							else if(channel==2)
							{
								UART2_D = Io_Asy_ch_info_ptr_int[channel].tx_buf[Io_Asy_ch_info_ptr_int[channel].tx_number ];
							}
							asy_devptr -> DR  = Io_Asy_ch_info_ptr_int[channel].tx_buf[Io_Asy_ch_info_ptr_int[channel].tx_number ];
							/*~T*/
							Io_Asy_ch_info_ptr_int[channel].tx_number++;
							/*~-*/
						}
						/*~E*/
						/*~-*/
					}
					/*~O*/
					/*~-2*/
					else
					{
						/*~T*/
						//Io_Int_DisableInterrupts();
						/*~T*/
						Io_Asy_ch_info_ptr_int[channel].txn_status &= (uint8)(~(uint8)Io_Asy_STAT_TX_BUSY); /* indicate tx as idle */
						/*~T*/
						//	Io_Int_EnableInterrupts();

						/*~I*/
						if ((Io_Asy_ch_info_ptr_int[channel].tx_sig_en))
							/*~-*/
						{
							/*~T*/
							SIG_RaiseFunc(io_asy_config_device_int->asy_config_channel[channel].asy_sig_tx);
							/*~-*/
						}
						/*~E*/
						/*~-*/
					}
					/*~E*/
					/*~I*/
					if (Io_Asy_ch_info_ptr_int[channel].rx_number < Io_Asy_ch_info_ptr_int[channel].rx_length)
						/*~-*/
					{
						/*~T*/

						/*~-*/
					}
					/*~O*/
					/*~-2*/
					else
					{
						/*~T*/
						Io_Asy_ch_info_ptr_int[channel].txn_status = 0;  /* reset all states */;
						/*~I*/
						if ((Io_Asy_ch_info_ptr_int[channel].rx_sig_en))
							/*~-*/
						{
							/*~T*/
							SIG_RaiseFunc(io_asy_config_device_int->asy_config_channel[channel].asy_sig_rx);
							/*~-*/
						}
						/*~E*/
						/*~-*/
					}
					/*~E*/
					/*~T*/

					/*~-*/
				}
				/*~O*/
				/*~-2*/
				else
				{
					/*~K*/
					/*~+:Read back mismatch error occured in the last transmission and reception so raise the error signal if configured*/
					/*~I*/
					if ((Io_Asy_ch_info_ptr_int[channel].err_sig_en))
						/*~-*/
					{
						/*~T*/
						SIG_RaiseFunc(io_asy_config_device_int->asy_config_channel[channel].asy_sig_err);
						/*~-*/
					}
					/*~E*/
					/*~-*/
				}
				/*~E*/
				/*~-*/
			}
			/*~E*/
			/*~-*/
		}
		/*~O*/
		/*~-2*/
		else
		{
			/*~T*/
			if(channel==0)
			{
				dummy_read =UART0_D;
			}
			else if(channel==1)
			{
				dummy_read=UART1_D;
			}
			else if(channel==2)
			{
				dummy_read =UART2_D;
			}
			//dummy_read = asy_devptr -> DR;         /* clear to avoid the OR error */

			/*~-*/
		}
		/*~E*/
		/*~E*/
		/*~T*/
		break;
		/*~-*/
	}
	/*~E*/
	/*~F*/
	case 0x0B: /* break ongoing and tx and rx are busy */
		/*~-*/
	{
		/*~A*/
		/*~+:Break Frame handling*/
		/*~T*/
		Io_Asy_ch_info_ptr_int[channel].txn_status = 0; /* Clear the status flags */
		/*~T*/
		Io_Asy_ClearStatus(object);
		if(channel==0)
		{
			dummy_read =UART0_D;
		}
		else if(channel==1)
		{
			dummy_read=UART1_D;
		}
		else if(channel==2)
		{
			dummy_read =UART2_D;
		}
		//dummy_read = asy_devptr -> DR;         /* clear to avoid the OR error */

		//dummy_read = asy_devptr -> DR;         /* clear to avoid the OR error */

		/*~I*/
		if (dummy_read != 0)
			/*~-*/
		{
			/*~T*/
			Io_Asy_ch_info_ptr_int[channel].rx_err = 1;
			/*~I*/
			if (Io_Asy_ch_info_ptr_int[channel].err_sig_en)
				/*~-*/
			{
				/*~T*/
				SIG_RaiseFunc( io_asy_config_device_int->asy_config_channel[channel].asy_sig_err );
				/*~-*/
			}

		}

		else
		{
			/*~I*/
			if (Io_Asy_ch_info_ptr_int[channel].rx_sig_en)
				/*~-*/
			{
				/*~T*/
				SIG_RaiseFunc( io_asy_config_device_int->asy_config_channel[channel].asy_sig_rx );
				/*~-*/
			}

		}

		break;
		/*~-*/
	}

	default:
		/*~-*/
	{
		/*~T*/
		/* default case not used */
		/*~T*/
		break;
		/*~-*/
	}

	}

}

/* -------------------------------------------------------- */

void UART_init(uint16 Baud) {

	uint16_t tmp,baud;
	uint16 low,high;
	uint32_t reg_temp = 0;

	/*********************UART0 configurare*****************/
	//SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); ; /* UART0 clock source select as MCGPLLCLK/2*/
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;     /* UART0 clock enabled*/

	//PORTE->PCR[20] |= PORT_PCR_ISF_MASK | PORT_PCR_MUX(4);       /* Interrupt is detected | UART0_RX */
	/* PORTA->PCR2: ISF=1,MUX=2, UART0_TX alterative */
	//	PORTE->PCR[21] |= PORT_PCR_ISF_MASK | PORT_PCR_MUX(4);        /* Interrupt is detected | UART0_TX */



	UART0_C2 &= ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
	UART0_C1 = 0x00;
	UART0_C3 = 0x00;
	UART0->C4 = UART0_C4_OSR(16 - 1);
	UART0_C5 = 0x00;
	UART0->S2 |= 0xC0;
	UART0->MA1 = 0x00;


	baud=(Io_Asy_STU_SYS_FREQ/2)/(Baud*16);
	low=0x00FF&baud;
	high=0x00FF&(baud>>8);

	UART0_BDH &= ~UART_BDH_SBR_MASK;
	UART0_BDH |= (uint8)high;
	UART0_BDL &= ~UART_BDL_SBR_MASK;
	UART0_BDL |=(uint8)low;
	UART0_C2 |= UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK;
	UART0_C2 |=UARTLP_C2_RIE_MASK;




	/*********************UART1 configurare*****************/


	//SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

	// Turn on clock to UART1 module and select 48Mhz clock (FLL/PLL source)
	SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
	//SIM_SOPT5 &= ~SIM_SOPT5_UART1TXSRC_MASK;
	//SIM_SOPT5 |= SIM_SOPT5_UART1TXSRC(0);                 // FLL/PLL source

	// Select "Alt 3" usage to enable UART1 on pins

	//PORTE->PCR[0] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(3);        /* Interrupt is detected | UART1_RX */
	/* PORTA->PCR2: ISF=1,MUX=2, UART1_TX alterative */
	//PORTE->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(3);

	UART1_C2 &= ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
	UART1_C1 = 0x00;
	UART1_C3 = 0x00;
	UART1_C4 |= 0x00;

	UART1->S2 |= 0xC0;



	baud=(Io_Asy_STU_SYS_FREQ/2)/(Baud*16);
	low=0x00FF&baud;
	high=0x00FF&(baud>>8);

	UART1_BDH &= ~UART_BDH_SBR_MASK;
	UART1_BDH |= (uint8)high;
	UART1_BDL &= ~UART_BDL_SBR_MASK;
	UART1_BDL |=(uint8)low;
	UART1_C2 |= UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK;
	UART1_C2 |=UARTLP_C2_RIE_MASK;



	/************UART2**********************/

	//SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

	// Turn on clock to UART1 module and select 48Mhz clock (FLL/PLL source)
	SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
	//SIM_SOPT5 &= ~SIM_SOPT5_UART2TXSRC_MASK;
	//SIM_SOPT5 |= SIM_SOPT5_UART2TXSRC(0);                 // FLL/PLL source

	// Select "Alt 3" usage to enable UART1 on pins

	//PORTE->PCR[22] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(4);        /* Interrupt is detected | UART0_RX */
	/* PORTA->PCR2: ISF=1,MUX=2, UART0_TX alterative */
	//PORTE->PCR[23] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(4);

	UART2_C2 &= ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
	UART2_C1 = 0x00;
	UART2_C3 = 0x00;
	UART2_C4 |= 0x00;

	UART2->S2 |= 0xC0;

	baud=(Io_Asy_STU_SYS_FREQ/2)/(Baud*16);
	low=0x00FF&baud;
	high=0x00FF&(baud>>8);

	UART2_BDH &= ~UART_BDH_SBR_MASK;
	UART2_BDH |= (uint8)high;
	UART2_BDL &= ~UART_BDL_SBR_MASK;
	UART2_BDL |=(uint8)low;
	UART2_C2 |=UARTLP_C2_RIE_MASK;
	UART2_C2 |= UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK;
	//NVIC_EnableIRQ(12);
	//NVIC_EnableIRQ(13);
	Io_Int_EnableInterrupts();
}

void UART0_sendchar( char c) {


	/* Check if transmit data register is empty */
	if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))
	{

		UART0_D = c;

		/* Send the data */

	}

}

void UART1_sendchar( char c) {

	/* Check if transmit data register is empty */

	if ((UART1_S1&UART_S1_TDRE_MASK)||(UART1_S1&UART_S1_TC_MASK))
	{

		UART1_D = c;

		/* Send the data */

	}


}

void UART2_sendchar( char c) {


	/* Check if transmit data register is empty */
	if ((UART2_S1&UART_S1_TDRE_MASK)||(UART2_S1&UART_S1_TC_MASK))
	{

		UART2_D = c;

		/* Send the data */

	}

}

char UART0_receivechar() {
	volatile char c;


	/* Wait while receive data register is empty */
	if((UART0_S1 & UART_S1_RDRF_MASK) != 0)
	{
		/* receive the data */
		c = UART0_D;
	}


	return c;
}

char UART1_receivechar() {
	volatile char c;


	/* Wait while receive data register is empty */
	if((UART1_S1 & UART_S1_RDRF_MASK) != 0)
	{
		/* receive the data */
		c = UART1_D;
	}

	return c;
}

char UART2_receivechar() {
	volatile char c;


	/* Wait while receive data register is empty */
	if((UART2_S1 & UART_S1_RDRF_MASK) != 0)
	{
		/* receive the data */
		c = UART2_D;
	}

	return c;
}

/*void UART0_ISR()
{


	c=UART0_receivechar();
}

void UART1_ISR()
{

	reception[pozition]=UART1_receivechar();
	pozition++;
	UART0_sendchar(transmission[pozition]);
}

void UART2_ISR()
{

	c=UART2_receivechar();
}

 */

