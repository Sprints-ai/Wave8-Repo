/*
* BCM.c
*
* Created: 3/2/2020 1:17:31 AM
*  Author: Abdallah & Amin
*/ 

#include "BCM.h"

/*Global Static Variables*/
static uint8_t gu8flag_uart=0;
static uint8_t gu8flag_spi=1;

/*BCM TX,RX STATES */
volatile uint8_t BCM_UART_RX_State = BCM_IDLE;
volatile uint8_t BCM_UART_TX_State = BCM_IDLE;

volatile uint8_t gu8DIS_State = BCM_IDLE;
volatile uint8_t gu8BUFF_CNT = 0;
volatile uint8_t gu8BUFF_IDX = 0;
volatile uint8_t gu8EXP_RX_Size = 0;
volatile uint8_t gu8LCK_BUFF = BUFFER_UNLOCKED;


/**
 *  @brief BCM Initialization function
 *  
 *  @param [in] bcm_id BCM channel ID
 *  @return ERROR_STATUS
 *  
 *  @details This function initializes the hardware interface and callbacks for the BCM
 */
ERROR_STATUS BCM_Init (uint8_t bcm_id)
{
	ERROR_STATUS E_STAT = E_NOK;
	SPI_ConfigType SPI_Cfg = {
		SPI_MASTER,
		SPI_INTERRUPT_ENABLED,
		SPI_F_OSC_4
	};
	
	UART_ConfigType uart_configtype={
		UART_ASYNCHRONOUS_MODE,
		UART_SENDER_RECEIVER_MODE,
		UART_EIGHT_BITS,
		UART_PARITY_DISABLED,
		UART_ONE_STOP_BIT,
		UART_INTERRUPT_ENABLED
	};
	
	switch (bcm_id){
	case UART_CH:
		UART_TXC_setCallBack(&BCM_UART_Tx_Call_Back);
		UART_RXC_setCallBack(&BCM_UART_Rx_Call_Back);
		UART_init(&uart_configtype);
		sei();	
		gu8flag_uart=1;
		E_STAT = E_OK;
		break;
	case SPI_CH:
		gu8flag_spi=1;
		SPI_setCallBack(&BCM_SPI_Tx_Call_Back);
		//SPI_setCallBack(&BCM_SPI_Rx_Call_Back);
		SPI_init(&SPI_Cfg);
		sei();
		E_STAT = E_OK;
		break;
	}
	return E_STAT;
}

/**
 *  @brief BCM send function
 *  
 *  @param [in] ptr_Buffer pointer to the buffer containing the payload
 *  @param [in] u16_Size   The size of the payload/message
 *  @param [in] u8_Channel The desired BCM channel
 *  @return ERROR_STATUS
 *  
 *  @details This function creates the whole frame of the message containg the message ID and size and calculates the checksum
 */
ERROR_STATUS BCM_Send (uint8_t* ptr_Buffer, uint16_t u16_Size, uint8_t u8_Channel)
{
	ERROR_STATUS E_STAT = E_NOK;
	if (ptr_Buffer!=NULL)
	{
		uint8_t cksum = 0, idx = 0;
		G_BUFF[0] = BCM_PAYLOAD_ID;
		G_BUFF[1] = (uint8_t) u16_Size >> 8;
		G_BUFF[2] = (uint8_t) u16_Size;
		for (idx = 0; idx < u16_Size; idx++)
		{
			G_BUFF[3+idx] = ptr_Buffer[idx];
			cksum += ptr_Buffer[idx];
		}
		G_BUFF[3+idx] = cksum;
		gu8BUFF_CNT = u16_Size + 4;
		E_STAT = E_OK;
	}
	return E_STAT;
}

/**
 *  @brief BCM receive function
 *  
 *  @param [in] u16_Size   The expected number of character to be reseived
 *  @param [in] bcm_id     The BCM chanel to receive the message from
 *  @return ERROR_STATUS
 *  
 *  @details Callback for received data
 */
