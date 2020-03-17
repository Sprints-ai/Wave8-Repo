/*
 * LCD_cfg.h
 *
 * Created: 3/13/2020 2:16:17 PM
 *  Author: A_ayman
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#include "../../MCAL/DIO/DIO.h"

#define LCD_PORT_DATA GPIOA
#define LCD_D4 BIT4
#define LCD_D5 BIT5
#define LCD_D6 BIT6
#define LCD_D7 BIT7

#define LCD_RS BIT1
#define LCD_RW BIT2

#define LCD_RS_PORT GPIOB
#define LCD_RW_PORT GPIOB
#define LCD_E_PORT  GPIOB
#define LCD_E       BIT3




#endif /* LCD_CFG_H_ */