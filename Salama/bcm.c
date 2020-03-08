/*
 * bcm.c
 *
 * Created: 2020-03-01 9:50:15 PM
 *  Author: Ahmed_Salama
 */


/************************************************************************/
/*				 INCLUDES												*/
/************************************************************************/

#include "Error.h"
#include "SPI.h"
#include "uart.h"
#include "BCM.h"
#include "std_types.h"


/************************************************************************/
/*				 DEFINES												*/
/************************************************************************/
#define FIRST_BYTE_SEND					(1)
#define SECOND_BYTE_SEND				(2)
#define OVERHEAD_BYTE_NUMBER				(3)
#define SHIT_LEFT_8BITS					(8)

/*- LOCAL Data types --------------------------------------*/

static void BCM_OneByte_TxComplete_CBK(void);

/*uart and spi not init*/
init_uart uart_0 = {ZERO};
config_spi spi_0 = {ZERO};

/*creating pointer to user's function*/
void (*ptr_userNotification)(uint16_t) = NULL;

/************************************************************************/
/*				 GLOBAL STATIC VARIABLES            			        */
/************************************************************************/
volatile static uint16_t gu16_TxISR_cnt = 0;
volatile static uint16_t gu16_RxISR_cnt = 0;

volatile static uint8_t gu8_rec_value = ZERO;

static uint8_t gu8_ProtocolToUse = ZERO;

static uint8_t gu8_BCM_UartState = NOT_INITIALIZED;
static uint8_t gu8_BCM_SpiState = NOT_INITIALIZED;

static ptrBuffer gptr_TxBuffer = NULL;
static uint16_t gu16_TxSize = 0;

static ptrBuffer gptr_RxBuffer = NULL;
static uint16_t gu16_RxSize = 0;

/************************************************************************/
/*					Dispatcher states			                        */
/************************************************************************/
static uint8_t gu8_BCM_TxDispatcher_State			= BCM_DISPATCHER_IDLE;
static uint8_t gu8_BCM_TxBuffer_LockState			= BCM_TX_BUFFER_UNLOCKED;
static uint8_t gu8_BCM_SendFlag						= BCM_SEND_NOT_TRIGGERED;

static uint8_t gu8_BCM_RxDispatcher_State			= BCM_DISPATCHER_IDLE;
static uint8_t gu8_BCM_RxBuffer_LockState			= BCM_RX_BUFFER_UNLOCKED;
/************************************************************************/
/*						Buffer Overheads                                */
/************************************************************************/
static uint8_t gu8_BCM_TxBuffer_Index = ZERO;
static uint8_t gu8_BCM_TxChecksum = ZERO;

volatile static uint8_t gu8_BCM_RxChecksum = ZERO;

static uint8_t gu8_BCM_TxC_Flag = ZERO;
static volatile uint8_t gu8_uart_BCM_TxC_Flag = BCM_TXC_FLAG_NOT_TRIGGERED;


/************************************************************************/
/*						CALLBACKS DEFINES                               */
/************************************************************************/
static gptr_BCM_TxC_CBK_Func_t gptr_BCM_TxC_CBK_Func = NULL;
ptr_Function gptr_BCM_TxC_CBK = NULL;

/************************************************************************/
/*				 FUNCTIONS IMPLEMENTATION            			        */
/************************************************************************/


/*call back function of BCM_Transmiting*/
static void BCM_OneByte_TxComplete_CBK(void)
{
	gu8_BCM_TxC_Flag = BCM_TXC_FLAG_TRIGGERED;

	gu16_TxISR_cnt++;
}

/**
* @brief: BCM Initialization
* @param: void
* @return: sint8 status code with error code if one occurred
* */
static void BCM_OneByte_RxComplete_CBK(void)
{
	/*receive data in buffer and increment index*/
	gptr_RxBuffer[gu16_RxISR_cnt] = (spi_receiver());

	/*increase buffer by one*/
	gu16_RxISR_cnt++;
}

