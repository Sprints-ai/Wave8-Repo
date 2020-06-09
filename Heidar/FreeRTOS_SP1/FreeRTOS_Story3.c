 /*
 * FreeRTOS_Story3.c
 *
 *      Author: Abdallah Heidar
 */

#include "task.h"
#include "FreeRTOS.h"
#include "LED.h"
#include "pushButton.h"

#define FALSE				(0)
#define TRUE				(1)

#define STACK_SIZE 			(100)
#define NO_PARAMETERS 		(1)
#define PRIORITY_1 			(1)
#define PRIORITY_2 			(2)
#define PRIORITY_3 			(3)

uint16_t gu16_LEDPeridicity;
uint8_t  gu8_ToggleFlag;

void SysInit_Task(void)
{
	gu16_LEDPeridicity = 50;
	gu8_ToggleFlag = TRUE;
	while(1)
	{
		Led_Init(LED_0);
		pushButtonInit(BTN_0);
		vTaskSuspend(NULL);
	}
}

void BTN_Task(void)
{
	TickType_t xLastWakeTime;
	const TickType_t delayTicks = 50;
	static uint8_t u8_LEDPeriodicityCounter;
	uint16_t u16_pressingPeridicity = 0;
	static uint8_t u8_CalibrateFlag = TRUE;
	while(1)
	{
		if(pushButtonGetStatus(BTN_0) == Pressed)
		{
			gu8_ToggleFlag = FALSE;
			u8_LEDPeriodicityCounter++;
			u16_pressingPeridicity = delayTicks * u8_LEDPeriodicityCounter;
			if (u16_pressingPeridicity < 4000 && u16_pressingPeridicity >= 2000)
			{
				gu16_LEDPeridicity = 400;
				u8_CalibrateFlag = FALSE;
			}
			else if(u16_pressingPeridicity >= 4000 )
			{
				gu16_LEDPeridicity = 100;
				u8_CalibrateFlag = FALSE;
			}
			else if(u16_pressingPeridicity < 2000)
			{
				gu16_LEDPeridicity = 50;
				u8_CalibrateFlag = TRUE;
			}
		}
		else
		{
			if(u8_CalibrateFlag)
			{
				gu8_ToggleFlag = FALSE;
			}
			else
				gu8_ToggleFlag = TRUE;
				u8_LEDPeriodicityCounter=0;
		}
		vTaskDelayUntil(&xLastWakeTime, delayTicks);
	}
}

void Toggle_Task(void)
{
	TickType_t xLastWakeTime;
	const TickType_t delayTicks = 50;
	while (1)
	{
		if(gu8_ToggleFlag == TRUE)
		{
			Led_Toggle(LED_0);
			vTaskDelayUntil( &xLastWakeTime, gu16_LEDPeridicity );
		}
		else
		{
			Led_Off(LED_0);
			vTaskDelayUntil( &xLastWakeTime, delayTicks );
		}
	}
}

int main(void)
{
	TaskHandle_t Toggle_Task_Handle = NULL;
	TaskHandle_t Btn_Task_Handle = NULL;
	TaskHandle_t SysInit_Task_Handle = NULL;
    
	xTaskCreate(Toggle_Task, "Toggle", STACK_SIZE, NO_PARAMETERS, PRIORITY_1, &Toggle_Task_Handle);
	xTaskCreate(Btn_Task, "BTN", STACK_SIZE, NO_PARAMETERS, PRIORITY_2, &Btn_Task_Handle);
	xTaskCreate(SysInit_Task, "sysInit", STACK_SIZE, NO_PARAMETERS, PRIORITY_3, &SysInit_Task_Handle);
	vTaskStartScheduler();
	while(1)
	{
	}
	return 0;
}
