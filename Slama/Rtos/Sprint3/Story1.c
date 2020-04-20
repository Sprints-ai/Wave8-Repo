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

/************************************************************************/
/*							GLOBALS                                      */
/************************************************************************/
/*Create DIO Structure*/
st_DIO_Cfg_t st_Dio_init;

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
*Description : Task To Initialize LCD and DIO once then Suspended
..It has the highest priority
*/
void System_Init(void * pvParameters)
{
	
	TickType_t xLastWakeTime;
	while(TRUE)
	{
		
		xCreatedEventGroup = xEventGroupCreate();
		xQueue = xQueueCreate (QUEUE_SIZE,sizeof(uint8_t));
		xQueueKeypad = xQueueCreate (QUEUE_SIZE,sizeof(uint8_t));
		gu8_SharedUARTBufferSize = ZERO;
		gu8_SharedUARTBufferStartIndex = ZERO;
		gu8_SharedKepadBufferStartIndex = ZERO;
		pushButtonInit(BTN_1);
		
		st_uart_init.UART_RxC_Cbk_Function = uart_Callback;
		uart_init(&st_uart_init);
		
		LCD_init(DATA_BITS_4);
		
		vTaskDelayUntil(&xLastWakeTime , LCD_INIT_DELAY);

		vTaskSuspend(NULL);

		
	}
}

void LCD_Task(void)
{
	TickType_t xLastWakeTime;
	const TickType_t delayTicks = TASK_LCD_PERIODICITY;
	EventBits_t	ebValues;
	xLastWakeTime = xTaskGetTickCount();
	vTaskDelayUntil(&xLastWakeTime,LCD_INIT_DELAY);
	uint8_t au8_keyPadVals[16],i=0,u8keypadBufferSize=0,u8_keyPadVal;
	while(TRUE)
	{
		//Check on the event group ely mynfa3sh atba3 tany (ebValues & BLOCKED_MASK)
		ebValues = xEventGroupWaitBits(xCreatedEventGroup,CLR_BTN_MASK,FALSE,FALSE,ZERO);
		//False :// In case yenfa3 atba3
		if (ebValues & CLR_BTN_MASK)
		{
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
		if (xQueueReceive(xQueueKeypad,&u8_keyPadVal,ZERO))
		{
			if(gu8_SharedKepadBufferStartIndex < QUEUE_SIZE)
			{
				LCD_goToRowColumn(LCD_ROW_2,gu8_SharedKepadBufferStartIndex++);
				LCD_displayCharacter(u8_keyPadVal);
			}
				
		}
		//Check on the event group ely mynfa3sh atba3 tany (ebValues & BLOCKED_MASK)
 		ebValues = xEventGroupWaitBits(xCreatedEventGroup,BLOCKED_MASK,FALSE,FALSE,ZERO);
		//False :// In case yenfa3 atba3
		if (!(ebValues & BLOCKED_MASK))
		{
			ebValues = xEventGroupWaitBits(xCreatedEventGroup,ONE_TIME_MASK,FALSE,FALSE,ZERO);
			if((ebValues & ONE_TIME_MASK))
			{
				xEventGroupSetBits(xCreatedEventGroup,BLOCKED_MASK);
			}
			for (; gu8_SharedUARTBufferStartIndex < gu8_SharedUARTBufferSize ; gu8_SharedUARTBufferStartIndex++)
			{
				LCD_goToRowColumn(LCD_ROW_1,gu8_SharedUARTBufferStartIndex);
				LCD_displayCharacter(gau8_SharedUARTBuffer[gu8_SharedUARTBufferStartIndex]);
			}
		
		}
		//men abl men el btn wla el lcd
		
		vTaskDelayUntil(&xLastWakeTime,delayTicks);
	}
	
}
void UART_Task(void)
{
	TickType_t xLastWakeTime;
	const TickType_t delayTicks = TASK_UART_PERIODICITY;
	xLastWakeTime = xTaskGetTickCount();
	vTaskDelayUntil(&xLastWakeTime,LCD_INIT_DELAY);
	uint8_t au8_Buffer[QUEUE_SIZE],bufferSize=ZERO;
	uint8_t i=ZERO;
	EventBits_t ebValues;
	xEventGroupClearBits(xCreatedEventGroup,ONE_TIME_MASK);
	xEventGroupClearBits(xCreatedEventGroup,BLOCKED_MASK);
	while(TRUE)
	{
		
		//Check on the event group if not set
		ebValues = xEventGroupWaitBits(xCreatedEventGroup,BLOCKED_MASK,FALSE,FALSE,ZERO);
		//False :// In case yenfa3 atba3
		if (!(ebValues & BLOCKED_MASK))
		{
			
			bufferSize = uxQueueMessagesWaiting(xQueue);
			if(xQueueReceive(xQueue,au8_Buffer,ZERO))
			{
				
				for (i=0;i<bufferSize;i++)
				{
					if(au8_Buffer[i]=='\r')
					{
						xEventGroupSetBits(xCreatedEventGroup,ONE_TIME_MASK);
						break;
					}
					else
					{
						gau8_SharedUARTBuffer[gu8_SharedUARTBufferSize++] = au8_Buffer[i];
						if (gu8_SharedUARTBufferSize== QUEUE_SIZE)
						{
							xEventGroupSetBits(xCreatedEventGroup,ONE_TIME_MASK);
							break;
						}
						else
						{
							xEventGroupClearBits(xCreatedEventGroup,ONE_TIME_MASK);//bn3ml el str da mra kman fel clear
						}
						
					}
				}
			}
		}
		vTaskDelayUntil(&xLastWakeTime,delayTicks);
	}
}

/*
 * Task: BTN_Task
 * Task description: This Task used for detecting whether the button is pressed
 *                   and released to take action with the led
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
		//PORTC_DATA=200;
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
	
	xQueueSendFromISR( xQueue, &uart_reception, &xHigherPriorityTaskWoken );
}