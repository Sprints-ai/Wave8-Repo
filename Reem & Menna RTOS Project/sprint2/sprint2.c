/*
 * sprint2.c
 *
 * Created: 4/16/2020 3:38:42 AM
 *  Author: MENA
 */ 

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "keypad.h"
#include "DIO.h"
#include "pushButton.h"

#include "LCD.h"
#define STACK_SIZE 80


/******sprint 2 story1 variables **************/
TaskHandle_t xHandle_initTask_s2 = NULL;
TaskHandle_t xHandle_Task_A_s2 = NULL ;
TaskHandle_t xHandle_Task_B_s2 = NULL ;
TaskHandle_t xHandle_Task_C_s2 = NULL ;

SemaphoreHandle_t xSemaphore;


/************************************************************************/
/***********************   sprint 2   ***********************************/
/************************************************************************/


/************************************************************************/
/*                         story 1                                      */
/************************************************************************/



/* Tasks to be created. */
void vTask_initTask_s2_s1 (void * pvParameters)
{
	/* The parameter value is expected to be 1 as 1 is passed in the
	pvParameters value in the call to xTaskCreate() below. */
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	
	DIO_Cfg_s Toggle_LED_init ;
	Toggle_LED_init.dir = OUTPUT ;
	Toggle_LED_init.GPIO = GPIOB ;
	Toggle_LED_init .pins = BIT7 ;
	DIO_init(&Toggle_LED_init);
	pushButtonInit(BTN_0);
	LCD_init();

	for( ;; )
	{
		vTaskDelete( xHandle_initTask_s2 );
		
	}
	
}

void vTask_A_s2_s1(void * pvParameters){
	
	const TickType_t xFrequency = 200 ;
	TickType_t xLastWakeTime;
	
	uint32_t ulNotifiedValue;
	
	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	

	for( ;; )
	{
		
		/******************************recieving PB signal  from task B***************/
		
		/* take semaphore*/
		
		if(xSemaphoreTake( xSemaphore, 0  )== pdTRUE ){
		/*display string*/
		LCD_gotoRowColumn(ROW2 ,COL1);
		LCD_displayString("I have been over-written !!!!!!!!");
		
		}
		else 
		{
			LCD_clear();
		}
	
		
		
		/******************************recieving string from task c***************/
		
		xTaskNotifyWait( 0x00,      /* Don't clear any notification bits on entry. */
		0xffffffff , /* Reset the notification value to 0 on exit. */
		&ulNotifiedValue, /* Notified value pass out in
		ulNotifiedValue. */
		0 );
		
		LCD_gotoRowColumn(0,0);
		LCD_displayString("            ");
		LCD_gotoRowColumn(0,0);
		LCD_displayString(ulNotifiedValue);
		
		
		vTaskDelayUntil( & xLastWakeTime,xFrequency);


		
		

		
	}
}


void vTask_B_s2_s1(void * pvParameters){
	
	const TickType_t xFrequency = 50 ;
	TickType_t xLastWakeTime;
	
	uint8_t au8_button_status ;
	
	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );


	for( ;; )
	{
		
		pushButtonGetStatus(BTN_0 , &au8_button_status) ;
		
		

		if (au8_button_status==Pressed){
		/**give semaphore*/
		DIO_Toggle(GPIOB,BIT7);
		xSemaphoreGive( xSemaphore );
		
		}
		vTaskDelayUntil( & xLastWakeTime,xFrequency);
	}
	
	
}


void vTask_C_s2_s1(void * pvParameters){
	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	
	const TickType_t xFrequency = 400 ;
	TickType_t xLastWakeTime;
	
	
	char str[] = "Hello LCD !! " ;
	
	
	
	for( ;; )
	{
		xTaskNotify( xHandle_Task_A_s2, (uint32_t)str , eSetValueWithOverwrite  );
		
		vTaskDelayUntil( & xLastWakeTime,xFrequency);

	}
	
}

/* Function that creates a task. */

void sprint2_Story1( void )
{
	BaseType_t xReturned_initTask;
	BaseType_t xReturned_Task_A;
	BaseType_t xReturned_Task_B;
	BaseType_t xReturned_Task_C;
	
	
	xSemaphore = xSemaphoreCreateBinary();

	
	/***************************** init task ********************************/

	/* Create the task, storing the handle. */
	xReturned_initTask = xTaskCreate(
	vTask_initTask_s2_s1,       /* Function that implements the task. */
	"M",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	3	,			/* Priority at which the task is created. */
	&xHandle_initTask_s2 );      /* Used to pass out the created task's handle. */
	
	/***************************** task A ********************************/
	
	xReturned_Task_A = xTaskCreate(
	vTask_A_s2_s1,       /* Function that implements the task. */
	"A",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	2	,			/* Priority at which the task is created. */
	&xHandle_Task_A_s2 );      /* Used to pass out the created task's handle. */

	/***************************** task B ********************************/
	
	
	xReturned_Task_B = xTaskCreate(
	vTask_B_s2_s1,       /* Function that implements the task. */
	"B",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	1	,			/* Priority at which the task is created. */
	&xHandle_Task_B_s2 );      /* Used to pass out the created task's handle. */
	
	
	/***************************** task C ********************************/
	
	
	xReturned_Task_C = xTaskCreate(
	vTask_C_s2_s1,       /* Function that implements the task. */
	"C",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	3	,			/* Priority at which the task is created. */
	&xHandle_Task_C_s2 );      /* Used to pass out the created task's handle. */
}

