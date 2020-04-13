/*
 * LCD.c
 *
 * Created: 3/12/2020 11:27:42 AM
 *  Author: Ehab
 */ 


/********************************** Header Files INCLUSIONS ****************************/
#define F_CPU 16000000
#include <util/delay.h>

#include "../Infrastructure/std_types.h"
#include "../MCAL/DIO.h"
#include "LCD.h"

/***************************************************************************************/

/*
 -------------                 ------------
 | ATmega32  |                 |   LCD    |
 |           |                 |          |
 |			 |	-------------->|D7        |
 |			 | |  ------------>|D6        |
 |			 | | |	---------->|D5        |
 |           | | | |   ------->|D4        |
 |        PA7|-| | |  |		   |D3        |
 |        PA6|---| |  |	 	   |D2        |
 |        PA5|-----|  |		   |D1        |
 |        PA4|--------|		   |D0        |
 |        PA3|---------------->|E         |
 |        PA2|---------------->|RW        |
 |        PA1|---------------->|RS        |
 |		  PA0|				   |		  |
 -------------                 ------------
 */


/***************************************************************************************/
/********************************** Macros *********************************************/
/***************************************************************************************/



#define LCD_OS_STATE_START			(0)
#define LCD_OS_STATE_HOME			(30)
#define LCD_OS_STATE_SET_4BIT		(45)
#define LCD_OS_STATE_DIS_ON			(46)
#define LCD_OS_STATE_CLEAR			(47)
#define LCD_OS_STATE_ENTRY_MODE		(62)
#define LCD_OS_STATE_FINISH_INIT	(64)

/***************************************************************************************/
/********************************** Global Variables ***********************************/
/***************************************************************************************/

static uint8_t gu8_LCD_InitFlag = FALSE;
uint8_t gu8_LCD_SendCmdFlag = FALSE;
static uint8_t gu8_LCD_SendCharFlag = FALSE;
static uint8_t gu8_gotoRowColumnFlag = FALSE;
static uint8_t gu8_sendStringFlag = FALSE;

/***************************************************************************************/
/* Description! Apply initialization sequence for LCD module                           */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
ERROR_STATUS LCD_init (uint8_t OperationMode,uint8_t* pu8_Notification)
{
	ERROR_STATUS ERR = E_OK;
	
	uint8_t static u8_LCD_OS_StateMachine_State = LCD_OS_STATE_START;
	
	
	DIO_Cfg_s LCD_DIO_Config = {LCD_PORT , LCD_PINS , OUTPUT};
	
	if (gu8_LCD_InitFlag)
	{
		ERR = ERROR_MODULE_ALREADY_INITIALIZED;
	}
	else
	{
		
		DIO_init(&LCD_DIO_Config);	
		switch (OperationMode)
		{
			case LCD_NORMAL:
				/* Delay 30ms to ensure the initialization of the LCD driver */
				_delay_ms(30);

				/* Return Home  */
				LCD_sendCommand(lcd_Home,LCD_NORMAL,NULL);
				_delay_ms(15);

				/* Function Set  */
				LCD_sendCommand(lcd_FunctionSet8bit,LCD_NORMAL,NULL);
				_delay_ms(1);

				/* Display ON OFF Control */
				LCD_sendCommand(lcd_DisplayOn,LCD_NORMAL,NULL);
				_delay_ms(1);

				/* Clear Display */
				LCD_sendCommand(lcd_Clear,LCD_NORMAL,NULL);
				_delay_ms(15);

				/* Entry Mode Set  */
				LCD_sendCommand(lcd_EntryMode,LCD_NORMAL,NULL);
				_delay_ms(2);
				
				break;
				
			case LCD_OS:
				switch (u8_LCD_OS_StateMachine_State)
				{
					case LCD_OS_STATE_HOME:
						
						LCD_sendCommand(lcd_Home , LCD_OS,NULL);
						
						if (gu8_LCD_SendCmdFlag)
						{
							
							u8_LCD_OS_StateMachine_State++;
							gu8_LCD_SendCmdFlag = FALSE;
							
						}
						break;
						
					case LCD_OS_STATE_SET_4BIT:
						
						LCD_sendCommand(lcd_FunctionSet4bit , LCD_OS,NULL);
						if (gu8_LCD_SendCmdFlag)
						{
							u8_LCD_OS_StateMachine_State++;
							gu8_LCD_SendCmdFlag = FALSE;
							
						}
						break;
						
					case LCD_OS_STATE_DIS_ON:
						
						LCD_sendCommand(lcd_DisplayOn , LCD_OS,NULL);
						
						if (gu8_LCD_SendCmdFlag)
						{
							u8_LCD_OS_StateMachine_State++;
							gu8_LCD_SendCmdFlag = FALSE;
							
						}
						break;
						
					case LCD_OS_STATE_CLEAR:
					
						LCD_sendCommand(lcd_Clear , LCD_OS,NULL);
						if (gu8_LCD_SendCmdFlag)
						{
							u8_LCD_OS_StateMachine_State++;
							gu8_LCD_SendCmdFlag = FALSE;
							
						}
						break;
						
					case LCD_OS_STATE_ENTRY_MODE:
						LCD_sendCommand(lcd_EntryMode , LCD_OS,NULL);
						if (gu8_LCD_SendCmdFlag)
						{
							u8_LCD_OS_StateMachine_State++;
							gu8_LCD_SendCmdFlag = FALSE;
							
						}
						break;
						
					case LCD_OS_STATE_FINISH_INIT:
						gu8_LCD_InitFlag = TRUE;
						
						PORTC_DATA = 0x06;
						
						
						break;
						
					default:
						u8_LCD_OS_StateMachine_State++;
						break;
				}
					
				if (gu8_LCD_InitFlag)
				{
					u8_LCD_OS_StateMachine_State = LCD_OS_STATE_START;
					*pu8_Notification = DONE;
				}
			
			break;
				
		default:
			ERR = ERROR_INVALID_PARAMETER;
			break;
		}
	}
	
	return ERR;	
}

