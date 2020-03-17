/*
 * LCD.c
 *
 * Created: 3/13/2020 2:05:29 PM
 *  Author: A_ayman
 */ 


/*
***Inclusions
*/
#include "LCD.h"
#include <util/delay.h>
#include "../../MCAL/DIO/registers.h"


/*
***Local Macros
*/

/* Function Status */
#define INITIALIZED 1
#define NOT_INITIALIZED 0

/* LCD_Writing_State_Machine values*/
#define WRITING_PART_ONE     1
#define WRITING_PART_TWO     2
#define WRITING_PART_THREE   3
#define WRITING_PART_FOUR    4

/* LCD_Sending_Command_State_Machine values*/
#define SEND_COMMAND_PART_ONE    1
#define SEND_COMMAND_PART_TWO    2
#define SEND_COMMAND_PART_THREE  3
#define SEND_COMMAND_PART_FOUR	4
#define SEND_COMMAND_PART_FIVE   5

/*
*** Global vVariables 
*/
uint8_t gu8_LCD_Init_Flag = NOT_INITIALIZED;

/*
*** Functions Implementation
*/


/*
*** This Function Is used To init LCD 4_BIT
*/
ERROR_STATUS LCD_Init ()
{
	uint8_t u8_Ret_Status = E_OK;
	gu8_LCD_Init_Flag = INITIALIZED;
	/* initializing LCD Directions as OUTPUT*/
	strDIOCfg_t strDIO_info = {LCD_PORT_DATA , UPPER_NIBBLE,OUTPUT};
	strDIOCfg_t strDIO_info2 = {LCD_E_PORT, LCD_E, OUTPUT};
	strDIOCfg_t strDIO_info3 = {LCD_RS_PORT, LCD_RS, OUTPUT};
	strDIOCfg_t strDIO_info4 = {LCD_RW_PORT, LCD_RW, OUTPUT};
	u8_Ret_Status |= DIO_Init(&strDIO_info);
	u8_Ret_Status |= DIO_Init(&strDIO_info2);
	u8_Ret_Status |= DIO_Init(&strDIO_info3);
	u8_Ret_Status |= DIO_Init(&strDIO_info4);
	_delay_ms(50);                                             // said in data sheet to delay after power on for 1st time
	u8_Ret_Status |= DIO_Write(LCD_E_PORT, LCD_E, LOW);
	if (u8_Ret_Status == E_NOK)
	{
		Error_Push(DIO_MODULE, ERROR_DIO_NOT_INITIALIZED);
	}
	u8_Ret_Status |= LCD_sendCommand_None_OS (FOUR_BIT_MODE);
	_delay_us(100);
	u8_Ret_Status |= LCD_sendCommand_None_OS (0x28);
	_delay_ms(1);
	u8_Ret_Status |= LCD_sendCommand_None_OS(CURSOR_OFF);     //D=1(LCD itself on or off) C=0, B=0
	u8_Ret_Status |= LCD_sendCommand_None_OS (CLEAR_LCD);     //clear LCD
	_delay_ms(2); //delay 2ms
	if (u8_Ret_Status == E_NOK)
	{
		gu8_LCD_Init_Flag = NOT_INITIALIZED;
		Error_Push(LCD_MODULE,ERROR_LCD_NOT_INITIALIZED);
	}
	return u8_Ret_Status ;
}


/*
*** this function is used to display string Based on os
*/
ERROR_STATUS LCD_displayString(uint8_t *ptrSentance)
{
	uint8_t u8_Ret_Status = E_OK;
	static uint8_t u8_Loop_Count=0;
	static uint8_t u8_Enteranc_Count = 0;
	u8_Enteranc_Count++;
	if (gu8_LCD_Init_Flag == INITIALIZED)
	{
		if (ptrSentance != NULL)
		{	
			if (u8_Enteranc_Count == 8)
			{
				u8_Loop_Count++;
	
				u8_Enteranc_Count=0;
			}
			for (u8_Loop_Count=u8_Loop_Count;ptrSentance[u8_Loop_Count]!= NULL;)
			{
				u8_Ret_Status |= LCD_displayChar(ptrSentance[u8_Loop_Count]);
				break;
			}
			if (ptrSentance[u8_Loop_Count]==NULL)
			{
				u8_Loop_Count=ZERO;
			}
		}
		else
		{
			u8_Ret_Status |= E_NOK;
			Error_Push(LCD_MODULE,ERROR_NULL_POINTER);
		}
	}
	else
	{
		u8_Ret_Status |= E_NOK;
		Error_Push(LCD_MODULE,ERROR_LCD_NOT_INITIALIZED);
	}
	return u8_Ret_Status ;
}