ERROR_STATUS BCM_Receive (uint16_t u16_Size, uint8_t bcm_id)
{
	ERROR_STATUS E_STAT = E_NOK;
	switch (bcm_id){
	case UART_CH:
		gu8EXP_RX_Size = u16_Size + 3;
		E_STAT = E_OK;
		break;
	case SPI_CH:
		gu8EXP_RX_Size = u16_Size + 3;
		E_STAT = E_OK;
		break;
	}
	return E_STAT;
}

/**
 *  @brief BCM Transmit Dispatcher
 *  
 *  @return void
 */
void BCM_TxDispatch(void)
{
	if(gu8flag_uart==1){
		switch(gu8DIS_State){
		case BCM_IDLE:
			if (gu8BUFF_CNT != 0)
			{
				UART_transmit(G_BUFF[gu8BUFF_IDX]);
				gu8BUFF_IDX++;
			}
			gu8DIS_State = BCM_SENDING_BYTE;
			break;
		case BCM_SENDING_BYTE:
			break;
		case BCM_SENDING_BYTE_COMPLETE:
			if (gu8BUFF_CNT == 0)
			{
				gu8DIS_State = BCM_IDLE;
			}
			else
			{
				UART_transmit(G_BUFF[gu8BUFF_IDX]);
				gu8BUFF_IDX++;
				gu8DIS_State = BCM_SENDING_BYTE;
			}
			break;
		}
	} if(gu8flag_spi==1){
		switch(gu8DIS_State){
		case BCM_IDLE:
			if (gu8BUFF_CNT != 0)
			{
				SPI_sendByte(G_BUFF[gu8BUFF_IDX]);
				gu8BUFF_IDX++;
			}

			gu8DIS_State = BCM_SENDING_BYTE;
			break;
		case BCM_SENDING_BYTE:
			
			break;
		case BCM_SENDING_BYTE_COMPLETE:
			if (gu8BUFF_CNT == 0)
			{
				gu8DIS_State = BCM_IDLE;
			}
			else
			{
				SPI_sendByte(G_BUFF[gu8BUFF_IDX]);
				gu8BUFF_IDX++;
				gu8DIS_State = BCM_SENDING_BYTE;
			}
			break;
		}
	}
}

/**
 *  @brief BCM Receive Dispatcher
 *  
 *  @return void
 */
void BCM_RxDispatch(void)
{
	switch(gu8DIS_State){
	case BCM_IDLE:
		if (gu8BUFF_CNT == gu8EXP_RX_Size)
		{
			uint8_t cksum = 0, idx = 0;
			for (idx = 3; idx < gu8BUFF_CNT; idx++)
			{
				cksum += G_BUFF[idx];
			}
			
			if (cksum == G_BUFF[gu8BUFF_CNT])
			{
				//TODO Err Hanlder
				PORTC_DATA = 0xFF;
			}
		}
		else
		{
			gu8DIS_State = BCM_RECEIVING_BYTE;
		}
		break;
	case BCM_RECEIVING_BYTE:
		break;
	case BCM_RECEIVING_BYTE_COMPLETE:
		break;
	}
}

/**
 *  @brief BCM UART interface receive callback
 *  
 *  @return void
 *  
 *  @details Callback for received data
 */
void BCM_UART_Rx_Call_Back(void)
{
	G_BUFF[gu8BUFF_IDX] = UART_receive();
	if (gu8BUFF_CNT == gu8EXP_RX_Size)
	{	 
		gu8DIS_State = BCM_IDLE;
		return;
	}
	gu8BUFF_IDX++;
	gu8BUFF_CNT++;
	gu8DIS_State = BCM_RECEIVING_BYTE_COMPLETE;
	
}

/**
 *  @brief BCM UART interface sent callback
 *  
 *  @return void
 *  
 *  @details Callback for sent data
 */
void BCM_UART_Tx_Call_Back(void)
{
	gu8BUFF_CNT--;
	gu8DIS_State = BCM_SENDING_BYTE_COMPLETE;
}

/**
 *  @brief BCM SPI interface sent callback
 *  
 *  @return void
 *  
 *  @details Callback for sent data
 */
void BCM_SPI_Tx_Call_Back(void){
	
	gu8BUFF_CNT--;
	gu8DIS_State = BCM_SENDING_BYTE_COMPLETE;
}

