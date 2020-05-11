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
#define TASK_KEYPAD_PERIODICITY                                 (80)
#define TASK_LED_PERIODICITY									(100)

/*Priorities*/
#define PERIORITY_1                                             (1)
#define PERIORITY_2                                             (2)
#define PERIORITY_3                                             (3)
#define PERIORITY_4                                             (4)
#define PERIORITY_5                                             (5)
#define PERIORITY_6												(6)

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
#define ROW2_CLEAR_TIME											(10)

/*LED Defines*/
#define LED_OFF_COUNT											(3)
#define LED_ON_COUNT											(0)
#define LED2_OFF_COUNT											(5)

/*Event Group Macro*/
#define ONE_TIME_MASK                                           (0x01)
#define BLOCKED_MASK                                            (0x02)
#define ENTR_BTN_MASK                                           (0x04)
#define KEYPAD_MASK                                             (0x08)
#define QUEUE_MASK												(0x10)

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
QueueHandle_t xQueueUart;
QueueHandle_t xQueueKeypad;
QueueHandle_t xQueueRec;

/*Handles*/
TaskHandle_t Sys_Init_Handle;
TaskHandle_t UART_Handle;
TaskHandle_t LCD_Handle ;
TaskHandle_t BTN_Handle ;
TaskHandle_t KeyPad_Handle ;
TaskHandle_t LED_Handle;


uint8_t gu8_SharedKepadBufferStartIndex;

uint8_t Led2_cnt = 0;

st_DIO_Cfg_t str_Dio;

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
		xQueueUart = xQueueCreate (QUEUE_SIZE,sizeof(uint8_t));
		xQueueKeypad = xQueueCreate (QUEUE_SIZE,sizeof(uint8_t));
		xQueueRec = xQueueCreate(QUEUE_SIZE , sizeof(uint8_t));
		
		gu8_SharedKepadBufferStartIndex = ZERO;
		
		/*init LED1,2*/
		str_Dio.dir = OUTPUT;
		str_Dio.GPIO = GPIOB;
		str_Dio.pins = PIN4;
		
		DIO_init(&str_Dio);
		
		str_Dio.dir = OUTPUT;
		str_Dio.GPIO = GPIOB;
		str_Dio.pins = PIN5;
		
		DIO_init(&str_Dio);
		
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
	
	/*2 Sec Cnt*/
	uint8_t au8_cnt = 0;
	uint8_t u8_RecUart = 0;
	
	xLastWakeTime = xTaskGetTickCount();
	vTaskDelayUntil(&xLastWakeTime,LCD_INIT_DELAY);
	uint8_t au8_keyPadVals[16],i=0,u8keypadBufferSize=0,u8_keyPadVal;
	
	while(TRUE)
	{
		/*Read Event Group Value*/
		ebValues = xEventGroupWaitBits(xCreatedEventGroup,(ENTR_BTN_MASK | QUEUE_MASK) ,FALSE,FALSE,ZERO);
		
		if (ebValues & ENTR_BTN_MASK)
		{
			/*Clear Screen*/
			LCD_displayStringRowColumn(0,0,"                 ");
			
			gu8_SharedKepadBufferStartIndex = ZERO;
			xEventGroupClearBits(xCreatedEventGroup,BLOCKED_MASK);
			xEventGroupClearBits(xCreatedEventGroup,ONE_TIME_MASK);
			xEventGroupClearBits(xCreatedEventGroup,ENTR_BTN_MASK);
		}
		
		/*If any data Received in Q then write it over LCD*/
		while (xQueueReceive(xQueueKeypad,&u8_keyPadVal,ZERO))
		{
			if(gu8_SharedKepadBufferStartIndex < QUEUE_SIZE)
			{
				/*Print pressed key Val*/
				LCD_goToRowColumn(LCD_ROW_1,gu8_SharedKepadBufferStartIndex++);
				
				xQueueSend(xQueueUart , &u8_keyPadVal , 0);
				
				LCD_displayCharacter(u8_keyPadVal);
			}	
		}
		
		if(ebValues & QUEUE_MASK)
		{
			/*Write in Row 2*/
			LCD_goToRowColumn(LCD_ROW_2 , ZERO);
			au8_cnt++;
			
			while(xQueueReceive(xQueueRec , &u8_RecUart , ZERO))
			{	
				/*write char in LCD*/
				LCD_displayCharacter(u8_RecUart);
			}
			if(au8_cnt == ROW2_CLEAR_TIME)
			{
				LCD_displayStringRowColumn(LCD_ROW_2, ZERO ,"                    ");
				Led2_cnt = 0;
				au8_cnt = 0;
				
				/*Clear Event*/
				xEventGroupClearBits(xCreatedEventGroup , QUEUE_MASK);
			}
		}
		vTaskDelayUntil(&xLastWakeTime,delayTicks);
	}	
}


