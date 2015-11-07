#include "io_cnfasy.h"

#include "PLATFORM_TYPES/Std_Types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include"MCU_DRIVERS/INT/io_int.h"

#ifndef BASY_INTMAIN_H

#define UARTLP_C4_OSR_MASK                       0x1Fu
#define UARTLP_C4_OSR_SHIFT                      0
#define UARTLP_C4_OSR(x)                         (((uint8_t)(((uint8_t)(x))<<UARTLP_C4_OSR_SHIFT))&UARTLP_C4_OSR_MASK)


#define BASY_INTMAIN_H

#include "PLATFORM_TYPES/Std_Types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"


extern const BIOS_ASY_config_device *bios_asy_config_device_int;   /**<  INT device configuration structure , pointer */

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

extern BIOS_ASY_CHAN_Struct *basy_ch_info_ptr_int;   /**<  INT channel, information pointer  */
extern BIOS_ASY_CHAN_Struct BIOS_ASY_channel_table[3];

extern uint16 tx_table[16];
extern uint16 rx_table[16];

extern void Io_Asy_Initialization(const BIOS_ASY_config_device *asy_config_device);


extern void Io_Asy_Ch_Initialization(uint16 ch);


extern void Io_Asy_Start(uint16 ch);


extern void Io_Asy_TxData(uint16 ch, uint8 tx_length, const uint8 *transmit_buffer);


extern uint8 Io_Asy_RxData(uint16 ch, uint16 *receive_buffer);


extern uint32 Io_Asy_ChannelStatus(uint16 ch);


extern void Io_Asy_Enable_RxSignal(uint16 ch, uint8 enable);


extern void Io_Asy_Enable_ErrSignal(uint16 ch, uint8 enable);


extern void BIOS_ASY_IntEnable_TxSignal(uint16 ch, uint8 enable);


extern void BIOS_ASY_IntRxLength(uint16 ch, uint8 rx_length);


extern void BIOS_ASY_IntStop(uint16 ch);


extern void Io_Asy_SetBaudrate(uint16 ch, uint32 baudrate);


extern uint32 Io_Asy_CalculateBaudrate(uint16 ch, uint32 baudrate);


extern void Io_Asy_Asy0_Isr(uint32 status_info);


extern void Io_Asy_Asy1_Isr(uint32 status_info);


extern void Io_Asy_Asy2_Isr(uint32 status_info);


extern void BIOS_ASY_IntFdTxIsr(uint8 object);


extern void BIOS_ASY_IntFdRxIsr(uint8 object, uint32 status_info);


extern void BIOS_ASY_IntIsr(uint8 object, uint32 status_info);

#endif

