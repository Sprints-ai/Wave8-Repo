/*
 * UART_BCM.c
 *
 * Created: 3/1/2020 7:40:16 PM
 * Author : ahmed
 */ 


#include "BCM.h"

#define BUFFER_SIZE		10
#define EMPTY_BUFFER	0

uint8_t data[BUFFER_SIZE]={EMPTY_BUFFER};

int main (void)
{
	/************************************/
	/*			MASTER					*/
	/************************************/
	
	/* USART's Configuration struct*/
	strUSART_Config_t USART_Config = {
		USART_NORMAL_SPEED,
		USART_RX_POLLING,
		USART_TX_POLLING,
		USART_UDR_EMPTY_POLLING,
		USART_RX_ENABLE,
		USART_TX_ENABLE,
		USART_ASYNC,
		USART_NO_PARITY,
		USART_1_STOP_BIT,
		USART_8_BIT_CHR
	};
	
	
	ENABLE_GINT;		/* Enable Global Interrupt */
	
	
	USART_Init(&USART_Config);
	
	BCM_Init();
	
 	BCM_Send (data , BUFFER_SIZE);
	 
	
	uint8_t u8_BufferIndex = EMPTY_BUFFER;		/* Local counter */
	
 	uint8_t u8_ReceivedChar = NULL_CHAR;		/*Variable to receive the byte in*/
	 
	while(1)
	{
		/*keep receiving bytes via UART until the buffer is FULL Then send the 
		whole buffer via BCM_TxDispatch*/
		if (u8_BufferIndex < EMPTY_BUFFER)
		{
			
			USART_ReceiveChar(&u8_ReceivedChar);
			data[u8_BufferIndex] = u8_ReceivedChar;
			
			u8_BufferIndex++;
			
		}
		else
		{
			BCM_TxDispatch();
		}
		
	}
}

