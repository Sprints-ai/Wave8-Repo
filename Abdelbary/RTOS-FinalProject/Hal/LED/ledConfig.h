/*
 * ledConfig.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef LEDCONFIG_H_
#define LEDCONFIG_H_

#include "../../Mcal/DIO/gpio.h"
#include "../../Utilities/common_macros.h"
#include "../../Utilities/std_types.h"
/*
 * This macro define the maximum used leds
 */
#define LED_MAX_NUM	(4)

/*
 * LED_x_GPIO and LED_x_BIT
 * where x is the led identifier
 */
#define LED_0_GPIO	(GPIOB)
#define LED_0_BIT	(BIT4)

#define LED_1_GPIO	(GPIOB)
#define LED_1_BIT	(BIT5)

#define LED_2_GPIO	(GPIOB)
#define LED_2_BIT	(BIT6)

#define LED_3_GPIO	(GPIOB)
#define LED_3_BIT	(BIT7)


#endif /* LEDCONFIG_H_ */