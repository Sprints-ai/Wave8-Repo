#ifndef LCD_H_
#define LCD_H_

/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

//#define F_CPU 16000000UL
//#include "util/delay.h"
#include "common_macros.h"
#include "std_types.h"
#include "LCD_config.h"






/********************************************************************************
 * 								Functions Prototypes							*
 ********************************************************************************/

/*
 * Description : A Function to Initialize the LCD Driver.
 */
ERROR_STATUS LCD_init(void);

/*
 * Description : A Function to send a Command.
 */
ERROR_STATUS LCD_sendCommand(uint8 command);

/*
 * Description : A Function to write data (display character).
 */
ERROR_STATUS LCD_displayCharacter(uint8 data);

/*
 * Description : A Function to display a string.
 */
ERROR_STATUS LCD_displayString(const sint8 *str);

/*
 * Description : A Function to move the cursor to an exact spot.
 */
ERROR_STATUS LCD_goToRowColumn(uint8 row, uint8 col);

/*
 * Description : A Function to move the cursor to an exact spot and display a string at the spot.
 */
ERROR_STATUS LCD_displayStringRowColumn(uint8 row, uint8 col, const sint8* str);

/*
 * Description : A Function to display an integer number.
 */
ERROR_STATUS LCD_displayInteger(uint8 num);

/*
 * Description : A Function to Clear the LCD Screen.
 */
ERROR_STATUS LCD_clearScreen(void);

#endif
