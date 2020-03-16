/*
 * main.c
 *
 *  Created on: Mar 14, 2020
 *      Author: Youssef Harby
 */


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "SERVICE/SOS.h"
#include "ECUAL/LCD.h"
#include "ECUAL/pushButton.h"
#include "MCAL/DIO.h"
#include <util/delay.h>
#include <avr/io.h>

/********************************************************************************
 *								Type Declaration								*
 ********************************************************************************/

typedef enum{
	APP_WELCOME,
	APP_QUESTION1,
	APP_QUESTION2,
	APP_QUESTION3,
	APP_QUESTION4,
	APP_QUESTION5,
	APP_FINAL_SCORE
}Application_SM;


/********************************************************************************
 * 								Preprocessor Macros								*
 ********************************************************************************/

#define NO		0
#define YES		1
#define INITIAL_VALUE		0
#define BUTTON_RELEASED		0
#define BUTTON_PRESSED		1
#define LCD_CLEARED			1

#define BTN_UNLOCKED		0
#define BTN_LOCKED			1

/********************************************************************************
 * 							  Global Static Variables							*
 ********************************************************************************/

static uint8_t gu8_LcdApplicationStateMachineVar = APP_WELCOME;
static uint8_t gu8_PushButtonReading0 = INITIAL_VALUE;
static uint8_t gu8_PushButtonReading1 = INITIAL_VALUE;
static uint8_t gu8_PushButtonLock = BTN_UNLOCKED;

/********************************************************************************
 * 							  	   Main Function								*
 ********************************************************************************/

void buttonstate0(void)
{
	pushButtonGetStatus(BTN_0 , &gu8_PushButtonReading0);
}

void buttonstate1(void)
{
	pushButtonGetStatus(BTN_1 , &gu8_PushButtonReading1);
}


