/*
 * SOS.c
 *
 * Created: 24-Feb-20 11:32:24 AM
 *  Author: ahmed
 */ 

/************************************************************************/
/*							INCLUDES                                    */
/************************************************************************/
#include "SOS.h"
#include "../timer.h"
#include "../Error_table.h"

/************************************************************************/
/*							DEFINES                                    */
/************************************************************************/
#define NUMBER_OF_TICKS		(247)
#define TCNT_VAL			(7)
#define TASK_STATE_DONE		(1)
#define TASK_STATE_NOTDONE	(2)

/************************************************************************/
/*							INIT DEFINES                                */
/************************************************************************/
#define MODULE_INIT			(1)
#define MODULE_NOT_INIT		(0)

/************************************************************************/
/*							START DEFINES		                        */
/************************************************************************/
#define MODULE_STARTED		(1)
/************************************************************************/
/*							DISPATCH DEFINES                            */
/************************************************************************/
#define DISPATCH_MAX_TRIGGER	(40000)

/************************************************************************/
/*							Variables                                   */
/************************************************************************/
static uint8_t u8_TaskNumber=ZERO;
static uint8_t u8_DeletedElements[SOS_BUFFER];
static uint8_t TMR_ch=0;
volatile static uint8_t Flag_1ms = LOW;
static uint8_t u8_Deleted_Tasks_Counter = 0;
volatile static uint32_t u32_cnts = 0;
static uint8_t ModuleInit_State = 0;
static uint8_t Module_started_state = 0;
static uint8_t Timer_started = 0;

/*create array of Tasks*/
SOS_TaskType Timer_tasks[SOS_BUFFER] ;


static void Timer_callback();

/************************************************************************/
/*							APIS                                        */
/************************************************************************/


/** Init SOS function
**Description : function takes pointer to struct of SOS init
*				struct has one variable which is the timer at which the SOS will operate
	
** @parm : pointer to SOS - Init type struct

*return "error_state* : -1 : for NULL POINTER
						-2 : for multiple initialization
						
*/
ERROR_STATUS SOS_Init(st_SOS_init *ConfigPtr)
{
	/*create Error_flag*/
	ERROR_STATUS error_flag = NO_ERROR;

	/*check if the module with inited before*/
	if(ModuleInit_State == MODULE_INIT){

		/*record an error status*/
		error_flag = ERROR_MULTIPLE_MODULE_INIT;
	}

	else{
		/*save that module is inited*/
		ModuleInit_State = MODULE_INIT;

		/*check for null pointer as it's not valid*/
		if(ConfigPtr == NULL)
		{
			/*record error status*/
			error_flag = ERROR_NULL_PTR_INIT;
		}
		else
		{
			/*create timer structure*/
			Timer_cfg_s st_timer_cfg;

			/*check which channel user wants*/
			switch(ConfigPtr->u8_timer_chnl){

			case SOS_TMR_CH0:

				/*configure TM0*/
				/*first save the selected timer*/
				TMR_ch = TIMER_CH0;
				st_timer_cfg.Timer_CH_NO = TIMER_CH0;
				st_timer_cfg.Timer_INT_Mode = TIMER_INTERRUPT_MODE;
				st_timer_cfg.Timer_Mode = TIMER_MODE;
				st_timer_cfg.Timer_Prescaler = TIMER_PRESCALER_64;
				st_timer_cfg.Timer_Cbk_ptr = (volatile void(*)(void))Timer_callback;

				break;

			case SOS_TMR_CH1:

				/*configure TM1*/
				/*first save the selected timer*/
				TMR_ch = TIMER_CH1;
				st_timer_cfg.Timer_CH_NO = TIMER_CH1;
				st_timer_cfg.Timer_INT_Mode = TIMER_INTERRUPT_MODE;
				st_timer_cfg.Timer_Mode = TIMER_MODE;
				st_timer_cfg.Timer_Prescaler = TIMER_PRESCALER_64;
				st_timer_cfg.Timer_Cbk_ptr = (volatile void(*)(void))Timer_callback;
				break;

			case SOS_TMR_CH2:

				/*configure TM2*/
				/*first save the selected timer*/
				TMR_ch = TIMER_CH2;
				st_timer_cfg.Timer_CH_NO = TIMER_CH2;
				st_timer_cfg.Timer_INT_Mode = TIMER_INTERRUPT_MODE;
				st_timer_cfg.Timer_Mode = TIMER_MODE;
				st_timer_cfg.Timer_Prescaler = TIMER_PRESCALER_64;
				st_timer_cfg.Timer_Cbk_ptr = (volatile void(*)(void))Timer_callback;
				break;

			default:
				error_flag = INVALID_INIT_PARAMETER;
				break;
			}

			/*init timer with previous settings*/
			Timer_Init(&st_timer_cfg);
		}

	}
	/*return error_status*/
	return error_flag;
}

