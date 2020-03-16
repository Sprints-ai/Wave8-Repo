/********************************************************************************
 *																				*
 * Module : LCD																	*
 *																				*
 * File Name : LCD.c															*
 *																				*
 * Description : Source File for LCD Driver.									*
 *																				*
 * Author : Youssef Harby														*
 *																				*
 ********************************************************************************/

#include "LCD.h"
#include "LCD_cfg.h"
#include "LCD_ErrorTable.h"
#include "../MCAL/DIO.h"
#include "util/delay.h"


/********************************************************************************
 * 								Preprocessor Macros								*
 ********************************************************************************/

#define Row0_OFFSET		0x00
#define Row1_OFFSET		0x40
#define Row2_OFFSET		0x10
#define Row3_OFFSET		0x50

#define Row0		0
#define Row1		1
#define Row2		2
#define Row3		3

#define LCD_NOT_INITIALIZED			0x00
#define LCD_INITIALIZED				0x01


/********************************************************************************
 * 							  Global Static Variables							*
 ********************************************************************************/

static uint8_t gu8_LCD_InitializationFlag = LCD_NOT_INITIALIZED;
static uint8_t gu8_LCD_SendCommandOsVar = 0;
static uint8_t gu8_LCD_DisplayCharacterOsVar = 0;


/********************************************************************************
 * 								Functions Definitions							*
 ********************************************************************************/

/*
 * Description : A Function to Initialize the LCD Driver.
 */
ERROR_STATUS LCD_init(void)
{
	sint8_t as8_Ret = E_OK;
	DIO_Cfg_s astr_LcdInitConfig;

	if(gu8_LCD_InitializationFlag == LCD_NOT_INITIALIZED)
	{
		gu8_LCD_InitializationFlag = LCD_INITIALIZED;

		astr_LcdInitConfig.GPIO = LCD_CTRL_GPIO;
		astr_LcdInitConfig.dir = OUTPUT;
		astr_LcdInitConfig.pins = RS | RW | E;

		as8_Ret = DIO_init(&astr_LcdInitConfig);

#if(DATA_BITS_MODE == EIGHT)
		astr_LcdInitConfig.GPIO = LCD_DATA_GPIO;
		astr_LcdInitConfig.dir = OUTPUT;
		astr_LcdInitConfig.pins = FULL_PORT;

		as8_Ret = DIO_init(&astr_LcdInitConfig);

		as8_Ret = LCD_sendCommand(TWO_LINE_LCD_EIGHT_BIT_MODE);
#elif(DATA_BITS_MODE == FOUR)
#ifdef UPPER_PORT_BITS
		astr_LcdInitConfig.GPIO = LCD_DATA_GPIO;
		astr_LcdInitConfig.dir = OUTPUT;
		astr_LcdInitConfig.pins = UPPER_NIBBLE;

		as8_Ret = DIO_init(&astr_LcdInitConfig);
#else
		astr_LcdInitConfig.GPIO = LCD_DATA_GPIO;
		astr_LcdInitConfig.dir = OUTPUT;
		astr_LcdInitConfig.pins = LOWER_NIBBLE;

		as8_Ret = DIO_init(&LCD_init_cfg);
#endif
		as8_Ret = LCD_sendCommand(FOUR_BITS_DATA_MODE_ACTIVATED);
		as8_Ret = LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE);
#endif
		as8_Ret = LCD_sendCommand(CURSOR_OFF);
		as8_Ret = LCD_sendCommand(CLEAR_COMMAND);
	}else
	{
		as8_Ret = LCD_ERROR_MULTIPLE_INITIALIZATION;
	}

	return as8_Ret;
}

/*
 * Description : A Function to send a Command.
 */
ERROR_STATUS LCD_sendCommand(uint8_t Command)
{
	sint8_t as8_Ret = E_OK;

	if(gu8_LCD_InitializationFlag == LCD_INITIALIZED)
	{
		as8_Ret = DIO_Write(LCD_CTRL_GPIO, (RS | RW), LOW);
		_delay_us(50);
		as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, HIGH);
		_delay_us(50);
#if(DATA_BITS_MODE == EIGHT)
		as8_Ret = DIO_Write(LCD_DATA_GPIO, FULL_PORT, Command);
#elif(DATA_BITS_MODE == FOUR)
#ifdef UPPER_PORT_BITS
		as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, UPPER_NIBBLE, UPPER_NIBBLE_OF(Command));
