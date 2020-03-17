/*
 * LCD.h
 *
 * Created: 3/12/2020 11:31:12 AM
 *  Author: ema
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "LCD_Config.h"
#include "../MCAL/DIO.h"
#include "../Infrastructure/Errors.h"

#define LCD_OS		0
#define LCD_NORMAL	1

#define READY		0
#define UNLOCKED	1
#define LOCKED		2

#define lcd_Clear           (0x01)         /* replace all characters with ASCII 'space' */
#define lcd_Home            (0x02)         /* return cursor to first position on first line */
#define lcd_EntryMode       (0x06)         /* shift cursor from left to right on read/write */
#define lcd_DisplayOff      (0x08)         /* turn display off */
#define lcd_DisplayOn       (0x0E)         /* display on, cursor off, don't blink character */
#define lcd_FunctionReset   (0x30)         /* reset the LCD */
#define lcd_FunctionSet8bit (0x38)         /* 8-bit data, 2-line display, 5 x 7 font */
#define lcd_FunctionSet4bit (0x28)         /* 4-bit data, 2-line display, 5 x 7 font */
#define lcd_SetCursor       (0x80)         /* set cursor position */

ERROR_STATUS LCD_init (uint8_t OperationMode);

void LCD_Deinit (void);

ERROR_STATUS LCD_sendCommand(uint8_t uint8_tCmdCpy , uint8_t OperationMode);

ERROR_STATUS LCD_DisplayChar(uint8_t u8_DataCpy, uint8_t OperationMode);

void LCD_DisplayString (uint8_t* puint8_tStringCpy, uint8_t uint8_tIndex, uint8_t* pu8_Notification);

void LCD_displayStringRowColumn (uint8_t u8_Row , uint8_t u8_Column, uint8_t* puint8_tStringCpy, uint8_t uint8_tIndex, uint8_t* pu8_Notification);

void gotoRowColumn (uint8_t u8_Row,uint8_t u8_Column);
#endif /* LCD_H_ */