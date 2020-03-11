/*
* SOS.c
*
* Created: 2/24/2020 11:47:28 AM
*  Author: Reem
*/
#include "SOS.h"
#include "SOS_PCfg.h"

/*******Static Global Variables*********/
static SOS_TASK_Cfg *gstr_TasksBuffer[SOS_TASK_BUFFER_SIZE];

static uint8_t gu8_InitFlag=FALSE,//>>Init flag should be initialized here before init to check whether the module is iniatilized or not
gu8_StartedFlag,
gu8_ISR_Flag;


/**********Static Prototypes************/

static ERROR_STATUS SOS_RemoveTask(uint16_t TaskID);
static void SOS_CheckFlag(void);
static void SOS_SortTasks(void);

/*******Function Implementation*********/

/**
* Input:
* Output:
* In/Out:
* Return:
* Description: this function used to act as a callback function that is called by the ISR in timer module to inform the SOS Dispatcher that the ISR came
*
*/
static void SOS_CheckFlag(void){
	gu8_ISR_Flag = TRUE;
}

/**
* Input: Pointer to a structure contains the information needed to initialize the SOS.
* Output:
* In/Out:
* Return: The error status of the function.
* Description: Initiates the timer.
*
*/
ERROR_STATUS SOS_Init(void){
	//Define locals
	ERROR_STATUS aES_errorStatus;
	static Timer_cfg_s astr_TimerCfg;
	uint16_t au16_TaskIterator;

	/*Check if the module is initialized or not*/
	if(gu8_InitFlag == FALSE){
		//ERROR assignment
		aES_errorStatus = E_OK;
		
		//Initialize the globals
		gu8_StartedFlag = FALSE,
		gu8_ISR_Flag=FALSE;
		
		for (au16_TaskIterator = 0; au16_TaskIterator < SOS_TASK_BUFFER_SIZE; au16_TaskIterator++)
		gstr_TasksBuffer[au16_TaskIterator] = NULL;
		
		
		//Check on timer channel
		switch(SOS_cfg.TIM_Ch){
			case SOS_TIMER_CH0:
			//Timer initialization
			astr_TimerCfg.Timer_CH_NO = SOS_TIMER_CH0;
			//ERROR assignment
			aES_errorStatus = E_OK;
			break;

			case SOS_TIMER_CH1:
			//Timer initialization
			astr_TimerCfg.Timer_CH_NO = SOS_TIMER_CH1;
			//ERROR assignment
			aES_errorStatus = E_OK;
			break;

			case SOS_TIMER_CH2:
			//Timer initialization
			astr_TimerCfg.Timer_CH_NO = SOS_TIMER_CH2;
			//ERROR assignment
			aES_errorStatus = E_OK;
			break;

			default:
			//ERROR assignment
			aES_errorStatus = (E_INVALID_PARAMETER + SOS_ERROR);
			break;
		}
		
		if(aES_errorStatus == E_OK){
			astr_TimerCfg.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;

			//Resolution >> prescaler 64
			astr_TimerCfg.Timer_Prescaler = TIMER_PRESCALER_64;
			astr_TimerCfg.Timer_Cbk_ptr= SOS_CheckFlag;

			//ERROR assignment
			aES_errorStatus = Timer_Init(&astr_TimerCfg);
		}
	}
	//In case the module is already initialized
	else{
		//ERROR assignment
		aES_errorStatus = (E_MULTIPLE_INITIALIZION + SOS_ERROR);
	}

	//Check whether the error is OK or not
	if (aES_errorStatus == E_OK)
	{
		//Mark that the module is initialized successfully
		gu8_InitFlag = TRUE;
	}
	else{
		//Mark that the module is initialized unsuccessfully
		gu8_InitFlag = FALSE;
	}

	//Return the error status
	return aES_errorStatus;
}

