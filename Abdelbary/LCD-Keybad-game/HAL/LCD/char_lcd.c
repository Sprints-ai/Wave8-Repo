//*****************************************************************************
//
// File Name	: 'lcd_lib.c'
// Title		: 4-bit LCd interface
// Editor		: MahmoudAbdelbary
// Date			: Mar 16 2019
// Target MCU	: Atmel AVR series
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
#include "char_lcd.h"
#include "softwareDelay.h"
#include <stdlib.h>
#include "../../MCAL/DIO/DIO.h"
/*lcd states*/
#define LCD_IDLE				0
#define LCD_INIT_CMD0			1
#define LCD_INIT_CMD1			2
#define LCD_INIT_CMD2			3
#define LCD_INIT_CMD3			4
#define LCD_INIT_CMD4			5
#define LCD_INIT_CMD5			6
#define LCD_INIT_CMD6			7
#define LCD_INIT_FIN			8
#define LCD_READY				9
#define LCD_POSITION_UPDATE		10
#define LCD_CLEAR				11

#define CHANGE_NIBBEL_POSITION	4
#define SHIFT_MULTIPLY_BY_TWO	1
#define ASCII_ZERO				'0'
#define ASSCI_NULL				'\0'
#define FIRST_ROW				0
#define SECON_ROW				1
#define THIRD_ROW				2
#define FOURTH_ROW				3
#define BASE_TEN				10
#define BASE_MIN				2
#define BASE_MAX				32
#define FOUR_BIT_INIT2_CMD		0X33
#define FOUR_BIT_INIT3_CMD		0X32
static uint8_t row = 0;
static uint8_t colum = 0;

#define FIRST_ROW			0
#define SECOND_RAW			1
#define LCD_MAX_CLUM		16/*LCD END OF LINE*/
#define LCD_MAX_RAW			2/*LCD END OF ROWS*/

static uint8_t gu8_lcdBuffer[LCD_ROWS][LCD_COLUMS];
static uint8_t gu8_lcdState;
static uint8_t gu8_moduleInitFlage = FALSE; /*I CANT INIT THIS IN THE INIT FUNCTION AS IT HAS TO CHECK ITS VALUE FOR VERFICATION*/


ERROR_STATUS LCD_EN_pulse(void){
	ERROR_STATUS u8_funStatus = OK;
	DIO_Write(LCD_EN_PORT, LCD_EN_PIN, HIGH);
	DIO_Write(LCD_EN_PORT, LCD_EN_PIN, LOW);
	return u8_funStatus;
}

ERROR_STATUS LCD_config_pins(void){

	ERROR_STATUS u8_funStatus = OK;
	/* set LCD pins as outputs */
	gpioPinDirection(LCD_RS_PORT, LCD_RS_PIN, OUTPUT);
	gpioPinDirection(LCD_RW_PORT, LCD_RW_PIN, OUTPUT);
	gpioPinDirection(LCD_EN_PORT, LCD_EN_PIN, OUTPUT);

	gpioPinDirection(LCD_D4_PORT, LCD_D4_PIN, OUTPUT);
	gpioPinDirection(LCD_D5_PORT, LCD_D5_PIN, OUTPUT);
	gpioPinDirection(LCD_D6_PORT, LCD_D6_PIN, OUTPUT);
	gpioPinDirection(LCD_D7_PORT, LCD_D7_PIN, OUTPUT);
	
	return u8_funStatus;
}

ERROR_STATUS LCD_send_nibble(uint8_t data)
{
	ERROR_STATUS s16_funStatus = OK;
	uint8_t mask = ONE;
	data >>= CHANGE_NIBBEL_POSITION;
	if(data&mask)
		DIO_Write(LCD_D4_PORT, LCD_D4_PIN, HIGH);
	else
		DIO_Write(LCD_D4_PORT, LCD_D4_PIN, LOW);

	mask <<= SHIFT_MULTIPLY_BY_TWO;
	if(data&mask)
		DIO_Write(LCD_D5_PORT, LCD_D5_PIN, HIGH);
	else
		DIO_Write(LCD_D5_PORT, LCD_D5_PIN, LOW);

	mask <<= SHIFT_MULTIPLY_BY_TWO;
	if(data&mask)
		DIO_Write(LCD_D6_PORT, LCD_D6_PIN, HIGH);
	else
		DIO_Write(LCD_D6_PORT, LCD_D6_PIN, LOW);

	mask <<= SHIFT_MULTIPLY_BY_TWO;
	if(data&mask)
		DIO_Write(LCD_D7_PORT, LCD_D7_PIN, HIGH);
	else
		DIO_Write(LCD_D7_PORT, LCD_D7_PIN, LOW);
		
		return s16_funStatus;
}

