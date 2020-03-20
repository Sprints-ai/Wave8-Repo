/*
 * LCD_APP.c
 *
 * Created: 17/03/2020 01:51:50 م
 *  Author: TOSHIBA
 */ 
#include "LCD_APP.h"
#include "LCD_APP_Cfg.h"
#include "../MCAL/DIO/DIO.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/pushButton/pushButton.h"

#define MAX_NUMBER_OF_QUESTION	5
#define	QUESTION_ONE			(uint8_t *)ENTER_QUESTION_ONE	
#define QUESTION_TWO			(uint8_t *)ENTER_QUESTION_TWO	
#define	QUESTION_THREE			(uint8_t *)ENTER_QUESTION_THREE	
#define	QUESTION_FOURE			(uint8_t *)ENTER_QUESTION_FOURE	
#define	QUESTION_FIVE			(uint8_t *)ENTER_QUESTION_FIVE
#define INITI_FIRST_BUTTON		0x01
#define INITI_SECOND_BUTTON		 0x02
#define INITI_LCD				 0x04
#define INIT_ALL_FUNCTION		0x07
#define UNINIT					0
#define CONVERT_INT_TO_CHAR		48
#define DISPLAY_DELAY			10
#define FIRST_QUESTION			0
#define ZERO					0
#define START_COUNT				0


/*  QuestionGame function's state  */

#define PRINT_QUESTION_ON_LCD_STATE	0
#define CHECK_BUTTON_PRESSSED		1
#define RIGH_STATE					2
#define WRONG_STATE					3
#define RESULT_STATE				4
#define LCD_WAIT_COUNT_STATE		5
#define END_STATE					6
u8_ERROR_STATUS_t QuestionGame_Init(void){
	
	u8_ERROR_STATUS_t u8_QuesGameError = E_OK;
	
	static uint8_t u8_InitCount= UNINIT	;
	static uint8_t u8_LCD_InitFlag=UNINIT	;
	//check if the correct button init or not 
	if((u8_InitCount & INITI_FIRST_BUTTON ) != INITI_FIRST_BUTTON )
		{
		
		if(pushButtonInit(CORRECT_BUTTON) == E_OK)
		u8_InitCount |= INITI_FIRST_BUTTON ;
		
		}
		
		//check if the wrong_button init or not
	if((u8_InitCount & INITI_SECOND_BUTTON) != INITI_SECOND_BUTTON)
		{
			
		if(pushButtonInit(WRONG_BUTTON) ==E_OK)
			u8_InitCount |= INITI_SECOND_BUTTON;
			
		}
		
		//check if the LCD init or not
	if(u8_LCD_InitFlag != LCD_INIT_DONE)	
	{
		
		u8_LCD_InitFlag=LCD_init();
		
	}
	
	else 
	{
		
		u8_InitCount |= INITI_LCD;
	}
		
		/* check if the ALL init. Functions initialized or not */
	
	if(u8_InitCount == INIT_ALL_FUNCTION)
	
		u8_QuesGameError = INIT_DONE; 

	return u8_QuesGameError;
}

