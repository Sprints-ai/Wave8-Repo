/*
 * APP.c
 *
 * Created: 3/15/2020 2:24:44 PM
 *  Author: A_ayman
 */ 

#include "APP.h"
#include "../HAL/LCD/LCD.h"
#include <util/delay.h>
/*
*** Local Macros
*/

#define FIRST_QUESTION_PART1   0
#define FIRST_QUESTION_PART2   1
#define FIRST_QUESTION_PART3   3

#define FIRST_QUESTION_PART4   4
#define FIRST_QUESTION_PART5   5
#define WAITING_ANSWER         6


#define RECEIVE_FIRST_ANS     7
#define RECEIVE_FIRST_ANS2    8


#define SECOND_QUESTION_PART1 21
#define THIRD_QUESTION_PART1  22
#define FOURTH_QUESTION_PART1 23
#define FIFTH_QUESTION_PART1  24
#define FIRST_ANSWER_PART1    0
#define FIRST_ANSWER_PART2    1
#define FIRST_ANSWER_PART3    3
#define FIRST_ANSWER_PART4    4


#define QUESTION1_TIME 88
#define COMMAND_TIME   8

/*
*** task 1 status 
*/
#define FIRST_QUESTION            0
#define DISPLAYING_CORRECT_ANSWER 1
#define DISPLAYING_WRONG_ANSWER   2
#define READY_FOR_NEXT_QUESTION   3
#define SECOND_QUESTION           4


/*
*** button status
*/
#define NOT_PRESSED 1
#define PRESSED     0
#define FINISHED 255


/*
*** shared Resources
*/
static uint8_t u8_Task_Status = FIRST_QUESTION_PART1;
static volatile uint8_t  Question_Disp_Status = FIRST_QUESTION_PART1;
static volatile uint8_t Button0_Pressed;
static volatile uint8_t Button1_Pressed ;
static volatile uint8_t u8_Task1_Entrance_Time = 0;
static volatile uint8_t u8_Task_EXECUTED_PART = FIRST_QUESTION;

/*
*** Static Function Prototypes
*/
void Display_Wrong_Answer ();
void Display_Correct_Answer ();




/*
*** Function Implementations
*/








void Task_25m ()
{
	uint8_t static u8_Button0_Status = NOT_PRESSED;
	uint8_t static u8_Button1_Status = NOT_PRESSED;
	uint8_t static Flag = 0;

	
	switch (Question_Disp_Status )
	{
		
		case WAITING_ANSWER:
		{
			Flag++;
			DIO_Read (BTN_0_GPIO	,BTN_0_BIT , &u8_Button0_Status);
			DIO_Read (BTN_1_GPIO	,BTN_1_BIT , &u8_Button1_Status);
			if (u8_Button0_Status == PRESSED )
			{
				if (Flag >= 2)
				{
					Flag = 0;
					Button0_Pressed = TRUE;
					u8_Button0_Status == NOT_PRESSED;
					Question_Disp_Status= RECEIVE_FIRST_ANS;
				}
				break;
		  }
		  if (u8_Button1_Status == PRESSED )
		  {
			  if (Flag >= 2)
			  {
				  Flag = 0;
				  Button1_Pressed = TRUE;
				  u8_Button1_Status == NOT_PRESSED;
				  Question_Disp_Status= RECEIVE_FIRST_ANS;
			  }
			  break;
		  }
		  
		
		}
		default:
		break;
	}
	}
	
