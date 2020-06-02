 /*
 * FreeRTOS_Story2.c
 *
 *      Author: Abdallah Heidar
 */

#include "FreeRTOS.h"
#include "task.h"
#include "LCD.h"
#include "pushButton.h"

#define TRUE							(1)
#define FALSE				          	(0)

#define BUTTON_1_FLAG      				(0x01)
#define BUTTON_0_FLAG       			(0x02)

#define BUTTON_PERIODICITY             	(50)
#define LCD_DISPLAY_PERIODICITY       	(200)

#define PRIORITY_1                 		(1)
#define PRIORITY_2                 		(2)
#define PRIORITY_3                 		(3)

#define STACK_SIZE 						(100)

EventGroupHandle_t Buttons_EventGroup_Handle;
EventGroupHandle_t LCD_EventGroup_Handle
xSemaphoreHandle switchSemaphore_Handle;

uint16_t gu16_LED_Peridicity;
uint8_t  gu8_ToggleFlag;

uint8_t Player1_Counter;
uint8_t Player2_Counter;

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

void BUTTON_0_Task(void)
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

void BUTTON_1_Task(void)
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
		else if(xEventGroupGetBits(Buttons_EventGroup_Handle) == BUTTON_1_FLAG)
		{
			LED_On(LED_0);
			xEventGroupSetBits(LCD_EventGroup_Handle, BUTTON_1_FLAG);
			vTaskDelayUntil( &xLastWakeTime, 50);
		}
		else
		{
			LED_Off(LED_0);
			vTaskDelayUntil( &xLastWakeTime, 50);
		}
	}
}

void LCD_Task(void)
{	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
		
	while (1)
	{
		if(xEventGroupGetBits(LCD_EventGroup_Handle) == BUTTON_0_FLAG)
		{
			LCD_displayStringRC(0, 0, "LED ON     ");
			LCD_displayStringRC(1, 0, "Button one ");
			vTaskDelayUntil(&xLastWakeTime, LCD_DISPLAY_PERIODICITY);
		}
		else if(xEventGroupGetBits(LCD_EventGroup_Handle) == BUTTON_1_FLAG)
		{
			LCD_displayStringRC(0, 0, "LED ON     ");
			LCD_displayStringRC(1, 0, "button TWO ");
			vTaskDelayUntil(&xLastWakeTime, LCD_DISPLAY_PERIODICITY);
		}
		else
		{
			LCD_displayStringRC(0, 0, "LED off    ");
			vTaskDelayUntil(&xLastWakeTime, LCD_DISPLAY_PERIODICITY);
		}
	}
}

int main(void)
{
	TaskHandle_t LED_Task_Handle = NULL;
	TaskHandle_t BUTTON_0_Task_Handle = NULL;
	TaskHandle_t BUTTON_1_Task_Handle = NULL;
	TaskHandle_t LCD_Task_Handle = NULL;
	TaskHandle_t SysInit_Task_Handle = NULL;
		
	vSemaphoreCreateBinary(switchSemaphore_Handle);
	
	LCD_EventGroup_Handle = xEventGroupCreate();
	Buttons_EventGroup_Handle = xEventGroupCreate();
	
    xTaskCreate(LED_Task, "LED", STACK_SIZE, NO_PARAMETERS, PERIORITY_1, &LED_Task_Handle);
	xTaskCreate(BUTTON_0_Task, "Button 0", STACK_SIZE, NO_PARAMETERS, PERIORITY_1, &BUTTON_0_Task_Handle);
	xTaskCreate(BUTTON_1_Task, "Button 1", STACK_SIZE, NO_PARAMETERS, PERIORITY_2, &BUTTON_1_Task_Handle);
	xTaskCreate(LCD_Task, "LCD", STACK_SIZE, NO_PARAMETERS, PERIORITY_2, &LCD_Task_Handle);
	xTaskCreate(SysInit_Task, "system Init", STACK_SIZE, NO_PARAMETERS, PERIORITY_3, &SysInit_Task_Handle);
	vTaskStartScheduler();
	while(1)
	{
	}
	return 0;
}
