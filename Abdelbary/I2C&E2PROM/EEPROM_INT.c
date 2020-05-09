/*
 * EEPROM_INT.c
 *
 * Created: 28/04/2020 23:37:28
 *  Author: sony
 */ 
#include "EEPROM_INT.h"
#include <avr/interrupt.h>
#include "macros.h"
#include "EEPROM_INT_CFG.h"
#define EEPROM_READY		0
#define EEROM_NOT_READY	1

/*STATES OF THE EEROM MODULE*/
#define EEPROM_IDLE				0
#define EEPROM_NOT_INIT			1
#define EEPROM_WRITE_REQ		2
#define EEPROM_READ_REQ			3
#define EEPROM_READ_COMP		4
#define EEPROM_WRITE_COMP		5


uint8_t  gu8_startAddress;
uint8_t* gu8_DataPtr;
uint8_t  gu8_dataLength;
uint8_t  gu8_EEROM_readyFlag;
uint8_t	 gu8_EEPROM_state = EEPROM_NOT_INIT;

void EEINT_Init(void)
{
	gu8_startAddress		= ZERO;
	gu8_DataPtr				= NULL;
	gu8_dataLength			= ZERO;
	gu8_EEROM_readyFlag		= EEROM_NOT_READY;
	gu8_EEPROM_state		= EEPROM_IDLE;
	sei();
}


EEINT_CheckType EEINT_ReqWrite(unsigned char StartAddress, const unsigned char* DataPtr, unsigned char Length)
{
	/************************************************************************
	    check if the module init
		check if the module is not busy
		load data to global variable and request a write
	************************************************************************/
	EEINT_CheckType retVal = EEINT_OK;
	if(gu8_EEPROM_state == EEPROM_NOT_INIT)
	{
		retVal = EEINT_NOK;
	}
	else if(gu8_EEPROM_state != EEPROM_IDLE)
	{
		retVal = EEINT_BUSY;
	}
	else
	{
		/*
		* save function paramter in global variable for the dispatcher
		* change state to req write and enbale interrupte
		*/
		gu8_startAddress = StartAddress;
		gu8_dataLength		 = Length;
		gu8_DataPtr		     = DataPtr;
		gu8_EEPROM_state = EEPROM_WRITE_REQ;
	}
	return retVal;
}


EEINT_CheckType EEINT_ReqRead(unsigned char StartAddress,unsigned char* DataPtr,unsigned char Length)
{
	/************************************************************************
	    check if the module init
		check if the module is not busy
		load data to global variable and request a read
	************************************************************************/
	EEINT_CheckType retVal = EEINT_OK;
	if(gu8_EEPROM_state == EEPROM_NOT_INIT)
	{
		retVal = EEINT_NOK;
	}
	else if(gu8_EEPROM_state != EEPROM_IDLE)
	{
		retVal = EEINT_BUSY;
	}
	else
	{
		/*
		* save function paramter in global variable for the dispatcher
		* change state to req write and enbale interrupte
		*/
		gu8_startAddress = StartAddress;
		gu8_dataLength		 = Length;
		gu8_DataPtr		 = DataPtr;
		gu8_EEPROM_state = EEPROM_READ_REQ;
	}
	return retVal;
}

void EEINT_Main(void)
{
	switch(gu8_EEPROM_state)
	{
		case EEPROM_IDLE:
		case EEPROM_NOT_INIT: /*if module is not init or no write or read req--> do nothing*/
		/*do nothing*/
		break;
		case EEPROM_READ_REQ:
			if (gu8_EEROM_readyFlag == EEPROM_READY)
			{
				static uint8_t u8_counter = ZERO;
				
				EEAR=(gu8_startAddress+u8_counter);
				
				EECR |= (1<<EERE);
				//loads current byte and increments index for next load
				*(gu8_DataPtr+u8_counter) = EEDR;
				
				gu8_EEROM_readyFlag = EEROM_NOT_READY;

				/*enable eeprom interrupt*/
				 EECR |= (1<<EERIE); 
				 
				 u8_counter++;
				
				if(u8_counter == gu8_dataLength)
				{
					u8_counter = ZERO;
					gu8_EEPROM_state = EEPROM_READ_COMP;
				}
			}
		break;
		case EEPROM_WRITE_REQ:
			if (gu8_EEROM_readyFlag == EEPROM_READY)
			{
				static uint8_t u8_counter = ZERO;
				
				EEAR=(gu8_startAddress+u8_counter);
				//loads current byte and increments index for next load
				EEDR=*(gu8_DataPtr+u8_counter);
				cli();
				//master write enable
				EECR|=(1<<EEMWE);
				//strobe eeprom write
				EECR|=(1<<EEWE);
				sei();
				
				gu8_EEROM_readyFlag = EEROM_NOT_READY;
				
				/*enable eeprom interrupt*/
				EECR |= (1<<EERIE);
				u8_counter++;
				
				if(u8_counter == gu8_dataLength)
				{
					u8_counter = ZERO;
					gu8_EEPROM_state = EEPROM_WRITE_COMP;
				}
			}
		break;
		case EEPROM_WRITE_COMP:
			/*
			*	change module state to idle
			*	calll app call back function
			*/
			gu8_EEPROM_state = EEPROM_IDLE;
			EEINT_ConfigParam.WriteDoneCbkPtr();
		break;
		case EEPROM_READ_COMP:
			/*
			*	change module state to idle
			*	calll app call back function
			*/
			gu8_EEPROM_state = EEPROM_IDLE;
			EEINT_ConfigParam.ReadDoneCbkPtr();
		break;
	}
}

ISR(EE_RDY_vect)
{
	gu8_EEROM_readyFlag = EEPROM_READY;
	CLEAR_BIT(EECR,EERIE);
	CLEAR_BIT(EECR,EEWE);
}
