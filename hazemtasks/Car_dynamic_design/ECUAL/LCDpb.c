/*
 * LCDpb.c
 *
 * Created: 3/15/2020 11:16:58 AM
 *  Author: hazem
 */ 

#include "LCDconfig.h"

DIO_Cfg_s  gstr_lcddataconfig={LCD_DATA_PORT,LCD_DATA_PINS,OUTPUT};

DIO_Cfg_s  gstr_lcdRSconfig={LCD_RS_PORT,LCD_RS_PIN,OUTPUT};

DIO_Cfg_s  gstr_lcdRWconfig={LCD_RW_PORT,LCD_RW_PIN,OUTPUT};
	
DIO_Cfg_s  gstr_lcdEnconfig={LCD_EN_PORT,LCD_EN_PIN,OUTPUT};		
	
uint8_t    gu8_lcdmode=LCD_FOUR_BIT;	