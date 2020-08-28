/*
 * SOS.c
 *
 * Created: 2/24/2020 3:58:24 PM
 *  Author: Hazem 
 */ 


/*- INCLUDES -----------------------------------------------*/

#include "SOS.h"

/*- LOCAL Data types ----------------------------------------*/

typedef  struct  Task_BlockType
{
	uint8_t perodicity;
	uint16_t delay;
	ptrtotask taskfunc;
	uint16_t delay_milistone;
	uint8_t  priority;
	
}Task_BlockType;

/*- GLOBAL STATIC VARIABLES -------------------------------*/

static uint8_t gu8_SOSresloution;
static uint8_t gu8_SOStasks;
static uint8_t gu8_SOSinitflag;
Task_BlockType static gastr_SOSbuffer[BUFFER_SIZE]={CLEAR};
volatile static uint32_t gu32_ostick;





/*- local function IMPLEMENTATION ----------------------*/

static void SOS_taskbublesort(Task_BlockType * astr_taskbuffer , uint8_t u8_numberoftasks)
{
	uint8_t au8_counter1;
	uint8_t au8_counter2;
	uint8_t au8_temppriority=0;
	uint16_t au8_tempdelay=0;
	ptrtotask pf_temp;
	uint8_t au8_tempperiodicity=0;
	uint16_t au8_tempdelaymilistone=0;
	
	for(au8_counter1=FIRST_TASK;au8_counter1<u8_numberoftasks;au8_counter1++)
	{
		for(au8_counter2=FIRST_TASK;au8_counter2<u8_numberoftasks;au8_counter2++)
		{
			if(astr_taskbuffer[au8_counter2].priority<=astr_taskbuffer[au8_counter2+1].priority)
			{
				au8_temppriority=astr_taskbuffer[au8_counter2].priority;
				astr_taskbuffer[au8_counter2].priority=astr_taskbuffer[au8_counter2+1].priority;
				astr_taskbuffer[au8_counter2+1].priority=au8_temppriority;
				
				au8_tempdelay=astr_taskbuffer[au8_counter2].delay;
				astr_taskbuffer[au8_counter2].delay=astr_taskbuffer[au8_counter2+1].delay;
				astr_taskbuffer[au8_counter2+1].delay=au8_tempdelay;
				
				pf_temp=astr_taskbuffer[au8_counter2].taskfunc;
				astr_taskbuffer[au8_counter2].taskfunc=astr_taskbuffer[au8_counter2+1].taskfunc;
				astr_taskbuffer[au8_counter2+1].taskfunc=pf_temp;
				
				au8_tempperiodicity=astr_taskbuffer[au8_counter2].perodicity;
				astr_taskbuffer[au8_counter2].perodicity=astr_taskbuffer[au8_counter2+1].perodicity;
				astr_taskbuffer[au8_counter2+1].perodicity=au8_tempperiodicity;
				
				au8_tempdelaymilistone=astr_taskbuffer[au8_counter2].delay_milistone;
				astr_taskbuffer[au8_counter2].delay_milistone=astr_taskbuffer[au8_counter2+1].delay_milistone;
				astr_taskbuffer[au8_counter2+1].delay_milistone=au8_tempdelaymilistone;
				
				
				
				
			}
		}
	}
	
	
}




	
/*- APIs IMPLEMENTATION -----------------------------------*/

	
/************************************************************************/
/* SOS_Init
EnmSOSError_t SOS_Init (const PtrSOS_Configtype ConfigPtr )
ConfigPtr Pointer to a selected configuration structure*/
/************************************************************************/

