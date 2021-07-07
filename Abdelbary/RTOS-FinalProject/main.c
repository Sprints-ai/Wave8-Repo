/*
 * FreeRTOS_Sotry1.c
 *
 * Created: 4/15/2020 8:59:02 PM
 * Author : Ahmed Amin
 */ 
/******************** INCLUDES***************/
#include "Service/RTOS/FreeRTOS.h"
#include "Service/RTOS/task.h"
#include "Service/RTOS/queue.h"
#include "Service/RTOS/timers.h"
#include "Service/RTOS/semphr.h"
#include "Hal/LCD/char_lcd.h"
#include "Hal/Keypad/keypad.h"
#include "Hal/LED/led.h"
#include "Hal/PushButton/pushButton.h"
#include "Mcal/UART/uart.h"
/********************Macros******************/

#define INIT_DONE 13
#define INIT_NOT_DONE 14
#define TASK_A_ 15
#define TASK_C_ 23
#define TASK_B_ 37
#define OFF 67
#define ON 43
#define NEW_VLAUE_TO_DISPLAY 10
#define NO_VALUE_TO_DISPLAY 0
#define  MAX_BUFFER_SIZE   16
#define LCD_FIRST_ROW   0
#define LCD_SECND_ROW	1
#define LCD_EMPTY_ROW    "                "
/*******************Global Variables********************/
TaskHandle_t xHandle_Sys_Init = NULL;
TaskHandle_t xHandle_TASK_A = NULL;
TaskHandle_t xHandle_TASK_C = NULL;
TaskHandle_t xHandle_TASK_B=NULL;
TaskHandle_t xHandle_TASK_D=NULL;
TaskHandle_t xhandle_TASK_uart = NULL;
TaskHandle_t xhandle_TASK_PbSEND = NULL;

SemaphoreHandle_t xMutex;
SemaphoreHandle_t xMutexPushButtonStatus;
SemaphoreHandle_t xMutexPushButtonCounter;

uint8_t gau8_sendBuffer[MAX_BUFFER_SIZE];
uint8_t gu8_sendBufferCounter;
uint8_t LCD_Init_state = INIT_NOT_DONE;
uint8_t LED_Init_state = INIT_NOT_DONE;
uint8_t gu8_byteTosend;
uint8_t gau8_UART_recivedBuffer[MAX_BUFFER_SIZE];
uint8_t gu8_pushButtonStatus;
uint8_t gu8_lcdClearFirstRow;
uint8_t gu8_lcdClearSecndRow;
uint8_t gu8_UART_recivedBufferCounter;
volatile uint8_t  gu8_UART_recivedFlag;
volatile uint8_t  gu8_ReciveLedFlag = FALSE;
/***********************ProtoTypes***********************/
void TASK_Sys_Init(void * Task_Parameter);
void KEY_PAD(void *Task_Parameter);
void TASK_C(void *Task_Parameter);
void LED_TASK(void *Task_Parameter);
void TASK_D(void *Task_Parameter);
void PB_SendTASK(void *argumentPtr);
void UART_TASK(void *argumentPtr);


int main(void)
{

	/*Creat Init Task   p--> highest[4] */
	xTaskCreate(TASK_Sys_Init,"System_Init",85,NULL,4,&xHandle_Sys_Init);
	/*KEYPAD task       p--> 3         */
	xTaskCreate(KEY_PAD,"KEY_PAD",85,NULL,3,&xHandle_TASK_A);
	/*push button task  p--> 3        */
	xTaskCreate(PB_SendTASK,"PB_SendTASK",85,NULL,3,&xhandle_TASK_PbSEND);
	/*uart task			p--> 2        */
	xTaskCreate(UART_TASK,"uart",85,NULL,2,&xhandle_TASK_uart);
	/*led task			p--> 1         */
	xTaskCreate(LED_TASK,"LED",85,NULL,1,&xHandle_TASK_B);
	/*lcd task         p--> 0          */
	xTaskCreate(TASK_D,"LCD",85,NULL,0,&xHandle_TASK_D);
	
	/*Start Scheduler*/
	vTaskStartScheduler();
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
	
}

uint8_t sendTX()
{
	return gu8_byteTosend;
}

void reciveRX(uint8_t value)
{
	gu8_UART_recivedFlag = TRUE;
	gu8_ReciveLedFlag = TRUE;
	if(gu8_UART_recivedBufferCounter < MAX_BUFFER_SIZE)
		LCD_setPosValue(LCD_SECND_ROW,gu8_UART_recivedBufferCounter++,value+'0');
}

