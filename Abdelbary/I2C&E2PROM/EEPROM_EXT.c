/*
 * EEPROM_EXT.c
 *
 * Created: 28/04/2020 23:51:42
 *  Author: Eman
 */ 

#include "EEPROM_EXT.h"
#include "EEPROM_EXT_Cfg.h"
#include "I2C.h"
#include <avr/io.h>
#define		WRITE		1
#define		READ		2
#define		BUSY		3
#define		IDLE		0
#define		ERROR		4
#define		CALLBCK		5

typedef unsigned char uint8_t;

static uint16_t EEPROM_byte_address = 0;
static uint8_t*	data_ptr = 0;
static uint8_t	data_length = 0;

uint8_t EEEXT_state = IDLE;
uint8_t EEEXT_pre_state = IDLE;

void EEEXT_Init(void)
{
	/* initialize the I2C */
	I2C_Init();
}

EEEXT_CheckType EEEXT_ReqWrite(uint16_t StartAddress, const unsigned char* DataPtr, unsigned char Length)
{
	EEEXT_CheckType retVal = EEEXT_OK;
	
	if(EEEXT_state == IDLE)
	{
		EEPROM_byte_address = StartAddress;
		data_ptr = DataPtr;
		data_length = Length;
		
		if (Length<=8 && Length>0)
		{
			EEEXT_state = WRITE;
			EEEXT_pre_state = IDLE;
		}
		else
		{
			retVal = EEEXT_NOK;
			EEEXT_state = ERROR;
		}
	}
	else
	{
		retVal = EEEXT_BUSY;
	}
	
	return retVal;
}

EEEXT_CheckType EEEXT_ReqRead(uint16_t StartAddress,unsigned char* DataPtr,unsigned char Length)
{
	EEEXT_CheckType retVal = EEEXT_OK;
	
	if(EEEXT_state == IDLE)
	{
		EEPROM_byte_address = StartAddress;
		data_ptr = DataPtr;
		data_length = Length;
	
		if (Length<=8 && Length>0)
		{
			EEEXT_state = READ;
		}
		else
		{
			retVal = EEEXT_NOK;
			EEEXT_state = ERROR;
		}
	}
	else
	{
		retVal = EEEXT_BUSY;
	}
	
	return retVal;
}

void EEEXT_Main(void)
{
	uint8_t status = 0;
	
	switch(EEEXT_state)
	{
		case IDLE:
		break;
		case READ:
		{
			if (EEEXT_pre_state == IDLE)
			{
				EEEXT_pre_state = WRITE;
				/* Send Start bit */
				I2C_Start();
				
				status = TWSR & 0xF8;
				if (status != TW_START)
				{
					EEEXT_state = ERROR;
					break;
				}
			}
			
			/* Send the device address, we need to get A8 A9 A10 address bits from the
			 * memory location address and R/W=0 (write) */
			TWI_data_type = ADDRESS;
			I2C_ReqWrite((uint8_t)(0xA0 | ((EEPROM_byte_address & 0x0700)>>7)),data_ptr,data_length);
			
			status = TWSR & 0xF8;
			if (status != TW_MT_SLA_W_ACK)
			{
				EEEXT_state = ERROR;
				break;
			}
			
			/* Send the required memory location address */
			I2C_ReqWrite((uint8_t)(EEPROM_byte_address),data_ptr,data_length);
			
			status = TWSR & 0xF8;
			if (status != TW_MT_DATA_ACK)
			{
				EEEXT_state = ERROR;
				break;
			}
				
			/* Send the Repeated Start Bit */
			I2C_Start();
					
			status = TWSR & 0xF8;
			if (status != TW_START)
			{
				EEEXT_state = ERROR;
				break;
			}

			/* Read Byte from Memory */
			I2C_ReqRead((uint8_t)(EEPROM_byte_address),data_ptr,data_length);
						
			status = TWSR & 0xF8;
			if (status != TW_MT_DATA_ACK)
			{
				EEEXT_state = ERROR;
				break;
			}
			data_length--;
							
			if (data_length == 0)
			{
			/* Send the Stop Bit */
			I2C_Stop();
			/* Return to IDLE state*/
			EEEXT_state = IDLE;
			}
		}
		break;
		case WRITE:
		{
			if (EEEXT_pre_state == IDLE)
			{
				EEEXT_pre_state = WRITE;
				/* Send Start bit */
				I2C_Start();	
				
				status = TWSR & 0xF8;
				if (status != TW_START)
				{
					EEEXT_state = ERROR;
					break;
				}
			} 
			
			/* Send the device address, we need to get A8 A9 A10 address bits from the
			 * memory location address and R/W=0 (write) */
			TWI_data_type = ADDRESS;
			I2C_ReqWrite((uint8_t)(0xA0 | ((EEPROM_byte_address & 0x0700)>>7)),data_ptr,data_length);
			status = TWSR & 0xF8;
			if (status != TW_MT_SLA_W_ACK)
			{
				EEEXT_state = ERROR;
			}
			
			/* Send the required memory location address */
			I2C_ReqWrite((uint8_t)(EEPROM_byte_address),data_ptr,data_length);
				
			status = TWSR & 0xF8;
			if (status != TW_MT_DATA_ACK)
			{
				EEEXT_state = ERROR;
				break;
			}
				
			/* write byte to EEPROM */
			TWI_data_type = DATA;
			I2C_ReqWrite((uint8_t)(EEPROM_byte_address),data_ptr,data_length);
					
			status = TWSR & 0xF8;
			if (status != TW_MT_DATA_ACK)
			{
				EEEXT_state = ERROR;
				break;
			}

			data_length--;
			
			if (data_length == 0)
			{
				/* Send the Stop Bit */
				I2C_Stop();
				/* Return to IDLE state*/
				EEEXT_state = IDLE;
			} 		
		}
		break;
		case ERROR:
		break;
		case CALLBCK:
		default:
		{
			EEEXT_state = ERROR;
		}
		break;
	}
	
}

void EEXT_ACtionDoneCallback(void)
{
	EEEXT_state= CALLBCK;
}