EnmSOSError_t SOS_Init (const PtrSOS_Configtype ConfigPtr )
{  
	 /* error variable for init fun*/	 
	EnmSOSError_t au8_SOSiniterror =E_OK;
	  	
	/* check pointer_config is null or not */
	if(ConfigPtr==NULL)
	{
		/*if null return null error from error handling*/
		au8_SOSiniterror =SOS_INIT_NULL_POINTER; 
	}
	else
	{  
		/*INITIALIZED all global variables*/
	    gu8_SOSresloution=CLEAR;
		gu8_SOStasks=CLEAR;
		/*check SOS is init or not*/
		if(gu8_SOSinitflag==INITIALIZED)
		{
			/*if yes return multiple init error from error handling*/
			au8_SOSiniterror=SOS_MULTIPLE_INIT;
		}
		else
		{   
			/*store Resolution into global static variable*/  
			gu8_SOSresloution=ConfigPtr->u8_res;
			/*config timer according to SOS_TIMERID*/  
			Timer_cfg_s str_SOStimerconfig={CLEAR};
			switch(ConfigPtr->u8_SOS_timerid)
			{
				case TIMER_0:
				str_SOStimerconfig.Timer_CH=TIMER_0;
				str_SOStimerconfig.Timer_Mode=TIMER_MODE;
				str_SOStimerconfig.Timer_Int_MODE=TIMER_INTERRUPT_MODE;
				str_SOStimerconfig.Timer_Prescaler=TIMER_PRESCALER_64;
				break;
				case TIMER_1:
				str_SOStimerconfig.Timer_CH=TIMER_1;
				str_SOStimerconfig.Timer_Mode=TIMER_MODE;
				str_SOStimerconfig.Timer_Int_MODE=TIMER_INTERRUPT_MODE;
				str_SOStimerconfig.Timer_Prescaler=TIMER_PRESCALER_64;
				break;
				case TIMER_2:
				str_SOStimerconfig.Timer_CH=TIMER_2;
				str_SOStimerconfig.Timer_Mode=TIMER_MODE;
				str_SOStimerconfig.Timer_Int_MODE=TIMER_INTERRUPT_MODE;
				str_SOStimerconfig.Timer_Prescaler=TIMER_PRESCALER_64;
				break;
				default:
				au8_SOSiniterror =E_NOK;
				break;
			}
			/*check timer is init correct or not */  
			if(Timer_Init(&str_SOStimerconfig)==E_OK)
			{
				
			}
			else
			{
				au8_SOSiniterror=E_NOK;
			}
		}
	}
	/*convert module into INITIALIZED mode*/  
	gu8_SOSinitflag=INITIALIZED;
	
	return au8_SOSiniterror;
}


/*
Function Name 	SOS_Start_Timer
Syntax:     
Sync/Async:   ASYNC  
Parameters (in):
Parameters (out):
Parameters (inOut):
Return:
*/

EnmSOSError_t SOS_Start_Timer(uint16_t u16_time,ptrtotask pf_task,uint8_t u8_periodicORoneshot,uint8_t u8_priority)
{   
	/* error variable for sos_start fun initial value no error*/
	EnmSOSError_t au8_SOSstarterror=E_OK;
	
	/*check if module is initialized or not*/
	if(gu8_SOSinitflag==NOTINITIALIZED)
	{
		au8_SOSstarterror=SOS_MODULE_NOTINITIALIZED;
	}
	
	else
	{
		/*check if tasks is less than the maximum number of tasks */
		if(gu8_SOStasks<MAX_NOTASKS)
		{
			/*check if period is neither one shot or periodic */
			if((u8_periodicORoneshot!=PERIODIC)&&(u8_periodicORoneshot!=ONESHOT))
			{
				au8_SOSstarterror=SOS_NOT_PERODICORONESHOT;
			}
			else
			{
				/*check if fun address is not a null */
				if(pf_task==NULL)
				{
					au8_SOSstarterror=SOS_FUN_NULL_POINTER;
				}
				else
				{
					/*add task to sos_buffer */
					gastr_SOSbuffer[gu8_SOStasks].delay=u16_time;
					gastr_SOSbuffer[gu8_SOStasks].taskfunc=pf_task;
					gastr_SOSbuffer[gu8_SOStasks].perodicity=u8_periodicORoneshot;
					gastr_SOSbuffer[gu8_SOStasks].delay_milistone=CLEAR;
					gastr_SOSbuffer[gu8_SOStasks].priority=u8_priority;
					SOS_taskbublesort(gastr_SOSbuffer,gu8_SOStasks);
                    /*check if task is the first task */
					if(gu8_SOStasks==FIRST_TASK)
					{
						/*start timer*/
						Timer_Setcallback(SOS_schedulertime);
						if(Timer_Start(SOS_TIMER_ID,TCNT_INITIAL_VALUE)==E_OK)
						{
							
						}
						else
						{
							au8_SOSstarterror=E_NOK;
						}
					}

					gu8_SOStasks++;
				}
			}
		}
		/*if task not less than max_number_of_tasks return buffer is full */
		else
		{
			au8_SOSstarterror=SOS_BUFFER_IS_FULL;
		}
	}
	return au8_SOSstarterror;
}
/**
* @brief: SOS Stop
* @param: ptrFun: pointer to callback function
* @return: EnmSOSError_t au8_SOSstoperror code with error code if one occurred
*/