/**
* Input:
* Output:
* In/Out:
* Return: The error status of the function.
* Description: this function De-initializes the module
*
*/
ERROR_STATUS SOS_DeInit(void){
	//Define locals
	ERROR_STATUS aES_errorStatus;
	uint16_t au16_TaskIterator;


	/*Check whether the module is initialized or not*/

	//The module has already been initialized
	if (gu8_InitFlag == TRUE)
	{
		//ERROR assignment
		aES_errorStatus = E_OK;
		
		//Re-Initialize the globals
		gu8_InitFlag=FALSE,
		gu8_StartedFlag = FALSE,
		gu8_ISR_Flag=FALSE;
		
		//LOOP on the whole buffer to reset it
		for (au16_TaskIterator = 0; au16_TaskIterator < SOS_TASK_BUFFER_SIZE; au16_TaskIterator++)
		gstr_TasksBuffer[au16_TaskIterator] = NULL;
		switch(SOS_cfg.TIM_Ch){
			case SOS_TIMER_CH0:
			aES_errorStatus = Timer_Stop(SOS_TIMER_CH0);
			break;
			case SOS_TIMER_CH1:
			aES_errorStatus = Timer_Stop(SOS_TIMER_CH1);
			break;
			case SOS_TIMER_CH2:
			aES_errorStatus = Timer_Stop(SOS_TIMER_CH2);
			break;
			default:
			aES_errorStatus =(E_INVALID_PARAMETER + SOS_ERROR);
			break;
		}
		if(aES_errorStatus ==E_OK){
			//MARK that the module is De-initialized
			gu8_InitFlag = FALSE;
		}

	}
	else{
		//ERROR assignment
		aES_errorStatus = (E_UNINITIALIZED_MODULE + SOS_ERROR);
	}

	//Return the error status
	return aES_errorStatus;
}