/**
* @brief: BCM Initialization
* @param: gptr_BCM_TxComplete_CBK: pointer to user TxComplete callback
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS BCM_Init(st_BCM_Cfg_t *st_BCM_Cfg)
{
	ERROR_STATUS ERR_Status = BCM_ERROR_BASE + NO_ERRORS;

	/*check for null ptr*/
	if(st_BCM_Cfg == NULL)
	{
		/*return null error ptr*/
		ERR_Status = BCM_ERROR_BASE + ERROR_NULL_POINTER;
	}
	else
	{
		/* Reset global variable to the init state */
		gptr_TxBuffer = NULL;
		gu16_TxSize = ZERO;
		gu8_BCM_TxBuffer_Index = ZERO;

		/*reset all frame flags and status*/
		gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_IDLE;
		gu8_BCM_TxChecksum = ZERO;
		gu8_BCM_TxC_Flag = BCM_TXC_FLAG_NOT_TRIGGERED;

		/*check for which protocol user chosed*/
		switch(st_BCM_Cfg->u8_Protocol)
		{
			/*for uart sent uart inits*/
			case UART_PROTOCOL:

				/*save that uart used*/
				gu8_ProtocolToUse = UART_PROTOCOL;

				/*check if uart was initialized before*/
				if (gu8_BCM_UartState == INITIALIZED)
				{
					/*save error state that it was init before*/
					ERR_Status = BCM_ERROR_BASE + ERROR_ALREADY_INITIALIZED;
				}
				else
				{
					/* Configure UART */
					st_uart_init.UART_TxC_Cbk_Function = BCM_OneByte_TxComplete_CBK;
					st_uart_init.UART_RxC_Cbk_Function = BCM_OneByte_RxComplete_CBK;

					/* Initialize UART */
					if( uart_init(&st_uart_init) == E_NOK)
					{

						ERR_Status = BCM_ERROR_BASE + ERROR_NOT_INITIALIZED;
					}
					else
					{
						// user call back check
						if(NULL == st_BCM_Cfg->Transmit_Cbk)
						{
							ERR_Status = BCM_ERROR_BASE + ERROR_NULL_POINTER;
						}
						else
						{
							gptr_BCM_TxC_CBK_Func = st_BCM_Cfg->Transmit_Cbk;
						}

					}
					/* Indicate BCM is initialized */
					gu8_BCM_UartState = INITIALIZED;
				}
				break;

				case SPI_PROTOCOL:

					/*save that SPI used*/
					gu8_ProtocolToUse = SPI_PROTOCOL;

					ptr_userNotification = BCM_Cfg.Recieve_Cbk;
				
					/*check if spi was init before*/
					if(gu8_BCM_SpiState == INITIALIZED)
					{
						/*save error state that it was init before*/
						ERR_Status = BCM_ERROR_BASE + ERROR_ALREADY_INITIALIZED;
					}

					else
					{
						/*config spi*/
						st_spi_inits.spi_callback = BCM_OneByte_RxComplete_CBK;

						spi_init(&st_spi_inits);
						gu8_BCM_SpiState = INITIALIZED;

					}
				break;
		}
	}

	return ERR_Status;
}

/**
* @brief: takes pointer to the TX buffer and
* 	  its size, checks if size is <= MAX_BUFFER_SIZE,
* 	  and passes them to the dispatcher.
* @param: ptr_Buffer, u16_Size
* @return: sint8 status code with error code if one occurred
*/
ERROR_STATUS BCM_Send(ptrBuffer ptr_Buffer, uint16_t u16_Size)
{
	ERROR_STATUS ERR_Status = BCM_ERROR_BASE + NO_ERRORS;

    /*check if no module was initialized before sending*/
    if( gu8_BCM_SpiState != INITIALIZED && gu8_BCM_UartState != INITIALIZED)
    {
        ERR_Status = BCM_ERROR_BASE + ERROR_NOT_INITIALIZED;
    }
    else
    {
        if(NULL == ptr_Buffer)
	{

		ERR_Status = BCM_ERROR_BASE + ERROR_NULL_POINTER;
	}
        else
        {
		/*check if buffer is locked or not*/
		if(gu8_BCM_TxBuffer_LockState == UNLOCKED)
		{
		    /*check for buffer length*/
		    if(u16_Size > MAX_BUFFER_SIZE)
            {

                ERR_Status = BCM_ERROR_BASE + BUFFER_NOT_FIT;
            }

            else
            {
            /*init buffer*/
			gptr_TxBuffer = ptr_Buffer;
			gu16_TxSize   = u16_Size;
			gu8_BCM_SendFlag = BCM_SEND_TRIGGERED;
			gu8_BCM_TxBuffer_LockState = LOCKED;
            }
		}
		else
		{
			/*save error flag*/
            ERR_Status = BCM_ERROR_BASE + ERROR_LOCKED_BUFFER;
		}
        }
    }

	return ERR_Status;
}