/***************************************************************************************/
/* Description! Interface to send the configuration commands to the LCD Driver         */
/* Input      ! Command number                                                         */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
ERROR_STATUS LCD_sendCommand(uint8_t u8_Cmd , uint8_t OperationMode , uint8_t* pu8_Notification)
{
	
	ERROR_STATUS ERR = E_OK;
	static uint8_t u8_LCD_OS_StateMachine_State = LCD_OS_STATE_START;
	
	if (TRUE)
	{
		switch (OperationMode)
		{
			case LCD_NORMAL:
			/* Set RS to LOW */
			DIO_Write(LCD_PORT, LCD_RS_PIN, LOW);

			/* Set R/W to LOW */
			DIO_Write(LCD_PORT, LCD_RW_PIN, LOW);

			/* Set E to HIGH  */
			DIO_Write(LCD_PORT, LCD_ENABLE, HIGH);

			/* Load Command on Data bus */
			DIO_Write(LCD_PORT,LCD_DATA_PINS, u8_Cmd);

			/* Set E to LOW */
			DIO_Write(LCD_PORT, LCD_ENABLE, LOW);

			/* Wait for E to settle */
			_delay_ms(5);

			/* Set E to HIGH */
			DIO_Write(LCD_PORT,LCD_ENABLE, HIGH);
			
			_delay_ms(1);

			/* Load Command on Data bus */
			DIO_Write(LCD_PORT,LCD_DATA_PINS, u8_Cmd << 4);

			/* Set E to LOW */
			DIO_Write(LCD_PORT, LCD_ENABLE, LOW);

			/* Delay for 10ms to let the LCD display the character */
			_delay_ms(10);
			
			break;
			
			case LCD_OS:
			switch (u8_LCD_OS_StateMachine_State)
			{
				case 0:
				/* Set RS to LOW */
				
				ClearBit(PORTA_DATA,LCD_RS_PIN);
				break;
				
				case 5:
				/* Set R/W to LOW */
				ClearBit(PORTA_DATA,LCD_RW_PIN);
				
				/* Set E to HIGH  */
				SetBit(PORTA_DATA,LCD_ENABLE);
				break;
				
				case 6:
				/* Load char on Data bus */
				PORTA_DATA = ((u8_Cmd & 0xF0));
				
				/* Set E to LOW */
				ClearBit(PORTA_DATA,LCD_ENABLE);
				break;
				
				case 11:
				/* Set E to HIGH */
				SetBit(PORTA_DATA,LCD_ENABLE);
				break;
				
				case 21:
				/* Load the Remainder of the char on data bus*/
				PORTA_DATA = ((u8_Cmd & 0x0F) << 4);
				break;
				
				case 22:
				/* Set E to LOW*/
				ClearBit(PORTA_DATA,LCD_ENABLE);
				break;
				
				case 28:
				/* Set E to HIGH */
				SetBit(PORTA_DATA,LCD_ENABLE);
				break;
				
				case 48:
				/* Wait for the LCD to Process the command then set the flag */
				gu8_LCD_SendCmdFlag = TRUE;
				break;
			}
			u8_LCD_OS_StateMachine_State++;
			
			if (gu8_LCD_SendCmdFlag)
			{
				u8_LCD_OS_StateMachine_State = LCD_OS_STATE_START;
				*pu8_Notification = DONE;
			}
			break;
			
			default:
			ERR = ERROR_INVALID_PARAMETER;
			break;
		}
	}
	return ERR;
}

