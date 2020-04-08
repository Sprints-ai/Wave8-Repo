/*
 * LCD.c
 *
 * Created: 3/14/2020 12:18:37 PM
 *  Author: Ahmed
 */ 

/************************************************************************/
/*                       	Includes                 	                */
/************************************************************************/

#include "std_types.h"
#include "DIO.h"
#include "LCD_cfg.h"
#include "LCD.h"

#define F_CPU	16000000UL
#include "Util/delay.h"

/************************************************************************/
/*                       General macros                                 */
/************************************************************************/

/*
* Register bit manipulation
*/
#define SET_BIT(REG,BIT)		REG |= (1<<BIT)
#define CLEAR_BIT(REG,BIT)		REG &= ~(1<<BIT)
#define TOGGLE_BIT(REG,BIT)		REG ^= (1<<BIT)
#define GET_BIT(REG,BIT)		((REG >> BIT) & 0x01)

/*Important LCD operation delays*/
#define INIT_DELAY_MS			(35)
#define INIT_CLEAR_DELAY_MS		(2)
#define CMD_INTERVAL_DELAY_MS	(1)
#define DATA_LATCHING_DELAY_US	(20)

/*4 bits right shifting*/
#define BITS_SHIFTING_RIGHT_4	(4)

/*Basic LCD commands*/
#define FUNCTION_SET_8BIT_CMD	(0x3C)
#define FUNCTION_SET_4BIT_CMD	(0x2C)
#define DISPLAY_ON_OFF_CMD		(0x0F)
#define DISPLAY_CLEAR_CMD		(0x01)
#define ENTRY_MODE_SET_CMD		(0x06)
#define FIRST_LINE_CMD			(0x80)
#define SECOND_LINE_CMD			(0xC0)

/*RS and RW pins status*/
#define RS_DATA_MODE			(HIGH)
#define RS_CMD_MODE				(LOW)
#define RW_READ_MODE			(HIGH)
#define RW_WRITE_MODE			(LOW)

/*Bits used in LCD operations*/
#define BIT0					(0)
#define BIT1					(1)
#define BIT2					(2)
#define BIT3					(3)
#define BIT4					(4)
#define BIT5					(5)
#define BIT6					(6)
#define BIT7					(7)

/************************************************************************/
/*                       LCD Function's definitions                     */
/************************************************************************/

