/*
 * SOS.c
 *
 * Created: 2020-02-24 11:21:04 AM
 *  Author: EbrahimOseif
 */ 



/************************************************************************/
/*				             INCLUDES		                 	        */
/************************************************************************/

#include "SOS.h"
#include "sleep.h"

/************************************************************************/
/*				         DEFINES								        */
/************************************************************************/

#define OVF_NOT_TRIGGERED	(0)
#define OVF_TRIGGERED		(1)

/************************************************************************/
/*		         TIMER FUNCTIONS' PROTOTYPES		                    */
/************************************************************************/


/* static functions prototype */

static void SOS_TimerOvf_CBK(void);
static void SOS_ClearTask(uint8_t u8_index);
static void SOS_ShiftTasks(uint8_t newIndex, uint8_t oldIndex);
static void SOS_BufferSort();




/************************************************************************/
/*				 Global / Static Variables						       */
/************************************************************************/

static uint8_t gsu8_SOSInitStatus = NOT_INITIALIZED;

/* the resolution of the triggering */
static volatile uint8_t gu8_SOS_TimerOvf_Flag = OVF_NOT_TRIGGERED;

/* ISR flag counter */
static volatile uint8_t gu8_OvfCounter;

/* the preload value of the timer */
static uint16_t gu16_PRELOAD;

 /* index of the buffer*/
static uint8_t gu8_Index;

Timer_cfg_s gstr_Timer_Cfg;

/************************************************************************/
/*		                FUNCTIONS' implementation				        */
/************************************************************************/

/**
* @brief: SOS Initialize
*		  initialize the timer and buffer
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS SOS_Init(void)
{
		
/*
		ERROR_STATUS u8_status = E_OK;
*/
		ERROR_STATUS u8_status = SOS_ERROR_BASE + NO_ERRORS;
		
		if (gsu8_SOSInitStatus == INITIALIZED)
		{
			u8_status = SOS_ERROR_BASE + ERROR_ALREADY_INITIALIZED;
		}
		else{
			 /* INITIALIZE THE BUFFER */
			uint8_t u8_counter;
			
			for(u8_counter = ZERO; u8_counter < MAX_TASK_COUNT; u8_counter++)
			{
				gastrSOS_Task_Buff[u8_counter].gptr_SOS_Task		= NULL;
				gastrSOS_Task_Buff[u8_counter].u8_SOSTask_Priority  = ZERO;
				gastrSOS_Task_Buff[u8_counter].u8_SOSTask_State		= ZERO;
				gastrSOS_Task_Buff[u8_counter].u16_Periodicity		= ZERO;
				gastrSOS_Task_Buff[u8_counter].u16_SOS_TicksCount	= ZERO;
			}


			/* switch on timer channel AND initialize  */
			
			#if SOS_TIMER_CH0
			
			gstr_Timer_Cfg.Timer_CH_NO = TIMER_CH0;
			gstr_Timer_Cfg.Timer_Prescaler = TIMER_PRESCALER_64; /* preload = 256 - 250 */
			gu16_PRELOAD = 256 - 250;
			
			#elif SOS_TIMER_CH1
			
			gstr_Timer_Cfg.Timer_CH_NO = TIMER_CH1;
			gstr_Timer_Cfg.Timer_Prescaler = TIMER_PRESCALER_1024; /* preload = 65536 - 156 */
			gu16_PRELOAD = 65536 - 15;
			
			#elif SOS_TIMER_CH2
			
			gstr_Timer_Cfg.Timer_CH_NO = TIMER_CH2;
			gstr_Timer_Cfg.Timer_Prescaler = TIMER_PRESCALER_1024; /* preload = 65536 - 156 */
			gu16_PRELOAD = 256 - 15;
			
			#endif
			
			
			gstr_Timer_Cfg.Timer_Mode = TIMER_MODE;
			gstr_Timer_Cfg.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
			gstr_Timer_Cfg.Timer_Cbk_Fun = SOS_TimerOvf_CBK;
			
			/* Initializing the  timer */
			
			u8_status = Timer_Init(&gstr_Timer_Cfg);
					
			/* set SOS module is initialized */
			
			gsu8_SOSInitStatus = INITIALIZED;
		}
		
	return u8_status;
}

