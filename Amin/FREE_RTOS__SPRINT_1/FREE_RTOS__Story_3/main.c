/*
 * FreeRTOS_Sotry3.c
 *
 * Created: 4/10/2020 8:59:02 PM
 * Author : Ahmed Amin
 */ 

/******************** INCLUDES***************/
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "gpio.h"
#include "keypad.h"

/********************Macros******************/
#define INIT_DONE 13
#define INIT_NOT_DONE 14

#define New_Dispaly 30
#define Old_Press 50

#define TOGGLE_ONE_HUNDRED_MILLI 11
#define TURN_OFF_LED 12
#define TOGGLE_FOUR_HUNDRED_MILLI 13

/*******************Global Variables********************/
TaskHandle_t xHandle_Sys_Init = NULL;
TaskHandle_t xHandle_Toggle_LED=NULL;
TaskHandle_t xHandle_KeyPad=NULL;

uint8_t LED_Init_state = INIT_NOT_DONE;
uint8_t LED_STATE=TURN_OFF_LED;



/***********************ProtoTypes***********************/
void TASK_Sys_Init(void * Task_Parameter);
void TASK_Toggle_LED(void *Task_Parameter);
void TASK_Read_KeyPad(void *Task_Parameter);




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
	
	/*Creat KEYPAD Task*/
	xTaskCreate(
	TASK_Read_KeyPad,
	"Read_KeyPad",
	85,
	NULL,
	1,
	&xHandle_KeyPad);
	
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


/*Toggle LED*/
void TASK_Toggle_LED(void *Task_Parameter){
	
	while(1){
		/*switch the led state which was taken in the keypad task to toggle led for specific time*/
		
		if(LED_STATE==TOGGLE_ONE_HUNDRED_MILLI&&LED_Init_state==INIT_DONE){
			Led_Toggle(LED_0);
			vTaskDelay(100);
		}
			if(LED_STATE==TOGGLE_FOUR_HUNDRED_MILLI&&LED_Init_state==INIT_DONE){
			Led_Toggle(LED_0);
			vTaskDelay(400);
			}
			if(LED_STATE==TURN_OFF_LED&&LED_Init_state==INIT_DONE){
			Led_Off(LED_0);
		}
	}
	
}


/*KeyPad Read*/
void TASK_Read_KeyPad(void *Task_Parameter){
	
	uint8_t Key_Value;
	uint8_t KeyPad_State;
	static uint8_t counter_for_time=0;
	while(1){
		/*Always check if there is a button is keeping being pressed and increament a counter which defines the time of the key pressed*/
		  KeyPad_State= KeyPad_getPressedKey(&Key_Value);
		  if(KeyPad_State==KEYPAD_DONE){
			  counter_for_time++;
		  }
		  /*this condition means that the button is no longer being pressed so we check the counter and decide the state of led*/
		  else{
			     if(counter_for_time>1&&counter_for_time<68){
				     LED_STATE=TURN_OFF_LED;
				     counter_for_time=0;
			     }
			  if(counter_for_time>=68&&counter_for_time<=135){
				  LED_STATE=TOGGLE_ONE_HUNDRED_MILLI;
				  counter_for_time=0;
			  }
		  if(counter_for_time>135){
			  LED_STATE= TOGGLE_FOUR_HUNDRED_MILLI;
			  counter_for_time=0;
		  }
		  
	}
	vTaskDelay(30);
}
}