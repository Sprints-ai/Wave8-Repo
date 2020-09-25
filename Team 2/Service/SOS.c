/*
 ============================================================================
 Name        : TMU.c
 Author      : Muhammed Gamal
 Description : this file contains the functions implementation of the SOS
 ============================================================================
 */


/*********************************includes**********************************/
#include "SOS.h"
#include "../MCAL/DIO.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define NULL_PTR ((void*)0)
#define CLEAR 0
#define COUNTER 0
#define DELAY 1
#define START 0
#define FLAG_HIGH 1
#define FLAG_LOW 0
#define NUM_OF_ARR_ELEMENTS 2
#define TIMER0_COMPARE_VALUE 250
#define ONE 1
#define FIRST_CHANNEL 0
#define TASK_EXCUTED 1
#define NO_TASK_EXCUTED 0
/***************************************************************************/


/******************************global variables*****************************/
static SOS_ConfigChannel * SOS_Tasks = NULL_PTR;
static uint8_t SOS_Status = SOS_NOT_INITIALIZED;
void (*g8_functionHoler[NUMBER_OF_TASKS])(void);
uint32_t gu32_Counter_Delay_Arr[NUMBER_OF_TASKS][NUM_OF_ARR_ELEMENTS];
uint8_t gu8_Active_Channels[NUMBER_OF_TASKS];
uint8_t Loop_Counter;
void (*g8_IdleState_PTR)(void)=NULL_PTR;
uint8_t Timer_Channel;
/***************************************************************************/




/************************************************************************************
* Function Name: SOS_InitRunable
* Parameters (in): ConfigPtr- pointer to the SOS configuration structure
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: this function is responsible for Initiating the SOS
************************************************************************************/
ERROR_STATUS SOS_InitRunable(SOS_Config* ConfigPtr)
{
	uint8_t u8_status=E_ok;
	St_TimerCfg timer0_stru_init=
	{
		timer0_stru_init.Timer_CH_NO=Timer_0,
		timer0_stru_init.Timer_Mode=T0_COMP_MODE,
		timer0_stru_init.Timer_Polling_Or_Interrupt=T0_INTERRUPT_CMP,
		timer0_stru_init.Timer_Prescaler=T0_PRESCALER_64,
	};
	if(ConfigPtr == NULL_PTR || SOS_Status == SOS_INITIALIZED)
	{
		u8_status |= E_NOk;
	}
	else
	{
		switch(ConfigPtr->Timer_CH_NO)
		{
			case Timer_0:
				u8_status |= Timer_Init(&timer0_stru_init);
				Timer_Channel=Timer_0;
				break;
			case Timer_1:

				u8_status |= E_NOk;
				break;
			case Timer_2:

				u8_status |= E_NOk;
				break;
			default:
				u8_status |= E_NOk;
				break;
		}
		SOS_Tasks = SOS_TasksConfiguration.Tasks;
		SOS_Status = SOS_INITIALIZED;
	}

	if(u8_status == E_ok)
	{
		u8_status = E_ok;
	}
	else
	{
		u8_status = E_NOk;
	}
	return u8_status;
}




/************************************************************************************
* Function Name: Task_Start
* Parameters (in): void (*ptr)(void)- pointer to call back task
*                  channel_id-
*                  repetition-
*                  delay-
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: this function is responsible for starting the SOS tasks
* NOTE: the channel_id also represent the channel priority
************************************************************************************/
ERROR_STATUS Task_Start(ERROR_STATUS (*ptr)(void), uint8_t channel_id, uint8_t repetition, uint16_t delay)
{
	uint8_t u8_status=E_ok;
	if(ptr == NULL_PTR ||   /*pointer to function is null*/
		SOS_Status == SOS_NOT_INITIALIZED ||  /*SOS is not initialized*/
		((gu8_Active_Channels[channel_id]==channel_id) && (channel_id!=FIRST_CHANNEL)) ||  /*restart a channel*/
		channel_id >= NUMBER_OF_TASKS ||  /*the SOS buffer is full*/
		repetition>PERIODIC  /*unexpected repetition input*/
	  )
	{
		u8_status |= E_NOk;
	}

	else
	{
		switch(Timer_Channel)
		{
			case Timer_0:
				Timer_Start(Timer_0,TIMER0_COMPARE_VALUE);
				break;
			case Timer_1:

				u8_status |= E_NOk;
				break;
			case Timer_2:

				u8_status |= E_NOk;
				break;
			default:
				u8_status |= E_NOk;
		}

		g8_functionHoler[channel_id]=ptr;
		gu32_Counter_Delay_Arr[channel_id][COUNTER]=CLEAR;
		gu32_Counter_Delay_Arr[channel_id][DELAY]=delay;
		SOS_Tasks[channel_id].Repetition=repetition;
		gu8_Active_Channels[channel_id]=channel_id;
	}

	if(u8_status == E_ok)
	{
		u8_status = E_ok;
	}
	else
	{
		u8_status = E_NOk;
	}
	return u8_status;
}




