/*
 * UART_BCM.c
 *
 * Created: 3/1/2020 7:40:16 PM
 * Author : ahmed
 */ 

/*#define F_CPU 16000000ul*/
#include "BCM.h"
/*#include <util/delay.h>*/

#define BUFFER_SIZE			(10)
#define EMPTY_BUFFER		(0)

uint8_t gau8_data[BUFFER_SIZE]={EMPTY_BUFFER};


int main (void)
{
		/************************************/
		/*			SLAVE					*/
		/************************************/
	
	ENABLE_GINT;
	strUSART_Config_t USART_Config = {
		USART_NORMAL_SPEED,
		USART_RX_POLLING,
		USART_TX_POLLING,
		USART_UDR_EMPTY_POLLING,
		USART_RX_DISABLE,
		USART_TX_ENABLE,
		USART_ASYNC,
		USART_NO_PARITY,
		USART_1_STOP_BIT,
		USART_8_BIT_CHR
	};
	USART_Init(&USART_Config);
	BCM_Init();
	BCM_Receive (gau8_data);
	
	
	uint8_t status = START_SENDING;
	uint8_t u8_LocalCounter = EMPTY_BUFFER;
	
	
	while(1)
	{
	    
		while (status != IDLE)
		{
			status = BCM_RxDispatch();
			
			
		}
		
		if (u8_LocalCounter<BUFFER_SIZE)
		{
			
			USART_SendChar(gau8_data[u8_LocalCounter]);
			u8_LocalCounter++;
		}
	}
}

