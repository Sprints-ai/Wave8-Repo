/*
 * APP.c
 *	Sprint1   -->>  Story 1
 *	Requirements :
 *	   Use an existing RTOS project to write a simple lock program with the following requirements:
 *		AGILE_REQ1:
 *						< A single task with periodicity 1000 ms >
 *		AGILE_REQ2:
 *						< Task shall toggle an LED at the rate of its periodicity >

 * Created on   : 4/15/2020 5:40:23 PM
 * Author       : AYA & EMAN
 */

/*
*** Inclusions
*/
#include "APP.h"

/*
*** Local Macros
*/

#define TOGGLE_LED_PERIODICITY			1000
#define PRIORITY_ONE			            1
#define PRIORITY_TWO		               2

/*
*** Local Function Prototypes
*/
void vTaskCode_Toggle_LED( void * );
void vTaskCode_Init( void * );



/* 
 * vTaskCode_Toggle_LED
 * Prototype	: void vTaskCode_Toggle_LED( void * pvParameters );
 * Description : Task Code for toggling a LED every 1000 msec
 * Input       : Pointer to the task’s parameter.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */

void vTaskCode_Toggle_LED( void * pvParameters )
{
	for( ;; )
	{
		Led_Toggle(LED_0);
		vTaskDelay(TOGGLE_LED_PERIODICITY);
	}
}


/* 
 * vTasksCreation_Toggle_LED
 * Prototype	: void vTasksCreation_LED_Toggle( void );
 * Description : Task Code for create Toggle Led Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void vTasksCreation_Toggle_LED( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
										vTaskCode_Toggle_LED,			 /* Function that implements the task. */
										"Toggle LED",						 /* Text name for the task. */
										configMINIMAL_STACK_SIZE,		 /* Stack size in words, not bytes. */
										( void * ) 1,						 /* Parameter passed into the task. */
										PRIORITY_TWO,						 /* Priority at which the task is created. */
										&xHandle								 /* Used to pass out the created task's handle. */
									);        
}

/* 
 * vTaskCode_Init
 * Prototype	: void vTaskCode_Init( void * pvParameters );
 * Description : Task Code for Initialization Task
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void vTaskCode_Init( void * pvParameters )
{
	
	Led_Init(LED_0);
	vTaskSuspend(NULL);
}


/* 
 * vTasksCreationInit
 * Prototype	: void vTasksCreationInit( void );
 * Description : Task Code for create Initialization Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void vTasksCreationInit( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
										vTaskCode_Init,					  /* Function that implements the task. */
										"Init Task",						  /* Text name for the task. */
										configMINIMAL_STACK_SIZE,       /* Stack size in words, not bytes. */
										( void * ) 1,                   /* Parameter passed into the task. */
										PRIORITY_ONE,                   /* Priority at which the task is created. */
										&xHandle 
								  );
}