void Question1_Display ()
{
	switch (Question_Disp_Status )
   {
		case  FIRST_QUESTION_PART1:
		{
			if ( u8_Task1_Entrance_Time == QUESTION1_TIME)
			{
				Question_Disp_Status = FIRST_QUESTION_PART2;
				u8_Task1_Entrance_Time = 0;
				break;
			}
			LCD_displayString(" are you ready ? ");
			break;
		}
		
		case  SECOND_QUESTION_PART1:
		{
			
			if ( u8_Task1_Entrance_Time == 96)
			{
				Question_Disp_Status = FIRST_QUESTION_PART2;
				u8_Task1_Entrance_Time = 0;
				break;
			}
			LCD_displayString(" Is 1+1 = 3 ");
			break;
		}
		case  THIRD_QUESTION_PART1:
		{
			
			if ( u8_Task1_Entrance_Time == 120)
			{
				Question_Disp_Status = FIRST_QUESTION_PART2;
				u8_Task1_Entrance_Time = 0;
				break;
			}
			LCD_displayString("Is that two '2'");
			break;
		}
		case  FOURTH_QUESTION_PART1:
		{
			
			if ( u8_Task1_Entrance_Time == 104)
			{
				Question_Disp_Status = FIRST_QUESTION_PART2;
				u8_Task1_Entrance_Time = 0;
				break;
			}
			LCD_displayString(" Is 5*5 = 55 ");
			break;
		}
		case  FIFTH_QUESTION_PART1:
		{
			
			if ( u8_Task1_Entrance_Time == 104)
			{
				Question_Disp_Status = FIRST_QUESTION_PART2;
				u8_Task1_Entrance_Time = 0;
				break;
			}
			LCD_displayString(" Is 5*5 = 25 ");
			break;
		}
		
		
		case  FIRST_QUESTION_PART2:
		{
			if ( u8_Task1_Entrance_Time == COMMAND_TIME)
			{
				Question_Disp_Status = FIRST_QUESTION_PART3;
				u8_Task1_Entrance_Time = 0;
				break;
			}
			
			LCD_sendCommand(0xC0);
			break;
		}
		case  FIRST_QUESTION_PART3:
		{
			if ( u8_Task1_Entrance_Time == 104)
			{
				Question_Disp_Status =WAITING_ANSWER;//FIRST_QUESTION_PART4;
				u8_Task1_Entrance_Time = 0;
			}
			
			LCD_displayString("1-YES  2-NO ");
			break;

		}
		case  WAITING_ANSWER:
		{
         // do nothing until the PushButton is Pushed
			break;
		}
		case  RECEIVE_FIRST_ANS:
		{
			LCD_clear ();
			if (Button0_Pressed == TRUE)
			{
				
				u8_Task_EXECUTED_PART= DISPLAYING_CORRECT_ANSWER;
				Button0_Pressed == FALSE;
			}
			else if (Button1_Pressed == TRUE)
			{
				u8_Task_EXECUTED_PART= DISPLAYING_WRONG_ANSWER;	
				Button1_Pressed = FALSE;
			}
		   Question_Disp_Status =FINISHED;
			u8_Task1_Entrance_Time = 0;			
			break;
		}
	
	}
}

void Task_1m ()
{
	u8_Task1_Entrance_Time ++;
	
	switch (u8_Task_EXECUTED_PART )
	{
		case FIRST_QUESTION:
		Question1_Display ();
		break;
		case DISPLAYING_CORRECT_ANSWER:
		Display_Correct_Answer ();
		break;
		case DISPLAYING_WRONG_ANSWER:
		Display_Wrong_Answer ();
		break;
		case READY_FOR_NEXT_QUESTION:
		Get_Ready_for_Next_Question();
		break;
		
		default:
		break;
	}
	
}

void Get_Ready_for_Next_Question ()
{
	static uint8_t entrance_count = 0;

	entrance_count ++;
	LCD_sendCommand(CLEAR_LCD);
	if (entrance_count == 1 )
	{
		Question_Disp_Status = SECOND_QUESTION_PART1;
		u8_Task_EXECUTED_PART = FIRST_QUESTION;
		u8_Task1_Entrance_Time =0;
	}
	if (entrance_count == 2)
	{
		Question_Disp_Status = THIRD_QUESTION_PART1;
		u8_Task_EXECUTED_PART = FIRST_QUESTION;
		u8_Task1_Entrance_Time =0;
	}
	if (entrance_count == 3 )
	{
		Question_Disp_Status = THIRD_QUESTION_PART1;
		u8_Task_EXECUTED_PART = FIRST_QUESTION;
		u8_Task1_Entrance_Time =0;
	}
	if (entrance_count == 4 )
	{
		Question_Disp_Status = FOURTH_QUESTION_PART1;
		u8_Task_EXECUTED_PART = FIRST_QUESTION;
		u8_Task1_Entrance_Time =0;
	}
	if (entrance_count == 5 )
	{
		Question_Disp_Status = FIFTH_QUESTION_PART1;
		u8_Task_EXECUTED_PART = FIRST_QUESTION;
		u8_Task1_Entrance_Time =0;
	}
	
}




