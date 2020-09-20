/*
 * LCD.h
 *
 * Created: 3/15/2020 11:16:34 AM
 *  Author: HAZEM
 */ 

/*- GARDIAN -----------------------------------------------*/
#ifndef LCD_H_
#define LCD_H_
/*- INCLUDES -----------------------------------------------*/
#include "LCDconfig.h"

/*- CONSTANTS ----------------------------------------------*/


/*- PRIMITIVE TYPES ----------------------------------------*/

typedef   sint8_t   ENMULCDERROR;
typedef   uint8_t *    string8_t;

/*- FUNCTION DECLARATIONS ----------------------------------*/
ENMULCDERROR  LCD_init(void);

ENMULCDERROR  LCD_displayChar(uint8_t u8_char);

ENMULCDERROR  LCD_displayString(string8_t au8_char);

ENMULCDERROR  LCD_sendCommand(uint8_t u8_command);

ENMULCDERROR  LCD_displayStringRowcolum(string8_t au8_char,uint8_t u8_posx,uint8_t u8_posy);

ENMULCDERROR  LCD_gotorowcolumn(uint8_t u8_posx,uint8_t u8_posy);

ENMULCDERROR  LCD_Clear(void);

ENMULCDERROR  LCD_Dinit(void);






















#endif /* LCD_H_ */