/***************************************************************************************/
/* Description! Interface to write character on LCD screen                             */
/* Input      ! Data to send                                                           */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
ERROR_STATUS LCD_DisplayChar(uint8_t u8_DataCpy, uint8_t OperationMode , uint8_t* pu8_Notification)
{
	ERROR_STATUS ERR = E_OK;
	static uint8_t u8_LCD_OS_StateMachine_State = LCD_OS_STATE_START;
	
	if (gu8_LCD_InitFlag)
	{
		
		/* Set RS to HIGH */
		SetBit(PORTA_DATA,LCD_RS_PIN);
		
		/* Set R/W to LOW */
		ClearBit(PORTA_DATA,LCD_RW_PIN);
		
		switch (OperationMode)
		{
			case LCD_NORMAL:
			/* Set RS to LOW */
			DIO_Write(LCD_PORT, LCD_RS_PIN, HIGH);

			/* Set R/W to LOW */
			DIO_Write(LCD_PORT, LCD_RW_PIN, LOW);

			/* Set E to HIGH  */
			DIO_Write(LCD_PORT, LCD_ENABLE, HIGH);

			/* Load Command on Data bus */
			DIO_Write(LCD_PORT,LCD_DATA_PINS, u8_DataCpy);

			/* Set E to LOW */
			DIO_Write(LCD_PORT, LCD_ENABLE, LOW);

			/* Wait for E to settle */
			_delay_ms(5);

			/* Set E to HIGH */
			DIO_Write(LCD_PORT,LCD_ENABLE, HIGH);
			
			_delay_ms(1);

			/* Load Command on Data bus */
			DIO_Write(LCD_PORT,LCD_DATA_PINS, u8_DataCpy << 4);

			/* Set E to LOW */
			DIO_Write(LCD_PORT, LCD_ENABLE, LOW);

			/* Delay for 10ms to let the LCD display the character */
			_delay_ms(10);
			
			break;
			
			case LCD_OS:
			if (!gu8_LCD_SendCharFlag)
			{
				switch (u8_LCD_OS_StateMachine_State)
				{
					case 0:
					/* Set E to HIGH  */
					SetBit(PORTA_DATA,LCD_ENABLE);
					
					/* Load char on Data bus */
					PORTA_DATA &=  0x0F;
					PORTA_DATA |= ((u8_DataCpy & 0xF0));
					
					/* Set E to LOW */
					ClearBit(PORTA_DATA,LCD_ENABLE);
					break;
					
					case 5:
					/* Set E to HIGH */
					SetBit(PORTA_DATA,LCD_ENABLE);
					
					break;
					
					case 15:
					PORTA_DATA &=  0x0F;
					PORTA_DATA |= ((u8_DataCpy & 0x0F) << 4);
					
					ClearBit(PORTA_DATA,LCD_ENABLE);
					
					break;
					
					case 20:
					SetBit(PORTA_DATA,LCD_ENABLE);
					break;
					
					case 30:
					gu8_LCD_SendCharFlag = TRUE;
					u8_LCD_OS_StateMachine_State = LCD_OS_STATE_START;
					break;
				}
			}
			
		
			if (!gu8_LCD_SendCharFlag)
			{
				u8_LCD_OS_StateMachine_State++;
			}
			else
			{
				u8_LCD_OS_StateMachine_State = LCD_OS_STATE_START;
				*pu8_Notification = DONE;
			}
			break;
			
			default:
			ERR = ERROR_INVALID_PARAMETER;
			break;
		}
	}
	return ERR;
}

