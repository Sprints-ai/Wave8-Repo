/*
 * FreeRTOS_Sotry1.c
 *
 * Created: 4/15/2020 8:59:02 PM
 * Author : Ahmed Amin
 */ 
/******************** INCLUDES***************/
#include "Service/FreeRTOS.h"
#include "Service/task.h"
#include "Service/queue.h"
#include "Service/timers.h"
#include "Service/semphr.h"
#include "Hal/LCD/LCD.h"
#include "Hal/Keypad/keypad.h"
#include "Hal/LED/led.h"
/********************Macros******************/

#define INIT_DONE 13
#define INIT_NOT_DONE 14
#define TASK_A_ 15
#define TASK_C_ 23
#define TASK_B_ 37
#define OFF 67
#define ON 43
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
uint8_t LED_Init_state = INIT_NOT_DONE;
uint8_t LED_STATE=OFF;

/***********************ProtoTypes***********************/
void TASK_Sys_Init(void * Task_Parameter);
void TASK_A(void *Task_Parameter);
void TASK_C(void *Task_Parameter);
void TASK_B(void *Task_Parameter);
void TASK_D(void *Task_Parameter);


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
		2,
		&xHandle_TASK_D);
	
	
	/*Start Scheduler*/
	vTaskStartScheduler();
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
	
}


void TASK_Sys_Init(void * argumentPtr)
{
	while(1)
	{
		/* Check if LCD Intialization is not done yet then initialize the lcd and switch the init task sate to Suspend*/
		if(LCD_Init_state==INIT_NOT_DONE&&LED_Init_state==INIT_NOT_DONE){
			/* Init LCD*/
			LCD_init();
			Led_Init(LED_0);
			vTaskDelay(2);
			LCD_Init_state=INIT_DONE;
			LED_Init_state=INIT_DONE;
			/*switch Init Task to Suspend State*/
			vTaskSuspend(xHandle_Sys_Init);
		}
		
	}

	}




	
	
void TASK_A(void *Task_Parameter){
	uint8_t Key_Value;
	uint8_t KeyPad_State;
	
	while(1){
		/*Always check if there is a button is keeping being pressed and increament a counter which defines the time of the key pressed*/
		KeyPad_State= KeyPad_getPressedKey(&Key_Value);
		if(KeyPad_State==KEYPAD_DONE&&Key_Value==1){
			if(xSemaphoreTake(xMutex,portMAX_DELAY) == pdTRUE)
			{
				I_HAVE_THE_ACCESS=TASK_A_;
				LED_STATE=ON;
				xSemaphoreGive(xMutex);

			}
		}
		/*this condition means that the button is no longer being pressed so we check the counter and decide the state of led*/
		else if(Key_Value == NO_KEY_PRESSED){
			if (xSemaphoreTake(xMutex,10) == pdTRUE)
			{
				 LED_STATE=OFF;
				 xSemaphoreGive(xMutex);
			}
		}
		
		vTaskDelay(50);
	}
}

void TASK_B(void *Task_Parameter){
	uint8_t Key_Value;
	uint8_t KeyPad_State;
	
	while(1){
		/*Always check if there is a button is keeping being pressed and increament a counter which defines the time of the key pressed*/
		KeyPad_State= KeyPad_getPressedKey(&Key_Value);
		
		if(KeyPad_State==KEYPAD_DONE&&Key_Value==2){
			if(xSemaphoreTake(xMutex,10) == pdTRUE )
			{
				I_HAVE_THE_ACCESS=TASK_B_;
				LED_STATE=ON;
				xSemaphoreGive(xMutex);
			}
			
		}
		/*this condition means that the button is no longer being pressed so we check the counter and decide the state of led*/
		else if(Key_Value == NO_KEY_PRESSED){
			if(xSemaphoreTake(xMutex,portMAX_DELAY) == pdTRUE)
			{
				LED_STATE=OFF;
				xSemaphoreGive(xMutex);
			}
			
		}
		
		vTaskDelay(50);
	}
}
void TASK_C(void *Task_Parameter){
	
	while(1){
		if(LED_Init_state==INIT_DONE){
			if(LED_STATE==ON){
				Led_On(LED_0);
			}else{
				Led_Off(LED_0);
			}
		}
		vTaskDelay(50);
	}		
}

void TASK_D(void *Task_Parameter){
	
	while(1){
		if(LCD_Init_state==INIT_DONE){
			if(I_HAVE_THE_ACCESS==TASK_A_&&LED_STATE==ON){
				vTaskDelay(2);
				LCD_displayString(" Led State:ON ");
				vTaskDelay(2);
				LCD_goToRowColumn(1,0);
				vTaskDelay(2);
				LCD_displayString(" BTN1:Pressed  ");
			}
			else if(I_HAVE_THE_ACCESS==TASK_B_&&LED_STATE==ON){
				vTaskDelay(2);
				LCD_displayString(" Led State:ON ");
				vTaskDelay(2);
				LCD_goToRowColumn(1,0);
				vTaskDelay(2);
				LCD_displayString(" BTN2:Pressed  ");
			}
			else
			{
				LCD_sendCommand(CLEAR_COMMAND);
			}
		}
		vTaskDelay(20);
	}
}

