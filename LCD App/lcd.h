/*
 * File Name	: 'lcd.h'
 * Title		: 4-bit LCd interface
 * Created: 3/15/2020 1:32:04 PM
 *  Author: Mohamed Ramadan
 */ 


#ifndef LCD_H_
#define LCD_H_
/*********************************************
 *				Includes  					 *
 ********************************************/
#include "lcd_cfg.h"
#include "util/delay.h"
/*******************************************
*											*
********************************************/
typedef sint8_t	EnmLCDError_t;
/*********************************************
 *				Defines  					 *
********************************************/
	
/**LCD Commands Definition**/
#define Lcd_Clear			0x01
#define Return_Home			0x02
#define Decrement_Cursor	0x04
#define Shift_Display_Right	0x05
#define Increment_cursor    0x06
#define Shift_display_left  0x07
#define Shift_cursor_left   0x10
#define Shift_cursor_right  0x14
#define Four_bit            0x28
#define Eight_bit           0x38
#define Cursor_off          0x0C
#define Cursor_on           0x0E


#define E_OK		0		//define E_OK : successful	
#define E_NOK		1		//define E_NOK : Not successful

/*********************************************
 *				Error Handling  			 *
********************************************/
#define	NULL_PTR					-1
#define	MODULE_UNITIALIZED			-2
#define	MULTIPLE_INIYIALIZATION		-3
#define	STOP_WITH_START				-4
#define	INVALID_PARAMETER			-5
#define	MULTIPLE_STOP				-6
#define	MULTIPLE_START				-7
#define	FULL_BUFFER					-8
#define	EMPTY_BUFFER				-9

/*********************************************
 *	  	   Function prototypes				 *
 ********************************************/


EnmLCDError_t LCD_SendNibble(uint8_t data);
/**
 * Func			: LCD_Configure_Pins
 * Input		: NO
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (LCD PINS)
 */
EnmLCDError_t LCD_Configure_Pins(void);
/**
 * Func			: LCD_Init
 * Input		: NO
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (LCD PINS)
 */
EnmLCDError_t LCD_Init(void);
/**
 * Func			: LCD_SendCommand
 * Input		: NO
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (LCD PINS)
 */
EnmLCDError_t LCD_SendCommand(uint8_t data);
/**
 * Func			: LCD_DisplayChar
 * Input		: NO
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (LCD PINS)
 */
EnmLCDError_t LCD_DisplayChar(void);
/**
 * Func			: LCD_DisplayString
 * Input		: NO
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (LCD PINS)
 */
EnmLCDError_t LCD_DisplayString(void);
/**
 * Func			: LCD_DisplayStringRowColumn
 * Input		: NO
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (LCD PINS)
 */
EnmLCDError_t LCD_DisplayStringRowColumn(void);
/**
 * Func			: LCD_Clear
 * Input		: NO
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (LCD PINS)
 */
EnmLCDError_t LCD_Clear(void);
/**
 * Func			: LCD_GotoRowColumn
 * Input		: NO
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (LCD PINS)
 */
EnmLCDError_t LCD_GotoRowColumn(void);



#endif /* LCD_H_ */