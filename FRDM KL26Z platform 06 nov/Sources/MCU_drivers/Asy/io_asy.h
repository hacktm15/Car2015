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

$Log: io_asy.h $

$Author: Iovescu Raul $

 ****************************************************************************/

#ifndef IO_ASY_H
#define IO_ASY_H


#include "MCU_DRIVERS/INT/io_int.h"

#include "io_asy_cnf.h"

#define UARTLP_C4_OSR_MASK                       0x1Fu
#define UARTLP_C4_OSR_SHIFT                      0
#define UARTLP_C4_OSR(x)                         (((uint8_t)(((uint8_t)(x))<<UARTLP_C4_OSR_SHIFT))&UARTLP_C4_OSR_MASK)

extern const Io_Asy_config_device *io_asy_config_device_int;   /**<  INT device configuration structure , pointer */

extern void UART_init(uint16 Baud);
extern void UART_sendchar( char c);
extern char UART_receivechar();
extern void init_UART0();

extern void UART0_sendchar( char c);
extern char UART0_receivechar();
extern void UART1_sendchar(char c);
extern char UART1_receivechar();
extern void UART2_sendchar(char c);
extern char UART2_receivechar();
extern void UART0_ISR();
extern void UART1_ISR();
extern void UART2_ISR();

extern char c;

extern int length,pozition;
extern char reception[8];
extern const char transmission[8];

extern Io_Asy_Chan_Struct *Io_Asy_ch_info_ptr_int;   /**<  INT channel, information pointer  */
extern Io_Asy_Chan_Struct Io_Asy_channel_table[3];

extern uint8 tx_table[16];
extern uint8 rx_table[16];

extern void Io_Asy_Initialization(const Io_Asy_config_device *asy_config_device);


extern void Io_Asy_Ch_Initialization(uint16 ch);


extern void Io_Asy_Start(uint16 ch);


extern void Io_Asy_TxData(uint16 ch, uint8 tx_length, uint8 *transmit_buffer);


extern void Io_Asy_RxData(uint16 ch, uint8 *receive_buffer);


extern uint32 Io_Asy_ChannelStatus(uint16 ch);


extern void Io_Asy_Enable_RxSignal(uint16 ch, uint8 enable);


extern void Io_Asy_Enable_ErrSignal(uint16 ch, uint8 enable);


extern void Io_Asy_IntEnable_TxSignal(uint16 ch, uint8 enable);


extern void Io_Asy_IntRxLength(uint16 ch, uint8 rx_length);


extern void Io_Asy_IntStop(uint16 ch);


extern void Io_Asy_SetBaudrate(uint16 ch, uint32 baudrate);


extern uint32 Io_Asy_CalculateBaudrate(uint16 ch, uint32 baudrate);


extern void Io_Asy_Asy0_Isr(void);


extern void Io_Asy_Asy1_Isr(void);


extern void Io_Asy_Asy2_Isr(void);


extern void Io_Asy_IntFdTxIsr(uint8 object);


extern void Io_Asy_IntFdRxIsr(uint8 object, uint32 status_info);


extern void Io_Asy_IntIsr(uint8 object, uint32 status_info);


#endif /* IO_ASY_H */
