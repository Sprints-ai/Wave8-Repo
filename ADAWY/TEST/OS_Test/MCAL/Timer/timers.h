/*
 * timers.h
 *
 *  Created on: Oct 22, 2019
 *      Author: Sprints
 */

#ifndef TIMERS_H_
#define TIMERS_H_


#include "../../SERVICE/std_types.h"
#include "../../SERVICE/Common_Macros.h"


#define  Timer_0      0
#define  Timer_1      1
#define  Timer_2      2

#define  COUNTER_MODE 0
#define  TIMER_MODE   1

#define  TIMER_MODE_POLLING   0
#define  TIMER_MODE_INTERRUPT 1

 #define  PRESCALER_1          1
 #define  PRESCALER_8          2
 #define  PRESCALER_32         3
 #define  PRESCALER_64         4
 #define  PRESCALER_128        5
 #define  PRESCALER_256        6
 #define  PRESCALER_1024       7

typedef struct Timer_Cfg_ST{
   uint8_t Timer_Ch;
	uint8_t Timer_Mode;
	uint8_t Timer_PreScaler;
	uint8_t Timer_Interrupt_Mode;
   void(* Ptr_TCB_Function)(void);

}Timer_Cfg_ST;





/**
 * Input: Pointer to a structure contains the information needed to initialize the timer.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Initiates the module.
 *
 */
extern uint8_t Timer_Init (Timer_Cfg_ST *Timer_Info);

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to be started.
 *	Timer_Count: The start value of the timer.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function strats the needed timer.
 *
 */
extern uint8_t Timer_Start (uint8_t Timer_Chan, uint16_t Timer_Count_No);

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to be stopped.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function stops the needed timer.
 *
 */
extern uint8_t Timer_Stop (uint8_t Timer_Chan);

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 	Data: This is the output variable of the function which holds the value of the timer.
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to return the value of the timer.
 *
 */
extern uint8_t Timer_Get_Value (uint8_t Timer_Chan, uint16_t *Timer_Value);

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 	Data: This is the output variable of the function which holds the value of the timer.
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to set the value of the timer.
 *
 */
extern uint8_t Timer_Set_Value (uint8_t Timer_Chan, uint16_t Timer_Value);

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its status.
 * Output:
 * 	Data: A variable of type bool returns if the flag of the timer is raised or not.
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to return if the flag of the timer is raised or not.
 *
 */
extern uint8_t Timer_Get_Status (uint8_t Timer_Chan, uint8_t *Timer_Status);

#endif /* TIMERS_H_ */
