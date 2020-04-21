/*
* main.c
*
* Created: 4/16/2020 3:38:42 AM
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

extern sprint2_Story1();
extern Story1();
extern Story3();
extern sprint3_Story1();

SemaphoreHandle_t xSemaphore;
EventGroupHandle_t x_LCD_EventGroup;

/******sprint 3 final project variables **************/

TaskHandle_t xHandle_initTask_s3_f = NULL;
TaskHandle_t xHandle_Task_A_s3_f = NULL ;
TaskHandle_t xHandle_Task_B_s3_f = NULL ;
TaskHandle_t xHandle_Task_C_s3_f = NULL ;
TaskHandle_t xHandle_Task_F_s3_f = NULL ;

TaskHandle_t xHandle_Task_D_s3_f = NULL ;
TaskHandle_t xHandle_Task_E_s3_f = NULL ;



QueueHandle_t xQueue_keypad_LCD ;
QueueHandle_t xQueue_keypad_UART ;

QueueHandle_t xQueue_UART_LCD ;



/************ UART ISR CallBack Function   ************/

void UART_ISR_RXcbf_f(void){
	EventBits_t uxBits;
	
	uxBits = xEventGroupSetBits(
	x_LCD_EventGroup,    /* The event group being updated. */
	BIT0|BIT1);
	
}

/************************************************************************/
/***********************   sprint 3   ***********************************/
/************************************************************************/


/************************************************************************/
/*                         final project                                */
/************************************************************************/


/* Tasks to be created. */

void vTask_initTask_s3_f (void * pvParameters)
{
	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	/*initialize led pins*/
	DIO_Cfg_s Toggle_LED_init ;
	Toggle_LED_init.dir = OUTPUT ;
	Toggle_LED_init.GPIO = GPIOB ;
	Toggle_LED_init .pins = BIT7|BIT6 ;
	DIO_init(&Toggle_LED_init);
	pushButtonInit(BTN_0);
	LCD_init();
	
	UART_cfg UART1 ;
	UART1.baudrate   = 9600;
	UART1.dataBits   = UART_Bits_8;
	UART1.stopBits   = StopBits_1;
	UART1.parity     = No_Parity;
	UART1.sampleEdge = RisingEdg;
	UART1.uartSync   = UART_Async;
	UART1.mode       = UART_Transceiver;
	UART1.uartInterrupts = OnRx ;
	UART_SetRX(UART_ISR_RXcbf_f);
	UART_Init(&UART1);
	
	
	for( ;; )
	{
		vTaskDelete( xHandle_initTask_s3_f );
		
	}
	
}

/* LCD task */
void vTask_A_s3_f(void * pvParameters){
	
	const TickType_t xFrequency = 100 ;
	TickType_t xLastWakeTime;
	
	uint8_t au8_CharRec_LCD;
	static uint8_t Col_number_keypad = COL1 ;
	static uint8_t Col_number_UART = COL1 ;
	static sint8_t as8_UART_msg_counter ;

	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	
	for( ;; )
	{
		/******************************recieving char from keypad  from task B***************/
		
		if( xQueueReceive( xQueue_keypad_LCD,&( au8_CharRec_LCD ),( TickType_t )0 ) == pdPASS )
		{
			LCD_gotoRowColumn(ROW1,Col_number_keypad);
			Col_number_keypad++;
			LCD_displayChar(au8_CharRec_LCD);

		}
		/******************************  recieving char from UART     ***************/

		else if( xQueueReceive( xQueue_UART_LCD,&( au8_CharRec_LCD ),( TickType_t )0 ) == pdPASS )
		{
			LCD_gotoRowColumn(ROW2,Col_number_UART);
			LCD_displayChar(au8_CharRec_LCD);
			Col_number_UART++;
			as8_UART_msg_counter = 20 ;
			

		}
		else if(xSemaphoreTake( xSemaphore, 0 )== pdTRUE )
		{
		/******** clear keypad msg on the upper row of LCD *******/
		LCD_gotoRowColumn(ROW1,COL1);
		LCD_displayString("                ");
		Col_number_keypad = ZERO ;
				
		}
		/***** check the the counter of the display UART msg counter to clear after 2sec ********/
		if (as8_UART_msg_counter==0)
		{
			LCD_gotoRowColumn(ROW2,COL1);
			LCD_displayString("                ");
			Col_number_UART= ZERO ;
		}
		as8_UART_msg_counter--;
		vTaskDelayUntil( & xLastWakeTime,xFrequency);

	}
}

 /****************** keypad task ******************************/

void vTask_B_s3_f(void * pvParameters){
	
	const TickType_t xFrequency = 150 ;
	TickType_t xLastWakeTime;
	
	uint8_t au8_key_pressed ;
	uint16_t au16_char_ascci_value ;
	
	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	
	for( ;; )
	{
		
		KeyPad_getPressedKey(&au8_key_pressed);
		
		au16_char_ascci_value = au8_key_pressed + 48 ;
		if (au8_key_pressed !=255)
		{
			xQueueSend( xQueue_keypad_LCD ,( void * ) &au16_char_ascci_value, ( TickType_t ) 0 );
			xQueueSend( xQueue_keypad_UART ,( void * ) &au16_char_ascci_value, ( TickType_t ) 0 );

		}
		
		
		vTaskDelayUntil( & xLastWakeTime,xFrequency);
		
	}
	
	
}


 /****************** UART recieve task ******************************/