/**
* @brief: SOS DeInitialization
*			empty the buffer from tasks
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS SOS_DeInit(void)
{	
		
		/*
		ERROR_STATUS u8_status = E_OK;
*/
		ERROR_STATUS u8_status = SOS_ERROR_BASE + NO_ERRORS;
		
		if (gsu8_SOSInitStatus == NOT_INITIALIZED)
		{
			u8_status = SOS_ERROR_BASE + ERROR_NOT_INITIALIZED;
		}
		else
		{
			/* empty the buffer */
			uint8_t u8_counter;
			for(u8_counter = ZERO; u8_counter < MAX_TASK_COUNT; u8_counter++)
			{
				gastrSOS_Task_Buff[u8_counter].gptr_SOS_Task		= NULL;
				gastrSOS_Task_Buff[u8_counter].u8_SOSTask_Priority  = ZERO;
				gastrSOS_Task_Buff[u8_counter].u8_SOSTask_State		= ZERO;
				gastrSOS_Task_Buff[u8_counter].u16_Periodicity		= ZERO;
			}


	/*Clear the Flags */
	        gu16_PRELOAD			= ZERO;
	        gsu8_SOSInitStatus		= NOT_INITIALIZED;
	        gu8_SOS_TimerOvf_Flag   = OVF_NOT_TRIGGERED;
	        gu8_OvfCounter			= ZERO;
	        gu8_Index				= ZERO;
			
			/* stop the timer */
			
			#if  SOS_TIMER_CH0
			Timer_Stop(TIMER_CH0);
			
			#elif  SOS_TIMER_CH1
			Timer_Stop(TIMER_CH1);
			#elif  SOS_TIMER_CH2
			Timer_Stop(TIMER_CH2);
			#endif
			
			/*  SOS module is not initialized */
			gsu8_SOSInitStatus = NOT_INITIALIZED;
			
		}
	
	return u8_status;
}

/**
* @brief: add task to the buffer
* @param: gptr_SOS_Task: pointer to callback function,
* 	  u16_Delay: requested delay,
* 	  u16_Periodicity: periodic or one shot
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS SOS_CreateTask(strSOS_TCB_t *gptr_SOS_Task)
{
	
	/*
		ERROR_STATUS u8_status = E_OK;
*/
		ERROR_STATUS u8_status = SOS_ERROR_BASE + NO_ERRORS;
		
		/* check the module */
	if(gsu8_SOSInitStatus == NOT_INITIALIZED)
	{
		u8_status = SOS_ERROR_BASE + ERROR_NOT_INITIALIZED;
	}
	else
	{
			/* check the function pointer  */	
		if(NULL == gptr_SOS_Task)
		{
			u8_status = SOS_ERROR_BASE + ERROR_NULL_POINTER;
		}
		else
		{
				/* check the buffer is full or not */
			if (gu8_Index == MAX_TASK_COUNT)
			{
				u8_status = SOS_ERROR_BASE + ERROR_FULL_BUFFER;
			}
			else{
				
			/* add the task to the buffer */
			gastrSOS_Task_Buff[gu8_Index].gptr_SOS_Task			= gptr_SOS_Task->gptr_SOS_Task;
			gastrSOS_Task_Buff[gu8_Index].u16_Periodicity       = gptr_SOS_Task->u16_Periodicity;
			gastrSOS_Task_Buff[gu8_Index].u8_SOSTask_Priority   = gptr_SOS_Task->u8_SOSTask_Priority;
			gastrSOS_Task_Buff[gu8_Index].u8_SOSTask_State      = gptr_SOS_Task->u8_SOSTask_State;
			gastrSOS_Task_Buff[gu8_Index].u16_SOS_TicksCount	= ZERO;

			

			/*start the timer for the first time */
			
			if(gu8_Index == ZERO)
			{
				#if  SOS_TIMER_CH0
								
				Timer_Start(TIMER_CH0, gu16_PRELOAD);

				#elif  SOS_TIMER_CH1
				Timer_Start(TIMER_CH1, gu16_PRELOAD);
				#elif  SOS_TIMER_CH2
				Timer_Start(TIMER_CH2, gu16_PRELOAD);
				#endif
		}else
		{
			/* Arrange array based on priority */
			SOS_BufferSort();
		}

			gu8_Index++;
		} /* end of else */
	}
  } /* end of outer else */

	return u8_status;
}

