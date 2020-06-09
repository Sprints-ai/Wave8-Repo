 /*
 * FreeRTOS_Story1.c
 *
 *      Author: Abdallah Heidar
 */
 
#include "DIO.h"
#include "task.h"
#include "FreeRTOS.h"

#define NO_PARAMETERS 	(1)
#define DELAY_TIME 		(1000)

#define PRIORITY_1 		(1)
#define PRIORITY_2 		(2)
#define PRIORITY_3 		(3)
#define STACK_SIZE 		(100)

void Sys_Init(void *pvParameters)
{	
	while(1)
	{
		st_DIO_Cfg_t DIO_init ={
			GPIOA,
			PIN0,
			OUTPUT
		};
	DIO_Init(&DIO_init);
	vTaskSuspend(NULL);
	}
}

void LED_Task(void *pvParameters)
{
	while(1)
	{
		DIO_Toggle(GPIOA , PIN0);
		vTaskDelay(DELAY_TIME);
	}
}

int main(void)
{
	TaskHandle_t Sys_Init_Task = ZERO;
	TaskHandle_t LED_Task = ZERO;

	xTaskCreate(Sys_Init, "SysInit", STACK_SIZE, (void *) NO_PARAMETERS, PRIORITY_3, &Sys_Init_Task);
	xTaskCreate(LED_Task, "LED", STACK_SIZE, (void *) NO_PARAMETERS, PRIORITY_1, &LED_Task);

	vTaskStartScheduler();
	while(1)
	{
	}
}