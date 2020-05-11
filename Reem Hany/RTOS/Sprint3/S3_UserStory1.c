#include "Services/FreeRTOS/FreeRTOS.h"
#include "Services/FreeRTOS/task.h"
#include "Services/FreeRTOS/queue.h"
#include "MCAL/DIO/DIO.h"
#include "MCAL/registers.h"
#include "MCAL/UART/uart.h"
#include "HAL/LCD/LCD.h"
#include "HAL/PushButton/pushButton.h"
#include "HAL/Keypad/my_keypad.h"
#include "Services/FreeRTOS/event_groups.h"

/************************************************************************/
/*							DEFINES                                     */
/************************************************************************/
/*Periodicity*/
#define TASK_LCD_PERIODICITY                                    200
#define TASK_UART_PERIODICITY                                   10
#define TASK_BTN_PERIODICITY                                    50
#define TASK_KEYPAD_PERIODICITY                                 130

/*Priorities*/
#define PERIORITY_1                                             (1)
#define PERIORITY_2                                             (2)
#define PERIORITY_3                                             (3)
#define PERIORITY_4                                             (4)
#define PERIORITY_5                                             (5)

/*Flags Macros*/
#define BTN_HIGH                                                (1)
#define BTN_LOW                                                 (0)

/*LED Control*/
#define BTN2_CONTROL                                            (2)
#define BTN1_CONTROL                                            (1)
#define NO_CONTROL                                              (0)

/*Task Parameters Defines*/
#define STACK_100_WORD                                          (100)
#define NO_PARAMETERS                                           (1)

/*LCD Defines*/
#define NULL_CHAR                                               ('0')
#define MAX_CHAR_NUM                                            (7)
#define LCD_INIT_DELAY                                          (2)
#define LCD_ROW_1                                               (0)
#define LCD_ROW_2                                               (1)

/*Event Group Macro*/
#define ONE_TIME_MASK                                           (0x01)
#define BLOCKED_MASK                                            (0x02)
#define CLR_BTN_MASK                                            (0x04)
#define KEYPAD_MASK                                             (0x08)

/*Queue Macro*/
#define QUEUE_SIZE                                              (16)
/*Common Struct for variables*/
typedef struct
{
	uint8_t BTN1_Flag;
	uint8_t BTN2_Flag;
	uint8_t LED_CNTROL;
}str_Flags_t;

/************************************************************************/
/*							GLOBALS                                      */
/************************************************************************/
/*Create DIO Structure*/
st_DIO_Cfg_t st_Dio_init;

str_Flags_t str_Flags;

/*Event group Variables*/
EventGroupHandle_t xCreatedEventGroup;

/*Queue Variables*/
QueueHandle_t xQueue;
QueueHandle_t xQueueKeypad;

/*Handles*/
TaskHandle_t Sys_Init_Handle;
TaskHandle_t UART_Handle;
TaskHandle_t LCD_Handle ;
TaskHandle_t BTN_Handle ;
TaskHandle_t KeyPad_Handle ;

uint8_t gau8_SharedUARTBuffer[20];
uint8_t gu8_SharedUARTBufferStartIndex;
uint8_t gu8_SharedUARTBufferSize;
uint8_t gu8_SharedKepadBufferStartIndex;


/************************************************************************/
/*                     Static prototypes                                */
/************************************************************************/
void uart_Callback();

/************************************************************************/
/*								APIS                                    */
/************************************************************************/
/*SystemInit
*Description : Task To Initialize Globals and used Drivers once then Suspended
* It has the highest priority
*/
void System_Init(void * pvParameters)
{
	
	TickType_t xLastWakeTime;
	while(TRUE)
	{
		/*Initialize Globals*/
		xCreatedEventGroup = xEventGroupCreate();
		xQueue = xQueueCreate (QUEUE_SIZE,sizeof(uint8_t));
		xQueueKeypad = xQueueCreate (QUEUE_SIZE,sizeof(uint8_t));
		gu8_SharedUARTBufferSize = ZERO;
		gu8_SharedUARTBufferStartIndex = ZERO;
		gu8_SharedKepadBufferStartIndex = ZERO;
		
		/*Initialize APIS*/
		pushButtonInit(BTN_1);
		
		st_uart_init.UART_RxC_Cbk_Function = uart_Callback;
		uart_init(&st_uart_init);
		
		LCD_init(DATA_BITS_4);
		
		vTaskDelayUntil(&xLastWakeTime , LCD_INIT_DELAY);

		vTaskSuspend(NULL);

		
	}
}
/*
 * Task: LCD_Task
 * Task description: This Task used for : 1- Displaying  the Data received from Keypad and UART 
 *                                        2- Clearing the this LCD and reseting the system on pressing the clear button
 */