/**SOS_Add_Task
*Description : function to start the chosen task by inserting it in the schedular
** INPUTS  : pointer to struct of SOS_Task @ which 1- task id 2-task counts 3- task state
4-task callback pointer
*Return : Error state
*/
ERROR_STATUS SOS_Add_Task(SOS_TaskType *SOS_start)
{
	/*create error flag to save error state*/
	ERROR_STATUS error_flag = NO_ERROR;

	/*create inner loop to check the id*/
	uint8_t id_loop = ZERO;

	/*check if module was init or not*/
	if(ModuleInit_State == MODULE_INIT)
	{
		/*check if null pointer then not valid*/
		if(SOS_start == NULL)
		{
			/*save error state*/
			error_flag = ERROR_NULL_PTR_START;
		}
		else if((SOS_start->u8_TaskPriority >= SOS_BUFFER) ||
				(SOS_start->task_ptr == NULL) ||
				((SOS_start->u8_periodic_state != SOS_PERIODIC) &&
				(SOS_start->u8_periodic_state != SOS_ONESHOOT)))
		{
			error_flag = ERROR_INVALID_START_PARAMETERS;
		}
		else{
			/*save starting state*/
			Module_started_state = MODULE_STARTED;

			/*check if the timer was started before then don't start it again*/
			if(Timer_started == TRUE){}

			else{
				Timer_started = TRUE;
				Timer_Start(TMR_ch,NUMBER_OF_TICKS);
			}

			/*check if the buffer is full*/
			if((u8_TaskNumber == SOS_BUFFER) && u8_Deleted_Tasks_Counter ==ZERO)
			{
				/*save error state full buffer*/
				error_flag = ERROR_START_FULL_BUFFER;
			}

			else{
				/*check if the id was inserted before*/
				for(id_loop = 0; id_loop<u8_TaskNumber; id_loop ++){

					/*check for task id entered*/
					if(Timer_tasks[id_loop].u8_id  == SOS_start->u8_id)
					{
						/*save error state*/
						error_flag = ERROR_MULTIPLE_MODULE_START;
					}
				}

				/*init only if it's the first time for module*/
				if(error_flag != ERROR_MULTIPLE_MODULE_START)
				{

					if((Timer_tasks[SOS_start->u8_TaskPriority].u8_id == 0) ||
					((Timer_tasks[SOS_start->u8_TaskPriority].u8_periodic_state == SOS_ONESHOOT) &&
					(Timer_tasks[SOS_start->u8_TaskPriority].u8_TaskState == TASK_STATE_DONE)))
					{
						/*allocate your data at the first free buffer*/
						Timer_tasks[SOS_start->u8_TaskPriority].u8_id = SOS_start->u8_id;
						Timer_tasks[SOS_start->u8_TaskPriority].u8_TaskPriority = SOS_start->u8_TaskPriority;
						Timer_tasks[SOS_start->u8_TaskPriority].u32_counts = SOS_start->u32_counts;
						Timer_tasks[SOS_start->u8_TaskPriority].u8_periodic_state = SOS_start->u8_periodic_state;
						Timer_tasks[SOS_start->u8_TaskPriority].task_ptr = SOS_start->task_ptr;
						Timer_tasks[SOS_start->u8_TaskPriority].u8_TaskState = TASK_STATE_NOTDONE;
						/*save the counts Val*/
						u8_TaskNumber++;
					}
					else
					{
						/*save error module can't be created*/
						error_flag = ERROR_MODULE_PRIORITY_USED;
					}
				}
			}
		}
	}

	else
	{
		/*set error state as module not initialized*/
		error_flag = MODULE_NOT_INIT;
	}


	/*return error state*/
	return error_flag;
}

