 /*
 ============================================================================
 Name        : I2C.c
 Author      : Muhammed Gamal
 Description : Source file for the I2C(TWI) AVR driver
 ============================================================================
 */


/*********************************includes**********************************/
#include "i2c.h"
#include "I2C_Cfg.h"
#include "../MCAL/registers.h"
#include "../MCAL/interrupt.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define TWI_NO_PRESCALLER           0u
#define TWI_PRESCALLER_4            1u
#define TWI_PRESCALLER_16           2u
#define TWI_PRESCALLER_64           3u
#define DEVICE_ID                   0x10u
#define TWO                         2u
#define FOUR                        4u
#define SIXTEEN                     16u
#define CLEAR                       0u
#define FIRST_ENTRY                 0u
#define SECOND_ENTRY                1u
#define READ_MASK                   0x01u
#define WRITE_MASK                  0xFEu
#define CLEAR                       0u
#define END                         0u
#define NULL	                    ((void *)0)
#define FLAG_HIGH                   1u
#define FLAG_LOW                    0u
#define MEM_RANGE                   1024u
#define WRITE_OPERATION             0u
#define READ_OPERATION              1u
/***************************************************************************/


/******************************global variables*****************************/
<<<<<<< HEAD
void (*Consumer_Clb_Ptr)(void) = NULL;
static uint8_t I2C_FLAG;
static uint8_t *write_data_ptr = NULL;
static uint8_t write_data_length = CLEAR;
static uint8_t write_data_address = CLEAR;
static uint8_t I2C_Operation = WRITE_OPERATION;
static uint8_t *read_data_ptr = NULL;
static uint8_t read_data_length = CLEAR;
static uint8_t read_data_address = CLEAR;
=======
static void (*Consumer_Clb_Ptr)(void) = NULL;
static uint8_t I2C_FLAG;
static uint8_t *write_data_ptr = NULL;
static uint8_t write_data_length ;
static uint8_t write_data_address;
static uint8_t I2C_Operation;
static uint8_t *read_data_ptr = NULL;
static uint8_t read_data_length;
static uint8_t read_data_address;
>>>>>>> 015459ef6f7feb7579abc1afee66999c88aa7a13
/***************************************************************************/


/************************************************************************************
* Function Name: I2C_Init
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this function initializes the module
************************************************************************************/
void I2C_Init(void)
{
	uint8_t au8_TWBR_Value;

    /* select the prescaller */
	switch(I2C_ConfigParam.PreScaler)
	{
	case TWI_NO_PRESCALLER:
		au8_TWBR_Value = 0;
		break;
	case TWI_PRESCALLER_4:
		au8_TWBR_Value = 1;
		break;
	case TWI_PRESCALLER_16:
		au8_TWBR_Value = 2;
		break;
	case TWI_PRESCALLER_64:
		au8_TWBR_Value = 3;
		break;
	}

	/* set the bit rate */
	TWBR = ((I2C_ConfigParam.CPUFreq) / (I2C_ConfigParam.TargerRate * (FOUR^au8_TWBR_Value) * TWO))-(SIXTEEN/((FOUR^au8_TWBR_Value)*TWO));

	TWSR = CLEAR;    /* clear the status register */

    /* Two Wire Bus address my address if any master device want to call me: 0x10 (used in case this MC is a slave device)
       General Call Recognition: Off */
    TWAR = DEVICE_ID; /* set the device address */

    TWCR = (1<<TWEN) | (1<<TWIE); /* enable TWI and TWI interrupt*/

    Consumer_Clb_Ptr = I2C_ConfigParam.ActionDoneCbkPtr;  /* set the call back function */

    /* initialize all global variables */
    I2C_FLAG = FLAG_LOW;
    write_data_length = CLEAR;
    write_data_address = CLEAR;
    I2C_Operation = WRITE_OPERATION;
    read_data_length = CLEAR;
    read_data_address = CLEAR;
}


/************************************************************************************
* Function Name: I2C_start
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this local function sends the start bit
************************************************************************************/
static void I2C_start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN) | (1<<TWIE);
}


/************************************************************************************
* Function Name: I2C_Stop
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this function sends the stop bit
************************************************************************************/
void I2C_Stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN) | (1<<TWIE);
}


