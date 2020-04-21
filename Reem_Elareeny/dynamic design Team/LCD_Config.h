/*
 * LCD_Config.h
 *
 * Created: 3/12/2020 2:45:36 PM
 *  Author: Reem el-Areeny
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#define LCD_PORT GPIOA
#define LCD_DATA_PORT PORTA_DATA
#define LCD_PORT_DIR PORTA_DIR

#define LCD_REGISTER_SELECT_PIN BIT1
#define LCD_READ_WRITE_PIN BIT2
#define LCD_ENABLE_PIN BIT3
//#define LCD_DATA_PINS BIT4 | BIT5 | BIT6 | BIT7

#endif /* LCD_CONFIG_H_ */