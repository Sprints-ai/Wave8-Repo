/*
 * sprint1.c
 *
 * Created: 4/13/2020 4:54:54 AM
 * Author : Reem el-Areeny
 */ 

#include "Services/Free_RTOS/FreeRTOS.h"
#include "Services/Free_RTOS/task.h"
#include "MCAL/DIO.h"
#include "ECUAL/pushButton.h"
 
#define STACK_SIZE 80

#define FOUR_SEC 40
#define TWO_SEC 20

#define MORE_4SEC_state 0
#define MORE_2SEC_state 1
#define LESS_2SEC_state 2

TaskHandle_t xHandle_initTask = NULL;
TaskHandle_t xHandle_toggleTask = NULL;

/* Task to be created. */
void vTask_toggleTask_s3( void * pvParameters )
{
	uint8_t au8_button_status ;
	
	uint8_t au8_current_operating_status = LESS_2SEC_state ;
	
	static uint8_t  au8_MORE_4SEC_state_counter = 0 ;
	
	static uint8_t au8_MORE_2SEC_state_counter = 0 ;
	
	const TickType_t xFrequency = 100 ;
	TickType_t xLastWakeTime;
	
	static uint32_t au32_time_counter = 0 ;

	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	
	/* The parameter value is expected to be 1 as 1 is passed in the
	pvParameters value in the call to xTaskCreate() below. */
	configASSERT( ( ( uint32_t ) pvParameters ) == 3 );

	for( ;; )
	{
		
		pushButtonGetStatus(BTN_0 , &au8_button_status) ;
		
		if(au8_button_status == Released)
		{
			
			if (au32_time_counter > FOUR_SEC)
			{
				au8_current_operating_status = MORE_4SEC_state ;
				au32_time_counter = 0 ;
			}
			else if (au32_time_counter > TWO_SEC)
			{
				au8_current_operating_status = MORE_2SEC_state ;
				au32_time_counter = 0 ;
			}
			else if (au32_time_counter >1)
			{
				au8_current_operating_status = LESS_2SEC_state ;
				au32_time_counter = 0 ;
			}
			
		}
		else if (Pressed)
		{
			au32_time_counter ++ ;
		}
		au8_MORE_4SEC_state_counter++;
		au8_MORE_2SEC_state_counter++;
		switch (au8_current_operating_status)
		{
			case MORE_4SEC_state :
			//au8_MORE_4SEC_state_counter++;
			if (au8_MORE_4SEC_state_counter == 1)
			{
				DIO_Toggle(GPIOB ,BIT4|BIT5|BIT6|BIT7 );
				au8_MORE_4SEC_state_counter = 0 ;
			}
			
			break;
			
			case MORE_2SEC_state :
			//au8_MORE_2SEC_state_counter++;
			if (au8_MORE_2SEC_state_counter == 4)
			{
				DIO_Toggle(GPIOB ,BIT4|BIT5|BIT6|BIT7 );
				au8_MORE_2SEC_state_counter = 0 ;
				//au8_MORE_4SEC_state_counter = 0;
			}
			
			break;
			
			case LESS_2SEC_state :
			
			DIO_Write(GPIOB ,BIT4|BIT5|BIT6|BIT7 , LOW );
			au8_MORE_4SEC_state_counter = 0;
			au8_MORE_2SEC_state_counter = 0;
			break;
			default:
			au8_MORE_4SEC_state_counter = 0;
			au8_MORE_2SEC_state_counter = 0;
			break;
		}
		
		
	vTaskDelayUntil( & xLastWakeTime,xFrequency);
	}
}

void vTask_initTask_s3(void * pvParameters)
{	
	/* The parameter value is expected to be 1 as 1 is passed in the
	pvParameters value in the call to xTaskCreate() below. */
	configASSERT( ( ( uint32_t ) pvParameters ) == 3 );
	
	DIO_Cfg_t Toggle_LRD_init ;
	Toggle_LRD_init.dir = OUTPUT ;
	Toggle_LRD_init.GPIO = GPIOB ;
	Toggle_LRD_init .pins = BIT4|BIT5|BIT6|BIT7 ;
	DIO_init(&Toggle_LRD_init);
	pushButtonInit(BTN_0);

	for( ;; )
	{
		vTaskDelete( xHandle_initTask );	
	}
}

/* Function that creates a task. */
void Story3(void)
{

	/* Create the task, storing the handle. */
	xTaskCreate(vTask_initTask_s3,       /* Function that implements the task. */
					"vTask_initTask_s3",          /* Text name for the task. */
					STACK_SIZE,      /* Stack size in words, not bytes. */
					( void * ) 3,    /* Parameter passed into the task. */
					3	,			/* Priority at which the task is created. */
					&xHandle_initTask );      /* Used to pass out the created task's handle. */
	
	
	 xTaskCreate(vTask_toggleTask_s3,       /* Function that implements the task. */
					"vTask_toggleTask_s3",          /* Text name for the task. */
					STACK_SIZE,      /* Stack size in words, not bytes. */
					( void * ) 3,    /* Parameter passed into the task. */
					1	,			/* Priority at which the task is created. */
					&xHandle_toggleTask );      /* Used to pass out the created task's handle. */

}

/************************************************************************/

void vTask_initTask_s1 (void * pvParameters)
{
		/* The parameter value is expected to be 1 as 1 is passed in the
	pvParameters value in the call to xTaskCreate() below. */
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	
	DIO_Cfg_t Toggle_LRD_init;
	Toggle_LRD_init.dir = OUTPUT;
	Toggle_LRD_init.GPIO = GPIOA;
	Toggle_LRD_init.pins = BIT7;
	DIO_init(&Toggle_LRD_init);

	for( ;; )
	{
		vTaskDelete( xHandle_initTask );
		
	}
}

void vTask_toggleTask_s1 (void * pvParameters)
{
	
	const TickType_t xFrequency = 1000; /* 1000 ms*/
	TickType_t xLastWakeTime;
	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

	for( ;; )
	{
		DIO_Toggle(GPIOA ,BIT7 );
		vTaskDelayUntil( &xLastWakeTime,xFrequency);

	}
	
}

/* Function that creates a task. */
void Story1( void )
{

	/* Create the task, storing the handle. */
	xTaskCreate(vTask_initTask_s1,       /* Function that implements the task. */
												"vTask_initTask_s1",          /* Text name for the task. */
												STACK_SIZE,      /* Stack size in words, not bytes. */
												( void * ) 1,    /* Parameter passed into the task. */
												3	,			/* Priority at which the task is created. */
												&xHandle_initTask );      /* Used to pass out the created task's handle. */
	
	
	xTaskCreate( vTask_toggleTask_s1,       /* Function that implements the task. */
													"vTask_toggleTask_s1",          /* Text name for the task. */
													STACK_SIZE,      /* Stack size in words, not bytes. */
													( void * ) 1,    /* Parameter passed into the task. */
													1	,			/* Priority at which the task is created. */
													&xHandle_toggleTask );      /* Used to pass out the created task's handle. */

}



int main(void)
{
	
	Story1();
	//Story3();
	
	/* Start Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}
	return 0 ;
}

