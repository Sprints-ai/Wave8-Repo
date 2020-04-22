/*
 * BCM.c
 *
 * Created: 3/2/2020 1:17:31 AM
 *  Author: A_ayman
 */ 


/* inclusions */
#include "BCM.h"
#include "BCM_CFG.h"
#include "../../MCAL/SPI/SPI_.h"
#include "../../MCAL/UART/UART.h"


/*LOCAL MACROS*/
/*Channels_flags_Values*/
#define NOT_INITIALIZED    0
#define INITIALIZED		   1


/* UART Receiving CALL BACK Function STATE */
#define RECEIVING_BCM_ID          0
#define RECEIVING_SIZE_PART1      1
#define RECEIVING_SIZE_PART2      2
#define RECEIVING_DATA            3
#define RECEIVING_DATA_COMPLETE   4


/*Global Static Variables*/
 /*SPI_Channels_flags*/
 static uint8_t  gu8_SPI_Channel_1 = NOT_INITIALIZED;
 static uint8_t  gu8_SPI_Channel_2 = NOT_INITIALIZED;
 
 /*UART_Channels_flags*/
 static uint8_t  gu8_UART_Channel_1 = NOT_INITIALIZED;
 static uint8_t  gu8_UART_Channel_2 = NOT_INITIALIZED;
 
 /*I2C_Channels_flags*/
 static uint8_t  gu8_I2C_Channel_1 = NOT_INITIALIZED;
 static uint8_t  gu8_I2C_Channel_2 = NOT_INITIALIZED;
 
/* UART BCM TX,RX Channels STATES */
volatile uint8_t BCM_UART_CH1_RX_State = BCM_IDLE;
volatile uint8_t BCM_UART_CH1_TX_State = BCM_IDLE;

/* SPI BCM TX,RX Channels STATES */
volatile uint8_t BCM_SPI_CH1_RX_State  = BCM_IDLE;
volatile uint8_t BCM_SPI_CH1_TX_State  = BCM_IDLE;


/*UART Channel 1 Buffer and data storage */
uint8_t  gu8_UART_CH1_Tx_Buffer = BUFFER_UNLOCKED;
uint8_t  garr_UART_CH1_Data_Storage [4] = {ZERO};
uint8_t* gptr_UART_Tx_Buffer = NULL;
uint16_t gu8_UART_CH1_Buffer_Index = ZERO;
uint16_t gu16_BCM_UART_CH1_Size = ZERO;
uint8_t  gu8_UART_CH1_Index = ZERO;

/*SPI Channel 1 Buffer and data storage */
uint8_t  gu8_SPI_CH1_Tx_Buffer = BUFFER_UNLOCKED;
uint8_t  gu8_SPI_CH1_Rx_Buffer = BUFFER_UNLOCKED;
uint8_t  garr_SPI_CH1_Data_Storage [4] = {ZERO};
uint8_t* gptr_SPI_Tx_Buffer = NULL;
uint16_t gu8_SPI_CH1_Buffer_Index = ZERO;
uint16_t gu16_BCM_SPI_CH1_Size = ZERO;
uint8_t  gu8_SPI_CH1_Index = ZERO;


/* UART receiving variables*/
uint8_t* gptr_UART_Rx_CH1_Buffer = NULL;
uint16_t gu16_BCM_UART_Rx_CH1_Size = ZERO;
uint8_t  gu8_UART_Rx_CH1_Buffer_Status =BUFFER_UNLOCKED;
uint8_t  garr_UART_Rx_CH1_Data_Storage [4] = {ZERO};
uint8_t  gu8_UART_Rx_CH1_Index = ZERO;
uint16_t gu16_UART_Rx_CH1_Buffer_Index = ZERO;
volatile uint8_t gu8_UART_Rx_CH1_Check_Sum = ZERO;
volatile uint8_t gu8_UART_RX_CH1_State = RECEIVING_BCM_ID ;
volatile uint8_t gu8_UART_Rx_CH1_Calculated_Check_Sum = ZERO;
uint8_t  gu8_UART_CH1_RX_Notification = NOT_PASSED;


