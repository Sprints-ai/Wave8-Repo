/*
 * BCM_ECU_1.c
 *
 * Created: 04/03/2020 08:16:57
 *  Author: ahmed_pc
 */ 


#include "SL/BCM/BCM.h"
#include "MCAL/DIO/registers.h"
#include "SL/Utilis/interrupts.h"
#include "MCAL/UART/UART.h"


#define  RX_ARR_TEST_SIZE 300
#define ENTER_ASCII 0x0D 

int main(void)
{
	/* UART INITIALIZATION */
	USART_CFG_t UART1_CFG;
	UART1_CFG.CHAR_DATA_NUMBER = USART_8BIT_DATA;
	UART1_CFG.STOP_BIT_SELECT = USART_1_STOP_BIT;
	UART1_CFG.USART_BAUD_RATE_SELECT = USART_9600_BAUD_RATE;
	UART1_CFG.USART_CLOCK_POLARITY = USART_RISING_TRANSMIT;
	UART1_CFG.USART_MODE = USART_ASYNC_MODE;
	UART1_CFG.USART_PARITY = USART_PARITY_DIS;
	UART1_CFG.USART_RX_TX = USART_RX_TX_Enable;
	UART1_CFG.USART_INTERRUPTS =  USART_Interrupt_Disabl;
	USART_Init2(& UART1_CFG);
	
	uint8_t Welcome_Message [] = "Hello, Please Enter What you want to send... \n";
	uint8_t garr_Rec_Message [RX_ARR_TEST_SIZE] = {0};
   uint8_t u16_Rec_Buffer_Index = ZERO;
	gstr_BCM_Config_t BCM_Config = {UART_NO_Channel,SPI_Channel_1,I2C_NO_Channel};
		
	//BCM Initialization
	BCM_Init(&BCM_Config );
	UART_Send_String( Welcome_Message);
	sei();
	
	while (1)
	{
		while (garr_Rec_Message [u16_Rec_Buffer_Index-1] != ENTER_ASCII && u16_Rec_Buffer_Index< RX_ARR_TEST_SIZE)
		{
			garr_Rec_Message [u16_Rec_Buffer_Index] = USART_Receive_POLLING();
			u16_Rec_Buffer_Index++;
		}
		BCM_Send(garr_Rec_Message,u16_Rec_Buffer_Index-1,SPI_Channel_1);
		UART_Send_String(garr_Rec_Message );
			while(1)
			{
				BCM_TxDispatch();
			}
		}
		
		
		 //
		//BCM_RxDispatch();
	}


