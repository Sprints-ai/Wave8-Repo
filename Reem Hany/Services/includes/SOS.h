/*
 * SOS.h
 *
 * Created: 3/10/2020 4:14:45 PM
 *  Author: Reem
 */ 


#ifndef SOS_H_
#define SOS_H_

#include "std_types.h"
#include "../../MCAL/includes/Timer.h"


/****************************************************/
/*              Defines                             */
/****************************************************/

//SOS Modes
#define     ONE_SHOT                        0
#define     PERIODIC                        1

//SOS Buffer size
#define SOS_TASK_BUFFER_SIZE                100

//ERROR Value Of the Module 
#define SOS_ERROR                          -700

       

/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/

typedef struct strSOS_TASK_Cfg_t{
	uint16_t Task_id;
	void (*SOS_Cbk_ptr)(void);
	uint8_t SOS_MODE;
	uint32_t Delay_TimeMs;
	uint32_t Delay_Counter;
	uint32_t Priority;
}strSOS_TASK_Cfg_t;

/************************************************************************/
/*			  Functions Prototypes		                                */
/************************************************************************/

/**
 * Input: Pointer to a structure contains the information needed to initialize the SOS. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the timer.
 * 							
 */
extern ERROR_STATUS SOS_Init(void);

/**
 * Input:  
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: this function De-initializes the module
 * 							
 */
extern ERROR_STATUS SOS_DeInit(void);

/**
 * Input: 
 * 	task: Pointer to a structure contains the information needed to create the SOS task.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function act as the SOS creator as it starts the initialized timer , 
 *              creates the task and save it in the SOS task buffer.
 * 							
 */
extern ERROR_STATUS SOS_Create_Task(strSOS_TASK_Cfg_t* task);

/**
 * Input: 
 * 	taskID: the id of a specific task.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function removes the task with the given id.
 * 							
 */
extern ERROR_STATUS SOS_Delete_Task(uint8_t taskID);

/**
 * Input: 
 * 	taskID: the id of a specific task.
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function act as the SOS Manager that manages the SOS task buffer and calls the SOS Consumers for each task
 *				 when the time is finished of this task
 * 							
 */
extern void SOS_Run(void);





#endif /* SOS_H_ */