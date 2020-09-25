/*
 * SOS.h
 *
 * Created: 2/24/2020 11:34:57 AM
 *  Author: Ahmed
 */ 

#ifndef __SOS_H__
#define __SOS_H__

/************************************************************************/
/*                       General macros                                 */
/************************************************************************/

/*Task calling types*/
#define ONE_SHOT_CALLING	(0)
#define PERIODIC_CALLING	(1)

/*SOS available timer channels*/
#define SOS_TIM_CH0			(0)
#define SOS_TIM_CH1 		(1)
#define SOS_TIM_CH2			(2)

/************************************************************************/
/*						SOS data types                                  */
/************************************************************************/

/*Task configuration structure*/
typedef struct
{
	uint8_t task_priority;
	void (*fptr)(void);
	uint8_t calling_type;	
	uint16_t periodicity;
}Task_ConfigType;

/*SOS configuration structure*/
typedef struct  
{
	uint8_t timer_channel;
	uint8_t timer_tick_time_ms;
}SOS_ConfigType;

/*SOS Error reporting*/
typedef enum
{
	InvalidChannel_Error = -9,
	NullPtr_Error,
	Dispatcher_Hold_Error,
	Deinit_Without_Init_Error,
	MultipleInit_Error,
	Deleting_Without_Adding_Error,
	MultipleStart_Error,
	FullBuffer_Error,
	OperationSuccess
}EnmSOSError_t;

/************************************************************************/
/*                         SOS functions' prototypes                    */
/************************************************************************/

/*
 * Description: Initializes the Timing Management Unit and its hardware timer.
 * Input: N/A
 * Output: SOS Error status
 * Input/Output: N/A
 */
EnmSOSError_t SOS_Init(void);

/*
 * Description: De-Initializes the Timing Management Unit and its hardware timer.
 * Input: N/A
 * Output: SOS Error status
 * Input/Output: N/A
 */
EnmSOSError_t SOS_DeInit(void);

/*
 * Description: Adds a task object to the SOS.
 * Input: pointer to specified task
 * Output: SOS Error status
 * Input/Output: N/A
 */
EnmSOSError_t SOS_addTask(const Task_ConfigType * TaskPtr);

/*
 * Description: Removes a task object from the SOS.
 * Input: pointer to specified task
 * Output: SOS Error status
 * Input/Output: N/A
 */
EnmSOSError_t SOS_deleteTask(const Task_ConfigType * TaskPtr);

/*
 * Description: Calls the dispatcher of the SOS.
 * Input: pointer to initialization structure of SOS
 * Output: SOS Error status
 * Input/Output: N/A
 */
EnmSOSError_t SOS_run(void);

#endif /* SOS_H_ */