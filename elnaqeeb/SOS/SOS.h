/*
 * TMU.h
 *
 * Created: 2/24/2020 11:34:57 AM
 *  Author: ahmed
 */ 


#ifndef __TMU_H__
#define __TMU_H__

#define ONE_SHOT_CALLING	(0)
#define PERIODIC_CALLING	(1)

#define TMU_TIM_CH0			(0)
#define TMU_TIM_CH1 		(1)
#define TMU_TIM_CH2			(2)

typedef struct
{
	uint8_t task_id;
	void (*fptr)(void);
	uint8_t calling_type;	
	uint16_t periodicity;
}Task_ConfigType;

typedef struct  
{
	uint8_t timer_channel;
	uint8_t timer_tick_time_ms;
}TMU_ConfigType;

typedef enum
{
	InvalidChannel_Error = -9,
	NullPtr_Error,
	Dispatcher_Hold_Error,
	Deinit_Without_Init_Error,
	MultipleInit_Error,
	Stop_Without_Start_Error,
	MultipleStart_Error,
	FullBuffer_Error,
	OperationSuccess
}EnmTMUError_t;



/************************************************************************/
/*                         TMU functions' prototypes                    */
/************************************************************************/

/*
 * Description: Initializes the Timing Management Unit and its hardware timer.
 * Input: pointer to initialization structure of TMU
 * Output: N/A
 * Input/Output: N/A
 */
EnmTMUError_t TMU_Init(const TMU_ConfigType * ConfigPtr);

/*
 * Description: De-Initializes the Timing Management Unit and its hardware timer.
 * Input: N/A
 * Output: N/A
 * Input/Output: N/A
 */
EnmTMUError_t TMU_DeInit(void);

/*
 * Description: Adds the timer software object to the TMU.
 * Input: pointer to specified task
 * Output: N/A
 * Input/Output: N/A
 */
EnmTMUError_t TMU_Start_Timer(const Task_ConfigType * TaskPtr);

/*
 * Description: Removes the timer software object to the TMU.
 * Input: pointer to specified task
 * Output: N/A
 * Input/Output: N/A
 */
EnmTMUError_t TMU_Stop_Timer(const Task_ConfigType * TaskPtr);

/*
 * Description: Calls the dispatcher of the TMU.
 * Input: pointer to initialization structure of TMU
 * Output: N/A
 * Input/Output: N/A
 */
EnmTMUError_t TMU_Dispatch(void);

#endif /* TMU_H_ */