/* SPI receiving variables*/
uint8_t* gptr_SPI_Rx_CH1_Buffer = NULL;
uint16_t gu16_BCM_SPI_Rx_CH1_Size = ZERO;
uint8_t  gu8_SPI_Rx_CH1_Buffer_Status = BUFFER_UNLOCKED;
uint8_t  garr_SPI_Rx_CH1_Data_Storage [4] = {ZERO};
uint8_t  gu8_SPI_Rx_CH1_Index = ZERO;
uint16_t gu16_SPI_Rx_CH1_Buffer_Index = ZERO;
volatile uint8_t gu8_SPI_Rx_CH1_Check_Sum = ZERO;
volatile uint8_t gu8_SPI_RX_CH1_State = RECEIVING_BCM_ID ;
volatile uint8_t gu8_SPI_Rx_CH1_Calculated_Check_Sum = ZERO;
uint8_t  gu8_SPI_CH1_RX_Notification = NOT_PASSED;


BCM_Rx_Call_Back_ptr gptr_UART_CH1_Rx_Consumer =NULL;
BCM_Rx_Call_Back_ptr gptr_SPI_CH1_Rx_Consumer =NULL;

uint8_t BCM_Init_Flag = NOT_INITIALIZED;

/*
*** this function is responsible for initialize BCM by taking a configuration pointer to structure
*/

ERROR_STATUS BCM_Init (gstr_BCM_Config_t * ConfigPtr )
{
	ERROR_STATUS  Ret_Error = E_OK;
	
	/* create instance  from UART configuration structure */
	USART_CFG_t UART1_CFG;

	if (BCM_Init_Flag == NOT_INITIALIZED)
	{
		/* check if the received pointer to structure not equal NULL*/
		if (ConfigPtr!=NULL)
		{
			switch (ConfigPtr->UART_Channel )
			{  
				case  UART_NO_Channel :
				{
					Ret_Error |= E_OK;
					break;
				}
				case UART_Channel_1 :
				{
					/* UART INITIALIZATION */  
					UART1_CFG.CHAR_DATA_NUMBER = USART_8BIT_DATA;
					UART1_CFG.STOP_BIT_SELECT = USART_1_STOP_BIT;
					UART1_CFG.USART_BAUD_RATE_SELECT = USART_9600_BAUD_RATE;
					UART1_CFG.USART_CLOCK_POLARITY = USART_RISING_TRANSMIT;
					UART1_CFG.USART_MODE = USART_ASYNC_MODE;
					UART1_CFG.USART_PARITY = USART_PARITY_DIS;
					UART1_CFG.USART_RX_TX = USART_RX_TX_Enable;
					UART1_CFG.USART_INTERRUPTS = USART_RX_Complete_Interrupt_Enable|USART_TX_Complete_Interrupt_Enable;
					Ret_Error |= USART_Init2(& UART1_CFG);
					/* set UART Channel 1 flag */
					gu8_UART_Channel_1 = INITIALIZED;
					Ret_Error |= E_OK;
					break;
				}
				case UART_Channel_2 :
				{ /* not handled, for future use*/
					Ret_Error |= E_OK;
					break;
				} 
				default: 
				{
					Ret_Error |= E_NOK;
					Error_Push (BCM_MODULE,ERROR_INVALID_PARAMETER);
					break;
				}			 
			 }
	
			switch (ConfigPtr->SPI_Channel )
			{
				case SPI_NO_Channel :
				{
					Ret_Error |= E_OK;
					break;
				}		
				case SPI_Channel_1 :
				{
					/*    SPI INITIALIZATION    */
					if (SPI_MODE == MASTER)
					{
						Ret_Error |= SPI_Init_(Interrupt_Enable,SPI_Enable,MSB,Master,Leading_Edge_Rising,Leading_Edge_Sample,Frequency_16);
					}
					else if (SPI_MODE == SLAVE)
					{
						Ret_Error |= SPI_Init_(Interrupt_Enable,SPI_Enable,MSB,Slave,Leading_Edge_Rising,Leading_Edge_Sample,Frequency_16);
					}
					else
					{
						Ret_Error |= E_NOK;
						Error_Push (BCM_MODULE,ERROR_INVALID_PARAMETER);
					
					}
				
					/* set SPI Channel 1 flag */
					gu8_SPI_Channel_1 = INITIALIZED;
					Ret_Error |= E_OK;
					break;
					}
				case SPI_Channel_2 :
				{
					// not handled, for future use
					Ret_Error |= E_OK;
					break;
				}
				default:
				{
					Ret_Error |= E_NOK;
					Error_Push (BCM_MODULE,ERROR_INVALID_PARAMETER);
					break;
				}
			 }
			switch (ConfigPtr->I2C_Channel )
			{
				case I2C_NO_Channel :
				{
					Ret_Error |= E_OK;
					break;
				}		
				case I2C_Channel_1 :
				{
					//SPI INITIALIZATION
					//Not Handled, for future use
					gu8_I2C_Channel_1 = INITIALIZED;
					Ret_Error |= E_OK;
					break;
				}
				case I2C_Channel_2 :
				{
					// not handled, for future use
					Ret_Error |= E_OK;
					break;
				}
				default:
				{
					Ret_Error |= E_NOK;
					Error_Push (BCM_MODULE,ERROR_INVALID_PARAMETER);
					break;
				}		
			}
		}
		else
		{
			Ret_Error |= E_NOK;
			Error_Push (BCM_MODULE,ERROR_NULL_POINTER	);
		}
	}
	
	else
	{
		Ret_Error |= E_NOK;
		Error_Push (BCM_MODULE,ERROR_BCM_ALREADY_INITIALIZED	);
		
	}

	/* if the INIT function returns any errors through any of its switch cases that's mean the INIT it function not successfully done*/
	if (Ret_Error != E_NOK)
	{
		BCM_Init_Flag = INITIALIZED;
	}
	else
	{
		Error_Push (BCM_MODULE,ERROR_BCM_NOT_INITIALIZED);
	}
	return Ret_Error;
}