u8_ERROR_STATUS_t QuestionGame_RUN(void)
{
	u8_ERROR_STATUS_t u8_QuesGameError = E_OK;
	
	static uint8_t * apu8_arrOFQuestion[MAX_NUMBER_OF_QUESTION]={QUESTION_ONE,QUESTION_TWO,QUESTION_THREE,QUESTION_FOURE,QUESTION_FIVE};
	
	static  uint8_t au8_SavedAnswer[MAX_NUMBER_OF_QUESTION] = { ANSWER_QUESTION_ONE,ANSWER_QUESTION_TWO,
																ANSWER_QUESTION_THREE,ANSWER_QUESTION_FOUR,ANSWER_QUESTION_FIVE };
	
	static uint8_t u8_QuestionIndex = FIRST_QUESTION;
	
	static uint8_t u8_QuestionGameState = PRINT_QUESTION_ON_LCD_STATE;	
	static uint8_t u8_score = ZERO;
	static uint8_t u8_WriteStringFlag= E_OK;
	static uint8_t u8_WriteCommandDoneFlag= E_OK ;
	static uint8_t u8_LCD_WriteCounter = START_COUNT;
	static uint8_t u8_Delay_action ;
	static uint8_t u8_CorrectButtonReadFlag= E_OK;
	static uint8_t u8_WrongButtonReadFlag= E_OK;
	
	switch (u8_QuestionGameState)
	{
		case PRINT_QUESTION_ON_LCD_STATE:
		
		if(u8_QuestionIndex < MAX_NUMBER_OF_QUESTION)
			{
				if(u8_WriteCommandDoneFlag != WRITE_COMMAND_DONE )
				{
					u8_WriteCommandDoneFlag=LCD_clear();
				}
			else if(u8_WriteStringFlag != LCD_WRITE_STRING_DONE)
				
				u8_WriteStringFlag = LCD_WriteString(apu8_arrOFQuestion[u8_QuestionIndex]);
				
				else
				{
					u8_QuestionGameState = LCD_WAIT_COUNT_STATE;
					u8_Delay_action = CHECK_BUTTON_PRESSSED;
					u8_WriteStringFlag = E_OK;
					u8_WriteCommandDoneFlag = E_OK;
				}	
		}
		else
			u8_QuestionGameState = RESULT_STATE;
		break;
	
		case LCD_WAIT_COUNT_STATE:
		
			u8_LCD_WriteCounter ++ ;
			
			if(u8_LCD_WriteCounter==DISPLAY_DELAY)
			{	
				if(u8_Delay_action == CHECK_BUTTON_PRESSSED)
				{
					
					u8_QuestionGameState = CHECK_BUTTON_PRESSSED ;
				}
					
				else if(u8_Delay_action == PRINT_QUESTION_ON_LCD_STATE)
				
					u8_QuestionGameState = PRINT_QUESTION_ON_LCD_STATE;
			}
		break;
		case CHECK_BUTTON_PRESSSED :;
		
			uint8_t u8_CorrectButtonStatus = Released ;
			uint8_t u8_WrongButtonStatus = Released ;
			
			if(u8_CorrectButtonReadFlag!=BTN_READ_DONE)
		{
			u8_CorrectButtonReadFlag=pushButtonGetStatus(CORRECT_BUTTON ,&u8_CorrectButtonStatus);
		}
		
		else if(u8_WrongButtonReadFlag!=BTN_READ_DONE)
		{
			u8_WrongButtonReadFlag = pushButtonGetStatus(WRONG_BUTTON,&u8_WrongButtonStatus );
		}
		
		else
		{
			u8_CorrectButtonReadFlag = E_OK;
			u8_WrongButtonReadFlag = E_OK;
		}
		
			 if (u8_CorrectButtonStatus == Pressed)
			{
				
				if(au8_SavedAnswer[u8_QuestionIndex] == RIGH_ANSWER)
				u8_QuestionGameState = RIGH_STATE;
				else
				u8_QuestionGameState = WRONG_STATE;
				
				u8_CorrectButtonReadFlag = E_OK;
			}
			  
				
			 if (u8_WrongButtonStatus == Pressed)
				{
					
					if(au8_SavedAnswer[u8_QuestionIndex] == WRONG_ASWER)
					u8_QuestionGameState = RIGH_STATE;
					
					else
					u8_QuestionGameState = WRONG_STATE;
					
					u8_WrongButtonReadFlag = E_OK;
				}
				
		break;
		
		case RIGH_STATE :
		
		if(u8_WriteCommandDoneFlag != WRITE_COMMAND_DONE )
		{ 
			
			u8_WriteCommandDoneFlag=LCD_clear();
			
		}
		else if(u8_WriteStringFlag != LCD_WRITE_STRING_DONE)
			{
				
				u8_WriteStringFlag = LCD_WriteString((uint8_t *)"Correct answer");
				
			}
			
			else
			{
				if(u8_QuestionIndex < MAX_NUMBER_OF_QUESTION)
				{
					u8_score ++ ;
					u8_QuestionIndex ++ ;
					u8_WriteStringFlag = E_OK;
					u8_WriteCommandDoneFlag = E_OK;
				}
				u8_Delay_action= PRINT_QUESTION_ON_LCD_STATE;
				u8_QuestionGameState = 	LCD_WAIT_COUNT_STATE;
				
			}
		
		
		
		break;
		case WRONG_STATE :
		if(u8_WriteCommandDoneFlag != WRITE_COMMAND_DONE )
		{
			u8_WriteCommandDoneFlag=LCD_clear();
		}
		else if(u8_WriteStringFlag != LCD_WRITE_STRING_DONE)
		
		u8_WriteStringFlag = LCD_WriteString((uint8_t *)"Wrong answer");
		
		else
		{
			if(u8_QuestionIndex < MAX_NUMBER_OF_QUESTION)
			{
			
				u8_QuestionIndex ++ ;
				u8_WriteStringFlag = E_OK;
				u8_WriteCommandDoneFlag = E_OK;
			}
			u8_Delay_action= PRINT_QUESTION_ON_LCD_STATE;
			u8_QuestionGameState = 	LCD_WAIT_COUNT_STATE;
			
		}
		break;
		case RESULT_STATE :
		if(u8_WriteCommandDoneFlag != WRITE_COMMAND_DONE )
		{
			u8_WriteCommandDoneFlag=LCD_clear();
		}
		else if(u8_WriteStringFlag != LCD_WRITE_STRING_DONE)
		
		u8_WriteStringFlag = LCD_WriteString((uint8_t *)"YOUR SCORE Is ");
		
		else
		{
			LCD_WriteChar( u8_score+CONVERT_INT_TO_CHAR);
			 u8_QuestionGameState = END_STATE;
			 u8_WriteStringFlag = E_OK;
			 u8_WriteCommandDoneFlag = E_OK;
		}
		break;
		case END_STATE:
		break;
		default:
		break;
		
		
		
	}
	return u8_QuesGameError;
}