void UART_Task(void)
{
	TickType_t xLastWakeTime;
	const TickType_t delayTicks = TASK_UART_PERIODICITY;
	xLastWakeTime = xTaskGetTickCount();
	
	uint8_t u8_keyPadVal = ZERO;
	
	/*Create Event group Val*/
	EventBits_t	ebValues;
	
	while(1){
		
		//Check on the event group ely mynfa3sh atba3 tany (ebValues & BLOCKED_MASK)
		ebValues = xEventGroupWaitBits(xCreatedEventGroup,ENTR_BTN_MASK,FALSE,FALSE,ZERO);
		
		/*Check for Btn*/
		if (ebValues & ENTR_BTN_MASK)
		{	
			/*Send all data in Q thru uart*/
			while (xQueueReceive(xQueueUart,&u8_keyPadVal,ZERO))
			{
					uart_tx_send(u8_keyPadVal);
			}
		}
		
		//deQ and send while Enter is pressed
		vTaskDelayUntil(&xLastWakeTime,delayTicks);
		}
		
}

void LeD_tasks(void)
{
	TickType_t xLastWakeTime;
	const TickType_t delayTicks = TASK_LED_PERIODICITY;
	xLastWakeTime = xTaskGetTickCount();
	
	/*LED1,2 Flags*/
 	uint8_t Led1_cnt = 0;
	
	/*Create Event group Val*/
	EventBits_t	ebValues;
	
	while(1)
	{
		
		//Check on the event group ely mynfa3sh atba3 tany (ebValues & BLOCKED_MASK)
		ebValues = xEventGroupWaitBits(xCreatedEventGroup,(ENTR_BTN_MASK | QUEUE_MASK),FALSE,FALSE,ZERO);
		
		/*Check if Btn pressed*/
		if ((ebValues & ENTR_BTN_MASK) && Led1_cnt == LED_ON_COUNT)
		{
			/*Cnt is used to keep led on fro Req.Time*/
			Led1_cnt++;
			
			/*Turn LED On*/
			DIO_Write(GPIOB , PIN4 , HIGH);	
		}
		
		if(Led1_cnt != LED_ON_COUNT)
		{	
			
			/*Increment Led cnt to reach the req time*/
			Led1_cnt++;
			
			/*time checking*/
			if(Led1_cnt == LED_OFF_COUNT)
			{
				DIO_Write(GPIOB , PIN4 , LOW);
				Led1_cnt = 0;
			}	
		}
		
		/*Check if Btn pressed*/
		if ((ebValues & QUEUE_MASK))
		{
			if(Led2_cnt < LED2_OFF_COUNT)
			{
				/*Turn LED On*/
				DIO_Write(GPIOB , PIN5 , HIGH);
				
				/*Increment Led cnt to reach the req time*/
				Led2_cnt++;
			}
			else
			{
				DIO_Write(GPIOB , PIN5 , LOW);
			}
		}
		vTaskDelayUntil(&xLastWakeTime , delayTicks);	
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
	xEventGroupClearBits(xCreatedEventGroup,ENTR_BTN_MASK);
	
	while(1)
	{
		// In case the btn is pressed
		if(pushButtonGetStatus(BTN_1) == Pressed)
		{
			xEventGroupSetBits(xCreatedEventGroup,ENTR_BTN_MASK);
		}
		else
		{
			//do nothing
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
	xTaskCreate(LeD_tasks,"Led_Task" , STACK_100_WORD , (void * ) NO_PARAMETERS ,PERIORITY_2,&LED_Handle );
	xTaskCreate(UART_Task,"UART" , STACK_100_WORD , (void * ) NO_PARAMETERS ,PERIORITY_3,&UART_Handle );
	xTaskCreate(KeyPad_Task,"Keypad" , STACK_100_WORD , (void * ) NO_PARAMETERS ,PERIORITY_4,&KeyPad_Handle );
	xTaskCreate(BTN_Task,"BTN" , STACK_100_WORD , (void * ) NO_PARAMETERS ,PERIORITY_5,&BTN_Handle );
	xTaskCreate(System_Init,"SysIn" , STACK_100_WORD , (void * ) NO_PARAMETERS , PERIORITY_6 , &Sys_Init_Handle);
	
	/* Start Scheduler */
	vTaskStartScheduler();
}

/*Uart Reception ISR*/
void uart_Callback()
{
	char uart_reception = 0;
	
	BaseType_t xHigherPriorityTaskWoken;

	/* We have not woken a task at the start of the ISR. */
	xHigherPriorityTaskWoken = pdFALSE;
	
	uart_reception = uart_rx();
	
	xEventGroupSetBits(xCreatedEventGroup , QUEUE_MASK);
	
	xQueueSendFromISR( xQueueRec, &uart_reception, &xHigherPriorityTaskWoken );
}

