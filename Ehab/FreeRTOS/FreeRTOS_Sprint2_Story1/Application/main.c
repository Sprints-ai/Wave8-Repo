

#include "../Services/FreeRTOS/FreeRTOS.h"
#include "../Services/FreeRTOS/semphr.h"
#include "../Services/FreeRTOS/task.h"


#define INIT_TASK_PRIORITY				0

#define BUTTON_TASK_PRIORITY			1
#define BUTTON_TASK_DELAY				30		/*In Milli seconds*/

#define HELLO_LCD_TASK_PRIORITY			2
#define HELLO_LCD_TASK_DELAY			400		/*In Milli seconds*/
#define READY							1
#define NOT_READY						0

#define	LCD_DISPLAY_TASK_PRIORITY		3
#define LCD_DISPLAY_TASK_DELAY			200		/*In Milli seconds*/

#define INITIAL_COUNT					-1
 

	
uint8_t gu8_Message[16]="Hello LCD!!";
uint8_t gu8_MessageStatus;

SemaphoreHandle_t x_SemaphoreForLCD;

uint8_t gu8_ButtonStatus;

/************************************************************************/
/*                     Initialization Task                              */
/************************************************************************/
void InitTask(void* pvParameters)
{
	
	while(1)
	{
		/*Initialize LCD*/
		LCD_init();
		
		//LCD_displayStringRowColumn(1,0,gu8_Message);
		
		/*Initialize push button 0*/
		pushButtonInit(BTN_0);
		
		x_SemaphoreForLCD = NULL;
		
		/*Create a binary semaphore for LCD accessing synchronization*/
		x_SemaphoreForLCD = xSemaphoreCreateBinary();
		
		/*Give the semaphore once so it's initial value is 1*/
		xSemaphoreGive(x_SemaphoreForLCD);
		
		/*Initialize button status to be released*/
		gu8_ButtonStatus = Released;
		
		/*Suspend the task as it is of no further use*/
		vTaskSuspend(NULL);
		
	}
}

/************************************************************************/
/*                     PushButton Task                                  */
/************************************************************************/
void PushButtonTask(void* pvParameters)
{
	while(1)
	{
		/*Get the push button status and update the global variable of the button status*/
		pushButtonGetStatus(BTN_0,&gu8_ButtonStatus);
		
		if (gu8_ButtonStatus == Pressed)
		{
			xSemaphoreTake(x_SemaphoreForLCD,(TickType_t) 10 );
		}
		
		vTaskDelay(BUTTON_TASK_DELAY);
	}
}

/************************************************************************/
/*                     Hello LCD Task                                   */
/************************************************************************/
void HelloLCD_Task (void* pvParamaters)
{
	uint8_t u8_Message[] = "Hello LCD !!";
	uint8_t u8_CharacterCounter = 0;
	while(1)
	{
		if (xSemaphoreTake(x_SemaphoreForLCD ,(TickType_t) 30) == pdTRUE)
		{
			for (u8_CharacterCounter = 0 ; u8_Message[u8_CharacterCounter] != NULL_CHAR ; u8_CharacterCounter++)
			{
				gu8_Message[u8_CharacterCounter]=u8_Message[u8_CharacterCounter];
			}
			gu8_MessageStatus = READY;
			xSemaphoreGive(x_SemaphoreForLCD);
		}
		else
		{
			gu8_MessageStatus = NOT_READY;
		}
		
		vTaskDelay(HELLO_LCD_TASK_DELAY);
	}
	
}

/************************************************************************/
/*                     LCD Displayer Task                               */
/************************************************************************/
void LCD_DisplayerTask(void* pvParameters)
{
	uint8_t u8_State = 0;
	uint8_t au8_LCD_OverWritten[] = "I am overwritten";
	while(1)
	{
		if (gu8_ButtonStatus == Pressed)
		{
			LCD_displayStringRowColumn(1,0,au8_LCD_OverWritten);
		}
		else
		{
			xSemaphoreGive(x_SemaphoreForLCD);
			LCD_ClearSecondRow();
		}
		
		if (gu8_MessageStatus == READY)
		{
			if (u8_State == 0)
			{
				LCD_displayStringRowColumn(0,0,gu8_Message);
				u8_State = 1;
			}
			else if (u8_State == 1)
			{
				LCD_ClearFirstRow();
				u8_State = 0;
				
			}
		}
		else
		{
			LCD_ClearFirstRow();
		}
		
		
		vTaskDelay(LCD_DISPLAY_TASK_DELAY);
	}
}

/**************************************************************************************/
int main(void)
{
	
	
	/*Create the init task*/
	xTaskCreate(InitTask,NULL,configMINIMAL_STACK_SIZE,NULL,INIT_TASK_PRIORITY,NULL);
	
	/*Create the push button's task*/
	xTaskCreate(PushButtonTask,NULL,configMINIMAL_STACK_SIZE,NULL,BUTTON_TASK_PRIORITY,NULL);
	
	/*Create the Task that is responsible for outputting on the LCD*/
	xTaskCreate(LCD_DisplayerTask,NULL,configMINIMAL_STACK_SIZE,NULL,LCD_DISPLAY_TASK_PRIORITY,NULL);
	
	/*Create the task that sends "Hello LCD" every 400ms*/
	xTaskCreate(HelloLCD_Task,NULL,configMINIMAL_STACK_SIZE,NULL,HELLO_LCD_TASK_PRIORITY,NULL);
	
	/*Start the scheduler*/
	vTaskStartScheduler();
	
	/*Code should not reach this point unless there is an error*/
	return 0;
}