void vTask_C_s3_f(void * pvParameters){
	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	
	const TickType_t xFrequency = 5;
	TickType_t xLastWakeTime;
	EventBits_t uxBits;
	uint8_t au8_UART_recived_data ;
	uint8_t au8_keypad_recived_data ;
	
	for( ;; )
	{
		
		uxBits = xEventGroupWaitBits(
		x_LCD_EventGroup , BIT0, pdTRUE,  pdFALSE,   ZERO );
		
		if( ( uxBits & ( BIT0 ) ) == ( BIT0 ) )
		{
			/* xEventGroupWaitBits() returned because bits were set. */
			au8_UART_recived_data = UART_Read();
			
			/*send to task A(LCD task) using queue */

			xQueueSend( xQueue_UART_LCD ,( void * ) &au8_UART_recived_data, ( TickType_t ) ZERO );

			/* Clear bit 0 in x_LCD_EventGroup. */
			
			uxBits = xEventGroupClearBits(
			x_LCD_EventGroup,  /* The event group being updated. */
			BIT0 );/* The bits being cleared. */
			
		}
		
		vTaskDelayUntil( & xLastWakeTime,xFrequency);
	}
	
}

 /****************** UART send task ******************************/
#define SENDING 1
#define NOT_SENDING 0

void vTask_F_s3_f(void * pvParameters){
	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	
	const TickType_t xFrequency = 10;
	TickType_t xLastWakeTime;
	EventBits_t uxBits;
	uint8_t au8_UART_recived_data ;
	uint8_t au8_keypad_recived_data ;
	static uint8_t au8_sending_state = NOT_SENDING  ;
	for( ;; )
	{
		/*	check group flag (bit 2)(button pressed flag) to send using UART the msg received from the keypad*/

		uxBits = xEventGroupWaitBits( x_LCD_EventGroup ,	BIT2, pdTRUE,  pdFALSE,   0 );

		if( ( uxBits & ( BIT2 ) ) == ( BIT2 ) )
		{
			
			/*set state to be send*/
			au8_sending_state = SENDING ;
			/* Clear bit 2 in xEventGroup. */
			
			uxBits = xEventGroupClearBits(
			x_LCD_EventGroup,  /* The event group being updated. */
			BIT2 );/* The bits being cleared. */
			
		}
		/* send each character in the queue of the keypad*/
		if (au8_sending_state == SENDING)
		{
			if (xQueueReceive( xQueue_keypad_UART,&( au8_keypad_recived_data ),( TickType_t )0 ) == pdPASS )
			{
				UART_Write(au8_keypad_recived_data) ;
			}
			else
			au8_sending_state = NOT_SENDING ;
		}
		
		vTaskDelayUntil( & xLastWakeTime,xFrequency);

	}
	
}

/************** Push button task  *******************/

void vTask_D_s3_f(void * pvParameters){
	
	const TickType_t xFrequency = 50 ;
	TickType_t xLastWakeTime;
	uint8_t au8_button_status ;
	EventBits_t uxBits;
	
	/*in group flag bit2 for send the msg , bit 3 to turn the led on ,  semaphore to clear screen of LCD */
	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

	for( ;; )
	{	
		pushButtonGetStatus(BTN_0 , &au8_button_status) ;
		
		if (au8_button_status==Pressed){
			/**give semaphore*/
			xSemaphoreGive( xSemaphore );
			uxBits = xEventGroupSetBits(
			x_LCD_EventGroup,    /* The event group being updated. */
			BIT2|BIT3);	
		}
		vTaskDelayUntil( & xLastWakeTime,xFrequency);
	}
	
}


/**************       LEDs task       *****************/

