/*
 * TMU.h
 *
 * Created: 2/24/2020 1:47:59 PM
 *  Author: Ema
 */ 


#ifndef TMU_H_
#define TMU_H_

/************************************************************************/
/*				 INCLUDES											    */
/************************************************************************/

#include "std_types.h"
#include "common_macros.h"
#include "Timer.h"

/************************************************************************/
/*				 DEFINES											    */
/************************************************************************/

#define ONESHOOT 0
#define PERIODIC 1

#define SOSError_t sint8_t

typedef struct SOS_ConfigType{
	uint8_t Timer_CH;
	uint8_t Sys_Tick;
	
}SOS_ConfigType;

typedef struct SOS_SW_Task{
	sint16_t Task_delay;
	uint8_t	 Task_priority;
	void (*Task_CallBackfun)(void);
	
}SOS_SW_Task;


/************************************************************************/
/*		         TIMER FUNCTIONS' PROTOTYPES						    */
/************************************************************************/

/**
 * Input: Pointer to a structure contains the information needed to initialize the SOS. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */
extern SOSError_t SOS_Init (const SOS_ConfigType * ConfigPtr);
/**
 * Input:  
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: DeInitiates the module.
 * 							
 */
extern SOSError_t SOS_DeInit (void);
/**
 * Input: Pointer to a structure contains the information needed to start a task.
 *		   Task Delay	    up to 65536
 *		   Task_priority :	up to TASKS_MAX_NUM  
 * Output:
 * In/Out: 
 *		   					
 * Return: The error status of the function.			
 * Description: Create a task.
 * SOS doesn't support round robin so each task should have a unique priority.. tasks priority reflects its ID.						
 */	
extern SOSError_t SOS_Create_Task(const SOS_SW_Task * SW_Task);
/**
 * Input: Pointer to a structure contains the information needed to stop the task. 
 *		  Task Delay	    up to 65536
 *		  Task_priority :	up to TASKS_MAX_NUM 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Delete a task.
 * 							
 */
extern SOSError_t SOS_Delete_Task(const SOS_SW_Task * SW_Task);
/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: 			
 * Description: Control the Tasks.
 * 							
 */
extern void SOS_Run(void);



#endif /* TMU_H_ */