/*
 * BCM.c
 *
 * Created: 3/2/2020 1:25:02 PM
 *  Author: ahmed
 */ 

#include "BCM.h"
#include "Errors.h"

#define INITIAL_VALUE			0

#define	DISPATCH_1ST_ROUND		0
#define	DISPATCH_2ND_ROUND		1
#define	DISPATCH_3RD_ROUND		2

#define  EIGHT_BIT_SHIFTER		8

volatile uint8_t gu8_TXC_Flag = TRUE;
volatile uint8_t gu8_RXC_Flag = FALSE;


uint8_t gu8_FSM_Status = IDLE;

uint16_t gu16_NumberOfBytes = INITIAL_VALUE;

uint8_t *gpu8_PointerToBuffer = NULL;

strUSART_Config_t USART_Config;

strSPI_Config_t SPI_Config;

uint8_t gu8_BCM_InitFlag = FALSE;

uint8_t gu8_BCM_SendFlag = FALSE;
uint8_t gu8_BCM_ReceiveFlag = FALSE;

/**
 *
 * Static function to be called in the Sender's ISR function to set a global flag
 *
 */
static void TX_SetFlag (void)
{
	gu8_TXC_Flag = TRUE;
	
}

/**
 *
 * Static function to be called in the Receiver's ISR function to set a global flag
 *
 */
static void RX_SetFlag (void)
{
	gu8_RXC_Flag = TRUE;
	
}

/**
 * Description: initializes the BCM Module using linking configuration
 *
 * @return: function status
 */
ERROR_STATUS BCM_Init(void)
{
	ERROR_STATUS ERR = E_OK;
	
	switch (BCM_Config.u8_SerialComType)
	{
		case UART:
			if (gu8_BCM_InitFlag == FALSE)
			{
				USART_Config.USART_SPEED = USART_NORMAL_SPEED;
				USART_Config.USART_UDR_EmptyInterrupt =	USART_UDR_EMPTY_POLLING;
				USART_Config.USART_OperationMode = USART_ASYNC;
				USART_Config.USART_Parity = USART_NO_PARITY;
				USART_Config.USART_StopBitsNumber =	USART_1_STOP_BIT;
				USART_Config.USART_CharSize = USART_8_BIT_CHR;
				
				switch (BCM_Config.u8_SenderOrReceiver)
				{
					case SENDER:
						USART_Config.USART_RX_Interrupt = USART_RX_POLLING;
						USART_Config.USART_TX_Interrupt = USART_TX_INTERRUPT_ENABLE;
						USART_Config.USART_RX_EnableDisable = USART_RX_DISABLE;
						USART_Config.USART_TX_EnableDisable = USART_TX_ENABLE;
						USART_Config.USART_TXC_CBK = TX_SetFlag;
						USART_Config.USART_RXC_CBK = NULL;
						break;
						
					case RECEIVER:
						USART_Config.USART_RX_Interrupt = USART_RX_INTERRUPT_ENABLE;
						USART_Config.USART_TX_Interrupt = USART_TX_POLLING;
						USART_Config.USART_RX_EnableDisable = USART_RX_ENABLE;
						USART_Config.USART_TX_EnableDisable = USART_TX_DISABLE;
						USART_Config.USART_TXC_CBK = NULL;
						USART_Config.USART_RXC_CBK = RX_SetFlag;
						break;
					
					default:
						ERR = BCM_MODULE_ID + ERROR_INVALID_PARAMETER;
						break;
				}
				USART_Init(&USART_Config);
				gu8_BCM_InitFlag  = TRUE;	
			}
			else
			{
				ERR = BCM_MODULE_ID + ERROR_MODULE_ALREADY_INITIALIZED;
			}
			break;
			
		case SPI:
			if (gu8_BCM_InitFlag == FALSE)
			{
				SPI_Config.u8_InterruptPollingMode = SPI_INTERRUPT;
				SPI_Config.u8_DataOrder = SPI_MSB_FIRST;
				SPI_Config.u8_ModeNumber = MODE_NUMBER0;
				SPI_Config.u8_ClockRate = SPI_FREQUENCY_DIVIDER_16;
				SPI_Config.u8_Speed = SPI_NORMAL_SPEED;
				SPI_Config.SPI_CBK = TX_SetFlag;
				
				switch(BCM_Config.u8_SenderOrReceiver)
				{
					case SENDER:
						SPI_Config.u8_MasterSlaveSelect = SPI_MASTER_MODE;
						break;
					
					case RECEIVER:
						SPI_Config.u8_MasterSlaveSelect = SPI_SLAVE_MODE;
						break;
					
					default:
						ERR = BCM_MODULE_ID + ERROR_INVALID_PARAMETER ;
						break;
				}
				SPI_Init(&SPI_Config);
				gu8_BCM_InitFlag  = TRUE;
			}
			else
			{
				ERR = BCM_MODULE_ID + ERROR_MODULE_ALREADY_INITIALIZED;
			}
			break;
			
		default:
			ERR = BCM_MODULE_ID + ERROR_INVALID_PARAMETER;
			break;
	
			}
	return ERR;
}

