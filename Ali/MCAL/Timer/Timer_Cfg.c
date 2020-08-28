/*
 * Timer_Cfg.c
 *
 * Created: 2/17/2020 10:46:08 AM
 *  Author: Az
 */ 

/*- INCLUDES ----------------------------------------------------------------------------------------------------------------------------------------*/
#include "Timer.h"
/*- GLOBAL VARIABLES -------------------------------------------------------------------------------------------------------------------------------*/

/* configuring (timer 2) to be used as a counter within SwICU */
strTimerConfig_t gstrTimerConfig = 
{
   TIMER_2,
   T2_NORMAL_MODE,
   T2_OC2_CLEAR,
   T2_PRESCALER_1024,      
   //0,
   //0,
   //0,
   T2_INTERRUPT_NORMAL   
};

/*--------------------------------------- TMU Configuration ------------------------------------------*/
/* configuring (timer 0) to be used to serve TMU unit */
strTimerConfig_t gstrTimer0TmuConfig =
{
   TIMER_0,
   T0_NORMAL_MODE,
   T0_OC0_CLEAR,
   T0_PRESCALER_1024,   
   T0_INTERRUPT_NORMAL
};

/* configuring (timer 1) to be used to serve TMU unit */
strTimerConfig_t gstrTimer1TmuConfig =
{
   TIMER_1,
   T1_NORMAL_MODE,
   T1_OC1B_CLEAR,
   T1_PRESCALER_1024,   
   T1_INTERRUPT_NORMAL
};

/* configuring (timer 2) to be used to serve TMU unit */
strTimerConfig_t gstrTimer2TmuConfig =
{
   TIMER_2,
   T2_NORMAL_MODE,
   T2_OC2_CLEAR,
   T2_PRESCALER_1024,  
   T2_INTERRUPT_NORMAL
};

/*--------------------------------------- SOS Configuration ------------------------------------------*/
/* configuring (timer 0) to be used to serve SOS */
strTimerConfig_t gstrTimer0SosConfig =
{
   TIMER_0,
   T0_NORMAL_MODE,
   T0_OC0_CLEAR,
   T0_PRESCALER_1024,
   T0_INTERRUPT_NORMAL
};

/* configuring (timer 1) to be used to serve SOS */
strTimerConfig_t gstrTimer1SosConfig =
{
   TIMER_1,
   T1_NORMAL_MODE,
   T1_OC1B_CLEAR,
   T1_PRESCALER_1024,
   T1_INTERRUPT_NORMAL
};

/* configuring (timer 2) to be used to serve SOS */
strTimerConfig_t gstrTimer2SosConfig =
{
   TIMER_2,
   T2_NORMAL_MODE,
   T2_OC2_CLEAR,
   T2_PRESCALER_1024,
   T2_INTERRUPT_NORMAL
};