/************************************************************************************
* Function Name: I2C_ReqWrite
* Parameters (in): -SlaveAddress
*                  -*DataPtr
*                  -DataLen
* Parameters (inout): None
* Parameters (out): None
* Return value: I2C_CheckType
* Description: this function writes data on I2C bus
************************************************************************************/
I2C_CheckType I2C_ReqWrite(uint8_t SlaveAddress, const uint8_t * DataPtr, uint8_t DataLen)
{
	uint8_t au8_stats = I2C_OK;
	static uint8_t au8_entry_counter;

	I2C_Operation = WRITE_OPERATION;       /* set the I2C operation to be write */
	/* errors checking */
	if(SlaveAddress > MEM_RANGE || DataPtr == NULL || DataLen > MEM_RANGE)
	{
		au8_stats = I2C_NOK;
	}

	else
	{
		write_data_length = DataLen;
		if(I2C_FLAG == FLAG_LOW)
		{
			I2C_FLAG = FLAG_HIGH;       /*  raise the flag */
			if(write_data_length > END)
			{
				if(au8_entry_counter == FIRST_ENTRY)
				{
					write_data_ptr = DataPtr;             /* save the data pointer */
					write_data_address = SlaveAddress;   /* save the address */
					I2C_start();                        /* send the start bit */
				}

				else if(au8_entry_counter == SECOND_ENTRY)
				{
					TWDR = SlaveAddress & WRITE_MASK;   /* slave address and write operation */
				}

				else
				{
					/* Put data On TWI data Register */
					TWDR = *write_data_ptr;
					write_data_length--;    /* increment the length */
					write_data_ptr++;      /* increment the pointer */
				}

				/*
				 * Clear the TWINT flag before sending the data TWINT=1
				 * Enable TWI Module TWEN=1
				 */
				TWCR = (1 << TWINT) | (1 << TWEN) | (1<<TWIE);

				au8_entry_counter++;
			}
		}
	}

	if(DataLen == END)
	{
		au8_entry_counter = CLEAR;  /* reset the counter */
		I2C_FLAG = FLAG_LOW;  /* reset the flag */

		if(Consumer_Clb_Ptr != NULL)
		{
			Consumer_Clb_Ptr();    /* notify the consumer */
		}
	}

	return au8_stats;
}


/************************************************************************************
* Function Name: I2C_ReqRead
* Parameters (in): -SlaveAddress
*                  -DataLen
* Parameters (inout): None
* Parameters (out): - *DataPtr
* Return value: I2C_CheckType
* Description: this function writes data on I2C bus
************************************************************************************/
I2C_CheckType I2C_ReqRead(uint8_t SlaveAddress, uint8_t * DataPtr, uint8_t DataLen)
{
	uint8_t au8_stats = I2C_OK;
	static uint8_t au8_entry_counter = CLEAR;

	I2C_Operation = READ_OPERATION;          /* set the I2C operation to be write */
	/* errors checking */
	if(SlaveAddress > MEM_RANGE || DataPtr == NULL || DataLen > MEM_RANGE)
	{
		au8_stats = I2C_NOK;
	}

	else
	{
		read_data_length = DataLen;
		if(I2C_FLAG == FLAG_LOW)
		{
			I2C_FLAG = FLAG_HIGH;       /*  raise the flag */

			if(read_data_length > END)
			{
				if(au8_entry_counter == FIRST_ENTRY)
				{
					read_data_ptr = DataPtr;             /* save the data pointer */
					read_data_address = SlaveAddress;   /* save the address */
					I2C_start();                       /* send the start bit */
				}

				else if(au8_entry_counter == SECOND_ENTRY)
				{
					TWDR = SlaveAddress | READ_MASK;   /* slave address and read operation */

					/*
					 * Clear the TWINT flag before sending the data TWINT=1
					 * Enable TWI Module TWEN=1
					 */
					TWCR = (1 << TWINT) | (1 << TWEN) | (1<<TWIE);

				}

				else
				{
					/*
					 * Clear the TWINT flag before reading the data TWINT=1
					 * Enable sending ACK after reading or receiving data TWEA=1
					 * Enable TWI Module TWEN=1
					 */
					TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA) | (1<<TWIE);

					/* Read Data */
					*read_data_ptr = TWDR;
					read_data_length--;    /* increment the length */
					read_data_ptr++;      /* increment the pointer */
				}
				au8_entry_counter++;
			}
		}
	}

	if(DataLen == END)
	{
		au8_entry_counter = CLEAR;  /* reset the counter */
		I2C_FLAG = FLAG_LOW;  /* reset the flag */

		if(Consumer_Clb_Ptr != NULL)
		{
			Consumer_Clb_Ptr();    /* notify the consumer */
		}
	}

	return au8_stats;
}


/************************************************************************************
					     				ISR
************************************************************************************/
ISR(TWI_vect)
{
	I2C_FLAG = FLAG_LOW;
	if(I2C_Operation == WRITE_OPERATION)
	{
		I2C_ReqWrite(write_data_address,write_data_ptr,write_data_length);    /* call the function to complete the operation */
	}
	else if(I2C_Operation == READ_OPERATION)
	{
		I2C_ReqRead(read_data_address,read_data_ptr,read_data_length);    /* call the function to complete the operation */
	}
}
