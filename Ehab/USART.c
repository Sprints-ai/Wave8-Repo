/*
 * USART.c
 *
 * Created: 2/12/2020 4:09:47 PM
 *  Author: ahmed
 */ 

#include "USART.h"



void (*USART_CBK[3])(void) = {NULL,NULL,NULL};

static volatile uint8_t gu8_UDRE_flag = FALSE; 
static volatile uint8_t gu8_TXC_flag = FALSE;
static volatile uint8_t gu8_RXC_flag = FALSE;

uint8_t USART_Init(strUSART_Config_t* Config)
{
	uint8_t ERR = E_OK;
	
	
	
	if (Config ==NULL)
	{
		ERR = E_NOK;
	}
	
	UCSRA |= Config->USART_SPEED;
	
	UCSRB = Config->USART_RX_Interrupt | Config->USART_TX_Interrupt | Config->USART_UDR_EmptyInterrupt |
	Config->USART_RX_EnableDisable | Config->USART_TX_EnableDisable;
	
	
	UCSRC |= URSEL | Config->USART_OperationMode | Config->USART_Parity | Config->USART_CharSize | Config->USART_CharSize;
	
	USART_CBK[USART_UDRE_CBK_INDEX] = Config->USART_UDRE_CBK;
	USART_CBK[USART_TXC_CBK_INDEX] = Config->USART_TXC_CBK;
	USART_CBK[USART_RXC_CBK_INDEX] = Config->USART_RXC_CBK;
	ASSIGN_BAUDRATE;
		
	return ERR;
}

uint8_t USART_SendChar(uint8_t u8_Char)
{
	uint8_t ERR = E_OK;
	static uint8_t u8_1stTimeFlag = TRUE;
	
	
	if (u8_1stTimeFlag)
	{
		u8_1stTimeFlag = FALSE;

		if ((UCSRB & TXCIE))
		{ 
			
			
			gu8_UDRE_flag = FALSE;
			UDR = u8_Char;
			
			
		}
		else
		{
			while (USART_DATA_REGISTER_NOT_EMPTY);
			
			UDR = u8_Char;
		}
	}
	else
	{	

		if ((UCSRB & TXCIE))
		{	
			
			if(gu8_TXC_flag)
			{	
				UDR = u8_Char;
				gu8_TXC_flag = FALSE;
			}
		}
		else
		{
			while (USART_DATA_REGISTER_NOT_EMPTY);
			
			UDR = u8_Char;
		}
	}
		
		return ERR;
}

uint8_t USART_ReceiveChar(uint8_t* pu8_Char)
{
	uint8_t ERR = E_OK;
	
	
	
	if (pu8_Char != NULL)
	{
		if (UCSRB & RXCIE)
		{
			*pu8_Char = UDR;
		}
		else
		{
			while (USART_RECEIVE_INCOMPLETE);
			*pu8_Char = UDR;
		}
	}
	
	else 
	{
		ERR = E_NOK;
	}
	
	return ERR;
}

uint8_t USART_SendString(uint8_t au8_Str[])
{
	uint8_t u8_FunctionStatus = E_OK;
	
	uint8_t u8_LocalIterator = ITERATION_START ;
	for (u8_LocalIterator = ITERATION_START ; au8_Str[u8_LocalIterator] != NULL_CHAR ; u8_LocalIterator++)
	{
		USART_SendChar (au8_Str[u8_LocalIterator]);
	}
	
	if (u8_LocalIterator == ITERATION_START)
		u8_FunctionStatus = E_NOK;
		
	return u8_FunctionStatus;
}

uint8_t USART_ReceiveString(uint8_t* pu8_Str , uint16_t u16_StringSize)
{
	uint8_t u8_FunctionStatus = E_OK;
	
	uint8_t u8_LocalIterator = ITERATION_START ;
	for (u8_LocalIterator = ITERATION_START ; pu8_Str[u8_LocalIterator] != NULL_CHAR ; u8_LocalIterator++)
	{
		USART_SendChar (pu8_Str[u8_LocalIterator]);
	}
	
	if (pu8_Str == NULL_CHAR)
		u8_FunctionStatus = E_NOK;
		
	return u8_FunctionStatus;
}

InterruptServiceRoutine(USART_RXC_vect)
{
	gu8_RXC_flag = TRUE;
	
	if (USART_CBK[USART_RXC_CBK_INDEX]!=NULL)
	{
		USART_CBK[USART_RXC_CBK_INDEX]();
	}
	
}
InterruptServiceRoutine(USART_UDRE_vect)
{
	gu8_UDRE_flag = TRUE;
	
	/*PORTA_DIR = 0xff;
	PORTA_DATA = 0xff;*/
	
	if(USART_CBK[USART_UDRE_CBK_INDEX]!=NULL)
	{
		USART_CBK[USART_UDRE_CBK_INDEX]();
	}
}
InterruptServiceRoutine(USART_TXC_vect)
{	gu8_TXC_flag = TRUE;
	
	PORTA_DIR = 0xff;
	PORTA_DATA = 0xff;
	if(USART_CBK[USART_TXC_CBK_INDEX]!=NULL)
	{
		USART_CBK[USART_TXC_CBK_INDEX]();
	}
}