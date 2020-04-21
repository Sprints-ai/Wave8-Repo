/*
 * BCM.c
 *
 * Created: 3/3/2020 10:58:53 AM
 *  Author: Ahmed
 */ 

#include "std_types.h"
#include "registers.h"
#include "USART.h"
#include "SPI.h"
#include "BCM_cfg.h"
#include "BCM.h"

/************************************************************************/
/*							General macros				                */
/************************************************************************/

/*Enable and Disable global interrupts*/
#define ENABLE_GLOBAL_INTRS		SET_BIT(SREG,7)
#define DISABLE_GLOBAL_INTRS	CLEAR_BIT(SREG,7)

/*Operation flags*/
#define ID_FLAG					(0)
#define	LENGTH_FLAG_1			(1)
#define LENGTH_FLAG_2			(2)
#define DATA_FLAG				(3)
#define CHECKSUM_FLAG			(4)
#define END_FLAG				(5)

/************************************************************************/
/*					BCM operation variables                             */
/************************************************************************/	

/*BCM configuration structure*/
BCM_ConfigType bcm_config_struct = BCM_CFG_DATA;

/*Tx & Rx operation flags*/
static uint8_t gu8_txOperationFlag = 0; 
static uint8_t gu8_rxOperationFlag = 0;

/************************************************************************/
/*                  BCM functions' definitions                          */
/************************************************************************/

EnmBCMError_t BCM_Init(void)
{
	/*Variable used in getting BCM error status*/
	EnmBCMError_t bcm_err_var = BCM_OPERATION_SUCCESS;
	
	/*Enable global interrupts*/
	ENABLE_GLOBAL_INTRS;
	
	/*BCM protocol validation*/
	if(bcm_config_struct.bcm_protocol == USART_PROTOCOL)
	{
		USART_init();
	} 
	else
	{
		SPI_init();		
	}
	
	return bcm_err_var;
}

EnmBCMError_t BCM_DeInit(void)
{
	/*Variable used in getting BCM error status*/	
	EnmBCMError_t bcm_err_var = BCM_OPERATION_SUCCESS;

	/*Disable global interrupts*/
	DISABLE_GLOBAL_INTRS;
	
	/*De-Init USART*/
	USART_DeInit();
	
	/*De-Init SPI and Stop it*/
	SPI_DeInit();
	SPI_stop();
	
	return bcm_err_var;
}

EnmBCMError_t BCM_Send(uint8_t* pu8_dataPtr , uint16_t au16_dataSize)
{
	/*BCM Error status variable*/
	EnmBCMError_t bcm_err_var = BCM_OPERATION_SUCCESS;
	
	/*NULL pointer validation*/
	if(pu8_dataPtr == NULL)
	{
		bcm_err_var = BCM_NULL_PTR_ERROR;
	} 
	else
	{
		/*Getting the data and its length*/
		bcm_config_struct.bcm_buffer_length = au16_dataSize;
		bcm_config_struct.bcm_buffer = pu8_dataPtr;
	}
	return bcm_err_var;	
}

EnmBCMError_t BCM_Receive(uint8_t* pu8_dataPtr)
{
	/*BCM Error status variable*/
	EnmBCMError_t bcm_err_var = BCM_OPERATION_SUCCESS;
	
	/*NULL pointer validation*/
	if(pu8_dataPtr == NULL)
	{
		bcm_err_var = BCM_NULL_PTR_ERROR;
	}
	else
	{
		/*Receiving data*/
		bcm_config_struct.bcm_buffer = pu8_dataPtr;
	}	
	return bcm_err_var;
}