/*
*** this function is responsible for configuring  BCM as a sender 
*/
ERROR_STATUS BCM_Send (uint8_t* ptr_Buffer, uint16_t u16_Size, uint8_t u8_Channel)
{
	ERROR_STATUS Ret_Error = E_OK;
	if( BCM_Init_Flag == INITIALIZED)
	{
		 //NULL Pointer check
		if (ptr_Buffer!=NULL)
		{
			//Making sure that size is greater than zero
			if ( u16_Size>0)
			{
				//selecting the channel we are going to send through it
				switch (u8_Channel)
				{
					case UART_Channel_1:
					{
						if (gu8_UART_Channel_1 == INITIALIZED)
						{	
							gptr_UART_Tx_Buffer = ptr_Buffer;				//save the address of the buffer we want to send
						   gu16_BCM_UART_CH1_Size = u16_Size;				//save the Size of the data we want to send 
							BCM_UART_CH1_TX_State = BCM_IDLE;				//setting the BCM channel state as idle to start 
							UART_Tx_CallBack_Set(BCM_UART_Tx_Call_Back); //setting the channel call back function " what we want to do when interrupt occurs"
						   gu8_UART_CH1_Tx_Buffer = BUFFER_LOCKED;      // setting buffer status as LOCKEd to prevent any modification while sending data from it
							garr_UART_CH1_Data_Storage [ZERO]= BCM_ID+48;
							garr_UART_CH1_Data_Storage [ONE] = ((uint8_t)(u16_Size >> 8)+48);
							garr_UART_CH1_Data_Storage [TWO] = ((uint8_t)(u16_Size)+48);	
						}
						else
						{
							//DO NOTHING
						} 
						Ret_Error |= E_OK;
						break; 
					 }
					 case SPI_Channel_1:
					 {
						if (gu8_SPI_Channel_1 == INITIALIZED)
						{
							gptr_SPI_Tx_Buffer = ptr_Buffer;            //save the address of the buffer we want to send
							gu16_BCM_SPI_CH1_Size = u16_Size;           //save the Size of the data we want to send 
							BCM_SPI_CH1_TX_State = BCM_IDLE;				  //setting the BCM channel state as idle to start 
							gu8_SPI_CH1_Tx_Buffer = BUFFER_LOCKED;      // setting buffer status as LOCKEd to prevent any modification while sending data from it 
							SPI_SET_CallBack(BCM_SPI_Tx_Call_Back);     //setting the channel call back function " what we want to do when interrupt occurs"
							/* these data help us to make sure that user wants to use BCM not any other protocol*/
							garr_SPI_CH1_Data_Storage [ZERO]= BCM_ID;   
							garr_SPI_CH1_Data_Storage [ONE] = (uint8_t)(u16_Size >> 8);
							garr_SPI_CH1_Data_Storage [TWO] = (uint8_t)(u16_Size);
						 }
						 else
						 {
							 //DO NOTHING
						 }
						 Ret_Error |= E_OK;
						 break;
					 }
					 default:
					 {
						 Ret_Error |= E_NOK;
						 Error_Push(BCM_MODULE,ERROR_INVALID_PARAMETER);
						 break;
					 }
					 
				 }
				}
			else //data size is zero or less than 
			{
				Ret_Error |= E_NOK;
				Error_Push (BCM_MODULE,ERROR_INVALID_PARAMETER);
			}
		}
		else
		{
			//error
			Ret_Error |= E_NOK;
			Error_Push (BCM_MODULE,ERROR_BCM_NOT_INITIALIZED);
		}
		 
	}
	else //in case we send NULL Pointer
	{
		Ret_Error |= E_NOK;
		Error_Push (BCM_MODULE,ERROR_NULL_POINTER);
	}
	return Ret_Error;
}

