/*
 * BCM.c
 *
 * Created: 3/2/2020 1:17:31 AM
 *  Author: Abdallah & Amin
 */ 


/*Includes*/
#include "BCM.h"
#include "UART.h"
#include "avr/interrupt.h"


/*Global Static Variables*/
static uint8_t gu8_flag_uart=0;
static uint8_t gu8_flag_spi=1;



/*Global Variables shared between ISR and Dispature */
volatile uint8_t gu8_BCM_UART_RX_State = BCM_IDLE;
volatile uint8_t gu8_DISPATURE_State = BCM_IDLE;
volatile uint8_t gu8_BUFF_CNT = 0;
volatile uint8_t gu8_BUFF_IDX = 0;
volatile uint8_t gu8_EXP_RX_Size = 0;
volatile uint8_t gu8_LCK_BUFF = BUFFER_UNLOCKED;
	
	
	/*
	Function Name: BCM_Init
	Discribtion: This function is used to initialize  the BCM Module for Specific Communication protocol
	Param: This function takes input value of BCM channel
	return: This function returns error status E_OK , E_NOK
	*/
ERROR_STATUS BCM_Init (uint8_t u8_bcm_id)
{
	ERROR_STATUS u8_error_retval=E_OK;
	/* this is the initialization of SPI communication protocol in case of Receiver*/
		SPI_ConfigType SPI_Cfg = {
			SPI_SLAVE,
			SPI_INTERRUPT_ENABLED,
			SPI_F_OSC_4
		};
		
	/* this the configurations of UART communication protocol in case of Receiver*/	
	UART_ConfigType uart_configtype={
		UART_ASYNCHRONOUS_MODE,
		UART_SENDER_MODE,
		UART_EIGHT_BITS,
		UART_PARITY_DISABLED,
		UART_ONE_STOP_BIT,
		UART_INTERRUPT_DISABLED
	};
	
	/* This switch case is used to initialize the BCM module for UART,SPI or I2C*/ 
	switch (u8_bcm_id)
	{
		case UART_CH:
		    gu8_flag_uart=1;
			//UART_TXC_setCallBack(&BCM_UART_Tx_Call_Back);
			UART_init(&uart_configtype);
			sei();	
			return E_OK;
			break;
		case SPI_CH:
			gu8_flag_spi=1;
			SPI_init(&SPI_Cfg);
			UART_init(&uart_configtype);
			sei();
			return E_OK;
			break;
		case I2C_CH:
		/*To be Handelled */
		return E_OK;	
	}
	
	return E_NOK;
}

/*
	Function Name: BCM_Receive
	Discribtion: This function is used to set the buffer size the BCM Module for Specific Communication protocol ( buffer size + overhead)
	Param: This function takes input value of BCM channel and buffer size 
	return: This function returns error status E_OK , E_NOK
	*/
ERROR_STATUS BCM_Receive (uint16_t u16_Size, uint8_t u8_bcm_id)
{
	
	switch (u8_bcm_id)
	{
		case UART_CH:
		gu8_EXP_RX_Size = u16_Size + 3;
		return E_OK;
		break;
		case SPI_CH:
		gu8_EXP_RX_Size = u16_Size + 3;
		return E_OK;
		break;
		case I2C_CH:
		/*TO be Handelled */
		break;
	}
	return E_NOK;
}


/*
	Function Name: BCM_RxDispatch
	Discribtion: This function is used to choose the state of the recieveing process and calculate the check sum 
	Param: This function takes void
	return: This function returns void
	*/
void BCM_RxDispatch(void)
{
	switch(gu8_DISPATURE_State)
	{
		case BCM_IDLE:
			if (gu8_BUFF_CNT == gu8_EXP_RX_Size)
			{
				uint8_t u8_cksum = 0, u8_idx = 0;
				
				/* this for loop start with index of the first byte of recived data and calculate the checksum*/
				for (u8_idx = 3; u8_idx < gu8_BUFF_CNT; u8_idx++)
				{
					u8_cksum += gu8_BUFF[u8_idx];
				}
				
				if (u8_cksum == gu8_BUFF[gu8_BUFF_CNT])
				{
					/*this is for test of checksum
					PORTC_DATA=0x0F; */
					UART_transmit('K');
					}
					else{
					UART_transmit('F');	
					}
					
				}
			else
			{
				gu8_DISPATURE_State = BCM_RECEIVING_BYTE;
			}
			break;
		case BCM_RECEIVING_BYTE:
			break;
		case BCM_RECEIVING_BYTE_COMPLETE:
			break;
	}
}


/*
	Function Name: SPI_handler
	Discribtion: This function is used to save received byte from transmitter in buffer and change the state  
	Param: Vectored
	return:None
	*/
ISR(SPI_STC_vect)
{
	gu8_BUFF[gu8_BUFF_IDX]=SPI_receiveByte();
	/*
	This is to test the received byte value on data register
	if(gu8_BUFF_IDX==0){
	PORTC_DATA=gu8_BUFF[gu8_BUFF_IDX];
	UART_transmit(PORTC_DATA);
	while(1);
	}
	*/
	UART_transmit(gu8_BUFF[gu8_BUFF_IDX]);
	if (gu8_BUFF_CNT == gu8_EXP_RX_Size)
	{
	gu8_DISPATURE_State = BCM_IDLE;
	}
	else
	{
	gu8_DISPATURE_State = BCM_RECEIVING_BYTE_COMPLETE;
	}
gu8_BUFF_IDX++;
gu8_BUFF_CNT++;
	}


