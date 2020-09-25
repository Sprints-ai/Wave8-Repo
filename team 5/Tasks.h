/*
 * Tasks.h
 *
 * Created: 3/30/2020 1:13:40 AM
 *  Author: A_ayman
 */ 


#ifndef TASKS_H_
#define TASKS_H_

#include "APP/car_sm.h"
#include "ECUAL/Us.h"
#include "ECUAL/LCD.h"

extern volatile uint16_t gu8_Distance;
extern uint8_t gu8_System_Init_Flag;

extern void System_Init_Task ();



#endif /* TASKS_H_ */