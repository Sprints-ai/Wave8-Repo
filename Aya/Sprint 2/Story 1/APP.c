/*
 * APP.c
 *	Sprint2   -->>  Story 1
 *	Requirements :
 *	   Use an existing RTOS project to write a simple lock program with the following requirements:
 *
 *		AGILE_REQ1:
 *						 < 3 tasks, A, B, C >
 *	   AGILE_REQ2:
 *						 < Task A shall be responsible for outputting data on LCD >
 *	   AGILE_REQ3:
 *						 < Task B shall be responsible for reading a button state >
 *	   AGILE_REQ4:
 *						 < Task C shall be responsible for sending periodic data to LCD to be displayed >
 *	   AGILE_REQ5:
 *						 < Task C shall send to Task A “Hello LCD !!” with periodicity 400ms, Task A shall display any string received from Task C. Displayed on Row 1, Displayed for 200ms and then cleared >
 *    AGILE_REQ6:
 *						 < When button is pressed LCD displays “I have been over-written !!!!!!!!!” as long as button is pressed. Displayed on Row 2  >
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
#define LCD_DISPLAY_PERIODICITY        400
#define GET_BTN_STATE_PERIODICITY      300
#define SEND_DATA_PERIODICITY          400	
#define LCD_DISPLAY_SENTENCE           200

/* Tasks Priorities */
#define PRIORITY_ONE			            1
#define PRIORITY_TWO		               2
#define PRIORITY_THREE		            3


/* LCD Modes */
#define NORMAL_MODE                    0
#define BUTTON_PRESSED_MODE            1
#define INITIAL_VALUE						0

/* Event Bit Values */
#define BTN_EVENT_BIT						( 1 << 0 )

/*
*** Global Static Variables
*/

volatile char  *gptr_Data_Display;            //global pointer for data to be displayed
uint8_t gu8_LCD_Display_Mode;
EventGroupHandle_t Group1;
EventBits_t uxBits;

/*
*** Local Function Prototypes
*/
static void Init_Task_Code( void * );
static void TaskA_LCD_Display_Code( void * );
static void TaskB_Get_Button_State_Code( void * );
static void TaskC_Send_Data_Code( void * );




/**********************************************************************************************
*                         Creation of task A																	 *
***********************************************************************************************/
/* 
 * Create_TaskA_LCD_Display
 * Prototype	: void Create_TaskA_LCD_Display( void );
 * Description : Task Code To create LCD Display Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void Create_TaskA_LCD_Display( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
										TaskA_LCD_Display_Code,       /* Function that implements the task. */
										"LCD Display Data",           /* Text name for the task. */
										configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
										( void * ) 1,                 /* Parameter passed into the task. */
										PRIORITY_THREE,               /* Priority at which the task is created. */
										&xHandle                      /* Used to pass out the created task's handle. */
							     );
}

/* 
 * TaskA_LCD_Display_Code
 * Prototype	: static void TaskA_LCD_Display_Code( void * pvParameters );
 * Description : Task Code for Display Data From Task c
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
static void TaskA_LCD_Display_Code( void * pvParameters )
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	for( ;; )
	{
		switch (gu8_LCD_Display_Mode)
		{
			/* In normal Mode WE Display Sentence "Hello LCD !!" for 200 msec*/
			case NORMAL_MODE:
			{
				//DIO_Write(GPIOD,BIT0,HIGH) ;  // just for debugging
				LCD_Send_Cmd(CLEAR_LCD);
				LCD_GoTo_Row_Col(ROW_0,COL_0);  // To display data in Row 1
				LCD_Display_String(gptr_Data_Display);
				vTaskDelayUntil( &xLastWakeTime,LCD_DISPLAY_SENTENCE);   //display Data for 200 msec and then clear LCD
				//DIO_Write(GPIOD,BIT0,LOW) ;  // just for debugging
				LCD_Send_Cmd(CLEAR_LCD);
				break;
			}
			
			/* In BUTTON_PRESSED_MODE WE Display Sentence "Over Written !!!" as long as the button is pressed */
			case BUTTON_PRESSED_MODE:
			{
				LCD_Send_Cmd(CLEAR_LCD);
				LCD_GoTo_Row_Col(ROW_1,COL_1); // To display data in Row 2
				LCD_Display_String(gptr_Data_Display); 
				break;
			}
		}
		
		// as we need the system to be deterministic, and make the periodicity constant through all cases		
		if (gu8_LCD_Display_Mode == BUTTON_PRESSED_MODE )
		{
			vTaskDelayUntil( &xLastWakeTime, LCD_DISPLAY_PERIODICITY);  //400msec
		}
		else
		{
			vTaskDelayUntil( &xLastWakeTime,LCD_DISPLAY_PERIODICITY-LCD_DISPLAY_SENTENCE); // 200 as it's already consumed 200 msec before
		}
	}
		
}




