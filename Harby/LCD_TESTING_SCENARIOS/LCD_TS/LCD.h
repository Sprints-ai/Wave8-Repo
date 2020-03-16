/********************************************************************************
 *																				*
 * Module : LCD																	*
 *																				*
 * File Name : LCD.h															*
 *																				*
 * Description : Header File for LCD Driver.									*
 *																				*
 * Author : Youssef Harby														*
 *																				*
 ********************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "../common_macros.h"
#include "../std_types.h"


/********************************************************************************
 * 								Preprocessor Macros								*
 ********************************************************************************/

/*
 * LCD Commands
 */
#define CLEAR_COMMAND					0x01
#define TWO_LINE_LCD_EIGHT_BIT_MODE 	0x38
#define FOUR_BITS_DATA_MODE_ACTIVATED 	0x02
#define TWO_LINE_LCD_FOUR_BIT_MODE 		0x28
#define CURSOR_OFF 						0x0C
#define CURSOR_ON 						0x0E
#define SET_CURSOR_LOCATION 			0x80

/*
 * Row, Column Macros
 */
#define ROW0		0x00
#define ROW1 		0x01
#define COLUMN0		0x00
#define COLUMN1		0x01
#define COLUMN2		0x02
#define COLUMN3		0x03
#define COLUMN4		0x04
#define COLUMN5		0x05
#define COLUMN6		0x06
#define COLUMN7		0x07
#define COLUMN8		0x08
#define COLUMN9		0x09
#define COLUMN10	0x0A
#define COLUMN11	0x0B
#define COLUMN12	0x0C
#define COLUMN13	0x0D
#define COLUMN14	0x0E
#define COLUMN15	0x0F

/********************************************************************************
 * 								Functions Prototypes							*
 ********************************************************************************/

/*
 * Description : A Function to Initialize the LCD Driver.
 */
extern ERROR_STATUS LCD_init(void);

/*
 * Description : A Function to send a Command.
 */
extern ERROR_STATUS LCD_sendCommand(uint8_t Command);


/*
 * Description : A Function to send a Command.
 */
extern ERROR_STATUS LCD_sendCommandWithOs(uint8_t Command);


extern void testDisplayCharacterOS(void);
extern void testSendCharacterOS(void);


/*
 * Description : A Function to write data (display character).
 */
extern ERROR_STATUS LCD_displayCharacter(uint8_t Data);

extern ERROR_STATUS LCD_displayCharacterWithOs(uint8_t Data);


/*
 * Description : A Function to display a string.
 */
extern ERROR_STATUS LCD_displayString(const sint8_t* StringPointer);

/*
 * Description : A Function to move the cursor to an exact spot.
 */
extern ERROR_STATUS LCD_goToRowColumn(uint8_t Row, uint8_t Column);

/*
 * Description : A Function to move the cursor to an exact spot and display a string at the spot.
 */
extern ERROR_STATUS LCD_displayStringRowColumn(uint8_t Row, uint8_t Column, const sint8_t* StringPointer);

/*
 * Description : A Function to display an integer number.
 */
extern ERROR_STATUS LCD_displayInteger(sint32_t IntegerNumber);

/*
 * Description : A Function to display an integer number.
 */
extern ERROR_STATUS LCD_displayIntegerRowColumn(uint8_t Row, uint8_t Column, sint32_t IntegerNumber);

/*
 * Description : A Function to Clear the LCD Screen.
 */
extern ERROR_STATUS LCD_clear(void);

#endif