ERROR_STATUS LCD_send_char(uint8_t data)		//Sends Char to LCD
{
	ERROR_STATUS s16_funStatus = OK;
	DIO_Write(LCD_RS_PORT, LCD_RS_PIN, HIGH);

	LCD_send_nibble(data); // Higher nibble first
	LCD_EN_pulse();

	LCD_send_nibble(data<<CHANGE_NIBBEL_POSITION);
	LCD_EN_pulse();
	return s16_funStatus;
}
ERROR_STATUS LCD_send_command(uint8_t data)	//Sends Command to LCD
{
	ERROR_STATUS s16_funStatus = OK;
	DIO_Write(LCD_RS_PORT, LCD_RS_PIN, LOW);

	LCD_send_nibble(data); // Higher nibble first
	LCD_EN_pulse();
	LCD_send_nibble(data<<CHANGE_NIBBEL_POSITION);
	LCD_EN_pulse();
	return s16_funStatus;
}

ERROR_STATUS LCD_init(void)//Initializes LCD
{
	ERROR_STATUS s16_funStatus = OK;
	if (s16_funStatus == TRUE)/*MODULE ALREADY INITALIZED*/
	{
		s16_funStatus = LCD_MODULE_ERR + MULTIPLE_INITALIZATION;
	}
	else
	{
		/*
		*	1-make a static local state machine  to excite 6 command one every entrance
		*	2-after last init command set global state variable to STATE_READY
		*	3-always check for invalic state
		*
		*/
		static uint8_t u8_LCD_initState = LCD_INIT_CMD0;
		switch(u8_LCD_initState)
		{
			case LCD_INIT_CMD0:
			LCD_config_pins();
				LCD_send_command(FOUR_BIT_INIT2_CMD);
			u8_LCD_initState = LCD_INIT_CMD1;
			break;
			case LCD_INIT_CMD1:
				LCD_send_command(FOUR_BIT_INIT3_CMD);
			u8_LCD_initState = LCD_INIT_CMD2;
			break;
			case LCD_INIT_CMD2:
				LCD_send_command(FOUR_BIT_INIT_CMD); // 4-bit
			u8_LCD_initState = LCD_INIT_CMD3;
			break;
			case LCD_INIT_CMD3:
				LCD_send_command(CURSOR_ON_CMD);
			u8_LCD_initState = LCD_INIT_CMD4;
			break;
			case LCD_INIT_CMD4:
				LCD_send_command(LCD_CLEAR_CMD);
			u8_LCD_initState = LCD_INIT_CMD5;
			break;
			case LCD_INIT_CMD5:
				LCD_send_command(INCREMENT_CURSOR_CMD);
			u8_LCD_initState = LCD_INIT_CMD6;
			break;
			case LCD_INIT_CMD6:
				LCD_send_command(CURSOR_OFF); // Cursor of
				if(s16_funStatus == OK)
				{
					gu8_moduleInitFlage = TRUE;
				}
				gu8_lcdState = LCD_READY;
			break;
			default:
				s16_funStatus = LCD_MODULE_ERR + INVALID_STATE;
			break;
		}	
		
			
	}
	
	return s16_funStatus;
}

ERROR_STATUS LCD_clear(void)				//Clears LCD
{
	ERROR_STATUS s16_funStatus = OK;
	if (gu8_moduleInitFlage == FALSE)
	{
		s16_funStatus  = LCD_MODULE_ERR + MODULE_NOT_INITALIZED;
	}
	else
	{
		/*after clearing go to postion zero and zero and go to state update position*/
		LCD_send_command(LCD_CLEAR_CMD);
		row = ZERO;
		colum = ZERO;
		gu8_lcdState = LCD_POSITION_UPDATE;
	}
	
	return s16_funStatus;
}


ERROR_STATUS LCD_send_string(uint8_t* data)	//Outputs string to LCD
{
	ERROR_STATUS s16_funStatus = OK;
	if (gu8_moduleInitFlage == FALSE)
	{
		s16_funStatus  = LCD_MODULE_ERR + MODULE_NOT_INITALIZED;
	}
	else
	{
		while(*data){
			LCD_send_char(*data++);
		}
	}
	
	return s16_funStatus;
}

