 /*
 * FreeRTOS_Story2.c
 *
 *      Author: Abdallah Heidar
 */

#include "FreeRTOS.h"
#include "task.h"
#include "DIO.h"
#include "LCD.h"
#include "my_keypad.h"

#define ZERO 				(0)
#define MAX_charIndex 		(7)
#define DISPALY_DELAY 		(2000)
#define PASS_MATCHED 		(6)

#define STACK_SIZE 			(100)
#define NO_PARAMETERS 		(1)
#define PRIORITY_1 			(1)
#define PRIORITY_2 			(2)
#define PRIORITY_3 			(3)

#define PARAMETER ((st_task_payload *)pvParameters)

uint8_t correctCharsCnt = 0;

typedef struct{
	char charsEntered[7];
	uint8_t charIndex;
	uint8_t charsHelpIndex;
	const char pass[6]

}st_task_payload;

st_task_payload parameter = {charsEntered = {0},
							charIndex = 0 ,
					        charsHelpIndex=0,
					        pass = {'1','2','3','4','5','6'}
							};

void Sys_Init()
{
	while(1)
	{
		LCD_Init(FOUR_BIT_MODE);
		vTaskSuspend(NULL);
	}
}

void KeyPad(void *pvParameters)
{
	TickType_t xLastWakeTime;
	const TickType_t REPEAT_DELAY_TICKS = 130;

	xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		if(Key_Pressed() >= ZERO && ((PARAMETER->charIndex) < MAX_charIndex) )
		{
			PARAMETER->charsEntered[PARAMETER->charIndex] = (Key_Pressed() + NULL_CHAR);
			(PARAMETER->charIndex)++;
		}
		vTaskDelayUntil(&xLastWakeTime , REPEAT_DELAY_TICKS);
	}
}

void ValidatePassword()
{		
	LCD_ClearScreen();
	if(correctCharsCnt == PASS_MATCHED)
	{
		LCD_displayStringRowColumn(0, 0, " CorrectPassword");
	}
	else
	{
		LCD_displayStringRowColumn(0, 0, " WRONG ONE ");
	}
	vTaskDelay(DISPALY_DELAY);
}

void PASS_Check(void *pvParameters)
{
	const TickType_t REPEAT_DELAY_TICKS = 140;

	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while(1)
	{		
		if(PARAMETER->charsEntered[PARAMETER->charIndex-1] == ';')
		{
			LCD_ClearScreen();
			PARAMETER->charIndex = 0;
			PARAMETER->charsHelpIndex = 0;	
			correctCharsCnt = 0;
		}
		else
		{
			if((PARAMETER->charsHelpIndex) < (PARAMETER->charIndex) )
			{
				for(PARAMETER->charsHelpIndex ; (PARAMETER->charsHelpIndex) < (PARAMETER->charIndex) ; (PARAMETER->charsHelpIndex++))
				{
					if(PARAMETER->charsHelpIndex < (MAX_charIndex - 1)){
						LCD_displayCharacter(PARAMETER->charsEntered[PARAMETER->charsHelpIndex]);
						if(PARAMETER->charsEntered[PARAMETER->charsHelpIndex] == PARAMETER->Pass[PARAMETER->charsHelpIndex])
						{
							correctCharsCnt++;
						}
					}
				}
			}
			else if( PARAMETER->charsHelpIndex == MAX_charIndex && PARAMETER->charsEntered[MAX_charIndex - 1] == ':')
			{
				ValidatePassword();
				LCD_ClearScreen();
				PARAMETER->charsHelpIndex++;
			    correctCharsCnt = 0;
			}	
		}
		vTaskDelayUntil(&xLastWakeTime, REPEAT_DELAY_TICKS);
	}
}

int main(void)
{
	TaskHandle_t Sys_Init = NULL;
	TaskHandle_t KeyPad_Task = NULL;
	TaskHandle_t PASS_Check_Task = NULL;

	xTaskCreate(PASS_Check,"PASS_Check" , STACK_100_WORD , &parameter 			   ,PRIORITY_1  , &PASS_Check_Task);
	xTaskCreate(KeyPad    ,"KeyPad" 	, STACK_100_WORD , &parameter 			   ,PRIORITY_2  , &KeyPad_Task);
	xTaskCreate(Sys_Init  ,"SysIn"  	, STACK_100_WORD , (void * ) NO_PARAMETERS ,PRIORITY_3 , &Sys_Init);
 
	vTaskStartScheduler();
	while(1)
	{
	}
}