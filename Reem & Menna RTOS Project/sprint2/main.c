/*
 * sprint2.c
 *
 * Created: 4/16/2020 4:14:37 AM
 * Author : Reem el-Areeny
 */ 


#include "Services/Free_RTOS/FreeRTOS.h"
#include "Services/Free_RTOS/task.h"
#include "Services/Free_RTOS/semphr.h"
#include "MCAL/DIO.h"
#include "ECUAL/pushButton.h"
#include "ECUAL/LCD.h"
 

#define STACK_SIZE 80
/*
#define FOUR_SEC 40
#define TWO_SEC 20

#define MORE_4SEC_state 0
#define MORE_2SEC_state 1
#define LESS_2SEC_state 2*/

TaskHandle_t xHandle_initTask_s2 = NULL;
TaskHandle_t xHandle_task_A_s2 = NULL;
TaskHandle_t xHandle_task_B_s2 = NULL;
TaskHandle_t xHandle_task_C_s2 = NULL;
TaskHandle_t xHandle_task_D_s2 = NULL;

SemaphoreHandle_t xSemaphore = NULL;

typedef struct system_status_s
{
	uint8_t u8_BTN_state;
	uint8_t * u8_BTN_name;
}system_status_t;

system_status_t system_status;

/***********************************************************************************************************************************/

void vTask_initTask_s2 (void * pvParameters)
{
		/* The parameter value is expected to be 1 as 1 is passed in the
	pvParameters value in the call to xTaskCreate() below. */
	configASSERT( ( ( uint32_t ) pvParameters ) == 2);

	DIO_Cfg_t LEDs;
	LEDs.dir = OUTPUT;
	LEDs.GPIO = GPIOB;
	LEDs.pins = BIT6;
	DIO_init(&LEDs);

	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);

	LCD_init();

	for( ;; )
	{
		vTaskDelete( xHandle_initTask_s2 );
		
	}
}

