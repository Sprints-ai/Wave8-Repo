/*
 * LCDconfig.h
 *
 * Created: 3/15/2020 11:17:13 AM
 *  Author: hazem
 */ 

/*- GARDIAN ----------------------------------------------*/
#ifndef LCDCONFIG_H_
#define LCDCONFIG_H_
/*- INCLUDES ----------------------------------------------*/
#include "..\Mcal\DIO.h"
#include "..\Common\softwareDelay.h"

extern DIO_Cfg_s  gstr_lcddataconfig;
extern DIO_Cfg_s  gstr_lcdRSconfig;
extern DIO_Cfg_s  gstr_lcdRWconfig;
extern DIO_Cfg_s  gstr_lcdEnconfig;
extern uint8_t   gu8_lcdmode;
/*define MCU pin connected to LCD RS*/
#define LCD_RS_PIN	BIT1 	
#define LCD_RS_PORT	GPIOA
/*define MCU pin connected to LCD R/W*/
#define LCD_RW_PIN	BIT2 	
#define LCD_RW_PORT	GPIOA
/*define MCU pin connected to LCD E*/
#define LCD_EN_PIN	BIT3	
#define LCD_EN_PORT	GPIOA
/*define MCU pin connected to LCD DATA*/
#define  LCD_DATA_PINS  UPPER_NIBBLE
#define  LCD_DATA_PORT  GPIOA

#define LCD_D4_PIN	BIT4	//define MCU pin connected to LCD D4
#define LCD_D4_GPIO	GPIOA

#define LCD_D5_PIN	BIT5	//define MCU pin connected to LCD D5
#define LCD_D5_GPIO	GPIOA

#define LCD_D6_PIN	BIT6	//define MCU pin connected to LCD D6
#define LCD_D6_GPIO	GPIOA

#define LCD_D7_PIN	BIT7	//define MCU pin connected to LCD D7
#define LCD_D7_GPIO	GPIOA
/* LCD Commands definition */
#define LCD_CLEAR           	 0x01
#define LCD_RETRUN_HOME          0x02
#define LCD_DECREMENT_CURSOR     0x04
#define LCD_SHIFT_DISPLAY_RIGHT  0x05
#define LCD_INCREMENT_CURSOR     0x06
#define LCD_SHIFT_DISPLAY_LEFT   0x07
#define LCD_SHIFT_CURSOR_LEFT    0x10
#define LCD_SHIFT_CURSOR_RIGHT   0x14
#define LCD_FOUR_BIT             0x28
#define LCD_EIGHT_BIT            0x38
#define LCD_ST                   0x32
#define LCD_CURSOR_OFF           0x0C
#define LCD_CURSOR_ON            0x0E
#define LCD_LINE0		         0x00
#define LCD_LINE1	             0x40
#define LCD_DDRAM                  7

#endif /* LCDCONFIG_H_ */