EnmBCMError_t BCM_TxDispatch(void)
{
	/*Error variables*/
	EnmBCMError_t bcm_err_var = BCM_OPERATION_FAILED;
	EnmUSARTError_t usart_ret = 0;
	EnmSPIError_t spi_ret = 0;
	
	/*Used protocol validation*/	
	switch(bcm_config_struct.bcm_protocol)
	{
		/*Using USART protocol*/
		case USART_PROTOCOL:
			if(gu8_txOperationFlag == ID_FLAG)
			{
				/*Sending ID byte*/
				usart_ret = USART_sendByteInt(bcm_config_struct.bcm_id);
				
				/*Validating data is sent or not*/
				if(usart_ret == USART_DATA_SENT)
				{
					/*Moving to the next flag*/
					gu8_txOperationFlag++;
				} 
				else
				{
					/*Do nothing*/
				}
			}
			else if(gu8_txOperationFlag == LENGTH_FLAG_1)
			{
				
				/*Sending first length byte*/
				usart_ret = USART_sendByteInt((uint8_t)bcm_config_struct.bcm_buffer_length);
				
				/*Validating data is sent or not*/
				if(usart_ret == USART_DATA_SENT)
				{
					/*Moving to the next flag*/
					gu8_txOperationFlag++;
				}
				else
				{
					/*Do nothing*/
				}
			}
			else if(gu8_txOperationFlag == LENGTH_FLAG_2)
			{
				/*Sending second byte*/
				usart_ret = USART_sendByteInt( (uint8_t)((bcm_config_struct.bcm_buffer_length)>>8) );
			
				/*Validating data is sent or not*/
				if(usart_ret == USART_DATA_SENT)
				{
					/*Moving to the next flag*/
					gu8_txOperationFlag++;
				}
				else
				{
					/*Do nothing*/
				}
			}
			else if(gu8_txOperationFlag == DATA_FLAG)
			{
				/*Variable used in counting sent data*/
				static uint16_t au16_buffer_counter = 0;
				
				/*Sending data*/
				usart_ret = USART_sendByteInt(bcm_config_struct.bcm_buffer[au16_buffer_counter]);
				
				/*Validating the data is sent or not*/
				if(usart_ret == USART_DATA_SENT)
				{
					/*Checksum calculation*/
					bcm_config_struct.bcm_check_sum += bcm_config_struct.bcm_buffer[au16_buffer_counter];
					/*Moving to the next data byte*/
					au16_buffer_counter++;
				}
				else
				{
					/*Do nothing*/
				}
				
				/*Checking that all data bytes is sent or not*/
				if(au16_buffer_counter == bcm_config_struct.bcm_buffer_length)
				{
					/*Moving to the next flag*/
					gu8_txOperationFlag++;
				} 
				else
				{
					/*Do nothing*/
				}
			}
			else if(gu8_txOperationFlag == CHECKSUM_FLAG)
			{
				/*Sending checksum byte*/
				usart_ret = USART_sendByteInt(bcm_config_struct.bcm_check_sum);

				/*Validating data is sent or not*/
				if(usart_ret == USART_DATA_SENT)
				{
					/*Moving to the next flag*/
					gu8_txOperationFlag++;
				}
				else
				{
					/*Do nothing*/
				}
			}
			else if(gu8_txOperationFlag == END_FLAG)
			{
				/*Transmission is done*/
				bcm_err_var = BCM_OPERATION_SUCCESS;
			}
			break;

		case SPI_PROTOCOL:
			
			SPI_start();
			
			if(gu8_txOperationFlag == ID_FLAG)
			{
				/*Sending ID byte*/
				spi_ret = SPI_sendByteInt(bcm_config_struct.bcm_id);
				
				/*Validating byte is sent or not*/
				if(spi_ret == SPI_OPERATION_SUCCESS)
				{
					/*Moving to the next flag*/
					gu8_txOperationFlag++;
				} 
				else
				{
					/*Do nothing*/
				}
			}
			else if(gu8_txOperationFlag == LENGTH_FLAG_1)
			{
				/*Sending first length byte*/	
				spi_ret = SPI_sendByteInt(bcm_config_struct.bcm_buffer_length);

				/*Validating byte is sent or not*/
				if(spi_ret == SPI_OPERATION_SUCCESS)
				{
					/*Moving to the next flag*/
					gu8_txOperationFlag++;
				}
				else
				{
					/*Do nothing*/
				}
			}
			else if(gu8_txOperationFlag == LENGTH_FLAG_2)
			{
				/*Sending the next length byte*/
				spi_ret = SPI_sendByteInt(bcm_config_struct.bcm_buffer_length>>8);

				/*Validating byte is sent or not*/
				if(spi_ret == SPI_OPERATION_SUCCESS)
				{
					/*Moving to the next flag*/
					gu8_txOperationFlag++;
				}
				else
				{
					/*Do nothing*/
				}
			}
			else if(gu8_txOperationFlag == DATA_FLAG)
			{
				/*Counter used to loop over data bytes*/
				static uint16_t au16_buffer_counter = 0;
				
				/*Sending data byte*/	
				spi_ret = SPI_sendByteInt(bcm_config_struct.bcm_buffer[au16_buffer_counter]);
				
				/*Validating data is sent or not*/
				if(spi_ret == SPI_OPERATION_SUCCESS)
				{
					/*Check sum calculation*/
					bcm_config_struct.bcm_check_sum += bcm_config_struct.bcm_buffer[au16_buffer_counter];
					
					/*Moving to the next data byte*/
					au16_buffer_counter++;
				}
				else
				{
					/*Do nothing*/
				}
				
				/*Checking all data bytes is sent or not*/
				if(au16_buffer_counter == bcm_config_struct.bcm_buffer_length)
				{
					/*Moving to the next flag*/
					gu8_txOperationFlag++;
				} 
				else
				{
					/*Do nothing*/
				}
			}
			else if(gu8_txOperationFlag == CHECKSUM_FLAG)
			{
				/*Sending check sum byte*/
				spi_ret = SPI_sendByteInt(bcm_config_struct.bcm_check_sum);

				/*Validating byte is sent or not*/
				if(spi_ret == SPI_OPERATION_SUCCESS)
				{
					/*Moving to the next flag*/
					gu8_txOperationFlag++;
				}
				else
				{
					/*Do nothing*/
				}
			}
			else if(gu8_txOperationFlag == END_FLAG)
			{
				/*Transmission is done*/
				bcm_err_var = BCM_OPERATION_SUCCESS;
			}		
			break;
		
		/*Choosing invalid protocol*/
		default: bcm_err_var = BCM_INVALID_PROTOCOL;
	}
	return bcm_err_var;
}