void LCD_Task(void)
{
	TickType_t xLastWakeTime;
	const TickType_t delayTicks = TASK_LCD_PERIODICITY;
	EventBits_t	ebValues;
	xLastWakeTime = xTaskGetTickCount();
	vTaskDelayUntil(&xLastWakeTime,LCD_INIT_DELAY);
	uint8_t au8_keyPadVals[QUEUE_SIZE],i=ZERO,u8keypadBufferSize=ZERO,u8_keyPadVal;
	while(TRUE)
	{
		/*Check whether clear button is pressed or not*/
		ebValues = xEventGroupWaitBits(xCreatedEventGroup,CLR_BTN_MASK,FALSE,FALSE,ZERO);
		if (ebValues & CLR_BTN_MASK)
		{
			//In case clear button is pressed, clear the LCD and reset the system
			LCD_clearScreen();
			xQueueReset(xQueue);
			xQueueReset(xQueueKeypad);
			gu8_SharedUARTBufferSize        = ZERO;
			gu8_SharedUARTBufferStartIndex  = ZERO;
			gu8_SharedKepadBufferStartIndex = ZERO;
			xEventGroupClearBits(xCreatedEventGroup,BLOCKED_MASK);
			xEventGroupClearBits(xCreatedEventGroup,ONE_TIME_MASK);
			xEventGroupClearBits(xCreatedEventGroup,CLR_BTN_MASK);
		}
		
		/*Check whether there is an input from the keypad*/
		if (xQueueReceive(xQueueKeypad,&u8_keyPadVal,ZERO))
		{
			if(gu8_SharedKepadBufferStartIndex < QUEUE_SIZE)
			{
				LCD_goToRowColumn(LCD_ROW_2,gu8_SharedKepadBufferStartIndex++);
				LCD_displayCharacter(u8_keyPadVal);
			}
				
		}
		/*Check Whether the LCD Row 1 is Blocked or not (it is blocked when the LCD reaches its limit)*/
 		ebValues = xEventGroupWaitBits(xCreatedEventGroup,BLOCKED_MASK,FALSE,FALSE,ZERO);
		if (!(ebValues & BLOCKED_MASK))
		{
			/*Check whether it is the last time to write on the LCD and then blocked it or not*/
			ebValues = xEventGroupWaitBits(xCreatedEventGroup,ONE_TIME_MASK,FALSE,FALSE,ZERO);
			if((ebValues & ONE_TIME_MASK))
			{
				xEventGroupSetBits(xCreatedEventGroup,BLOCKED_MASK);
			}
			/*Display the Data recieved from the UART task on the LCD*/
			for (; gu8_SharedUARTBufferStartIndex < gu8_SharedUARTBufferSize ; gu8_SharedUARTBufferStartIndex++)
			{
				LCD_goToRowColumn(LCD_ROW_1,gu8_SharedUARTBufferStartIndex);
				LCD_displayCharacter(gau8_SharedUARTBuffer[gu8_SharedUARTBufferStartIndex]);
			}
		
		}
		
		vTaskDelayUntil(&xLastWakeTime,delayTicks);
	}
	
}
/*
 * Task: UART_Task
 * Task description: This Task used for saving the UART received values and send it to the LCD
 */
