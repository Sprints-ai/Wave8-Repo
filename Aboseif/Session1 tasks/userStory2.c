/*
 * userStory2.c
 *
 * Created: 2020-04-14 4:20:42 PM
 *  Author: EbrahimOseif
 */
 


#include "FreeRTOS.h"
#include "task.h"
#include "DIO.h"
#include "LCD.h"
#include "my_keypad.h"



/************************************************************************/
/*					tasks  DEFINES                                     */
/************************************************************************/

#define PERIORITY_1 		(1)
#define PERIORITY_2 		(2)
#define PERIORITY_3 		(3)
#define STACK_SIZE 			(100)
#define NO_PARAMETERS 		(1)

#define ZERO 				(0)
#define MAX_Chars_Index 	(7)
#define DISPALY_DELAY 		(2000)
#define PASS_MATCHED 		(6)

#define Paramter ((st_task_payload *)pvParameters)

/************************************************************************/
/*							TASK Varibales                              */
/************************************************************************/

uint8_t Correct_Chars_cnt = 0;

typedef struct{
	char Chars_Entered[7];
	uint8_t Chars_Index;
	uint8_t Chars_help_Index;
	const char Pass[6]

}st_task_payload;

st_task_payload parameter = {Chars_Entered = {0},
							Chars_Index = 0 ,
					        Chars_help_Index=0,
					        Pass = {'1','2','3','4','5','6'}
					      };



/************************************************************************/
/*								APIS                                    */
/************************************************************************/

void Sys_Init(){
	
	while(1)
	{
	LCD_init(FOUR_BIT_MODE);

	vTaskSuspend(NULL);
	}
}

void KeyPad(void * pvParameters

	 TickType_t xLastWakeTime;
	 const TickType_t REPEAT_DELAY_TICKS = 130;

	 // Initialize the xLastWakeTime variable with the current time.
	 xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		/* if valid char store it in the payload struct */
		if(Key_Pressed() >= ZERO && ((Paramter->Chars_Index) < MAX_Chars_Index) ){

			Paramter->Chars_Entered[Paramter->Chars_Index] = (Key_Pressed() + NULL_CHAR);

			(Paramter->Chars_Index)++;
		}
		vTaskDelayUntil(&xLastWakeTime , REPEAT_DELAY_TICKS);
	}
}


void ValidatePassword(){
				
		LCD_clearScreen();
		if(Correct_Chars_cnt == PASS_MATCHED)
				{
					LCD_displayStringRowColumn(0,0," CorrectPassword ");
				}
				else
				{
					LCD_displayStringRowColumn(0,0," WRONG ONE    ");
				}
				vTaskDelay(DISPALY_DELAY);
}

void PASS_Check(void * pvParameters){
	
	const TickType_t REPEAT_DELAY_TICKS = 140;

	// Initialize the xLastWakeTime variable with the current time.
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		/* clear the screen and clear the indeces order with ; char */
		
		if(Paramter->Chars_Entered[Paramter->Chars_Index-1] == ';')
		{
			LCD_clearScreen();
			Paramter->Chars_Index = 0;
			Paramter->Chars_help_Index = 0;	
			Correct_Chars_cnt = 0;

		}
		else
		{	/* display the typed chars and track the right chars */
	
			if((Paramter->Chars_help_Index) < (Paramter->Chars_Index) )
			{
				for(Paramter->Chars_help_Index ; (Paramter->Chars_help_Index) < (Paramter->Chars_Index) ; (Paramter->Chars_help_Index++))
				{
					if(Paramter->Chars_help_Index < (MAX_Chars_Index - 1)){
						LCD_displayCharacter(Paramter->Chars_Entered[Paramter->Chars_help_Index]);
							/* if the right char move on */
						if(Paramter->Chars_Entered[Paramter->Chars_help_Index] == Paramter->Pass[Paramter->Chars_help_Index])
						{
							Correct_Chars_cnt++;
						}
					}
				}
			}
			/* check the entered chars with the password */
			else if( Paramter->Chars_help_Index == MAX_Chars_Index && Paramter->Chars_Entered[MAX_Chars_Index - 1] == ':')
			{
				ValidatePassword();
				LCD_clearScreen();
				Paramter->Chars_help_Index++;
			    Correct_Chars_cnt = 0;
			}	
		}

		vTaskDelayUntil(&xLastWakeTime , REPEAT_DELAY_TICKS);
	}
}


int main(void)
{

	/*Create Tasks Handles*/
	TaskHandle_t Sys_Init 				= NULL;
	TaskHandle_t KeyPad_Task 			= NULL;
	TaskHandle_t PASS_Check_Task 		= NULL;

	/*Task Creation*/
	xTaskCreate(PASS_Check,"PASS_Check" , STACK_100_WORD , &parameter 			   ,PERIORITY_1  , &PASS_Check_Task);
	xTaskCreate(KeyPad    ,"KeyPad" 	, STACK_100_WORD , &parameter 			   ,PERIORITY_2  , &KeyPad_Task);
	xTaskCreate(Sys_Init  ,"SysIn"  	, STACK_100_WORD , (void * ) NO_PARAMETERS ,PERIORITY_3 , &Sys_Init);
 
	/* run the kernel Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}
}