#else
		as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, LOWER_NIBBLE, RIGHT_SHIFT(UPPER_NIBBLE_OF(Command), FOUR));
#endif
		_delay_us(50);
		as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, LOW);
		_delay_us(50);
		as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, HIGH);
		_delay_us(50);
#ifdef UPPER_PORT_BITS
		as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, UPPER_NIBBLE, LEFT_SHIFT(LOWER_NIBBLE_OF(Command), FOUR));
#else
		as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, LOWER_NIBBLE, LOWER_NIBBLE_OF(Command));
#endif
#endif
		_delay_us(50);
		as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, LOW);
	}else if(gu8_LCD_InitializationFlag == LCD_NOT_INITIALIZED)
	{
		as8_Ret = LCD_ERROR_NOT_INITIALIZED;
	}

	return as8_Ret;
}


void testSendCommandOS(void)
{
	static uint8_t testing = 0;

	if(gu8_LCD_SendCommandOsVar != 20)
	{
		testing++;
		gu8_LCD_SendCommandOsVar = testing;
	}
}

/*
 * Description : A Function to send a Command.
 */
ERROR_STATUS LCD_sendCommandWithOs(uint8_t Command)
{
	sint8_t as8_Ret = E_OK;

	if(gu8_LCD_InitializationFlag == LCD_INITIALIZED)
	{
		switch(gu8_LCD_SendCommandOsVar)
		{
		case 0:
			as8_Ret = DIO_Write(LCD_CTRL_GPIO, (RS | RW), LOW);
			gu8_LCD_SendCommandOsVar = 10;
			break;
		case 1:
			as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, HIGH);
			gu8_LCD_SendCommandOsVar = 10;
			break;
		case 2:
#if(DATA_BITS_MODE == EIGHT)
			as8_Ret = DIO_Write(LCD_DATA_GPIO, FULL_PORT, Command);
#elif(DATA_BITS_MODE == FOUR)
#ifdef UPPER_PORT_BITS
			as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, UPPER_NIBBLE, UPPER_NIBBLE_OF(Command));
#else
			as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, LOWER_NIBBLE, RIGHT_SHIFT(UPPER_NIBBLE_OF(Command), FOUR));
#endif
			gu8_LCD_SendCommandOsVar = 10;
			break;
		case 3:
			as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, LOW);
			gu8_LCD_SendCommandOsVar = 10;
			break;
		case 4:
			as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, HIGH);
			gu8_LCD_SendCommandOsVar = 10;
			break;
		case 5:
#ifdef UPPER_PORT_BITS
			as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, UPPER_NIBBLE, LEFT_SHIFT(LOWER_NIBBLE_OF(Command), FOUR));
#else
			as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, LOWER_NIBBLE, LOWER_NIBBLE_OF(Command));
#endif
#endif
			gu8_LCD_SendCommandOsVar = 10;
			break;
		case 6:
			as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, LOW);
			gu8_LCD_SendCommandOsVar = 20;
			break;
		default:
			break;
		}
	}else if(gu8_LCD_InitializationFlag == LCD_NOT_INITIALIZED)
	{
		as8_Ret = LCD_ERROR_NOT_INITIALIZED;
	}

	return as8_Ret;
}


/*
 * Description : A Function to write data (display character).
 */
ERROR_STATUS LCD_displayCharacter(uint8_t Data)
{
	sint8_t as8_Ret = E_OK;

	if(gu8_LCD_InitializationFlag == LCD_INITIALIZED)
	{
		as8_Ret = DIO_Write(LCD_CTRL_GPIO, RS, HIGH);
		as8_Ret = DIO_Write(LCD_CTRL_GPIO, RW, LOW);
		_delay_us(50);
		as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, HIGH);
		_delay_us(50);
#if(DATA_BITS_MODE == EIGHT)
		as8_Ret = DIO_Write(LCD_DATA_GPIO, FULL_PORT, Data);
#elif(DATA_BITS_MODE == FOUR)
#ifdef UPPER_PORT_BITS
		as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, UPPER_NIBBLE, UPPER_NIBBLE_OF(Data));
#else
		as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, LOWER_NIBBLE, RIGHT_SHIFT(UPPER_NIBBLE_OF(Data), FOUR));
#endif
		_delay_us(50);
		as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, LOW);
		_delay_us(50);
		as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, HIGH);
		_delay_us(50);
#ifdef UPPER_PORT_BITS
		as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, UPPER_NIBBLE, LEFT_SHIFT(LOWER_NIBBLE_OF(Data), FOUR));
