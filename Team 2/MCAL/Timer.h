#ifndef TIMERS_H_
#define TIMERS_H_


/*********************************includes**********************************/
#include "registers.h"
#include "../Common/common_macros.h"
#include "../Common/std_types.h"
#include "interrupt.h"
/***************************************************************************/


/*******************definitions, macros, ENUMs & types*******************/
#define cpu_frq 16000000
#define TIMER0_NUMBER_OF_TICKS 256
#define TIMER2_NUMBER_OF_TICKS 256
#define TIMER1_NUMBER_OF_TICKS_10_BITS 1024
#ifndef SEC
#define SEC 1000
#endif



#define		TIMER_CH0					0
#define		TIMER_CH1					1
#define		TIMER_CH2					2


#define		TIMER_MODE					0
#define		COUNTER_RISING_MODE		    1
#define		COUNTER_FALLING_MODE		2


#define T0_NORMAL_MODE 0
#define T0_COMP_MODE 0x08
#define T0_PHASECORRECT_MODE 0X40
#define T0_FAST_MODE 0x48


#define T1_NORMAL_MODE 0x0000
#define T1_COMP_MODE_OCR1A_TOP 0x0008
#define T1_COMP_MODE_ICR1_TOP 0x0018

#define T2_NORMAL_MODE 0
#define T2_COMP_MODE 0x08

#define T0_POLLING 0
#define T0_INTERRUPT_NORMAL 0x01
#define T0_INTERRUPT_CMP 0x02

#define T1_POLLING 0
#define T1_INTERRUPT_NORMAL 0x40
#define T1_INTERRUPT_CMP_1B 0x80
#define T1_INTERRUPT_CMP_1A 0x10
#define T1_INTERRUPT_ICAPTURE 0x20


#define T2_POLLING 0
#define T2_INTERRUPT_NORMAL 0x40
#define T2_INTERRUPT_CMP 0x80


#define T0_NO_CLOCK                     0
#define T0_PRESCALER_NO                 0x01
#define T0_PRESCALER_8                  0x02
#define T0_PRESCALER_64                 0x03
#define T0_PRESCALER_256                0x04
#define T0_PRESCALER_1024               0x05


#define T1_NO_CLOCK                     0x0000
#define T1_PRESCALER_NO                 0x0001
#define T1_PRESCALER_8                  0x0002
#define T1_PRESCALER_64                 0x0003
#define T1_PRESCALER_256                0x0004
#define T1_PRESCALER_1024               0x0005


#define T2_NO_CLOCK                     0
#define T2_PRESCALER_NO                 0x01
#define T2_PRESCALER_8                  0x02
#define T2_PRESCALER_32                 0x03
#define T2_PRESCALER_64                 0x04
#define T2_PRESCALER_128                0x05
#define T2_PRESCALER_256                0x06
#define T2_PRESCALER_1024               0x07


#define     Timer_0                     0
#define     Timer_1                     1
#define     Timer_2                     2



/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/

typedef struct St_TimerCfg
{
	uint8_t Timer_CH_NO;
	uint8_t Timer_Mode;
	uint8_t Timer_Polling_Or_Interrupt;
	uint8_t Timer_Prescaler;
	void (*Timer_Cbk_ptr)(void);
}St_TimerCfg;

/********************** User Configuration Macros***********************/
#define MS_OCR_value 250
#define US_OCR_value 16

#define T0_PWM_GPIO	GPIOD
#define T0_PWM_BIT	BIT0

#define T1_PWM_GPIO	GPIOD
#define T1_PWM_BIT	BIT1

#define T2_PWM_GPIO GPIOD
#define T2_PWM_BIT	BIT2

/***************************************************************************/


/******************************global variables*****************************/
extern uint8_t g8_TCNT0_value_Swpwm_ISR;
extern uint8_t gu8_Timer0CompFlag;
/***************************************************************************/


/*********************************functions*********************************/
/*
 * Input: Pointer to a structure contains the information needed to initialize the timer.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Initiates the module.
 *
 */
ERROR_STATUS Timer_Init(St_TimerCfg* Timer_cfg);

/*
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to be started.
 *	Timer_Count: The start value of the timer.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function strats the needed timer.
 *
 */
ERROR_STATUS Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count);

/*
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to be stopped.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function stops the needed timer.
 *
 */
ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO);

/*
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its status.
 * Output:
 * 	Data: A variable of type bool returns if the flag of the timer is raised or not.
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to return if the flag of the timer is raised or not.
 *
 */
ERROR_STATUS Timer_GetStatus(uint8_t Timer_CH_NO, bool_t* Data);

/*
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 	Data: This is the output variable of the function which holds the value of the timer.
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to return the value of the timer.
 *
 */
ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO,uint16_t* Data);



/*
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to reset the TCNTX register value.
 *
 */
ERROR_STATUS Timer_Clear(uint8_t Timer_CH_NO);



/*
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to de-initialize TIMERX.
 *
 */
ERROR_STATUS Timer_DeInit(uint8_t Timer_CH_NO);


#endif /* TIMERS_H_ */