EnmLCDError_t LCD_init(void)
{
	/*Variable used for LCD error indication*/
	EnmLCDError_t err_var = OPERATION_SUCCESS;
	
	/*Choosing LCD operating mode*/
	#if (LCD_DATA_MODE == DATA_8BIT_MODE)
	{
		/*Setting LCD control pins(Rs - RW - EN) as OUTPUTs*/
		DIO_init(LCD_CTRL_PORT , LCD_RS_PIN | LCD_RW_PIN | LCD_EN_PIN , OUTPUT);
		
		/*Setting LCD data pins (D0 ~ D7) as OUTPUTs*/
		DIO_init(LCD_DATA_PORT , LCD_DATA_PIN0 | LCD_DATA_PIN1 | LCD_DATA_PIN2 |
								 LCD_DATA_PIN3 | LCD_DATA_PIN4 | LCD_DATA_PIN5 |
								 LCD_DATA_PIN6 | LCD_DATA_PIN7 , OUTPUT);
		
		/*8-bit Mode basic initialization*/
		
		/*Initialization delay*/
		_delay_ms(INIT_DELAY_MS);
		
		/*Function set command which indicates the character size and number of lines used*/
		LCD_sendCommand(FUNCTION_SET_8BIT_CMD);
		
		/*Interval delay between two commands*/
		_delay_ms(CMD_INTERVAL_DELAY_MS);
		
		/*Command controls display power on and off and the cursor settings*/
		LCD_sendCommand(DISPLAY_ON_OFF_CMD);
		
		/*Interval delay between two commands*/
		_delay_ms(CMD_INTERVAL_DELAY_MS);
		
		/*Clearing the display*/
		LCD_sendCommand(DISPLAY_CLEAR_CMD);
		
		/*Delay after clearing the display*/
		_delay_ms(INIT_CLEAR_DELAY_MS);
		
		/*Setting the LCD mode with no shifting*/
		LCD_sendCommand(ENTRY_MODE_SET_CMD);						 		
	} 
	#else
	{
		/*Setting LCD control pins(Rs - RW - EN) as OUTPUTs*/
		DIO_init(LCD_CTRL_PORT , LCD_RS_PIN | LCD_RW_PIN | LCD_EN_PIN , OUTPUT);
		
		/*Setting LCD data pins (D4 ~ D7) as OUTPUTs*/
		DIO_init(LCD_DATA_PORT , LCD_DATA_PIN4 | LCD_DATA_PIN5 |
								 LCD_DATA_PIN6 | LCD_DATA_PIN7 , OUTPUT);
		
		/*4-bit Mode basic initialization*/
		
		/*Initialization delay*/
		_delay_ms(INIT_DELAY_MS);
		
		/*Function set command which indicates the character size and number of lines used*/
		/*Sending the command the highest 4-bit nibble first*/
		DIO_Write(LCD_CTRL_PORT , LCD_RS_PIN , RS_CMD_MODE);
		DIO_Write(LCD_CTRL_PORT , LCD_RW_PIN , RW_WRITE_MODE);
		
		/*Writing data to the MSByte*/		
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN4 , LOW );
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN5 , HIGH );
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN6 , LOW );
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN7 , LOW );

		/*Rising enable pin to high so LCD can read coming data*/
		DIO_Write(LCD_CTRL_PORT , LCD_EN_PIN , HIGH);
		
		/*Waiting the data to be written*/
		_delay_us(DATA_LATCHING_DELAY_US);
		
		/*Setting enable pin to low so that LCD can write the received data*/
		DIO_Write(LCD_CTRL_PORT , LCD_EN_PIN , LOW);
		
		/*Sending the function set command*/		
		LCD_sendCommand(FUNCTION_SET_4BIT_CMD);
		
		/*Interval delay between two commands*/
		_delay_ms(CMD_INTERVAL_DELAY_MS);
		
		/*Command controls display power on and off and the cursor settings*/
		LCD_sendCommand(DISPLAY_ON_OFF_CMD);
		
		/*Interval delay between two commands*/
		_delay_ms(CMD_INTERVAL_DELAY_MS);
		
		/*Clearing the display*/
		LCD_sendCommand(DISPLAY_CLEAR_CMD);
		
		/*Delay after clearing the display*/
		_delay_ms(INIT_CLEAR_DELAY_MS);
		
		/*Setting the LCD mode with no shifting*/
		LCD_sendCommand(ENTRY_MODE_SET_CMD);
	}
	#endif
	
	return err_var;
}