/*This Function Is Used To Force Cursor to a Certain Position*/
ERROR_STATUS LCD_displayStringRowColumn (uint8_t ROW, uint8_t COL)
{	
	uint8_t u8_Ret_Status = E_OK;
	if (gu8_LCD_Init_Flag == INITIALIZED)
	{
		if(ZERO == COL)
		{
			if (ROW>=0 && ROW <=15)
			{
				u8_Ret_Status |= LCD_sendCommand(0x80 + ROW);
			}
		}
		else if (ONE == COL)
		{
			if (ROW>=0 && ROW <=15)
			{
				u8_Ret_Status |= LCD_sendCommand(0xC0 + ROW);
			}
		}
	}
	else
	{
		u8_Ret_Status|= E_NOK;
		Error_Push(LCD_MODULE, ERROR_LCD_NOT_INITIALIZED);
	}
	return u8_Ret_Status ;
}

/*
*** This Function Is used To Clear LCD
*/
ERROR_STATUS LCD_clear(void)
{
	uint8_t u8_Ret_Status = E_OK;
	if (gu8_LCD_Init_Flag == INITIALIZED)
	{
		u8_Ret_Status |= DIO_Write (LCD_RS_PORT, LCD_RS, LOW);
		u8_Ret_Status |= DIO_Write (LCD_RW_PORT, LCD_RW, LOW);
		u8_Ret_Status |= DIO_Write (LCD_PORT_DATA,UPPER_NIBBLE,(1));
		u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, HIGH);
		u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, LOW);
	}
	else
	{
		u8_Ret_Status |= E_NOK;
		Error_Push(LCD_MODULE, ERROR_LCD_NOT_INITIALIZED);
	}
	
	return u8_Ret_Status;
}

/*
*** This Function Is used To SEND CMD Based on 4 bit mode and Sos
*/
ERROR_STATUS LCD_sendCommand(uint8_t u8_Command)
{
	uint8_t u8_Ret_Status = E_OK;
	static uint8_t u8_SendCommand_State = SEND_COMMAND_PART_ONE;
	static uint8_t u8_sendCommand_Entrance_Time = ZERO;
   u8_sendCommand_Entrance_Time ++;
	if (gu8_LCD_Init_Flag == INITIALIZED)
	{
		switch (u8_SendCommand_State)
		{
			case SEND_COMMAND_PART_ONE:
			{
				if ( u8_sendCommand_Entrance_Time == TWO)
				{
					u8_SendCommand_State = WRITING_PART_TWO;
					u8_sendCommand_Entrance_Time = ZERO;
					break;
				}
				u8_Ret_Status |= DIO_Write (LCD_RS_PORT, LCD_RS, LOW);
				u8_Ret_Status |= DIO_Write (LCD_RW_PORT, LCD_RW, LOW);
				u8_Ret_Status |= DIO_Write (LCD_PORT_DATA, UPPER_NIBBLE,(u8_Command&UPPER_NIBBLE));
				u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, HIGH);
				break;
			}
			case SEND_COMMAND_PART_TWO:
			{
				if ( u8_sendCommand_Entrance_Time == TWO)
				{
					u8_SendCommand_State = WRITING_PART_THREE;
					u8_sendCommand_Entrance_Time = ZERO;
					break;
				}
			  u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, LOW);
				break;
			}
			case SEND_COMMAND_PART_THREE:
			{
				if ( u8_sendCommand_Entrance_Time == TWO)
				{
					u8_SendCommand_State =SEND_COMMAND_PART_FOUR;
					u8_sendCommand_Entrance_Time = ZERO;
					break;
				}	
				u8_Ret_Status |= DIO_Write (LCD_PORT_DATA, UPPER_NIBBLE,(u8_Command<<4));
				u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, HIGH);
				break;
			}
			case SEND_COMMAND_PART_FOUR:
			{
				if ( u8_sendCommand_Entrance_Time == TWO)
				{
					u8_SendCommand_State = SEND_COMMAND_PART_ONE;
					u8_sendCommand_Entrance_Time = ZERO;
					break;
				}
				u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, LOW);
				break;
			}
			default:
			break;
		}
	}
	else
	{
		u8_Ret_Status |= E_NOK;
		Error_Push(LCD_MODULE, ERROR_LCD_NOT_INITIALIZED);
	}
		
	return u8_Ret_Status;
}
 
