/*
 ============================================================================
 Name        : LCD.c
 Author      : Muhammed Gamal
 Description : This File Includes The Functions Implementation Of The LCD Driver
 ============================================================================
 */


#include "lcd.h"

#define START 0
#define CLEAR 0
#define FLAG_HIGH 1
#define FLAG_LOW 0
#define UPPER_NIBBLE_MASK 0xF0
#define LOWER_NIBBLE_MASK 0x0F

uint8_t gu8_LCDInit_CompleteFlag;
uint8_t gu8_SendCommand_CompleteFlag;
uint8_t gu8_SendChar_CompleteFlag;
uint8_t gu8_String_CompleteFlag;
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void LCD_init(void)
{
	static uint8_t u8_entry_count=CLEAR;
	if(u8_entry_count==START)
	{
		/*Initialize all global variables*/
		gu8_LCDInit_CompleteFlag=CLEAR;
		gu8_SendCommand_CompleteFlag=CLEAR;
		gu8_SendChar_CompleteFlag=CLEAR;
		gu8_String_CompleteFlag=CLEAR;

		LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW); /* Configure the control pins(E,RS,RW) as output pins */
		LCD_DATA_PORT_DIR |= UPPER_NIBBLE_MASK; /* Configure the highest 4 bits of the data port as output pins */
		LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
	}
	else if(u8_entry_count==1)
	{
		LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
	}
	else if(u8_entry_count==2)
	{
		LCD_sendCommand(CURSOR_OFF); /* cursor off */
	}
	else if(u8_entry_count==3)
	{
		LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
	}
	else if(u8_entry_count==4)
	{
		gu8_LCDInit_CompleteFlag=FLAG_HIGH;
	}
	if(gu8_SendCommand_CompleteFlag==FLAG_HIGH)
	{
		gu8_SendCommand_CompleteFlag=FLAG_LOW;
		u8_entry_count++;
	}
}

void LCD_sendCommand(uint8_t command)
{
	/*NOTE THAT:
	 * ALL The LCD Delays Has Been Removed Since It's Too Small
	 * And The SOS Tick Is 1ms
	 */
	static uint8_t u8_entry_count=CLEAR;
	if(u8_entry_count==START)
	{
		CLEAR_BIT(LCD_CTRL_PORT,RS); /* Instruction Mode RS=0 */
		CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	}
	else if(u8_entry_count==1)
	{
		SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	}
	else if(u8_entry_count==2)
	{
			/* out the highest 4 bits  */
			LCD_DATA_PORT = (LCD_DATA_PORT & LOWER_NIBBLE_MASK) | (command & UPPER_NIBBLE_MASK);
	}
	else if(u8_entry_count==3)
	{
		CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	}
	else if(u8_entry_count==4)
	{
		SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	}
	else if(u8_entry_count==5)
	{
		/* out the lowest 4 bits  */
		LCD_DATA_PORT = (LCD_DATA_PORT & LOWER_NIBBLE_MASK) | ((command & LOWER_NIBBLE_MASK) << 4);
	}
	else if(u8_entry_count==6)
	{
		CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	}
	else if(u8_entry_count==7)
	{

	}
	else if(u8_entry_count==8)
	{
		gu8_SendCommand_CompleteFlag=FLAG_HIGH;
		u8_entry_count=CLEAR;
	}

	u8_entry_count++;
}

void LCD_displayCharacter(uint8_t data)
{
	static uint8_t u8_entry_count=START;
	if(u8_entry_count==START)
	{
		SET_BIT(LCD_CTRL_PORT,RS);
		CLEAR_BIT(LCD_CTRL_PORT,RW);
	}
	else if(u8_entry_count==1)
	{
		SET_BIT(LCD_CTRL_PORT,E);
	}

	else if(u8_entry_count==2)
	{
		LCD_DATA_PORT = (LCD_DATA_PORT & LOWER_NIBBLE_MASK) | (data & UPPER_NIBBLE_MASK);
	}

	else if(u8_entry_count==3)
	{
		CLEAR_BIT(LCD_CTRL_PORT,E);
	}

	else if(u8_entry_count==3)
	{
		SET_BIT(LCD_CTRL_PORT,E);
	}

	else if(u8_entry_count==4)
	{
		/* out the lowest 4 bits  */
		LCD_DATA_PORT = (LCD_DATA_PORT & LOWER_NIBBLE_MASK) | ((data & LOWER_NIBBLE_MASK) << 4);
	}

	else if(u8_entry_count==5)
	{
		CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	}

	else if(u8_entry_count==7)
	{
		gu8_SendChar_CompleteFlag=FLAG_HIGH;
	}

	u8_entry_count++;
}

void LCD_displayString(const char *Str)
{
	static uint8_t i = START;
	if(Str[i] != '\0')
	{
		gu8_String_CompleteFlag=CLEAR;
		if(gu8_SendChar_CompleteFlag==FLAG_HIGH || i==START)
		{
			gu8_SendChar_CompleteFlag=FLAG_LOW;
			LCD_displayCharacter(Str[i]);
			i++;
		}
	}
	else
	{
		gu8_String_CompleteFlag=FLAG_HIGH;
	}
}

void LCD_goToRowColumn(uint8_t row,uint8_t col)
{
	uint8_t Address;

	/* calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
	 /* I need to apply the corresponding command 0b10000000+Address
	 * to write to a specific address in the LCD*/
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}


void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); /*clear display*/
}