void MainTask(void)
{
	uint8_t au8_ExpectedAnswer = INITIAL_VALUE;
	uint8_t au8_Answer = INITIAL_VALUE;
	static uint8_t au8_FinalScore = INITIAL_VALUE;
	static uint8_t au8_ClearOnce = INITIAL_VALUE;

	if(gu8_PushButtonReading0 != TRUE && gu8_PushButtonReading1 != TRUE)
	{
		gu8_PushButtonLock = BTN_UNLOCKED;
	}

	switch(gu8_LcdApplicationStateMachineVar)
	{
	case APP_WELCOME:
		LCD_displayStringRowColumn(ROW0, COLUMN0, "Welcome!");
		LCD_displayStringRowColumn(ROW1, COLUMN0, "Press any key..");

		if(gu8_PushButtonReading0 == TRUE)
		{
			gu8_LcdApplicationStateMachineVar = APP_QUESTION1;
			gu8_PushButtonLock = BTN_LOCKED;
		}

		if(gu8_PushButtonReading1 == TRUE)
		{
			gu8_LcdApplicationStateMachineVar = APP_QUESTION1;
			gu8_PushButtonLock = BTN_LOCKED;
		}

		break;
	case APP_QUESTION1:
		au8_ExpectedAnswer = NO;

		if(au8_ClearOnce == INITIAL_VALUE)
		{
			LCD_clear();
			au8_ClearOnce = LCD_CLEARED;
		}

		LCD_displayStringRowColumn(ROW0, COLUMN0, "ASCII of 0 = 0");
		LCD_displayStringRowColumn(ROW1, COLUMN0, "B0:Y  B1:N");

		if(gu8_PushButtonReading0 == TRUE)
		{
			au8_Answer = YES;
		}

		if(gu8_PushButtonReading1 == TRUE)
		{
			au8_Answer = NO;
		}

		if((gu8_PushButtonReading0 == TRUE || gu8_PushButtonReading1 == TRUE) && gu8_PushButtonLock == BTN_UNLOCKED)
		{
			gu8_PushButtonLock = BTN_LOCKED ;
			if(au8_Answer == au8_ExpectedAnswer)
				au8_FinalScore++;

			au8_ClearOnce = INITIAL_VALUE;
			gu8_LcdApplicationStateMachineVar = APP_QUESTION2;

			gu8_PushButtonReading0 = INITIAL_VALUE;
			gu8_PushButtonReading1 = INITIAL_VALUE;
		}

		break;
	case APP_QUESTION2:
		au8_ExpectedAnswer = NO;

		if(au8_ClearOnce == INITIAL_VALUE)
		{
			LCD_clear();
			au8_ClearOnce = LCD_CLEARED;
		}

		LCD_displayStringRowColumn(0, 0, "Mars has 3 moons");
		LCD_displayStringRowColumn(1, 0, "B0:Y  B1:N");

		if(gu8_PushButtonReading0 == TRUE)
		{
			au8_Answer = YES;
		}

		if(gu8_PushButtonReading1 == TRUE)
		{
			au8_Answer = NO;
		}

		if((gu8_PushButtonReading0 == TRUE || gu8_PushButtonReading1 == TRUE) && gu8_PushButtonLock == BTN_UNLOCKED)
		{
			gu8_PushButtonLock = BTN_LOCKED ;
			if(au8_Answer == au8_ExpectedAnswer)
				au8_FinalScore++;

			au8_ClearOnce = INITIAL_VALUE;
			gu8_LcdApplicationStateMachineVar = APP_QUESTION3;

			gu8_PushButtonReading0 = INITIAL_VALUE;
			gu8_PushButtonReading1 = INITIAL_VALUE;
		}

		break;
	case APP_QUESTION3:
		au8_ExpectedAnswer = NO;

		if(au8_ClearOnce == INITIAL_VALUE)
		{
			LCD_clear();
			au8_ClearOnce = LCD_CLEARED;
		}

		LCD_displayStringRowColumn(0, 0, "Is skyline near");
		LCD_displayStringRowColumn(1, 0, "B0:Y  B1:N");

		if(gu8_PushButtonReading0 == TRUE)
		{
			au8_Answer = YES;
		}

		if(gu8_PushButtonReading1 == TRUE)
		{
			au8_Answer = NO;
		}

		if((gu8_PushButtonReading0 == TRUE || gu8_PushButtonReading1 == TRUE)&& gu8_PushButtonLock == BTN_UNLOCKED)
		{
			gu8_PushButtonLock = BTN_LOCKED ;
			if(au8_Answer == au8_ExpectedAnswer)
				au8_FinalScore++;

			au8_ClearOnce = INITIAL_VALUE;
			gu8_LcdApplicationStateMachineVar = APP_QUESTION4;

			gu8_PushButtonReading0 = INITIAL_VALUE;
			gu8_PushButtonReading1 = INITIAL_VALUE;
		}

		break;
	case APP_QUESTION4:
		au8_ExpectedAnswer = NO;

		if(au8_ClearOnce == INITIAL_VALUE)
		{
			LCD_clear();
			au8_ClearOnce = LCD_CLEARED;
		}

		LCD_displayStringRowColumn(0, 0, "Is gold cheap");
		LCD_displayStringRowColumn(1, 0, "B0:Y  B1:N");

		if(gu8_PushButtonReading0 == TRUE)
		{
			au8_Answer = YES;
		}

		if(gu8_PushButtonReading1 == TRUE)
		{
			au8_Answer = NO;
		}

		if((gu8_PushButtonReading0 == TRUE || gu8_PushButtonReading1 == TRUE)&&gu8_PushButtonLock == BTN_UNLOCKED)
		{
			gu8_PushButtonLock = BTN_LOCKED ;
			if(au8_Answer == au8_ExpectedAnswer)
				au8_FinalScore++;

			au8_ClearOnce = INITIAL_VALUE;
			gu8_LcdApplicationStateMachineVar = APP_QUESTION5;

			gu8_PushButtonReading0 = INITIAL_VALUE;
			gu8_PushButtonReading1 = INITIAL_VALUE;
		}

		break;
	case APP_QUESTION5:
		au8_ExpectedAnswer = YES;

		if(au8_ClearOnce == INITIAL_VALUE)
		{
			LCD_clear();
			au8_ClearOnce = LCD_CLEARED;
		}

		LCD_displayStringRowColumn(0, 0, "Can we go home:(");
		LCD_displayStringRowColumn(1, 0, "B0:Y  B1:N");

		if(gu8_PushButtonReading0 == TRUE)
		{
			au8_Answer = YES;
		}

		if(gu8_PushButtonReading1 == TRUE)
		{
			au8_Answer = NO;
		}

		if((gu8_PushButtonReading0 == TRUE || gu8_PushButtonReading1 == TRUE) && gu8_PushButtonLock == BTN_UNLOCKED)
		{
			gu8_PushButtonLock = BTN_LOCKED ;
			if(au8_Answer == au8_ExpectedAnswer)
				au8_FinalScore++;

			au8_ClearOnce = INITIAL_VALUE;
			gu8_LcdApplicationStateMachineVar = APP_FINAL_SCORE;

			gu8_PushButtonReading0 = INITIAL_VALUE;
			gu8_PushButtonReading1 = INITIAL_VALUE;
		}

		break;
	case APP_FINAL_SCORE:
		if(au8_ClearOnce == INITIAL_VALUE)
		{
			LCD_clear();
			au8_ClearOnce = LCD_CLEARED;
		}

		LCD_displayStringRowColumn(0, 0, "Final Score = ");
		LCD_displayIntegerRowColumn(1, 0, au8_FinalScore);
		break;
	default:

		break;
	}
}


int main(void)
{
	st_SOS_init str_SOS_InitConfig = {
			SOS_TMR_CH0
	};

	SOS_TaskType str_SOS_MainTask = {
			SOS_PERIODIC,
			ZERO,
			ZERO,
			50,
			2,
			MainTask,
	};

	SOS_TaskType str_SOS_ButtonGetStatus0 = {
			SOS_PERIODIC,
			TWO,
			ONE,
			1,
			2,
			buttonstate0,
	};

	SOS_TaskType str_SOS_ButtonGetStatus1 = {
			SOS_PERIODIC,
			THREE,
			TWO,
			1,
			2,
			buttonstate1,
	};

	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);

	LCD_init();

	SOS_Init(&str_SOS_InitConfig);

	SOS_Add_Task(&str_SOS_MainTask);
	SOS_Add_Task(&str_SOS_ButtonGetStatus0);
	SOS_Add_Task(&str_SOS_ButtonGetStatus1);

	SEI();

	while(1)
	{
		SOS_Run();
	}
}
