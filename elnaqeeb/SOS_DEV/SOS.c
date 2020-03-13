/*
 * SOS.c
 *
 * Created: 2/24/2020 11:34:40 AM
 *  Author: Ahmed
 */ 

#include "std_types.h"
#include "registers.h"
#include "interrupts.h"
#include "Timer.h"
#include "SOS.h"
#include "SOS_config.h"

/************************************************************************/
/*                           General macros                             */
/************************************************************************/

#define NOT_VALID_TASK			(0xFF)
#define MS_TO_US_CONVERSION		(1000)
#define TICK_4US				(4)
#define GLOBAL_INT_ENABLE_BIT	(7)

/************************************************************************/
/*                        Operation global variables                    */
/************************************************************************/

/*SOS tasks list which is an array of tasks*/
static Task_ConfigType task_arr[TASKS_NUMBER] = {0};

/*Flag indicates whether the SOS is initialized or not*/
static uint8_t gu8_init_flag = 0;

/*Variable holds the timer selected channel*/
static uint8_t gu8_timer_selectedChannel = 0;

/*Variable used in holding the value to be loaded for the timer*/
static uint8_t gu8_timer_tickTime = 0;

/*Variable used in counting added tasks to SOS*/
static uint8_t gu8_task_counter = 0;

/*Variable holds the system ticks*/
static volatile uint32_t gu32_ticksCount = 0;

/*Configuration structre instance golds the SOS configuration data*/
static SOS_ConfigType sos_cfg = SOS_CONFIG_DATA;

/************************************************************************/
/*                      SOS functions' definition                       */
/************************************************************************/

EnmSOSError_t SOS_Init(void)
{
	/*Variable used to report the returned error*/	
	EnmSOSError_t  err_var = OperationSuccess; 

	/*Checking whether the SOS is initialized already or not*/
	if (gu8_init_flag)
	{
		err_var = MultipleInit_Error;
	}
	else
	{
		/*Setting selected timer channel to 4us tick count*/
		switch(sos_cfg.timer_channel)
		{
			case SOS_TIM_CH0:
			Timer_Init(TIMER_CH0 , TIMER_MODE , TIMER_PRESCALER_64 , TIMER_INTERRUPT_MODE);
			gu8_timer_selectedChannel = TIMER_CH0;
			gu8_timer_tickTime = (sos_cfg.timer_tick_time_ms);
			break;
				
			case SOS_TIM_CH1:
			Timer_Init(TIMER_CH1 , TIMER_MODE , TIMER_PRESCALER_64 , TIMER_INTERRUPT_MODE);
			gu8_timer_selectedChannel = TIMER_CH1;
			gu8_timer_tickTime = (sos_cfg.timer_tick_time_ms);
			break;

			case SOS_TIM_CH2:
			Timer_Init(TIMER_CH2 , TIMER_MODE , TIMER_PRESCALER_64 , TIMER_INTERRUPT_MODE);
			gu8_timer_selectedChannel = TIMER_CH2;
			gu8_timer_tickTime = (sos_cfg.timer_tick_time_ms);
			break;
				
			/*Invalid channel selected error*/
			default: err_var = InvalidChannel_Error;
		}
			
		/*Rising the init flag*/
		gu8_init_flag++;
	}	
	return err_var;
}

EnmSOSError_t SOS_DeInit(void)
{
	/*Variables used in error indication*/
	EnmSOSError_t err_var = OperationSuccess;
	
	/*De-Initializing the timer*/
	Timer_DeInit();

	/*Resetting the init flag*/
	gu8_init_flag = 0;

	return err_var;
}

EnmSOSError_t SOS_addTask(const Task_ConfigType * TaskPtr)
{
	/*Variable used in error indication*/
	EnmSOSError_t err_var = OperationSuccess;

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
			/*Adding the task to the SOS list according to its priority if there's a place available*/
			task_arr[TaskPtr -> task_priority] = (*TaskPtr);
			
			/*Increasing the task counter by one*/
			gu8_task_counter++;			
		}	
	}
	
	return err_var;	
}

EnmSOSError_t SOS_deleteTask(const Task_ConfigType * TaskPtr)
{
	/*Variable used in error indication*/
	EnmSOSError_t err_var = 0;
	
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
		for (au8_looping_var = 0 ; au8_looping_var < TASKS_NUMBER ; au8_looping_var++)
		{
			if( (TaskPtr -> task_priority) == task_arr[au8_looping_var].task_priority )
			{
				task_arr[au8_looping_var].task_priority = NOT_VALID_TASK;
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
			err_var = Deleting_Without_Adding_Error;
		}
		else
		{
			/*Do nothing*/
		}
	}
	
	return err_var;
}

EnmSOSError_t SOS_run(void)
{
	/*Variable used in error indication*/
	EnmSOSError_t err_var = OperationSuccess;
	
	/* Calculation of system tick time by converting timer tick to us (stored in uint32_t)
	 * Then dividing by selected timer count time (which is 4us)
	 */
	uint16_t au16_systemTick = (uint16_t)( ( (uint32_t)gu8_timer_tickTime * MS_TO_US_CONVERSION ) / TICK_4US );
		
	/*Starting the selected timer channel and rising the dispatcher start flag*/
	Timer_Start(gu8_timer_selectedChannel , au16_systemTick);
		
	/*Enable global interrupts*/
	SET_BIT(SREG , GLOBAL_INT_ENABLE_BIT);
	
	return err_var;
}

static void SOS_dispatcher(void)
{
	/*Variable used in dispatcher operation*/
	volatile uint8_t au8_looping_var = 0;
	
	/*Looping over SOS task list and executing the task that its period comes*/
	for(au8_looping_var = 0 ; au8_looping_var < TASKS_NUMBER ; au8_looping_var++)
	{
		/*Executing only valid tasks*/
		if(task_arr[au8_looping_var].task_priority != NOT_VALID_TASK)
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
			task_arr[au8_looping_var].task_priority = NOT_VALID_TASK;
		} 
		else
		{
			/*DO nothing*/
		}
	}	
	return;
}

/***********************************************************************************************/
/*Selected timer channels ISR's that starts the dispatcher operation and increases system ticks*/
/***********************************************************************************************/

ISR(TIMER0_COMP_vect)
{
	gu32_ticksCount++;
	SOS_dispatcher();
}

ISR(TIMER1_COMPA_vect)
{
	gu32_ticksCount++;	
	SOS_dispatcher();
}

ISR(TIMER2_COMP_vect)
{
	gu32_ticksCount++;
	SOS_dispatcher();
}