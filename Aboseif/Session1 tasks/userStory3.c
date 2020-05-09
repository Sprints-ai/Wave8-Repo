/*
 * userStory3.c
 *
 * Created: 2020-04-14 4:20:42 PM
 *  Author: EbrahimOseif
 */
 

#include "FreeRTOS.h"
#include "task.h"
#include "pushButton.h"
#include "LED.h"



/************************************************************************/
/*					tasks  DEFINES                                     */
/************************************************************************/

#define FALSE				(0)
#define TRUE				(1)


#define PERIORITY_1 		(1)
#define PERIORITY_2 		(2)
#define PERIORITY_3 		(3)
#define STACK_SIZE 			(100)
#define NO_PARAMETERS 		(1)


/************************************************************************/
/*					global vars                                         */
/************************************************************************/

uint16_t gu16_LED_Peridicity;
uint8_t  gu8_toggleFlag;

/************************************************************************/
/*					API  Implementations                                */
/************************************************************************/


void SysInit_Task(void)
{
	gu16_LED_Peridicity = 50;
	gu8_toggleFlag = TRUE;

	while(1)
	{
		//initializing modules
		Led_Init(LED_0);
		pushButtonInit(BTN_0);
		
		vTaskSuspend(NULL);
	}
}

void BTN_Task(void)
{
	TickType_t xLastWakeTime;
	
	const TickType_t delayTicks = 50;
	static uint8_t u8_ledPeriodicityCounter;
	uint16_t u16_pressingPeridicity = 0;
	
	static uint8_t u8_CalibrateFlag = TRUE;
	
	while(1)
	{
		// In case the btn is pressed
		if( pushButtonGetStatus(BTN_0) == Pressed)
		{
			gu8_toggleFlag = FALSE;
			u8_ledPeriodicityCounter++;
			
			u16_pressingPeridicity = delayTicks * u8_ledPeriodicityCounter;
			
			/* calibrate the presssing time and led periodicity */
			
			if (u16_pressingPeridicity < 4000 && u16_pressingPeridicity >= 2000)
			{
				gu16_LED_Peridicity = 400;
				u8_CalibrateFlag = FALSE;
			}
			else if(u16_pressingPeridicity >= 4000 )
			{
				gu16_LED_Peridicity = 100;
				u8_CalibrateFlag = FALSE;
			}
			else if(u16_pressingPeridicity < 2000)
			{
				gu16_LED_Peridicity = 50;
				u8_CalibrateFlag = TRUE;
			}
		}
		else
		{
			//In case the led won't toggle 
			if(u8_CalibrateFlag)
			{
				gu8_toggleFlag = FALSE;
			}
			else
				gu8_toggleFlag = TRUE;
			
			u8_ledPeriodicityCounter=0;
		}
		
		vTaskDelayUntil( &xLastWakeTime, delayTicks );
	}
}

void Toggle_Task(void)
{
	TickType_t xLastWakeTime;
	const TickType_t delayTicks = 50;
	
	while (1)
	{
		if(gu8_toggleFlag == TRUE)
		{
			Led_Toggle(LED_0);
			vTaskDelayUntil( &xLastWakeTime, gu16_LED_Peridicity );
		}
		else
		{
			Led_Off(LED_0);
			vTaskDelayUntil( &xLastWakeTime, delayTicks );
		}
	}
}


int main(void)
{


		TaskHandle_t Toggle_Task_handle  = NULL;;
		TaskHandle_t BTN_Task_handle 	 = NULL;;
		TaskHandle_t SysInit_Task_handle = NULL;;

	/*Creating tasks*/
    
	xTaskCreate(Toggle_Task , "Toggle"  , STACK_SIZE , NO_PARAMETERS , PERIORITY_1 , &Toggle_Task_handle);
	xTaskCreate(BTN_Task    , "BTN"     , STACK_SIZE , NO_PARAMETERS , PERIORITY_2 , &BTN_Task_handle);
	xTaskCreate(SysInit_Task, "sysInit" , STACK_SIZE , NO_PARAMETERS , PERIORITY_3 , &SysInit_Task_handle);
	
	/* run the kernel Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}
	return 0;
}
