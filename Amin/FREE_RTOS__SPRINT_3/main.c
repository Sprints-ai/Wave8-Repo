/*
 * Sprint_3.c
 *
 * Created: 4/19/2020 1:59:28 AM
 * Author : Ahmed Amin
 */ 

/******************** INCLUDES***************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
#include "LCD.h"
#include "keypad.h"
#include "UART.h"
/********************Macros******************/

#define INIT_DONE 13
#define INIT_NOT_DONE 14
#define TASK_A_ 15
#define TASK_C_ 23
#define TASK_B_ 37
#define New_Dispaly 30
#define Old_Press 50
#define ERASE_KEY 7
#define UART_New_Data 107
#define UART_Old_Data 106
#define Not_Detected 103
#define Detected 104

/*******************Global Variables********************/
TaskHandle_t xHandle_Sys_Init = NULL;
TaskHandle_t xHandle_TASK_A = NULL;
TaskHandle_t xHandle_TASK_C = NULL;
TaskHandle_t xHandle_TASK_B=NULL;
TaskHandle_t xHandle_TASK_D=NULL;

SemaphoreHandle_t xMutex;

uint8_t LCD_Init_state = INIT_NOT_DONE;
uint8_t Display_data;
uint8_t I_HAVE_THE_ACCESS;
uint8_t New_Press_To_Dispaly=Old_Press;
uint8_t Clear_LCD=Not_Detected;
uint8_t UART_Init_state=INIT_NOT_DONE;
volatile uint8_t Uart_recieved_Data;
volatile uint8_t Uart_state;

/***********************ProtoTypes***********************/
void TASK_Sys_Init(void * Task_Parameter);
void TASK_A(void *Task_Parameter);
void TASK_C(void *Task_Parameter);
void TASK_B(void *Task_Parameter);
void TASK_D(void *Task_Parameter);
void uart(void);


int main(void)
{
	xMutex = xSemaphoreCreateMutex();

	/*Creat Init Task*/
	xTaskCreate(
	TASK_Sys_Init,
	"System_Init",
	85,
	NULL,
	0,
	&xHandle_Sys_Init);


	xTaskCreate(
	TASK_A,
	"BTN1",
	85,
	NULL,
	1,
	&xHandle_TASK_A);


	xTaskCreate(
	TASK_B,
	"BTN2",
	85,
	NULL,
	1,
	&xHandle_TASK_B);

	xTaskCreate(
	TASK_C,
	"LED",
	85,
	NULL,
	2,
	&xHandle_TASK_C);

	xTaskCreate(
	TASK_D,
	"LCD",
	85,
	NULL,
	4,
	&xHandle_TASK_D);


	/*Start Scheduler*/
	vTaskStartScheduler();


	/* Replace with your application code */
	while (1)
	{
	}

}

/* This task intialize LCD and UART*/
void TASK_Sys_Init(void * argumentPtr)
{
	while(1)
	{
		/* Check if UART&LCD Intialization are not done yet then initialize them  and switch the init task sate to Suspend*/
		if(LCD_Init_state==INIT_NOT_DONE&&UART_Init_state==INIT_NOT_DONE){
			/* Init LCD*/
			LCD_init();

			/* UART INIT */
			UART_ConfigType uart_configtype = {
				UART_ASYNCHRONOUS_MODE,
				UART_RECEIVER_MODE,
				UART_EIGHT_BITS,
				UART_PARITY_DISABLED,
				UART_ONE_STOP_BIT,
				UART_INTERRUPT_ENABLED
			};
			UART_RXC_setCallBack(&uart);
			UART_init(&uart_configtype);
			vTaskDelay(2);
			LCD_Init_state=INIT_DONE;
			UART_Init_state=INIT_DONE;
			/*switch Init Task to Suspend State*/
			vTaskSuspend(xHandle_Sys_Init);
		}

	}

}





