/*
 * TMU.c
 *
 * Created: 2/24/2020 11:34:40 AM
 *  Author: ahmed
 */ 

#include "std_types.h"
#include "registers.h"
#include "interrupts.h"
#include "Timer.h"
#include "TMU.h"
#include "TMU_config.h"

/************************************************************************/
/*                             General macros                           */
/************************************************************************/

#define NOT_VALID_TASK			(0xFF)
#define MS_TO_US_CONVERSION		(1000)
#define TICK_4US				(4)
#define GLOBAL_INT_ENABLE_BIT	(7)

/************************************************************************/
/*                        Operation global variables                    */
/************************************************************************/

/*TMU tasks list which is an array of tasks*/
static Task_ConfigType task_arr[TASKS_NUMBER] = {0};

/*Counter used to count tasks of the all system*/	
static uint8_t gu8_task_counter = 0;

/*Flag indicates whether the TMU is initialized or not*/
static uint8_t gu8_init_flag = 0;

/*Variable holds the timer selected channel*/
static uint8_t gu8_timer_selectedChannel = 0;

/*Variable used in holding the value to be loaded for the timer*/
static uint8_t gu8_timer_tickTime = 0;

/*Flag indicates whether the dispatcher is started or not*/
static uint8_t gu8_dispatcherStart = 0;

/*Flag indicates the dispatcher operation is running or not*/
static volatile uint8_t gu8_dispatcherStartOperation = 0;

/*Variable holds the system ticks*/
static volatile uint32_t gu32_ticksCount = 0;

/************************************************************************/
/*                             TMU functions' definition                */
/************************************************************************/

EnmTMUError_t TMU_Init(const TMU_ConfigType * ConfigPtr)
{
	/*Variable used to report the returned error*/	
	EnmTMUError_t err_var = 0; 
	
	/*Checking the pointer is NULL or not*/
	if(ConfigPtr == NULL)
	{
		err_var = NullPtr_Error;
	} 
	else
	{
		/*Checking whether the TMU is initialized already or not*/
		if (gu8_init_flag)
		{
			err_var = MultipleInit_Error;
		}
		else
		{
			/*Setting selected timer channel to 4us tick count*/
			switch(ConfigPtr -> timer_channel)
			{
				case TMU_TIM_CH0:
				Timer_Init(TIMER_CH0 , TIMER_MODE , TIMER_PRESCALER_64 , TIMER_INTERRUPT_MODE);
				gu8_timer_selectedChannel = TIMER_CH0;
				gu8_timer_tickTime = (ConfigPtr -> timer_tick_time_ms);
				break;
				
				case TMU_TIM_CH1:
				Timer_Init(TIMER_CH1 , TIMER_MODE , TIMER_PRESCALER_64 , TIMER_INTERRUPT_MODE);
				gu8_timer_selectedChannel = TIMER_CH1;
				gu8_timer_tickTime = (ConfigPtr -> timer_tick_time_ms);
				break;

				case TMU_TIM_CH2:
				Timer_Init(TIMER_CH2 , TIMER_MODE , TIMER_PRESCALER_64 , TIMER_INTERRUPT_MODE);
				gu8_timer_selectedChannel = TIMER_CH2;
				gu8_timer_tickTime = (ConfigPtr -> timer_tick_time_ms);
				break;
				
				/*Invalid channel selected error*/
				default: err_var = InvalidChannel_Error;
			}
			
			/*Rising the init flag and returning operation success*/
			gu8_init_flag++;
			err_var = OperationSuccess;
		}	
	}
	
	return err_var;
}

EnmTMUError_t TMU_DeInit(void)
{
	/*Variables used in error indication*/
	EnmTMUError_t err_var = 0;
	ERROR_STATUS timer_err = E_OK;
	
	/*De-Initializing the timer*/
	timer_err = Timer_DeInit();
	
	/*If the timer is uninitialized from the beginning*/
	if(timer_err == E_NOK)
	{
		err_var = Deinit_Without_Init_Error;
	}
	else
	{
		/*Resetting the init flag if the timer is already de-initialized*/
		gu8_init_flag = 0;
		err_var = OperationSuccess;
	}
	return err_var;
}

