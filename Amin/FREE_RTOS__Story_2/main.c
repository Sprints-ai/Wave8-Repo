/*
 * FreeRTOS_Sotry2.c
 *
 * Created: 4/10/2020 8:59:02 PM
 * Author : Ahmed Amin
 */ 
/******************** INCLUDES***************/
#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"
#include "LCD.h"
#include "keypad.h"
/********************Macros******************/
#define New_Dispaly 30
#define Old_Press 50
#define ERASE_KEY 7
#define ENTER_KEY 8
#define CORRECT 10 
#define INCORRECT 20
#define INIT_DONE 13
#define INIT_NOT_DONE 14


/*******************Global Variables********************/
TaskHandle_t xHandle_Sys_Init = NULL;
TaskHandle_t xHandle_LCD = NULL;
TaskHandle_t xHandle_KeyPad=NULL;

uint8_t PassWord[6]={1,2,3,4,5,6};
uint8_t User_Entered_Password[6];
uint8_t Index=0;
uint8_t Iterrate=0;
uint8_t PassWord_Status_Flag=CORRECT;
uint8_t LCD_Init_state = INIT_NOT_DONE;
uint8_t Display_data;
uint8_t New_Press_To_Dispaly=Old_Press;

/***********************ProtoTypes***********************/
void TASK_Sys_Init(void * Task_Parameter);
void TASK_LCD(void *Task_Parameter);
void TASK_Read_KeyPad(void *Task_Parameter);


int main(void)
{
	
	/*Creat Init Task*/
	xTaskCreate(
	TASK_Sys_Init,
	"System_Init",
	85,
	NULL,
	1,
	&xHandle_Sys_Init);
	
	/*Creat LCD Task*/
	xTaskCreate(
	TASK_LCD,
	"LCD",
	85,
	NULL,
	1,
	&xHandle_LCD);
	
	/*Creat Keypad Task*/
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


void TASK_LCD(void *Task_Parameter){
	while(1){
		/* 
		This is to Test Lcd with Keypad
		if(New_Press_To_Dispaly==New_Dispaly&&LCD_Init_state==INIT_DONE){
			LCD_displayInteger(Display_data);
		}*/
		/* Check first if the LCD is Intialized and new Button is Pressed */
		if(New_Press_To_Dispaly==New_Dispaly&&LCD_Init_state==INIT_DONE){
			/*Save the Pressed Button Value in array for further Check if Password is Correct or not */
			User_Entered_Password[Index++]=Display_data;
			/* display "*" for every number of password that user press */
			LCD_displayCharacter('*');
	}
	vTaskDelay(200);

	/*Check if user Pressed the ERASE Button which is KEY_8 on Keypad and if yes clear the LCD*/
	if(Display_data==8){
	LCD_sendCommand(CLEAR_COMMAND);
	Index=0;	
	}
	/*Check if user Enterd the 6 digit password and then Pressed Enter_KEY which is KEY_7 on Keypad*/
	if(Index==7&&Display_data==7){
		/*Check if the Password that user entered is correct or not */
		for(Iterrate=0;Iterrate<6;Iterrate++){
			if(User_Entered_Password[Iterrate]!=PassWord[Iterrate]){
				PassWord_Status_Flag=INCORRECT;
			}
		}
   /* If correct display string Correct PASS for 2 seconds and erase the lcd for new process*/
		if(PassWord_Status_Flag==CORRECT){
			LCD_sendCommand(CLEAR_COMMAND);
			LCD_displayString(" CORRECT PASS");
			vTaskDelay(2000);
			LCD_sendCommand(CLEAR_COMMAND);
			Index=0;
		}
		/* If not correct display string Wrong PASS for 2 seconds and erase the lcd for new process*/
		else{
			LCD_sendCommand(CLEAR_COMMAND);
			LCD_displayString(" WRONG PASS");
			vTaskDelay(2000);
			LCD_sendCommand(CLEAR_COMMAND);
			Index=0;
		}
	}
}

}

	
	
void TASK_Read_KeyPad(void *Task_Parameter){
	uint8_t Key_Value;
	uint8_t KeyPad_State;
	
	while(1){
		/*Check if key is  Pressed and get the Pessed Key*/
		  KeyPad_State= KeyPad_getPressedKey(&Key_Value);
		  if(KeyPad_State==KEYPAD_DONE){
			  Display_data=Key_Value;
			  New_Press_To_Dispaly=New_Dispaly;
		  }
		  else{
			  New_Press_To_Dispaly=Old_Press;
		  }
		  vTaskDelay(50);
	}
	
}


