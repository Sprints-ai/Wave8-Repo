/*
 * FreeRTOS_Story3.c
 *
 * Created: 4/13/2020 6:10:49 PM
 * Author : Ahmed
 */ 

/************************************************************************/
/*                            Includes                                          */
/************************************************************************/

#include "std_types.h"
#include "DIO.h"
#include "FreeRTOS.h"
#include "task.h"

/************************************************************************/
/*                         General macros	                            */
/************************************************************************/

/*System configurations*/
#define LED_PORT			(GPIOA)
#define PB_PORT				(GPIOA)
#define LED_PIN				(DIO_PIN1)
#define PB_PIN				(DIO_PIN0)

/*System control macros*/
#define COUNTER_RST			(0)

/*LED start and stop operations*/
#define LED_STOP			(0)
#define LED_START			(1)

/*LED OFF and Toggling modes*/
#define LED_OFF				(1)
#define LED_TOGGLE_400MS	(2)
#define LED_TOGGLE_100MS	(3)

/*Timing for two seconds and four seconds*/
#define TWO_SEC				(20)
#define FOUR_SEC			(40)

/*Tasks blocking delays*/
#define DEL_100_MS			(100)
#define DEL_400_MS			(400)

/*Tasks priorities*/
#define INIT_TASK_PRI		(3)
#define PB_TASK_PRI			(2)
#define LED_TASK_PRI		(1)

/************************************************************************/
/*                         System important variables                   */
/************************************************************************/

/*Variable indicates LED status*/
uint8_t  gu8_ledStatus = 0;

/*Variable indicates start of the LED*/
uint8_t gu8_ledStart = 0;

/*Variable indicates button status*/
uint8_t  gu8_buttonStatus = 0;

/*Button pressed counter*/
uint16_t gu16_buttonPressedCounter = 0;

/*System initialization task*/
void systemInit_Task(void* pv_param)
{
	for(;;)
	{
		/*Makes LED pin as output and Push Button pin as input pulled up*/
		DIO_init(LED_PORT , LED_PIN ,OUTPUT);
		DIO_init(PB_PORT , PB_PIN ,INPUT);
		DIO_Write(PB_PORT , PB_PIN ,HIGH);
		
		/*Delete the current task*/
		vTaskDelete(NULL);
	}
	return;
}

/*Task responsible for getting push button status and counting time*/
void pushButton_Task(void* pv_param)
{
	for(;;)
	{
		/*Read Push Button status*/
		DIO_Read(PB_PORT , PB_PIN , &gu8_buttonStatus);
		
		/*If the button is pressed*/
		if(gu8_buttonStatus == LOW)
		{
			/*Increase the counter by 1*/
			gu16_buttonPressedCounter++;	
		}
		else
		{
			/*Reset the counter if the button is unpressed*/
			gu16_buttonPressedCounter = COUNTER_RST;
			
			/*Start LED Toggling*/
			gu8_ledStart = LED_START;
		}
		
		/*Block this task for 100ms*/
		vTaskDelay(DEL_100_MS);		
	}
	return;
}

/*Task responsible for toggling LED*/
void LED_Toggle_Task(void* pv_param)
{	
	for(;;)
	{
		/*If the pressing time is less than 2 seconds*/
		if(gu16_buttonPressedCounter > ZERO && gu16_buttonPressedCounter < TWO_SEC)
		{
			/*Stop the LED operation and choose LED OFF mode*/
			gu8_ledStart  = LED_STOP;
			gu8_ledStatus = LED_OFF;
		}
		else if(gu16_buttonPressedCounter > TWO_SEC && gu16_buttonPressedCounter < FOUR_SEC)
		{
			/*Stop the LED operation and choose LED Toggling for 400ms mode*/
			gu8_ledStart  = LED_STOP;
			gu8_ledStatus = LED_TOGGLE_400MS;
		}
		else if(gu16_buttonPressedCounter > FOUR_SEC)
		{ 
			/*Stop the LED operation and choose LED Toggling for 100ms mode*/
			gu8_ledStart  = LED_STOP;
			gu8_ledStatus = LED_TOGGLE_100MS;
		}
		else
		{
			/*Do nothing*/
		}
		
		/*If the LED operation is started*/
		if(gu8_ledStart == LED_START)
		{
			/*Validate LED OFF and Toggling modes*/
			if(gu8_ledStatus == LED_OFF)
			{
				/*Turn off the LED*/
				DIO_Write(LED_PORT , LED_PIN , LOW);
			}
			else if(gu8_ledStatus == LED_TOGGLE_400MS)
			{
				/*Toggle the LED every 400ms*/
				DIO_Toggle(LED_PORT , LED_PIN);
				vTaskDelay(DEL_400_MS);
			}
			else if(gu8_ledStatus == LED_TOGGLE_100MS)
			{
				/*Toggle the LED every 100ms*/
				DIO_Toggle(LED_PORT , LED_PIN);
				vTaskDelay(DEL_100_MS);
			}
			else
			{
				/*Do nothing*/
			}
		}
		else
		{
			/*Do nothing*/
		}
		/*Yield the task for the scheduler*/
		taskYIELD();		
	}
	return;
}
int main(void)
{
	/*Create system tasks*/
    xTaskCreate(systemInit_Task,"Init",configMINIMAL_STACK_SIZE,NULL,INIT_TASK_PRI,NULL);
    xTaskCreate(pushButton_Task,"PBTask",configMINIMAL_STACK_SIZE,NULL,PB_TASK_PRI,NULL);
    xTaskCreate(LED_Toggle_Task,"LEDTask",configMINIMAL_STACK_SIZE,NULL,LED_TASK_PRI,NULL);
	
	/*Start RTOS scheduler*/
	vTaskStartScheduler();
	
    while (1) 
    {
		/*Do nothing*/
    }
	return 0;
}

