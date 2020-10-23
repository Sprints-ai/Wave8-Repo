/*
 * I2C.c
 *
 * Created: 28/04/2020 23:20:59
 *  Author: sony
 */ 

/************************************************************************/
/*								INCLUDES                                */
/************************************************************************/
#include "std_types.h"
#include "registers.h"
#include "interrupts.h"
#include "I2C_Cfg.h"

/************************************************************************/
/*								Defines                                 */
/************************************************************************/
#define FREQ_1ST_CONST   (16u)
#define FREQ_2ND_CONST   (8u)

#define CTRL_REG_WITH_START (229u)
#define CTRL_REG_VAL (197u)
#define CTRL_IRQ_MASK (0x80u)
#define CTRL_NO_IRQ (0u)
#define CTRL_REG_WITH_STOP (0x94u)
#define CTRL_INTERRUPT_ENABLE (0x01)

#define STATUS_START_MASK (0x08u)
#define STATUS_R_START_MASK (0x10u)
#define STATUS_SHIFT (3u)
#define STATUS_TX_ACK_MASK (0x18u)
#define STATUS_TX_BYTE_MASK (0x28u)

#define STATUS_RX_ACK_MASK (0x40u)
#define STATUS_RX_BYTE_MASK (0x50u)

#define READ_BIT_VAL (1u)
#define WRITE_BIT_VAL (0u)
#define RW_BIT_SHIFT (1u)

#define LOOP_INIT_VALUE (0u)

#define TRANSACTION_ON_GOING (1)
#define TRANSACTION_FREE (0)

#define READ_STATE (1)
#define WRITE_STATE (0)
/************************************************************************/
/*								GLOBALS                                 */
/************************************************************************/
static I2C_CbkPftype User_CallBack;

static uint8_t gu8_SlaveAddr = 0;
static volatile uint8_t gu8_IRQ_loop = LOOP_INIT_VALUE;
static uint8_t * gptr_I2C_Data = 0;
static volatile uint8_t gu8_Data_Length = 0;
static volatile uint8_t gu8_Transaction_Status = TRANSACTION_FREE;
static uint8_t gu8_ProcessState = READ_STATE;

/************************************************************************/
/*								APIS                                    */
/************************************************************************/

/*
*Description: Function to init I2c From an init struct defined at
.I2c_Cfg.c file
*Input : Void , Output:Void
*/
void I2C_Init(void)
{
    
	/*Bit Rate Var*/
	uint8_t u8_BitRate = 0u;
	
	/*Calculate BitRate Value*/
	u8_BitRate = (((uint8_t)(I2C_ConfigParam.CPUFreq/I2C_ConfigParam.TargerRate))
	              - (uint8_t)FREQ_1ST_CONST)/FREQ_2ND_CONST;
	
	/*Write BitRate Var into Reg*/
	TWBR = u8_BitRate;
	
	/*Enable IRQ*/
	TWCR = CTRL_INTERRUPT_ENABLE;
	
	/*Create Callback*/
	User_CallBack = I2C_ConfigParam.ActionDoneCbkPtr;
	
	SET_BIT(SREG,7);
}

/*
*Description: Function to send a value to a slave
@Parm : Slave address , inter to data array , Number of byte to be sent
@Output : Error if found
*/
I2C_CheckType I2C_ReqWrite(unsigned char SlaveAddress, const unsigned char* DataPtr, unsigned char DataLen)
{
	/*Create Error Var*/
	I2C_CheckType ERR_STATE = I2C_OK;
	
	/*Check if there's Transaction going on or not*/
	if(gu8_Transaction_Status ==TRANSACTION_FREE)
	{
		/*Create loop*/
		gu8_Data_Length = DataLen;
		gu8_SlaveAddr = SlaveAddress;
		gptr_I2C_Data = DataPtr;
		gu8_ProcessState = WRITE_STATE;

		TWCR = CTRL_REG_WITH_START;
	}
	else
	{
		ERR_STATE = I2C_NOK;
	}

	return ERR_STATE;
}