/** SOS_Run
*Description : Function that starts the timer and trigger the scheduled tasks 
*Input : none
*Output : ERROR STATUS: NO_ERROR , ERROR_NO_TASK if no task is inserted*/
ERROR_STATUS  SOS_Run(void)
{
	/*create error flag*/
	ERROR_STATUS error_flag = NO_ERROR;

	/*create a loop variable*/
	uint8_t u8_loop = ZERO;

	/*check if it's was started before or not*/
	if(Module_started_state == MODULE_STARTED)
	{
		/*check for the triggers*/
		if(Flag_1ms == HIGH){

			/*reset trigger flag*/
			Flag_1ms = LOW;

			for(u8_loop=ZERO ;u8_loop<SOS_BUFFER;u8_loop++){

				/*for 1 shot only task check if it's the first time then fire it if not then neglect it*/
				if(Timer_tasks[u8_loop].u8_periodic_state  == SOS_ONESHOOT &&
						(u32_cnts % (Timer_tasks[u8_loop].u32_counts) == ZERO) &&
						Timer_tasks[u8_loop].u8_TaskState == TASK_STATE_NOTDONE){

					/*call the function stop to send it to done state*/
					SOS_Delete_Task(Timer_tasks[u8_loop].u8_id);

				}

				/*if it's periodic then keep it runing*/
				else if(Timer_tasks[u8_loop].u8_periodic_state == SOS_PERIODIC &&
						(u32_cnts % (Timer_tasks[u8_loop].u32_counts) == ZERO))
				{

					/*call it*/
					Timer_tasks[u8_loop].task_ptr();
				}

				/*reinit the counter every 40000 msecond*/
				if(u32_cnts == DISPATCH_MAX_TRIGGER)

					u32_cnts = ZERO;
			}
		}
	}

	else
	{
		error_flag = ERROR_MODULE_DIDNOT_START;
	}


	/*check if no tasks available*/
	if(u8_TaskNumber == ZERO || ((u8_TaskNumber - u8_Deleted_Tasks_Counter) == ZERO))

		error_flag = ERROR_DISPATCH_NO_TASKS;

	return error_flag;
}

/* Description : function idicates which Task is nolonger operating
** Inputs : Task_ID
* Output : ERROR_STATUS 1-NO_ERROR 2_MODULE NOT STARTED
*/
ERROR_STATUS SOS_Delete_Task(uint8_t Task_ID){

	/*create error flag*/
	ERROR_STATUS error_flag = NO_ERROR;

	/*create inner loop for stop timer*/
	uint8_t u8_stop_loop = ZERO;

	/*loop to save index of task id*/
	for(u8_stop_loop = ZERO; u8_stop_loop <u8_TaskNumber ; u8_stop_loop++){

		if(Timer_tasks[u8_stop_loop].u8_id == Task_ID){

			/*change Task configs*/
			Timer_tasks[u8_stop_loop].u8_periodic_state = SOS_ONESHOOT;
			Timer_tasks[u8_stop_loop].u8_TaskState = TASK_STATE_DONE;

			/*break*/
			break;
		}
	}
	if(u8_stop_loop == u8_TaskNumber)
	{
		error_flag = ERROR_MODULE_DIDNOT_START;
	}

	if(error_flag != ERROR_MODULE_DIDNOT_START)
	{

		/*write the task id at the deleted tasks array*/
		u8_DeletedElements[u8_Deleted_Tasks_Counter] = u8_stop_loop;

		/*increment the deleted counter by 1*/
		u8_Deleted_Tasks_Counter++;
	}
	return error_flag;
}


/*callback function for the timer interrupt*/
static void Timer_callback(void){

	/*set the flag high to indicated 1 milli second received*/
	Flag_1ms = HIGH;

	/*increase cnt by 1*/
	u32_cnts++;

	/*reinit timer value*/
	Timer_SetValue(SOS_TMR_CH0,TCNT_VAL);
}

/** SOS_deinit module
*Description : return everything to the starting point
** Output : nothing
*/
void SOS_DeInit(void)
{
	/*reinit all variables*/
	u8_Deleted_Tasks_Counter = ZERO;
	u8_TaskNumber = ZERO;

	/*reinit timer module*/
	Timer_Stop(TMR_ch);
}
