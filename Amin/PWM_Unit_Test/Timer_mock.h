/*
 * Timer.h
 *
 *  Created on: Dec 21, 2019
 *      Author: Amin
 */

#ifndef TIMER_mock_H_
#define TIMER_mock_H_

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "std_types.h"
#include "registers.h"
#include "common_macros.h"

/************************************************************************/
/*				 DEFINES			        */
/************************************************************************/


#define		TIMER_CH0					0
#define		TIMER_CH1					1
#define		TIMER_CH2					2

#define		TIMER_MODE					0
#define		COUNTER_RISING_MODE					1
#define		COUNTER_FALLING_MODE				2

#define		TIMER_POLLING_MODE				0
#define		TIMER_INTERRUPT_MODE			1


#define T0_POLLING 0
#define T0_INTERRUPT_NORMAL 0x01


#define T1_POLLING 0
#define  T1_INTERRUPT_CMP_1A 0x10
#define T1_COMP_MODE_OCR1A_TOP 0x0008
#define T1_INTERRUPT_ICAPTURE 0x20

#define T2_POLLING 0
#define T2_INTERRUPT_NORMAL 0x40




#define		TIMER_NO_CLOCK					0
#define		TIMER_PRESCALER_NO				1
#define		TIMER_PRESCALER_8				2
#define		TIMER_PRESCALER_32				3
#define		TIMER_PRESCALER_64				4
#define		TIMER_PRESCALER_128				5
#define		TIMER_PRESCALER_256				6
#define		TIMER_PRESCALER_1024			7

#define T0_NO_CLOCK 0
#define T0_PRESCALER_NO 0x01
#define T0_PRESCALER_8 0x02
#define T0_PRESCALER_64 0x03
#define T0_PRESCALER_256 0x04
#define T0_PRESCALER_1024 0x05

#define T1_NO_CLOCK 0x0000
#define T1_PRESCALER_NO 0x0001
#define T1_PRESCALER_8 0x0002
#define T1_PRESCALER_64 0x0003
#define T1_PRESCALER_256 0x0004
#define T1_PRESCALER_1024 0x0005

#define T2_NO_CLOCK 0
#define T2_PRESCALER_NO 0x01
#define T2_PRESCALER_8 0x02
#define T2_PRESCALER_32 0x03
#define T2_PRESCALER_64 0x04
#define T2_PRESCALER_128 0x05
#define T2_PRESCALER_256  0x06
#define T2_PRESCALER_1024 0x07



#define TOV0  0
#define TOV2  6
#define OCF1A 4

#define CS00 0
#define CS01 1
#define CS02 2

#define CS20 0
#define CS21 1
#define CS22 2

#define CS20 0
#define CS21 1
#define CS22 2

#define CS10 0
#define CS11 1
#define CS12 2


/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/

typedef struct Timer_cfg_s
{
	uint8 Timer_CH_NO;
	uint8 Timer_Mode;
	uint8 Timer_Polling_Or_Interrupt;
	uint8 Timer_Prescaler;
	void (*Timer_Cbk_ptr)(void);
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
ERROR_STATUS Timer_Start(uint8 Timer_CH_NO, uint16 Timer_Count);

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to be stopped.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function stops the needed timer.
 *
 */
ERROR_STATUS Timer_Stop(uint8 Timer_CH_NO);


ERROR_STATUS Timer_SetValue(uint8 Timer_CH_NO, uint16 Data);








#endif /* TIMER_H_ */