/**
* @brief: takes pointer to the RX buffer
* 	  and passes it to the dispatcher.
* @param: ptr_Buffer
* @return: sint8 status code with error code if one occurred
*/

ERROR_STATUS BCM_SetupReceive(ptrBuffer ptr_Buffer,uint16_t u16_Rx_size)
{
	/*create error flag*/
	ERROR_STATUS error_flag = BCM_ERROR_BASE;

	if(ptr_Buffer == NULL)
    {
        error_flag = BCM_ERROR_BASE + ERROR_NULL_POINTER;
    }
    else
    {

            /*check if no module was initialized before sending*/
        if( gu8_BCM_SpiState != INITIALIZED && gu8_BCM_UartState != INITIALIZED)
        {
            error_flag = BCM_ERROR_BASE + ERROR_NOT_INITIALIZED;
        }
        else
        {
            if(gu8_BCM_RxBuffer_LockState == UNLOCKED)
            {
            /*save buffer address and length*/
            gptr_RxBuffer = ptr_Buffer;
            gu16_RxSize  = u16_Rx_size;

            }

            /*return error buffer locked*/
            else
            {
                error_flag = ERROR_LOCKED_BUFFER;
            }
        }


    }

	return error_flag;
}

/**
* @brief: Handles data reception.
* @param: void
* @return: sint8 status code with error code if one occurred
*/
ERROR_STATUS BCM_RxDispatcher(void)
{
	/*variable to use it for looping*/
	uint8_t loopVar = ZERO;
	
	/*create error flag*/
	ERROR_STATUS ERROR_Status = BCM_ERROR_BASE + NO_ERRORS;
	
	/*create local length variable*/
	static uint16_t u16_length = ZERO;
	
	/*check for states*/
	switch(gu8_BCM_RxDispatcher_State)
	{
		case BCM_DISPATCHER_IDLE:
										
			/*check if data received and id matches*/
			if(gptr_RxBuffer[ZERO] == (BCM_ID ) && gu16_RxISR_cnt > ZERO)
			{		
			
				/*set State as it's received*/
				gu8_BCM_RxDispatcher_State = BCM_DISPATCHER_RECEIVE;	
			}
			else
			{
				/*set error as ID_NOT_MATCHED*/
				ERROR_Status = BCM_ERROR_BASE + ID_NOT_MATCHED;
			} 
		break;
		
		case BCM_DISPATCHER_RECEIVE:
		
		/*init buffer_length with zero*/
			u16_length = ZERO;
			
			if(gu16_RxISR_cnt >= OVERHEAD_BYTE_NUMBER)
			{
				
				if(u16_length == ZERO)
				{
					/*save length sent by user*/
					u16_length = ((gptr_RxBuffer[FIRST_BYTE_SEND] << SHIT_LEFT_8BITS) + (gptr_RxBuffer[SECOND_BYTE_SEND]));
					
					/*if length more than your buffer maximum size then save error*/
					if(u16_length > (gu16_RxSize ))
					{
						/*length not match then save error BUFFER_NOT_FIT*/
						ERROR_Status = BCM_ERROR_BASE + BUFFER_NOT_FIT;
						
						/*reset idle*/
						gu8_BCM_RxDispatcher_State = BCM_DISPATCHER_IDLE;
					}
					
				else if(gu16_RxISR_cnt > (u16_length+3))
				{
					/*count checksum value*/
					for(loopVar = ZERO; loopVar < (u16_length + OVERHEAD_BYTE_NUMBER) ; loopVar++)
					{
						gu8_BCM_RxChecksum+= gptr_RxBuffer[loopVar];
						gptr_RxBuffer[loopVar] = gptr_RxBuffer[loopVar + OVERHEAD_BYTE_NUMBER];
						
					}
					
					/*compare it to sent check sum*/
					if(gu8_BCM_RxChecksum == gptr_RxBuffer[u16_length + OVERHEAD_BYTE_NUMBER])
					{
					/*if matched move to next state*/		
					gu8_BCM_RxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE;
					
					}
				}
			}
		}
		break;
		
		case BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE:
			
			/*call notification function*/
			BCM_Cfg.Recieve_Cbk(u16_length);
			
			/*Deinit*/
			BCM_DeInit();
		break;
	}
	
	/*return error value*/
	return ERROR_Status;
}

