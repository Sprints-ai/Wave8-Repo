#ifndef LCD_H_
#define LCD_H_

/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#define F_CPU 16000000UL
#include "LCD_config.h"






/********************************************************************************
 * 								Functions Prototypes							*
 ********************************************************************************/

/*
 * Description : A Function to Initialize the LCD Driver.
 */
void LCD_init(void);

/*
 * Description : A Function to send a Command.
 */
void LCD_sendCommand(uint8_t command);

/*
 * Description : A Function to write data (display character).
 */
void LCD_displayCharacter(uint8_t data);

/*
 * Description : A Function to display a string.
 */
void LCD_displayString(const sint8_t *str);

/*
 * Description : A Function to move the cursor to an exact spot.
 */
void LCD_goToRowColumn(uint8_t row, uint8_t col);

/*
 * Description : A Function to move the cursor to an exact spot and display a string at the spot.
 */
void LCD_displayStringRowColumn(uint8_t row, uint8_t col, const sint8_t* str);

/*
 * Description : A Function to display an integer number.
 */
void LCD_displayInteger(uint8_t num);

/*
 * Description : A Function to Clear the LCD Screen.
 */
void LCD_clearScreen(void);

#endif
