/*
 * LCD.h
 *
 * Created: 3/12/2020 2:45:13 PM
 *  Author: Reem el-Areeny
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "LCD_Config.h"
#include "std_types.h"
#include "DIO.h"

extern void LCD_init();
extern void LCD_writeChar(uint8_t character);
extern void LCD_writeString();
extern void LCD_writeGlobalChar();
#endif /* LCD_H_ */