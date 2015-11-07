#include "PLATFORM_TYPES/Std_Types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include<system_MKL26Z4.h>

#ifndef IO_CNFASY_H
#define IO_CNFASY_H


#define BIOS_ASY_MAX_TX_BYTES  (16)
#define BIOS_ASY_MAX_RX_BYTES  (16)
#define BIOS_ASY_STU_SYS_FREQ    DEFAULT_SYSTEM_CLOCK
#define BIOS_ASY_DMA_MAJ_CH(unit,channel) BIOS_INT_DMA_MAJ_CH(unit,channel)

#define BIOS_ASY_LOGICAL_DEVICE_BITSHIFT             (8)
#define BIOS_ASY_CHANNEL_MASK                        (0x00FF)
#define BIOS_ASY_MODE_8Y2                            0x01   /**<    1      8     P(Yes)     2                  */
#define BIOS_ASY_MODE_8Y1                            0x02   /**<    1      8     P(Yes)     1 (M=1 PE=1 M2=0)  */
#define BIOS_ASY_MODE_7Y1                            0x03   /**<    1      7     P(Yes)     1 (M=0 PE=1 M2=0)  */
#define BIOS_ASY_MODE_8N1                            0x04   /**<    1      8     P(No)      1  */
#define BIOS_ASY_MODE_PARITY_EVEN                    (0 << 8)   /**<  Parity type: Even Parity */
#define BIOS_ASY_MODE_PARITY_ODD                     (1 << 8)   /**<  Parity type: Odd Parity */
#define BIOS_ASY_STAT_RX_OVERRUN                     (1 << 27)
#define BIOS_ASY_STAT_RX_NO_OVERRUN                  (0 << 27)
#define BIOS_ASY_STAT_RX_ERR                         (1 << 26)
#define BIOS_ASY_STAT_RX_NO_ERR                      (0 << 26)
#define BIOS_ASY_STAT_RX_FRAME_ERR                   (1 << 25)
#define BIOS_ASY_STAT_RX_NO_FRAME_ERR                (0 << 25)
#define BIOS_ASY_STAT_RX_PARITY_ERR                  (1 << 24)
#define BIOS_ASY_STAT_RX_NO_PARITY_ERR               (0 << 24)
#define BIOS_ASY_STAT_RX_TX_NOT_EQUAL                (1 << 23)
#define BIOS_ASY_STAT_RX_TX_EQUAL                    (0 << 23)
#define BIOS_ASY_STAT_DEV_ACTIVE                     (1 << 4)
#define BIOS_ASY_STAT_DEV_INACTIVE                   (0 << 4)
#define BIOS_ASY_STAT_BREAK_ONGOING                  (1 << 3)
#define BIOS_ASY_STAT_BREAK_NONE                     (0 << 3)
#define BIOS_ASY_STAT_FRAME_ONGOING                  (1 << 2)
#define BIOS_ASY_STAT_FRAME_NONE                     (0 << 2)
#define BIOS_ASY_STAT_RX_IDLE                        (0 << 1)
#define BIOS_ASY_STAT_RX_BUSY                        (1 << 1)
#define BIOS_ASY_STAT_TX_IDLE                        (0 << 0)
#define BIOS_ASY_STAT_TX_BUSY                        (1 << 0)
#define BIOS_ASY_HALFDUPLEX                          0x0   /**<  device configured for half duplex communication */
#define BIOS_ASY_FULLDUPLEX                          0x1   /**<  device configured for full duplex communication */

#define HAL_ASY_STAT_DEV_ACTIVE                      (BIOS_ASY_STAT_DEV_ACTIVE)
#define HAL_ASY_STAT_DEV_INACTIVE                    (BIOS_ASY_STAT_DEV_INACTIVE)
#define HAL_ASY_STAT_RX_NO_ERR                       (BIOS_ASY_STAT_RX_NO_ERR)
#define HAL_ASY_STAT_RX_ERR                          (BIOS_ASY_STAT_RX_ERR)
#define HAL_ASY_STAT_TX_IDLE                         (BIOS_ASY_STAT_TX_IDLE)
#define HAL_ASY_STAT_TX_BUSY                         (BIOS_ASY_STAT_TX_BUSY)
#define HAL_ASY_STAT_RX_IDLE                         (BIOS_ASY_STAT_RX_IDLE)
#define HAL_ASY_STAT_RX_BUSY                         (BIOS_ASY_STAT_RX_BUSY)
#define HAL_ASY_STAT_RX_OVERRUN                      (BIOS_ASY_STAT_RX_OVERRUN)
#define HAL_ASY_STAT_RX_NO_OVERRUN                   (BIOS_ASY_STAT_RX_NO_OVERRUN)
#define HAL_ASY_STAT_RX_PARITY_ERR                   (BIOS_ASY_STAT_RX_PARITY_ERR)
#define HAL_ASY_STAT_RX_NO_PARITY_ERR                (BIOS_ASY_STAT_RX_NO_PARITY_ERR)
#define HAL_ASY_STAT_BREAK_ONGOING                   (BIOS_ASY_STAT_BREAK_ONGOING)
#define HAL_ASY_STAT_BREAK_NONE                      (BIOS_ASY_STAT_BREAK_NONE)
#define HAL_ASY_STAT_FRAME_ONGOING                   (BIOS_ASY_STAT_FRAME_ONGOING)
#define HAL_ASY_STAT_FRAME_NONE                      (BIOS_ASY_STAT_FRAME_NONE)
#define HAL_ASY_STAT_FRAME_ERR                       (BIOS_ASY_STAT_RX_FRAME_ERR)
#define HAL_ASY_STAT_NO_FRAME_ERR                    (BIOS_ASY_STAT_RX_NO_FRAME_ERR)
#define HAL_ASY_STAT_RX_TX_EQUAL                     (BIOS_ASY_STAT_RX_TX_EQUAL)
#define HAL_ASY_STAT_RX_TX_NOT_EQUAL                 (BIOS_ASY_STAT_RX_TX_NOT_EQUAL)


