/*
 * SOS_config.h
 *
 * Created: 2/24/2020 4:47:09 PM
 *  Author: Ahmed
 */ 

#ifndef __SOS_CONFIG_H__
#define __SOS_CONFIG_H__

/*
 * SOS is a small operating system designed based on time triggering event so when event comes, Tasks
 * are executed according to their priorities.
 */

/************************************************************************/
/*                  Macros controlling tasks of the SOS                 */
/************************************************************************/

/*Tasks number in TMU  list*/
#define TASKS_NUMBER		(1)

/*If you're using one shot task satisfy its start period here*/
#define ONE_SHOT_PERIOD		(20)

/*System tick time*/
#define SYSTEM_TICK_MS		(10)

/*
 * You only have three options:
 * Timer_Channel0 with maximum system tick of 16.35ms
 * Timer_Channel1 with maximum system tick of 4194.24ms
 * Timer_Channel2 with maximum system tick of 16.35ms
 */
#define SOS_SYSTEM_TIMER	(SOS_TIM_CH0)

/*Macro passed to the configuration struct of the TMU*/
#define SOS_CONFIG_DATA		{ SOS_SYSTEM_TIMER , SYSTEM_TICK_MS }

#endif /* SOS_CONFIG_H_ */