/*
*** this function is responsible for configuring  BCM as a Receiver
*/
ERROR_STATUS BCM_Receive (uint8_t* ptr_Buffer, uint16_t u16_Size, uint8_t u8_Channel,BCM_Rx_Call_Back_ptr Func_ptr )
{
	ERROR_STATUS Ret_Error = E_OK;
	//NULL Pointer check
	if (ptr_Buffer!=NULL)
	{
		if ( u16_Size > ZERO) //check size of the buffer we want to receive in 
		{
			switch (u8_Channel)
			{
				case UART_Channel_1:
				{
					if (gu8_UART_Channel_1 == INITIALIZED)
					{
						gptr_UART_Rx_CH1_Buffer =  ptr_Buffer;           //Save the address of the receiving Buffer
						gu16_BCM_UART_Rx_CH1_Size = u16_Size;            //Save the size of the receiving Buffer
						gptr_UART_CH1_Rx_Consumer = Func_ptr;            //save the address of the consumer function
						gu8_UART_Rx_CH1_Buffer_Status = BUFFER_LOCKED;   //lock buffer to prevent any one to modify it while receiving
						UART_Rx_CallBack_Set (BCM_UART_Rx_Call_Back );   // set UART Call back Function

					}
					else
					{
						//DO NOTHING
					}
					Ret_Error |= E_OK;
					break;
					
				}
				case SPI_Channel_1:
				{
					if (gu8_SPI_Channel_1 == INITIALIZED)
					{
						gptr_SPI_Rx_CH1_Buffer =  ptr_Buffer;				//Save the address of the receiving Buffer											
						gu16_BCM_SPI_Rx_CH1_Size = u16_Size;            //Save the size of the receiving Buffer
						gptr_SPI_CH1_Rx_Consumer = Func_ptr;            //save the address of the consumer function
						gu8_SPI_Rx_CH1_Buffer_Status = BUFFER_LOCKED;   //lock buffer to prevent any one to modify it while receiving                                                
						SPI_SET_CallBack (BCM_SPI_Rx_Call_Back);        // set SPI Call back Function
					}
					else
					{
						//DO NOTHING
					}
					Ret_Error |= E_OK;
					break;
				}
				default:
				{
					Ret_Error |= E_NOK;
					Error_Push(BCM_MODULE,ERROR_INVALID_PARAMETER);
					break;
				}
			}
		}
		else
		{
			//error
			Ret_Error |= E_NOK;
			Error_Push(BCM_MODULE,ERROR_INVALID_PARAMETER);
		}
	}
	else
	{
		Ret_Error |= E_NOK;
		Error_Push(BCM_MODULE,ERROR_NULL_POINTER);
	}
	
	return Ret_Error;
}


