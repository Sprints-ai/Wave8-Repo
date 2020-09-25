/*
 ============================================================================
 Name        : LCD_Application.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#include "LCD_Application.h"


#define NEAR                           0
#define INTERMEDIATE                   1
#define FAR                            2

extern uint16_t Distance;
extern uint8_t u8_state;

ERROR_STATUS LCD_Print(void)
{
	uint8_t au8_status=E_ok;
	uint8_t frist_digit;
	uint8_t second_digit;
	uint8_t thired_digit;
	//Distance=115;  /*for debugging*/
	//u8_state=NEAR; /*for debugging*/

	LCD_clearScreen();
	LCD_displayString("DISTANCE: ");
	if(Distance<10)
	{
		frist_digit=Distance+48;
		LCD_displayCharacter(frist_digit);
	}
	else if(Distance>=10 && Distance<100)
	{
		frist_digit=(Distance/10)+48;
		second_digit=(Distance%10)+48;
		LCD_displayCharacter(frist_digit);
		LCD_displayCharacter(second_digit);
	}
	else if(Distance>=100 && Distance<=400)
	{
		frist_digit=(Distance/100)+48;
		second_digit=(Distance%100);
		thired_digit=(second_digit%10)+48;
		second_digit=(second_digit/10)+48;
		LCD_displayCharacter(frist_digit);
		LCD_displayCharacter(second_digit);
		LCD_displayCharacter(thired_digit);
	}

	LCD_goToRowColumn(1,0);
	LCD_displayString("STEER: ");
	switch(u8_state)
	{
		case NEAR:
			LCD_displayString("BACKWARD");
			break;
		case INTERMEDIATE:
			LCD_displayString("RIGHT");
			break;
		case FAR:
			LCD_displayString("FORWARD");
			break;
	}


	return au8_status;
}

