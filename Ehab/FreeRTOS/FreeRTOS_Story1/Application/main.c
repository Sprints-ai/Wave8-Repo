

#include "../Services/FreeRTOS/FreeRTOS.h"
#include "../Services/FreeRTOS/task.h"

#define INIT_TASK_PRIORITY		0

#define LED_TOG_TASK_DELAY		1000 /*toggling delay in Milli seconds*/
#define	LED_TOG_TASK_PRIORITY	1


/************************************************************************/
/*                     Initialization Task                              */
/************************************************************************/
void LedInitTask(void* pvParameters)
{
	while(1)
	{
		/*Initialize LED_0*/
		Led_Init(LED_0);
		
		/*Suspend the task as it is of no further use*/
		vTaskSuspend(NULL);
		
	}
}

/************************************************************************/
/*                     Led Toggle Task                                  */
/************************************************************************/
void LedToggleTask(void* pvParameters)
{
	while(1)
	{
		/*Toggle the LED*/
		Led_Toggle(LED_0);
		
		/*Delay for a period*/
		vTaskDelay(LED_TOG_TASK_DELAY);
	}
	
}

/**************************************************************************************/
int main(void)
{
	/*Create the init task*/
	xTaskCreate(LedInitTask,NULL,configMINIMAL_STACK_SIZE,NULL,0,NULL);
	
	/*Create the Led Toggle Task*/
	xTaskCreate(LedToggleTask,NULL,configMINIMAL_STACK_SIZE,NULL,1,NULL);
	
	/*Start the scheduler*/
	vTaskStartScheduler();
	
	/*Code should not reach this point unless there is an error*/
	return 0;
}