/*
*** BCM TX main function, this function is responsible for handling transmission
*/
void BCM_TxDispatch(void)
{
	switch (BCM_UART_CH1_TX_State)
	{
		case BCM_IDLE :
		{
			//Check if th buffer is locked, sending BCM ID
			if (gu8_UART_CH1_Tx_Buffer == BUFFER_LOCKED)
			{
				 USART_SEND_NO_POLLING(garr_UART_CH1_Data_Storage [gu8_UART_CH1_Index ]);
				 gu8_UART_CH1_Index ++;
				 BCM_UART_CH1_TX_State = BCM_SENDING_BYTE;
			}
			else
			{
				//do nothing
			}
			break;
		}
		case BCM_SENDING_BYTE :
		{	
			//do nothing		
			break;
		}
		case BCM_SENDING_BYTE_COMPLETE :
		{ 
			/*this case is to handle sending BCM frame first and without consuming user TX buffer size*/
			if ( gu8_UART_CH1_Index < THREE)
			{
			   USART_SEND_NO_POLLING(garr_UART_CH1_Data_Storage [gu8_UART_CH1_Index ]);
				gu8_UART_CH1_Index++;
				BCM_UART_CH1_TX_State = BCM_SENDING_BYTE;
			}
			/* this case is to handle sending data */
			else if (gu8_UART_CH1_Buffer_Index < gu16_BCM_UART_CH1_Size )
			{
			   USART_SEND_NO_POLLING(gptr_UART_Tx_Buffer [gu8_UART_CH1_Buffer_Index]);
				/*calculating check sum for the received data*/
				garr_UART_CH1_Data_Storage [gu8_UART_CH1_Index ]+=gptr_UART_Tx_Buffer [gu8_UART_CH1_Buffer_Index]; 
				gu8_UART_CH1_Buffer_Index++;
				BCM_UART_CH1_TX_State = BCM_SENDING_BYTE;
				
			}
			else
			{
				// sending check sum 
				USART_SEND_NO_POLLING(garr_UART_CH1_Data_Storage [gu8_UART_CH1_Index ]); 
				gu8_UART_CH1_Tx_Buffer = BUFFER_UNLOCKED;
				BCM_UART_CH1_TX_State = BCM_IDLE;
			}			
			break;
		}
		default:
		{
			Error_Push(BCM_MODULE, ERROR_INVALID_PARAMETER);
			break;
		}
	}
	switch (BCM_SPI_CH1_TX_State)
	{
		case BCM_IDLE :
		{
			//Check if th buffer is locked, sending BCM ID
			if (gu8_SPI_CH1_Tx_Buffer == BUFFER_LOCKED)
			{
				SPI_Send_Unblock(garr_SPI_CH1_Data_Storage [gu8_SPI_CH1_Index ]);
				gu8_SPI_CH1_Index ++;
				BCM_SPI_CH1_TX_State = BCM_SENDING_BYTE;
			}
			else
			{
				//do nothing
			}
			break;
		}
		case BCM_SENDING_BYTE :
		{
			break;
		}
		case BCM_SENDING_BYTE_COMPLETE :
		{
			/*this case is to handle sending BCM frame first and without consuming user TX buffer size*/
			if ( gu8_SPI_CH1_Index < THREE)
			{
				SPI_Send_Unblock(garr_SPI_CH1_Data_Storage [gu8_SPI_CH1_Index ]);
				gu8_SPI_CH1_Index++;
				BCM_SPI_CH1_TX_State = BCM_SENDING_BYTE;
			}
			else if (gu8_SPI_CH1_Buffer_Index < gu16_BCM_SPI_CH1_Size )
			{			
				SPI_Send_Unblock(gptr_SPI_Tx_Buffer [gu8_SPI_CH1_Buffer_Index]);
				//calculating Check sum for the received data
				garr_SPI_CH1_Data_Storage [gu8_SPI_CH1_Index ]+= gptr_SPI_Tx_Buffer [gu8_SPI_CH1_Buffer_Index]; 
				gu8_SPI_CH1_Buffer_Index++;
				BCM_SPI_CH1_TX_State = BCM_SENDING_BYTE;
			
			}
			else
			{
				// sending  check sum
				SPI_Send_Unblock(garr_SPI_CH1_Data_Storage [gu8_SPI_CH1_Index ]); 
				gu8_SPI_CH1_Tx_Buffer = BUFFER_UNLOCKED;
				BCM_SPI_CH1_TX_State = BCM_IDLE;			
			}
			break;
		}
		default:
		{
			Error_Push(BCM_MODULE, ERROR_INVALID_PARAMETER);
			break;
	   }
   }
}
	/*
*** BCM RX main function, this function is responsible for handling Receiving
*/

