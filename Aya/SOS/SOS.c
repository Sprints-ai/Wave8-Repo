/*
 * SOS.c
 *
 * Created: 3/11/2020 7:21:07 AM
 *  Author: A_ayman
 */ 

#include "SOS.h"

 /*
 *** Local Macros
 */
 
/* TASKS STATUS VALUES */
#define NOT_USED  0
#define RUNNING   1
#define DELETED   2
#define READY	   3
#define WAITING	4

/* to determine if the flags are initialized or not*/
#define NOT_INITIALIZED  0
#define INITIALIZED      1

/* this struct is used to update the status of OS */
typedef struct str_FuncStatus_t
{
	uint8_t u8_Init_Flag;            
	uint8_t u8_Start_Flag;           
	uint8_t u8_Stop_Flag;            
	uint8_t u8_Deinit_Flag;
}str_FuncStatus_t;

/* this struct is used to determine the characteristics of each task */
typedef struct str_SOS_Buffer_t
{
	uint8_t u8_Task_ID;               /* determine the Id for the consumer task */
	uint16_t u8_Periodicity_Time;     /* the wanted delay time */
	uint8_t u8_Status;                /* whether the task is running or not */
	uint8_t u8_Repeat;                /* whether the task is repeated or one shot */
	void(* Ptr_Consumer)(void);       /* pointer to the consumer function */
	uint8_t u8_Pre_Flag;              /* count the time for consumer function until reach it's periodicity  */
	  
}str_SOS_Buffer_t;

/*
*** definition of global variables
*/

/* create OS buffer to serve functions "array of structures"*/
static str_SOS_Buffer_t arrstr_OS_Buffer [OS_BUFFER_SIZE];

/* create instance of str_FuncStatus_t  */
static str_FuncStatus_t  str_FuncStatus;

/* to count elements in the OS buffer*/
static uint8_t gu8_OS_Buffer_Counter = ZERO;

static uint8_t gu8_Timer_Ch_ID = ZERO;
static uint8_t	gu8_Tick_Flag = LOW;



/*
*** local functions prototypes
*/
static ERROR_STATUS Is_Buffer_Empty(void);
static ERROR_STATUS Is_Buffer_Full(void);
static void Timer_CallBack_Function (void);

/*
*** implementation of local functions 
*/

/* this function is used to check if OS buffer is empty or not */
static ERROR_STATUS Is_Buffer_Empty(void)
{
	uint8_t u8_Ret_Status = FALSE;
	if (gu8_OS_Buffer_Counter == ZERO)
	{
		u8_Ret_Status = TRUE;
	}
	else
	{
		u8_Ret_Status = FALSE;
	}
	return u8_Ret_Status;
}

/* this function is used to check if SOS buffer is full or not */
static ERROR_STATUS Is_Buffer_Full(void)
{
	uint8_t u8_Ret_Status = FALSE;
	if (gu8_OS_Buffer_Counter == OS_BUFFER_SIZE)
	{
		u8_Ret_Status=TRUE;
	}
	else
	{
		u8_Ret_Status=FALSE;
	}
	return u8_Ret_Status;
}

/* this function is called when timer over flow occur, this function is used to set a specific flag */
void Timer_CallBack_Function (void)
{
	Timer_SetValue(gu8_Timer_Ch_ID, 6);
	gu8_Tick_Flag = HIGH;

}

/*
***implementation of interface functions
*/

/* this function is used to initialize SOS */
ERROR_STATUS Sos_Init (const gstr_SOS_InitConfig_t * pstr_ConfigPtr )
{
	uint8_t Error = E_OK;
	if (pstr_ConfigPtr!= NULL)
	{
		if (str_FuncStatus.u8_Init_Flag == NOT_INITIALIZED)
		{
			/* set SOS status, already initialized */
			str_FuncStatus.u8_Init_Flag = INITIALIZED;

			/*Timer Configurations*/
			gstr_TimerCfg_t str_TimerCfg;
			str_TimerCfg.Timer_Ch = (pstr_ConfigPtr->u8_Timer_Id);
			str_TimerCfg.Timer_Mode = TIMER_MODE;
			str_TimerCfg.Timer_Prescaler = T0_PRESCALER_64;         //so by using FCPU= 16 MHz, after 250 count we will have a 1 msec 
			str_TimerCfg.Timer_INT_Mode = T0_INTERRUPT_NORMAL ;
			str_TimerCfg.ptr_Timer_CallBack_Func= Timer_CallBack_Function;
			Error|= Timer_Init(&str_TimerCfg);
			/*store timer id in global variable to use in SOS_Start*/
			gu8_Timer_Ch_ID = pstr_ConfigPtr->u8_Timer_Id;
		}
		else
		{
			Error_Push (SOS_MODULE, ERROR_ALREADY_INITIALIZED);
			Error = E_NOK;
		}
			
			
	}
	else
	{
		Error_Push (SOS_MODULE, ERROR_NULL_POINTER);
		Error = E_NOK;
	}

	return Error;	
}