/**
* @brief: SOS_RemoveTask remove the task from buffer
* @param: gptr_SOS_Task: pointer to callback function
* @return: ERROR_STATUS status code with error code if one occurred
*/
 
ERROR_STATUS SOS_RemoveTask(gptr_SOS_Task_t gptr_SOS_Task){

		/*
		ERROR_STATUS u8_status = E_OK;
*/
		ERROR_STATUS u8_status = SOS_ERROR_BASE + NO_ERRORS;
		
		uint8_t u8_TaskIndex;
		
		/* check the module */

	if(gsu8_SOSInitStatus == NOT_INITIALIZED)
	{
		u8_status = SOS_ERROR_BASE + ERROR_NOT_INITIALIZED;
	}
	else
	{
		uint8_t u8_Counter;
		/* check the buffer is empty or not */

		if(gu8_Index == ZERO)
		{
			u8_status = SOS_ERROR_BASE + ERROR_EMPTY_BUFFER;
		}
		else
		{
			/* check the function pointer */

			if (NULL == gptr_SOS_Task)
			{
			u8_status = SOS_ERROR_BASE + ERROR_NULL_POINTER;
			}
			else
			{
					/* loop to find the task  */
			for(u8_Counter = ZERO; u8_Counter < MAX_TASK_COUNT; u8_Counter++)
				{
					if(gastrSOS_Task_Buff[u8_Counter].gptr_SOS_Task == gptr_SOS_Task)
					{
					/* Check if one task exist or full */
					if((gu8_Index == 1) || (gu8_Index == MAX_TASK_COUNT))
						{
						SOS_ClearTask(gu8_Index);
						gu8_Index--;
						}
						else
						{
							u8_TaskIndex = u8_Counter;

							/* Shift TCBs up by one starting from the TCB next to the one to be removed */
							uint8_t u8_temp;
							
							for(u8_temp=(u8_TaskIndex+1); u8_temp<gu8_Index-1; u8_temp++)
							{
								SOS_ShiftTasks(u8_temp , (u8_temp+1));
							}
						
						  /* SOS_ClearTask((gu8_Index-1)); */
						gu8_Index--;
						}
				   }
			  }
		  }
		}

		/*  if buffer is empty so stop the timer */
		
		if(gu8_Index == ZERO)
		{
			#if  SOS_TIMER_CH0
			Timer_Stop(TIMER_CH0);
			
			#elif  SOS_TIMER_CH1
			Timer_Stop(TIMER_CH1); 
			#elif  SOS_TIMER_CH2
			Timer_Stop(TIMER_CH2);
			#endif
		}
	}
	return u8_status;
}

/**
* @brief: SOS_Run Loops through task list and execute each one as requested
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS SOS_Run(void)
{
		/*
		ERROR_STATUS u8_status = E_OK;
*/
		ERROR_STATUS u8_status = SOS_ERROR_BASE + NO_ERRORS;
		
			/* check the resolution flag */
	if(gu8_SOS_TimerOvf_Flag == OVF_TRIGGERED)
	{
		uint8_t u8_Counter;
					
					/* loop the buffer of tasks */
		for(u8_Counter = ZERO; u8_Counter < gu8_Index; u8_Counter++)
		{
			if(NULL == gastrSOS_Task_Buff[u8_Counter].gptr_SOS_Task)
			{
				/* skip for now until making circular buffer */
				u8_status = SOS_ERROR_BASE + ERROR_NULL_POINTER;

			}
			else
			{
				gastrSOS_Task_Buff[u8_Counter].u16_SOS_TicksCount++;
				
				if ( gastrSOS_Task_Buff[u8_Counter].u16_SOS_TicksCount >= gastrSOS_Task_Buff[u8_Counter].u16_Periodicity)
				{
					gastrSOS_Task_Buff[u8_Counter].u8_SOSTask_State = READY_STATE;
				}
			}
		}


		/* Loop through TCB buffer and execute the tasks */
		
		for(u8_Counter = ZERO; u8_Counter < gu8_Index; u8_Counter++)
		{
			if(NULL == gastrSOS_Task_Buff[u8_Counter].gptr_SOS_Task)
			{
				/* skip for now until making circular buffer */
				u8_status = SOS_ERROR_BASE + ERROR_NULL_POINTER;

			}
			else
			{
				/* if the delay is complete */
				
			if(	gastrSOS_Task_Buff[u8_Counter].u8_SOSTask_State == READY_STATE)
				{
					gastrSOS_Task_Buff[u8_Counter].u16_SOS_TicksCount = ZERO;

					gastrSOS_Task_Buff[u8_Counter].gptr_SOS_Task();
					
					gastrSOS_Task_Buff[u8_Counter].u8_SOSTask_State = WAITING_STATE;
					
					break;
								
					/* release it if one shot */

					/*if(gastrSOS_Task_Buff[u8_Counter].u16_Periodicity == ONE_SHOT)
					{
						SOS_Stop(gastrSOS_Task_Buff[u8_Counter].gptr_SOS_Task);
					}*/
				}	
			} /* end of else */
		} /* end of for */
	gu8_SOS_TimerOvf_Flag = OVF_NOT_TRIGGERED;
	} /*check the ovf flag */
	
	else
	{
		/*u8_status = E_NOK;*/
	}
	return u8_status;
}