void BCM_RxDispatch(void)
{
	//check if the UART channel ends receiving all the data
	if (BCM_UART_CH1_RX_State == BCM_RECEIVING_BYTE_COMPLETE)
	{
		//check if the received check sum equal to the calculated check sum
		if (gu8_UART_Rx_CH1_Calculated_Check_Sum == gu8_UART_Rx_CH1_Check_Sum )
 		{
			//call consumer function and passing the status of the sending operation
			gptr_UART_CH1_Rx_Consumer (PASSED);
			BCM_UART_CH1_RX_State = BCM_IDLE;
	   }
		else
		{
			gptr_UART_CH1_Rx_Consumer (NOT_PASSED);
		}
	}
	//check if the SPI channel ends receiving all the data
	if (BCM_SPI_CH1_RX_State == BCM_RECEIVING_BYTE_COMPLETE)
	{
		//check if the received check sum equal to the calculated check sum
		if (gu8_SPI_Rx_CH1_Calculated_Check_Sum == gu8_SPI_Rx_CH1_Check_Sum )
		{
			//call consumer function and passing the status of the sending operation
			gptr_SPI_CH1_Rx_Consumer (PASSED);
			BCM_SPI_CH1_RX_State = BCM_IDLE;
		}
		else
		{
			gptr_SPI_CH1_Rx_Consumer (NOT_PASSED);
		}
	}
		 
}





/* call back functions */


/*
*** this function will be called when UART Rx interrupt occurs
*/
void BCM_UART_Rx_Call_Back(void)
{
	static uint8_t u16_Rec_Size = ZERO;
	BCM_UART_CH1_RX_State = BCM_RECEIVING_BYTE;
	switch (gu8_UART_RX_CH1_State) 
	{
		case RECEIVING_BCM_ID:
		{
			//check if the received ID equal to the Stored ID			
			if (BCM_ID == USART_Receive_NO_POLLING())
			{
				gu8_UART_RX_CH1_State = RECEIVING_SIZE_PART1; //move to next state which is receiving the first part of the u16 size
			}
         else
			{
				Error_Push(BCM_MODULE, ERROR_INVALID_PARAMETER);
         }
			break;
		}
		case RECEIVING_SIZE_PART1:
		{
			u16_Rec_Size = USART_Receive_NO_POLLING();
			gu8_UART_RX_CH1_State = RECEIVING_SIZE_PART2 ;
			break;
		}
		case RECEIVING_SIZE_PART2:
		{
			u16_Rec_Size  = u16_Rec_Size <<8;
			u16_Rec_Size |= (USART_Receive_NO_POLLING());
			if (u16_Rec_Size <= gu16_BCM_UART_Rx_CH1_Size)
			{
				gu8_UART_RX_CH1_State = RECEIVING_DATA;
         }
			else
			{
				//error
				Error_Push(BCM_MODULE, ERROR_INVALID_PARAMETER);
			}
			break;
		}
		case RECEIVING_DATA:
		{
			//start receiving data
			if ( gu16_UART_Rx_CH1_Buffer_Index < u16_Rec_Size  )
			{
				(gptr_UART_Rx_CH1_Buffer[gu16_UART_Rx_CH1_Buffer_Index])= USART_Receive_NO_POLLING();
				//calculating Check sum 
				gu8_UART_Rx_CH1_Calculated_Check_Sum  += gptr_UART_Rx_CH1_Buffer[gu16_UART_Rx_CH1_Buffer_Index];
				gu16_UART_Rx_CH1_Buffer_Index++;
			}
			else
			{  //receiving cs
				gu8_UART_Rx_CH1_Check_Sum = USART_Receive_NO_POLLING();
				BCM_UART_CH1_RX_State = BCM_RECEIVING_BYTE_COMPLETE  ;
				gu8_UART_RX_CH1_State = RECEIVING_BCM_ID;
         }	
			break;
		}
		default:
		Error_Push(BCM_MODULE, ERROR_INVALID_PARAMETER);
		break;				
	}
}