EnmLCDError_t LCD_sendCommand(uint8_t au8_cmd)
{
	/*Variable used for LCD error indication*/
	EnmLCDError_t err_var = OPERATION_SUCCESS;

	/*Setting LCD to command and write modes*/
	DIO_Write(LCD_CTRL_PORT , LCD_RS_PIN , RS_CMD_MODE);
	DIO_Write(LCD_CTRL_PORT , LCD_RW_PIN , RW_WRITE_MODE);
	
	#if (LCD_DATA_MODE == DATA_8BIT_MODE)
	{
		/*Setting LCD command to data pins*/
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN0 , (HIGH & GET_BIT(au8_cmd , BIT0)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN1 , (HIGH & GET_BIT(au8_cmd , BIT1)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN2 , (HIGH & GET_BIT(au8_cmd , BIT2)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN3 , (HIGH & GET_BIT(au8_cmd , BIT3)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN4 , (HIGH & GET_BIT(au8_cmd , BIT4)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN5 , (HIGH & GET_BIT(au8_cmd , BIT5)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN6 , (HIGH & GET_BIT(au8_cmd , BIT6)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN7 , (HIGH & GET_BIT(au8_cmd , BIT7)));
		
		/*Rising enable pin to high so LCD can read coming data*/
		DIO_Write(LCD_CTRL_PORT , LCD_EN_PIN , HIGH);
		
		/*Waiting the data to be written*/
		_delay_us(DATA_LATCHING_DELAY_US);

		/*Setting enable pin to low so that LCD can write the received data*/		
		DIO_Write(LCD_CTRL_PORT , LCD_EN_PIN , LOW);	
	}		
	#else
	{
		/*Writing the highest 4BITs*/
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN4 , (GET_BIT(au8_cmd , BIT4)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN5 , (GET_BIT(au8_cmd , BIT5)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN6 , (GET_BIT(au8_cmd , BIT6)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN7 , (GET_BIT(au8_cmd , BIT7)));

		/*Rising enable pin to high so LCD can read coming data*/
		DIO_Write(LCD_CTRL_PORT , LCD_EN_PIN , HIGH);
				
		/*Waiting the data to be written*/
		_delay_us(DATA_LATCHING_DELAY_US);
		
		/*Setting enable pin to low so that LCD can write the received data*/
		DIO_Write(LCD_CTRL_PORT , LCD_EN_PIN , LOW);	
		
		/*Writing the lowest 4BITs*/
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN4 , (GET_BIT(au8_cmd , BIT0)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN5 , (GET_BIT(au8_cmd , BIT1)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN6 , (GET_BIT(au8_cmd , BIT2)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN7 , (GET_BIT(au8_cmd , BIT3)));
		
		/*Rising enable pin to high so LCD can read coming data*/
		DIO_Write(LCD_CTRL_PORT , LCD_EN_PIN , HIGH);
		
		/*Waiting the data to be written*/
		_delay_us(DATA_LATCHING_DELAY_US);
		
		/*Setting enable pin to low so that LCD can write the received data*/
		DIO_Write(LCD_CTRL_PORT , LCD_EN_PIN , LOW);		
	}	
	#endif
	
	return err_var;	
}

EnmLCDError_t LCD_displayChar(uint8_t au8_data)
{
	/*Variable used for LCD error indication*/
	EnmLCDError_t err_var = OPERATION_SUCCESS;

	/*Setting LCD to data and write modes*/
	DIO_Write(LCD_CTRL_PORT , LCD_RS_PIN , RS_DATA_MODE);
	DIO_Write(LCD_CTRL_PORT , LCD_RW_PIN , RW_WRITE_MODE);
	
	#if (LCD_DATA_MODE == DATA_8BIT_MODE)
	{
		/*Setting LCD command to data pins*/
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN0 , (HIGH & GET_BIT(au8_data , BIT0)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN1 , (HIGH & GET_BIT(au8_data , BIT1)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN2 , (HIGH & GET_BIT(au8_data , BIT2)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN3 , (HIGH & GET_BIT(au8_data , BIT3)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN4 , (HIGH & GET_BIT(au8_data , BIT4)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN5 , (HIGH & GET_BIT(au8_data , BIT5)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN6 , (HIGH & GET_BIT(au8_data , BIT6)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN7 , (HIGH & GET_BIT(au8_data , BIT7)));
		
		/*Rising enable pin to high so LCD can read coming data*/
		DIO_Write(LCD_CTRL_PORT , LCD_EN_PIN , HIGH);
		
		/*Waiting the data to be written*/
		_delay_us(DATA_LATCHING_DELAY_US);
		
		/*Setting enable pin to low so that LCD can write the received data*/		
		DIO_Write(LCD_CTRL_PORT , LCD_EN_PIN , LOW);
	}
	#else
	{
		/*Writing the highest 4BITs*/
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN4 , (GET_BIT(au8_data , BIT4)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN5 , (GET_BIT(au8_data , BIT5)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN6 , (GET_BIT(au8_data , BIT6)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN7 , (GET_BIT(au8_data , BIT7)));
		
		/*Rising enable pin to high so LCD can read coming data*/
		DIO_Write(LCD_CTRL_PORT , LCD_EN_PIN , HIGH);
		
		/*Waiting the data to be written*/
		_delay_us(DATA_LATCHING_DELAY_US);

		/*Setting enable pin to low so that LCD can write the received data*/		
		DIO_Write(LCD_CTRL_PORT , LCD_EN_PIN , LOW);
						
		/*Writing the lowest 4BITs*/
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN4 , (GET_BIT(au8_data , BIT0)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN5 , (GET_BIT(au8_data , BIT1)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN6 , (GET_BIT(au8_data , BIT2)));
		DIO_Write(LCD_DATA_PORT , LCD_DATA_PIN7 , (GET_BIT(au8_data , BIT3)));	
		
		/*Rising enable pin to high so LCD can read coming data*/
		DIO_Write(LCD_CTRL_PORT , LCD_EN_PIN , HIGH);
		
		/*Waiting the data to be written*/
		_delay_us(DATA_LATCHING_DELAY_US);
		
		/*Setting enable pin to low so that LCD can write the received data*/		
		DIO_Write(LCD_CTRL_PORT , LCD_EN_PIN , LOW);			
	}
	
	#endif	
	
	return err_var;	
}

EnmLCDError_t LCD_displayString(uint8_t* pu8_string)
{
	/*Variable used for LCD error indication*/
	EnmLCDError_t err_var = OPERATION_SUCCESS;
		
	/*Validating the sent string contains NULL or not*/
	if(pu8_string == NULL)
	{
		err_var = NULL_PTR_ERROR;
	}
	else
	{
		/*Sending string characters except the NULL character*/
		while(*pu8_string != '\0')
		{
			LCD_displayChar(*pu8_string);
			pu8_string++;
		}
	}
	return err_var;
}


EnmLCDError_t LCD_gotoRowColumn(uint8_t au8_row , uint8_t au8_col)
{
	/*Variable used for LCD error indication*/
	EnmLCDError_t err_var = OPERATION_SUCCESS;
	
	/*Selecting which row to write data in*/
	switch(au8_row)
	{
		case ROW_0:
			/*Go to specified column in the row*/
			LCD_sendCommand(FIRST_LINE_CMD | au8_col);			
			break;
			
		case ROW_1:
			/*Go to specified column in the row*/
			LCD_sendCommand(SECOND_LINE_CMD | au8_col);
			break;	
	}
	
	return err_var;
}

EnmLCDError_t LCD_displayStringRowColumn(uint8_t* pu8_string , uint8_t au8_row , uint8_t au8_col)
{
	/*Variable used for LCD error indication*/
	EnmLCDError_t err_var = OPERATION_SUCCESS;

	/*Validating the sent string contains NULL or not*/
	if(pu8_string == NULL)
	{
		err_var = NULL_PTR_ERROR;
	}
	else
	{
		/*Selecting which row to write data in*/
		switch(au8_row)
		{
			case ROW_0:
			/*Go to specified column in the row*/
			LCD_sendCommand(FIRST_LINE_CMD | au8_col);
			break;
			
			case ROW_1:
			/*Go to specified column in the row*/
			LCD_sendCommand(SECOND_LINE_CMD | au8_col);
			break;
		}
	
		/*Sending string characters except the NULL character*/
		while(*pu8_string != '\0')
		{
			LCD_displayChar(*pu8_string);
			pu8_string++;
		}
	}
	
	return err_var;	
}
EnmLCDError_t LCD_clear(void)
{
	/*Variable used for LCD error indication*/
	EnmLCDError_t err_var = OPERATION_SUCCESS;
	
	/*Clearing the display*/
	LCD_sendCommand(DISPLAY_CLEAR_CMD);
	_delay_ms(INIT_CLEAR_DELAY_MS);	
	return err_var;	
}
