/*
 * LCD.h
 *
 * Created: 3/15/2020 11:50:03 AM
 *  Author: MENA
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include "LCD_cfg.h"

#define LCD_SECOND_ROW 1
#define LCD_MAX_WIDTH 16

ERROR_STATUS LCD_init(void) ;

ERROR_STATUS LCD_sendCommand(uint8_t command) ;

ERROR_STATUS LCD_displayChar(uint8_t data) ;

ERROR_STATUS LCD_displayString(uint8_t * str_data) ;

ERROR_STATUS LCD_displayStringRowColumn() ;

ERROR_STATUS LCD_clear() ;

ERROR_STATUS LCD_gotoRowColumn(uint8_t row , uint8_t col) ;

ERROR_STATUS LCD_WriteData(uint8_t DataByte);


#endif /* LCD_H_ */