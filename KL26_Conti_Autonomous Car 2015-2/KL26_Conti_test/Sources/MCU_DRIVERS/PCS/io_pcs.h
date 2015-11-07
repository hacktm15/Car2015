/****************************************************************************

COPYRIGHT (C) $Date: Sept 24, 2015 $
$CompanyInfo:  $
ALL RIGHTS RESERVED.                                                 

The reproduction, transmission or use of this document or its contents is  
not permitted without express written authority.                           
Offenders will be liable for damages. All rights, including rights created 
by patent grant or registration of a utility model or design, are reserved.
---------------------------------------------------------------------------

$ProjectName: FRDM KL26-Z PLATFORM $

$Log: io_pcs.h $

$Author: Flueran Gabriel $

 ****************************************************************************/

#ifndef IO_PCS_H
#define IO_PCS_H


/** Includes **/

#include "MKL26Z4.h"
#include "PLATFORM_TYPES/std_types.h"
#include "PLATFORM_TYPES/powersar_addon_types.h"
#include "PLATFORM_TYPES/platform_types.h"

/** end of Includes **/

/** Defines **/

	/* Macros */
#define IO_PCS_GET_PORT(PortPin)      	((PortPin >> 8) & 0x00FF)     /* get port (bit 8-15 of PortPin) */
#define IO_PCS_GET_PIN(PortPin)       	(PortPin & 0x00FF)  		  /* get pin (bit 0-7 of PortPin) */

	/* end of Macros */

#define IO_PCS_INTER_REG_ADDR_SIZE		4		/* specify the inter register addreses size (in uint16) - for ease the access */

#define IO_PCS_PIN_MUXING_INFO         	1       /* pin configuration */
#define IO_PCS_INIT_LEVEL_INFO			2 		/* pin initial level */
#define IO_PCS_DIRECTION_INFO        	3       /* pin direction */
#define IO_PCS_INTERRUPT_INFO			4		/* pin interrupt type */
#define IO_PCS_CONFIG_INFO				5

#define IO_PCS_LEVEL_LOW    			0x0		/* PIN LEVEL LOW*/
#define IO_PCS_LEVEL_HIGH				0x1		/* PIN LEVEL HIGH*/

#define IO_PCS_PIN_0					(uint8)(0)
#define IO_PCS_PIN_1					(uint8)(1)
#define IO_PCS_PIN_2					(uint8)(2)
#define IO_PCS_PIN_3					(uint8)(3)
#define IO_PCS_PIN_4					(uint8)(4)
#define IO_PCS_PIN_5					(uint8)(5)
#define IO_PCS_PIN_6					(uint8)(6)
#define IO_PCS_PIN_7					(uint8)(7)
#define IO_PCS_PIN_8					(uint8)(8)
#define IO_PCS_PIN_9					(uint8)(9)
#define IO_PCS_PIN_10					(uint8)(10)
#define IO_PCS_PIN_11					(uint8)(11)
#define IO_PCS_PIN_12					(uint8)(12)
#define IO_PCS_PIN_13					(uint8)(13)
#define IO_PCS_PIN_14					(uint8)(14)
#define IO_PCS_PIN_15					(uint8)(15)
#define IO_PCS_PIN_16					(uint8)(16)
#define IO_PCS_PIN_17					(uint8)(17)
#define IO_PCS_PIN_18					(uint8)(18)
#define IO_PCS_PIN_19					(uint8)(19)
#define IO_PCS_PIN_20					(uint8)(20)
#define IO_PCS_PIN_21					(uint8)(21)
#define IO_PCS_PIN_22					(uint8)(22)
#define IO_PCS_PIN_23					(uint8)(23)
#define IO_PCS_PIN_24					(uint8)(24)
#define IO_PCS_PIN_25					(uint8)(25)
#define IO_PCS_PIN_26					(uint8)(26)
#define IO_PCS_PIN_27					(uint8)(27)
#define IO_PCS_PIN_28					(uint8)(28)
#define IO_PCS_PIN_29					(uint8)(29)
#define IO_PCS_PIN_30					(uint8)(30)
#define IO_PCS_PIN_31					(uint8)(31)

