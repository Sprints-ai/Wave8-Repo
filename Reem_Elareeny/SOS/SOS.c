/*
 * SOS.c
 *
 * Created: 3/10/2020 5:28:47 PM
 *  Author: Reem el-Areeny
 */ 
 

#include "SOS_Config.h"

/************************************************************************/
/*									  GLOBAL VARIABLES								   */
/************************************************************************/
Timer_cfg_s Timer_Config ;
SOS_Task TaskBuffer[BUFFER_SIZE] = {INITIAL_VALUE};


/************************************************************************/
/*								  GLOBAL STATIC VARIABLES							   */
/************************************************************************/
static uint8_t gu8_SOS_InitFlag = FALSE;
volatile static uint8_t ISR_Fire = FALSE;
static uint32_t u32_Buff_index = STARTING_INDEX;

/************************************************************************/
/*								  EXTERNAL VARIABLES							   */
/************************************************************************/
extern SOS_ConfigType SOS_Config;


/************************************************************************/
/*					  TIMER FUNCTIONS' IMPLEMENTATIONS							   */
/************************************************************************/
/**
 * Description: Initializes SOS module 
 * @return function status 
 */
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
		Timer_Config.Timer_Prescaler = TIMER_PRESCALER_64;
		
		ERR = Timer_Init(&Timer_Config);
		gu8_SOS_InitFlag = TRUE;
	}
	return ERR;
}


/**
 * Description: DeInitializes SOS module 
 * @return function status 
 */
ERROR_STATUS SOS_DeInit(void)
{
	ERROR_STATUS ERR = E_OK;
	if (gu8_SOS_InitFlag)
	{
		ERR = Timer_DeInit(Timer_Config.Timer_CH_NO);
		u32_Buff_index = STARTING_INDEX;
		gu8_SOS_InitFlag = FALSE;
	}
	else 
	{
		ERR = ERROR_SOS_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
	}
	return ERR;
}


/**
* Description: adds a new task to the task buffer
* @param: Task_Priority : ID of the Consumer
* @param: CBK_TOV : pointer to function (consumer)
* @param: delay_ms: period of the consumer
* @return function status
*/
ERROR_STATUS SOS_Create(uint8_t Task_Priority , void (*CBK_TOV)(void) , uint32_t delay_ms , uint8_t periodic_or_oneShot)
{
	ERROR_STATUS ERR = E_OK;
	
	static uint8_t u8_FirstCallFlag = TRUE;
	
	if (gu8_SOS_InitFlag)
	{
		if (CBK_TOV != NULL)
		{
			if (u8_FirstCallFlag)
			{
				ERR = Timer_Start(Timer_Config.Timer_CH_NO,TIMER_INITIAL_VALUE);
				u8_FirstCallFlag = FALSE;
			}
			
			if (Task_Priority < BUFFER_SIZE && TaskBuffer[Task_Priority].CBK_TOV == NULL /*u32_Buff_index < BUFFER_SIZE*/)
			{
				
				TaskBuffer[Task_Priority].Task_Priority = Task_Priority;
				
				TaskBuffer[Task_Priority].delay_ms = delay_ms;
				
				TaskBuffer[Task_Priority].CBK_TOV = CBK_TOV;
				
				TaskBuffer[Task_Priority].current_ticks = INITIAL_VALUE;

				TaskBuffer[Task_Priority].periodic_or_oneShot = periodic_or_oneShot;
				
				/*u32_Buff_index++;*/
				
			}
			else
			{
				ERR = ERROR_SOS_MODULE_ID + ERROR_FULL_BUFFER;
			}
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


/**
 * Description: stops a specific task from the task buffer
 * @param: Task_Priority : ID of the Consumer
 * @return function status 
 */
ERROR_STATUS SOS_Delete(uint8_t Task_Priority)
{
	ERROR_STATUS ERR = E_OK;
	uint32_t u32_Counter;
	uint8_t u8_IDFoundFlag = FALSE;
	
	for(u32_Counter=STARTING_INDEX; u32_Counter<BUFFER_SIZE; u32_Counter++)
	{
		if (TaskBuffer[u32_Counter].Task_Priority == Task_Priority)
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


/**
 * Description: starts implementing the tasks based on their periods
 * @return function status 
 */
ERROR_STATUS SOS_Run(void)
{
	ERROR_STATUS ERR = E_OK;
	while(1){
		uint32_t u32_Counter;	
		if (gu8_SOS_InitFlag)
		{
			if (ISR_Fire)
			{
				ISR_Fire = FALSE;
				
				for (u32_Counter=STARTING_INDEX; u32_Counter<BUFFER_SIZE ; u32_Counter++)
				{
					TaskBuffer[u32_Counter].current_ticks++;
					if((TaskBuffer[u32_Counter].CBK_TOV!=NULL) 
						&& (TaskBuffer[u32_Counter].current_ticks == TaskBuffer[u32_Counter].delay_ms))
					{

						if(TaskBuffer[u32_Counter].periodic_or_oneShot == PERIODIC){
							TaskBuffer[u32_Counter].CBK_TOV();
							TaskBuffer[u32_Counter].current_ticks = INITIAL_VALUE;
							}
							else if(TaskBuffer[u32_Counter].periodic_or_oneShot == ONE_SHOT)
							{
							TaskBuffer[u32_Counter].CBK_TOV();
							TaskBuffer[u32_Counter].current_ticks = INITIAL_VALUE;
							TaskBuffer[u32_Counter].periodic_or_oneShot = INITIAL_VALUE;
							TaskBuffer[u32_Counter].CBK_TOV = NULL;
						}
					}
					
				}
			}
		}
		else
		{
			ERR = ERROR_SOS_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
		}	
	}
	return ERR;
}


/************************************************************************/
/*					  TIMERS INTERRUPT SERVICE ROUTINES 						   */
/************************************************************************/
InterruptServiceRoutine(TIMER_OVF_VECT)
{
	
	ISR_Fire = TRUE;
	Timer_SetValue(TIMER_CHANNEL,TIMER_INITIAL_VALUE);
}