EnmSOSError_t SOS_Stop_Timer(ptrtotask ptrtofun)
{	
	/* error variable for sos_stop fun initial value no error*/
	EnmSOSError_t au8_SOSstoperror=E_OK;
	uint8_t au8_counter;
    /* flag variable to identify the task wanted to stop exist or not */
	uint8_t au8_taskisfound=NOT_FOUND;
	/* if no task is running return sos_bufferisempty */
	if(gu8_SOStasks==NOTASKTOSTOP)
	{
		au8_SOSstoperror=SOS_BUFFER_IS_EMPTY;
	}
	else
	{
		/* loop over running tasks */
		for(au8_counter=FIRST_TASK;au8_counter<gu8_SOStasks;au8_counter++)
		{
             /* task wanted to stop founded  */
			if(gastr_SOSbuffer[au8_counter].taskfunc==ptrtofun)
			{
				/* raise flag*/  
			    au8_taskisfound=FOUND;
			     /* if stooped task equal last task in buffer*/
				if(au8_counter==LAST_TASK)
				{
		            /* just null it to initial state and decrease running task by one*/
					gastr_SOSbuffer[au8_counter].taskfunc=NULL;
					gastr_SOSbuffer[au8_counter].delay_milistone=CLEAR;
					gastr_SOSbuffer[au8_counter].delay=CLEAR;
					gastr_SOSbuffer[au8_counter].perodicity=CLEAR;
				}
				else
				{
				    /* if not swap stooped task by the last task in buffer and null the last one*/
					gastr_SOSbuffer[au8_counter].taskfunc=gastr_SOSbuffer[gu8_SOStasks].taskfunc;
					gastr_SOSbuffer[au8_counter].delay_milistone=gastr_SOSbuffer[gu8_SOStasks].delay_milistone;
					gastr_SOSbuffer[au8_counter].delay=gastr_SOSbuffer[gu8_SOStasks].delay;
					gastr_SOSbuffer[au8_counter].perodicity=gastr_SOSbuffer[gu8_SOStasks].perodicity;
                    /* and null it to initial state and decrease running task by one*/
					gastr_SOSbuffer[gu8_SOStasks].taskfunc=NULL;
					gastr_SOSbuffer[gu8_SOStasks].delay_milistone=CLEAR;
					gastr_SOSbuffer[gu8_SOStasks].delay=CLEAR;
					gastr_SOSbuffer[gu8_SOStasks].perodicity=CLEAR;
				}
				gu8_SOStasks--;
				SOS_taskbublesort(gastr_SOSbuffer,gu8_SOStasks);
			}

		}
	    /* if task deleted equal last task stop timer*/	
		if(gu8_SOStasks==LAST_TASK)
		{
			if(Timer_Stop(SOS_TIMER_ID)==E_OK)
			{
				
			}
			else
			{
				au8_SOSstoperror=E_NOK;
			}
		}
	     /* if task deleted not found return no_task to stop_error */
		if(au8_taskisfound==NOT_FOUND)
		{
			au8_SOSstoperror=SOS_NOTASK_FOUND_TO_STOP;
		}
	}
	return au8_SOSstoperror;
}


/**
* @brief: SOS Loops through task list and service each one as requested
* @param: void
* Input : void
* Output: None
* @return: EnmSOSError_t au8_SOSdiserror code with error code if one occurred
*/