#define IO_PCS_PIN_0_MASK				(uint32)(0x1 << 0)
#define IO_PCS_PIN_1_MASK				(uint32)(0x1 << 1)
#define IO_PCS_PIN_2_MASK				(uint32)(0x1 << 2)
#define IO_PCS_PIN_3_MASK				(uint32)(0x1 << 3)
#define IO_PCS_PIN_4_MASK				(uint32)(0x1 << 4)
#define IO_PCS_PIN_5_MASK				(uint32)(0x1 << 5)
#define IO_PCS_PIN_6_MASK				(uint32)(0x1 << 6)
#define IO_PCS_PIN_7_MASK				(uint32)(0x1 << 7)
#define IO_PCS_PIN_8_MASK				(uint32)(0x1 << 8)
#define IO_PCS_PIN_9_MASK				(uint32)(0x1 << 9)
#define IO_PCS_PIN_10_MASK				(uint32)(0x1 << 10)
#define IO_PCS_PIN_11_MASK				(uint32)(0x1 << 11)
#define IO_PCS_PIN_12_MASK				(uint32)(0x1 << 12)
#define IO_PCS_PIN_13_MASK				(uint32)(0x1 << 13)
#define IO_PCS_PIN_14_MASK				(uint32)(0x1 << 14)
#define IO_PCS_PIN_15_MASK				(uint32)(0x1 << 15)
#define IO_PCS_PIN_16_MASK				(uint32)(0x1 << 16)
#define IO_PCS_PIN_17_MASK				(uint32)(0x1 << 17)
#define IO_PCS_PIN_18_MASK				(uint32)(0x1 << 18)
#define IO_PCS_PIN_19_MASK				(uint32)(0x1 << 19)
#define IO_PCS_PIN_20_MASK				(uint32)(0x1 << 20)
#define IO_PCS_PIN_21_MASK				(uint32)(0x1 << 21)
#define IO_PCS_PIN_22_MASK				(uint32)(0x1 << 22)
#define IO_PCS_PIN_23_MASK				(uint32)(0x1 << 23)
#define IO_PCS_PIN_24_MASK				(uint32)(0x1 << 24)
#define IO_PCS_PIN_25_MASK				(uint32)(0x1 << 25)
#define IO_PCS_PIN_26_MASK				(uint32)(0x1 << 26)
#define IO_PCS_PIN_27_MASK				(uint32)(0x1 << 27)
#define IO_PCS_PIN_28_MASK				(uint32)(0x1 << 28)
#define IO_PCS_PIN_29_MASK				(uint32)(0x1 << 29)
#define IO_PCS_PIN_30_MASK				(uint32)(0x1 << 30)
#define IO_PCS_PIN_31_MASK				(uint32)(0x1 << 31)


#define IO_PCS_MUX_DISABLE 				(0)     	/* 000 Pin disabled (analog). */
#define IO_PCS_MUX_GPIO  				(1)     	/* 001 Alternative 1 (GPIO). */
#define IO_PCS_MUX_ALT2   				(2)     	/* 010 Alternative 2 (chip-specific). */
#define IO_PCS_MUX_ALT3   				(3)     	/* 011 Alternative 3 (chip-specific). */
#define IO_PCS_MUX_ALT4   				(4)      	/* 100 Alternative 4 (chip-specific). */
#define IO_PCS_MUX_ALT5   				(5)      	/* 101 Alternative 5 (chip-specific). */
#define IO_PCS_MUX_ALT6   				(6)      	/* 110 Alternative 6 (chip-specific). */
#define IO_PCS_MUX_ALT7   				(7)      	/* 111 Alternative 7 (chip-specific). */

#define IO_PCS_INPUT					0		/* pin is configured as input */
#define IO_PCS_OUTPUT                 	1       /* pin is configured as output */

