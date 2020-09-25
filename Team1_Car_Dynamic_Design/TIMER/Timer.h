/*
 * Timer.h
 *
 *  Created on: 17 Feb, 2020
 *      Author: Ahmed Ashraf
 */

#ifndef __TIMER_H__
#define __TIMER_H__

/************************************************************************/
/*				General DEFINES			      							*/
/************************************************************************/

#define		TIMER_CH0						(0)
#define		TIMER_CH1						(1)
#define		TIMER_CH2						(2)

#define		TIMER_CH0_MAX_VAL				(255)
#define		TIMER_CH1_MAX_VAL				(65535)
#define		TIMER_CH2_MAX_VAL				(255)

#define		TIMER_MODE						(0)
#define		COUNTER_RISING_MODE				(1)
#define		COUNTER_FALLING_MODE			(2)

#define		TIMER_POLLING_MODE				(0)
#define		TIMER_INTERRUPT_MODE			(1)

#define     TIMER_CNT_CLK_STOP              (0xF8)
#define		TIMER_NO_CLOCK					(0)
#define		TIMER_PRESCALER_NO				(1)
#define		TIMER_PRESCALER_8				(2)
#define		TIMER_PRESCALER_32				(3)
#define		TIMER_PRESCALER_64				(4)
#define		TIMER_PRESCALER_128				(5)
#define		TIMER_PRESCALER_256				(6)
#define		TIMER_PRESCALER_1024			(7)

#define 	E_OK			                (1)
#define		E_NOK			                (-1)

#define		TIMER_FLAG_RAISED				(1)
#define		TIMER_FLAH_NOT_RAISED			(0)

/************************************************************************/
/*		         Timer user defined data types		        			*/
/************************************************************************/

typedef sint8_t		ERROR_STATUS;
typedef uint8_t		bool;

/************************************************************************/
/*		         TIMER FUNCTIONS' PROTOTYPES		        			*/
/************************************************************************/

/**
 * Input:
 *	Timer_CH_NO: The channel number of the timer needed to be started.
 *	Timer_mode:	The mode used to run the timer on.
 *	Timer_prescaler: The prescaler of timer clock.
 *	TImer_INT_mode: Chossing polling or interrupt mode.
 * Output: N/A
 * In/Out: N/A			
 * Return: The error status of the function.			
 * Description: Initializes the timer module.
 * 							
 */
ERROR_STATUS Timer_Init(uint8_t Timer_CH_NO, uint8_t Timer_mode, uint8_t Timer_prescaler, uint8_t Timer_INT_mode);

/**
 * Input:  N/A
 * Output: N/A
 * In/Out: N/A			
 * Return: The error status of the function.			
 * Description: De-Initializes the timer module.
 * 							
 */
ERROR_STATUS Timer_DeInit(void);

/**
 * Input: 
 *	Timer_CH_NO: The channel number of the timer needed to be started.
 *	Timer_Count: The start value of the timer.
 * Output: N/A
 * In/Out: N/A		
 * Return: The error status of the function.			
 * Description: This function strats the needed timer.
 * 							
 */
ERROR_STATUS Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count);

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to be stopped.
 * Output: N/A
 * In/Out: N/A			
 * Return: The error status of the function.			
 * Description: This function stops the needed timer.
 * 							
 */
ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO);

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to get its status.
 * Output:
 * 	Data: A variable of type bool returns if the flag of the timer is raised or not.
 * In/Out: N/A			
 * Return: The error status of the function.			
 * Description: This function is used to return if the flag of the timer is raised or not.
 * 							
 */
ERROR_STATUS Timer_GetStatus(uint8_t Timer_CH_NO, bool* Data);

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 	Data: This is the output variable of the function which holds the value of the timer.
 * In/Out: N/A			
 * Return: The error status of the function.			
 * Description: This function is used to return the value of the timer.
 * 							
 */
ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO, uint16_t* Data);

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to set its value.
 *  Data: This is the input variable of the function which sets the value of the timer.
 * Output: N/A
 * In/Out: N/A			
 * Return: The error status of the function.			
 * Description: This function is used to set a value to the timer.
 * 							
 */
ERROR_STATUS Timer_SetValue(uint8_t Timer_CH_NO, uint16_t Data);	


#endif /* __TIMER_H__ */