//*****************************************************************************
//
// File Name	: 'lcd_lib.c'
// Title		: 4-bit LCd interface
// Editor		: MahmoudAbdelbary
// Date			: Mar 16 2019
// Target MCU	: Atmel AVR series
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
#ifndef CHAR_LCD_H_
#define CHAR_LCD_H_

#include "../../Utilities/std_types.h"
#include "../../Utilities/regesters.h"
#include "../../Mcal/DIO/gpio.h"

#define LCD_COLUMS	16
#define LCD_ROWS	2

#define LCD_RS_PIN	0x02 	//define MCU pin connected to LCD RS
#define LCD_RS_PORT	GPIOA

#define LCD_RW_PIN	0x04 	//define MCU pin connected to LCD R/W
#define LCD_RW_PORT	GPIOA

#define LCD_EN_PIN	0x08	//define MCU pin connected to LCD E
#define LCD_EN_PORT	GPIOA

#define LCD_D4_PIN	0x10	//define MCU pin connected to LCD D4
#define LCD_D4_PORT	GPIOA

#define LCD_D5_PIN	0x20	//define MCU pin connected to LCD D5
#define LCD_D5_PORT	GPIOA

#define LCD_D6_PIN	0x40	//define MCU pin connected to LCD D6
#define LCD_D6_PORT	GPIOA

#define LCD_D7_PIN	0x80	//define MCU pin connected to LCD D7
#define LCD_D7_PORT	GPIOA

/* LCD Commands definition */
#define LCD_CLEAR_CMD           0x01
#define Return_home         0x02
#define Decrement_cursor    0x04
#define Shift_display_right 0x05
#define INCREMENT_CURSOR_CMD    0x06
#define Shift_display_left  0x07
#define Shift_cursor_left   0x10
#define Shift_cursor_right  0x14
#define FOUR_BIT_INIT_CMD            0x28
#define Eight_bit           0x38
#define CURSOR_OFF          0x0C
#define CURSOR_ON_CMD           0x0E

#define LCD_MODULE_ERR      -400
// cursor position to DDRAM mapping
#define LCD_DDRAM           7	//DB7: set DD RAM address
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54


/*lcd states*/
#define LCD_IDLE				0
#define LCD_INIT_CMD0			1
#define LCD_INIT_CMD1			2
#define LCD_INIT_CMD2			3
#define LCD_INIT_CMD3			4
#define LCD_INIT_CMD4			5
#define LCD_INIT_CMD5			6
#define LCD_INIT_CMD6			7
#define LCD_INIT_FIN			8
#define LCD_READY				9
#define LCD_POSITION_UPDATE		10
#define LCD_CLEAR				11


ERROR_STATUS lcd_dispatcher(void);
ERROR_STATUS LCD_EN_pulse(void);
ERROR_STATUS LCD_config_pins(void); // configure LCD pins.
ERROR_STATUS LCD_send_nibble(uint8_t data); // re-maps data bits to LCD Pins.
ERROR_STATUS LCD_send_char(uint8_t data);		//forms data ready to send to LCD
ERROR_STATUS LCD_send_command(uint8_t data);	//forms command ready to send to LCD
ERROR_STATUS LCD_init(void);			//Initializes LCD
ERROR_STATUS LCD_clear(void);				//Clears LCD
ERROR_STATUS LCD_send_string(uint8_t* data);	//Outputs string to LCD
ERROR_STATUS LCD_goto_xy(uint8_t x, uint8_t y);	//Cursor to X Y position
ERROR_STATUS LCD_setPosValue(uint8_t x, uint8_t y , uint8_t value);
ERROR_STATUS LCD_setFirstRowBuffer(uint8_t * u8_firstRow);
ERROR_STATUS LCD_setScndRowBuffer(uint8_t * u8_secondRow);
extern uint8_t gu8_UARTmoduleInitFlage;
/*---Modification--------------------------------------------------------------------------------------*/
// inline function to swap two numbers
//inline void swap(char *x, char *y);
// function to reverse buffer[i..j]
uint8_t* reverse(uint8_t *buffer, uint32_t i, uint32_t j);
// Iterative function to implement itoa() function in C
uint8_t* itoa_(uint32_t value, uint8_t* buffer, uint32_t base);
ERROR_STATUS LCD_setNewBuffer(uint8_t * u8_firstRow,uint8_t * u8_secondRow);
#endif // LCD_H_