/**
* Input:
* 	task: Pointer to a structure contains the information needed to create the SOS task.
* Output:
* In/Out:
* Return: The error status of the function.
* Description: This function act as the SOS creator as it starts the initialized timer , creates the task and save it in the SOS task buffer.
*
*/
ERROR_STATUS SOS_Create_Task(SOS_TASK_Cfg* task){

	//Define locals
	uint16_t au16_TaskIterator;
	uint8_t  au8_CreatedFlag=FALSE;
	ERROR_STATUS aES_errorStatus;

	/*Check whether the module is initialized or not*/

	//In case the module is already initialized
	if(gu8_InitFlag == TRUE){

		//ERROR assignment
		aES_errorStatus = E_OK;

		/*Check whether the pointer is null or not*/

		//In case the pointer not equal to NULL
		if(task != NULL){
			//ERROR assignment
			aES_errorStatus = E_OK;

			/*Task parameters checking*/

			task->Delay_Counter = task->Delay_TimeMs;
			for (au16_TaskIterator = 0; au16_TaskIterator < SOS_TASK_BUFFER_SIZE; au16_TaskIterator++)
			{
				if(gstr_TasksBuffer[au16_TaskIterator] != NULL){
					if (task->Task_id == gstr_TasksBuffer[au16_TaskIterator]->Task_id)
					{
						aES_errorStatus = (E_INVALID_PARAMETER + SOS_ERROR);
						break;
					}
				}

			}
			if (aES_errorStatus == E_OK)
			{


				switch(task->SOS_MODE){
					case PERIODIC:
					//ERROR assignment
					aES_errorStatus = E_OK;
					break;

					case ONE_SHOT:
					//ERROR assignment
					aES_errorStatus = E_OK;
					break;

					default:
					//ERROR assignment
					aES_errorStatus = (E_INVALID_PARAMETER + SOS_ERROR);
					break;
				}

				/*ERROR Checking to decide whether to continue the next step or not*/


				//In case error is OK
				if (aES_errorStatus == E_OK)
				{
					/*Check whether the pointer to function is NULL or not*/

					//In case the pointer is NULL
					if(task->SOS_Cbk_ptr == NULL){
						//ERROR assignment
						aES_errorStatus = (E_NULL_PTR + SOS_ERROR);
					}
					//In case the the pointer is not equal to NULL
					else{

						//ERROR assignment
						aES_errorStatus = E_OK;

						/*Loop on the whole Buffer, Get the first empty place and save the task in this place in the buffer*/
						for(au16_TaskIterator = 0; au16_TaskIterator < SOS_TASK_BUFFER_SIZE ;au16_TaskIterator++){
							if(gstr_TasksBuffer[au16_TaskIterator] == NULL){
								au8_CreatedFlag =TRUE;
								gstr_TasksBuffer[au16_TaskIterator] = task;
								break;
							}
						}
						
						if(au8_CreatedFlag == FALSE){
							//ERROR assignment
							aES_errorStatus = (E_FULL_BUFFER + SOS_ERROR);
						}
						else{
							
							//Sort the task according to its priorities
							SOS_SortTasks();
							//In case the timer is already started
							if(gu8_StartedFlag == TRUE){
								aES_errorStatus = E_OK;
							}
							//In case the timer is not started
							else{
								/*Check on timer channel*/
								switch(SOS_cfg.TIM_Ch){
									//In case using Timer 0
									case SOS_TIMER_CH0:
									//Start the timer
									aES_errorStatus = Timer_Start(SOS_TIMER_CH0,(_8BIT_RESOLUTION_-SOS_cfg.Resolutions));
									//Mark that the timer is started successfully
									gu8_StartedFlag = TRUE;
									
									break;

									//In case using Timer 1
									case SOS_TIMER_CH1:
									
									//Start the timer
									aES_errorStatus = Timer_Start(SOS_TIMER_CH1,(_16BIT_RESOLUTION_-SOS_cfg.Resolutions));
									//Mark that the timer is started successfully
									gu8_StartedFlag = TRUE;
									break;

									//In case using Timer 2
									case SOS_TIMER_CH2:
									//Start the timer
									aES_errorStatus = Timer_Start(SOS_TIMER_CH2,SOS_cfg.Resolutions);
									//Mark that the timer is started successfully
									gu8_StartedFlag = TRUE;
									break;
									
									default:
									//ERROR assignment
									aES_errorStatus = (E_INVALID_PARAMETER + SOS_ERROR);
									break;
								}
							}
						}				
					}
				}
			}

			//if (aES_errorStatus != E_OK)
			else{
				//Do nothing
			}

		}
		//In case the task is a null pointer
		else{
			//ERROR assignment
			aES_errorStatus = (E_NULL_PTR + SOS_ERROR);
		}
	}
	//In case the module is uninitialized
	else{
		//ERROR assignment
		aES_errorStatus = (E_UNINITIALIZED_MODULE + SOS_ERROR);
	}

	//Return the error status
	return aES_errorStatus;
}

/**
* Input:
* 	taskID: the id of a specific task.
* Output:
* In/Out:
* Return: The error status of the function.
* Description: This function removes the task with the given id.
*
*/
ERROR_STATUS SOS_Delete_Task(uint8_t taskID){
	/*Define Locals*/
	ERROR_STATUS aES_errorStatus;

	/*Check whether the module is initialized or not*/

	//In case the module has already been initialized
	if (gu8_InitFlag == TRUE)
	{
		//ERROR assignment
		aES_errorStatus = E_OK;

		/*Check if the SOS is started or not*/

		//In case the SOS is started
		if(gu8_StartedFlag == TRUE){
			//ERROR assignment
			aES_errorStatus = E_OK;

			/*Remove the task with the given task_id */
			aES_errorStatus = SOS_RemoveTask(taskID);
			
			//Sort the task according to its priorities
			SOS_SortTasks();

		}
		else{
			//ERROR assignment
			aES_errorStatus = (E_STOP_WITHOUT_START + SOS_ERROR);
		}
	}
	//In case the module is uninitialized
	else{
		//ERROR assignment
		aES_errorStatus = (E_UNINITIALIZED_MODULE + SOS_ERROR);
	}

	//Return the error status
	return aES_errorStatus;
}

