/*
 * NEW_BCM.c
 *
 * Created: 3/2/2020 1:53:36 PM
 * Author : A_ayman
 */ 

#include "SL/BCM/BCM.h"
#include "MCAL/DIO/registers.h"
#include "SL/Utilis/interrupts.h"
#include "MCAL/UART/UART.h"



#define  RX_ARR_TEST_SIZE 300


uint8_t garr_Buffer[RX_ARR_TEST_SIZE]= {0};

void BCM_UART_CH1_Rx_Consumer()
{
	if (gu8_UART_CH1_RX_Notification == 0 )
	{
		PORTA_DATA =0xff;
		
	}

}

void BCM_SPI_CH1_Rx_Consumer(uint8_t state)
{
	if (state == PASSED)
	{
		/* send what we received to make sure of the data--- kind of test*/
		UART_Send_String(garr_Buffer);
		
		/* unlock the buffer in case we want to use it again*/
		gu8_SPI_Rx_CH1_Buffer_Status = BUFFER_UNLOCKED;
	}
	else
	{
		UART_Send_String("FAILED");
	}

}
int main(void)
{
	//enable global interrupt
	sei();
	/*		UART initialization    */
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
	
	/* BCM configuration to Init SPI */
	gstr_BCM_Config_t BCM_Config = {UART_NO_Channel,SPI_Channel_1,I2C_NO_Channel};
	BCM_Init(&BCM_Config );
	BCM_Receive(garr_Buffer,300,SPI_Channel_1,BCM_SPI_CH1_Rx_Consumer);
	/* Replace with your application code */
	while (1)
	{
		BCM_RxDispatch();
	}
}
