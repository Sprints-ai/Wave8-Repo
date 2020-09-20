/*
 * LCD_OS_Task.c
 *
 * Created: 3/13/2020 5:46:00 PM
 *  Author: Reem
 */ 


#include "ECUAL/includes/LCD.h"
#include "ECUAL/includes/pushButton.h"
#include "Services/includes/SOS.h"

#define QUESTION1      1
#define QUESTION2      2
#define QUESTION3      3
#define QUESTION4      4
#define QUESTION5      5
#define REWARD         6
#define AGAIN          7
#define EXIT           8

#define LEDS_STATE1    8
#define LEDS_STATE2    9
#define LEDS_STATE3    10
#define LEDS_STATE4    11

#define LEDS_STOP      12

static uint8_t gu8_appSM;
static uint8_t gu8_questionfinished;
static uint8_t gu8_RewardSM;
static strSOS_TASK_Cfg_t RewardTask;
static uint8_t YesFlag;
static uint8_t NoFlag;
static uint8_t gu8RewardFlag;

void App(void);
void Reward(void);
void BtnTask(void);

int main(void)
{
	strSOS_TASK_Cfg_t Task1,Task2;
	strDIO_Cfg_s astr_DIOcfg={ GPIOB,
		(BIT4|BIT5|BIT6|BIT7),
	OUTPUT};
	
	Task1.Delay_TimeMs = 2;
	Task1.Priority=3;
	Task1.SOS_MODE = PERIODIC;
	Task1.Task_id =2;
	Task1.SOS_Cbk_ptr = LCD_Runnable;
	
	Task2.Delay_TimeMs = 200;
	Task2.Priority=1;
	Task2.SOS_MODE = PERIODIC;
	Task2.Task_id =1;
	Task2.SOS_Cbk_ptr = BtnTask;
	
	RewardTask.Delay_TimeMs = 500;
	RewardTask.Priority=2;
	RewardTask.Task_id=3;
	RewardTask.SOS_Cbk_ptr = Reward;
	RewardTask.SOS_MODE=PERIODIC;
	
	gu8_appSM = QUESTION1;
	gu8_RewardSM =LEDS_STOP;
	YesFlag = FALSE;
	NoFlag = FALSE;
	gu8RewardFlag= FALSE;
	
	SOS_Init();
	DIO_init(&astr_DIOcfg);
	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);
	SOS_Create_Task(&Task1);
	SOS_Create_Task(&Task2);
	SOS_Create_Task(&RewardTask);
    while(1)
    {
		SOS_Run();
		App();
		/*if(Flag == 0)
		{
			ERR = DisplayData("ONE");
			if(ERR == E_OK)
			Flag=1;
		}
		if (YesFlag == TRUE)
		{
			YesFlag =FALSE;
			DIO_Toggle(GPIOB,BIT7);
			Flag=2;
				
		}
		else if(NoFlag == TRUE)
		{
			NoFlag = FALSE;
			DIO_Toggle(GPIOB,BIT6);
			Flag=3;
		}
		
		
		if (Flag == 2)
		{
			ERR = DisplayData("TWO");
			if(ERR == E_OK)
			Flag=1;
		}
		
		if (Flag == 3)
		{
			ERR = DisplayData("THREE");
			if(ERR == E_OK)
			Flag=1;
		}*/
        //TODO:: Please write your application code 
    }
}
void BtnTask(void)
{
	if (pushButtonGetStatus(BTN_0)== Pressed)
	{
		YesFlag = TRUE;
		
	}
	if (pushButtonGetStatus(BTN_1)== Pressed)
	{
		NoFlag = TRUE;
		
	}
}

