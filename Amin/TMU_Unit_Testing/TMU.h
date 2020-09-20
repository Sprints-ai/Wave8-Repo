#ifndef TMU_H_
#define TMU_H_

/************************************************************************/
/*				 INCLUDES											    */
/************************************************************************/

#include "mock_std_types.h"
#include "common_macros.h"
#include "mock_timer.h"

/************************************************************************/
/*				 DEFINES											    */
/************************************************************************/

#define ONESHOOT 0
#define PERIODIC 1

#define TMUError_t sint8_t

typedef struct TMU_ConfigType{
	sint8_t Timer_CH;
	uint8_t resloution;

}TMU_ConfigType;

typedef struct TMU_SW_Timer{
	uint8_t TaskID;   //5
	sint16_t Task_delay;  //1
	sint8_t Delay_type;   //1
	void (*Task_CallBackfun)(void);

}TMU_SW_Timer;


/************************************************************************/
/*		         TIMER FUNCTIONS' PROTOTYPES						    */
/************************************************************************/

/**
 * Input: Pointer to a structure contains the information needed to initialize the TMU.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Initiates the module.
 *
 */
extern TMUError_t TMU_Init (const TMU_ConfigType * ConfigPtr);
/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: DeInitiates the module.
 *
 */
extern TMUError_t TMU_DeInit (void);
/**
 * Input: Pointer to a structure contains the information needed to start a task.
 *         Task ID			0 -> 9
 *		   Task Delay	    up to 65536
 *		   Delay type : periodic / oneshoot
 * Output:
 * In/Out:
 *
 * Return: The error status of the function.
 * Description: start a task to be served by TMU.
 *
 */
extern TMUError_t TMU_Start_Timer(const TMU_SW_Timer * SW_Timer);
/**
 * Input: Pointer to a structure contains the information needed to stop the task.
 *		  In/Out: Task ID			0 -> 9
 *		  Task Delay	    up to 65536
 *		  Delay type : periodic / oneshoot
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: stop a task to be served by TMU.
 *
 */
extern TMUError_t TMU_Stop_Timer(const TMU_SW_Timer * SW_Timer);
/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Control the Tasks.
 *
 */
extern TMUError_t TMU_Dispatch(void);



#endif /* TMU_H_ */
