

#include "../Services/FreeRTOS/FreeRTOS.h"
#include "../Services/FreeRTOS/task.h"

#define INIT_TASK_PRIORITY				0

#define BUTTON_TASK_PRIORITY			1
#define BUTTON_TASK_DELAY				1		/*Button Task delay in Milli seconds*/
#define MINIMUM_BUTTON_PRESS			2000	/*Minimum button press time in Milli Seconds*/
#define MAXIMUM_BUTTON_PRESS			4000	/*Maximum button press time in Milli Seconds*/

#define	LED_TOG_TASK_PRIORITY			2
#define LED_TOG_TASK_400ms_DELAY		400		/*Toggling delay in Milli seconds*/
#define LED_TOG_TASK_100ms_DELAY		100		/*Toggling delay in Milli seconds*/
#define LED_TOG_TASK_NO_DELAY			1		/*Toggling delay in Milli seconds*/

#define INITIAL_COUNT					-1
 
/*Global Counter to be shared between the tasks*/
sint32_t su32_Counter; 

/*Global Flag to be shared between the tasks*/
uint8_t gu8_LedToggleTaskReady; 

/************************************************************************/
/*                     Initialization Task                              */
/************************************************************************/
void InitTask(void* pvParameters)
{
	while(1)
	{
		/*Initialize LED_0*/
		Led_Init(LED_0);
		
		/*Initialize push button 0*/
		pushButtonInit(BTN_0);
		
		/*Set the counter to the initial value (-1)*/
		su32_Counter = INITIAL_COUNT;
		
		/*Initialize the flag to be set when the led toggle task is ready to work by FALSE*/
		gu8_LedToggleTaskReady = FALSE;
		
		/*Suspend the task as it is of no further use*/
		vTaskSuspend(NULL);
		
	}
}

/************************************************************************/
/*                     PushButton Task                                  */
/************************************************************************/
void PushButtonTask(void* pvParameters)
{
	/*Variable to store the push button status in*/
	uint8_t u8_PushButtonStatus = Released;
	
	while(1)
	{
		/*Get the push button status*/
		pushButtonGetStatus(BTN_0,&u8_PushButtonStatus);
		
		/*Check the push button status if it is pressed increment the counter by 1
		and since this task's periodicity is 1 ms so each counter incrementation represents
		1 Milli second press on the button*/
		if (u8_PushButtonStatus == Pressed )
		{
			su32_Counter++;
		}
		
		/*If the button is pressed again reset the counter to count the pressing time again*/
		if (u8_PushButtonStatus == Pressed && gu8_LedToggleTaskReady)
		{
			su32_Counter = INITIAL_COUNT;
			gu8_LedToggleTaskReady = FALSE;
		}
		
		/*if the button is released after being pressed set the "ready flag" for the led toggle task*/
		if ((u8_PushButtonStatus == Released) && (su32_Counter > INITIAL_COUNT))
		{
			gu8_LedToggleTaskReady = TRUE;
		}
		
		/*delay for 1 Milli second*/
		vTaskDelay(BUTTON_TASK_DELAY);
	}
}

/************************************************************************/
/*                     Led Toggle Task                                  */
/************************************************************************/
void LedToggleTask(void* pvParameters)
{
	uint16_t u16_LedTaskDelay = LED_TOG_TASK_NO_DELAY;
	while(1)
	{
		/*check the "ready flag"*/
		if (gu8_LedToggleTaskReady)
		{
			/*if the button is pressed less than 2000 Milli seconds switch the LED off*/
			if (su32_Counter<=MINIMUM_BUTTON_PRESS)
			{
				Led_Off(LED_0);
			}
			
			/*if the button is pressed more than 2000 and less than 4000 Milli seconds toggle the led with 400ms periodicity*/
			else if (su32_Counter>MINIMUM_BUTTON_PRESS && su32_Counter<=MAXIMUM_BUTTON_PRESS)
			{
				Led_Toggle(LED_0);
				u16_LedTaskDelay = LED_TOG_TASK_400ms_DELAY;
			}
			
			/*if the button is pressed more than 4000 Milli seconds toggle the led with 100ms periodicity*/
			else if (su32_Counter>MAXIMUM_BUTTON_PRESS)
			{
				Led_Toggle(LED_0);
				u16_LedTaskDelay = LED_TOG_TASK_100ms_DELAY;
			}
			
		}
		
		vTaskDelay(u16_LedTaskDelay);
	}
	
}

/**************************************************************************************/
int main(void)
{
	/*Create the init task*/
	xTaskCreate(InitTask,NULL,configMINIMAL_STACK_SIZE,NULL,INIT_TASK_PRIORITY,NULL);
	
	/*Create the push button's task*/
	xTaskCreate(PushButtonTask,NULL,configMINIMAL_STACK_SIZE,NULL,BUTTON_TASK_PRIORITY,NULL);
	
	/*Create the Led Toggle Task*/
	xTaskCreate(LedToggleTask,NULL,configMINIMAL_STACK_SIZE,NULL,LED_TOG_TASK_PRIORITY,NULL);
	
	/*Start the scheduler*/
	vTaskStartScheduler();
	
	/*Code should not reach this point unless there is an error*/
	return 0;
}
