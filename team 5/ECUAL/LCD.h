/*
 * LCD.h
 *
 * Created: 3/15/2020 11:50:03 AM
 *  Author: MENNA
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../Service/std_types.h"

#define LCD_SECOND_ROW 1
#define LCD_MAX_WIDTH 16


extern uint8_t init_done ;
extern uint8_t sendStr_done ;

ERROR_STATUS LCD_init(void) ;

ERROR_STATUS LCD_sendCommand(uint8_t command) ;

ERROR_STATUS LCD_displayChar(uint8_t data) ;

ERROR_STATUS LCD_displayString(sint8_t * str_data) ;

ERROR_STATUS LCD_displayStringRowColumn() ;

ERROR_STATUS LCD_clear() ;

ERROR_STATUS LCD_gotoRowColumn(uint8_t row , uint8_t col) ;

ERROR_STATUS LCD_WriteData(uint8_t DataByte);

ERROR_STATUS LCD_displayInteger(uint16_t IntegerNumber);


#endif /* LCD_H_ */
