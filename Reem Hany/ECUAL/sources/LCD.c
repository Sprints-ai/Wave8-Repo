/*
 * LCD.c
 *
 * Created: 3/13/2020 5:49:37 PM
 *  Author: Reem
 */ 

#include "../includes/LCD_preCfg.h"
#include "../includes/LCD.h"
#include "../../Services/includes/softwareDelay.h"

/*************************************************************************/
/*                            DEFINES                                    */
/*************************************************************************/

#define LCD_BUFFER_SIZE     500
#define _LCD_WRITING_DELAY  5

/*************************************************************************/
/*                            Globals                                    */
/*************************************************************************/
static uint8_t gau8LCDBuffer[LCD_BUFFER_SIZE]={0};
static uint8_t gu8LCD_BufferSize;
static uint8_t gu8LCD_BufferLockState;
// These variables should be initialized here because it will be checked in the beginning of the init function
static uint8_t gu8LCD_InitSTATE = _LCD_INIT_DIO_INIT_STATE;
static uint8_t gu8_WriteState;
static uint8_t gu8LCDInitFlag = FALSE;
static uint8_t gu8LCDState = _LCD_IDLE;

/*****************************************************************/
/*                    Static prototype functions                 */
/*****************************************************************/

/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Enables the LCD
 * 							
 */
static ERROR_STATUS LCD_Enable(void);

/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Sending (CMD/DATA) Nibble (HIGH / LOW)
 * 							
 */
static ERROR_STATUS LCD_SendingNibble(uint8_t InfoNibble);

/**
 * Input: Pointer to Data string
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Send LCD Write string internally synchronizing with the whole lcd functions
 * 							
 */
static ERROR_STATUS LCD_WriteStr(uint8_t * DataStr);

/*****************************************************************/
/*                    Function implementation                    */
/*****************************************************************/

/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Sending (CMD/DATA) Nibble (HIGH / LOW)
 * 							
 */
static ERROR_STATUS LCD_SendingNibble(uint8_t InfoNibble)
{
	ERROR_STATUS ERR;
	/*Sending the Nibble bit by bit to the LCD 4-bit Data bits*/
	
	//Check on the LSB High or Low
	if(InfoNibble % TWO)
		ERR = DIO_Write(LCD_PORT,LCD_DATA_4,HIGH);
	else
		ERR = DIO_Write(LCD_PORT,LCD_DATA_4,LOW);
	
	//Shift right to change the LSB of the Nibble
	InfoNibble >>= ONE;
	
	//Check on the LSB High or Low
	if(InfoNibble % TWO)
		ERR = DIO_Write(LCD_PORT,LCD_DATA_5,HIGH);
	else
		ERR = DIO_Write(LCD_PORT,LCD_DATA_5,LOW);
	
	//Shift right to change the LSB of the Nibble
	InfoNibble >>= ONE;
	
	//Check on the LSB High or Low
	if(InfoNibble % TWO)
		ERR = DIO_Write(LCD_PORT,LCD_DATA_6,HIGH);
	else
		ERR = DIO_Write(LCD_PORT,LCD_DATA_6,LOW);
	
	//Shift right to change the LSB of the Nibble
	InfoNibble >>= ONE;
	
	//Check on the LSB High or Low
	if(InfoNibble % TWO)
		ERR = DIO_Write(LCD_PORT,LCD_DATA_7,HIGH);
	else
		ERR = DIO_Write(LCD_PORT,LCD_DATA_7,LOW);
	
	
	return ERR;
	
}

/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Enables the LCD
 * 							
 */
static ERROR_STATUS LCD_Enable(void)
{
	ERROR_STATUS ERR = LCD_ERROR + E_INVALID_PARAMETER;;
	
	ERR = DIO_Write(LCD_PORT,LCD_EN,HIGH);
	ERR = DIO_Write(LCD_PORT,LCD_EN,LOW);
	return ERR;
}
/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the LCD
 * 							
 */