/**
 * Description: Deinitializes the BCM Module
 *
 * @return: function status
 */
ERROR_STATUS BCM_DeInit(void)
{
	ERROR_STATUS ERR = E_OK;

	if (gu8_BCM_InitFlag)
	{
		gu8_BCM_InitFlag = FALSE;
	}
	else
	{
		ERR = BCM_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
	}
	return ERR;
}
/**
 * Description: starts the sender's dispatcher
 *
 * @return: function status
 */
ERROR_STATUS BCM_TxDispatch(void)
{
	
	ERROR_STATUS ERR = E_OK;
	static uint16_t u16_DataBufferIndex = INITIAL_VALUE;
	static uint8_t u8_CHKSUM = INITIAL_VALUE;
	static uint8_t u8_Dispatch_enterence_counter = INITIAL_VALUE;
	
	uint8_t u8_NumberOfBytesLSBs = gu16_NumberOfBytes;
	uint8_t u8_NumberOfBytesMSBs = (gu16_NumberOfBytes >> EIGHT_BIT_SHIFTER);
	if (gu8_BCM_SendFlag)
	{
		
		switch (BCM_Config.u8_SerialComType)
		{
			case UART:
				switch(BCM_Config.u8_SenderOrReceiver)
				{
					case SENDER:
						if(gu8_TXC_Flag)
						{
							gu8_TXC_Flag = FALSE;
							switch (gu8_FSM_Status)
							{
								case IDLE:
									switch(u8_Dispatch_enterence_counter)
									{
										case DISPATCH_1ST_ROUND: 
											USART_SendChar(BCM_ID);
											u8_Dispatch_enterence_counter = DISPATCH_2ND_ROUND;
											break;
										
										case DISPATCH_2ND_ROUND:
											USART_SendChar(u8_NumberOfBytesMSBs);
											u8_Dispatch_enterence_counter = DISPATCH_3RD_ROUND;
											break;
										
										case DISPATCH_3RD_ROUND:
											USART_SendChar(u8_NumberOfBytesLSBs);
											u8_Dispatch_enterence_counter = INITIAL_VALUE;
											gu8_FSM_Status = SENDING;
											break;
									}
									break;
													
								case SENDING:
									if (u16_DataBufferIndex < gu16_NumberOfBytes && gpu8_PointerToBuffer[u16_DataBufferIndex] != NULL_CHAR)
									{
									
										USART_SendChar(gpu8_PointerToBuffer[u16_DataBufferIndex]);
										u8_CHKSUM += gpu8_PointerToBuffer[u16_DataBufferIndex];
										u16_DataBufferIndex++;
									}
									else
									{
										gu8_FSM_Status = SENDING_COMPLETE;
									}
									break;
								
								case SENDING_COMPLETE:
									USART_SendChar(u8_CHKSUM);
									gu8_FSM_Status = IDLE;
									break;
							
							}
						
						}
						break;
				
					case RECEIVER:
						gu8_FSM_Status = BCM_MODULE_ID + ERROR_INVALID_PARAMETER;
						break;
				
					default:
						gu8_FSM_Status = BCM_MODULE_ID + ERROR_INVALID_PARAMETER;
						break;
						
				}
		
			case SPI:
				switch (BCM_Config.u8_SenderOrReceiver)
				{
					case SENDER :
						if(gu8_TXC_Flag)
						{
							gu8_TXC_Flag = FALSE;
						
							switch (gu8_FSM_Status)
							{
								case START_SENDING:
								switch(u8_Dispatch_enterence_counter)
								{
									case DISPATCH_1ST_ROUND:
										SPI_SendChar(BCM_ID);
										u8_Dispatch_enterence_counter = DISPATCH_2ND_ROUND;
										break;
								
									case DISPATCH_2ND_ROUND:
										SPI_SendChar(u8_NumberOfBytesMSBs);
										u8_Dispatch_enterence_counter = DISPATCH_3RD_ROUND;
										break;
								
									case DISPATCH_3RD_ROUND:
										SPI_SendChar(u8_NumberOfBytesLSBs);
										u8_Dispatch_enterence_counter = INITIAL_VALUE;
										gu8_FSM_Status = SENDING;
										break;
								}
								break;
							
								case SENDING:
								if (u16_DataBufferIndex < gu16_NumberOfBytes && gpu8_PointerToBuffer[u16_DataBufferIndex] != NULL_CHAR /*&& gpu8_PointerToBuffer[u16_DataBufferIndex] != '\n'*/)
								{
								
									SPI_SendChar(gpu8_PointerToBuffer[u16_DataBufferIndex]);
									u8_CHKSUM += gpu8_PointerToBuffer[u16_DataBufferIndex];

									u16_DataBufferIndex++;
								}
								else
								{
									gu8_FSM_Status = SENDING_COMPLETE;
									gu8_TXC_Flag = TRUE;
								}
								break;
							
								case SENDING_COMPLETE:
									SPI_SendChar(u8_CHKSUM);
									gu8_FSM_Status = IDLE;
									break;
							
							}
						}
						break;
				
					case RECEIVER :
						gu8_FSM_Status = BCM_MODULE_ID + ERROR_INVALID_PARAMETER;
						break;
				
					default:
						gu8_FSM_Status = BCM_MODULE_ID + ERROR_INVALID_PARAMETER;
						break;
				}
		}
	}
	else
	{
		gu8_FSM_Status = BCM_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
	}
	ERR = gu8_FSM_Status;
	return ERR;
}

