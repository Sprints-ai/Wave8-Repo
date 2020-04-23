/*
 * SOS.h
 *
 * Created: 2020-02-24 11:20:47 AM
 *  Author: EbrahimOseif
 */ 


#ifndef SOS_H_
#define SOS_H_

/************************************************************************/
/*				             INCLUDES		                 	        */
/************************************************************************/

#include "std_types.h"
#include "SOS_cfg.h"
#include "Timer.h"
#include "Error.h"


/************************************************************************/
/*				         DEFINES								        */
/************************************************************************/


 /* function state periodic or one shot */
 
#define		PERIODIC				(0)
#define		ONE_SHOT				(1)

/* timer resolution in ms */

#define		SOS_RESOLUTION			(10)

/* pointer to function type */

typedef void (*gptr_SOS_Task_t) (void);

/* module state */
#define		NOT_INITIALIZED		0
#define		INITIALIZED			1

/* SOSTask states */
#define		WAITING_STATE		0
#define		READY_STATE			1


typedef	uint16_t u16_Delay_t;


/************************************************************************/
/*			  Structures Declarations		                            */
/************************************************************************/


typedef struct strSOS_TCB_t
{
  gptr_SOS_Task_t gptr_SOS_Task;
  uint8_t	u8_SOSTask_Priority;
  uint8_t	u8_SOSTask_State;
  uint16_t	u16_SOS_TicksCount;
  uint16_t	u16_Periodicity;
}strSOS_TCB_t;

/* Create the buffer  of tasks */
strSOS_TCB_t gastrSOS_Task_Buff[MAX_TASK_COUNT];



/************************************************************************/
/*						 FUNCTIONS' PROTOTYPES		                    */
/************************************************************************/

/**
* @brief: SOS Initialization
*		  initialize the timer and buffer
* @param: void
* Input : void
* Output:  
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS SOS_Init(void);

/**
* @brief: SOS DeInitialization
*			empty the buffer from tasks
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS SOS_DeInit(void);

/**
* @brief: add task to the buffer
* @param: gptr_SOS_Task: task structure 
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS SOS_CreateTask(strSOS_TCB_t *gptr_SOS_Task);

/**
* @brief: SOS_RemoveTask remove the task from buffer
* @param: gptr_SOS_Task: pointer to callback function
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS SOS_RemoveTask(gptr_SOS_Task_t gptr_SOS_Task);

/**
* @brief: SOS_Run Loops through task list and execute each one as requested
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS SOS_Run(void);


#endif /* SOS_H_ */