#ifndef BIOS_ASY_config_channel_TYPEDEF
#define BIOS_ASY_config_channel_TYPEDEF
typedef struct  BIOS_ASY_config_channel_tag BIOS_ASY_config_channel;
#endif
/** ASY channel configuration*/
#define HAL_ASY_Initialization() BIOS_ASY_Initialization(&config_asy[0])

struct SIG_definition {
  void (*func) (const void * sig);                                 /**< pointer to function */
  const void *sig;                                             /**< pointer parameter */
};
typedef struct SIG_definition SIG_definition;

static inline void SIG_RaiseFunc(const SIG_definition *sig)
{
	if(sig)
		sig->func(sig->sig);
}

typedef void ( * SIG_func_t)(const void * sig);
typedef void ( * SIG_init)(const void * sig);
typedef void ( * SIG_shut)(const void * sig);

#define SIG_DEFINE(name,func,data)                       \
/*lint -e{923,826,416} integer to pointer / pointer arithmetic */\
  const SIG_definition name  = { (SIG_func_t)(func), (const void *)(data) }
   /**<  To define a signal, that has a pointer parameter (or no parameter), the macro 'SIG_DEFINE' must be used */
#define SIG_DEFINE_WRP_CHTRG(name, func, data)           SIG_DEFINE(name, func, data)
   /**<  To define a signal, that has a channel parameter, the macro 'SIG_DEFINE_WRP_CHTRG' must be used */