/*
*** This Function Is Used To Display Character Based on OS
*/
ERROR_STATUS LCD_displayChar(uint8_t u8_Data)
{
	uint8_t u8_Ret_Status = E_OK;
	static uint8_t displayChar_State = WRITING_PART_ONE; 
   static uint8_t u8_displayChar_Entrance_Time = ZERO;
	if (gu8_LCD_Init_Flag == INITIALIZED)
	{
		if (u8_Data != NULL)
		{
			switch (displayChar_State)
			{
				case WRITING_PART_ONE:
				{
					u8_displayChar_Entrance_Time++;
					if (u8_displayChar_Entrance_Time == TWO)
					{
						displayChar_State = WRITING_PART_TWO;
						u8_displayChar_Entrance_Time = ZERO;
						break;
					}
					u8_Ret_Status |= DIO_Write (LCD_RS_PORT, LCD_RS,HIGH);
					u8_Ret_Status |= DIO_Write (LCD_RW_PORT, LCD_RW, LOW);
					u8_Ret_Status |= DIO_Write (LCD_PORT_DATA, UPPER_NIBBLE,(u8_Data&UPPER_NIBBLE));
					u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, HIGH);
					break;
				}
				case WRITING_PART_TWO:
				{
					u8_displayChar_Entrance_Time++;
					if (u8_displayChar_Entrance_Time == TWO)
					{
						displayChar_State = WRITING_PART_THREE;
						u8_displayChar_Entrance_Time = ZERO;
						break;
					}
					u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E,LOW);
					break;
				}
				case  WRITING_PART_THREE:
				{
					u8_displayChar_Entrance_Time++;
					if (u8_displayChar_Entrance_Time == TWO)
					{
						displayChar_State = WRITING_PART_FOUR;
						u8_displayChar_Entrance_Time = ZERO;
						break;
					}
					u8_Ret_Status |= DIO_Write (LCD_PORT_DATA,UPPER_NIBBLE,(u8_Data<<4));
					u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, HIGH);
					break;
				}
				case WRITING_PART_FOUR:
				{ 
					u8_displayChar_Entrance_Time++;
					if (u8_displayChar_Entrance_Time == TWO)
					{
						displayChar_State = WRITING_PART_ONE;
						u8_displayChar_Entrance_Time = ZERO;
						break;
					}
					u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, LOW);
					break;
				}
				default:
				break;

			}
		}
		else 
		{
			u8_Ret_Status = E_NOK;
			Error_Push(LCD_MODULE,ERROR_INVALID_PARAMETER);
		}
	}
	else
	{
		u8_Ret_Status = E_NOK;
		Error_Push(LCD_MODULE,ERROR_LCD_NOT_INITIALIZED);
		
	}
}


/*
*** This Function Is Used To Display Character 
*/
ERROR_STATUS LCD_displayChar_None_OS(uint8_t u8_Data)
{
	uint8_t u8_Ret_Status = E_OK ;
	if (gu8_LCD_Init_Flag == INITIALIZED)
	{
		if (u8_Data != NULL) 
		{
			u8_Ret_Status |= DIO_Write (LCD_RS_PORT, LCD_RS,HIGH);
			u8_Ret_Status |= DIO_Write (LCD_RW_PORT, LCD_RW, LOW);
			_delay_ms(1);
			u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, HIGH);
			_delay_ms(1);
			u8_Ret_Status |= DIO_Write (LCD_PORT_DATA,UPPER_NIBBLE,(u8_Data & UPPER_NIBBLE));
			_delay_ms(1);
			u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E,LOW);
			_delay_ms(1);
			u8_Ret_Status |= DIO_Write (LCD_RS_PORT, LCD_RS,HIGH);
			u8_Ret_Status |= DIO_Write (LCD_RW_PORT, LCD_RW, LOW);
			_delay_ms(1);
			u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, HIGH);
			u8_Ret_Status |= DIO_Write (LCD_PORT_DATA,UPPER_NIBBLE,(u8_Data<<4));
			_delay_ms(1);
			u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, LOW);
			_delay_ms(1);
		}
		else
		{
			u8_Ret_Status |= E_NOK;
			Error_Push(LCD_MODULE, ERROR_INVALID_PARAMETER);
		}
	}
	else
	{
		u8_Ret_Status |=E_NOK;
		Error_Push(LCD_MODULE, ERROR_LCD_NOT_INITIALIZED);
	}
	return u8_Ret_Status;
}