#else
		as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, LOWER_NIBBLE, LOWER_NIBBLE_OF(Data));
#endif
#endif
		_delay_us(50);
		as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, LOW);
	}else if(gu8_LCD_InitializationFlag == LCD_NOT_INITIALIZED)
	{
		as8_Ret = LCD_ERROR_NOT_INITIALIZED;
	}

	return as8_Ret;
}


void testDisplayCharacterOS(void)
{
	static uint8_t testing = 0;

	if(gu8_LCD_DisplayCharacterOsVar != 20)
	{
		testing++;
		gu8_LCD_DisplayCharacterOsVar = testing;
	}else
	{
		testing = 0;
		gu8_LCD_DisplayCharacterOsVar = 0;
	}
}


ERROR_STATUS LCD_displayCharacterWithOs(uint8_t Data)
{
	sint8_t as8_Ret = E_OK;

	if(gu8_LCD_InitializationFlag == LCD_INITIALIZED)
	{
		switch(gu8_LCD_DisplayCharacterOsVar)
		{
		case 0:
			as8_Ret = DIO_Write(LCD_CTRL_GPIO, RS, HIGH);
			as8_Ret = DIO_Write(LCD_CTRL_GPIO, RW, LOW);
			gu8_LCD_DisplayCharacterOsVar++;
			break;
		case 1:
			as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, HIGH);
			gu8_LCD_DisplayCharacterOsVar++;
			break;
		case 2:
#if(DATA_BITS_MODE == EIGHT)
			as8_Ret = DIO_Write(LCD_DATA_GPIO, FULL_PORT, Data);
#elif(DATA_BITS_MODE == FOUR)
#ifdef UPPER_PORT_BITS
			as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, UPPER_NIBBLE, UPPER_NIBBLE_OF(Data));
#else
			as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, LOWER_NIBBLE, RIGHT_SHIFT(UPPER_NIBBLE_OF(Data), FOUR));
#endif
			gu8_LCD_DisplayCharacterOsVar++;
			break;
		case 3:
			as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, LOW);
			gu8_LCD_DisplayCharacterOsVar++;
			break;
		case 4:
			as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, HIGH);
			gu8_LCD_DisplayCharacterOsVar++;
			break;
		case 5:
#ifdef UPPER_PORT_BITS
			as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, UPPER_NIBBLE, LEFT_SHIFT(LOWER_NIBBLE_OF(Data), FOUR));
#else
			as8_Ret = DIO_WriteValue(LCD_DATA_GPIO, LOWER_NIBBLE, LOWER_NIBBLE_OF(Data));
#endif
#endif
			gu8_LCD_DisplayCharacterOsVar++;
			break;
		case 6:
			as8_Ret = DIO_Write(LCD_CTRL_GPIO, E, LOW);
			gu8_LCD_DisplayCharacterOsVar = 0;
			break;
		default:
			break;
		}
	}else if(gu8_LCD_InitializationFlag == LCD_NOT_INITIALIZED)
	{
		as8_Ret = LCD_ERROR_NOT_INITIALIZED;
	}

	return as8_Ret;
}


/*
 * Description : A Function to display a string.
 */
ERROR_STATUS LCD_displayString(const sint8_t* StringPointer)
{
	sint8_t as8_Ret = E_OK;

	if(gu8_LCD_InitializationFlag == LCD_NOT_INITIALIZED)
	{
		as8_Ret = LCD_ERROR_NOT_INITIALIZED;
	}else if(StringPointer == NULL)
	{
		as8_Ret = LCD_ERROR_NULL_POINTER;
	}else if(StringPointer != NULL)
	{
		while((*StringPointer) != NULL_OPERATOR)
		{
			as8_Ret = LCD_displayCharacter(*StringPointer);
			StringPointer++;
		}
	}

	return as8_Ret;
}

/*
 * Description : A Function to move the cursor to an exact spot.
 */