void UART_Task(void)
{
	TickType_t xLastWakeTime;
	const TickType_t delayTicks = TASK_UART_PERIODICITY;
	xLastWakeTime = xTaskGetTickCount();
	vTaskDelayUntil(&xLastWakeTime,LCD_INIT_DELAY);
	uint8_t u8_UARTval,bufferSize=ZERO;
	uint8_t i=ZERO;
	EventBits_t ebValues;
	xEventGroupClearBits(xCreatedEventGroup,ONE_TIME_MASK);
	xEventGroupClearBits(xCreatedEventGroup,BLOCKED_MASK);
	while(TRUE)
	{
		
		/*Check Whether the LCD Row 1 is Blocked or not (it is blocked when the LCD reaches its limit)*/
		ebValues = xEventGroupWaitBits(xCreatedEventGroup,BLOCKED_MASK,FALSE,FALSE,ZERO);
		if (!(ebValues & BLOCKED_MASK))
		{
			/*Check Whether the LCD Row 1 is Blocked or not (it is blocked when the LCD reaches its limit)*/
			while(xQueueReceive(xQueue,&u8_UARTval,ZERO))
			{
				gau8_SharedUARTBuffer[gu8_SharedUARTBufferSize++] = u8_UARTval;
				/*Check Whether the LCD Row 1 reaches its limit*/
				if (gu8_SharedUARTBufferSize== QUEUE_SIZE)
				{
					xEventGroupSetBits(xCreatedEventGroup,ONE_TIME_MASK);//Set the event that LCD will display the data one more time
					break;
				}
				else
				{
					xEventGroupClearBits(xCreatedEventGroup,ONE_TIME_MASK);
				}
				
			}
		}
		vTaskDelayUntil(&xLastWakeTime,delayTicks);
	}
}

/*
 * Task: BTN_Task
 * Task description: This Task used for detecting whether the clear button is pressed
 */
void BTN_Task(void)
{
	TickType_t xLastWakeTime;
	static uint8_t u8ledperiodicityCounter;
	xEventGroupClearBits(xCreatedEventGroup,CLR_BTN_MASK);
	while(1)
	{
		// In case the btn is pressed
		if(pushButtonGetStatus(BTN_1) == Pressed)
		{
			xEventGroupSetBits(xCreatedEventGroup,CLR_BTN_MASK);
		}
		else
		{
			xEventGroupClearBits(xCreatedEventGroup,CLR_BTN_MASK);

		}
		vTaskDelayUntil( &xLastWakeTime, TASK_BTN_PERIODICITY );
	}
}

void KeyPad_Task(void * pvParameters)
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = TASK_KEYPAD_PERIODICITY;
	uint8_t keyVal;
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	
	while(TRUE)
	{
		/*Getting input from keypad and save it in the keypad queue*/
		keyVal =Key_Pressed();
		
		if(keyVal != DEFAULT_CHAR){
			
			keyVal = keyVal + NULL_CHAR;
			
			xQueueSend (xQueueKeypad,&keyVal,ZERO);
			
		}
		vTaskDelayUntil(&xLastWakeTime , xFrequency);
		
	}
}

int main(void)
{

	
	/*Task Creation*/
	xTaskCreate(LCD_Task,"LCD" , STACK_100_WORD , (void * ) NO_PARAMETERS ,PERIORITY_1,&LCD_Handle );
	xTaskCreate(UART_Task,"UART" , STACK_100_WORD , (void * ) NO_PARAMETERS ,PERIORITY_2,&UART_Handle );
	xTaskCreate(KeyPad_Task,"Keypad" , STACK_100_WORD , (void * ) NO_PARAMETERS ,PERIORITY_3,&KeyPad_Handle );
	xTaskCreate(BTN_Task,"BTN" , STACK_100_WORD , (void * ) NO_PARAMETERS ,PERIORITY_4,&BTN_Handle );
	xTaskCreate(System_Init,"SysIn" , STACK_100_WORD , (void * ) NO_PARAMETERS , PERIORITY_5 , &Sys_Init_Handle);

	/* Start Scheduler */
	vTaskStartScheduler();
}

void uart_Callback()
{
	char uart_reception = 0;
	
	BaseType_t xHigherPriorityTaskWoken;
	
	

	/* We have not woken a task at the start of the ISR. */
	xHigherPriorityTaskWoken = pdFALSE;
	
	uart_reception = uart_rx();
	//Saving received values in the queue
	xQueueSendFromISR( xQueue, &uart_reception, &xHigherPriorityTaskWoken );
}