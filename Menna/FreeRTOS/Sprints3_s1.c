/*
 * Sprints3.c
 *
 * Created: 4/20/2020 8:14:40 PM
 *  Author: MENNA
 */ 


#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "keypad.h"
#include "DIO.h"
#include "pushButton.h"
#include "UART.h"
#include "event_groups.h"

#include "LCD.h"
#define STACK_SIZE 80


SemaphoreHandle_t xSemaphore;
EventGroupHandle_t x_LCD_EventGroup;

/******sprint 2 story1 variables **************/
TaskHandle_t xHandle_initTask_s3_s1 = NULL;
TaskHandle_t xHandle_Task_A_s3_s1 = NULL ;
TaskHandle_t xHandle_Task_B_s3_s1 = NULL ;
TaskHandle_t xHandle_Task_C_s3_s1 = NULL ;
TaskHandle_t xHandle_Task_D_s3_s1 = NULL ;


QueueHandle_t xQueue_keypad_LCD ;
QueueHandle_t xQueue_UART_LCD ;


/************ UART ISR CallBack Function   ************/

void UART_ISR_RXcbf(void){
	EventBits_t uxBits;
	
	uxBits = xEventGroupSetBits(
	x_LCD_EventGroup,    /* The event group being updated. */
	BIT0);
	
}

/************************************************************************/
/***********************   sprint 3   ***********************************/
/************************************************************************/


/************************************************************************/
/*                         story 1                                      */
/************************************************************************/


/* Tasks to be created. */
void vTask_initTask_s3_s1 (void * pvParameters)
{
	/* The parameter value is expected to be 1 as 1 is passed in the
	pvParameters value in the call to xTaskCreate() below. */
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	
	pushButtonInit(BTN_0);
	LCD_init();
	
	UART_cfg UART1 ;
	UART1.baudrate   = 9600;
	UART1.dataBits   = UART_Bits_8;
	UART1.stopBits   = StopBits_1;
	UART1.parity     = No_Parity;
	UART1.sampleEdge = RisingEdg;
	UART1.uartSync   = UART_Async;
	UART1.mode       = UART_RX;
	UART1.uartInterrupts = OnRx ;
	UART_SetRX(UART_ISR_RXcbf);
	UART_Init(&UART1);
	
	
	for( ;; )
	{
		vTaskDelete( xHandle_initTask_s3_s1 );
		
	}
	
}

/*task responsible of the display and clear of LCD */

void vTask_A_s3_s1(void * pvParameters){
	
	const TickType_t xFrequency = 100 ;
	TickType_t xLastWakeTime;
	
	uint8_t au8_CharRec_LCD;
	static uint8_t au8_Col_number_keypad = COL1 ;
	static uint8_t au8_Col_number_UART = COL1 ;

	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	
	for( ;; )
	{
		/************************ recieving char from keypad  from task B ***************/
		
		
		if( xQueueReceive( xQueue_keypad_LCD,&( au8_CharRec_LCD ),( TickType_t )0 ) == pdPASS )
		{
			
			LCD_gotoRowColumn(ROW1,au8_Col_number_keypad);
			au8_Col_number_keypad++;

			LCD_displayChar(au8_CharRec_LCD);

	/************************ recieving char from UART  from task B ***************/
		}else if( xQueueReceive( xQueue_UART_LCD,&( au8_CharRec_LCD ),( TickType_t )0 ) == pdPASS )
		{
			LCD_gotoRowColumn(ROW2,au8_Col_number_UART);
			LCD_displayChar(au8_CharRec_LCD);
			au8_Col_number_UART++;
/************************ push button is pressed clear LCD ***************/
			}else if(xSemaphoreTake( xSemaphore, 0 )== pdTRUE ){
			
			LCD_clear();
			au8_Col_number_UART= ZERO;
			au8_Col_number_keypad = ZERO ;
			
			
		}
		
		vTaskDelayUntil( & xLastWakeTime,xFrequency);

	}
}

/* keypad task */

void vTask_B_s3_s1(void * pvParameters){
	
	const TickType_t xFrequency = 150 ;
	TickType_t xLastWakeTime;
	
	uint8_t au8_key_pressed ;
	uint16_t au16_char_ascci_value ;
	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	
	for( ;; )
	{
		
		KeyPad_getPressedKey(&au8_key_pressed);
		
		au16_char_ascci_value = au8_key_pressed + 48 ;
		/* if no button of keypad is pressed it sends 255 */
		if (au8_key_pressed !=255)
		{
			xQueueSend( xQueue_keypad_LCD ,( void * ) &au16_char_ascci_value, ( TickType_t ) ZERO );
		}	
		
		vTaskDelayUntil( & xLastWakeTime,xFrequency);		
	}
		
}

