/*
 * NVIC_lcfg.h
 *
 * Created: 4/3/2020 10:50:40 AM
 *  Author: Khaled
 */ 


#ifndef NVIC_LCFG_H_
#define NVIC_LCFG_H_

#include "NVIC_Types.h"

#define NUM_OF_ACTIVATED_INTERRUPTS			3

extern NVIC_CfgType NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS];
#endif /* NVIC_LCFG_H_ */
