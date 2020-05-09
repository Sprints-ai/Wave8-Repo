/*
 * userStory1.c
 *
 *	toggle led with delay
 * Created: 2020-04-14 4:20:42 PM
 *  Author: EbrahimOseif
 */
 


#include "FreeRTOS.h"
#include "task.h"
#include "DIO.h"


/************************************************************************/
/*							DEFINES                                     */
/************************************************************************/

#define PERIORITY_1 		(1)
#define PERIORITY_2 		(2)
#define PERIORITY_3 		(3)

#define STACK_SIZE 			(100)

#define NO_PARAMETERS 		(1)

#define DELAY_TIME 			(1000)

/************************************************************************/
/*			        	APIS  implemetations                            */
/************************************************************************/

void Sys_Init(void * pvParameters)
{
	/* Initialize the dio pins for the led */
	
	while(1)
	{
	st_DIO_Cfg_t Dio_init ={
		GPIOA,
		PIN0,
		OUTPUT
	};

	DIO_init(&Dio_init);
	
	vTaskSuspend(NULL);
	}
}

void Led_Task(void * pvParameters)
{
	while(1)
	{
		DIO_Toggle(GPIOA , PIN0);

		vTaskDelay(DELAY_TIME);
	}
}


int main(void)
{

	/*Create Tasks Handles*/
	TaskHandle_t Sys_Init_Task = ZERO;
	TaskHandle_t LED_Task = ZERO;

	xTaskCreate(Led_Task, "LED" 	, STACK_SIZE , (void *) NO_PARAMETERS  , PERIORITY_1	, &LED_Task);
	xTaskCreate(Sys_Init, "SysInit" , STACK_SIZE , (void * ) NO_PARAMETERS , PERIORITY_3 	, &Sys_Init_Task);
	
	/* run the kernel Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}
}