/*
 * userStory1.c
 *
 * Created: 2020-04-15 8:20:02 PM
 *  Author: EbrahimOseif
 */
 
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "pushButton.h"
#include "LCD.h"

 

#define Button_Flag                            0x02

#define LCD_DISPLAY_PERIODICITY                200
#define Button_PERIODICITY                     50
#define SendString_PERIODICITY                 400

#define STACK_SIZE              	           100


#define PRIORITY_1                             1
#define PRIORITY_2                             2
#define PRIORITY_3                             3
#define PRIORITY_4                             4



uint8_t gu8_SharedString[100];
EventGroupHandle_t xCreatedEventGroup;


void SysInit_Task(void)
{
	while(1)
	{
		//initializing modules
		pushButtonInit(BTN_0);
 		LCD_init(FOUR_BIT_MODE);

		vTaskSuspend( NULL );
	}
}


void LCD_Display_Task(void)
{	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
		
	while (1)
	{
		if(xEventGroupGetBits( xCreatedEventGroup ) == Button_Flag)
		{
			LCD_displayStringRowColumn(0,0,"                ");
			LCD_displayStringRowColumn(0,0,gu8_SharedString);
			LCD_displayStringRowColumn(1,0,"LCD Overwritten!");
			
			vTaskDelayUntil( &xLastWakeTime, LCD_DISPLAY_PERIODICITY );
		}
		else
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,gu8_SharedString);
			
			vTaskDelayUntil( &xLastWakeTime, LCD_DISPLAY_PERIODICITY );
		}
	}
}


void BTN_Task(void)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	xEventGroupClearBits(xCreatedEventGroup, Button_Flag);
	
	while(1)
	{
		if(pushButtonGetStatus(BTN_0) == Pressed)
		{
			xEventGroupSetBits(xCreatedEventGroup, Button_Flag);
		}
		else
		{
			xEventGroupClearBits(xCreatedEventGroup, Button_Flag);
		}
		vTaskDelayUntil( &xLastWakeTime, Button_PERIODICITY );
	}
}


void SendString_Task(void){
	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	uint8_t u8_LoopCounter, u8_string[] = "Hello LCD";
	
	while(1)
	{
		for (u8_LoopCounter=0; u8_string[u8_LoopCounter] !='\0'; u8_LoopCounter++)
		{
			gu8_SharedString[u8_LoopCounter] = u8_string[u8_LoopCounter];
		}

		vTaskDelayUntil( &xLastWakeTime, SendString_PERIODICITY );
	}
}





int main(void)
{

	TaskHandle_t LCD_Display_Task_handle  = NULL;
	TaskHandle_t SendString_Task_handle   = NULL;
	TaskHandle_t BTN_Task_handle		  = NULL;
	TaskHandle_t SysInit_Task_handle      = NULL;
	
	xCreatedEventGroup = xEventGroupCreate();

	/*Creating tasks*/
    xTaskCreate(LCD_Display_Task ,"LCD_Display" , STACK_SIZE   , NULL ,TASK_PRIORITY_1	,&LCD_Display_Task_handle);
    xTaskCreate(SendString_Task  ,"SendString"  , STACK_SIZE   , NULL ,TASK_PRIORITY_2	,&SendString_Task_handle);
    xTaskCreate(BTN_Task		 , "button" 	, STACK_SIZE   , NULL ,TASK_PRIORITY_3	,&BTN_Task_handle);
	xTaskCreate(SysInit_Task     , "sysInit"    , STACK_SIZE   , NULL ,TASK_PRIORITY_4	,&SysInit_Task_handle);
	
	/* Start Scheduler */
	vTaskStartScheduler();
	
	while(1){
		
	}

	return 0;
}