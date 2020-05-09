/*
 * FreeRTOS_Sotry1.c
 *
 * Created: 4/10/2020 8:59:02 PM
 * Author : Ahmed Amin
 */ 
/******************** INCLUDES***************/
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "gpio.h"


/********************Macros******************/
#define INIT_DONE 13
#define INIT_NOT_DONE 14

/*******************Global Variables********************/
TaskHandle_t xHandle_Sys_Init = NULL;
TaskHandle_t xHandle_Toggle_LED=NULL;
uint8_t LED_Init_state = INIT_NOT_DONE;


/***********************ProtoTypes***********************/
void TASK_Sys_Init(void * Task_Parameter);
void TASK_Toggle_LED(void *Task_Parameter);



int main(void)
{
	/*Creat Toggle Task*/
	xTaskCreate(
	TASK_Toggle_LED,
	"ToggleLED",
	85,
	NULL,
	1,
	&xHandle_Toggle_LED);
	
	/*Creat Init Task*/
	xTaskCreate(
	TASK_Sys_Init,
	"System_Init",
	85,
	NULL,
	1,
	&xHandle_Sys_Init);
	
	/*Start Scheduler*/
	vTaskStartScheduler();
	
	/* Replace with your application code */
	while (1)
	{
	}
}


/*System Init*/
void TASK_Sys_Init(void * argumentPtr)
{
	while(1)
	{
		/* Check if LED Intialization is not done yet then initialize the LED and switch the init task sate to Suspend*/
		if(LED_Init_state==INIT_NOT_DONE){
			//gpioPortDirection(GPIOB,OUTPUT);
			Led_Init(LED_0);
			vTaskDelay(2);
			LED_Init_state=INIT_DONE;
			vTaskSuspend(xHandle_Sys_Init);
		}

	}
}


/*LED TOGGLE */
void TASK_Toggle_LED(void *Task_Parameter){
	
	while(1)
	{
		/* Check if Intialization is done or not then do the process*/
		if(LED_Init_state==INIT_DONE){
		Led_Toggle(LED_0);
	}
	vTaskDelay(1000);

	}
}