void Display_Correct_Answer ()
{
	static uint8_t Answer_Disp_Status = FIRST_ANSWER_PART1;

	switch (Answer_Disp_Status )
	{
		case  FIRST_ANSWER_PART1:
		{
			if ( u8_Task1_Entrance_Time ==8)
			{
				Answer_Disp_Status = FIRST_ANSWER_PART2;
				u8_Task1_Entrance_Time = 0;
				break;
			}
			LCD_sendCommand(0X01);
			break;
		}
    	case FIRST_ANSWER_PART2:
		{
			if ( u8_Task1_Entrance_Time == 8)
			{
				Answer_Disp_Status = FIRST_ANSWER_PART3;
				u8_Task1_Entrance_Time = 0;
				break;
			}
			LCD_displayStringRowColumn (3,1);
		   break;
		}
		case FIRST_ANSWER_PART3:
		{
			if ( u8_Task1_Entrance_Time  ==88 )
			{
				Answer_Disp_Status = FIRST_ANSWER_PART4;//FIRST_QUESTION_PART4;
				u8_Task1_Entrance_Time = 0;
			
				break;
			}
				LCD_displayString(" Correct :)"); 
	   	
			break;
		}
		case FIRST_ANSWER_PART4:
		{
			// JUST USED FOR DELAY
			if ( u8_Task1_Entrance_Time  == 200)
			{
				Answer_Disp_Status =FINISHED;//FIRST_QUESTION_PART4;
				u8_Task_EXECUTED_PART = READY_FOR_NEXT_QUESTION;
				u8_Task1_Entrance_Time = 0;
					
				break;
						
			}
				
			break;
		}
	}
}


void Display_Wrong_Answer ()
{
	static uint8_t Wrong_Answer_Disp_Status = FIRST_ANSWER_PART1;

	switch (Wrong_Answer_Disp_Status )
	{
		case  FIRST_ANSWER_PART1:
		{
			if ( u8_Task1_Entrance_Time ==8)
			{
				Wrong_Answer_Disp_Status = FIRST_ANSWER_PART2;
				u8_Task1_Entrance_Time = 0;
				break;
			}
			LCD_sendCommand(0X01);
			break;
		}
		case FIRST_ANSWER_PART2:
		{
			if ( u8_Task1_Entrance_Time == 8)
			{
				Wrong_Answer_Disp_Status = FIRST_ANSWER_PART3;
				u8_Task1_Entrance_Time = 0;
				break;
			}
			LCD_displayStringRowColumn (2,0);
			break;
		}


		case FIRST_ANSWER_PART3:
		{
			if ( u8_Task1_Entrance_Time  == 72)
			{
				Wrong_Answer_Disp_Status = FIRST_ANSWER_PART4;//FIRST_QUESTION_PART4;
				u8_Task1_Entrance_Time = 0;
				
				break;
			}
			LCD_displayString(" Wrong :(");
			
			break;
		} 
		case FIRST_ANSWER_PART4:
		{
			// JUST USED FOR DELAY
			if ( u8_Task1_Entrance_Time  == 200)
			{
				Wrong_Answer_Disp_Status =FINISHED;
				u8_Task_EXECUTED_PART = READY_FOR_NEXT_QUESTION;
				u8_Task1_Entrance_Time = 0;
					
				break;
					
			}
	}
}
	}