/**********************************************************************************************
*                         Creation of task B											               	 *
***********************************************************************************************/

/* 
 * TaskB_Get_Button_State_Code
 * Prototype	: static void TaskB_Get_Button_State_Code( void *pvParameters );
 * Description : Task Code For reading Button State
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */

static void TaskB_Get_Button_State_Code( void *pvParameters )
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	Group1 = xEventGroupCreate( );
	uint8_t au8_Button_Status;
	for( ;; )
	{		
		au8_Button_Status = pushButtonGetStatus(BTN_0);
		
		if (au8_Button_Status == Pressed)
		{
			 uxBits = xEventGroupSetBits( Group1,BTN_EVENT_BIT);   //in Case Button is pressed and we need to take action, Set Event 
		}
		else
		{
			uxBits = xEventGroupClearBits( Group1,BTN_EVENT_BIT);  //Clear Event
		}
	
		vTaskDelayUntil( &xLastWakeTime, GET_BTN_STATE_PERIODICITY );
	}
}


/* 
 * Create_TaskB_Get_Button_State
 * Prototype	: void Create_TaskB_Get_Button_State( void );
 * Description : Task Code To create Button monitoring state Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void Create_TaskB_Get_Button_State( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;
	xReturned = xTaskCreate(
										TaskB_Get_Button_State_Code, 	/* Function that implements the task. */
										"Get BTN State",         		/* Text name for the task. */
										configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
										( void * ) 1,    				   /* Parameter passed into the task. */
										PRIORITY_ONE,					   /* Priority at which the task is created. */
										&xHandle								/* Used to pass out the created task's handle. */
									);     
}


/**********************************************************************************************
*                         Creation of task C															       *
***********************************************************************************************/
/* 
 * Create_TaskC_Send_Data
 * Prototype	: void Create_TaskC_Send_Data( void );
 * Description : Task Code To create a Task to Send Data To LCD.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void Create_TaskC_Send_Data( void )
{
	
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
										TaskC_Send_Data_Code,         /* Function that implements the task. */
										"Send Data",                  /* Text name for the task. */
										configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
										( void * ) 1,                 /* Parameter passed into the task. */
										PRIORITY_TWO,                 /* Priority at which the task is created. */
										&xHandle                      /* Used to pass out the created task's handle. */
									);
}

/* 
 * TaskC_Send_Data_Code
 * Prototype	: static void TaskC_Send_Data_Code( void * pvParameters );
 * Description : Task Code for Sending data to LCD to be displayed each 400 msec
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
static void TaskC_Send_Data_Code( void * pvParameters )
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
   EventBits_t BTN_Event; 
	for (;;)
	{
		BTN_Event = xEventGroupGetBits(Group1);
		
		//check event 
		if(BTN_Event != BTN_EVENT_BIT)
		{
			gptr_Data_Display = "Hello LCD !!";
			gu8_LCD_Display_Mode = NORMAL_MODE;
		}
		else
		{
			gptr_Data_Display = "Over-written !!!";
			gu8_LCD_Display_Mode = BUTTON_PRESSED_MODE;
			
		}
		
		vTaskDelayUntil( &xLastWakeTime,SEND_DATA_PERIODICITY );
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
	pushButtonInit(BTN_0);
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
										configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
										( void * ) 1,                 /* Parameter passed into the task. */
										PRIORITY_ONE,                 /* Priority at which the task is created. */
										&xHandle 
								  );
}