ERROR_STATUS LCD_Init(void)
{
	
	ERROR_STATUS ERR = LCD_ERROR + E_INVALID_PARAMETER;
	
	/*Check whether the module is Initialized or not*/
	if (gu8LCDInitFlag)
	{
		ERR = LCD_ERROR + E_MULTIPLE_INITIALIZION;
	}
	else
	{
		/*In case 4-Bit mode*/
		#if _4_BIT_MODE == ENABLE
		
		DIO_Cfg_s astr_DIOcfg={ LCD_PORT,
			(LCD_RS|LCD_RW|LCD_EN|LCD_DATA_4|LCD_DATA_5|LCD_DATA_6|LCD_DATA_7),
		OUTPUT};
		
		switch(gu8LCD_InitSTATE)
		{
			//DIO_Init
			case _LCD_INIT_DIO_INIT_STATE:
		
			ERR = DIO_init(&astr_DIOcfg);
			gu8LCD_InitSTATE = _LCD_INIT_EXE_CMD_STATE;
			break;
			
			//Execute the commands
			case _LCD_INIT_EXE_CMD_STATE:
			
			ERR = LCD_ExecuteCommand(_LCD_4BIT_INIT_CMD);
			ERR = LCD_ExecuteCommand(_LCD_2_LINE_CMD);
			ERR = LCD_ExecuteCommand(_LCD_CURSOR_OFF_CMD);
			ERR = LCD_ExecuteCommand(_LCD_CURSOR_SHIFT_TO_RIGHT_CMD);
			ERR = LCD_Clear();
			
			gu8LCD_InitSTATE = _LCD_INIT_GLOBALS_INIT__STATE3;
			
			break;
			
			//Initialize Globals
			case _LCD_INIT_GLOBALS_INIT__STATE3:
			
			gu8LCD_BufferSize =ZERO;
			gu8LCD_BufferLockState = _LCD_BUFFER_UNLOCKED;
			gu8LCDInitFlag = TRUE;
			ERR =E_TASK_DONE;
			break;
		}	
		#else
		ERR = LCD_ERROR + E_INVALID_PARAMETER;
		#endif
	}
	
	return ERR;
}

/**
 * Input: Command
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Send LCD Commands
 * 							
 */
ERROR_STATUS LCD_ExecuteCommand(uint8_t Command)
{
	ERROR_STATUS ERR;
	
	
	#if _4_BIT_MODE == ENABLE
	
	//Get High Nibble
	uint8_t commandHigherNibble = GET_NIBBLE_HIGH(Command);
	//Get Low Nibble
	uint8_t commandLowerNibble  = GET_NIBBLE_LOW(Command);

		
	//Command Register selection
	DIO_Write(LCD_PORT,LCD_RS, LOW);
	//Write option selection
	DIO_Write(LCD_PORT,LCD_RW, LOW);
		
	//Sending the higher nibble first
		
	//Load Higher command nibble on the 4 bit data pins
		
		
	ERR = LCD_SendingNibble(commandHigherNibble);
	
	//Enable
	ERR =LCD_Enable();
		
	//Sending the lower nibble
		
	//Load Lower command nibble on the 4 bit data pins

	ERR = LCD_SendingNibble(commandLowerNibble);
	ERR = LCD_Enable();
	#endif
	return ERR;
	
}

/**
 * Input: Data byte
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Send LCD data
 * 							
 */
ERROR_STATUS LCD_WriteData(uint8_t DataByte)
{
	ERROR_STATUS ERR =E_NOK;
	
	//Check whether the module is initialized
	if (gu8LCDInitFlag)
	{
		static uint8_t au8_counter;
		#if _4_BIT_MODE == ENABLE
		
		//Get the High nibble
		uint8_t dataHigherNibble = GET_NIBBLE_HIGH(DataByte);
		
		//Get the Low nibble
		uint8_t dataLowerNibble  = GET_NIBBLE_LOW(DataByte);
		
		//Check on the Write states
		switch(gu8_WriteState)
		{
			case _LCD_WRITE_STATE1:
			//Data Register selection
			ERR=DIO_Write(LCD_PORT,LCD_RS, HIGH);
			//Write option selection
			ERR=DIO_Write(LCD_PORT,LCD_RW, LOW);
			
			/*Sending the higher nibble first*/
			
			//Load Higher data nibble on the 4 bit data pins
			ERR=LCD_SendingNibble(dataHigherNibble);
			LCD_Enable();
			
			/*Sending the lower nibble*/
			
			//Load Lower data nibble on the 4 bit data pins

			ERR=LCD_SendingNibble(dataLowerNibble);
			
			//Enable LCD
			LCD_Enable();
			
			//Update State
			gu8_WriteState = _LCD_WRITE_STATE2;
			break;
			case _LCD_WRITE_STATE2:
			au8_counter++;
			//Delay by os for 5 Seconds
			if (au8_counter == _LCD_WRITING_DELAY)
			{
				ERR = _LCD_WRITE_DONE;
				gu8_WriteState = _LCD_WRITE_STATE1;
			}
			break;
		}
		
		
		#endif
	}
	else
	{
		ERR = LCD_ERROR + E_UNINITIALIZED_MODULE;
	}
	return ERR;
}

/**
 * Input: Pointer to Data string
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Send LCD Write string internally synchronizing with the whole lcd functions
 * 							
 */
