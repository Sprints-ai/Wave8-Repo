/*
 * Timer.h
 *
 *  Created on: Dec 21, 2019
 *      Author: Zayed & Saad
 */

#ifndef TIMER_H_
#define TIMER_H_

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/
#include "..\Common\common_macros.h"
#include "..\Common\std_types.h"
#include "..\Mcal\registers.h"
#include "..\Mcal\interrupt.h"

/************************************************************************/
/*				 DEFINES			        */
/************************************************************************/


#define		TIMER_0					0
#define		TIMER_1					1
#define		TIMER_2					2

#define  Rasied 0
#define  not_rasied 1


#define		TIMER_MODE					        0
#define		COUNTER_RISING_MODE					1
#define		COUNTER_FALLING_MODE				2

#define		TIMER_POLLING_MODE				0
#define		TIMER_INTERRUPT_MODE			1

#define		TIMER_NO_CLOCK					0
#define		TIMER_PRESCALER_NO				1
#define		TIMER_PRESCALER_8				2
#define		TIMER_PRESCALER_32				3
#define		TIMER_PRESCALER_64				4
#define		TIMER_PRESCALER_128				5
#define		TIMER_PRESCALER_256				6
#define		TIMER_PRESCALER_1024			7
typedef void(*timer_Cbk)(void);
extern uint32_t gu_timer_count1;
extern uint32_t gu_timer_count2;
extern uint32_t gu_timer_count3;



/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/

typedef struct Timer_cfg_s
{
	uint8_t Timer_CH;
	uint8_t Timer_Mode;
	uint8_t Timer_Int_MODE;
	uint8_t Timer_Prescaler;
}Timer_cfg_s;



/************************************************************************/
/*		         TIMER FUNCTIONS' PROTOTYPES		        */
/************************************************************************/


/**
 * Input: Pointer to a structure contains the information needed to initialize the timer. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */
ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg);

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
ERROR_STATUS Timer_Start(uint8_t Timer_CH, uint16_t Timer_Count);

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to be stopped.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function stops the needed timer.
 * 							
 */
ERROR_STATUS Timer_Stop(uint8_t Timer_CH);



/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to get its status.
 * Output:
 * 	Data: 
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to return if the flag of the timer is raised or not.
 * 							
 */
extern ERROR_STATUS Timer_SetValue(uint8_t Timer_CH, uint8_t* Data);
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
ERROR_STATUS Timer_GetStatus(uint8_t Timer_CH, uint8_t* Data);

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
ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO,volatile uint16_t* Data);




ERROR_STATUS Timer_Setcallback(timer_Cbk pf);




#endif /* TIMER_H_ */