#define SIG_DEFINE_WRP_FUNC(name, prio, sig)             \
const SIG_WrapperFunc name##_wrp_func = {prio, sig};                                \
  SIG_DEFINE(name, SIG_WRP_Func, &name##_wrp_func)
   /**<  To define a signal, that performs a priority shift, the macro 'SIG_DEFINE_WRP_FUNC' must be used */
#define SIG_DEFINE_WRP_MUX(name, sig0, sig1, sig2, sig3)   const SIG_WrapperMux name##_wrp_mux = {                                             \
    {                                                                                 \
      (const SIG_definition*)(sig0),                                                  \
      (const SIG_definition*)(sig1),                                                  \
      (const SIG_definition*)(sig2),                                                  \
      (const SIG_definition*)(sig3)                                                   \
    }                                                                                 \
  };                                                                              \
    SIG_DEFINE(name, SIG_WRP_Mux, &name##_wrp_mux)
   /**<  To define a signal, that performs a multiplexing of signals, the macro 'SIG_DEFINE_WRP_MUX' must be used */

struct BIOS_ASY_config_channel_tag
{
	uint8 asy_channel;                                                          /**<  Resource channel identifier */
	uint8 asy_type_of_communication;                                            /**<  Selects Full duplex or Half duplex communication */
	uint16 asy_mode;                                                            /**<  Selects the ASY Frame Format */
	uint32 asy_baudrate;                                                        /**<  Initial baudrate */
	const SIG_definition * asy_sig_tx;                                       /**<  Signal raised after the completion of transmission */
	const SIG_definition * asy_sig_rx;                                       /**<  Signal raised after the completion of reception */
	const SIG_definition * asy_sig_err;                                      /**<  Signal raised when reception fails */
};



#ifndef BIOS_ASY_config_device_TYPEDEF
#define BIOS_ASY_config_device_TYPEDEF
typedef struct  BIOS_ASY_config_device_tag BIOS_ASY_config_device;

extern const BIOS_ASY_config_channel  asy_channels[];
extern const BIOS_ASY_config_device config_asy_device;

extern const uint16 buffer[8];

#endif
/** ASY device configuration structure*/
struct BIOS_ASY_config_device_tag
{
	uint8 asy_number_of_channels;                                               /**<  No of active channels */
	const BIOS_ASY_config_channel *asy_config_channel;                       /**<  pointer to the channel configuration */
};


#ifndef BIOS_ASY_config_peripheral_TYPEDEF
#define BIOS_ASY_config_peripheral_TYPEDEF
typedef struct  BIOS_ASY_config_peripheral_tag BIOS_ASY_config_peripheral;
#endif
/** Consists of all the definitions of all the function pointers to the peripherals*/
struct BIOS_ASY_config_peripheral_tag
{
	const BIOS_ASY_config_device *asy_config_device;
	void (*const asy_init)(const BIOS_ASY_config_device * asy_config_device);
	void (*const asy_init_ch)(uint16 ch);
	void (*const asy_start)(uint16 ch);
	void (*const asy_txdata)(uint16 ch, uint8 tx_length, const uint16 * transmit_buffer);
	uint8 (*const asy_rxdata)(uint16 ch, uint16 * receive_buffer);
	uint32 (*const asy_channelstatus)(uint16 ch);
	void (*const asy_enablerxsig)(uint16 ch, uint8 enable);
	void (*const asy_enableerrsig)(uint16 ch, uint8 enable);
	void (*const asy_enabletxsig)(uint16 ch, uint8 enable);
	void (*const asy_rxlength)(uint16 ch, uint8 rx_length);
	void (*const asy_stop)(uint16 ch);
	void (*const asy_setbaudrate)(uint16 ch, uint32 baudrate);
	uint32 (*const asy_calculatebaudrate)(uint16 ch, uint32 baudrate);
	void (*const asy_sendbreak)(uint16 ch);
	void (*const asy_shutdown)(void);
	void (*const asy_chshutdown)(uint16 ch);
};


#ifndef BIOS_ASY_config_TYPEDEF
#define BIOS_ASY_config_TYPEDEF
typedef struct  BIOS_ASY_config_tag BIOS_ASY_config;
#endif
/** ASY configuration structure*/

struct BIOS_ASY_config_tag
{
	uint8 asy_number_of_peripherals;                                            /**<  Number of peripherals i.e DMA , Interrupt or both */
	const BIOS_ASY_config_peripheral *asy_config_peri;                       /**<  pointer to the peripheral configuration */
};


#endif

extern const  BIOS_ASY_config config_asy[];
extern const SIG_definition BIOS_ASY_SIG_INT0;
extern const SIG_definition BIOS_ASY_SIG_INT1;

extern void BIOS_ASY_IntSendBreak(uint16 ch);
extern void BIOS_ASY_IntCh_ShutDown(uint16 ch);
extern void BIOS_ASY_IntShutDown(void);


extern inline void BASY_ClearStatus(uint16 channel);


#ifndef BASY_PRIVATE_H
#define BASY_PRIVATE_H


#define BIOS_ASY_ESCI_CR3_OFFSET                     0x06   /**<  The macro which gives the offset address for the eSCI_CR3/eSCI_LPR register in MPC5674/(MPC5634 and SPC564A)*/

#ifndef BIOS_ASY_DeviceStruct_TYPEDEF
#define BIOS_ASY_DeviceStruct_TYPEDEF
typedef struct  BIOS_ASY_DeviceStruct_tag BIOS_ASY_DeviceStruct;
#endif
/** SCI control register information*/
struct BIOS_ASY_DeviceStruct_tag
{
   volatile uint32 CR1;                                                        /**<  SCI Control Register 0 */
   volatile uint16 CR2;                                                        /**<  SCI Control Register 1 */
   volatile uint16 DR;                                                         /**<  SCI Data    Register */
   volatile uint32 SR;                                                         /**<  SCI Status  Register */
};

#ifndef BIOS_ASY_CHAN_Struct_TYPEDEF
#define BIOS_ASY_CHAN_Struct_TYPEDEF
typedef struct  BIOS_ASY_CHAN_Struct_tag BIOS_ASY_CHAN_Struct;
#endif
/** Channel Information structure.*/
extern const BIOS_ASY_config  * bios_asy_config;
extern uint8 basy_phy_to_log_ch[3];
extern const uint32 BIOS_ASY_Dev_Addr[3];
struct BIOS_ASY_CHAN_Struct_tag
{
   uint16 data_format;                                                         /**<  Stores the  data format */
   uint8 *tx_buf;                                                             /**<  pointer to the buffer for txn */
   uint8 *rx_buf;                                                             /**<  pointer to the buffer for rxn */
   volatile uint8 txdata_opr_called_twice;                                     /**<  Flag to indicate that the TxData interface is called twice */
   volatile uint8 data_mismatch;                                               /**<  The flag which is used by the driver for the readback data mismatch. */
   volatile uint8 tx_sig_en;                                                   /**<  flag to enable signal after transmission is completed */
   volatile uint8 rx_sig_en;                                                   /**<  flag to enable signal after reception is completed */
   volatile uint8 err_sig_en;                                                  /**<  flag to enable signal after tx/rx failures */
   volatile uint8 txn_status;                                                  /**<  Current status of the asy communication  */
   volatile uint8 rx_err;                                                      /**<  flag to indicate error during frame txn */
   volatile uint8 rx_length;                                                   /**<  number of bytes to be received */
   volatile uint8 tx_length;                                                   /**<  number of bytes to be transmitted */
   volatile uint8 rx_number;                                                   /**<  number of actual received byte */
   volatile uint8 tx_number;                                                   /**<  number of actual transmitted bytes */
};




#endif