/*This task reads the keypad pressed button */
void TASK_A(void *Task_Parameter){
	uint8_t Key_Value;
	uint8_t KeyPad_State;

	while(1){
		
		/*Always check if there is a button is pressed and save its value to display it later on lcd and take the access of the resource */
		KeyPad_State= KeyPad_getPressedKey(&Key_Value);
		if(KeyPad_State==KEYPAD_DONE&&Key_Value!=ERASE_KEY){
			if(xSemaphoreTake(xMutex,portMAX_DELAY) == pdTRUE)
			{
				Display_data=Key_Value;
				New_Press_To_Dispaly=New_Dispaly;
				I_HAVE_THE_ACCESS=TASK_A_;
				xSemaphoreGive(xMutex);

			}
		}
		/*this condition means that the button is not pressed and release the access of resource  */
		else if(Key_Value == NO_KEY_PRESSED){
			if (xSemaphoreTake(xMutex,portMAX_DELAY) == pdTRUE)
			{
				New_Press_To_Dispaly=Old_Press;
				xSemaphoreGive(xMutex);
			}
		}

		vTaskDelay(50);
	}
	
}

/*This Task check if the Erase Key is pressed or not */
void TASK_C(void *Task_Parameter){
	uint8_t Key_Value;
	uint8_t KeyPad_State;

	while(1){
		/*Always check if the Erase Key is pressed and take the access of resource to clear the lcd later in the lcd task*/
		KeyPad_State= KeyPad_getPressedKey(&Key_Value);

		if(KeyPad_State==KEYPAD_DONE&&Key_Value==ERASE_KEY){
			if(xSemaphoreTake(xMutex,portMAX_DELAY) == pdTRUE )
			{
				I_HAVE_THE_ACCESS=TASK_C_;
				Clear_LCD=Detected;
				xSemaphoreGive(xMutex);
			}

		}
		vTaskDelay(50);
	}
}
/*This Task check if there is any recived data by UART */
void TASK_B(void *Task_Parameter){

	while(1){
		/*Always Check if there is new data recived by uart and if yes take the resource to display it on lcd */
		if(UART_Init_state==INIT_DONE&&Uart_state==UART_New_Data){
			if(xSemaphoreTake(xMutex,10) == pdTRUE ){
				I_HAVE_THE_ACCESS=TASK_B_;
				xSemaphoreGive(xMutex);
			}
			}
		vTaskDelay(20);
	}
}
/*This Task Diplay the data of Uart and Keypad On LCD and check if the erase key is pressed or not to clear the lcd */
void TASK_D(void *Task_Parameter){
	static uint8_t Row_zero_col=0;
	static uint8_t Row_one_col=0;
	while(1){
		if(LCD_Init_state==INIT_DONE&&UART_Init_state==INIT_DONE){
			/*check if there is new pressed key and dispaly it on first row on lcd */
			if(I_HAVE_THE_ACCESS==TASK_A_&&New_Press_To_Dispaly==New_Dispaly){
				LCD_goToRowColumn(0,Row_zero_col);
				vTaskDelay(2);
				LCD_displayInteger(Display_data);
				vTaskDelay(2);
				Row_zero_col++;
				New_Press_To_Dispaly=Old_Press;
				
			}
			/*check if there is new uart data recieved and dispaly it on second row on lcd */
			else if(I_HAVE_THE_ACCESS==TASK_B_&&Uart_state==UART_New_Data){
				LCD_goToRowColumn(1,Row_one_col);
				vTaskDelay(2);
				LCD_displayInteger(Uart_recieved_Data-48);
				vTaskDelay(2);
				Row_one_col++;
				Uart_state=UART_Old_Data;
				
			}
			/*check if the erase key is pressed or not and then clear the lcd */
			else if(I_HAVE_THE_ACCESS==TASK_C_&&Clear_LCD==Detected)
			{
				LCD_sendCommand(CLEAR_COMMAND);
				Clear_LCD=Not_Detected;
				Row_one_col=0;
				Row_zero_col=0;
				
			}
		}
		vTaskDelay(200);
	}
}


/*recive the uart data and change the state for further check in lcd display task*/
void uart(void)
{

	Uart_recieved_Data=UART_receive();
	Uart_state=UART_New_Data;
}
