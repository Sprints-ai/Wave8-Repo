/*
 * APP.h
 *
 * Created: 3/15/2020 2:25:24 PM
 *  Author: A_ayman
 */ 


#ifndef APP_H_
#define APP_H_

#include "../SL/Utilis/interrupts.h"
extern void Task_1m();
extern void Task_25m ();

extern void Question2_Display ();



#define BTN_0_GPIO	  GPIOD//GPIOC //correct answer
#define BTN_0_BIT    BIT0///	BIT4

#define BTN_1_GPIO	GPIOD//GPIOB
#define BTN_1_BIT	   BIT1//BIT2
#endif /* APP_H_ */