static ERROR_STATUS LCD_WriteStr(uint8_t * DataStr)
{
	ERROR_STATUS ERR;
	uint8_t* str = NULL;
	static uint8_t au8_BufferIterator_i,au8_BufferIterator_j;
	
	/*Check if the module initialized or not*/
	if(gu8LCDInitFlag)
	{
		str = DataStr;
		
		/*Check if the Ptr Equal NULL*/
		if(DataStr == NULL)
		{
			ERR =LCD_ERROR + E_NULL_PTR;
		}
		else
		{
			ERR = LCD_ERROR + E_INVALID_PARAMETER;
			/*Loop on the Buffer and send the data byte by byte*/
			while(au8_BufferIterator_i<gu8LCD_BufferSize)
			{
				/*In case the lcd reaches the last col in line one move to line 2*/
				if (au8_BufferIterator_j == LINE_1_LAST_CHAR_POS+ONE)
				{
					LCD_GoToXY(LINE_2,ZERO);
				}
				/*In case the lcd reaches the last col in line two clear the lcd
				 and start from the beginning*/
				else if (au8_BufferIterator_j ==LINE_2_LAST_CHAR_POS+ONE)
				{
					LCD_Clear();
					LCD_GoToXY(LINE_1,ZERO);
					au8_BufferIterator_j=ZERO;
				}
				
				//Sending LCD Data
				ERR = LCD_WriteData(str[au8_BufferIterator_i]);
				
				if (ERR == _LCD_WRITE_DONE)
				{
					au8_BufferIterator_i++;
					au8_BufferIterator_j++;
				}
				
			}
			/*When the writing is finished*/
			ERR = E_TASK_DONE;
			gu8LCD_BufferLockState = _LCD_BUFFER_UNLOCKED;
			au8_BufferIterator_i=ZERO;
			au8_BufferIterator_j=ZERO;
			gu8LCD_BufferSize=ZERO;
		}
	}
	else
	{
		ERR = LCD_ERROR + E_UNINITIALIZED_MODULE;
	}
	
	return ERR;
}

/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Clears LCD
 * 							
 */
ERROR_STATUS LCD_Clear(void)
{
	ERROR_STATUS ERR = LCD_ExecuteCommand(_LCD_CLR);
	return ERR;
}

/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function acts as the LCD Manager that synchronizes the  lcd functions
 * 							
 */
void LCD_Runnable(void)
{
	ERROR_STATUS ERR =E_NOK;
	switch(gu8LCDState)
	{
		/*In case the the lcd is uninialized*/
		case _LCD_IDLE:
		ERR = LCD_Init();
		
		if (ERR ==E_TASK_DONE)
		{
			gu8LCDState = _LCD_BUSY;
		}
		
		break;
		/*In case the the lcd is Ready to print the data*/
		case _LCD_BUSY:
		
		if (gu8LCDState == _LCD_BUFFER_LOCKED)
		{
			
			gu8_WriteState = _LCD_WRITE_STATE1;
			/*Sending the globle buffer*/
			ERR =LCD_WriteStr(gau8LCDBuffer);
		}
		break;
	}
	
}

/**
 * Input: Pointer to Data string
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function act as interface with the user to send data string
 * 							
 */
ERROR_STATUS DisplayData(uint8_t * Data)
{
	ERROR_STATUS ERR;
	if (gu8LCDInitFlag == FALSE)
	{
		ERR = LCD_ERROR + E_NULL_PTR;
	}
	else
	{
		uint8_t * str = Data;
		static uint8_t xFlag;
		/*In case the Buffer is unlocked it will be able to accept new data*/
		if (gu8LCD_BufferLockState == _LCD_BUFFER_UNLOCKED)
		{
			
			while((*str) != '\0')
			{
				gau8LCDBuffer[gu8LCD_BufferSize] = (*str);
				gu8LCD_BufferSize++;
				str++;
				
			}
			/*the Buffer is locked it will be unable to accept new data*/
			gu8LCD_BufferLockState = _LCD_BUFFER_LOCKED;
			ERR= E_OK;
			
			LCD_Clear();
		}
		
		
	}
	return ERR;
}

/**
 * Input: row in the lcd (0/1) and col in the lcd 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function used to re allocate the lcd cursor
 * 							
 */
ERROR_STATUS LCD_GoToXY(uint8_t row, uint8_t col)
{
	ERROR_STATUS ERR;
	if(gu8LCDInitFlag == FALSE)
	{
		ERR = LCD_ERROR + E_UNINITIALIZED_MODULE;
	}
	else
	{
		/*in case the row or the columns are invalid */
		if ((row != LINE_1 && row != LINE_2 )||(col > LAST_LCD_COL))
		{
			ERR = LCD_ERROR + E_INVALID_PARAMETER;
		}
		else
		{
			/*in case the row or the columns are valid move to this location */
			if(row == LINE_1)
				ERR = LCD_ExecuteCommand(DDRAM+LINE_1_FIRST_CHAR+col);
			else
				ERR = LCD_ExecuteCommand(DDRAM+LINE_2_FIRST_CHAR+col);
		}
	}
	return ERR;
}