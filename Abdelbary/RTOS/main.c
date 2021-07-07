/*
 * FreeRTOS_Sotry1.c
 *
 * Created: 4/15/2020 8:59:02 PM
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
/********************Macros******************/

#define INIT_DONE 13
#define INIT_NOT_DONE 14
#define TASK_C 23
#define TASK_B 37

/*******************Global Variables********************/
TaskHandle_t xHandle_Sys_Init = NULL;
TaskHandle_t xHandle_TASK_A_LCD = NULL;
TaskHandle_t xHandle_TASK_C_LCD = NULL;
TaskHandle_t xHandle_TASK_B_KeyPad=NULL;

SemaphoreHandle_t xMutex;


uint8_t LCD_Init_state = INIT_NOT_DONE;
uint8_t Display_data;
uint8_t I_HAVE_THE_ACCESS;
/***********************ProtoTypes***********************/
void TASK_Sys_Init(void * Task_Parameter);
void TASK_A_To_Dispaly_ON_LCD(void *Task_Parameter);
void TASK_C_TO_Send_To_LCD(void *Task_Parameter);
void TASK_B_TO_Read_KeyPad(void *Task_Parameter);


int main(void)
{
	xMutex = xSemaphoreCreateMutex();
	
	/*Creat Init Task*/
	xTaskCreate(
	TASK_Sys_Init,
	"System_Init",
	85,
	NULL,
	4,
	&xHandle_Sys_Init);
	
	/*Creat LCD Task*/
	xTaskCreate(
	TASK_A_To_Dispaly_ON_LCD,
	"LCD",
	85,
	NULL,
	3,
	&xHandle_TASK_A_LCD);
	
	/*Creat Keypad Task*/
	xTaskCreate(
	TASK_B_TO_Read_KeyPad,
	"Read_KeyPad",
	85,
	NULL,
	2,
	&xHandle_TASK_B_KeyPad);
	
	xTaskCreate(
	TASK_C_TO_Send_To_LCD,
	"Send_LCD",
	85,
	NULL,
	1,
	&xHandle_TASK_C_LCD);
	
	
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
		if(LCD_Init_state==INIT_NOT_DONE){
			/* Init LCD*/
			LCD_init();
			vTaskDelay(2);
			LCD_Init_state=INIT_DONE;
			
			/*switch Init Task to Suspend State*/
			vTaskSuspend(xHandle_Sys_Init);
		}
		
	}

	}




	
	
void TASK_B_TO_Read_KeyPad(void *Task_Parameter){
	uint8_t Key_Value;
	uint8_t KeyPad_State;
	
	while(1){
		/*Always check if there is a button is keeping being pressed and taking or giving the mutex depends on the key state*/
		KeyPad_State= KeyPad_getPressedKey(&Key_Value);
		/* This condition means the key is pressed*/
		if(KeyPad_State==KEYPAD_DONE){
			xSemaphoreTake(xMutex,0);
			/* now task B have the access on resource*/
			I_HAVE_THE_ACCESS=TASK_B;
		}
		/* This condition means the key is not pressed*/
		else{
			xSemaphoreGive(xMutex);
		}
		
		vTaskDelay(30);
	}
}


void TASK_C_TO_Send_To_LCD(void *Task_Parameter){
	
	while(1){
		xSemaphoreTake(xMutex, portMAX_DELAY);
		/* task C have the access on resource*/
		I_HAVE_THE_ACCESS=TASK_C;
		vTaskDelay(400);
		xSemaphoreGive(xMutex);
	}

		
}

void TASK_A_To_Dispaly_ON_LCD(void *Task_Parameter){
	
	while(1){
		/* Check if LCD Intialization is  done yet then display on  lcd and message from task C or B depends on which task has the access*/
		if(LCD_Init_state==INIT_DONE){
			if(I_HAVE_THE_ACCESS==TASK_C){
				LCD_displayString(" HELLO LCD ");
				vTaskDelay(200);
				LCD_sendCommand(CLEAR_COMMAND);
			}
			if(I_HAVE_THE_ACCESS==TASK_B){
				LCD_clearScreen();
				LCD_goToRowColumn(1,0);
				LCD_displayString(" Over Written !");
			}
		}
		vTaskDelay(30);
	}
}
