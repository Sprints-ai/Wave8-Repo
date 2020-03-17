/*
 ============================================================================
 Name        : LCD.h
 Author      : Muhammed Gamal
 Description : LCD Header File
 ============================================================================
 */

#ifndef LCD_H_
#define LCD_H_

#include "../Common/std_types.h"
#include "../Common/common_macros.h"
#include "../MCAL/DIO.h"
#include "../Common/softwareDelay.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif

/* LCD HW Pins */
#define RS 4
#define RW 5
#define E  6
#define LCD_CTRL_PORT PORTD_DATA
#define LCD_CTRL_PORT_DIR PORTD_DIR
#define LCD_DATA_PORT PORTC_DATA
#define LCD_DATA_PORT_DIR PORTC_DIR

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80



/*******************************************************************************
 *                      Gloabal Variables                                  *
 *******************************************************************************/
extern uint8_t gu8_LCDInit_CompleteFlag;
extern uint8_t gu8_SendCommand_CompleteFlag;
extern uint8_t gu8_String_CompleteFlag;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_sendCommand(uint8_t command);
void LCD_displayCharacter(uint8_t data);
void LCD_displayString(const char *Str);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const char *Str);
void LCD_goToRowColumn(uint8_t row,uint8_t col);
void LCD_intgerToString(int data);

#endif
