/*
 * LCD_app.c
 *
 * Created: 24-Feb-20 11:26:07 AM
 * Author : ahmed
 */

#include <stdio.h>
#include "LCD_TS/LCD.h"
#include "LCD_TS/LCD_ErrorTable.h"



void LCD_initTesting(void)
{
	sint8_t output = 0;

	output = LCD_init();

	if(output == LCD_ERROR_MULTIPLE_INITIALIZATION)
	{
		printf("INIT ERROR #1 - MULTIPLE MODULE INITIALIZATION\n");
	}else if(output == E_OK)
	{
		printf("NO ERRORS DETECTED\n");
	}
}

void LCD_sendCommandTesting(uint8_t Command)
{
	sint8_t output = 0;

	output = LCD_sendCommand(Command);

	if(output == LCD_ERROR_NOT_INITIALIZED)
	{
		printf("SEND COMMAND ERROR #1 - MODULE NOT INITIALIZED\n");
	}else if(output == E_OK)
	{
		printf("NO ERRORS DETECTED\n");
	}
}

void LCD_displayCharacterTesting(uint8_t Data)
{
	sint8_t output = 0;

	output = LCD_sendCommand(Data);

	if(output == LCD_ERROR_NOT_INITIALIZED)
	{
		printf("DISPLAY CHARACTER ERROR #1 - MODULE NOT INITIALIZED\n");
	}else if(output == E_OK)
	{
		printf("NO ERRORS DETECTED\n");
	}
}

void LCD_displayStringTesting(sint8_t* ptr)
{
	sint8_t output = 0;

	output = LCD_displayString(ptr);

	if(output == LCD_ERROR_NOT_INITIALIZED)
	{
		printf("DISPLAY STRING ERROR #1 - MODULE NOT INITIALIZED\n");
	}else if(output == LCD_ERROR_NULL_POINTER)
	{
		printf("DISPLAY STRING ERROR #2 - NULL POINTER DETECTED\n");
	}else if(output == E_OK)
	{
		printf("NO ERRORS DETECTED\n");
	}
}

void LCD_goToRowColumnTesting(uint8_t Row, uint8_t Column)
{
	sint8_t output = 0;

	output = LCD_goToRowColumn(Row,Column);

	if(output == LCD_ERROR_NOT_INITIALIZED)
	{
		printf("GO TO ROW COLUMN ERROR #1 - MODULE NOT INITIALIZED\n");
	}else if(output == LCD_ERROR_INVALID_PARAMETERS)
	{
		printf("GO TO ROW COLUMN ERROR #2 - INVALID PARAMETERS\n");
	}else if(output == E_OK)
	{
		printf("NO ERRORS DETECTED\n");
	}
}

void LCD_displayStringRowColumnTesting(uint8_t Row, uint8_t Column, sint8_t* ptr)
{
	sint8_t output = 0;

	output = LCD_displayStringRowColumn(Row, Column, ptr);

	if(output == LCD_ERROR_NOT_INITIALIZED)
	{
		printf("DISPLAY STRING ROW COLUMN ERROR #1 - MODULE NOT INITIALIZED\n");
	}else if(output == LCD_ERROR_NULL_POINTER)
	{
		printf("DISPLAY STRING ROW COLUMN ERROR #2 - NULL POINTER DETECTED\n");
	}else if(output == LCD_ERROR_INVALID_PARAMETERS)
	{
		printf("DISPLAY STRING ROW COLUMN ERROR #3 - INVALID PARAMETERS\n");
	}else if(output == E_OK)
	{
		printf("NO ERRORS DETECTED\n");
	}
}

void LCD_clearTesting(void)
{
	sint8_t output = 0;

	output = LCD_clear();

	if(output == LCD_ERROR_NOT_INITIALIZED)
	{
		printf("CLEAR ERROR #1 - MODULE NOT INITIALIZED\n");
	}else if(output == E_OK)
	{
		printf("NO ERRORS DETECTED\n");
	}

}

int main(void)
{
	sint8_t test = 0;
	sint8_t* string = &test;

	/*
	 * REMOVE DOUBLE SLASH FOR TESTING
	 */

	/* LCD_INIT_SCENARIO1 : MULTIPLE INITIALIZATION */
	//	LCD_initTesting();
	//	LCD_initTesting();

	/* LCD_SENDCOMMAND_SCENARIO1 : CALL WITHOUT INITIALIZATION */
	//	LCD_sendCommandTesting(5);

	/* LCD_DISPLAYCHARACTER_SCENARIO1 : CALL WITHOUT INITIALIZATION */
	//	LCD_displayCharacterTesting(5);

	/* LCD_DISPLAYSTRING_SCENARIO1 : CALL WITHOUT INITIALIZATION */
	//	LCD_displayStringTesting(string);
	/* LCD_DISPLAYSTRING_SCENARIO2 : CALL WITH NULL POINTER */
	//	LCD_displayStringTesting(NULL);

	/* LCD_GOTOROWCOLUMN_SCENARIO1 : CALL WITHOUT INITIALIZATION */
	//	LCD_goToRowColumnTesting(1, 2)
	/* LCD_GOTOROWCOLUMN_SCENARIO2 : INVALID PARAMEDTER */
	//	LCD_goToRowColumnTesting(6, 20)


	/* LCD_DISPLAYSTRINGROWCOLUMN_SCENARIO1 : CALL WITHOUT INITIALIZATION */
	//	LCD_displayStringRowColumnTesting(1, 2, string);
	/* LCD_DISPLAYSTRINGROWCOLUMN_SCENARIO2 : CALL WITHOUT INITIALIZATION */
	//	LCD_displayStringRowColumnTesting(1, 2, NULL);
	/* LCD_DISPLAYSTRINGROWCOLUMN_SCENARIO3 : CALL WITHOUT INITIALIZATION */
	//	LCD_displayStringRowColumnTesting(6, 20, string);

	/* LCD_CLEAR_SCENARIO1 : CALL WITHOUT INITIALIZATION */
	//	LCD_clearTesting();

	return 0;
}
