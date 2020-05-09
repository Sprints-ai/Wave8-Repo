/*
 * userStory3.c
 *
 * Created: 2020-04-14 4:20:42 PM
 *  Author: EbrahimOseif
 */
 

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
#include "pushButton.h"
#include "LED.h"



/************************************************************************/
/*					tasks  DEFINES                                     */
/************************************************************************/

#define FALSE				                   (0)
#define TRUE								   (1)

#define Button_0_Flag       				    0x02
#define Button_1_Flag      					    0x01

#define LCD_DISPLAY_PERIODICITY                 200
#define Button_PERIODICITY                      50


#define PERIORITY_1 							(1)
#define PERIORITY_2 							(2)
#define PERIORITY_3 							(3)
#define STACK_SIZE 								(100)
#define NO_PARAMETERS 							(1)


/************************************************************************/
/*					global vars                                         */
/************************************************************************/

EventGroupHandle_t Buttons_EventGroup;
EventGroupHandle_t LCD_EventGroup
xSemaphoreHandle switchSemaphore;

uint8_t player1_Counter;
uint8_t player2_Counter;


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
		pushButtonInit(BTN_1);
		
		vTaskSuspend(NULL);
	}
}

void BTN_0_Task(void)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	xEventGroupClearBits(Buttons_EventGroup, Button_0_Flag);
	xSemaphoreTake(switchSemaphore, 50);
	while(1)
	{
		if(pushButtonGetStatus(BTN_0) == Pressed)
		{
			xEventGroupSetBits(Buttons_EventGroup, Button_0_Flag);
			player1_Counter++;
		}
		else
		{
			xEventGroupClearBits(Buttons_EventGroup, Button_0_Flag);
		}
	
		xSemaphoreGive(switchSemaphore);
		vTaskDelayUntil( &xLastWakeTime, Button_PERIODICITY );
	}
}


void BTN_1_Task(void)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	xEventGroupClearBits(Buttons_EventGroup, Button_1_Flag);
	xSemaphoreTake(switchSemaphore, 50);
	while(1)
	{
		if(pushButtonGetStatus(BTN_1) == Pressed)
		{
			xEventGroupSetBits(Buttons_EventGroup, Button_1_Flag);
			player2_Counter++;	
		}
		else
		{
			xEventGroupClearBits(Buttons_EventGroup, Button_1_Flag);
		}
	
		xSemaphoreGive(switchSemaphore);
		vTaskDelayUntil( &xLastWakeTime, Button_PERIODICITY );
	}
}
	
void LED_Task(void)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	while (1)
	{
		if(xEventGroupGetBits( Buttons_EventGroup ) == Button_0_Flag)
		{
			Led_On(LED_0);
			xEventGroupSetBits(LCD_EventGroup, Button_0_Flag);

			vTaskDelayUntil( &xLastWakeTime, 50 );
		}
		else if(xEventGroupGetBits( xCreatedEventGroup ) == Button_1_Flag)
		{
			Led_On(LED_0);
			xEventGroupSetBits(LCD_EventGroup, Button_1_Flag);

			vTaskDelayUntil( &xLastWakeTime, 50 );
		}
		else
		{
			Led_Off(LED_0);
			vTaskDelayUntil( &xLastWakeTime, 50 );
		}
	}
}

void LCD_Task(void)
{	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
		
	while (1)
	{
		if( player1_Counter != 50 && player2_Counter != 50){
			if(xEventGroupGetBits( Buttons_EventGroup ) == Button_0_Flag)
		{
			LCD_displayStringRowColumn(0,0,"player one     ");

			vTaskDelayUntil( &xLastWakeTime, LCD_DISPLAY_PERIODICITY );
		}
		else if(xEventGroupGetBits( Buttons_EventGroup ) == Button_1_Flag)

		{
			LCD_displayStringRowColumn(0,0,"player two      ");

			vTaskDelayUntil( &xLastWakeTime, LCD_DISPLAY_PERIODICITY );
		}
		/* winners */
	  }
	  else if(player1_Counter == 50 ){
		  
			LCD_displayStringRowColumn(0,0,"player 1 wins   ");
			LCD_displayStringRowColumn(1,0,"congratualtions ");
			player1_Counter = 0;
			player2_Counter = 0
			vTaskDelayUntil( &xLastWakeTime, LCD_DISPLAY_PERIODICITY );
	  }
	  else if(player2_Counter == 50 ){
		  
			LCD_displayStringRowColumn(0,0,"player 2 wins   ");
			LCD_displayStringRowColumn(1,0,"congratualtions ");
			player1_Counter = 0;
			player2_Counter = 0
			vTaskDelayUntil( &xLastWakeTime, LCD_DISPLAY_PERIODICITY );
	  }
		
	}
}

int main(void)
{


	TaskHandle_t BTN_0_Task_handle 	 = NULL;
	TaskHandle_t BTN_1_Task_handle 	 = NULL;
	TaskHandle_t LCD_Task_handle 	 = NULL;
	TaskHandle_t SysInit_Task_handle = NULL;
		
	/*Creating semaphore */
	
	vSemaphoreCreateBinary(switchSemaphore);

	
	/*Creating event group */
	
	Buttons_EventGroup = xEventGroupCreate();
	LCD_EventGroup     = xEventGroupCreate();



	/*Creating tasks*/ 
    
	xTaskCreate(BTN_0_Task    , "BTN_0"   , STACK_SIZE , NO_PARAMETERS   , PERIORITY_1 , &BTN_0_Task_handle);
	xTaskCreate(BTN_1_Task    , "BTN_1"   , STACK_SIZE , NO_PARAMETERS   , PERIORITY_2 , &BTN_1_Task_handle);
	xTaskCreate(LCD_Task      , "BTN_1"   , STACK_SIZE , NO_PARAMETERS   , PERIORITY_2 , &LCD_Task_handle);
	xTaskCreate(SysInit_Task  , "sysInit" , STACK_SIZE , NO_PARAMETERS   , PERIORITY_3 , &SysInit_Task_handle);
	
	/* run the kernel Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}
	return 0;
}
