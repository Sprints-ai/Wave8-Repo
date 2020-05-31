/*
 * SYSCTR_LCFG.h
 *
 * Created: 4/6/2020 8:19:07 PM
 *  Author: Khaled
 */ 


#ifndef SYSCTR_LCFG_H_
#define SYSCTR_LCFG_H_

#include "stdint.h"


#define NUMBER_OF_PERIPHERALS                   5

typedef struct
{
	uint16_t Peripheral;
	uint8_t  Channel;
}SYSCL_Type;


extern SYSCL_Type garrstr_SYSCTR_Cfg[NUMBER_OF_PERIPHERALS];



#endif /* SYSCTR_LCFG_H_ */
