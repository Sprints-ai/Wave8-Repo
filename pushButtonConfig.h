/*
 * pushButtonConfig.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef PUSHBUTTONCONFIG_H_
#define PUSHBUTTONCONFIG_H_

#include "gpio.h"


#define BTN_MAX_NUM		(2)


#define BTN_0_GPIO	GPIOC
#define BTN_0_BIT	BIT4EN

#define BTN_1_GPIO	GPIOB
#define BTN_1_BIT	BIT2EN

#define BTN_2_GPIO	GPIOA
#define BTN_2_BIT	BIT2EN

#define BTN_3_GPIO 	GPIOA
#define BTN_3_BIT	BIT3EN


#endif /* PUSHBUTTONCONFIG_H_ */