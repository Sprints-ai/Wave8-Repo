/*
 * SOS.c
 *
 * Created: 2/24/2020 11:51:32 AM
 *  Author: Ehab & Reem
 */ 


#include "SOS_Config.h"






Timer_cfg_s Timer_Config ;

SOS_Task TaskBuffer[BUFFER_SIZE] = {EMPTY_BUFFER};
	
static uint8_t gu8_SOS_InitFlag = FALSE;

volatile static uint8_t ISR_Fire = INITIAL_VALUE_ZERO;

static uint32_t gu32_BuffIndex = STARTING_INDEX;



static void ISR_Flag_Setter_Fn (void)
{
	ISR_Fire++;
}

static void TaskBufferBubbleSort(void)
{
	uint32_t u32_localIterator_I = STARTING_INDEX , u32_localIterator_J = STARTING_INDEX ;
	SOS_Task Temp_Task ;
	
	for (u32_localIterator_I = STARTING_INDEX ; u32_localIterator_I < gu32_BuffIndex ; u32_localIterator_I++)
	{
		for (u32_localIterator_J = STARTING_INDEX ; u32_localIterator_J < (gu32_BuffIndex - u32_localIterator_I - NEXT_INDEX) ; u32_localIterator_J++)
		{
			if (TaskBuffer[u32_localIterator_J].Task_ID > TaskBuffer[u32_localIterator_J + NEXT_INDEX].Task_ID)
			{
				Temp_Task = TaskBuffer[u32_localIterator_J];
				TaskBuffer[u32_localIterator_J] = TaskBuffer[u32_localIterator_J + NEXT_INDEX];
				TaskBuffer[u32_localIterator_J + NEXT_INDEX] = Temp_Task;
			}
		}
	}
}

ERROR_STATUS SOS_Init(void)
{
	ERROR_STATUS ERR = E_OK; 
	
	if (SOS_Config.Timer_Channel != TIMER_CH0 && SOS_Config.Timer_Channel != TIMER_CH2 )
	{
		ERR = ERROR_SOS_MODULE_ID + ERROR_INVALID_PARAMETER;
	}
	else if (gu8_SOS_InitFlag)
	{
		ERR = ERROR_SOS_MODULE_ID + ERROR_MODULE_ALREADY_INITIALIZED;
	}
	else
	{
		Timer_Config.Timer_CH_NO = SOS_Config.Timer_Channel;
		Timer_Config.Timer_Mode = TIMER_MODE;
		Timer_Config.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
		Timer_Config.Timer_Prescaler = TIMER_PRESCALER_1024;
		Timer_Config.Timer_Cbk_ptr = ISR_Flag_Setter_Fn;
		
		ERR = Timer_Init(&Timer_Config);
		gu8_SOS_InitFlag = TRUE;
		
		
	}
	return ERR;
}

ERROR_STATUS SOS_DeInit(void)
{
	ERROR_STATUS ERR = E_OK;
	if (gu8_SOS_InitFlag)
	{
		ERR = Timer_DeInit(Timer_Config.Timer_CH_NO);
		gu32_BuffIndex = STARTING_INDEX;
		gu8_SOS_InitFlag = FALSE;
	}
	else 
	{
		ERR = ERROR_SOS_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
	}
	return ERR ;
}

ERROR_STATUS SOS_Start_Timer (uint8_t Task_ID , void (*CBK_TOV)(void) , uint32_t delay_ms , uint8_t Periodicity)
{
	ERROR_STATUS ERR = E_OK;
	
	static uint8_t u8_FirstCallFlag = TRUE;
	
	if (gu8_SOS_InitFlag)
	{
		if (CBK_TOV !=NULL)
		{
			if (u8_FirstCallFlag)
			{
				ERR = Timer_Start(Timer_Config.Timer_CH_NO,TCNT_PRELOAD_VALUE);
				u8_FirstCallFlag = FALSE;
			}
			
			if (gu32_BuffIndex < BUFFER_SIZE)
			{
				TaskBuffer[gu32_BuffIndex].Task_ID = Task_ID;
				
				TaskBuffer[gu32_BuffIndex].delay_ms = delay_ms;
				
				TaskBuffer[gu32_BuffIndex].CBK_TOV = CBK_TOV;
				
				TaskBuffer[gu32_BuffIndex].Periodicity = Periodicity;
				
				TaskBuffer[gu32_BuffIndex].current_ticks = INITIAL_VALUE_ZERO;
				
				gu32_BuffIndex++;
				
			}
			else
			{
				ERR = ERROR_SOS_MODULE_ID + ERROR_FULL_BUFFER;
			}
			
			TaskBufferBubbleSort();
		}
		else 
		{
			ERR = ERROR_SOS_MODULE_ID + ERROR_NULL_POINTER;
		}
		
	}
	
	else
	{
		ERR = ERROR_SOS_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
	}
	
	return ERR ;
}

ERROR_STATUS SOS_Stop_Timer(uint8_t Task_ID)
{
	ERROR_STATUS ERR = E_OK;
	uint32_t u32_Counter;
	uint8_t u8_IDFoundFlag = FALSE;
	
	for(u32_Counter=STARTING_INDEX; u32_Counter</*BUFFER_SIZE*/gu32_BuffIndex; u32_Counter++)
	{
		if (TaskBuffer[u32_Counter].Task_ID == Task_ID)
		{				
			TaskBuffer[u32_Counter].CBK_TOV = NULL;
			u8_IDFoundFlag = TRUE;
		}
	}
	if (!u8_IDFoundFlag)
	{
		ERR = ERROR_SOS_MODULE_ID + ERROR_INVALID_PARAMETER;
	}
	return ERR ;
}

ERROR_STATUS SOS_Dispatch(void)
{
	
	ERROR_STATUS ERR = E_OK;
	uint32_t u32_Counter;
	
	if (gu8_SOS_InitFlag)
	{
		if (ISR_Fire == 3)
		{
			ISR_Fire = INITIAL_VALUE_ZERO;
			Timer_SetValue(SOS_Config.Timer_Channel,TCNT_PRELOAD_VALUE);
			
			for (u32_Counter=STARTING_INDEX; u32_Counter<BUFFER_SIZE ; u32_Counter++)
			{
				TaskBuffer[u32_Counter].current_ticks++;
				if(TaskBuffer[u32_Counter].CBK_TOV!=NULL  &&  (TaskBuffer[u32_Counter].current_ticks == TaskBuffer[u32_Counter].delay_ms))
				{
					TaskBuffer[u32_Counter].CBK_TOV();
					
					switch (TaskBuffer[u32_Counter].Periodicity)
					{
						case ONESHOT:
							TaskBuffer[u32_Counter].CBK_TOV = NULL;
							break;
							
						case PERIODIC:
							TaskBuffer[u32_Counter].current_ticks=INITIAL_VALUE_ZERO;
							break;
					}
				}
				
			}
		}
	}
	else
	{
		ERR = ERROR_SOS_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
	}
	
	return ERR;
}

