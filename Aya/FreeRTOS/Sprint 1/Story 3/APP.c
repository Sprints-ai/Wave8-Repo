/*
 * APP.c
 *	Sprint1   -->>  Story 3
 *	Requirements :
 *	   Use an existing RTOS project to write a simple lock program with the following requirements:
 *		AGILE_REQ1:
 *						< User shall be able to control LED toggling rate by pressing a push button, Action after releasing button > 
 *		AGILE_REQ2:
 *						< Press longer than two seconds and less than 4 seconds will toggle the LED with periodicity 400ms >
 *    AGILE_REQ3:
 *						< Press longer than 4 seconds will toggle the LED with periodicity 100ms >
 *    AGILE_REQ4:
 *                < Press shorter than 2 seconds will turn the LED OFF >
 *
 * Created: 4/15/2020 5:40:23 PM
 *  Author: AYA and EMAN
 */ 


/*
*** Inclusions
*/
#include "APP.h"

/*
*** Local Macros
*/
#define PRIORITY_ONE							 1
#define PRIORITY_TWO							 2
#define LED_TOGGLE_RATE_400				 400
#define LED_TOGGLE_RATE_100				 100
#define PRESS_BUTTON_PERIODICITY			 250
#define TOGGLE_LED_PERIODICITY			 200
#define NUMBER_COUNTS_PER_SEC				 4      // 1000 msec/PRESS_BUTTON_PERIODICITY 
#define TWO_SECONDS							 2
#define FOUR_SECONDS							 4

/*
*** Global Static Variables           
*/         
volatile uint16_t gu16_LED_Toggle_Rate;

/* 
 * vTaskCode_LED_Toggle
 * Prototype	: static void vTaskCode_LED_Toggle( void *pvParameters );
 * Description : Task Code for Toggle Led due to specific rate
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
static void vTaskCode_LED_Toggle( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 250;  //1sec
	xLastWakeTime = xTaskGetTickCount();
	for( ;; )
	{
		if (gu16_LED_Toggle_Rate == ZERO)
		{
			Led_Off(LED_0);	
			vTaskDelayUntil( &xLastWakeTime,TOGGLE_LED_PERIODICITY);	 
		}
		else
		{
			Led_Toggle(LED_0);
			vTaskDelayUntil( &xLastWakeTime,gu16_LED_Toggle_Rate);
			
		}
	}
}

/* 
 * vTasksCreation_LED_Toggle
 * Prototype	: void vTasksCreation_LED_Toggle( void );
 * Description : Task Code To create Led Toggle Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void vTasksCreation_LED_Toggle( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;
	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
										vTaskCode_LED_Toggle,				 /* Function that implements the task. */
										"LED ON",								 /* Text name for the task. */
										configMINIMAL_STACK_SIZE,			 /* Stack size in words, not bytes. */
										( void * ) 1, 							 /* Parameter passed into the task. */
										PRIORITY_TWO ,							 /* Priority at which the task is created. */
										&xHandle									 /* Used to pass out the created task's handle. */
									);
}



/* 
 * vTaskCode_Press_Button
 * Prototype	: static void vTaskCode_Press_Button( void *pvParameters );
 * Description : Task Code for Get time of pressing Button
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */

static void vTaskCode_Press_Button( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 250;
	xLastWakeTime = xTaskGetTickCount();
	static uint8_t au8_Count = ZERO;
	static uint8_t au8_Pre_Button_Status;
	uint8_t au8_Button_Status;
	
	for( ;; )
	{
		/*this Task is called each 250 m sec so if we need to know,how much time the button kept pressed
		  we need to divide the au8_Count by four*/ 
		au8_Button_Status = pushButtonGetStatus(BTN_0);
		
		if (au8_Button_Status == Pressed)
		{
			au8_Count++;
		}
		else
		{
			/* In case we need to take action after release*/
			if (au8_Pre_Button_Status == Pressed)
			{
				if ( au8_Count / NUMBER_COUNTS_PER_SEC >= TWO_SECONDS && au8_Count / NUMBER_COUNTS_PER_SEC <= FOUR_SECONDS)
				{
					gu16_LED_Toggle_Rate = LED_TOGGLE_RATE_400;
				}
				else if ( au8_Count / NUMBER_COUNTS_PER_SEC >= FOUR_SECONDS)
				{
					gu16_LED_Toggle_Rate = LED_TOGGLE_RATE_100;
				}
				else if(au8_Count / NUMBER_COUNTS_PER_SEC < TWO_SECONDS)
				{
					gu16_LED_Toggle_Rate = ZERO;
				}
				au8_Count = ZERO;
			}
			else
			{
				au8_Count = ZERO;
			}
			

		}
		
		au8_Pre_Button_Status = au8_Button_Status;
		vTaskDelayUntil( &xLastWakeTime, PRESS_BUTTON_PERIODICITY );
		
	}
}


/* 
 * vTasksCreation_PushButton
 * Prototype	: void vTasksCreation_PushButton( void );
 * Description : Task Code To create Push Button Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void vTasksCreation_PushButton( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;
	xReturned = xTaskCreate(
										vTaskCode_Press_Button,       	   /* Function that implements the task. */
										"Press Button",         				/* Text name for the task. */
										configMINIMAL_STACK_SIZE,     	   /* Stack size in words, not bytes. */
										( void * ) 1,    						   /* Parameter passed into the task. */
										PRIORITY_ONE,							   /* Priority at which the task is created. */
										&xHandle										/* Used to pass out the created task's handle. */
									);     
}

/* 
 * vTaskCode_Init_Task
 * Prototype	: static void vTaskCode_Init_Task( void * pvParameters );
 * Description : Task Code for Initialization Task
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
static void vTaskCode_Init_Task( void * pvParameters )
{
	
	strDIOCfg_t strDIOCfg= {GPIOB, UPPER_NIBBLE, OUTPUT};
	DIO_Init(&strDIOCfg);
	Led_Init(LED_0);
	pushButtonInit(BTN_0);
	vTaskSuspend(NULL);
}


/* 
 * vTasksCreation_Init_Task
 * Prototype	: void vTasksCreation_Init_Task( void );
 * Description : Task Code for create Initialization Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void vTasksCreation_Init_Task( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;
	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
										vTaskCode_Init_Task,					 /* Function that implements the task. */
										"Init Task",							 /* Text name for the task. */
										configMINIMAL_STACK_SIZE,			 /* Stack size in words, not bytes. */
										( void * ) 1,							 /* Parameter passed into the task. */
										PRIORITY_ONE,							 /* Priority at which the task is created. */
										&xHandle									 /* Used to pass out the created task's handle. */
									);
}