/**
* Input:
* Output:
* In/Out:
* Return:
* Description: This function act as the SOS Manager that manages the SOS task buffer and calls the SOS Consumers for each task
*				 when the time is finished of this task
*
*/
void SOS_Run(void){
	//Define locals
	uint16_t au16_TaskIterator = 0;

	//In case there is an interrupt
	if(gu8_ISR_Flag == TRUE){
		//Reset the ISR FLAG
		gu8_ISR_Flag = FALSE;
		
		//Loop on all the objects in the buffer
		while(gstr_TasksBuffer[au16_TaskIterator] != NULL){
			//In case an object exists in this index
			
			//Decrease the delay
			gstr_TasksBuffer[au16_TaskIterator]->Delay_Counter--;

			//In case the delay is finished
			if (gstr_TasksBuffer[au16_TaskIterator]->Delay_Counter == 0)
			{
				//Execute the callback function
				gstr_TasksBuffer[au16_TaskIterator]->SOS_Cbk_ptr();

				//In case the task is periodic reset the Counter
				if(gstr_TasksBuffer[au16_TaskIterator]->SOS_MODE == PERIODIC){
					gstr_TasksBuffer[au16_TaskIterator]->Delay_Counter = gstr_TasksBuffer[au16_TaskIterator]->Delay_TimeMs;
				}
				//In case the task is one shot function remove the task
				else{
					gstr_TasksBuffer[au16_TaskIterator]= NULL;
				}
			}
			au16_TaskIterator++;
		}
	}
}

/**
* Input:
* 	taskID: the id of a specific task.
* Output:
* In/Out:
* Return:
* Description: This function Removes the task with the given id from the buffer
*
*/
static ERROR_STATUS SOS_RemoveTask(uint16_t TaskID){
	//Define Locals
	uint16_t au16_TaskIterator;
	ERROR_STATUS aES_errorStatus;

	for (au16_TaskIterator =0; au16_TaskIterator < SOS_TASK_BUFFER_SIZE; au16_TaskIterator++)
	{
		if(gstr_TasksBuffer[au16_TaskIterator] != NULL){
			if (gstr_TasksBuffer[au16_TaskIterator]->Task_id == TaskID)
			{
				gstr_TasksBuffer[au16_TaskIterator] = NULL;
				aES_errorStatus = E_OK;
				break;
			}
			else{
				aES_errorStatus = (E_INVALID_PARAMETER + SOS_ERROR);
			}
		}
		else{
			aES_errorStatus = (E_INVALID_PARAMETER + SOS_ERROR);
		}

	}
	return aES_errorStatus;
}


static void SOS_SortTasks(void){
	uint16_t au16_task_i, au16_task_j ;
	
	SOS_TASK_Cfg *temp;
	for (au16_task_i = 0; au16_task_i < SOS_TASK_BUFFER_SIZE-1; au16_task_i++){
		// Last i elements are already in place
		for (au16_task_j = 0; au16_task_j < SOS_TASK_BUFFER_SIZE-au16_task_i-1; au16_task_j++)
		{
			if((gstr_TasksBuffer[au16_task_j] == NULL ))
			{
				temp = gstr_TasksBuffer[au16_task_j];
				gstr_TasksBuffer[au16_task_j] = gstr_TasksBuffer[au16_task_j+1];
				gstr_TasksBuffer[au16_task_j+1] = temp;
			}
			else if(gstr_TasksBuffer[au16_task_j+1]!= NULL){
				if( (gstr_TasksBuffer[au16_task_j]->Priority > gstr_TasksBuffer[au16_task_j+1]->Priority)){
					temp = gstr_TasksBuffer[au16_task_j];
					gstr_TasksBuffer[au16_task_j] = gstr_TasksBuffer[au16_task_j+1];
					gstr_TasksBuffer[au16_task_j+1] = temp;
				}
			}
		}
		
	}
}