/**
 * Description: starts the receiver's dispatcher
 *
 * @return: function status
 */
ERROR_STATUS BCM_RxDispatch(void)
{
	
	ERROR_STATUS ERR = E_OK;
	static uint16_t u16_DataBufferIndex = INITIAL_VALUE;
	static uint8_t u8_CHKSUM = INITIAL_VALUE;
	static uint8_t u8_Dispatch_enterence_counter = INITIAL_VALUE;
	static uint8_t u8_ReceivedID = INITIAL_VALUE;
	static uint16_t u16_ReceivedDataSize = INITIAL_VALUE;
	uint8_t u8_TempValueForMSBs = INITIAL_VALUE;
	uint8_t u8_ReceivedCHKSUM = INITIAL_VALUE;
	
	if (gu8_BCM_ReceiveFlag)
	{
		switch (BCM_Config.u8_SerialComType)
		{
			case UART:
			break;
			
			case SPI:
			switch (BCM_Config.u8_SenderOrReceiver)
			{
				case SENDER:
					ERR = BCM_MODULE_ID + ERROR_INVALID_PARAMETER;
					break;
				
				case RECEIVER:
					if (gu8_RXC_Flag)
					{
						gu8_RXC_Flag = FALSE;
						switch (gu8_FSM_Status)
						{
							case START_RECEIVING:
							
							switch(u8_Dispatch_enterence_counter)
							{
								case DISPATCH_1ST_ROUND:
								SPI_ReceiveChar(&u8_ReceivedID);
								
								u8_Dispatch_enterence_counter = DISPATCH_2ND_ROUND;
								break;
								
								case DISPATCH_2ND_ROUND:
								SPI_ReceiveChar(&u8_TempValueForMSBs);
								
								u16_ReceivedDataSize = u8_TempValueForMSBs;
								
								u16_ReceivedDataSize <<= EIGHT_BIT_SHIFTER;
								
								u8_Dispatch_enterence_counter = DISPATCH_3RD_ROUND;
								break;
								
								case DISPATCH_3RD_ROUND:
								SPI_ReceiveChar(&u8_TempValueForMSBs);
								
								u16_ReceivedDataSize += u8_TempValueForMSBs;
								
								
								u8_Dispatch_enterence_counter = INITIAL_VALUE;
								gu8_FSM_Status = RECEIVING;
								break;
							}
							break;
							
							case RECEIVING:
							if (u16_DataBufferIndex < u16_ReceivedDataSize )
							{
								SPI_ReceiveChar(gpu8_PointerToBuffer + u16_DataBufferIndex );
								u8_CHKSUM += gpu8_PointerToBuffer[u16_DataBufferIndex];
								
								u16_DataBufferIndex++;

							}
							else
							{
								
								gu8_FSM_Status = RECEIVING_COMPLETE;
								gu8_RXC_Flag = TRUE;
							}
							break;
							
							case RECEIVING_COMPLETE:
							
							SPI_ReceiveChar(&u8_ReceivedCHKSUM);
							PORTA_DIR = u8_ReceivedCHKSUM;
							if (u8_ReceivedCHKSUM != u8_CHKSUM)
							{
								gu8_FSM_Status = ERROR_FALSE_DATA_RECEIVED;
								ERR = BCM_MODULE_ID + ERROR_FALSE_DATA_RECEIVED;
								gu8_FSM_Status = IDLE;
							}
							else
							{
								gu8_FSM_Status = IDLE;
								ERR = IDLE;
							}
							
						}
					}
			}
			
		}
	}
	
// 	ERR = gu8_FSM_Status;
	return  ERR;
}
/**
 * Description: sets the buffer and the number of bytes to be sent for the TxDispatcher and initiates it's state machine
 *
 * @param: pu8_Data: input parameter: the buffer that is required to be sent
 * @param: u16_BytesNumber: the size of the buffer (Number of bytes in the buffer)
 *
 * @return: function status
 */