/*
*** this function will be called when SPI TX interrupt occurs
*/
void BCM_SPI_Tx_Call_Back(void)
{
	if(BCM_SPI_CH1_TX_State == BCM_SENDING_BYTE)
	{
		BCM_SPI_CH1_TX_State = BCM_SENDING_BYTE_COMPLETE;
	}
	else
	{
		//do nothing
	}
}

/*
*** this function will be called when SPI Rx interrupt occurs
*/
void BCM_SPI_Rx_Call_Back(void)
{
	static uint8_t u16_Rec_Size = ZERO;
	char u8_Rx_Data =ZERO;
	
	//check SPI channel state 
	switch (gu8_SPI_RX_CH1_State)
	{
		case RECEIVING_BCM_ID:
		{
			SPI_Recive_Unblock(& u8_Rx_Data);
			
			//check BCM ID
			if (BCM_ID == u8_Rx_Data )
			{	
				gu8_SPI_RX_CH1_State = RECEIVING_SIZE_PART1;
			}
			else
			{
				Error_Push(BCM_MODULE,ERROR_INVALID_PARAMETER);
			}
			break;
		}
		case RECEIVING_SIZE_PART1:
		{		
			SPI_Recive_Unblock(& u8_Rx_Data);
			u16_Rec_Size = u8_Rx_Data;
			gu8_SPI_RX_CH1_State = RECEIVING_SIZE_PART2 ;
			break;
		}
		case RECEIVING_SIZE_PART2:
		{
			SPI_Recive_Unblock(& u8_Rx_Data);
			u16_Rec_Size  = u16_Rec_Size <<8;
			u16_Rec_Size |= (u8_Rx_Data);
			
			//check if the received size less than or equal to the Rx buffer size
			if (u16_Rec_Size <= gu16_BCM_SPI_Rx_CH1_Size)
			{
				gu8_SPI_RX_CH1_State = RECEIVING_DATA ;
			}
			else
			{	
				Error_Push(BCM_MODULE,ERROR_INVALID_PARAMETER);
			}
			break;
		}
		case RECEIVING_DATA:
		{
			if ( gu16_SPI_Rx_CH1_Buffer_Index < u16_Rec_Size  )
			{
				SPI_Recive_Unblock(& u8_Rx_Data);
				(gptr_SPI_Rx_CH1_Buffer[gu16_SPI_Rx_CH1_Buffer_Index])= u8_Rx_Data;
				gu8_SPI_Rx_CH1_Calculated_Check_Sum  +=gptr_SPI_Rx_CH1_Buffer[gu16_SPI_Rx_CH1_Buffer_Index];
				gu16_SPI_Rx_CH1_Buffer_Index++;
			}
			else
			{ 
				//receiving cs
				SPI_Recive_Unblock(& u8_Rx_Data);
				gu8_SPI_Rx_CH1_Check_Sum = u8_Rx_Data;
				BCM_SPI_CH1_RX_State = BCM_RECEIVING_BYTE_COMPLETE  ;
				gu8_SPI_RX_CH1_State = RECEIVING_BCM_ID;
			}
			break;
		}
		default:
		{
			Error_Push(BCM_MODULE,ERROR_INVALID_PARAMETER);
			break;
		}
	}
}

/*
*** this function will be called when UART TX interrupt occur
*/
void BCM_UART_Tx_Call_Back(void)
{
	if(BCM_UART_CH1_TX_State == BCM_SENDING_BYTE)
	{
		BCM_UART_CH1_TX_State = BCM_SENDING_BYTE_COMPLETE;
	}
	else
	{
		//do nothing
	} 
}
