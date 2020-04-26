/*
 * APP.c
 *	Sprint 3  -->>  Story 2
 *	Requirements :
 *	   Use an existing RTOS project to write a simple lock program with the following requirements:
 *
 *		AGILE_REQ1:
 *						< The two micro-controllers shall communicate over a UART channel (9600 bps) full duplex  >
 *		AGILE_REQ2:
 *						< Each micro-controller will contain 1 keypad, 2 LEDs, 1 LCD, and 1 push button>
 *		AGILE_REQ3:
 *						< LCD shall display the received message in the lower row.
                    The received message will be displayed when received for two seconds and then cleared >
 *		AGILE_REQ4:
 *						< LCD shall display the sender input from keypad in the upper row.
                    When sender press the push button the message displayed in the upper row is sent to
                    the other micro-controller through UART channel and the message is cleared from the sender LCD >
 *		AGILE_REQ5:
 *                < LED 1 is turned ON for 500ms when a new message is received >
 *		AGILE_REQ6:
 *                < LCD shall display any Keypad readings on row 1, And shall display any new data from UART on row 2 >
 *		AGILE_REQ7:
 *                < LED 2 is turned ON for 200ms when a new message is sent >
 *
 * Created on   : 4/22/2020 1:48:36 AM
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
#define TASKA_LCD_DISPLAY_PERIODICITY			200
#define TASKB_KEYPAD_GET_KEY_PERIODICITY	   170
#define TASKD_GET_BTN1_STATE_PERIDICITY		130
#define TASKC_UART_DATA_PERIODICITY          100  /* in case this task take action based action based on interrupt event and we don't know,
                                                         when it happens we make it's periodicity as short as we can*/


/* Tasks Priorities */
#define PRIORITY_ONE								   1
#define PRIORITY_TWO								   2
#define PRIORITY_THREE							   3
														  
/* Event Bit Values */							  

#define UART_EVENT_BIT							  	( 1 << 0)
#define UART_EVENT_BIT							  	( 1 << 0)
#define BTN1_EVENT_BIT							  	( 1 << 3)
#define KEYPAD_EVENT_BIT							( 1 << 3)
														  
#define INITIAL_VALUE							  	0
														  
#define SET_FLAG                             1
#define UN_SET_FLAG                          0		

#define DATA_START_POSITION                  5			
#define SENDING_LED_PERIODICITY					200  // time of making a led on in msec			  
#define DISPLAYING_MSG                       2000 // time of displaying received message on lcd in msec	
#define RECEIVING_LED_PERIODICITY	         500  // time of making a led on in msec	
/*
*** Global Static Variables
*/

volatile static uint8_t gu8_KeyPad_Key ;
volatile static uint8_t gptr_UART_Rec_Data[16];
volatile static uint8_t* gptr_Button1_State;
volatile static uint8_t gu8_New_Data_Available;



static uint8_t Rec_array [16] ;
static uint8_t Tx_array [16] ;
static uint8_t gu8_Tx_Loop_counter = 0;

EventGroupHandle_t UART_Event_Group;
EventGroupHandle_t BTN_Event_Group;
EventGroupHandle_t KeyPad_Event_Group;

EventBits_t uxBits_UART;
EventBits_t uxBits_BTN;
EventBits_t uxBits_KeyPad;

/*
*** Local Function Prototypes
*/
static void UART_Call_Back_Func();
static void Init_Task_Code( void * );
static void TaskA_Get_Button1_State_Code( void* );
static void TaskB_Get_Button2_State_Code( void* );
static void TaskC_Get_UART_Data_Code( void * );
static void TaskA_LCD_Display_Code( void * );



/*
*** Function Implementation
*/

/**********************************************************************************************
*                         Creation of task A																 *
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
										TaskA_LCD_Display_Code,      /* Function that implements the task. */
										"LCD Display Data",          /* Text name for the task. */
										configMINIMAL_STACK_SIZE,    /* Stack size in words, not bytes. */
										( void * ) 1,                /* Parameter passed into the task. */
										PRIORITY_TWO,                /* Priority at which the task is created. */
										&xHandle                     /* Used to pass out the created task's handle. */
							    );
}


