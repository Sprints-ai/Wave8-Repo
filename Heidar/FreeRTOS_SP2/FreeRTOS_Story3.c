 /*
 * FreeRTOS_Story3.c
 *
 *      Author: Abdallah Heidar
 */
 
#include "task.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "semphr.h"

#include "LED.h"
#include "pushButton.h"

#define FALSE				            (0)
#define TRUE							(1)

#define BUTTON_0_FLAG       			(0x02)
#define BUTTON_1_FLAG      				(0x01)

#define LCD_DISPLAY_PERIODICITY         (200)
#define BUTTON_PERIODICITY              (50)

#define PRIORITY_1                 		(1)
#define PRIORITY_2                 		(2)
#define PRIORITY_3                 		(3)

#define STACK_SIZE 						(100)
#define NO_PARAMETERS 					(1)

EventGroupHandle_t Buttons_EventGroup_Handle;
EventGroupHandle_t LCD_EventGroup_Handle
xSemaphoreHandle switchSemaphore_Handle;

uint8_t Player1_Counter;
uint8_t Player2_Counter;

uint16_t gu16_LED_Peridicity;
uint8_t  gu8_ToggleFlag;

void SysInit_Task(void)
{
	gu16_LED_Peridicity = 50;
	gu8_ToggleFlag = TRUE;
	while(1)
	{
		LED_Init(LED_0);
		pushButtonInit(BTN_0);
		pushButtonInit(BTN_1);
		vTaskSuspend(NULL);
	}
}

void Button_0_Task(void)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	xEventGroupClearBits(Buttons_EventGroup_Handle, BUTTON_0_FLAG);
	xSemaphoreTake(switchSemaphore_Handle, 50);
	while(1)
	{
		if(pushButtonGetStatus(BTN_0) == Pressed)
		{
			xEventGroupSetBits(Buttons_EventGroup_Handle, BUTTON_0_FLAG);
			Player1_Counter++;
		}
		else
		{
			xEventGroupClearBits(Buttons_EventGroup_Handle, BUTTON_0_FLAG);
		}
		xSemaphoreGive(switchSemaphore_Handle);
		vTaskDelayUntil(&xLastWakeTime, BUTTON_PERIODICITY);
	}
}

void Button_1_Task(void)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	xEventGroupClearBits(Buttons_EventGroup_Handle, BUTTON_1_FLAG);
	xSemaphoreTake(switchSemaphore_Handle, 50);
	while(1)
	{
		if(pushButtonGetStatus(BTN_1) == Pressed)
		{
			xEventGroupSetBits(Buttons_EventGroup_Handle, BUTTON_1_FLAG);
			Player2_Counter++;	
		}
		else
		{
			xEventGroupClearBits(Buttons_EventGroup_Handle, BUTTON_1_FLAG);
		}
		xSemaphoreGive(switchSemaphore_Handle);
		vTaskDelayUntil(&xLastWakeTime, BUTTON_PERIODICITY);
	}
}
	
void LED_Task(void)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while (1)
	{
		if(xEventGroupGetBits(Buttons_EventGroup_Handle) == BUTTON_0_FLAG)
		{
			LED_On(LED_0);
			xEventGroupSetBits(LCD_EventGroup_Handle, BUTTON_0_FLAG);
			vTaskDelayUntil(&xLastWakeTime, 50);
		}
		else if(xEventGroupGetBits(xCreatedEventGroup) == BUTTON_1_FLAG)
		{
			LED_On(LED_0);
			xEventGroupSetBits(LCD_EventGroup_Handle, BUTTON_1_FLAG);
			vTaskDelayUntil(&xLastWakeTime, 50);
		}
		else
		{
			LED_Off(LED_0);
			vTaskDelayUntil(&xLastWakeTime, 50);
		}
	}
}

void LCD_Task(void)
{	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while (1)
	{
		if(Player1_Counter != 50 && Player2_Counter != 50)
		{
			if(xEventGroupGetBits(Buttons_EventGroup_Handle) == BUTTON_0_FLAG)
		{
			LCD_displayStringRC(0, 0, "Player One  ");
			vTaskDelayUntil(&xLastWakeTime, LCD_DISPLAY_PERIODICITY);
		}
		else if(xEventGroupGetBits(Buttons_EventGroup_Handle) == BUTTON_1_FLAG)
		{
			LCD_displayStringRC(0, 0, "Player Two  ");
			vTaskDelayUntil( &xLastWakeTime, LCD_DISPLAY_PERIODICITY);
		}
		}
		else if(Player1_Counter == 50)
		{
			LCD_displayStringRC(0, 0, "Player 1 Wins   ");
			LCD_displayStringRC(1, 0, "congratualtions ");
			Player1_Counter = 0;
			Player2_Counter = 0
			vTaskDelayUntil(&xLastWakeTime, LCD_DISPLAY_PERIODICITY);
		}
		else if(Player2_Counter == 50)
		{
			LCD_displayStringRC(0, 0, "Player 2 Wins   ");
			LCD_displayStringRC(1, 0, "Congratualtions ");
			Player1_Counter = 0;
			Player2_Counter = 0
			vTaskDelayUntil(&xLastWakeTime, LCD_DISPLAY_PERIODICITY);
		}
	}
}

int main(void)
{
	TaskHandle_t Button_0_Task_Handle = NULL;
	TaskHandle_t Button_1_Task_Handle = NULL;
	TaskHandle_t LCD_Task_Handle = NULL;
	TaskHandle_t SysInit_Task_Handle = NULL;
	
	vSemaphoreCreateBinary(switchSemaphore_Handle);
	
	Buttons_EventGroup_Handle = xEventGroupCreate();
	LCD_EventGroup_Handle = xEventGroupCreate();
    
	xTaskCreate(Button_0_Task, "Button 0", STACK_SIZE, NO_PARAMETERS, PERIORITY_1, &Button_0_Task_Handle);
	xTaskCreate(Button_1_Task, "Button 1", STACK_SIZE, NO_PARAMETERS, PERIORITY_2, &Button_1_Task_Handle);
	xTaskCreate(LCD_Task, "LCD", STACK_SIZE, NO_PARAMETERS, PERIORITY_2, &LCD_Task_Handle);
	xTaskCreate(SysInit_Task, "sysInit", STACK_SIZE, NO_PARAMETERS, PERIORITY_3, &SysInit_Task_Handle);
	
	vTaskStartScheduler();
	while(1)
	{
	}
	return 0;
}
