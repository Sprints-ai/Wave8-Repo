#define F_CPU 16000000
#include "Services/FreeRTOS/FreeRTOS.h"
#include "Services/FreeRTOS/task.h"
#include "Services/FreeRTOS/semphr.h"
#include "Services/FreeRTOS/event_groups.h"
#include "HAL/PushButton/pushButton.h"
#include "HAL/LCD/LCD.h"

/********************** User Story 1 *****************/
/*____________________________________________*/
/*_________________Defines____________________*/
/*____________________________________________*/
#define ROW1                                   0
#define ROW2                                   1
#define COL1                                   0

#define BTN_MASK                               0x02

#define TASK_A_PERIODICITY                     200
#define TASK_B_PERIODICITY                     50
#define TASK_C_PERIODICITY                     400

#define TASK_A_STACK_SIZE                      100
#define TASK_B_STACK_SIZE                      100
#define TASK_C_STACK_SIZE                      100
#define TASK_INIT_STACK_SIZE                   100

#define TASK_PRIORITY_1                        1
#define TASK_PRIORITY_2                        2
#define TASK_PRIORITY_3                        3
#define TASK_PRIORITY_4                        4

/*____________________________________________*/
/*______________Static Globals _______________*/
/*____________________________________________*/
TaskHandle_t xHandle ;
TaskHandle_t xHandle1;
TaskHandle_t xHandle2;
TaskHandle_t xHandle3;
SemaphoreHandle_t xSemaphore;
EventGroupHandle_t xCreatedEventGroup;
uint8__t gau8_SharedStr[100];

/*____________________________________________*/
/*______________Task definition_______________*/
/*____________________________________________*/

/*
 * Task: SystemInit_Task
 * Task description: This Task used for initializing the used modules and globals
 */
void SystemInit_Task(void)
{
	//initializing globals
	while(1)
	{
		//initializing modules
		pushButtonInit(BTN_0);
 		LCD_init(DATA_BITS_4);
		//Suspend this task to avoid repeating it again
		vTaskSuspend( xHandle2 );
	}



}


/*
 * Task: LCD_Display_TaskA
 * Task description: This Task used for displaying on the lcd the given string
 */
void LCD_Display_TaskA(void)
{
	EventBits_t	ebValues;
	TickType_t xLastWakeTime;
	const TickType_t xdelayTicks = 200;
	while (1)
	{

		ebValues = xEventGroupWaitBits(xCreatedEventGroup,BTN_MASK,FALSE,FALSE,ZERO);
		//Check if the Button is pushed or not
		if(ebValues & BTN_MASK)
		{
			LCD_displayStringRowColumn(ROW1,COL1,"                ");
			LCD_displayStringRowColumn(ROW1,COL1,gau8_SharedStr);
			LCD_displayStringRowColumn(ROW2,COL1,"LCD Overwritten!");
			vTaskDelayUntil( &xLastWakeTime, TASK_A_PERIODICITY );
			LCD_displayStringRowColumn(ROW1,COL1,"                ");
		}
		else
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(ROW1,COL1,gau8_SharedStr);
			vTaskDelayUntil( &xLastWakeTime, TASK_A_PERIODICITY );
			LCD_clearScreen();
		}
		
	}

}

/*
 * Task: BTN_Task
 * Task description: This Task used for detecting whether the button is pressed
 *                   and released to take action with the led
 */
void BTN_TaskB(void)
{
	TickType_t xLastWakeTime;
	static uint8__t u8ledperiodicityCounter;
	xEventGroupClearBits(xCreatedEventGroup,BTN_MASK);
	while(1)
	{
		// In case the btn is pressed
		if(pushButtonGetStatus(BTN_0) == Pressed)
		{
			xEventGroupSetBits(xCreatedEventGroup,BTN_MASK);
		}
		else
		{
			xEventGroupClearBits(xCreatedEventGroup,BTN_MASK);

		}
		vTaskDelayUntil( &xLastWakeTime, TASK_B_PERIODICITY );
	}
}

/*
 * Task: SendStr_TaskC
 * Task description: This Task used for Sending the 
 */
void SendStr_TaskC(void)
{
	TickType_t xLastWakeTime;
	static uint8__t u8ledperiodicityCounter;
	static uint8__t u8lessFlag = TRUE;
	uint8__t u8_i, au8str[]="Hello LCD";
	while(1)
	{
		//Saving the string in a shared resource
		for (u8_i=0;u8_i<10;u8_i++)
		{
			gau8_SharedStr[u8_i]=au8str[u8_i];
		}

		vTaskDelayUntil( &xLastWakeTime, TASK_C_PERIODICITY );
	}
}





int main(void)
{

    BaseType_t ret_,ret_1,ret_2,ret_3,ret_4;
	xHandle  = NULL;
	xHandle1 = NULL;
	xHandle2 = NULL;
	xHandle3 = NULL;
	/*Creating Semaphore*/
	xSemaphore = xSemaphoreCreateBinary();
    xCreatedEventGroup = xEventGroupCreate();
	/*Creating tasks*/
    ret_1= xTaskCreate(LCD_Display_TaskA,"LCD_Display", TASK_A_STACK_SIZE,NULL,TASK_PRIORITY_1,&xHandle3);
    ret_2= xTaskCreate(SendStr_TaskC, "SendStr", TASK_C_STACK_SIZE,NULL,TASK_PRIORITY_2,&xHandle);
    ret_3= xTaskCreate (BTN_TaskB, "BTN", TASK_B_STACK_SIZE,NULL,TASK_PRIORITY_3,&xHandle1);
	ret_4= xTaskCreate (SystemInit_Task, "sysInit",TASK_INIT_STACK_SIZE, NULL ,TASK_PRIORITY_4,&xHandle2);
	/* Start Scheduler */
	vTaskStartScheduler();
	
	return 0;
}
