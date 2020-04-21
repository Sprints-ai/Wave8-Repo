/*
 * LCD.h
 *
 * Created: 3/12/2020 2:45:13 PM
 *  Author: Reem el-Areeny
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "LCD_Config.h"
#include "../Infrastructure/std_types.h"
#include "../MCAL/DIO.h"

extern ERROR_STATUS LCD_init();
extern ERROR_STATUS LCD_writeChar(uint8_t character);
extern ERROR_STATUS LCD_writeString();
extern ERROR_STATUS LCD_writeGlobalChar();
extern void LCD_Clear();
#endif /* LCD_H_ */