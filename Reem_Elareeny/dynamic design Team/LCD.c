/*
 * LCD.c
 *
 * Created: 3/12/2020 2:44:59 PM
 *  Author: Reem el-Areeny
 */ 
 


#include "LCD.h"

#define COMMAND	LOW
#define DATA		HIGH

#define WRITE		LOW
#define READ		HIGH

#define F_CPU 16000000ul
#include <util/delay.h>

static void LCD_writeCMD (uint8_t cmd);


uint8_t LCD_isInitialized = FALSE;


uint8_t c = 'R';


ERROR_STATUS LCD_init(){
	ERROR_STATUS ERR = /*ERROR_LCD_MODULE*/ + E_OK;
	if(!LCD_isInitialized){
		LCD_PORT_DIR = OUTPUT;
			LCD_writeCMD(0x02); /* to initialize LCD in 4-bit mode.*/
			_delay_ms(1);
 			LCD_writeCMD(0x28); /* Initialization of 16X2 LCD in 4bit mode */
			_delay_ms(1);
			LCD_writeCMD(0x28); /* Initialization of 16X2 LCD in 4bit mode */
			_delay_ms(1);
			LCD_writeCMD(0x0F); /* Display ON Cursor OFF */
			_delay_ms(1);
			LCD_writeCMD(0x06); /* Entry Mode, Auto Increment cursor */
			_delay_ms(1);
			LCD_writeCMD(0x01); /* clear display */
			_delay_ms(1);
			LCD_writeCMD(0x80); /* cursor at first position */
			_delay_ms(1);
			LCD_isInitialized = TRUE;
	}else{
		ERR = /*ERROR_LCD_MODULE*/ + ERROR_MODULE_ALREADY_INITIALIZED;
	}
	return ERR;
}

void static LCD_writeCMD(uint8_t cmd){
		LCD_DATA_PORT = cmd & 0xF0;
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
		DIO_Write(LCD_PORT,LCD_REGISTER_SELECT_PIN,COMMAND);
		DIO_Write(LCD_PORT,LCD_READ_WRITE_PIN,WRITE);
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,LOW);
 		/*_delay_ms(1);*/
		LCD_DATA_PORT = (cmd << 4) & 0xF0;
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
		DIO_Write(LCD_PORT,LCD_REGISTER_SELECT_PIN,COMMAND);
		DIO_Write(LCD_PORT,LCD_READ_WRITE_PIN,WRITE);
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,LOW);
}

ERROR_STATUS LCD_writeChar(uint8_t character)
{
	ERROR_STATUS ERR = /*ERROR_LCD_MODULE*/ + E_OK;
	if(LCD_isInitialized)
	{
		LCD_DATA_PORT = character & 0xF0;
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
		DIO_Write(LCD_PORT,LCD_REGISTER_SELECT_PIN,DATA);
		DIO_Write(LCD_PORT,LCD_READ_WRITE_PIN,WRITE);
		//_delay_ms(1);
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,LOW);
		//_delay_ms(1);
		LCD_DATA_PORT = (character << 4) & 0xF0;
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
		DIO_Write(LCD_PORT,LCD_REGISTER_SELECT_PIN,DATA);
		DIO_Write(LCD_PORT,LCD_READ_WRITE_PIN,WRITE);
		//_delay_ms(1);
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,LOW);
		_delay_ms(1);
	}
	else
	{
		ERR = /*ERROR_LCD_MODULE +*/ ERROR_MODULE_NOT_INITIALIZED;
	}
	return ERR;
}




ERROR_STATUS LCD_writeGlobalChar()
{
	ERROR_STATUS ERR = /*ERROR_LCD_MODULE +*/ E_OK;
	if(LCD_isInitialized)
	{
		LCD_DATA_PORT = c & 0xF0;
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
		DIO_Write(LCD_PORT,LCD_REGISTER_SELECT_PIN,DATA);
		DIO_Write(LCD_PORT,LCD_READ_WRITE_PIN,WRITE);
		//_delay_ms(1);
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,LOW);
		//_delay_ms(1);
		LCD_DATA_PORT = (c << 4) & 0xF0;
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
		DIO_Write(LCD_PORT,LCD_REGISTER_SELECT_PIN,DATA);
		DIO_Write(LCD_PORT,LCD_READ_WRITE_PIN,WRITE);
		//_delay_ms(1);
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,LOW);
		//_delay_ms(1);
	}
	else
	{
		ERR = /*ERROR_LCD_MODULE +*/ ERROR_MODULE_NOT_INITIALIZED;
	}
	return ERR;
}

void LCD_Clear()
{
	LCD_writeCMD(0x01); /* clear display */
	_delay_ms(1);
	 
}