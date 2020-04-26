/*
 * APP.c
 *	Sprint2   -->>  Story 2
 *	Requirements :
 *	   Use an existing RTOS project to write a simple lock program with the following requirements:
 *
 *		AGILE_REQ1:
 *						< 4 tasks, A, B, C, D >
 *		AGILE_REQ2:
 *						< Task A shall be responsible for monitoring push button 1 state >
 *		AGILE_REQ3:
 *						< Task B shall be responsible for monitoring push button 2 state >
 *		AGILE_REQ4:
 *						< Task C shall be responsible for switching LED ON/OFF >
 *		AGILE_REQ5:
 *						< Task D shall be responsible for monitoring state of LED and printing its state on LCD and which button is currently activating the LED >
 *		AGILE_REQ6:
 *						< When push button 1 is pressed the LED is switched ON as long as it’s pressed and LCD prints current LED state and current push button 1 state >
 *		AGILE_REQ7:
 *						< If push button 2 is pressed the LED is switched ON as long as it’s pressed and LCD prints current LED state and current push button 2 state >
 *		AGILE_REQ8:
 *						< Only one push button is allowed to be pressed at a time to switch LED ON >
 *
 * Created on   : 4/21/2020 1:48:36 AM
 * Author       : AYA & EMAN
 */

/*
*** Inclusions
*/
#include "APP.h"

/*
*** Local Macros
*/

/* Tasks Periodicities */
#define LCD_DISPLAY_CHAR_PERIODICITY			400
#define TASKA_GET_BTN1_STATE_PERIDICITY		100
#define TASKB_GET_BTN2_STATE_PERIDICITY		250
#define LED_SWITCH_PERIODICITY					400	

/* Tasks Priorities */
#define PRIORITY_ONE								   1
#define PRIORITY_TWO								   2
#define PRIORITY_THREE							   3
														  
/* Event Bit Values */							  
#define BTN1_EVENT_BIT							  	( 1 << 0 )
#define BTN2_EVENT_BIT							  	( 1 << 1 )
														  
#define INITIAL_VALUE							  	0
														  


/*
*** Global Static Variables
*/

volatile char* gptr_LED_State = "OFF";
volatile char* gptr_Button1_State ='R';
volatile char* gptr_Button2_State ='R';

EventGroupHandle_t Group1;
EventGroupHandle_t Group2;
EventBits_t uxBits;
EventBits_t uxBits2;

/*
*** Local Function Prototypes
*/

static void Init_Task_Code( void * );
static void TaskA_Get_Button1_State_Code( void* );
static void TaskB_Get_Button2_State_Code( void* );
static void TaskC_Switch_LED_Code( void * );
static void TaskD_LCD_Display_Code( void * );






/**********************************************************************************************
*                         Creation of task A                 											 *
***********************************************************************************************/


/* 
 * TaskA_Get_Button1_State_Code
 * Prototype	: static void TaskA_Get_Button1_State_Code( void *pvParameters );
 * Description : Task Code for monitoring push button 1 state 
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */

static void TaskA_Get_Button1_State_Code( void *pvParameters )
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	uint8_t au8_Button_Status;
	Group1 = xEventGroupCreate( );
	for( ;; )
	{		
		au8_Button_Status = pushButtonGetStatus(BTN_0);
		if ( au8_Button_Status == Pressed)
		{
			uxBits = xEventGroupSetBits( Group1, BTN1_EVENT_BIT); //in Case Button1 is pressed and we need to take action, Set Event 
		}
		else
		{
			uxBits = xEventGroupClearBits( Group1, BTN1_EVENT_BIT); //Clear Event
		}
		vTaskDelayUntil( &xLastWakeTime,TASKA_GET_BTN1_STATE_PERIDICITY );
	}
}


/* 
 * Create_TaskA_Get_Button1_State
 * Prototype	: void Create_TaskA_Get_Button1_State( void );
 * Description : Task Code To create Push Button 1 Get status Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void Create_TaskA_Get_Button1_State( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;
	xReturned = xTaskCreate(
										TaskA_Get_Button1_State_Code, /* Function that implements the task. */
										"Get BTN1 Status",         	/* Text name for the task. */
										configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
										( void * ) 1,    					/* Parameter passed into the task. */
										PRIORITY_ONE,						/* Priority at which the task is created. */
										&xHandle								/* Used to pass out the created task's handle. */
									);     
}
/**********************************************************************************************
*                         Creation of task B											                	 *
***********************************************************************************************/

/* 
 * TaskB_Get_Button2_State_Code
 * Prototype	: static void TaskB_Get_Button2_State_Codee( void *pvParameters );
 * Description : Task Code for Get for Monitoring Button 2 state
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */

static void TaskB_Get_Button2_State_Code( void *pvParameters )
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	uint8_t au8_Button_Status;
	Group2 = xEventGroupCreate( );
	for( ;; )
	{
	   au8_Button_Status = pushButtonGetStatus(BTN_1);
		if (au8_Button_Status == Pressed)
		{
			uxBits2 = xEventGroupSetBits( Group2, BTN2_EVENT_BIT);  //in Case Button is pressed and we need to take action, Set Event 
		}
		else
		{
			uxBits2 = xEventGroupClearBits( Group2, BTN2_EVENT_BIT);  //Clear Event 
		}
		vTaskDelayUntil( &xLastWakeTime, TASKB_GET_BTN2_STATE_PERIDICITY);		
	}
}


