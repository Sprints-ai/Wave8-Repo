#include "Services/FreeRTOS/FreeRTOS.h"
#include "Services/FreeRTOS/task.h"
#include "HAL/LED/LED.h"
#include "HAL/PushButton/pushButton.h"

/********************** User Story 3 *****************/

/*____________________________________________*/
/*______________Static Globals _______________*/
/*____________________________________________*/
uint16__t gu16LED_Peridicity;
uint8__t  gu8toggleFlag;
TaskHandle_t xHandle ;
TaskHandle_t xHandle1;
TaskHandle_t xHandle2;

/*____________________________________________*/
/*______________Task definition_______________*/
/*____________________________________________*/

/*
 * Task: SystemInit_Task
 * Task description: This Task used for initializing the used modules and globals
 */
void SystemInit_Task(void)
{
	//initializing globals
	gu16LED_Peridicity=50;
	gu8toggleFlag= TRUE;
	
	while(1)
	{
		//initializing modules
		Led_Init(LED_0);
		pushButtonInit(BTN_0);
		//Suspend this task to avoid repeating it again
		vTaskSuspend( xHandle2 );
	}
	
	
	
}

/*
 * Task: BTN_Task
 * Task description: This Task used for detecting whether the button is pressed
 *                   and released to take action with the led
 */
void BTN_Task(void)
{
	TickType_t xLastWakeTime;
	const TickType_t xdelayTicks = 50;
	static uint8__t u8ledperiodicityCounter;
	uint16_t u16pressingPeridicity = 50;
	static uint8__t u8lessFlag = TRUE;
	while(1)
	{
		// In case the btn is pressed
		if(pushButtonGetStatus(BTN_0) == Pressed)
		{
			gu8toggleFlag = FALSE;
			u8ledperiodicityCounter++;
			u16pressingPeridicity = xdelayTicks*u8ledperiodicityCounter;//Calculate the pressing time
			//in case the time lies between 4 sec and 2 sec
			if (u16pressingPeridicity < 4000 && u16pressingPeridicity >= 2000)
			{
				gu16LED_Peridicity = 400;// led periodicity will be 400 ms
				u8lessFlag = FALSE;//mark that the btn is pressed and th led will toggle
			}
			//in case the time greater than 4 sec 
			else if(u16pressingPeridicity >= 4000 )
			{
				gu16LED_Peridicity = 100;// led periodicity will be 100 ms
				u8lessFlag = FALSE;//mark that the btn is pressed and th led will toggle
			}
			//in case the time lies smaller than 2 sec
			else if(u16pressingPeridicity < 2000)
			{
				gu16LED_Peridicity = 50;// led periodicity will be 50 ms
				u8lessFlag = TRUE;//mark that the btn is pressed and th led will be off
			}
		}
		else
		{
			//In case the led won't toggle 
			if(u8lessFlag)
			{
				gu8toggleFlag = FALSE;
			}
			//In case the led will toggle 
			else
				gu8toggleFlag = TRUE;
			u8ledperiodicityCounter=0;
		}
		vTaskDelayUntil( &xLastWakeTime, xdelayTicks );
	}
}

/*
 * Task: BTN_Task
 * Task description: This Task used for toggling the led with a time is determined by  
 *                  pushing the btn
 */
void Toggle_Task(void)
{
	TickType_t xLastWakeTime;
	const TickType_t xdelayTicks = 50;
	while (1)
	{
		//In case the button is pressed with sufficient period
		if(gu8toggleFlag == TRUE)
		{
			Led_Toggle(LED_0);
			vTaskDelayUntil( &xLastWakeTime, gu16LED_Peridicity );
		}
		//In case the button is not pressed or pressed with insufficient period
		else
		{
			Led_Off(LED_0);
			vTaskDelayUntil( &xLastWakeTime, xdelayTicks );
		}
		
	}
	
}







int main(void)
{
	
    BaseType_t ret_,ret_1,ret_2,ret_3,ret_4;
	xHandle  = NULL;
	xHandle1 = NULL;
	xHandle2 = NULL;
	/*Creating tasks*/
    ret_2=  xTaskCreate(Toggle_Task   , "Toggle" , 100 , NULL , 1 , &xHandle);
	ret_3= xTaskCreate (BTN_Task       , "BTN"     , 100 , NULL , 2 , &xHandle1);
	ret_4= xTaskCreate (SystemInit_Task, "sysInit" , 100  , NULL , 3 , &xHandle2);
	/* Start Scheduler */
	vTaskStartScheduler();

	
	return 0;
}