/*I2c_Read
*Description : To read a value written by slave to master
*Input : Slave address , pointer to buffer , Buffer length
*Output : Error state
*/
I2C_CheckType I2C_ReqRead(unsigned char SlaveAddress, unsigned char* DataPtr, unsigned char DataLen)
{
	/*Create Error State Var*/
	I2C_CheckType ERR_STATE = I2C_OK;
	
	/*Check if there's Transaction going on or not*/
	if(gu8_Transaction_Status ==TRANSACTION_FREE)
	{
		/*Save Values in global Vars*/
		gu8_SlaveAddr = SlaveAddress;
		gu8_Data_Length = DataLen;
		gptr_I2C_Data = DataPtr;
		gu8_ProcessState = READ_STATE;
		
		TWCR = CTRL_REG_WITH_START;	
	}
	else
	{
		ERR_STATE = I2C_NOK;
	}
	return ERR_STATE;
}

/*STOP_I2C
*Description : Function To Stop data transaction in I2C
*Input , Output : None
*/
void I2C_Stop(void)
{
	 /*Write Stop in TWCR*/
	 TWCR = 0x94;
}

/*I2C Interrupt*/
ISR(TWI_vect)
{
	switch(TWSR)
	{
		case STATUS_R_START_MASK:
		case STATUS_START_MASK:
			
			/*Write Slave address with write bit on*/
			TWDR = (uint8_t)(gu8_SlaveAddr  + gu8_ProcessState);
			
			/*Save Transaction state*/
			gu8_Transaction_Status = TRANSACTION_ON_GOING;
		
			/*Write Address in data Reg*/
			TWCR = CTRL_REG_VAL;
		break;
		
		case STATUS_TX_ACK_MASK:
			
			/*Write Data*/
			TWDR = gptr_I2C_Data[gu8_IRQ_loop];
			
			/*Write CTRL Value*/
			TWCR = CTRL_REG_VAL;
			
			/*Increment loop by one */
			gu8_IRQ_loop++;
			
		break;
		
		case STATUS_TX_BYTE_MASK:
		
			/*Check for data length*/
			if(gu8_IRQ_loop < gu8_Data_Length){
				
				/*Write Data*/
				TWDR = gptr_I2C_Data[gu8_IRQ_loop];
				
				/*Write CTRL Value*/
				TWCR = CTRL_REG_VAL;
				
				/*Increment loop by one */
				gu8_IRQ_loop++;	
			}
			else
			{
				TWCR = 0;
			
				/*Reinit Loop and Free Transaction*/
				gu8_IRQ_loop = LOOP_INIT_VALUE;
				gu8_Transaction_Status = TRANSACTION_FREE;
				
				if(User_CallBack != NULL)
				{
					User_CallBack();
				}
			}
			
		break;
		
		case STATUS_RX_ACK_MASK:
			
			/*Save Received Data*/
			gptr_I2C_Data[gu8_IRQ_loop] = TWDR;
			
			TWCR = CTRL_REG_VAL;
			
			/*Save Received Data*/
			gu8_IRQ_loop++;

		break;
		
		case STATUS_RX_BYTE_MASK:
			
			if(gu8_IRQ_loop < gu8_Data_Length)
			{
				/*Save Received Data*/
				gptr_I2C_Data[gu8_IRQ_loop] = TWDR;
				
				/*Write CTRL Value*/
				TWCR = CTRL_REG_VAL;
				
				/*Increment loop by one */
				gu8_IRQ_loop++;
			}
			else
			{
				TWCR = 0;
				
				/*Reinit loop and Free Transaction*/
				gu8_IRQ_loop = LOOP_INIT_VALUE;
				
				gu8_Transaction_Status = TRANSACTION_FREE;
				
				if(User_CallBack != NULL)
				{
					User_CallBack();
				}
			}
			break;
			
		default:
			/*Reinit CTRL Reg*/
			TWCR = 0;

			gu8_Transaction_Status = TRANSACTION_FREE;
		break;
	}	
}