void vTask_A_monitor_BTN0_s2 (void * pvParameters)
{	

	const TickType_t xFrequency = 30; /* 30 ms*/
	uint8_t u8_state = Released;
	static uint8_t u8_pressed_counter = 0;
	 
	TickType_t xLastWakeTime;

	configASSERT(((uint32_t)pvParameters) == 2);

	for( ;; )
	{
		pushButtonGetStatus(BTN_0,&u8_state);

		if(u8_state == Pressed)
		{
			u8_pressed_counter++;
			
			if(u8_pressed_counter >= 3){
				//u8_pressed_counter = 0;
				/*update led*/
									
				if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
				{
					system_status.u8_BTN_state = Pressed;
					system_status.u8_BTN_name = "BTN_0";
				}
			}
		}
		else if(u8_state == Released)
		{
			//u8_pressed_counter = 0;
			/*update led*/

			if(u8_pressed_counter)
			{
						system_status.u8_BTN_state = Released;
						system_status.u8_BTN_name = "BTN_0";
				xSemaphoreGive( xSemaphore );
				u8_pressed_counter = 0;
			 }
		}
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}

void vTask_B_monitor_BTN1_s2(void * pvParameters)
{
	const TickType_t xFrequency = 30; /* 30 ms*/
	uint8_t u8_state = Released;
	static uint8_t u8_pressed_counter = 0;

	TickType_t xLastWakeTime;
		
	configASSERT(((uint32_t)pvParameters) == 2);

	for( ;; )
	{
		pushButtonGetStatus(BTN_1,&u8_state);

		if(u8_state == Pressed)
		{
			u8_pressed_counter++;
				
			if(u8_pressed_counter >= 3)
			{
				//u8_pressed_counter = 0;
				/*update led*/
				if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
				{
					system_status.u8_BTN_state = Pressed;
					system_status.u8_BTN_name = "BTN_1";
				}
			}
		}
		else if(u8_state == Released)
		{
			/*update led*/

			if(u8_pressed_counter)
			{	
				system_status.u8_BTN_state = Released;
				system_status.u8_BTN_name = "BTN_1";
				xSemaphoreGive( xSemaphore );
				u8_pressed_counter = 0;
			}
		}
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}

void vTask_C_control_LED_s2(void * pvParameters)
{
	const TickType_t xFrequency = 100; /* 30 ms*/
	TickType_t xLastWakeTime;

	configASSERT(((uint32_t)pvParameters) == 2);

	for( ;; )
	{
		if(system_status.u8_BTN_state == Pressed)
		{
			DIO_Write(GPIOB,BIT6,HIGH);
		}
		else
		{
			DIO_Write(GPIOB,BIT6,LOW);
		}
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}

void vTask_D_print_state_s2(void * pvParameters)
{
	const TickType_t xFrequency = 100; /* 100 ms*/
	TickType_t xLastWakeTime;
	
	static uint8_t u8_prev_state = 0;

	configASSERT(((uint32_t)pvParameters) == 2);
	
	for( ;; )
	{
		if(system_status.u8_BTN_state != u8_prev_state)
		{
			u8_prev_state = system_status.u8_BTN_state ;
			LCD_clearLCD();
			if(system_status.u8_BTN_state  == Pressed)
			{	
				LCD_setLine(0);
				LCD_writeString(system_status.u8_BTN_name);
				LCD_writeString(" is Pressed");
				LCD_setLine(1);
				LCD_writeString("LED is ON");
			}
		}

		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}

/* Function that creates a task. */
void Story2( void )
{
	xSemaphore = xSemaphoreCreateMutex();

	/* Create the task, storing the handle. */
	xTaskCreate(vTask_initTask_s2,       /* Function that implements the task. */
					"vTask_initTask_s2",          /* Text name for the task. */
					STACK_SIZE,      /* Stack size in words, not bytes. */
					( void * ) 2,    /* Parameter passed into the task. */
					4	,			/* Priority at which the task is created. */
					&xHandle_initTask_s2);      /* Used to pass out the created task's handle. */
	
	
	xTaskCreate( vTask_A_monitor_BTN0_s2,       /* Function that implements the task. */
					"vTask_A_monitor_BTN0_s2",          /* Text name for the task. */
					STACK_SIZE,      /* Stack size in words, not bytes. */
					( void * ) 2,    /* Parameter passed into the task. */
					3	,			/* Priority at which the task is created. */
					&xHandle_task_A_s2 );      /* Used to pass out the created task's handle. */


	xTaskCreate( vTask_B_monitor_BTN1_s2,       /* Function that implements the task. */
					"vTask_B_monitor_BTN1_s2",          /* Text name for the task. */
					STACK_SIZE,      /* Stack size in words, not bytes. */
					( void * ) 2,    /* Parameter passed into the task. */
					3	,			/* Priority at which the task is created. */
					&xHandle_task_B_s2 );      /* Used to pass out the created task's handle. */

	xTaskCreate( vTask_C_control_LED_s2,       /* Function that implements the task. */
					"vTask_C_control_LED_s2",          /* Text name for the task. */
					STACK_SIZE,      /* Stack size in words, not bytes. */
					( void * ) 2,    /* Parameter passed into the task. */
					2	,			/* Priority at which the task is created. */
					&xHandle_task_C_s2 );      /* Used to pass out the created task's handle. */


	xTaskCreate( vTask_D_print_state_s2,       /* Function that implements the task. */
					"vTask_D_print_state_s2",          /* Text name for the task. */
					STACK_SIZE,      /* Stack size in words, not bytes. */
					( void * ) 2,    /* Parameter passed into the task. */
						2,			/* Priority at which the task is created. */
					&xHandle_task_D_s2 );      /* Used to pass out the created task's handle. */
}
/***********************************************************************************************************************************/

int main(void)
{
	Story2();

	/* Start Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}
	return 0 ;
}



