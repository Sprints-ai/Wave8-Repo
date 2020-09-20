/*
 * TMU.h
 *
 * Created: 2/24/2020 11:51:46 AM
 *  Author: Ehab & Reem
 */ 


#ifndef TMU_H_
#define TMU_H_

#include "../Infrastructure/std_types.h"
#include "../MCAL/Timer.h"
#include "../MCAL/interrupt.h"
#include "../Infrastructure/Errors.h"

#define BUFFER_SIZE		50
#define STARTING_INDEX	 0

#define TIMER_OVF_VECT	TIMER0_OVF_vect 
#define TCNT			TCNT0
#define ERROR_TMU_MODULE_ID 200

typedef enum EnmTMUError_t 
{
	error1,
	error2,
	error3
	
}EnmTMUError_t;
	


typedef struct TMU_Task
{
	uint8_t Task_ID;
	uint32_t delay_ms;
	uint32_t current_ticks;
	void (*CBK_TOV)(void);
	
}TMU_Task;

/**
 * Description: Initializes TMU module 
 * @return function status 
 */
ERROR_STATUS TMU_Init(void);

/**
 * Description: DeInitializes TMU module 
 * @return function status 
 */
ERROR_STATUS TMU_DeInit(void);

/**
 * Description: adds a new task to the task buffer
 * @param: Task_ID : ID of the Consumer
 * @param: CBK_TOV : pointer to function (consumer)
 * @param: delay_ms: period of the consumer
 * @return function status 
 */
ERROR_STATUS TMU_Start_Timer (uint8_t Task_ID , void (*CBK_TOV)(void) , uint32_t delay_ms );

/**
 * Description: stops a specific task from the task buffer
 * @param: Task_ID : ID of the Consumer
 * @return function status 
 */
ERROR_STATUS TMU_Stop_Timer(uint8_t Task_ID);

/**
 * Description: starts implementing the tasks based on their periods
 * @return function status 
 */
ERROR_STATUS TMU_Dispatch(void);


#endif /* TMU_H_ */