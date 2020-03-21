/*
 * SOS.h
 *
 * Created: 2/24/2020 11:51:46 AM
 *  Author: Ehab & Reem
 */ 


#ifndef SOS_H_
#define SOS_H_

#include "../Infrastructure/std_types.h"
#include "../MCAL/Timer.h"
#include "../MCAL/interrupt.h"
#include "../Infrastructure/Errors.h"





#define STARTING_INDEX		0
#define EMPTY_BUFFER		0
#define NEXT_INDEX			1
#define TCNT_PRELOAD_VALUE	5
#define INITIAL_VALUE_ZERO	0

#define ONESHOT			0
#define PERIODIC		1


#define ERROR_SOS_MODULE_ID 200


	


typedef struct SOS_Task
{
	uint8_t Task_ID;
	uint8_t Periodicity;
	uint32_t delay_ms;
	uint32_t current_ticks;
	void (*CBK_TOV)(void);
	
}SOS_Task;

/**
 * Description: Initializes SOS module 
 * @return function status 
 */
ERROR_STATUS SOS_Init(void);

/**
 * Description: DeInitializes SOS module 
 * @return function status 
 */
ERROR_STATUS SOS_DeInit(void);

/**
 * Description: adds a new task to the task buffer
 * @param: Task_ID : ID of the Consumer
 * @param: CBK_TOV : pointer to function (consumer)
 * @param: delay_ms: period of the consumer
 * @param: Periodicity: either the task is ONESHOT or PERIODIC
 * @return function status 
 */
ERROR_STATUS SOS_Start_Timer (uint8_t Task_ID , void (*CBK_TOV)(void) , uint32_t delay_ms , uint8_t Periodicity);

/**
 * Description: stops a specific task from the task buffer
 * @param: Task_ID : ID of the Consumer
 * @return function status 
 */
ERROR_STATUS SOS_Stop_Timer(uint8_t Task_ID);

/**
 * Description: starts implementing the tasks based on their periods
 * @return function status 
 */
ERROR_STATUS SOS_Dispatch(void);




#endif /* SOS_H_ */