/* this function is used to check timing for each task*/
ERROR_STATUS Sos_Run(void)
{
	uint8_t u8_Buffer_Index = ZERO;
	static uint8_t u8_Flag = ZERO;
	uint8_t Error = E_OK;
	while (1)
	{
		
		if (HIGH == gu8_Tick_Flag)
		{
		/*Search in OS buffer if there is function to server this tick */
		for (u8_Buffer_Index=0; u8_Buffer_Index<OS_BUFFER_SIZE && u8_Flag<gu8_OS_Buffer_Counter; u8_Buffer_Index++)
		{
			if(arrstr_OS_Buffer[u8_Buffer_Index].u8_Status == WAITING)
			{
				arrstr_OS_Buffer[u8_Buffer_Index].u8_Pre_Flag++;

				/*Check if this task will serve this tick*/
				if  (arrstr_OS_Buffer[u8_Buffer_Index].u8_Pre_Flag == (arrstr_OS_Buffer[u8_Buffer_Index].u8_Periodicity_Time) )
				{
					arrstr_OS_Buffer[u8_Buffer_Index].u8_Status = RUNNING;
					arrstr_OS_Buffer[u8_Buffer_Index].Ptr_Consumer();
					arrstr_OS_Buffer[u8_Buffer_Index].u8_Pre_Flag = ZERO;
					arrstr_OS_Buffer[u8_Buffer_Index].u8_Status = WAITING;					
				}
			}
		}
		/*clear the tick flag to let the timer call back function set it again and call the dispatch*/
		gu8_Tick_Flag = LOW;
		}
		CPU_Sleep_Mode_Enable (CPU_IDLE_SLEEP_MODE );
	}
	
	return Error;
}
	
/* this function is used to delete a specific function */
ERROR_STATUS Sos_Delete_Task (uint8_t Task_Id)
{
	uint8_t au8_Search_Loop_Counter = ZERO;
	uint8_t Error = E_OK;

	if (INITIALIZED == str_FuncStatus.u8_Init_Flag  )
	{	
		if (INITIALIZED == str_FuncStatus.u8_Start_Flag )
		{
			if (FALSE == Is_Buffer_Empty())
				{
					/* Search for about given task*/
					for (au8_Search_Loop_Counter = ZERO; au8_Search_Loop_Counter < OS_BUFFER_SIZE; au8_Search_Loop_Counter++)
					{
						/*Check if this task is the desired to stop*/
						if ((Task_Id == arrstr_OS_Buffer[au8_Search_Loop_Counter].u8_Task_ID))
						{
							/*stop the task*/
							arrstr_OS_Buffer[au8_Search_Loop_Counter].u8_Status = NOT_USED;
							arrstr_OS_Buffer[au8_Search_Loop_Counter].Ptr_Consumer = NULL;
							/*decrease the buffer*/
							gu8_OS_Buffer_Counter --;
							break;
						}
					}
					/*if the buffer empty after this decrease stop the timer to stop receiving timer interrupt */
					if (TRUE == Is_Buffer_Empty())
					Timer_Stop(Timer_0);
				}
				else
				{
					Error_Push (SOS_MODULE, ERROR_EMPTY_BUFFER);
					Error = E_NOK;
				}
		}
		else
		{
			Error_Push (SOS_MODULE,ERROR_STOP_WITHOUT_START  );
			Error = E_NOK;
		}
	}
	else
	{
		Error_Push (SOS_MODULE, ERROR_NOT_INITIALIZED);
		Error = E_NOK;
		
	}
		
	return Error;	
}

/* this function is used to start a specific function */
ERROR_STATUS Sos_Create_Task (gstr_Task_Info_t* ptrstr_Task)
{
	uint8_t Error = E_OK;
	
	if (INITIALIZED == str_FuncStatus.u8_Init_Flag)
	{
	   if (FALSE == Is_Buffer_Full())
		{
		   if (NULL != ptrstr_Task->Ptr_Func)
		   {
				 
			   /*Create struct for the new creator*/
				str_SOS_Buffer_t str_Buffer;
				str_Buffer.u8_Status = WAITING;
				str_Buffer.u8_Periodicity_Time = ptrstr_Task-> Time_Delay;
				str_Buffer.u8_Repeat = ptrstr_Task-> Repeat;
				str_Buffer.Ptr_Consumer =  ptrstr_Task-> Ptr_Func;
				str_Buffer.u8_Pre_Flag = 1;
				str_Buffer.u8_Task_ID = ptrstr_Task-> Task_Id;
				      
				/*Insert the created struct for the new creator in the SOS buffer*/
				arrstr_OS_Buffer[ptrstr_Task-> Task_Id] = str_Buffer;
				      
				/*if the buffer empty start the timer */
				if (TRUE == Is_Buffer_Empty())
				Timer_Start(Timer_0,250);

				/*increment buffer counter before adding new task*/
				gu8_OS_Buffer_Counter++;

			}
			else
			{
				Error_Push (SOS_MODULE, ERROR_NULL_POINTER);
				Error = E_NOK;
			}
		}

		else
		{
		   Error_Push (SOS_MODULE, ERROR_FULL_BUFFER);
			Error = E_NOK;
		}
		  
	}

	else
	{
	   Error_Push (SOS_MODULE, ERROR_NOT_INITIALIZED);
		Error = E_NOK;
	}
	return Error;
}

/* this function is used to deinitialize Sos */
ERROR_STATUS Sos_DeInit (void)
{
	uint8_t Error = E_OK;

	/*check if the module was initialized early*/
	if (INITIALIZED == str_FuncStatus.u8_Init_Flag)
	{
		/*check if the Sos buffer is empty to keep the tasks correct*/
		if (TRUE == Is_Buffer_Empty())
		{
			str_FuncStatus.u8_Init_Flag = NOT_INITIALIZED;
			str_FuncStatus.u8_Start_Flag = NOT_INITIALIZED;
			str_FuncStatus.u8_Stop_Flag = NOT_INITIALIZED;

		}
	else
	{
		Error_Push (SOS_MODULE, ERROR_NOT_EMPTY_BUFFER);
		Error = E_NOK;
	}
	}
	else
	{
		Error_Push (SOS_MODULE, ERROR_NOT_INITIALIZED);
		Error = E_NOK;
	}
return Error;
}
