/*
 * pushButtonConfig.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef PUSHBUTTONCONFIG_H_
#define PUSHBUTTONCONFIG_H_

#include "../../Mcal/DIO/gpio.h"


#define BTN_MAX_NUM		(2)


#define BTN_0_GPIO	GPIOD
#define BTN_0_BIT	BIT6

#define BTN_1_GPIO	GPIOD
#define BTN_1_BIT	BIT7
#define PB_MODULE_ERR	-500

#endif /* PUSHBUTTONCONFIG_H_ */