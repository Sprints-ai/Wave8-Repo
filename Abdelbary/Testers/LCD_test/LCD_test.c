/*
 * LCD_test.c
 *
 * Created: 3/16/2020 5:33:57 PM
 *  Author: mahmo
 */ 
#ifdef GCC 


#include "LCD_test.h"
#define LCD_INIT_STATES  7
#define LCD_TEST_FUNCTIONS	5
static uint8_t gu8_testCaseNumber;
typedef void(*Funptr)(void);

void lcd_dispatcher_test(void);
void LCD_EN_pulse_test(void);
void LCD_config_pins_test(void); // configure LCD pins.
void LCD_send_nibble_test(void); // re-maps data bits to LCD Pins.
void LCD_send_char_test(void);		//forms data ready to send to LCD
void LCD_send_command_test(void);	//forms command ready to send to LCD
void LCD_init_test(void);			//Initializes LCD
void LCD_clear_test(void);				//Clears LCD
void LCD_goto_xy_test(void);	//Cursor to X Y position


void LCD_Module_run_test()
{
	lcd_dispatcher_test();
}
void lcd_dispatcher_test(void)
{
	/*call without init*/
	sint16_t s16_expected_return = OK;
	sint16_t s16_fun_return;
	uint8_t u8_stateCounter = ZERO ;
	uint8_t u8_funCounter   = ZERO ;
	//Funptr LCD_Funptrs[2] = {LCD_clear_test ,LCD_goto_xy_test};
	/*	we need to lcd_dispatcher 6 times for module to be intalized so we will loop 6 times call every function 
	*	everyTime we should see error state except for the last time we should see OK
	*/
	for(;u8_stateCounter<LCD_INIT_STATES;++u8_stateCounter)
	{
		for(u8_funCounter = ZERO ; u8_funCounter < LCD_TEST_FUNCTIONS ; ++u8_funCounter)
			{
				
			}
		
	}
	s16_fun_return = lcd_dispatcher();
	checkTestCase((LCD_MODULE_ERR+MODULE_NOT_INITALIZED) ,s16_fun_return,&gu8_testCaseNumber);
}
void LCD_EN_pulse_test(void);
void LCD_config_pins_test(void); // configure LCD pins.
void LCD_send_nibble_test(void); // re-maps data bits to LCD Pins.
void LCD_send_char_test(void);		//forms data ready to send to LCD
void LCD_send_command_test(void);	//forms command ready to send to LCD
void LCD_init_test(void);			//Initializes LCD
void LCD_clear_test(void);				//Clears LCD
void LCD_send_string_test(void);	//Outputs string to LCD
void LCD_goto_xy_test(void);	//Cursor to X Y position

#endif