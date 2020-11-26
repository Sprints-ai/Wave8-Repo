/*
 * FreeRTOS_SP2_Story1.c
 *
 * Created: 4/16/2020 8:19:33 PM
 * Author : Ahmed
 */ 

/************************************************************************/
/*                          Includes                                    */
/************************************************************************/

#include "std_types.h"
#include "DIO.h"
#include "LCD.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

/************************************************************************/
/*							General macros                              */
/************************************************************************/

/*Push buttons configuration*/
#define PB1_PORT			(GPIOB)
#define PB2_PORT			(GPIOB)
#define PB1_PIN				(DIO_PIN6)
#define PB2_PIN				(DIO_PIN7)

/*LED Configuration*/
#define LED_PORT			(GPIOD)
#define LED_PIN				(DIO_PIN0)

/*Push buttons group bits*/
#define PB1_GRP_BIT			(1 << 0)
#define PB2_GRP_BIT			(1 << 1)

/*Tasks priorities*/
#define INIT_TASK_PRI		(5)
#define TASKA_PRI			(3)
#define TASKB_PRI			(2)
#define TASKC_PRI			(1)
#define TASKD_PRI			(4)

/*Task blocking delays*/
#define TASKA_DELAY_50MS	(50)
#define TASKB_DELAY_50MS	(50)
#define TASKC_DELAY_50MS	(50)
#define TASKD_DELAY_250MS	(250)

/*Global variables holds the status of push button pins*/
uint8_t gu8_PB1_status = 0;
uint8_t gu8_PB2_status = 0;

/*Create event group bits*/
EventGroupHandle_t event_LED;

/*System initialization task*/
void systemInit(void * pv_init_param)
{
	/*Create event group*/
	event_LED = xEventGroupCreate();
	
	for(;;)
	{
		/*If the event group isn't created then cancel the initialization*/
		if(event_LED == NULL)
		{
			/*Do nothing*/
		}
		else
		{
			/*LCD initialization*/
			LCD_init();
			
			/*Initialize LED pin as output*/
			DIO_init(LED_PORT , LED_PIN , OUTPUT);
			
			/*Initialize push button pins as input*/
			DIO_init(PB1_PORT , PB1_PIN , INPUT);
			DIO_init(PB2_PORT , PB2_PIN , INPUT);
			
			/*Activate pull-up resistors for push button pins */
			DIO_Write(PB1_PORT , PB1_PIN , HIGH);
			DIO_Write(PB2_PORT , PB2_PIN , HIGH);
		}
		
		/*Delete the initialization task*/
		vTaskDelete(NULL);		
	}
	return;
}

/*Push button1 monitoring task*/
void taskA_PB1(void* pv_taskA_param)
{	
	for(;;)
	{
		/*Read PB1 status*/
		DIO_Read(PB1_PORT , PB1_PIN , &gu8_PB1_status);
		
		/*Check whether PB1 is pressed or not*/
		if(gu8_PB1_status == LOW)
		{
			/*If PB1 is pressed then set its event group bit and clear PB2 event group bit*/
			xEventGroupSetBits(event_LED , PB1_GRP_BIT);
			xEventGroupClearBits(event_LED , PB2_GRP_BIT);
		}
		else
		{
			/*Clear PB1 group bit if it's not pressed*/
			xEventGroupClearBits(event_LED , PB1_GRP_BIT);
		}
		
		/*Block the task for 50ms*/
		vTaskDelay(TASKA_DELAY_50MS);
	}
	return;
}

/*Push button2 monitoring task*/
void taskB_PB2(void* pv_taskB_param)
{
	for(;;)
	{
		/*Read PB2 status*/
		DIO_Read(PB2_PORT , PB2_PIN , &gu8_PB2_status);
		
		/*Check whether PB2 is pressed or not*/
		if(gu8_PB2_status == LOW)
		{
			/*If PB2 is pressed then set its event group bit and clear PB1 event group bit*/
			xEventGroupSetBits(event_LED , PB2_GRP_BIT);
			xEventGroupClearBits(event_LED , PB1_GRP_BIT);
		}
		else
		{
			/*Clear PB2 group bit if it's not pressed*/
			xEventGroupClearBits(event_LED , PB2_GRP_BIT);
		}
		
		/*Block the task for 50ms*/
		vTaskDelay(TASKB_DELAY_50MS);		
	}
	return;
}

void taskC_LED(void* pv_taskC_param)
{
	/*Create variable to hold event group bits value*/
	EventBits_t event_status;
	
	for(;;)
	{
		/*Read the current event group bits*/
		event_status = xEventGroupGetBits(event_LED);
		
		/*Check whether PB1 or PB2 is pressed*/
		if( (event_status & PB1_GRP_BIT) || (event_status & PB2_GRP_BIT) )
		{
			/*LED is ON if any PB is pressed*/
			DIO_Write(LED_PORT , LED_PIN , HIGH);
		}
		else
		{
			/*LED is OFF if the push buttons are released*/
			DIO_Write(LED_PORT , LED_PIN , LOW);
		}
		
		/*Block the task for 50ms*/
		vTaskDelay(TASKC_DELAY_50MS);
	}
	return;
}

void taskD_LCD_LED_State(void* pv_taskC_param)
{
	/*Create variable to hold event group bits value*/
	EventBits_t event_status;
	
	for(;;)
	{
		/*Read the current event group bits*/
		event_status = xEventGroupGetBits(event_LED);
		
		/*Check event group bits current value*/
		if( (event_status & PB1_GRP_BIT) )
		{
			/*If PB1 is pressed then display LED is ON on LCD and current pressed PB*/
			LCD_clear();
			LCD_displayStringRowColumn((uint8_t*)"LED state is:ON",ROW_0,COL_0);
			LCD_displayStringRowColumn((uint8_t*)"PB1 is pressed",ROW_1,COL_0);
		}
		else if( ((event_status & PB2_GRP_BIT) >> 1) )
		{
			/*If PB2 is pressed then display LED is ON on LCD and current pressed PB*/
			LCD_clear();
			LCD_displayStringRowColumn((uint8_t*)"LED state is:ON",ROW_0,COL_0);
			LCD_displayStringRowColumn((uint8_t*)"PB2 is pressed",ROW_1,COL_0);			
		}
		else
		{
			/*If the two buttons are released then display LED is OFF*/
			LCD_clear();
			LCD_displayStringRowColumn((uint8_t*)"LED state is:OFF",ROW_0,COL_0);
		}
		
		/*Block the task for 250ms*/
		vTaskDelay(TASKD_DELAY_250MS);
	}
	return;
}

int main(void)
{
	/*Create system tasks*/
	xTaskCreate(systemInit,"Init",configMINIMAL_STACK_SIZE,NULL,INIT_TASK_PRI,NULL);
	xTaskCreate(taskA_PB1,"TaskA",configMINIMAL_STACK_SIZE,NULL,TASKA_PRI,NULL);
	xTaskCreate(taskB_PB2,"TaskB",configMINIMAL_STACK_SIZE,NULL,TASKB_PRI,NULL);	
	xTaskCreate(taskC_LED,"TaskC",configMINIMAL_STACK_SIZE,NULL,TASKC_PRI,NULL);
	xTaskCreate(taskD_LCD_LED_State,"TaskD",configMINIMAL_STACK_SIZE,NULL,TASKD_PRI,NULL);
	
	
	/*Start scheduling over the tasks*/
	vTaskStartScheduler();
   
    while(1) 
    {
		/*Do nothing*/
    }
	return 0;
}