#define IO_PCS_INIT_LOW					0
#define IO_PCS_INIT_HIGH				1

#define IO_PCS_IRQC_DISABLED 			(0)  		/* 0000 Interrupt/DMA request disabled. */
#define IO_PCS_IRQC_DMA_RIS_EDGE 		(1)  		/* 0001 DMA request on rising edge. */
#define IO_PCS_IRQC_DMA_FALL_EDGE		(2)  		/* 0010 DMA request on falling edge. */
#define IO_PCS_IRQC_DMA_BOTH_EDGES		(3)  		/* 0011 DMA request on either edge. */
#define IO_PCS_IRQC_INT_LOW_LEVEL		(8)  		/* 1000 Interrupt when logic zero. */
#define IO_PCS_IRQC_INT_RIS_EDGE 		(9)  		/* 1001 Interrupt on rising edge. */
#define IO_PCS_IRQC_INT_FALL_EDGE		(10) 		/* 1010 Interrupt on falling edge. */
#define IO_PCS_IRQC_INT_BOTH_EDGES		(11) 		/* 1011 Interrupt on either edge. */
#define IO_PCS_IRQC_INT_HIGH_LEVEL		(12) 		/* 1100 Interrupt when logic one. */

#define IO_PCS_ISF_RESET_MASK			(0 << 24)   /* 0 Configured interrupt is not detected. */
#define IO_PCS_ISF_SET_MASK 			(1 << 24)   /* 1 Configured interrupt is detected. */

#define IO_PCS_DSE_LOW_MASK				(0 << 6)    /* 0 Low drive strength is configured on the corresponding pin */
#define IO_PCS_DSE_HIGH_MASK			(1 << 6)    /* 1 High drive strength is configured on the corresponding pin */

#define IO_PCS_PFE_DISABLE_MASK			(0 << 4)    /* 0 Passive input filter is disabled on the corresponding pin. */
#define IO_PCS_PFE_ENABLE_MASK			(1 << 4)    /* 1 Passive input filter is enabled on the corresponding pin. */

#define IO_PCS_SRE_FAST_MASK			(0 << 2)    /* 0 Fast slew rate is configured on the corresponding pin. */
#define IO_PCS_SRE_SLOW_MASK			(1 << 2)    /* 1 Slow slew rate is configured on the corresponding pin. */

#define IO_PCS_PE_DISABLE_MASK 			(0 << 1)    /* 0 Internal pullup or pulldown resistor is not enabled on the
														 corresponding pin.*/
#define IO_PCS_PE_ENABLE_MASK			(1 << 1)    /* 1 Internal pullup or pulldown resistor is enabled on the corresponding
														 pin, if the pin is configured as a digital input.*/

#define IO_PCS_PS_PULL_DOWN_MASK		(0 << 0)   	/* 0 Internal pulldown resistor is enabled on the corresponding pin,
												  	  	 if the corresponding Port Pull Enable field is set.*/
#define IO_PCS_PS_PULL_UP_MASK			(1 << 0)    /* 1 Internal pullup resistor is enabled on the corresponding pin,
												  	  	 if the corresponding Port Pull Enable field is set.*/

#define IO_PCS_PE_DISABLED_MASK			(uint32)(IO_PCS_PE_DISABLE_MASK | IO_PCS_PS_PULL_DOWN_MASK)
#define IO_PCS_PE_PULL_DOWN_MASK		(uint32)(IO_PCS_PE_ENABLE_MASK | IO_PCS_PS_PULL_DOWN_MASK)
#define IO_PCS_PE_PULL_UP_MASK			(uint32)(IO_PCS_PE_ENABLE_MASK | IO_PCS_PS_PULL_UP_MASK)

#define IO_PCS_PORTA  					(0)
#define IO_PCS_PORTB  					(1)
#define IO_PCS_PORTC  					(2)
#define IO_PCS_PORTD  					(3)
#define IO_PCS_PORTE  					(4)

#define IO_PCS_ISFR_NO_ISF_SET			(uint32)0x0

/** end of Defines **/