/***************************************************************************************/
/* Description! Interface to write string on LCD screen                                */
/* Input      ! Pointer to the string                                                  */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_DisplayString (uint8_t* puint8_tStringCpy, uint8_t uint8_tIndex,uint8_t* pu8_Notification)
{
	static uint8_t i = 0;
	
	if (gu8_LCD_InitFlag)
	{
		if (!gu8_sendStringFlag)
		{
			if (i<uint8_tIndex)
			{
				LCD_DisplayChar(puint8_tStringCpy[i],LCD_OS,NULL);
				if (gu8_LCD_SendCharFlag)
				{
					i++;
					gu8_LCD_SendCharFlag = FALSE;
					
				}
			}
			else
			{
				*pu8_Notification = DONE;
				gu8_LCD_SendCharFlag = FALSE;
				gu8_sendStringFlag = TRUE;
				
				i=0;
				
			}
		}
	}
	
}

/***************************************************************************************/
/* Description! Interface to start the writing process at certain digit in the LCD     */
/* Input      ! Y = Row position , X = Column position                                 */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void gotoRowColumn (uint8_t u8_Row,uint8_t u8_Column)
{
	static uint8_t x = 1;
	
	if (!gu8_gotoRowColumnFlag)
	{
		
		if (u8_Column>0 && u8_Column<=16)
		{
			switch(u8_Row)
			{
				case 1:
				LCD_sendCommand(u8_Column+0x80,LCD_OS,NULL);
				if(gu8_LCD_SendCmdFlag)
				{
					gu8_gotoRowColumnFlag = TRUE;
					
				}
				break;
				case 2:
				LCD_sendCommand(u8_Column+191,LCD_OS,NULL);
				TCNT1 = x;
				x++;
				if(gu8_LCD_SendCmdFlag)
				{
					gu8_gotoRowColumnFlag = TRUE;
					
				}
				break;
				
				default:
				break;
			}
			
		}
	}
	
}

/***************************************************************************************/
/* Description! Interface to start displaying at certain digit in the LCD              */
/* Input      ! Y = Row position , X = Column position                                 */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_displayStringRowColumn (uint8_t u8_Row , uint8_t u8_Column, uint8_t* puint8_tStringCpy, uint8_t uint8_tIndex, uint8_t* pu8_Notification)
{
	static uint8_t u8_Command_Finished =  FALSE;
	//pu8_Notification = 0;
	if (gu8_LCD_InitFlag)
	{
		switch (u8_Row)
		{
			case 1:
			if (!u8_Command_Finished)
			{
				LCD_sendCommand(u8_Column|0x80 ,LCD_OS,NULL);
			}
			if(gu8_LCD_SendCmdFlag)
			{
				u8_Command_Finished = TRUE;
				LCD_DisplayString(puint8_tStringCpy,uint8_tIndex,pu8_Notification);
			}
			break;
			
			case 2:
			if (!u8_Command_Finished)
			{
				LCD_sendCommand(u8_Column|0xC0,LCD_OS,NULL);
			}
			if (gu8_LCD_SendCmdFlag)
			{
				u8_Command_Finished = TRUE;
				LCD_DisplayString(puint8_tStringCpy,uint8_tIndex,pu8_Notification);
			}
			break;
		}
		if (gu8_sendStringFlag)
		{
			gu8_LCD_SendCmdFlag = FALSE;
			u8_Command_Finished = FALSE;
			gu8_sendStringFlag = FALSE;
			*pu8_Notification = DONE;
		}
	}
	
}