EnmSOSError_t SOS_Dispatch(void)
{
    /* error variable for sos_stop fun initial value no error*/
	EnmSOSError_t au8_SOSdiserror=E_OK;
	/* pre_load value of timer variable to readjust the system tick*/
	uint8_t au8_preloadtimer=TCNT_INITIAL_VALUE;
	/* if system tick equal to adjust pre_configure resolution start dispatcher */
	if(gu32_ostick==RESOLUTION)
	{
		/* clear system tick */
		gu32_ostick=CLEAR;
       /* readjust timer to make a system_tick after 1ms(system tick) */
		if(Timer_SetValue(SOS_TIMER_ID,&au8_preloadtimer)==E_OK)
		{
			
		}
		else 
		{
			au8_SOSdiserror=E_NOK;
		}
		/*Loop through Tasks in the array and increment milestones*/
		uint8_t u8_counter=CLEAR;
		for(u8_counter=START;u8_counter<BUFFER_SIZE;u8_counter++)
		{
			if(gastr_SOSbuffer[u8_counter].taskfunc==NULL)
			{

			}
			else
			{
				gastr_SOSbuffer[u8_counter].delay_milistone++;
			}
		}
		/* Loop through  array of tasks and handle each one */
		for(u8_counter=START;u8_counter<gu8_SOStasks;u8_counter++)
		{
			if(gastr_SOSbuffer[u8_counter].taskfunc==NULL)
			{

			}
			else
			{
				/* if delay task time_delay is ready  clear milestones ticks of task and serve it*/
				if(gastr_SOSbuffer[u8_counter].delay_milistone==gastr_SOSbuffer[u8_counter].delay)
				{
					gastr_SOSbuffer[u8_counter].delay_milistone=CLEAR;
					gastr_SOSbuffer[u8_counter].taskfunc();
				   /* if task is one shot remove it from scheduler*/
					if(gastr_SOSbuffer[u8_counter].perodicity==ONESHOT)
					{
						if(SOS_Stop_Timer(gastr_SOSbuffer[u8_counter].taskfunc)==E_OK)
						{
							
						}
						else
						{
							au8_SOSdiserror=E_NOK;
						}
					}
				}
				else
				{

				}
			}
		}
	}
	else
	{

	}
	return au8_SOSdiserror;
}

/**
* @brief: SOS DeInitialization
* @param: void
* Input : void
* Output: None
* @return: EnmSOSError_t au8_SOSdiserror code with error code if one occurred
*/
EnmSOSError_t SOS_DeInit(void)
{
	/* error variable for sos_dinit fun initial value no error*/
	EnmSOSError_t au8_SOSEROR=E_OK;
   /* clear all global  variable */
	uint8_t u8_counter=CLEAR;
	gu8_SOSresloution=CLEAR;
	gu8_SOStasks =CLEAR;
	/*if sos was INITIALIZED */
	if(gu8_SOSinitflag==INITIALIZED)
	{
		/*loop to all tasks and null it and stop system tick by stopped the timer*/
		for(u8_counter=START;u8_counter<BUFFER_SIZE;u8_counter++)
		{
			gastr_SOSbuffer[u8_counter].taskfunc=NULL;
			gastr_SOSbuffer[u8_counter].delay_milistone=CLEAR;
			gastr_SOSbuffer[u8_counter].delay=CLEAR;
			gastr_SOSbuffer[u8_counter].perodicity=CLEAR;

		}
		if(Timer_Stop(SOS_TIMER_ID)==E_OK)
		{
			
		}
		else
		   au8_SOSEROR=E_NOK;
		  
	}
    /*if SOS WAS NOT_INITIALIZED RETURN SOS_MODULE_NOTINITIALIZED*/
	else
	{
		au8_SOSEROR=SOS_MODULE_NOTINITIALIZED;
	}
	gu8_SOSinitflag = NOTINITIALIZED;
	return au8_SOSEROR;
}
 /*increment system tick variable each interrupt of the timer by this callback function*/
void SOS_schedulertime(void)
{
	gu32_ostick++;
}

