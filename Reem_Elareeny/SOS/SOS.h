/*
 * SOS.h
 *
 * Created: 3/10/2020 5:32:41 PM
 *  Author: Reem el-Areeny
 */ 


#ifndef SOS_H_
#define SOS_H_

/************************************************************************/
/*											INCLUDES							            */
/************************************************************************/
#include "../Infrastructure/std_types.h"
#include "../MCAL/Timer.h"
#include "../MCAL/interrupt.h"
#include "../Infrastructure/Errors.h"


/************************************************************************/
/*											DEFINES							            */
/************************************************************************/
#define BUFFER_SIZE		50
#define STARTING_INDEX	0

#define INITIAL_VALUE	0

#define PERIODIC			1
#define ONE_SHOT			2

/* configurations */
#define TIMER_OVF_VECT			TIMER0_OVF_vect
#define TIMER_CHANNEL			TIMER_CH0
#define TIMER_INITIAL_VALUE	0x05
#define TCNT						TCNT0

#define ERROR_SOS_MODULE_ID	200


/************************************************************************/
/*								  Structures Definitions	                     */
/************************************************************************/
typedef struct SOS_Task
{
	uint8_t Task_Priority;
	uint8_t periodic_or_oneShot;
	uint32_t delay_ms;
	uint32_t current_ticks;
	void (*CBK_TOV)(void);
	
}SOS_Task;


/************************************************************************/
/*						    TIMER FUNCTIONS' PROTOTYPES							   */
/************************************************************************/
/**
 * Description: Initializes SOS module 
 * @return function status 
 */
extern ERROR_STATUS SOS_Init(void);

/**
 * Description: DeInitializes SOS module 
 * @return function status 
 */
extern ERROR_STATUS SOS_DeInit(void);

/**
 * Description: adds a new task to the task buffer
 * @param: Task_ID : ID of the Consumer
 * @param: CBK_TOV : pointer to function (consumer)
 * @param: delay_ms: period of the consumer
 * @return function status 
 */
extern ERROR_STATUS SOS_Create(uint8_t Task_ID , void (*CBK_TOV)(void) , uint32_t delay_ms, uint8_t periodic_or_oneShot);

/**
 * Description: stops a specific task from the task buffer
 * @param: Task_ID : ID of the Consumer
 * @return function status 
 */
extern ERROR_STATUS SOS_Delete(uint8_t Task_ID);

/**
 * Description: starts implementing the tasks based on their periods
 * @return function status 
 */
extern ERROR_STATUS SOS_Run(void);


#endif /* SOS_H_ */