ERROR_STATUS LCD_goto_xy(uint8_t row, uint8_t colum)	//Cursor to X Y position
{
	ERROR_STATUS s16_funStatus = OK;
	if (gu8_moduleInitFlage == FALSE)
	{
		s16_funStatus  = LCD_MODULE_ERR + MODULE_NOT_INITALIZED;
	}
	else
	{
		uint8_t DDRAMAddr;
		// remap lines into proper order
		switch(row)
		{
			case FIRST_ROW : DDRAMAddr = LCD_LINE0_DDRAMADDR+colum; break;
			case SECON_ROW : DDRAMAddr = LCD_LINE1_DDRAMADDR+colum; break;
			case THIRD_ROW : DDRAMAddr = LCD_LINE2_DDRAMADDR+colum; break;
			case FOURTH_ROW: DDRAMAddr = LCD_LINE3_DDRAMADDR+colum; break;
			default: DDRAMAddr = LCD_LINE0_DDRAMADDR+colum;
		}
		// set data address
		LCD_send_command(ONE<<LCD_DDRAM | DDRAMAddr);
	}
	
	return s16_funStatus;
}


ERROR_STATUS lcd_dispatcher(void)
{
	ERROR_STATUS s16_funStatus= OK;
	
	switch(gu8_lcdState)
	{
		case LCD_IDLE:
			LCD_init();
		break;
		case LCD_READY:
			LCD_send_char(gu8_lcdBuffer[row][colum]);
			++colum;
			if (colum == LCD_MAX_CLUM)
			{
				/*go to first culm in next line*/
				colum = ZERO;
				++row;
				/*if line > max lcd lines zero line*/
				if (row == LCD_MAX_RAW)
					row = ZERO;
				/*change state to update curser*/
				gu8_lcdState = LCD_POSITION_UPDATE;
			}
		break;
		
		case LCD_POSITION_UPDATE:
			LCD_goto_xy(row,colum);
			gu8_lcdState = LCD_READY;
		break;
		default:
			s16_funStatus = LCD_MODULE_ERR + INVALID_STATE;
		break;
	}	
	return s16_funStatus;
}
/*---Modification----------------------------------------------------------------------------------------------*/

//function to swap two numbers
void swap(uint8_t *x, uint8_t *y) {
	uint8_t t = *x; *x = *y; *y = t;
}

// function to reverse buffer[i..j]
uint8_t* reverse(uint8_t *buffer, uint32_t i, uint32_t j)
{
	while (i < j)
	swap(&buffer[i++], &buffer[j--]);

	return buffer;
}

// Iterative function to implement itoa() function in C
uint8_t* itoa_(uint32_t value, uint8_t* buffer, uint32_t base)
{
	// invalid input
	if (base < BASE_MIN || base > BASE_MAX)
	return buffer;

	// consider absolute value of number
	uint8_t u8_abdValue = abs(value);

	uint8_t u8_counter = ZERO;
	while (u8_abdValue)
	{
		uint8_t r = u8_abdValue % base;

		if (r >= BASE_TEN)
		buffer[u8_counter++] = 'a' + (r - BASE_TEN);
		else
		buffer[u8_counter++] = ASCII_ZERO + r;

		u8_abdValue = u8_abdValue / base;
	}

	// if number is 0
	if (u8_counter == ZERO)
	buffer[u8_counter++] = ASCII_ZERO;

	// If base is 10 and value is negative, the resulting string
	// is preceded with a minus sign (-)
	// With any other base, value is always considered unsigned
	if (value < ZERO && base == BASE_TEN)
	buffer[u8_counter++] = '-';

	buffer[u8_counter] = ASCII_ZERO; // null terminate string

	// reverse the string and return it
	return reverse(buffer, ZERO, u8_counter - ONE);
}

ERROR_STATUS LCD_setNewBuffer(uint8_t * u8_firstRow,uint8_t * u8_secondRow)
{
	ERROR_STATUS s16_funStatus = OK;
	if (s16_funStatus == FALSE && 0)
	{
		s16_funStatus  = LCD_MODULE_ERR + MODULE_NOT_INITALIZED;
	}
	else
	{
		uint8_t u8_counter = ZERO ;
	
		/*
		*	1-set new data to buffer.
		*	2-clear LCD.
		*/
		while(u8_counter < LCD_MAX_CLUM)
		{
			gu8_lcdBuffer[FIRST_ROW][u8_counter] = u8_firstRow[u8_counter];
			gu8_lcdBuffer[SECOND_RAW][u8_counter] = u8_secondRow[u8_counter];
			u8_counter++;
		}
	}
	return s16_funStatus;
}
