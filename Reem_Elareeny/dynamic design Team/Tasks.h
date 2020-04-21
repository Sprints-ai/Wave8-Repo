/*
 * Tasks.h
 *
 * Created: 3/30/2020 4:13:40 PM
 *  Author: Ehab , Ramadan , Reem , Eman
 */ 


#ifndef TASKS_H_
#define TASKS_H_

#include "car_sm.h"
#include "../Services/Displayer.h"
#include "../Services/DistanceReader.h"

extern void CAR_Init_Task(void);
extern void DistanceReaderTask(void);
extern void CarControlTask(void);
extern void DisplayerTask(void);





#endif /* TASKS_H_ */