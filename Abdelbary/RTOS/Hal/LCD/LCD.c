#include "LCD.h"


/********************************************************************************
 * 								Functions Definitions							*
 ********************************************************************************/

/*
 * Description : A Function to Initialize the LCD Driver.
 */
void LCD_init(void)
{
	LCD_CTRL_PORT_DIR |= (1 << E) | (1 << RS) | (1 << RW);
#if(DATA_BITS_MODE == 8)
	LCD_DATA_PORT_DIR = 0xFF;
	LCD_sendCommand(TWO_LINE_LCD_EIGHT_BIT_MODE);
#elif(DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_BITS
	LCD_DATA_PORT_DIR |= 0xF0;
#else
	LCD_DATA_PORT_DIR |= 0x0F;
#endif
	LCD_sendCommand(FOUR_BITS_DATA_MODE_ACTIVATED);
	LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE);
#endif
	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_COMMAND);
}

/*
 * Description : A Function to send a Command.
 */
void LCD_sendCommand(uint8_t command)
{
	CLEAR_BIT(LCD_CTRL_PORT, RS);
	CLEAR_BIT(LCD_CTRL_PORT, RW);
	_delay_us(10);
	SET_BIT(LCD_CTRL_PORT, E);
	_delay_us(10);
#if(DATA_BITS_MODE == 8)
	LCD_DATA_PORT = command;
#elif(DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_BITS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
#endif
	_delay_us(10);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	_delay_us(10);
	SET_BIT(LCD_CTRL_PORT, E);
	_delay_us(10);
#ifdef UPPER_PORT_BITS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
#endif
#endif
	_delay_us(10);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	_delay_us(10);
}

/*
 * Description : A Function to write data (display character).
 */
void LCD_displayCharacter(uint8_t data)
{
	SET_BIT(LCD_CTRL_PORT, RS);
	CLEAR_BIT(LCD_CTRL_PORT, RW);
	_delay_us(10);
	SET_BIT(LCD_CTRL_PORT, E);
	_delay_us(10);
#if(DATA_BITS_MODE == 8)
	LCD_DATA_PORT = data;
#elif(DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_BITS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
#endif
	_delay_us(10);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	_delay_us(10);
	SET_BIT(LCD_CTRL_PORT, E);
	_delay_us(10);
#ifdef UPPER_PORT_BITS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
#endif
#endif
	_delay_us(10);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	_delay_us(10);
}

/*
 * Description : A Function to display a string.
 */
void LCD_displayString(const sint8_t* str)
{
	uint8_t index=0;
	while((str[index]) != '\0')
	{
		LCD_displayCharacter(str[index]);
		index++;
		vTaskDelay(2);
	}
}

/*
 * Description : A Function to move the cursor to an exact spot.
 */
void LCD_goToRowColumn(uint8_t row, uint8_t col)
{
	uint8_t address;
	switch(row)
	{
	case 0 :
		address = col;
		break;
	case 1 :
		address = col + 0x40;
		break;
	case 2 :
		address = col + 0x10;
		break;
	case 3 :
		address = col + 0x50;
		break;
	}
	LCD_sendCommand(address | SET_CURSOR_LOCATION);
}

/*
 * Description : A Function to move the cursor to an exact spot and display a string at the spot.
 */
void LCD_displayStringRowColumn(uint8_t row, uint8_t col, const sint8_t* str)
{
	LCD_goToRowColumn(row, col);
	LCD_displayString(str);
}

/*
 * Description : A Function to display an integer number.
 */
void LCD_displayInteger(uint8_t num)
{
	uint8_t buff[12];
	uint8_t* ptr = &buff[11]; 				// char *ptr = (buff + 11); [] is another way of describing the dereferencing operator
	char N_flag = 0;
	if(num < 0)
	{
		N_flag = 1;
		num = -num;
	}
	*ptr = '\0';
	do{
	    *--ptr = (num % 10) + 48;
	    num /= 10;
	}while(num != 0);
	if(N_flag)
		*--ptr = '-';
	LCD_displayString(ptr);
}

/*
 * Description : A Function to Clear the LCD Screen.
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display
}
