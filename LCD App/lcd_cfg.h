/*
 * lcd_cfg.h
 *
 * Created: 3/15/2020 1:45:50 PM
 *  Author: Mohamed Ramadan
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/*********************************************
 *				Includes  					 *
 ********************************************/
#include "registers.h"
#include "std_types.h"
#include "DIO.h"
/*********************************************
 *				Defines  					 *
********************************************/
#define LCD_RS_PIN	0x02 		//define MCU pin connected to LCD RS
#define LCD_RS_PORT	GPIOA
	
#define LCD_RW_PIN	0x04 		//define MCU pin connected to LCD R/W
#define LCD_RW_PORT	GPIOA

#define LCD_EN_PIN	0x08		//define MCU pin connected to LCD E
#define LCD_EN_PORT	GPIOA

#define LCD_D4_PIN	0x10		//define MCU pin connected to LCD D4
#define LCD_D4_PORT	GPIOA

#define LCD_D5_PIN	0x20		//define MCU pin connected to LCD D5
#define LCD_D5_PORT	GPIOA

#define LCD_D6_PIN	0x40		//define MCU pin connected to LCD D6
#define LCD_D6_PORT	GPIOA

#define LCD_D7_PIN	0x80		//define MCU pin connected to LCD D7
#define LCD_D7_PORT	GPIOA

#define LCD_PORT	PORTA_DATA		
/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/
DIO_Cfg_s LCD_RS_Cfg_S={LCD_RS_PORT,LCD_RS_PIN,OUTPUT};
DIO_Cfg_s LCD_RW_Cfg_S={LCD_RW_PORT,LCD_RW_PIN,OUTPUT};
DIO_Cfg_s LCD_EN_Cfg_S={LCD_EN_PORT,LCD_EN_PIN,OUTPUT};	
DIO_Cfg_s LCD_D4_Cfg_S={LCD_D4_PORT,LCD_D4_PIN,OUTPUT};	
DIO_Cfg_s LCD_D5_Cfg_S={LCD_D5_PORT,LCD_D5_PIN,OUTPUT};
DIO_Cfg_s LCD_D6_Cfg_S={LCD_D6_PORT,LCD_D6_PIN,OUTPUT};	
DIO_Cfg_s LCD_D7_Cfg_S={LCD_D7_PORT,LCD_D7_PIN,OUTPUT};
		
#endif /* LCD_CFG_H_ */