/*
*** This Function Is Used To Display String
*/
ERROR_STATUS LCD_displayString_None_OS(uint8_t *ptrSentance)
{
   uint8_t u8_Loop_Count=ZERO;
	uint8_t u8_Ret_Status = E_OK;
	if (gu8_LCD_Init_Flag == INITIALIZED)
	{
		if (ptrSentance != NULL)
		{
			while (ptrSentance[u8_Loop_Count]!=NULL)
			{
				u8_Ret_Status |= LCD_displayChar_None_OS(ptrSentance[u8_Loop_Count]);
					u8_Loop_Count++;
			}
		}
		else 
		{
			u8_Ret_Status = E_NOK;
			Error_Push(LCD_MODULE,ERROR_NULL_POINTER);
		}
	}
	else
	{
		u8_Ret_Status |= E_NOK;
		Error_Push(LCD_MODULE,ERROR_LCD_NOT_INITIALIZED);
	}
	return u8_Ret_Status;

}
/*
*** Sending Commands using 4 bit mode without OS
*/
ERROR_STATUS LCD_sendCommand_None_OS(uint8_t u8_Command)
{	
	uint8_t u8_Ret_Status = E_OK; 
	if (gu8_LCD_Init_Flag == INITIALIZED)
	{
		u8_Ret_Status |= DIO_Write (LCD_RS_PORT, LCD_RS, LOW);
		u8_Ret_Status |= DIO_Write (LCD_RW_PORT, LCD_RW, LOW);
		u8_Ret_Status |= 	DIO_Write (LCD_PORT_DATA,UPPER_NIBBLE,(u8_Command & UPPER_NIBBLE));
		u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, HIGH);
		_delay_ms(2);
		u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, LOW);
		_delay_ms(2);
		u8_Ret_Status |= DIO_Write (LCD_PORT_DATA,UPPER_NIBBLE,(u8_Command<<4));
		u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, HIGH);
		_delay_ms(2);
		u8_Ret_Status |= DIO_Write (LCD_E_PORT, LCD_E, LOW);
		_delay_ms(2);
	}
	else
	{
		u8_Ret_Status |= E_NOK;
		Error_Push(LCD_MODULE,ERROR_LCD_NOT_INITIALIZED);
	}
	return u8_Ret_Status ;
}


/*
*** This Function Is used To init LCD 8_BIT
*/
ERROR_STATUS LCD_init_8Bit_Mode ()
{
	uint8_t u8_Ret_Status = E_OK;
	gu8_LCD_Init_Flag = INITIALIZED;
	/* initializing LCD Directions as OUTPUT*/
	strDIOCfg_t strDIO_info  = {LCD_PORT_DATA ,0XF0,OUTPUT};
	strDIOCfg_t strDIO_info2 = {LCD_E_PORT, LCD_E, OUTPUT};
	strDIOCfg_t strDIO_info3 = {LCD_RS_PORT, LCD_RS, OUTPUT};
	strDIOCfg_t strDIO_info4 = {LCD_RW_PORT, LCD_RW, OUTPUT};
	u8_Ret_Status |= DIO_Init(&strDIO_info);
	u8_Ret_Status |= DIO_Init(&strDIO_info2);
	u8_Ret_Status |= DIO_Init(&strDIO_info3);
	u8_Ret_Status |= DIO_Init(&strDIO_info4);
	_delay_ms(50);                                             // said in data sheet to delay after power on for 1st time
	u8_Ret_Status |= LCD_sendCommand_None_OS (0x32);           //N=1 , F=0
	_delay_ms(1);                                              //delay 1ms a must delay as said in data sheet
	u8_Ret_Status |= LCD_sendCommand_None_OS (CURSOR_OFF);     //D=1(LCD itself on or off) C=0, B=0
	_delay_ms(1);                                              //delay 1ms
	u8_Ret_Status |= LCD_sendCommand_None_OS (CLEAR_LCD);      //clear LCD
	_delay_ms(2);
	u8_Ret_Status |= LCD_sendCommand_None_OS(0x0E);
	_delay_ms(2);
	
	return u8_Ret_Status ;
}