void vTask_E_s3_f(void * pvParameters){
	
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	
	const TickType_t xFrequency = 100 ;
	TickType_t xLastWakeTime;
	EventBits_t uxBits;
	static uint8_t au8_led_1_conter = 0 ;
	static uint8_t au8_led_2_conter = 0 ;

	
	for( ;; )
	{
		
		/********************  check for led 1 - msg is recieved *******************************/
		
		uxBits = xEventGroupWaitBits(
		x_LCD_EventGroup ,   /* The event group being tested. */
		BIT1, /* The bits within the event group to wait for. */
		pdTRUE,        /* BIT_0 & BIT_4 should be cleared before returning. */
		pdFALSE,       /* Don't wait for both bits, either bit will do. */
		0 );/* Wait a maximum of 100ms for either bit to be set. */
		
		if( ( uxBits & ( BIT1 ) ) == ( BIT1 ) )
		{
			/* xEventGroupWaitBits() returned because bits were set. */
			
			DIO_Write(GPIOB,BIT7,HIGH) ;
			
			/* Clear bit 0 and bit 4 in xEventGroup. */
			
			uxBits = xEventGroupClearBits(
			x_LCD_EventGroup,  /* The event group being updated. */
			BIT1 );/* The bits being cleared. */
			au8_led_1_conter = 5 ;	

		}else if (au8_led_1_conter == ZERO)
		{
			DIO_Write(GPIOB,BIT7,LOW) ;

		}
		else
		au8_led_1_conter--;
		
		/********************  check for led 2 - msg is sent *******************************/
		
		uxBits = xEventGroupWaitBits(
		x_LCD_EventGroup ,   /* The event group being tested. */
		BIT3, /* The bits within the event group to wait for. */
		pdTRUE,        /* BIT_0 & BIT_4 should be cleared before returning. */
		pdFALSE,       /* Don't wait for both bits, either bit will do. */
		0 );/* Wait a maximum of 100ms for either bit to be set. */
		
		if( ( uxBits & ( BIT3 ) ) == ( BIT3 ) )
		{
			/* xEventGroupWaitBits() returned because bits were set. */
			
			DIO_Write(GPIOB,BIT6,HIGH) ;
			
			/* Clear bit 3 in xEventGroup. */
			
			uxBits = xEventGroupClearBits(
			x_LCD_EventGroup,  /* The event group being updated. */
			BIT3 );/* The bits being cleared. */
			au8_led_2_conter = 2 ;

		}else if (au8_led_2_conter == ZERO)
		{
			DIO_Write(GPIOB,BIT6,LOW) ;

		}
		else
		au8_led_2_conter--;
		
		vTaskDelayUntil( & xLastWakeTime,xFrequency);

	}
	
}




void sprint3_f( void )
{
	BaseType_t xReturned_initTask;
	BaseType_t xReturned_Task_A;
	BaseType_t xReturned_Task_B;
	BaseType_t xReturned_Task_C;
	BaseType_t xReturned_Task_F;

	BaseType_t xReturned_Task_D;
	BaseType_t xReturned_Task_E;

	
	xSemaphore = xSemaphoreCreateBinary();
	xQueue_keypad_LCD = xQueueCreate( 16, sizeof( uint16_t ) );
	xQueue_keypad_UART = xQueueCreate( 16, sizeof( uint16_t ) );
	xQueue_UART_LCD = xQueueCreate( 16, sizeof( uint8_t ) );

	
	/* Declare a variable to hold the created event group. */
	
	x_LCD_EventGroup = xEventGroupCreate();
	
	
	/***************************** init task ********************************/

	/* Create the task, storing the handle. */
	xReturned_initTask = xTaskCreate(
	vTask_initTask_s3_f,       /* Function that implements the task. */
	"M",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	3	,			/* Priority at which the task is created. */
	&xHandle_initTask_s3_f );      /* Used to pass out the created task's handle. */
	
	/***************************** task A ********************************/
	
	xReturned_Task_A = xTaskCreate(
	vTask_A_s3_f ,       /* Function that implements the task. */
	"A",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	2	,			/* Priority at which the task is created. */
	&xHandle_Task_A_s3_f );      /* Used to pass out the created task's handle. */

	/***************************** task B ********************************/
	
	
	xReturned_Task_B = xTaskCreate(
	vTask_B_s3_f,       /* Function that implements the task. */
	"B",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	1	,			/* Priority at which the task is created. */
	&xHandle_Task_B_s3_f );      /* Used to pass out the created task's handle. */
	
	
	/***************************** task C ********************************/
	
	
	xReturned_Task_C = xTaskCreate(
	vTask_C_s3_f,       /* Function that implements the task. */
	"C",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	3	,			/* Priority at which the task is created. */
	&xHandle_Task_C_s3_f );      /* Used to pass out the created task's handle. */

	/***************************** task F ********************************/
	
	
	xReturned_Task_F = xTaskCreate(
	vTask_F_s3_f,       /* Function that implements the task. */
	"F",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	3	,			/* Priority at which the task is created. */
	&xHandle_Task_F_s3_f );      /* Used to pass out the created task's handle. */



	/***************************** task D ********************************/
	
	
	xReturned_Task_D = xTaskCreate(
	vTask_D_s3_f,       /* Function that implements the task. */
	"D",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	3	,			/* Priority at which the task is created. */
	&xHandle_Task_D_s3_f );      /* Used to pass out the created task's handle. */

	/***************************** task E ********************************/
	
	
	xReturned_Task_E = xTaskCreate(
	vTask_E_s3_f,       /* Function that implements the task. */
	"E",          /* Text name for the task. */
	STACK_SIZE,      /* Stack size in words, not bytes. */
	( void * ) 1,    /* Parameter passed into the task. */
	3	,			/* Priority at which the task is created. */
	&xHandle_Task_E_s3_f );      /* Used to pass out the created task's handle. */


}



int main(void)
{
		
	//sprint3_Story1();
	sprint3_f();
	/* Start Scheduler */
	
	vTaskStartScheduler();
	

	while(1)
	{

		return 0 ;
	}
}
