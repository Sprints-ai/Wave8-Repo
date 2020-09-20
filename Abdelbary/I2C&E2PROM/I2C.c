/*
 * I2C.c
 *
 * Created: 28/04/2020 23:20:59
 *  Author: Eman
 */ 

#include "I2C.h"
#include "I2C_Cfg.h"
#include "macros.h"
#include "avr/interrupt.h"


#define TWI_START			1
#define TWI_REPEATED_START	2
#define TWI_NOSTART			0
#define TWI_OPERATION_DONE	3
#define TWI_OPERATION_HOLD	4




uint8_t TWI_status = TWI_NOSTART;
uint8_t TWI_operation_status = TWI_OPERATION_HOLD;
uint8_t  TWI_data_type = ADDRESS;
const uint8_t* dataPointer = NULL;


ISR(TWI_vect)
{
	TWI_operation_status = TWI_OPERATION_DONE; 
}


void I2C_Init(void)
{
		/* Value of the TWI Bit Rate Register */
		TWBR = 0x02;
		/* Value of the pre-scaler bits in the TWI Status Register */
		TWSR = 0x00;
		/* address if it's a slave, don't choose 0 */
		TWAR = 0b00000110;
		/* Enable TWI in interrupt mode */
		TWCR = (1<<TWEN | 1<<TWIE);
}

I2C_CheckType I2C_ReqWrite(unsigned char SlaveAddress, const unsigned char* DataPtr, unsigned char DataLen)
{
	I2C_CheckType retVal = I2C_OK;
	
	uint8_t slave_address = 0;
	uint8_t data_length_write = DataLen;
	
	dataPointer = DataPtr;
	
	if (data_length_write>0)
	{
		if (TWI_status == TWI_START && TWI_operation_status == TWI_OPERATION_DONE)
		{
			if(TWI_data_type == ADDRESS)
			{
				slave_address = SlaveAddress;
				/* Put address On TWI data Register */
				TWDR = slave_address;
				TWCR = (1 << TWINT) | (1 << TWEN);
				/* allow ISR to change the flag to DONE for the new operation */
				TWI_operation_status = TWI_OPERATION_HOLD;
			}
			else
			{
				/* Put data On TWI data Register */
				TWDR = *dataPointer;
				TWCR = (1 << TWINT) | (1 << TWEN);
				/* allow ISR to change the flag to DONE for the new operation */
				TWI_operation_status = TWI_OPERATION_HOLD;
				
				data_length_write--;
			}
		}
		else
		{
			retVal = I2C_NOK;
		}
	}
	else
	{
		retVal = I2C_NOK;
	}
	
	I2C_ConfigParam.ActionDoneCbkPtr();
	
	return retVal;
}

I2C_CheckType I2C_ReqRead(unsigned char SlaveAddress, unsigned char* DataPtr, unsigned char DataLen)
{
	I2C_CheckType retVal = I2C_OK;
	
	uint8_t data_length_read = DataLen;
	
	dataPointer = DataPtr;
	
	if (data_length_read>0 && data_length_read!=1)
	{
		/* Read with ACK */
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		/* allow ISR to change the flag to DONE for the new operation */
		TWI_operation_status = TWI_OPERATION_HOLD;
		/* Read Data */
		*DataPtr = TWDR;
		
		data_length_read--;
	}
	else
	{
		/* READ with NACK for last data element */
		TWCR = (1 << TWINT) | (1 << TWEN);
		/* allow ISR to change the flag to DONE for the new operation */
		TWI_operation_status = TWI_OPERATION_HOLD;
		/* Read Data */
		*DataPtr = TWDR;
			
		data_length_read--;
	}
	
	I2C_ConfigParam.ActionDoneCbkPtr();
	
	return retVal;
}

void I2C_Stop(void)
{
	/* 	
	 * Clear the TWINT flag before sending the stop bit TWINT=1	
	 * send the stop bit by TWSTO=1	
	 * Enable TWI Module TWEN=1 	
	 */	
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    
}

void I2C_Start(void)
{
	
	
	uint8_t status = 0;	
	/* 	
	 * Clear the TWINT flag before sending the start bit TWINT=1	
	 * send the start bit by TWSTA=1	
	 * Enable TWI Module TWEN=1 	
	 */	
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);	
	/* allow ISR to change the flag to DONE for the new operation */	
	//TWI_operation_status == TWI_OPERATION_HOLD;	
	TWI_operation_status = TWI_OPERATION_HOLD;	
    	
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */	
	status = TWSR & 0xF8;	
    /* check start bit is send successfully */	
    if (status != TW_START)	
	{	
		TWI_status = TWI_NOSTART;	
	}	
	else	
	{	
		TWI_status = TWI_START;	
	}
}