/************************************************************************************
* Function Name: SOS_Runable
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: this function is responsible for managing the SOS
************************************************************************************/
void SOS_Runable(void)
{
	uint8_t Tick_state=NO_TASK_EXCUTED;
	if(gu8_Timer0CompFlag==FLAG_HIGH)
	{
		gu8_Timer0CompFlag=FLAG_LOW;
		for(Loop_Counter=START;Loop_Counter<NUMBER_OF_TASKS;Loop_Counter++)
		{
			if(gu32_Counter_Delay_Arr[Loop_Counter][COUNTER]==gu32_Counter_Delay_Arr[Loop_Counter][DELAY] && gu32_Counter_Delay_Arr[Loop_Counter][DELAY]!=0)
			{
				Tick_state=TASK_EXCUTED;
				(*g8_functionHoler[Loop_Counter])();
				if(SOS_Tasks[Loop_Counter].Repetition==PERIODIC)
				{
					gu32_Counter_Delay_Arr[Loop_Counter][COUNTER]=CLEAR;
				}
				else
				{
					gu32_Counter_Delay_Arr[Loop_Counter][COUNTER]=gu32_Counter_Delay_Arr[Loop_Counter][DELAY]+ONE;
				}
			}
			gu32_Counter_Delay_Arr[Loop_Counter][COUNTER]++;
		}

		if(g8_IdleState_PTR!=NULL_PTR && Tick_state==NO_TASK_EXCUTED)
		{
			g8_IdleState_PTR();
		}

	}
}



/************************************************************************************
* Function Name: SOS_DeInit
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: this task is responsible for de-initializing the SOS
************************************************************************************/
ERROR_STATUS SOS_DeInit(void)
{
	uint8_t u8_status=E_ok;
	if(SOS_Status == SOS_NOT_INITIALIZED)
	{
		u8_status |= E_NOk;
	}
	else
	{
		Timer_DeInit(Timer_0);
		SOS_Status = SOS_NOT_INITIALIZED;

		for(int i=START;i<NUMBER_OF_TASKS;i++)
		{
			u8_status |= Task_Stop(i);
		}
	}

	if(u8_status == E_ok)
	{
		u8_status = E_ok;
	}

	else
	{
		u8_status = E_NOk;
	}

	return u8_status;
}



/************************************************************************************
* Function Name: Task_Stop
* Parameters (in): Channel_ID
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: this function stops the any running task according to the task id
************************************************************************************/
ERROR_STATUS Task_Stop(uint8_t Channel_ID)
{
	uint8_t u8_status=E_ok;

	/* check if the task has been started or not
	 * no need to check if the task is initialized or not since no task
	 * will start without initializing the module
	 *  */
	if(gu8_Active_Channels[Channel_ID]!=Channel_ID)
	{
		u8_status |= E_NOk;
	}
	else
	{
		g8_functionHoler[Channel_ID]=NULL_PTR;
		gu32_Counter_Delay_Arr[Channel_ID][COUNTER]=CLEAR;
		gu32_Counter_Delay_Arr[Channel_ID][DELAY]=CLEAR;
		SOS_Tasks[Channel_ID].Repetition=ONE_SHOOT;
		gu8_Active_Channels[Channel_ID]=CLEAR;
	}

	if(u8_status == E_ok)
	{
		u8_status = E_ok;
	}

	else
	{
		u8_status = E_NOk;
	}

	return u8_status;
}




/************************************************************************************
* Function Name: SOS_SetIdleTask
* Parameters (in): void (*callback)(void)- pointer to the idle task
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: this function sets the call back to the idle task
************************************************************************************/
ERROR_STATUS SOS_SetIdleTask(void (*callback)(void))
{
	uint8_t u8_status=E_ok;

	if(callback!=NULL_PTR)
	{
		g8_IdleState_PTR=callback;
	}

	else
	{
		u8_status = E_NOk;
	}

	return u8_status;
}