/* 
 * Create_TaskB_Get_Button2_State
 * Prototype	: void Create_TaskB_Get_Button2_State( void );
 * Description : Task Code To create Push Button 2 Get Status Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void Create_TaskB_Get_Button2_State( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;
	xReturned = xTaskCreate(
										TaskB_Get_Button2_State_Code, /* Function that implements the task. */
										"Get BTN2 Status ",         	/* Text name for the task. */
										configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
										( void * ) 1,    					/* Parameter passed into the task. */
										PRIORITY_ONE,						/* Priority at which the task is created. */
										&xHandle								/* Used to pass out the created task's handle. */
									);     
}
/**********************************************************************************************
*                         Creation of task C															       *
***********************************************************************************************/
/* 
 * Create_TaskC_Switch_LED
 * Prototype	: void Create_TaskC_Switch_LED( void );
 * Description : Task Code To create a Task to switch LED ON, OFF.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void Create_TaskC_Switch_LED( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;
	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
										TaskC_Switch_LED_Code,        /* Function that implements the task. */
										"Switch LED ON OFF",          /* Text name for the task. */
										configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
										( void * ) 1,                 /* Parameter passed into the task. */
										PRIORITY_TWO,                 /* Priority at which the task is created. */
										&xHandle                      /* Used to pass out the created task's handle. */
									);										   
}

/* 
 * TaskC_Switch_LED_Code
 * Prototype	: static void TaskC_Switch_LED_Code( void * pvParameters );
 * Description : Task Code for switching LED ON/OFF 
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
static void TaskC_Switch_LED_Code( void * pvParameters )
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
   EventBits_t BTN1_Event;
	EventBits_t BTN2_Event;
	for (;;)
	{
		BTN1_Event = xEventGroupGetBits(Group1);
		BTN2_Event = xEventGroupGetBits(Group2);
		
		//BTN1 Is Pressed and BTN2 Is Released 
		if(BTN1_Event == BTN1_EVENT_BIT && BTN2_Event !=  BTN2_EVENT_BIT)
		{
			Led_On(LED_0);
			gptr_LED_State = "ON ";
         gptr_Button1_State = 'P';
			gptr_Button2_State = 'R';
		}
		//Two BTNs are Released 
		else if (BTN1_Event !=  BTN1_EVENT_BIT && BTN2_Event !=  BTN2_EVENT_BIT)
		{
			Led_Off(LED_0);
			gptr_LED_State = "OFF";
			gptr_Button1_State = 'R';
			gptr_Button2_State = 'R';
		}
		//BTN2 Is Pressed and BTN1 Is Released 
		else if (BTN2_Event == BTN2_EVENT_BIT && BTN1_Event !=  BTN1_EVENT_BIT)
		{
			Led_On(LED_0);
			gptr_LED_State = "ON ";
			gptr_Button1_State = 'R';
			gptr_Button2_State = 'P';	
		}
		vTaskDelayUntil( &xLastWakeTime,LED_SWITCH_PERIODICITY);
	}
}


/**********************************************************************************************
*                         Creation of task D																 *
***********************************************************************************************/
/* 
 * Create_TaskD_LCD_Display
 * Prototype	: void Create_TaskD_LCD_Display( void );
 * Description : Task Code To create LCD Display Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void Create_TaskD_LCD_Display( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
										TaskD_LCD_Display_Code,      /* Function that implements the task. */
										"LCD Display Data",          /* Text name for the task. */
										configMINIMAL_STACK_SIZE,    /* Stack size in words, not bytes. */
										( void * ) 1,                /* Parameter passed into the task. */
										PRIORITY_ONE,                /* Priority at which the task is created. */
										&xHandle                     /* Used to pass out the created task's handle. */
							    );
}

/* 
 * TaskD_LCD_Display_Code
 * Prototype	: static void TaskD_LCD_Display_Code( void * pvParameters );
 * Description : Task Code for Display LED and Button's status
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
static void TaskD_LCD_Display_Code( void * pvParameters )
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		LCD_GoTo_Row_Col(ROW_0,COL_0);
		LCD_Display_String("LED State Is:");
		LCD_Display_String(gptr_LED_State);
		LCD_GoTo_Row_Col(ROW_1,COL_0);
		LCD_Display_String("B1: ");
		LCD_Display_Char(gptr_Button1_State);
		LCD_Display_String("  B2: ");
		LCD_Display_Char(gptr_Button2_State);
		
		vTaskDelayUntil( &xLastWakeTime,LCD_DISPLAY_CHAR_PERIODICITY);
	}
		
}


/* 
 * Init_Task_Code
 * Prototype	: static void Init_Task_Code( void * pvParameters );
 * Description : Task Code for Initialization Task
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
static void Init_Task_Code( void * pvParameters )
{
	LCD_Init();
	Led_Init(LED_0);
	PORTB_DATA &=~UPPER_NIBBLE;
	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);
	vTaskSuspend(NULL);
}


/* 
 * Create_Init_Task
 * Prototype	: void Create_Init_Task( void );
 * Description : Task Code for create Initialization Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void Create_Init_Task( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
										Init_Task_Code,					/* Function that implements the task. */
										"Init Task",						/* Text name for the task. */
										configMINIMAL_STACK_SIZE,		/* Stack size in words, not bytes. */
										( void * ) 1,						/* Parameter passed into the task. */
										PRIORITY_ONE,						/* Priority at which the task is created. */
										&xHandle 
								  );
}

