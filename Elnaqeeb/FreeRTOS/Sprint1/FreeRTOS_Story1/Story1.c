/************************************************************************/
/*                         Includes                                     */
/************************************************************************/

#include "std_types.h"
#include "registers.h"
#include "DIO.h"
#include "FreeRTOS.h"
#include "task.h"

/************************************************************************/
/*                        General macros                                */
/************************************************************************/

/*LED pin configuration*/
#define	LED_PORT		(GPIOA)
#define LED_PIN			(DIO_PIN0)

/*Tasks configuration*/
#define INIT_TASK_PRIORITY	(2)
#define LED_TASK_PRIORITY	(1)
#define LED_TASK_DELAY_MS	(1000)

/************************************************************************/
/*                        APP Functions definition                      */
/************************************************************************/

void initTask(void* pv)
{
	/*Task infinite loop*/
	for(;;)
	{
		/*Configure LED pin as output*/
		DIO_init(LED_PORT , LED_PIN , OUTPUT);
		
		
		/*Delete initTask*/
		vTaskDelete(NULL);
	}
	return;
}

void LED_Task(void* pv)
{
	/*Task infinite loop*/
	for(;;)
	{		
		/*Toggle LED pin every time task is called*/
		DIO_Toggle(LED_PORT , LED_PIN);
			
		/*Block the task for a time in milli-seconds*/		
		vTaskDelay(LED_TASK_DELAY_MS);
	}
	return;
}

int main(void)
{	
	/*Initialization task creation*/
	xTaskCreate(initTask,"initTask",configMINIMAL_STACK_SIZE,NULL,INIT_TASK_PRIORITY,NULL);

	/*LED task creation*/	
	xTaskCreate(LED_Task,"LED_Task",configMINIMAL_STACK_SIZE,NULL,LED_TASK_PRIORITY,NULL);
	
	/* Start Scheduler */
	vTaskStartScheduler();

	while(1)
	{
		/*Do nothing*/
	}
	return 0;
}
