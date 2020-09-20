/*
 * SPI.c
 *
 * Created: 3/1/2020 8:45:16 PM
 *  Author: ahmed
 */ 

#include "SPI.h"

	
void (*SPI_CBK)(void) = NULL;

static volatile uint8_t gu8_SPI_Flag = FALSE;

ERROR_STATUS SPI_Init(strSPI_Config_t* SPI_Config)
{
	ERROR_STATUS ERR = E_OK;
	
	if (SPI_Config==NULL)
	{
		/*error*/
	}
	else
	{
		
		switch(SPI_Config->u8_MasterSlaveSelect)
		{
			case SPI_MASTER_MODE:
				PORTB_DIR |= MASTER_PORT_MASK;
				SPCR |= MSTR;
				break;
			
			case SPI_SLAVE_MODE:
				PORTB_DIR |= SLAVE_PORT_MASK;
				SPCR &=~ MSTR;
				break;
			
			default:
				ERR = E_NOK;
			
		}
		
		switch(SPI_Config->u8_InterruptPollingMode)
		{
			case SPI_INTERRUPT:
				SPCR |= SPIE;
				break;
				
			case SPI_POLLING:
				SPCR &=~ SPIE;
				break;
				
			default:
				ERR = E_NOK;
		}
		
		switch(SPI_Config->u8_DataOrder)
		{
			case SPI_LSB_FIRST:
				SPCR |= DORD;
				break;
			case SPI_MSB_FIRST:
				SPCR &= ~DORD;
				break;
				
			default:
				ERR = E_NOK;
				break;
		}
		
		switch (SPI_Config->u8_Speed)
		{
			 case SPI_NORMAL_SPEED:
			 SPSR &= ~SPI2X;
			 break;
			 
			 case SPI_2X_SPEED:
			 SPSR |= SPI2X;
			 break;
			 
			 default:
			 ERR= E_NOK;
			 break;
		}
		
		if ((SPI_Config->u8_ModeNumber == MODE_NUMBER0			|| 
		SPI_Config->u8_ModeNumber == MODE_NUMBER1				|| 
		SPI_Config->u8_ModeNumber == MODE_NUMBER2				|| 
		SPI_Config->u8_ModeNumber == MODE_NUMBER3)				&&
		(SPI_Config->u8_ClockRate == SPI_FREQUENCY_DIVIDER_4	||
		SPI_Config->u8_ClockRate == SPI_FREQUENCY_DIVIDER_16	||
		SPI_Config->u8_ClockRate == SPI_FREQUENCY_DIVIDER_64	|| 
		SPI_Config->u8_ClockRate == SPI_FREQUENCY_DIVIDER_128))
		{
			SPCR |= SPI_Config->u8_ModeNumber | SPI_Config->u8_ClockRate ;
			
		}
		else
		{
			ERR = E_NOK;
		}
		
	}
	
	SPI_CBK = SPI_Config->SPI_CBK ;
	
	SPCR |= SPE;
	return ERR;
}

ERROR_STATUS SPI_SendChar(uint8_t u8_Data)
{
	ERROR_STATUS ERR = E_OK;
	static uint8_t u8_FirstTimeFlag = TRUE;
	
	static uint8_t x = 0;
	
	if (u8_FirstTimeFlag)
	{
		u8_FirstTimeFlag = FALSE;
		if (SPCR & SPIE)
		{
			x++;
			SPDR = u8_Data;
		}
		else
		{
			SPDR = u8_Data;
			while (TRANSMISSION_NOT_COMPLETE);
		}
	}
	else
	{
		if (SPCR & SPIE)
		{
			if (gu8_SPI_Flag)
			{
				gu8_SPI_Flag = FALSE;
				x++;
				SPDR = u8_Data;
				/*u8_SPI_Dummy = SPDR;
				TCNT2 = SPDR;*/
				/*while (SPSR & WCOL)
				{
					x++;
					SPDR = u8_Data;
				}*/
			}
			
		}
		else
		{
			SPDR = u8_Data;
			while (TRANSMISSION_NOT_COMPLETE);
		}
	}
	
	
	return ERR;
	
}

ERROR_STATUS SPI_ReceiveChar(uint8_t* pu8_Data)
{
	ERROR_STATUS ERR = E_OK;
	
	uint8_t u8_PollingInterrupt = (SPCR & SPIE);
	
	if (u8_PollingInterrupt)
	{
		*pu8_Data = SPDR ;
	}
	else
	{
		while (TRANSMISSION_NOT_COMPLETE);
		*pu8_Data = SPDR ;
	}
	return ERR;
	
}

InterruptServiceRoutine(SPI_STC_vect)
{
	gu8_SPI_Flag = TRUE;
	
	if (SPI_CBK != NULL)
		SPI_CBK();
}