/* 
 * TaskA_LCD_Display_Code
 * Prototype	: static void TaskA_LCD_Display_Code( void * pvParameters );
 * Description : Task Code for Display data from UART, KeyPad and Button state
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
static void TaskA_LCD_Display_Code( void * pvParameters )
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	volatile static uint8_t Re_Init_Flag = SET_FLAG;
	
	for( ;; )
	{
		/* In case button Set and Released*/
		if (Re_Init_Flag == SET_FLAG && uxBits_BTN != BTN1_EVENT_BIT)
		{
				
			Re_Init_Flag = UN_SET_FLAG;
			LCD_GoTo_Row_Col(ROW_0, COL_0);
			// this is used to clear the Lcd Without affecting other displayed data
			// as we are using UART full duplex so ther's a case to send while receiving
			LCD_Display_String("Send:           "); 
			LCD_GoTo_Row_Col(ROW_1, COL_0);
			LCD_Display_String("Rec : ");
		}
			
		/* In case there are new data sent from keypad*/
		if (uxBits_KeyPad == KEYPAD_EVENT_BIT && uxBits_BTN != BTN1_EVENT_BIT)
		{
			LCD_GoTo_Row_Col(ROW_0, COL_0);
			LCD_Display_String("Send:");
			LCD_GoTo_Row_Col(ROW_0, (DATA_START_POSITION+gu8_Tx_Loop_counter));
			LCD_Display_Char(gu8_KeyPad_Key);
			//storing data from keypad
			Tx_array[gu8_Tx_Loop_counter] = gu8_KeyPad_Key;
			uxBits_KeyPad = xEventGroupClearBits(KeyPad_Event_Group,KEYPAD_EVENT_BIT); //Clear KeyPad Event
			gu8_Tx_Loop_counter++;
			
		}
		
	   /* In case there are new data sent through UART*/
		if (uxBits_UART == UART_EVENT_BIT)
		{
			uxBits_UART = xEventGroupClearBits( UART_Event_Group , UART_EVENT_BIT); //Clear UART receive data Event

         DIO_Write(GPIOA,BIT0,HIGH);
			LCD_GoTo_Row_Col(ROW_1,COL_0);
			LCD_Display_String("Rec :");	
			LCD_Display_String(gptr_UART_Rec_Data);
			Led_On(LED_0);
			vTaskDelayUntil(&xLastWakeTime, RECEIVING_LED_PERIODICITY);
			Led_Off(LED_0);
         vTaskDelayUntil(&xLastWakeTime, (DISPLAYING_MSG-RECEIVING_LED_PERIODICITY));
		   DIO_Write(GPIOA,BIT0,LOW);
			LCD_GoTo_Row_Col(ROW_1,COL_0);
			//Clear the message without affecting any other displayed values for ex. if we send something while receiving 
 			LCD_Display_String("Rec :               ");  
		}
		 /* In case BTN Is Pressed */
		if (uxBits_BTN == BTN1_EVENT_BIT)
		{
			Re_Init_Flag = SET_FLAG;
		}
		vTaskDelayUntil( &xLastWakeTime,TASKA_LCD_DISPLAY_PERIODICITY);
	}
		
}


/**********************************************************************************************
*                         Creation of task B															       *
***********************************************************************************************/

/*
* TaskB_KYEPAD_GetKey_Code
* Prototype	: static void TaskB_KYEPAD_GetKey_Code( void * pvParameters );
* Description : Task Code for Read Input from Keypad 
* Input       : Pointer to the task’s parameters.
* Output      : None
* In/Out      : None
* Return      : None
*/

static void TaskB_KYEPAD_GetKey_Code( void * pvParameters )
{	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	KeyPad_Event_Group = xEventGroupCreate();
	for( ;; )
	{
		gu8_KeyPad_Key = Get_Pressed_key();
		
		/* this task will be executed Periodically, we want to make sure Our Key that set the event is Between 0 and 9 */
		/* and not any unknown data */
		if (gu8_KeyPad_Key>='0' && gu8_KeyPad_Key <='9' )
		{
			uxBits_KeyPad =xEventGroupSetBits(KeyPad_Event_Group, KEYPAD_EVENT_BIT);
			
		}
		else
		{
			uxBits_KeyPad =xEventGroupClearBits(KeyPad_Event_Group, KEYPAD_EVENT_BIT);
		}
		
		vTaskDelayUntil(&xLastWakeTime,TASKB_KEYPAD_GET_KEY_PERIODICITY);
	}
}


/* 
 * vTasksCreation_KYEPAD_GetKey
 * Prototype	: void vTasksCreation_KYEPAD_GetKey( void );
 * Description : Task Code To create Keypad Read Input Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void Create_TaskB_KYEPAD_GetKey( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
										TaskB_KYEPAD_GetKey_Code,     /* Function that implements the task. */
										"KYEPAD GetKey",				   /* Text name for the task. */
										configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
										( void * ) 1,					   /* Parameter passed into the task. */
										PRIORITY_ONE,					   /* Priority at which the task is created. */
										&xHandle							   /* Used to pass out the created task's handle. */
									);        
}

/**********************************************************************************************
*                         Creation of task C															       *
***********************************************************************************************/
/* 
 * Create_TaskC_Get_UART_Data
 * Prototype	: void Create_TaskC_Get_UART_Data( void );
 * Description : Task Code To create a Task to rec data from UART.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void Create_TaskC_Get_UART_Data( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;
	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
										TaskC_Get_UART_Data_Code,     /* Function that implements the task. */
										"Rec UART Data",              /* Text name for the task. */
										configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
										( void * ) 1,                 /* Parameter passed into the task. */
										PRIORITY_ONE,                 /* Priority at which the task is created. */
										&xHandle                      /* Used to pass out the created task's handle. */
									);										   
}