EnmTMUError_t TMU_Start_Timer(const Task_ConfigType * TaskPtr)
{
	/*Variable used in error indication*/
	EnmTMUError_t err_var = 0;

	/*Checking the pointer is NULL or not*/	
	if(TaskPtr == NULL)
	{
		err_var = NullPtr_Error;
	} 
	else
	{
		/*Checking the tasks buffer is full or not*/
		if (gu8_task_counter == TASKS_NUMBER)
		{
			err_var = FullBuffer_Error;
		}
		else
		{
			/*Adding the task to the TMU list if there's a place available*/
			task_arr[gu8_task_counter] = (*TaskPtr);
			gu8_task_counter++;
			
			/*Returning operation success*/
			err_var = OperationSuccess;
		}	
	}
	
	return err_var;	
}

EnmTMUError_t TMU_Stop_Timer(const Task_ConfigType * TaskPtr)
{
	/*Variable used in error indication*/
	EnmTMUError_t err_var = 0;
	
	/*Variable used in task searching operation*/
	uint8_t au8_looping_var = 0;		
	
	/*Checking the pointer is NULL or not*/
	if(TaskPtr == NULL)
	{
		err_var = NullPtr_Error;
	} 
	else
	{
		/*Searching for the specified task and deleting it if found*/
		for (au8_looping_var = 0 ; au8_looping_var < gu8_task_counter ; au8_looping_var++)
		{
			if( (TaskPtr -> task_id) == task_arr[au8_looping_var].task_id )
			{
				task_arr[au8_looping_var].task_id = NOT_VALID_TASK;
				err_var = OperationSuccess;
				break;
			}
			else
			{
				/*DO nothing*/
			}
		}
		
		/*If the task isn't found then return stop without error*/
		if (err_var != OperationSuccess)
		{
			err_var = Stop_Without_Start_Error;
		}
		else
		{
			/*Do nothing*/
		}
	}
	
	return err_var;
}

EnmTMUError_t TMU_Dispatch(void)
{
	/*Variable used in error indication*/
	EnmTMUError_t err_var = 0;

	/*Variable used in dispatcher operation*/
	uint8_t au8_looping_var = 0;
	
	/*Checking whether the dispatcher is started before or not*/
	if (gu8_dispatcherStart)
	{
		/*Do nothing*/
	} 
	else
	{		
		/* Calculation of system tick time by converting timer tick to us (stored in uint32_t)
		 * Then dividing by selected timer count time (which is 4us)
		 */
		uint16_t au16_systemTick = (uint16_t)( ( (uint32_t)gu8_timer_tickTime * MS_TO_US_CONVERSION ) / TICK_4US );
		
		/*Starting the selected timer channel and rising the dispatcher start flag*/
		Timer_Start(gu8_timer_selectedChannel , au16_systemTick);
		gu8_dispatcherStart++;
		
		/*Enable global interrupts*/
		SET_BIT(SREG , GLOBAL_INT_ENABLE_BIT);
	}
	
	/*Checking whether the system tick happened or not*/
	if(gu8_dispatcherStartOperation)
	{
		/*Looping over TMU task list and executing the task that its period comes*/
		for(au8_looping_var = 0 ; au8_looping_var < TASKS_NUMBER ; au8_looping_var++)
		{
			/*Executing only valid tasks*/
			if(task_arr[au8_looping_var].task_id != NOT_VALID_TASK)
			{
				if( (gu32_ticksCount % task_arr[au8_looping_var].periodicity) == 0)
				{
					task_arr[au8_looping_var].fptr();
				} 
				else
				{
					/*Do nothing*/
				}
			} 
			else
			{
				/*Do nothing*/
			}
			
			/*If the task is one shot task then make it invalid after it has been executed*/
			if( (task_arr[au8_looping_var].calling_type == ONE_SHOT_CALLING) && (task_arr[au8_looping_var].periodicity == gu32_ticksCount))
			{
				task_arr[au8_looping_var].task_id = NOT_VALID_TASK;
			} 
			else
			{
				/*DO nothing*/
			}
		}
		
		/*Resetting dispatcher operation starting flag*/
		gu8_dispatcherStartOperation = 0;
		
		/*Return operation success because tasks is executed*/
		err_var = OperationSuccess;
	} 
	else
	{
		err_var = Dispatcher_Hold_Error;		
	}
	
	return err_var;
}


/***********************************************************************************************/
/*Selected timer channels ISR's that starts the dispatcher operation and increases system ticks*/
/***********************************************************************************************/

ISR(TIMER0_COMP_vect)
{
	gu8_dispatcherStartOperation++;
	gu32_ticksCount++;
}

ISR(TIMER1_COMPA_vect)
{
	gu8_dispatcherStartOperation++;
	gu32_ticksCount++;	
}

ISR(TIMER2_COMP_vect)
{
	gu8_dispatcherStartOperation++;
	gu32_ticksCount++;
}