/**
* @brief: Handles data transmission.
* @param: void
	Description : Dispatcher function of Tx that accumlate checksum
	and send data to the receiver in the order predefined at BCM_SEND.
* @return: sint8 status code with error code if one occurred
*/
ERROR_STATUS BCM_TxDispatcher(void)
{
	/*create error flag*/
	ERROR_STATUS ERR_Status = BCM_ERROR_BASE + NO_ERRORS;

	/*check for the protocal to be used*/
	if(gu8_ProtocolToUse == UART_MODE)
	{
		switch(gu8_BCM_TxDispatcher_State)
		{
			case (BCM_DISPATCHER_IDLE):

				if((gu8_BCM_SendFlag == BCM_SEND_TRIGGERED)
				&& (gu8_BCM_TxBuffer_LockState == BCM_TX_BUFFER_UNLOCKED))
				{
					/* Lock the TX buffer */
					gu8_BCM_TxBuffer_LockState = BCM_TX_BUFFER_LOCKED;

					/*send first byte*/
					uart_tx_send(BCM_ID);

					/*move the state to start your sequence*/
					gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE;
				}

			break;

			/*first state which indicate that isr came*/
			case BCM_DISPATCHER_TRANSMIT_BYTE:

				/*check for ISR*/
				if(gu8_BCM_TxC_Flag == BCM_TXC_FLAG_TRIGGERED)
				{
					/*Set state as byte complete*/
					gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE;
				}

			break;

			case BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE:

				/*send byte*/
				if(gu16_TxISR_cnt == FIRST_BYTE_SEND)
				{
					/*send first length byte*/
					uart_tx_send((gu16_TxSize>>8));
				}

				/*send second byte of length*/
				else if(gu16_TxISR_cnt == SECOND_BYTE_SEND)
				{
					/*send second length byte*/
					uart_tx_send(((uint8_t) gu16_TxSize));
				}

				/*last byte for checksum*/
				else if(gu16_TxISR_cnt == (gu16_TxSize+OVERHEAD_BYTE_NUMBER)){

					/* send check sum*/
					uart_tx_send(gu8_BCM_TxChecksum);

					/*reset buffer states to not triggered and unlock it*/
					gu8_BCM_TxC_Flag = BCM_TXC_FLAG_NOT_TRIGGERED;
					gu8_BCM_TxBuffer_LockState = BCM_TX_BUFFER_UNLOCKED;

				}
				/*for data always increment it in check sum and then send it*/
				else
				{
					gu8_BCM_TxChecksum += *gptr_TxBuffer;
						uart_tx_send(*(gptr_TxBuffer++));
				}

				/*change state to receive a new byte*/
				gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE;

				/*reset triggger*/
				gu8_BCM_TxC_Flag = BCM_TXC_FLAG_NOT_TRIGGERED;
			break;

			default:

			break;
		}
	}

	else if(gu8_ProtocolToUse == SPI_PROTOCOL)
	{
		switch(gu8_BCM_TxDispatcher_State)
		{
			case (BCM_DISPATCHER_IDLE):

			if((gu8_BCM_SendFlag == BCM_SEND_TRIGGERED)
			&& (gu8_BCM_TxBuffer_LockState == BCM_TX_BUFFER_UNLOCKED))
			{
				/* Lock the TX buffer */
				gu8_BCM_TxBuffer_LockState = BCM_TX_BUFFER_LOCKED;

				spi_transmitter(BCM_ID);

				gu8_BCM_TxChecksum += BCM_ID;
				/*set state*/
				gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE;
			}
			else;

			break;

			/*first state which indicate that isr came*/
			case BCM_DISPATCHER_TRANSMIT_BYTE:

			/*check for ISR*/
			if(gu8_BCM_TxC_Flag == BCM_TXC_FLAG_TRIGGERED)
			{
				/*Set state as byte complete*/
				gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE;
			}

			break;

			case BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE:

			/*send byte*/
			if(gu16_TxISR_cnt == FIRST_BYTE_SEND)
			{

				/*send first length byte*/
				spi_transmitter((gu16_TxSize>>8));

				/*increase checksum*/
				gu8_BCM_TxChecksum += (gu16_TxSize>>8);
			}
			/*send second byte of length*/
			else if(gu16_TxISR_cnt == SECOND_BYTE_SEND)
			{
				/*send second length byte*/
				spi_transmitter((uint8_t) gu16_TxSize);

				/*increase check sum value*/
				gu8_BCM_TxChecksum += (uint8_t)gu16_TxSize;

			}

			/*last byte for checksum*/
			else if(gu16_TxISR_cnt == (gu16_TxSize+OVERHEAD_BYTE_NUMBER)){

				/* send check sum*/
				spi_transmitter(gu8_BCM_TxChecksum);

				/*reset buffer states to not triggered and unlock it*/
				spi_init(&spi_0);
				gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_IDLE;
				gu8_BCM_TxC_Flag = BCM_TXC_FLAG_NOT_TRIGGERED;
				gu8_BCM_TxBuffer_LockState = BCM_TX_BUFFER_LOCKED;
			}
			/*for data always increment it in check sum and then send it*/
			else
			{
				gu8_BCM_TxChecksum += *gptr_TxBuffer;
				spi_transmitter(*(gptr_TxBuffer++));
			}

			/*convert status to receive new flag*/
			gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE;

			/*reset triggger*/
			gu8_BCM_TxC_Flag = BCM_TXC_FLAG_NOT_TRIGGERED;
			break;
		}
	}

	/*return error status*/
	return ERR_Status;

}