void App(void)
{
	static uint8_t au8RightAnswerCounter;
	ERROR_STATUS ERR;
	static uint8_t au8WriteFlag;
	static uint8_t au8_RewardFlag;
	switch(gu8_appSM)
	{
		case QUESTION1:
			gu8_questionfinished = FALSE;
			if(au8WriteFlag == 0)
			{
				ERR = DisplayData("Do write nicely?");//yes
			}
			if (ERR == E_OK)
			{
				au8WriteFlag=1;
				au8_RewardFlag=0;
				
				if (YesFlag == TRUE)
				{
					YesFlag =FALSE;
							
					au8RightAnswerCounter++;
					gu8_appSM = QUESTION2;
					au8WriteFlag=0;
					ERR = E_NOK;
				}
				else if(NoFlag == TRUE)
				{
					NoFlag =FALSE;
					gu8_appSM = QUESTION2;
					au8WriteFlag=0;
					ERR = E_NOK;
				}	
			}
		break;
		case QUESTION2:
			if(au8WriteFlag == 0)
			{
				ERR = DisplayData("Do you like eatiing chips?");//yes
			}
			if (ERR == E_OK)
			{
				au8WriteFlag=1;
				
				if (YesFlag == TRUE)
				{
					YesFlag =FALSE;
					au8RightAnswerCounter++;
					gu8_appSM = QUESTION3;
					au8WriteFlag=0;
					ERR = E_NOK;
				}
				else if(NoFlag == TRUE)
				{
					NoFlag =FALSE;
					gu8_appSM = QUESTION3;
					au8WriteFlag=0;
					ERR = E_NOK;
				}
				
			}
		
		break;
		case QUESTION3:
		if(au8WriteFlag == 0)
		{
			ERR = DisplayData("Do you drink Cofffee?");//yes
		}
		if (ERR == E_OK)
		{
			au8WriteFlag=1;
			
			if (YesFlag == TRUE)
			{
				YesFlag =FALSE;
				au8RightAnswerCounter++;
				gu8_appSM = QUESTION4;
				au8WriteFlag=0;
				ERR = E_NOK;
			}
			else if(NoFlag == TRUE)
			{
				NoFlag =FALSE;
				gu8_appSM = QUESTION4;
				au8WriteFlag=0;
				ERR = E_NOK;
			}
			
		}
		break;
		case QUESTION4:
		if(au8WriteFlag == 0)
		{
			ERR = DisplayData("Do you have a Carr?");//no
		}
		if (ERR == E_OK)
		{
			au8WriteFlag=1;
			
			if (YesFlag == TRUE)
			{
				YesFlag =FALSE;
				gu8_appSM = QUESTION5;
				au8WriteFlag=0;
				ERR = E_NOK;
			}
			else if(NoFlag == TRUE)
			{
				NoFlag =FALSE;
				au8RightAnswerCounter++;
				gu8_appSM = QUESTION5;
				au8WriteFlag=0;
				ERR = E_NOK;
			}
		}
		break;
		case QUESTION5:
		if(au8WriteFlag == 0)
		{
			ERR = DisplayData("Do you have Instaagram?");//no
		}
		if (ERR == E_OK)
		{
			au8WriteFlag=1;
			if (YesFlag == TRUE)
			{
				YesFlag =FALSE;
				gu8_appSM = REWARD;
				au8WriteFlag=0;
				ERR = E_NOK;
			}
			else if(NoFlag == TRUE)
			{
				NoFlag =FALSE;
				au8RightAnswerCounter++;
				gu8_appSM = REWARD;
				au8WriteFlag=0;
				ERR = E_NOK;
			}
		}
		/*
		if (gu8_questionfinished == TRUE)
		{
			if(au8_RewardFlag == 0)
			{
				if(au8RightAnswerCounter == 5)
				{
					ERR = DisplayData("Congrats !");
					if (ERR == E_OK)
					{
						au8_RewardFlag=1;
						gu8_RewardSM = LEDS_STATE1;
						gu8RewardFlag =TRUE;
						au8RightAnswerCounter=0;
					}
				}
				else
				{
					ERR = DisplayData("Hard Luck !");
					if (ERR == E_OK)
					{
						au8_RewardFlag=1;
						gu8_RewardSM = LEDS_STOP;
						gu8RewardFlag =FALSE;
						au8RightAnswerCounter=0;
						//	gu8_appSM = AGAIN;
						
					}
				}
			}
			if(gu8RewardFlag == FALSE)
			{
				gu8_appSM = AGAIN;
				au8WriteFlag=0;
				ERR = E_NOK;
				au8_RewardFlag=0;
				gu8_questionfinished =FALSE;
			}
			
		}*/
		break;
		case REWARD:
			if(au8RightAnswerCounter == 5)
			{
				if(au8WriteFlag == 0)
				{
					ERR = DisplayData("Congrats !");
				}
				
				if (ERR == E_OK)
				{
					gu8_RewardSM = LEDS_STATE1;
					gu8RewardFlag =TRUE;
					au8WriteFlag=1;
					au8_RewardFlag=1;
					
					
					au8RightAnswerCounter=0;
					
				}
			}
			else
			{
				
				if(au8WriteFlag == 0)
				{
					ERR = DisplayData("Hard Luck !");
				}
				if (ERR == E_OK)
				{
					au8WriteFlag=1;
					au8_RewardFlag=1;
					gu8_RewardSM = LEDS_STOP;
					gu8RewardFlag =FALSE;
					au8RightAnswerCounter=0;
					
					//	gu8_appSM = AGAIN;
					
				}
			}
			
			if(gu8RewardFlag == FALSE)
			{
				if (YesFlag == TRUE || NoFlag ==TRUE)
				{
					YesFlag =FALSE;
					NoFlag =FALSE;
					au8RightAnswerCounter=0;
					gu8_appSM = AGAIN;
					au8WriteFlag=0;
					ERR = E_NOK;
				}
				
			}
		break;
		case AGAIN:
		if(au8WriteFlag == 0)
		{
			ERR = DisplayData("Play Again?");
		}
		if (ERR == E_OK)
		{
			au8WriteFlag=1;
			
			if (YesFlag == TRUE)
			{
				YesFlag =FALSE;
				au8RightAnswerCounter=0;
				gu8_appSM = QUESTION1;
				au8WriteFlag=0;
				ERR = E_NOK;
			}
			else if(NoFlag == TRUE)
			{
				NoFlag =FALSE;
				gu8_appSM = EXIT;
				au8WriteFlag=0;
				ERR = E_NOK;
			}
		}
		break;
		case EXIT:
		if(au8WriteFlag == 0)
		{
			ERR = DisplayData("Thanks!");
		}
		if (ERR == E_OK)
		{
			au8WriteFlag = 1;
		}
		break;
	}
}
void Reward(void)
{
	if(gu8RewardFlag == TRUE)
	{
		switch(gu8_RewardSM)
		{
			case LEDS_STATE1:
				DIO_Toggle(GPIOB,BIT4);
				DIO_Toggle(GPIOB,BIT7);
				gu8_RewardSM = LEDS_STATE2;
			break;
			case LEDS_STATE2:
				DIO_Toggle(GPIOB,BIT5);
				DIO_Toggle(GPIOB,BIT6);
				gu8_RewardSM = LEDS_STATE3;
			break;
			
			case LEDS_STATE3:
				DIO_Toggle(GPIOB,BIT5);
				DIO_Toggle(GPIOB,BIT6);
				gu8_RewardSM = LEDS_STATE4;

			break;
			case LEDS_STATE4:
			
				DIO_Toggle(GPIOB,BIT4);
				DIO_Toggle(GPIOB,BIT7);
				gu8_RewardSM = LEDS_STOP;
			
			break;
			case LEDS_STOP:
			
			gu8RewardFlag =FALSE;
			break;
		}
	}
}