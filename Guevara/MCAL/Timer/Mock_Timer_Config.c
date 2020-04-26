/*
 * Timers_Config.c
 *
 * Created: 14/02/2020 04:58:23 ص
 *  Author: mo
 */
/*INCLUDES**/
#include "Mock_Timer_Config.h"

Timer_cfg_s Timer_Configuration2 =
{
		TIMER_CH2,
		TIMER_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_1024,/*it will not start untill we call timer start function*/
};
Timer_cfg_s Timer_Configuration0  =
{ 
		TIMER_CH0,
		TIMER_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_64,/*it will not start untill we call timer start function*/
};
Timer_cfg_s Timer_Deinit_Configuration0  =
{
		TIMER_CH0,
		TIMER_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_NO_CLOCK,/*it will not start untill we call timer start function*/
};
Timer_cfg_s testcase2 =
{
		TIMER_CH2,
		TIMER_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_1024,/*it will not start untill we call timer start function*/
};
Timer_cfg_s testcase3 =
{
		TIMER_CH2,
		TIMER_MODE,
		TIMER_POLLING_MODE,
		TIMER_PRESCALER_256,/*it will not start untill we call timer start function*/
};

Timer_cfg_s testcase4 =
{
		TIMER_CH2,
		COUNTER_RISING_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_128,/*it will not start untill we call timer start function*/
};
Timer_cfg_s testcase5 =
{
		TIMER_CH2,
		COUNTER_FALLING_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_64,/*it will not start untill we call timer start function*/
};
Timer_cfg_s testcase6 =
{
		TIMER_CH2,
		TIMER_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_32,/*it will not start untill we call timer start function*/
};
Timer_cfg_s testcase7 =
{
		TIMER_CH2,
		TIMER_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_8,/*it will not start untill we call timer start function*/
};
Timer_cfg_s testcase8 =
{
		TIMER_CH0,
		TIMER_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_1024,/*it will not start untill we call timer start function*/
};
Timer_cfg_s testcase9 =
{
		TIMER_CH0,
		TIMER_MODE,
		TIMER_POLLING_MODE,
		TIMER_PRESCALER_256,/*it will not start untill we call timer start function*/
};
/**/
Timer_cfg_s testcase10 =
{
		TIMER_CH0,
		COUNTER_RISING_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_128,/*it will not start untill we call timer start function*/
};
Timer_cfg_s testcase11 =
{
		TIMER_CH0,
		COUNTER_FALLING_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_64,/*it will not start untill we call timer start function*/
};
Timer_cfg_s testcase12 =
{
		TIMER_CH0,
		TIMER_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_8,/*it will not start untill we call timer start function*/
};

Timer_cfg_s testcase13 =
{
		TIMER_CH1,
		TIMER_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_1024,/*it will not start untill we call timer start function*/
};
Timer_cfg_s testcase14 =
{
		TIMER_CH1,
		TIMER_MODE,
		TIMER_POLLING_MODE,
		TIMER_PRESCALER_256,/*it will not start untill we call timer start function*/
};
/**/
Timer_cfg_s testcase15 =
{
		TIMER_CH1,
		COUNTER_RISING_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_128,/*it will not start untill we call timer start function*/
};
Timer_cfg_s testcase16 =
{
		TIMER_CH1,
		COUNTER_FALLING_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_64,/*it will not start untill we call timer start function*/
};
Timer_cfg_s testcase17 =
{
		TIMER_CH1,
		TIMER_MODE,
		TIMER_INTERRUPT_MODE,
		TIMER_PRESCALER_8,/*it will not start untill we call timer start function*/
};