/**
* @Description : function that reinit all configs that was initialized before
	Inputs : none
	Output Error if occured*/
ERROR_STATUS BCM_DeInit(void)
{
	/*create error flag*/
	ERROR_STATUS error_flag = BCM_ERROR_BASE + NO_ERRORS;

	/*check if buffer locked or not*/
	if((gu8_BCM_TxBuffer_LockState == BCM_TX_BUFFER_LOCKED) || (gu8_BCM_RxBuffer_LockState == BCM_RX_BUFFER_LOCKED))

	{
		/*check for which protocol you use to DeInit it*/
		switch(gu8_ProtocolToUse)
		{
			case UART_PROTOCOL:

				/*Deinitialize it*/
				uart_init(&uart_0);
			break;

			case SPI_PROTOCOL:

				/*deinitialize it*/
				spi_init(&spi_0);

			break;

			default:

				/*wrong protocol or not implemented*/
				error_flag = BCM_ERROR_BASE + ERROR_BCM_PROTOCOL_NOT_IMPLEMENTED;
			break;
		}

		/*reset all flags*/
		 gu8_ProtocolToUse = ZERO;

		 gu8_BCM_UartState = NOT_INITIALIZED;
		 gu8_BCM_SpiState = NOT_INITIALIZED;

		 gptr_TxBuffer = NULL;
		 gu16_TxSize = ZERO;

		 gptr_RxBuffer = NULL;
		 gu16_RxSize = ZERO;

		 gu8_BCM_TxDispatcher_State			= BCM_DISPATCHER_IDLE;
		 gu8_BCM_TxBuffer_LockState			= BCM_TX_BUFFER_UNLOCKED;
		 gu8_BCM_SendFlag						= BCM_SEND_NOT_TRIGGERED;

		 gu8_BCM_RxDispatcher_State			= BCM_DISPATCHER_IDLE;
		 gu8_BCM_RxBuffer_LockState			= BCM_RX_BUFFER_UNLOCKED;

		 gu8_BCM_TxBuffer_Index = ZERO;
		 gu8_BCM_TxChecksum = ZERO;

		 gu8_BCM_RxChecksum = ZERO;

		 gu8_BCM_TxC_Flag = ZERO;
		 gu8_uart_BCM_TxC_Flag = BCM_TXC_FLAG_NOT_TRIGGERED;

		 gptr_BCM_TxC_CBK = NULL;
	}

	else{

		/*error buffer cannot be initialized while locked*/
		error_flag = BCM_ERROR_BASE + ERROR_BCM_PROTOCOL_LOCKED;
	}

	return error_flag;
}