/* 
 * TaskC_Get_UART_Data_Code
 * Prototype	: static void TaskC_Get_UART_Data_Code( void * pvParameters );
 * Description : Task Code for a task that's responsible for receiving data from UART 
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
static void TaskC_Get_UART_Data_Code( void * pvParameters )
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	UART_Event_Group = xEventGroupCreate();
	for (;;)
	{
		if (gu8_New_Data_Available == SET_FLAG)
		{
			uxBits_UART = xEventGroupSetBits( UART_Event_Group , UART_EVENT_BIT);
			gu8_New_Data_Available = UN_SET_FLAG;
		}
		else
		{
			uxBits_UART = xEventGroupClearBits( UART_Event_Group , UART_EVENT_BIT);
		}
		
		vTaskDelayUntil( &xLastWakeTime,TASKC_UART_DATA_PERIODICITY);
	}
}

/**********************************************************************************************
*                         Creation of task D                											 *
***********************************************************************************************/


/* 
 * TaskD_Get_Button1_State_Code
 * Prototype	: static void TaskD_Get_Button1_State_Code( void *pvParameters );
 * Description : Task Code for monitoring push button 1 state 
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */

static void TaskD_Get_Button1_State_Code( void *pvParameters )
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	uint8_t au8_Button_Status;
	BTN_Event_Group = xEventGroupCreate( );
	for( ;; )
	{		
		au8_Button_Status = pushButtonGetStatus(BTN_0);
		if ( au8_Button_Status == Pressed)
		{
			
			uxBits_BTN = xEventGroupSetBits( BTN_Event_Group, BTN1_EVENT_BIT); //in Case Button1 is pressed and we need to take action, Set Event 
			//make a special end as we don't know the size of the data and
			Tx_array[gu8_Tx_Loop_counter] ='.';
			gu8_Tx_Loop_counter++;
			//in case to use uart send string, this function sends characters until it finds a null
			Tx_array[gu8_Tx_Loop_counter] =NULL;
			UART_Send_String(Tx_array);
			Led_On(LED_1);
		   vTaskDelayUntil( &xLastWakeTime, SENDING_LED_PERIODICITY);
			Led_Off(LED_1);
			gu8_Tx_Loop_counter = NOT_INITIAALIZED;
		}
		else
		{
			uxBits_BTN = xEventGroupClearBits( BTN_Event_Group, BTN1_EVENT_BIT); //Clear Event
		}
		vTaskDelayUntil( &xLastWakeTime,TASKD_GET_BTN1_STATE_PERIDICITY );
	}
}


/* 
 * Create_TaskD_Get_Button1_State
 * Prototype	: void Create_TaskD_Get_Button1_State( void );
 * Description : Task Code To create Push Button 1 Get status Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void Create_TaskD_Get_Button1_State( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;
	xReturned = xTaskCreate(
										TaskD_Get_Button1_State_Code, /* Function that implements the task. */
										"Get BTN1 Status",         	/* Text name for the task. */
										configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
										( void * ) 1,    					/* Parameter passed into the task. */
										PRIORITY_ONE,						/* Priority at which the task is created. */
										&xHandle								/* Used to pass out the created task's handle. */
									);     
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
	Led_Init(LED_1);
	pushButtonInit(BTN_0);
	//UART configurations 
	USART_CFG_t UART1_CFG;
	UART1_CFG.CHAR_DATA_NUMBER = USART_8BIT_DATA;
	UART1_CFG.STOP_BIT_SELECT = USART_1_STOP_BIT;
	UART1_CFG.USART_BAUD_RATE_SELECT = USART_9600_BAUD_RATE;
	UART1_CFG.USART_CLOCK_POLARITY = USART_RISING_TRANSMIT;
	UART1_CFG.USART_MODE = USART_ASYNC_MODE;
	UART1_CFG.USART_PARITY = USART_PARITY_DIS;
	UART1_CFG.USART_RX_TX = USART_RX_TX_Enable;
	UART1_CFG.USART_INTERRUPTS =  USART_RX_Complete_Interrupt_Enable;
	USART_Init2(& UART1_CFG);
	UART_Rx_CallBack_Set(UART_Call_Back_Func);
	KeyPAd_Init();
	vTaskSuspend(NULL);
}


/* 
 * UART_Call_Back_Func
 * Prototype	: static void UART_Call_Back_Func();
 * Description : Code of function that will be executed when UART RX interrupt happen
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
static void UART_Call_Back_Func()
{
	static int au8_Loop_Counter = ZERO;
	
	gptr_UART_Rec_Data [au8_Loop_Counter] = USART_Receive_NO_POLLING();
	
	if (gptr_UART_Rec_Data [au8_Loop_Counter]!= '.')
	{
		au8_Loop_Counter++;
	}
	else
	{
		gptr_UART_Rec_Data [au8_Loop_Counter]='\0';
		gu8_New_Data_Available = SET_FLAG;
		au8_Loop_Counter = ZERO;
		
		
	}
}