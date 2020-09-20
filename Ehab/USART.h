/*
 * USART.h
 *
 * Created: 2/12/2020 4:05:19 PM
 *  Author: ahmed
 */ 


#ifndef USART_H_
#define USART_H_


#include "std_types.h"
#include "registers.h"
#include "USART_Config.h"
#include "interrupt.h"

#define BAUDRATE								(((F_CPU)/(BAUD*16ul))-1)
#define ASSIGN_BAUDRATE							UBRRL = BAUDRATE;\
												UBRRH = (BAUDRATE>>8)

#define ITERATION_START							(0)
#define URSEL									(0x80)
#define UDRE									(0x20)
#define RXC										(0x80)
#define TXC										(0x40)

#define UDRIE									(0x20)
#define RXCIE									(0x80)
#define TXCIE									(0x40)

#define USART_DATA_REGISTER_NOT_EMPTY			(!(UCSRA & UDRE))
#define USART_RECEIVE_INCOMPLETE				(!(UCSRA & RXC))

#define USART_2X_SPEED							(0x02)
#define USART_NORMAL_SPEED						(0x00)

#define USART_RX_INTERRUPT_ENABLE				(0x80)
#define USART_RX_POLLING						(0x00)

#define USART_TX_INTERRUPT_ENABLE				(0x40)
#define USART_TX_POLLING						(0x00)

#define USART_UDR_EMPTY_INTERRUPT_ENABLE		(0x20)
#define USART_UDR_EMPTY_POLLING					(0x00)

#define USART_RX_ENABLE							(0x10)
#define USART_RX_DISABLE						(0x00)

#define USART_TX_ENABLE							(0x08)
#define USART_TX_DISABLE						(0x00)

#define USART_ASYNC								(0x00)
#define USART_SYNC								(0x40)

#define USART_EVEN_PARITY						(0x20)
#define USART_ODD_PARITY						(0x30)
#define USART_NO_PARITY							(0x00)

#define USART_1_STOP_BIT						(0x00)
#define USART_2_STOP_BITS						(0x08)

#define USART_5_BIT_CHR							(0x00)
#define USART_6_BIT_CHR							(0x01)
#define USART_7_BIT_CHR							(0x02)
#define USART_8_BIT_CHR							(0x03)
#define USART_9_BIT_CHR							(0x04)
#define USART_9th_BIT_ACTIVATION				(0x02)

#define USART_UDRE_CBK_INDEX					(0)
#define USART_TXC_CBK_INDEX						(1)
#define USART_RXC_CBK_INDEX						(2)

typedef struct strUSART_Config_t{
	uint8_t USART_SPEED;
	uint8_t USART_RX_Interrupt;
	uint8_t USART_TX_Interrupt;
	uint8_t USART_UDR_EmptyInterrupt;
	uint8_t USART_RX_EnableDisable;
	uint8_t USART_TX_EnableDisable;
	uint8_t USART_OperationMode;
	uint8_t USART_Parity;
	uint8_t USART_StopBitsNumber;
	uint8_t USART_CharSize;
	void(*USART_UDRE_CBK)(void);
	void(*USART_TXC_CBK)(void);
	void(*USART_RXC_CBK)(void);
	
}strUSART_Config_t;

/**
 * Description: initializes the USART module
 * @param: Config: USART's configuration struct
 *
 *@return: function's error status
 */
ERROR_STATUS USART_Init(strUSART_Config_t* Config);

/**
 * Description: sends a character via USART
 * @param: u8_Char: the 8-bit character required to be sent
 *
 * @return: function's error status
 */
ERROR_STATUS USART_SendChar(uint8_t u8_Char);

/**
 * Description: receives a character via UART
 * @param: pu8_Char: Output parameter: pointer to receive the 8-bit character in
 *
 * @return: function's error status
 */
ERROR_STATUS USART_ReceiveChar(uint8_t* pu8_Char);

/**
 * Description: sends a string via USART
 * @param: au8_Str: the string required to be sent
 *
 * @return: function's error status
 */
ERROR_STATUS USART_SendString(uint8_t au8_Str[]);

/**
 * Description: receives a string via UART
 * @param: pu8_Char: Output parameter: pointer to receive the string in
 * @param: u16_StringSize: the size of the string
 *
 * @return: function's error status
 */
ERROR_STATUS USART_ReceiveString(uint8_t* pu8_Str , uint16_t u16_StringSize);




#endif /* USART_H_ */