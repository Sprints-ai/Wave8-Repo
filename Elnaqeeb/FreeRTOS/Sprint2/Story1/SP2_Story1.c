/*
 * FreeRTOS_SP2_Story1.c
 *
 * Created: 4/16/2020 8:19:33 PM
 * Author : Ahmed
 */ 

/************************************************************************/
/*							 Includes                            	    */
/************************************************************************/

#include "std_types.h"
#include "DIO.h"
#include "LCD.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/************************************************************************/
/*							General macros                              */
/************************************************************************/

/*Push button configuration*/
#define PB_PORT		(GPIOB)
#define PB_PIN		(DIO_PIN7)

/*Semaphore wait tick times*/
#define SEMAPHORE_WAIT_TICKS	((TickType_t) 10)

/*Tasks priorities*/
#define INITTASK_PRI			(4)
#define TASKA_PRI				(1)
#define TASKB_PRI				(3)
#define TASKC_PRI				(2)

/*Tasks blocking delays*/
#define TASKA_DELAY_200MS		(200)
#define TASKB_DELAY_50MS		(50)
#define TASKC_DELAY_400MS		(400)

/*Global variable holds the LCD Message*/
uint8_t gu8_LCD_arr[] = "Hello LCD!!";

/*Creating semaphore object*/
SemaphoreHandle_t sem_LCD;

/*System initialization task*/
void systemInit(void * pv_init_param)
{
	for(;;)
	{
		/*Create binary semaphore*/
		sem_LCD = xSemaphoreCreateBinary();
		
		/*If semaphore isn't created cancel the initialization*/
		if(sem_LCD == NULL)
		{
			/*Do nothing*/	
		}
		else
		{
			/*Free the semaphore so that any task can take it*/
			xSemaphoreGive(sem_LCD);	
			
			/*Initialize LCD*/
			LCD_init();
			
			/*Initialize the Push Button pin as INPUT-PULLUP*/
			DIO_init(PB_PORT , PB_PIN , INPUT);
			DIO_Write(PB_PORT , PB_PIN , HIGH);
		}
		
		/*Delete the initializing task*/
		vTaskDelete(NULL);
	}
	return;
}

/*LCD displaying task*/
void taskA_LCD_Display(void* pv_taskA_param)
{
	for(;;)
	{
		/*Validate if the semaphore is available to be taken or not*/
		if(xSemaphoreTake(sem_LCD , SEMAPHORE_WAIT_TICKS) == pdTRUE)
		{
			/*If the semaphore is available display certain string over the LCD*/
			LCD_displayStringRowColumn(gu8_LCD_arr,ROW_0 , COL_0);
		} 
		else
		{
			/*If the semaphore is already taken clear the LCD*/
			LCD_clear();
		}
		/*Block the task for 200ms*/
		vTaskDelay(TASKA_DELAY_200MS);		
	}
	return;
}

void taskB_PushButton(void* pv_taskB_param)
{
	/*Variable contains stores push button current status*/
	uint8_t au8_pushButton_status = 0;
	
	for(;;)
	{
		/*Read pin status*/
		DIO_Read(PB_PORT , PB_PIN , &au8_pushButton_status);
		
		/*Validate pin status*/
		if(au8_pushButton_status == LOW)
		{
			/*If it's LOW clear the LCD and overwrite it*/
			LCD_clear();
			LCD_displayStringRowColumn((uint8_t*)"I have been over",ROW_0 , COL_0);
			LCD_displayStringRowColumn((uint8_t*)"Written !!!!!!!!",ROW_1 , COL_0);
		}
		else
		{
			/*Do nothing*/
		}
		/*Block the task for 50ms*/
		vTaskDelay(TASKB_DELAY_50MS);
		
	}
	return;
}

void taskC_LCD_Periodic(void* pv_taskC_param)
{
	for(;;)
	{
		/*Gives the semaphore so that any task can take it*/
		xSemaphoreGive(sem_LCD);
		
		/*Block the task for 400ms*/
		vTaskDelay(TASKC_DELAY_400MS);	
	}
	return;
}

int main(void)
{
	/*Create system tasks*/
	xTaskCreate(systemInit,"Init",configMINIMAL_STACK_SIZE,NULL,INITTASK_PRI,NULL);
	xTaskCreate(taskA_LCD_Display,"TaskA",configMINIMAL_STACK_SIZE,NULL,TASKA_PRI,NULL);
	xTaskCreate(taskB_PushButton,"TaskB",configMINIMAL_STACK_SIZE,NULL,TASKB_PRI,NULL);	
	xTaskCreate(taskC_LCD_Periodic,"TaskC",configMINIMAL_STACK_SIZE,NULL,TASKC_PRI,NULL);

	/*Start scheduling over the tasks*/
	vTaskStartScheduler();
   
    while (1) 
    {
		/*Do nothing*/
    }
	return 0;
}

