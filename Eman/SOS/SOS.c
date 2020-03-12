/*
 * TMU.c
 *
 * Created: 2/24/2020 10:00:29 AM
 *  Author: Ema
 */


#include "SOS.h"
#include "SOS_cfg.h"


SOSError_t SOS_Init (const SOS_ConfigType * ConfigPtr)
{
	SOSError_t retVal = E_OK;

	if(ConfigPtr != NULL)
	{
		//cli();										//disable the interrupts as this system is time trigger system so we use interrupts only with timer

		guSOS_TIMER = ConfigPtr->Timer_CH;			// save TMU_Timer channel

		switch(ConfigPtr->Timer_CH)
		{
			case TIMER_CH0:
			{
				Timer_cfg_s Timer_cfg = {TIMER_CH0,T0_COMP_MODE,TIMER_PRESCALER_64,T0_INTERRUPT_CMP,SOS_Set_Tick_Flag};
				Timer_Init(&Timer_cfg);
				Timer_Start(ConfigPtr->Timer_CH,COMP_VALUE);
			}
			break;
			case TIMER_CH1:
			{
				Timer_cfg_s Timer_cfg = {TIMER_CH1,T1_COMP_MODE_OCR1A_TOP,TIMER_PRESCALER_64,T1_INTERRUPT_CMP_1A,SOS_Set_Tick_Flag};
				Timer_Init(&Timer_cfg);
				Timer_Start(ConfigPtr->Timer_CH,COMP_VALUE);
			}
			break;
			case TIMER_CH2:
			{
				Timer_cfg_s Timer_cfg = {TIMER_CH2,T2_COMP_MODE,TIMER_PRESCALER_64,T2_INTERRUPT_CMP,SOS_Set_Tick_Flag};
				Timer_Init(&Timer_cfg);
				Timer_Start(ConfigPtr->Timer_CH,COMP_VALUE);
			}
			break;
			default:
			retVal = E_NOK;
			break;
		}
	}
	else
	{
		retVal = NULL_PTR;
	}

	return retVal;
}

SOSError_t SOS_DeInit (void)
{
	SOSError_t retVal = E_OK;

	if (guSOS_TIMER >= TIMER_CH0)
	{
	//	cli();			// disable global interrupt so TMU functionality will stop
		Timer_Stop(guSOS_TIMER);
	}
	else
	{
		retVal = NO_INIT;
	}

	return retVal;
}

SOSError_t SOS_Create_Task(const SOS_SW_Task * SW_Task)
{
	SOSError_t retVal = E_OK;

	if (SW_Task != NULL)			//check null pointer error
	{
		if((SW_Task->Task_delay>ZERO) && (SW_Task->Task_priority !=IDLE_TASK)&& ((SW_Task->Task_priority)<TASKS_MAX_NUM))
		{
					if (tasks_counter < TASKS_MAX_NUM)		//check full buffer
					{
						Tasks_buffer[SW_Task->Task_priority] = SW_Task->Task_delay;
						tasks_counter++;
					}
					else
					{
						retVal = FULL_BUFFER;
					}

			if(retVal == E_OK)				//check if no error occurs set call back function
			{
				/*set the call back function*/
				arrTask_CallBackfun[SW_Task->Task_priority] = SW_Task->Task_CallBackfun;

			//	sei();			//enable interrupts to start getting the ISR after the first start
			}
		}
		else
		{
			retVal = INVALID_PARAM;
		}
	}
	else
	{
		retVal = NULL_PTR;
	}

	return retVal;
}

SOSError_t SOS_Delete_Task(const SOS_SW_Task * SW_Task)
{
	SOSError_t retVal = E_OK;

	if( SW_Task != NULL)
	{
				if ((tasks_counter > ZERO) && ((Tasks_buffer[SW_Task->Task_priority]) !=IDLE_TASK))
				{
					tasks_counter--;
					Tasks_buffer[SW_Task->Task_priority] = ZERO;
				}
				else
				{
					retVal = STOP_NO_START;
				}

		if (retVal == E_OK)
		{
			arrTask_CallBackfun[SW_Task->Task_priority] = NULL;
		}

	}
	else
	{
		retVal = NULL_PTR;
	}

	return retVal;
}

void SOS_Run(void)
{
	uint8_t u8_index =ZERO;

	if(SOS_flag)
	{
		SOS_flag = ZERO;
		Tick_count++;

		/*loop over tasks buffer*/

		while(Tasks_buffer[u8_index])
		{
			if ((Tick_count % Tasks_buffer[u8_index] == ZERO) && (Tick_count / Tasks_buffer[u8_index] > ZERO))
			{
				arrTask_CallBackfun[u8_index]();			//call back function call
			}
			u8_index++;
		}
	}
}

void SOS_Set_Tick_Flag(void)
{
	SOS_flag = 1;
}
