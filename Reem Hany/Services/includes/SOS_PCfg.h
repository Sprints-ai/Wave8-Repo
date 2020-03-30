/*
 * SOS_PCfg.h
 *
 * Created: 3/10/2020 11:11:43 PM
 *  Author: Reem
 */ 


#ifndef SOS_PCFG_H_
#define SOS_PCFG_H_

#include "std_types.h"

//SOS Channels
#define		SOS_TIMER_CH0					0
#define		SOS_TIMER_CH1					1
#define		SOS_TIMER_CH2					2

//SOS Resolution
#define SOS_RESOLUTION_1M                   250
#define SOS_RESOLUTION_12M                  188
#define SOS_RES_PRESCALE_1M                 TIMER_PRESCALER_64
#define SOS_RES_PRESCALE_12M                TIMER_PRESCALER_1024

#define SOS_RESOLUTION                      SOS_RESOLUTION_12M
#define SOS_RES_PRESCALE                    SOS_RES_PRESCALE_12M
#define SOS_RES_TICK                        12


typedef struct strSOS_Cfg_t{
	uint8_t TIM_Ch;
	uint8_t Resolutions;
}strSOS_Cfg_t;


extern strSOS_Cfg_t SOS_cfg;



#endif /* SOS_PCFG_H_ */