ERROR_STATUS BCM_Send (uint8_t* pu8_Data , uint16_t u16_NumberOfBytes)
{
	ERROR_STATUS ERR = E_OK;
	
	if (pu8_Data != NULL)
	{
		if (gu8_BCM_InitFlag)
		{
			gpu8_PointerToBuffer = pu8_Data;
			if (gu8_FSM_Status == IDLE)
			{
				gu8_FSM_Status = START_SENDING;
				gu16_NumberOfBytes = u16_NumberOfBytes;
				gu8_BCM_SendFlag = TRUE;
			}
		}
		else
		{
			ERR = BCM_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
		}
	}
	else 
	{
		ERR = BCM_MODULE_ID + ERROR_NULL_POINTER;
	}
	
	return ERR;
}

/**
 * Description: sets the buffer to receive the data in for the RxDispatcher and initiates it's state machine
 *
 * @param: pu8_Data: in out parameter: the buffer to receive the data in
 *
 * @return: function status
 */
ERROR_STATUS BCM_Receive(uint8_t* pu8_Data)
{
	ERROR_STATUS ERR = E_OK;
	
	if (pu8_Data != NULL)
	{
		
		if (gu8_BCM_InitFlag)
		{
			gpu8_PointerToBuffer = pu8_Data;
			if (gu8_FSM_Status == IDLE)
			{
				gu8_FSM_Status = START_RECEIVING;
				gu8_BCM_ReceiveFlag = TRUE;
			}
		}
		else
		{
			ERR = BCM_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
		}
	}
	else 
	{
		ERR = BCM_MODULE_ID + ERROR_NULL_POINTER;
	}
	
	return ERR;
}