void UART_TASK(void *argumentPtr)
{
	while (1)
	{
		if(gu8_pushButtonStatus == Pressed)
		{
			uint8_t u8_counter =ZERO;
			TCNT2 +=gu8_sendBufferCounter;
			for (; u8_counter < gu8_sendBufferCounter ; u8_counter++)
			{			
				while(UDR_ReadyStatus() != TRUE);
				gu8_byteTosend = gau8_sendBuffer[u8_counter];
				UartTX_Enable();			
			}
			gu8_pushButtonStatus = Released;
			gu8_sendBufferCounter = ZERO;
		}
			vTaskDelay(50);

	}
}



void PB_SendTASK(void *argumentPtr)
{
	
	while(1)
	{
		 uint8_t u8_pushButtonStatus = Released;
		pushButtonPressed(BTN_0,&u8_pushButtonStatus);
		if (u8_pushButtonStatus == Pressed && gu8_pushButtonStatus == Released)
		{
			gu8_lcdClearFirstRow = TRUE;
			gu8_pushButtonStatus = u8_pushButtonStatus;
		}
		vTaskDelay(20);
	}
}



void TASK_Sys_Init(void * argumentPtr)
{
	while(1)
	{
		/* Check if LCD Intialization is not done yet then initialize the lcd and switch the init task sate to Suspend*/
		if(LCD_Init_state==INIT_NOT_DONE&&LED_Init_state==INIT_NOT_DONE){
			/* Init LCD*/
			sei();
			while(gu8_UARTmoduleInitFlage != TRUE)
			{
				LCD_init();
				vTaskDelay(10);
			}
			
			LCD_setNewBuffer("                ","                ");
			Led_Init(LED_0);
			Led_Init(LED_1);
			pushButtonInit(BTN_0);
			gstr_uart_cfg_t uart_cfg = {sendTX,reciveRX};
			Uart_Init(&uart_cfg);
			gu8_pushButtonStatus = Released;
			gu8_sendBufferCounter = ZERO;
			gu8_UART_recivedBufferCounter = ZERO;
			gu8_lcdClearFirstRow = FALSE;
			gu8_lcdClearSecndRow = FALSE;
			gu8_UART_recivedFlag = FALSE;
			//gu8_ReciveLedFlag = FALSE;
			LCD_Init_state=INIT_DONE;
			LED_Init_state=INIT_DONE;
			/*switch Init Task to Suspend State*/
			vTaskSuspend(xHandle_Sys_Init);
			vTaskDelay(10);
		}
		
	}

	}



void KEY_PAD(void *Task_Parameter){
	uint8_t Key_Value;
	uint8_t KeyPad_State;
	uint8_t u8_keyPadLock = UNLOCK;
	while(1){
		/*Always check if there is a button is keeping being pressed and increament a counter which defines the time of the key pressed*/
		KeyPad_State= KeyPad_getPressedKey(&Key_Value);
		if(KeyPad_State==KEYPAD_DONE && u8_keyPadLock == UNLOCK){
			   u8_keyPadLock = LOCK;
				if(gu8_sendBufferCounter < MAX_BUFFER_SIZE)
				{
					gau8_sendBuffer[gu8_sendBufferCounter] = Key_Value;
					LCD_setPosValue(LCD_FIRST_ROW,gu8_sendBufferCounter,Key_Value+'0');
					gu8_sendBufferCounter++;/*increase counter*/
				}
		}else if(KeyPad_State == NO_KEY_PRESSED) /*no button pressed on keypad*/
		{
			u8_keyPadLock = UNLOCK;
		}
	
		vTaskDelay(20);
	}
}

void LED_TASK(void *Task_Parameter){

	while (1)
	{
		if(gu8_ReciveLedFlag == TRUE )
		{
			gu8_ReciveLedFlag = FALSE;
			Led_Toggle(LED_0);
			vTaskDelay(500);
			Led_Toggle(LED_0);
		}

		vTaskDelay(50);

	}
}



void TASK_D(void *Task_Parameter){
	static uint16_t u16_lcdRecivedBufferDislayTimer =ZERO;
	while(1){
		if(gu8_lcdClearFirstRow == TRUE)
		{
			LCD_setFirstRowBuffer(LCD_EMPTY_ROW);
			gu8_lcdClearFirstRow = FALSE;
		}
		if(gu8_UART_recivedFlag == TRUE)
		{
			u16_lcdRecivedBufferDislayTimer++;
			if(u16_lcdRecivedBufferDislayTimer == 500)
			{
				gu8_UART_recivedFlag = FALSE;
				gu8_UART_recivedBufferCounter = ZERO;
				u16_lcdRecivedBufferDislayTimer = ZERO;
				LCD_setScndRowBuffer(LCD_EMPTY_ROW);
			}
		}
		lcd_dispatcher();
		vTaskDelay(2);
	}
}