EnmBCMError_t BCM_RxDispatch(void)
{
	/*Error variables*/
	EnmBCMError_t bcm_err_var = BCM_OPERATION_FAILED;
	EnmUSARTError_t usart_ret = 0;
	EnmSPIError_t spi_ret = 0;
	
	/*Data buffer counter*/
	uint16_t au16_buffer_counter = 0;
	
	/*Temporary data buffer*/
	uint8_t au8_temp_buffer = 0;
	
	/*Received check sum variable*/
	uint8_t au8_received_cs = 0;
	
	/*Checking used protocol*/
	switch(bcm_config_struct.bcm_protocol)
	{
		case USART_PROTOCOL:
			switch(gu8_rxOperationFlag)
			{
				case ID_FLAG:
					/*Receiving ID byte*/
					usart_ret = USART_recvByteInt(&bcm_config_struct.bcm_id);
					
					/*Validating data is received or not*/
					if(usart_ret == USART_DATA_RECEIVED)
					{
						/*Moving to the next flag*/
						gu8_rxOperationFlag++;
					}
					else
					{
						/*Do nothing*/
					}
					break;

				case LENGTH_FLAG_1:
					/*Receiving first length byte*/
					usart_ret = USART_recvByteInt((uint8_t*)&bcm_config_struct.bcm_buffer_length);
					
					/*Validating data is received or not*/
					if(usart_ret == USART_DATA_RECEIVED)
					{
						/*Moving to the next flag*/
						gu8_rxOperationFlag++;
					}
					else
					{
						/*Do nothing*/
					}
					break;

				case LENGTH_FLAG_2:
					/*Receiving the second length byte*/
					usart_ret = USART_recvByteInt(&au8_temp_buffer);
					
					/*Validating data is received or not*/
					if(usart_ret == USART_DATA_RECEIVED)
					{
						/*Getting the full length*/
						bcm_config_struct.bcm_buffer_length |= (au8_temp_buffer<<8); 
						
						/*Moving to the next flag*/
						gu8_rxOperationFlag++;
					}
					else
					{
						/*Do nothing*/
					}
					break;
					
				case DATA_FLAG:
					/*Receiving data byte*/
					usart_ret = USART_recvByteInt(&bcm_config_struct.bcm_buffer[au16_buffer_counter]);
					
					/*Validating data is received or not*/
					if(usart_ret == USART_DATA_RECEIVED)
					{
						/*Calculation of check sum*/
						bcm_config_struct.bcm_check_sum += bcm_config_struct.bcm_buffer[au16_buffer_counter];
						
						/*Moving to the next data byte*/
						au16_buffer_counter++;
					}
					else
					{
						/*Do nothing*/
					}
					
					/*Checking all data bytes is received or not*/
					if((au16_buffer_counter) == bcm_config_struct.bcm_buffer_length)
					{
						/*Moving to the next flag*/
						gu8_rxOperationFlag++;
					} 
					else
					{
						/*Do nothing*/
					}
					break;	

				case CHECKSUM_FLAG:
					/*Receiving the check sum byte*/
					usart_ret = USART_recvByteInt(&au8_received_cs);
					
					/*Validating data is received or not*/				
					if(usart_ret == USART_DATA_RECEIVED)
					{
						/*Check sum validation*/
						if(au8_received_cs == bcm_config_struct.bcm_check_sum)
						{
							/*Moving to the next flag*/
							gu8_rxOperationFlag++;
						}
						else
						{
							/*Return check sum error*/
							bcm_err_var = BCM_CHECKSUM_ERROR;
						}
					}
					else
					{
						/*Do nothing*/
					}
					break;	

				case END_FLAG:
					bcm_err_var = BCM_OPERATION_SUCCESS;
					break;	
				
				default: /*Do nothing*/ break;
			}
			break;
			
		case SPI_PROTOCOL:
			switch(gu8_rxOperationFlag)
			{
				case ID_FLAG:
					/*Receiving ID byte*/
					spi_ret = SPI_recvByteInt(&bcm_config_struct.bcm_id);
					
					/*Validating byte is received or not*/
					if(spi_ret == SPI_OPERATION_SUCCESS)
					{
						/*Moving to the next flag*/
						gu8_rxOperationFlag++;
					}
					else
					{
						/*Do nothing*/
					}
					break;

				case LENGTH_FLAG_1:
					/*Getting the first length byte*/
					spi_ret = SPI_recvByteInt((uint8_t*)&bcm_config_struct.bcm_buffer_length);

					/*Validating byte is received or not*/
					if(spi_ret == SPI_OPERATION_SUCCESS)
					{
						/*Moving to the next flag*/
						gu8_rxOperationFlag++;
					}
					else
					{
						/*Do nothing*/
					}
					break;

				case LENGTH_FLAG_2:
					/*Receiving the next length byte*/
					spi_ret = SPI_recvByteInt(&au8_temp_buffer);
					
					/*Validating byte is received or not*/
					if(spi_ret == SPI_OPERATION_SUCCESS)
					{
						/*Getting the total length*/
						bcm_config_struct.bcm_buffer_length |= (au8_temp_buffer<<8); 
						
						/*Moving to the next flag*/
						gu8_rxOperationFlag++;
					}
					else
					{
						/*Do nothing*/
					}
					break;
					
				case DATA_FLAG:
					/*Receiving data byte*/
					spi_ret = SPI_recvByteInt(&bcm_config_struct.bcm_buffer[au16_buffer_counter]);
					
					/*Validating data is received or not*/
					if(spi_ret == SPI_OPERATION_SUCCESS)
					{
						/*Check sum calculation*/
						bcm_config_struct.bcm_check_sum += bcm_config_struct.bcm_buffer[au16_buffer_counter];
						
						/*Receiving the next data byte*/
						au16_buffer_counter++;
					}
					else
					{
						/*Do nothing*/
					}
					
					/*Checking the all data bytes received or not*/
					if(au16_buffer_counter == bcm_config_struct.bcm_buffer_length)
					{
						/*Moving to the next flag*/
						gu8_rxOperationFlag++;
					} 
					else
					{
						/*Do nothing*/
					}
					break;	

				case CHECKSUM_FLAG:
					/*Receiving the check sum byte*/
					spi_ret = SPI_recvByteInt(&au8_received_cs);
					
					/*Validating byte is received or not*/
					if(spi_ret == SPI_OPERATION_SUCCESS)
					{
						/*Checking the check sum is correct or not*/
						if(au8_received_cs == bcm_config_struct.bcm_check_sum)
						{
							/*Moving to the next flag*/
							gu8_rxOperationFlag++;
						}
						else
						{
							/*check sum error report*/
							bcm_err_var = BCM_CHECKSUM_ERROR;
						}
					}
					else
					{
						/*Do nothing*/
					}
					break;	

				case END_FLAG:
					bcm_err_var = BCM_OPERATION_SUCCESS;
					break;	
				
				default: /*Do nothing*/ break;
			}
			break;
		
		/*Invalid protocol choice*/
		default: bcm_err_var = BCM_INVALID_PROTOCOL;	
	}
	return bcm_err_var;
}