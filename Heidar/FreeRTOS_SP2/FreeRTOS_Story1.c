 /*
 * FreeRTOS_Story1.c
 *
 *      Author: Abdallah Heidar
 */
 
#include "event_groups.h"
#include "FreeRTOS.h"
#include "task.h"
#include "LCD.h"
#include "pushButton.h"

#define LCD_DISPLAY_PERIODICITY  	(200)
#define BUTTON_PERIODICITY        	(50)
#define SEND_STRING_PERIODICITY     (400)

#define BUTTON_FLAG             	(0x02)

#define PRIORITY_1                 	(1)
#define PRIORITY_2                 	(2)
#define PRIORITY_3                 	(3)
#define PRIORITY_4                 	(4)

#define STACK_SIZE              	(100)

EventGroupHandle_t xCreatedEventGroup;
uint8_t gu8_sharedString[100];

void SysInit_Task(void)
{
	while(1)
	{
		pushButtonInit(BTN_0);
 		LCD_Init(FOUR_BIT_MODE);
		vTaskSuspend( NULL );
	}
}

void LCDDisplayTask(void)
{	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while (1)
	{
		if(xEventGroupGetBits( xCreatedEventGroup ) == BUTTON_FLAG)
		{
			LCD_displayStringRC(0, 0, "            ");
			LCD_displayStringRC(0, 0, gu8_sharedString);
			LCD_displayStringRC(1, 0, "LCD Overwritten");
			vTaskDelayUntil(&xLastWakeTime, LCD_DISPLAY_PERIODICITY);
		}
		else
		{
			LCD_Cls();
			LCD_displayStringRC(0, 0, gu8_sharedString);
			vTaskDelayUntil(&xLastWakeTime, LCD_DISPLAY_PERIODICITY);
		}
	}
}

void Button_Task(void)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	xEventGroupClearBits(xCreatedEventGroup, BUTTON_FLAG);
	while(1)
	{
		if(pushButtonGetStatus(BTN_0) == Pressed)
		{
			xEventGroupSetBits(xCreatedEventGroup, BUTTON_FLAG);
		}
		else
		{
			xEventGroupClearBits(xCreatedEventGroup, BUTTON_FLAG);
		}
		vTaskDelayUntil(&xLastWakeTime, BUTTON_PERIODICITY);
	}
}

void SendString_Task(void){
	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	uint8_t u8_loopCounter, u8_string[] = "Hello LCD";
	while(1)
	{
		for (u8_loopCounter=0; u8_string[u8_loopCounter] != '\0'; u8_loopCounter++)
		{
			gu8_sharedString[u8_loopCounter] = u8_string[u8_loopCounter];
		}
		vTaskDelayUntil(&xLastWakeTime, SEND_STRING_PERIODICITY);
	}
}

int main(void)
{
	TaskHandle_t LCDDisplayTask_handle = NULL;
	TaskHandle_t SendString_Task_handle = NULL;
	TaskHandle_t Button_Task_handle = NULL;
	TaskHandle_t SysInit_Task_handle = NULL;
	
	xCreatedEventGroup = xEventGroupCreate();

    xTaskCreate(LCDDisplayTask ,"LCD_Display", STACK_SIZE, NULL,TASK_PRIORITY_1, &LCDDisplayTask_handle);
    xTaskCreate(SendString_Task, "SendString", STACK_SIZE, NULL,TASK_PRIORITY_2, &SendString_Task_handle);
    xTaskCreate(Button_Task, "button", STACK_SIZE, NULL ,TASK_PRIORITY_3, &Button_Task_handle);
	xTaskCreate(SysInit_Task, "sysInit", STACK_SIZE, NULL ,TASK_PRIORITY_4, &SysInit_Task_handle);
	vTaskStartScheduler();
	while(1)
	{
	}
	return 0;
}