static void SOS_TimerOvf_CBK(void)
{
		PORTC_DATA ^= HIGH;

	gu8_OvfCounter++;
	
	if(gu8_OvfCounter == SOS_RESOLUTION)
	{
		gu8_SOS_TimerOvf_Flag = OVF_TRIGGERED;

		gu8_OvfCounter = ZERO;
	}
		
	/* Restart and pre-load timer */
	#if  SOS_TIMER_CH0
	
	Timer_Start(TIMER_CH0, gu16_PRELOAD);
	
	#elif  SOS_TIMER_CH1
	Timer_Start(TIMER_CH1, 65286);
	#elif  SOS_TIMER_CH2
	Timer_Start(TIMER_CH2, 6);
	#endif
	
	
	/*sleep disable to clear SE */
	//Sleep_Disable();
}

static void SOS_ClearTask(uint8_t u8_index){
	
				gastrSOS_Task_Buff[gu8_Index].gptr_SOS_Task		    = NULL;
				gastrSOS_Task_Buff[gu8_Index].u8_SOSTask_Priority   = ZERO;
				gastrSOS_Task_Buff[gu8_Index].u8_SOSTask_State		= ZERO;
				gastrSOS_Task_Buff[gu8_Index].u16_Periodicity		= ZERO;
				gastrSOS_Task_Buff[gu8_Index].u16_SOS_TicksCount	= ZERO;
}

static void SOS_ShiftTasks(uint8_t newIndex, uint8_t oldIndex){
	
	
	  gastrSOS_Task_Buff[newIndex].gptr_SOS_Task		= gastrSOS_Task_Buff[oldIndex].gptr_SOS_Task;		
	  gastrSOS_Task_Buff[newIndex].u8_SOSTask_Priority  = gastrSOS_Task_Buff[oldIndex].u8_SOSTask_Priority;  
	  gastrSOS_Task_Buff[newIndex].u8_SOSTask_State		= gastrSOS_Task_Buff[oldIndex].u8_SOSTask_State;		
	  gastrSOS_Task_Buff[newIndex].u16_Periodicity		= gastrSOS_Task_Buff[oldIndex].u16_Periodicity;		
	  gastrSOS_Task_Buff[newIndex].u16_SOS_TicksCount	= gastrSOS_Task_Buff[oldIndex].u16_SOS_TicksCount;	

}


static void SOS_BufferSort(){

strSOS_TCB_t str_TempTask = {0};
uint8_t u8_OuterCounter, u8_InnerCounter;

/* Bubble sort the array based on priority */
for(u8_OuterCounter = 0; u8_OuterCounter < gu8_Index; u8_OuterCounter++){
	for(u8_InnerCounter = 0; u8_InnerCounter < (gu8_Index-1); u8_InnerCounter++){
		
		if(gastrSOS_Task_Buff[u8_InnerCounter].u8_SOSTask_Priority > gastrSOS_Task_Buff[u8_InnerCounter+1].u8_SOSTask_Priority){
			str_TempTask = gastrSOS_Task_Buff[u8_InnerCounter+1];
			gastrSOS_Task_Buff[u8_InnerCounter+1] = gastrSOS_Task_Buff[u8_InnerCounter];
			gastrSOS_Task_Buff[u8_InnerCounter] = str_TempTask;
		}
	 }
   }
   
}