/*UART recieve task */

void vTask_C_s3_s1(void * pvParameters){
	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	
	const TickType_t xFrequency = 20;
	TickType_t xLastWakeTime;
	EventBits_t uxBits;
	uint8_t au8_UART_recived_data ;
	
	for( ;; )
	{
		//xTaskNotify( xHandle_Task_A_s2, (uint32_t)str , eSetValueWithOverwrite  );
		
		uxBits = xEventGroupWaitBits(
		x_LCD_EventGroup ,   /* The event group being tested. */
		BIT0, /* The bits within the event group to wait for. */
		pdTRUE,        /* BIT_0 & BIT_4 should be cleared before returning. */
		pdFALSE,       /* Don't wait for both bits, either bit will do. */
		0 );/* Wait a maximum of 100ms for either bit to be set. */
		
		if( ( uxBits & ( BIT0 ) ) == ( BIT0 ) )
		{
			/* xEventGroupWaitBits() returned because bits were set. */
			au8_UART_recived_data = UART_Read();
			
			/*send to task A using queue */

			xQueueSend( xQueue_UART_LCD ,( void * ) &au8_UART_recived_data, ( TickType_t ) 0 );

			/* Clear bit 0 in xEventGroup. */
			
			uxBits = xEventGroupClearBits(x_LCD_EventGroup,  BIT0 );/* The bits being cleared. */

		}
		
		vTaskDelayUntil( & xLastWakeTime,xFrequency);

	}
	
}
/*pushbutton task*/

void vTask_D_s3_s1(void * pvParameters){
	
	const TickType_t xFrequency = 50 ;
	TickType_t xLastWakeTime;
	
	uint8_t au8_button_status ;
	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

	for( ;; )
	{
		
		pushButtonGetStatus(BTN_0 , &au8_button_status) ;
		
		if (au8_button_status==Pressed){
			/**give semaphore */
			xSemaphoreGive( xSemaphore );
			
		}
		vTaskDelayUntil( & xLastWakeTime,xFrequency);
	}
	
}



void sprint3_Story1( void )
{
	BaseType_t xReturned_initTask;
	BaseType_t xReturned_Task_A;
	BaseType_t xReturned_Task_B;
	BaseType_t xReturned_Task_C;
	BaseType_t xReturned_Task_D;
	
	xSemaphore = xSemaphoreCreateBinary();
	xQueue_keypad_LCD = xQueueCreate( 16, sizeof( uint16_t ) );
	xQueue_UART_LCD = xQueueCreate( 16, sizeof( uint8_t ) );

	
	/* Declare a variable to hold the created event group. */
	
	x_LCD_EventGroup = xEventGroupCreate();
	
	
	/***************************** init task ********************************/

	/* Create the task, storing the handle. */
	xReturned_initTask = xTaskCreate(
	vTask_initTask_s3_s1,       /* Function that implements the task. */
	"M",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	3	,			/* Priority at which the task is created. */
	&xHandle_initTask_s3_s1 );      /* Used to pass out the created task's handle. */
	
	/***************************** task A ********************************/
	
	xReturned_Task_A = xTaskCreate(
	vTask_A_s3_s1 ,       /* Function that implements the task. */
	"A",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	2	,			/* Priority at which the task is created. */
	&xHandle_Task_A_s3_s1 );      /* Used to pass out the created task's handle. */

	/***************************** task B ********************************/
	
	
	xReturned_Task_B = xTaskCreate(
	vTask_B_s3_s1,       /* Function that implements the task. */
	"B",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	1	,			/* Priority at which the task is created. */
	&xHandle_Task_B_s3_s1 );      /* Used to pass out the created task's handle. */
	
	
	/***************************** task C ********************************/
	
	
	xReturned_Task_C = xTaskCreate(
	vTask_C_s3_s1,       /* Function that implements the task. */
	"C",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	3	,			/* Priority at which the task is created. */
	&xHandle_Task_C_s3_s1 );      /* Used to pass out the created task's handle. */


	/***************************** task D ********************************/
	
	
	xReturned_Task_D = xTaskCreate(
	vTask_D_s3_s1,       /* Function that implements the task. */
	"D",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	3	,			/* Priority at which the task is created. */
	&xHandle_Task_D_s3_s1 );      /* Used to pass out the created task's handle. */


}