/** Structure Typedefs and Nested Structures **/

typedef struct Io_Pcs_PortTypeStruct_tag Io_Pcs_PortTypeStruct;
typedef struct Io_Pcs_CnfTypeStruct_tag Io_Pcs_CnfTypeStruct;

/* DESCRIPTION: this structure contains the configuration elements for a uC's Pin. */
struct Io_Pcs_PortTypeStruct_tag
{
	uint8 Port;
	uint8 Pin;
	uint8 PinMuxing;
	uint8 InitLevel;
	uint8 Direction;
	uint8 InterruptType;
	uint32 Cfg;
};

/* DESCRIPTION: this structure contains the configuration elements for all uC's Pins. */
struct Io_Pcs_CnfTypeStruct_tag
{
	uint8 Nr_Of_Pins;
	const Io_Pcs_PortTypeStruct *Io_Pcs_PinPtr;
};

/** end of Structure Typedefs and Nested Structures **/

/** External Global Variables and Constants **/

//extern const Io_Pcs_CnfTypeStruct *pcs_ram_cfg;

/** end of External Global Variables and Constants **/

/** External Interfaces prototypes **/

/* FUNCTION NAME: Io_Pcs_Initialization
 * DESCRIPTION: Initializes the uC's PORTS & PINS for desired functions.
 * @*PtrCnf: pointer to the configuration structure for PCS
 * -> possible values: Io_Pcs_PinPtr
 */
extern void Io_Pcs_Initialization(const Io_Pcs_CnfTypeStruct *PtrCnf);

/* FUNCTION NAME: Io_Pcs_PinDir
 * DESCRIPTION: Sets direction of a given pin.
 * @PortPin: indicates port and pin
 *   - bits 0-7 are used to code pin information
 *   - bits 8-15 are used to code port information
 *  -> possible values: see "io_pcs_cnf.h" file (eg.: CNF_IO_PCS_P0A_00)
 * @dir: selects pin direction (0-input/1-output)
 *  -> possible values: IO_PCS_INPUT
 * 	  	  	  	     	IO_PCS_OUTPUT
 */
extern void Io_Pcs_PinDir(uint16 PortPin, uint8 dir);

/* FUNCTION NAME: Io_Pcs_GetInfo
 * DESCRIPTION: Indicates the required information for a given pin.
 * @PortPin: indicates port and pin
 * 	 - bits 0-7 are used to code pin information
 * 	 - bits 8-15 are used to code port information
 * 	-> possible values: see "io_pcs_cnf.h" file (eg.: CNF_IO_PCS_P0A_00)
 * @detail: The information required for the given pin
 *	-> possible values: IO_PCS_PIN_MUXING_INFO 	-> @return pin muxing info
 *						IO_PCS_INIT_LEVEL_INFO	-> @return pin init level info
 *						IO_PCS_DIRECTION_INFO	-> @return pin dir info
 *						IO_PCS_INTERRUPT_INFO	-> @return pin interrupt info
 *						IO_PCS_CONFIG_INFO     	-> @return pin config info
 */
extern uint32 Io_Pcs_GetInfo(uint16 PortPin, uint8 detail);

/* FUNCTION NAME: Io_Pcs_GetGpioDirection
 * DESCRIPTION: Indicates direction of a pin.
 * @PortPin: indicates port and pin
 * 	 - bits 0-7 are used to code pin information
 * 	 - bits 8-15 are used to code port information
 * 	-> possible values: see "io_pcs_cnf.h" file (eg.: CNF_IO_PCS_P0A_00)
 *	   -> @return pin direction
 */
extern uint8 Io_Pcs_GetGpioDirection(uint16 PortPin);

/* FUNCTION NAME: Io_Pcs_Portc_Portd_Isr
 * DESCRIPTION: Interrupt handler for PORTC and PORTD interrupts
 * @ void
 */
extern void Io_Pcs_Portc_Portd_Isr(void);

/** end of External Interfaces prototypes **/

#endif /* IO_PCS_H */
