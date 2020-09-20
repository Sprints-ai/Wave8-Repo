/*
 * TMU.c
 *
 * Created: 2/24/2020 11:51:32 AM
 *  Author: Ehab & Reem
 */ 


#include "TMU_Config.h"


Timer_cfg_s Timer_Config ;

TMU_Task TaskBuffer[BUFFER_SIZE] = {0};
	
static uint8_t gu8_TMU_InitFlag = FALSE;

volatile static uint8_t ISR_Fire = FALSE;

static uint32_t u32_Buff_index = STARTING_INDEX;

extern TMU_ConfigType TMU_Config;

ERROR_STATUS TMU_Init(void)
{
	ERROR_STATUS ERR = E_OK; 
	
	if (TMU_Config.Timer_Channel != TIMER_CH0 && TMU_Config.Timer_Channel != TIMER_CH2 )
	{
		ERR = ERROR_TMU_MODULE_ID + ERROR_INVALID_PARAMETER;
	}
	else if (gu8_TMU_InitFlag)
	{
		ERR = ERROR_TMU_MODULE_ID + ERROR_MODULE_ALREADY_INITIALIZED;
	}
	else
	{
		Timer_Config.Timer_CH_NO = TMU_Config.Timer_Channel;
		Timer_Config.Timer_Mode = TIMER_MODE;
		Timer_Config.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
		Timer_Config.Timer_Prescaler = TIMER_PRESCALER_64;
		
		ERR = Timer_Init(&Timer_Config);
		gu8_TMU_InitFlag = TRUE;
	}
	return ERR;
}

ERROR_STATUS TMU_DeInit(void)
{
	ERROR_STATUS ERR = E_OK;
	if (gu8_TMU_InitFlag)
	{
		ERR = Timer_DeInit(Timer_Config.Timer_CH_NO);
		u32_Buff_index = STARTING_INDEX;
		gu8_TMU_InitFlag = FALSE;
	}
	else 
	{
		ERR = ERROR_TMU_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
	}
	return ERR ;
}

ERROR_STATUS TMU_Start_Timer (uint8_t Task_ID , void (*CBK_TOV)(void) , uint32_t delay_ms )
{
	ERROR_STATUS ERR = E_OK;
	
	static uint8_t u8_FirstCallFlag = TRUE;
	
	if (gu8_TMU_InitFlag)
	{
		if (CBK_TOV !=NULL)
		{
			if (u8_FirstCallFlag)
			{
				ERR = Timer_Start(Timer_Config.Timer_CH_NO,5);
				u8_FirstCallFlag = FALSE;
			}
			
			if (u32_Buff_index < BUFFER_SIZE)
			{
				TaskBuffer[u32_Buff_index].Task_ID = Task_ID;
				
				TaskBuffer[u32_Buff_index].delay_ms = delay_ms;
				
				TaskBuffer[u32_Buff_index].CBK_TOV = CBK_TOV;
				
				TaskBuffer[u32_Buff_index].current_ticks = 0;
				
				u32_Buff_index++;
				
			}
			else
			{
				ERR = ERROR_TMU_MODULE_ID + ERROR_FULL_BUFFER;
			}
		}
		else 
		{
			ERR = ERROR_TMU_MODULE_ID + ERROR_NULL_POINTER;
		}
		
	}
	
	else
	{
		ERR = ERROR_TMU_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
	}
	
	return ERR ;
}

ERROR_STATUS TMU_Stop_Timer(uint8_t Task_ID)
{
	ERROR_STATUS ERR = E_OK;
	uint32_t u32_Counter;
	uint8_t u8_IDFoundFlag = FALSE;
	
	for(u32_Counter=STARTING_INDEX; u32_Counter<BUFFER_SIZE; u32_Counter++)
	{
		if (TaskBuffer[u32_Counter].Task_ID == Task_ID)
		{				
			TaskBuffer[u32_Counter].CBK_TOV = NULL;
			u8_IDFoundFlag = TRUE;
		}
	}
	if (!u8_IDFoundFlag)
	{
		ERR = ERROR_TMU_MODULE_ID + ERROR_INVALID_PARAMETER;
	}
	return ERR ;
}

ERROR_STATUS TMU_Dispatch(void)
{
	ERROR_STATUS ERR = E_OK;
	uint32_t u32_Counter;
	
	if (gu8_TMU_InitFlag)
	{
		if (ISR_Fire)
		{
			ISR_Fire = FALSE;
			
			for (u32_Counter=STARTING_INDEX; u32_Counter<BUFFER_SIZE ; u32_Counter++)
			{
				TaskBuffer[u32_Counter].current_ticks++;
				if(TaskBuffer[u32_Counter].CBK_TOV!=NULL  &&  (TaskBuffer[u32_Counter].current_ticks == TaskBuffer[u32_Counter].delay_ms))
				{
					TaskBuffer[u32_Counter].CBK_TOV();
					
					TaskBuffer[u32_Counter].current_ticks=0;
				}
				
			}
		}
	}
	else
	{
		ERR = ERROR_TMU_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
	}
	
	return ERR;
}

InterruptServiceRoutine(TIMER_OVF_VECT)
{
	
	ISR_Fire = TRUE;
	
	TCNT = 5;
}