ERROR_STATUS LCD_goToRowColumn(uint8_t Row, uint8_t Column)
{
	sint8_t as8_Ret = E_OK;
	uint8_t au8_Address;

	if(gu8_LCD_InitializationFlag == LCD_NOT_INITIALIZED)
	{
		as8_Ret = LCD_ERROR_NOT_INITIALIZED;
	}else if(Row > THREE || Column > FIFTEEN)
	{
		as8_Ret = LCD_ERROR_INVALID_PARAMETERS;
	}else
	{
		switch(Row)
		{
		case ZERO :
			au8_Address = Column + Row0_OFFSET;
			break;
		case ONE :
			au8_Address = Column + Row1_OFFSET;
			break;
		case TWO :
			au8_Address = Column + Row2_OFFSET;
			break;
		case THREE :
			au8_Address = Column + Row3_OFFSET;
			break;
		default:
			break;
		}

		as8_Ret = LCD_sendCommand(au8_Address | SET_CURSOR_LOCATION);
	}

	return as8_Ret;
}

/*
 * Description : A Function to move the cursor to an exact spot and display a string at the spot.
 */
ERROR_STATUS LCD_displayStringRowColumn(uint8_t Row, uint8_t Column, const sint8_t* StringPointer)
{
	sint8_t as8_Ret = E_OK;

	if(gu8_LCD_InitializationFlag == LCD_NOT_INITIALIZED)
	{
		as8_Ret = LCD_ERROR_NOT_INITIALIZED;
	}else if(Row > THREE || Column > FIFTEEN)
	{
		as8_Ret = LCD_ERROR_INVALID_PARAMETERS;
	}else if(StringPointer == NULL)
	{
		as8_Ret = LCD_ERROR_NULL_POINTER;
	}else
	{
		as8_Ret = LCD_goToRowColumn(Row, Column);
		as8_Ret = LCD_displayString(StringPointer);
	}

	return as8_Ret;
}

/*
 * Description : A Function to display an integer number.
 */
ERROR_STATUS LCD_displayInteger(sint32_t IntegerNumber)
{
	sint8_t as8_Ret = E_OK;
	sint8_t aas8_Buffer[TWELVE];
	sint8_t* aps8_StringPointer = &aas8_Buffer[ELEVEN];
	sint8_t as8_NegativityFlag = ZERO;

	if(gu8_LCD_InitializationFlag == LCD_NOT_INITIALIZED)
	{
		as8_Ret = LCD_ERROR_NOT_INITIALIZED;
	}else
	{
		if(IntegerNumber < ZERO)
		{
			as8_NegativityFlag = ONE;
			IntegerNumber = -IntegerNumber;
		}

		*aps8_StringPointer = NULL_OPERATOR;

		do{
			*--aps8_StringPointer = (IntegerNumber % TEN) + '0';
			IntegerNumber /= TEN;
		}while(IntegerNumber != ZERO);

		if(as8_NegativityFlag)
			*--aps8_StringPointer = '-';

		as8_Ret = LCD_displayString(aps8_StringPointer);
	}

	return as8_Ret;
}

/*
 * Description : A Function to display an integer number at a certain place.
 */
ERROR_STATUS LCD_displayIntegerRowColumn(uint8_t Row, uint8_t Column, sint32_t IntegerNumber)
{
	sint8_t as8_Ret = E_OK;
	sint8_t aas8_Buffer[TWELVE];
	sint8_t* aps8_StringPointer = &aas8_Buffer[ELEVEN];
	sint8_t as8_NegativityFlag = ZERO;

	if(gu8_LCD_InitializationFlag == LCD_NOT_INITIALIZED)
	{
		as8_Ret = LCD_ERROR_NOT_INITIALIZED;
	}else if(Row > THREE || Column > FIFTEEN)
	{
		as8_Ret = LCD_ERROR_INVALID_PARAMETERS;
	}else
	{
		if(IntegerNumber < ZERO)
		{
			as8_NegativityFlag = ONE;
			IntegerNumber = -IntegerNumber;
		}

		*aps8_StringPointer = NULL_OPERATOR;

		do{
			*--aps8_StringPointer = (IntegerNumber % TEN) + '0';
			IntegerNumber /= TEN;
		}while(IntegerNumber != ZERO);

		if(as8_NegativityFlag)
			*--aps8_StringPointer = '-';

		as8_Ret = LCD_displayStringRowColumn(Row, Column, aps8_StringPointer);
	}

	return as8_Ret;
}

/*
 * Description : A Function to Clear the LCD Screen.
 */
ERROR_STATUS LCD_clear(void)
{
	sint8_t as8_Ret = E_OK;

	if(gu8_LCD_InitializationFlag == LCD_NOT_INITIALIZED)
	{
		as8_Ret = LCD_ERROR_NOT_INITIALIZED;
	}else
	{
		as8_Ret = LCD_sendCommand(CLEAR_COMMAND);
	}
	return as8_Ret;
}
