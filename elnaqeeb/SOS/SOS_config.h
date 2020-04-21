/*
 * TMU_config.h
 *
 * Created: 2/24/2020 4:47:09 PM
 *  Author: ahmed
 */ 


#ifndef __TMU_CONFIG_H__
#define __TMU_CONFIG_H__

/************************************************************************/
/*                  Macros controlling tasks of the TMU                 */
/************************************************************************/

/*Tasks number in TMU  list*/
#define TASKS_NUMBER		(2)

/*If you're using one shot task satisfy its start period here*/
#define ONE_SHOT_PERIOD		(20)

/*System tick time*/
#define SYSTEM_TICK_MS		(100)

/*
 * You only have three options:
 * Timer_Channel0 with maximum system tick of 1ms
 * Timer_Channel1 with maximum system tick of 262ms
 * Timer_Channel2 with maximum system tick of 1ms
 */
#define TMU_SYSTEM_TIMER	(TMU_TIM_CH1)

/*Macro passed to the configuration struct of the TMU*/
#define TMU_CONFIG_DATA		{ TMU_SYSTEM_TIMER,\
							  SYSTEM_TICK_MS }

#endif /* TMU_CONFIG_H_ */