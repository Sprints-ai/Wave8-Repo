/*
 ============================================================================
 Name        : LCD.c
 Author      : Muhammed Gamal
 Description : This File Includes The Functions Implementation Of The LCD Driver
 ============================================================================
 */

#include "../../MCAL/gpio.h"

#include "LCD.h"

#define START 0
#define CLEAR 0
#define FLAG_HIGH 1
#define FLAG_LOW 0
#define UPPER_NIBBLE_MASK 0xF0
#define LOWER_NIBBLE_MASK 0x0F
#define CLEAR_BIT(regis,bit) (regis &=~(1<<bit) )
#define SET_BIT(regis,bit) (regis |=(1<<bit) )

uint8_t gu8_LCDInit_CompleteFlag;
uint8_t gu8_SendCommand_CompleteFlag;
uint8_t gu8_SendChar_CompleteFlag;
uint8_t gu8_String_CompleteFlag;
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void LCD_init(void)
{
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW); /* Configure the control pins(E,RS,RW) as output pins */
	LCD_DATA_PORT_DIR |= 0xF0; /* Configure the highest 4 bits of the data port as output pins */

	LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
  _delay_us(50);

	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
	  _delay_us(50);

	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	  _delay_us(50);

	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
	  _delay_us(50);

	gu8_LCDInit_CompleteFlag=0;
	gu8_SendCommand_CompleteFlag=0;
	gu8_SendChar_CompleteFlag=0;
	gu8_String_CompleteFlag=0;
}

void LCD_sendCommand(uint8_t command)
{
	/*this function contains 12us delay*/

	CLEAR_BIT(LCD_CTRL_PORT,RS); /* Instruction Mode RS=0 */
	CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	//_delay_us(1); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	//_delay_us(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);

	_delay_us(3); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_us(3); /* delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_us(3);/* delay for processing Tpw - Tdws = 190ns */

	/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);

	_delay_us(3); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	//_delay_us(1); /* delay for processing Th = 13ns */
	gu8_SendCommand_CompleteFlag=1;
}

void LCD_displayCharacter(uint8_t data)
{
	/*
	 * this function contains 15us delay
	 * the first call of this function after call LCD_sendcommand function
	 * will take 800 additional us delay
	 * */

	if(gu8_SendCommand_CompleteFlag==1)
	{
		gu8_SendCommand_CompleteFlag=0;
		_delay_us(800);
	}
	SET_BIT(LCD_CTRL_PORT,RS); /* Data Mode RS=1 */
	CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the highest 4 bits of the required data to the data bus D4 --> D7 */
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);


	_delay_ms(3); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_ms(3); /* delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_ms(3); /* delay for processing Tpw - Tdws = 190ns */

	/* out the lowest 4 bits of the required data to the data bus D4 --> D7 */
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);

	_delay_ms(3); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
}

void LCD_displayString(const uint8_t *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

void LCD_goToRowColumn(uint8_t row,uint8_t col)
{
	uint8_t Address;

	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
	}
	/* to write to a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const uint8_t *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display
}

