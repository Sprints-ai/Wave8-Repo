/*
 * led.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef LED_H_
#define LED_H_

#include "../MCAL/gpio.h"
#include "../Infrastructure/std_types.h"
#include "ledConfig.h"


#define		LED_0		0
#define     LED_1		1
#define     LED_2		2
#define     LED_3		3

/**
 * Description: Initialize the LED_x (where x 0, 1, 2, 3) as output
 * @param led_id: The led to be initialized and it takes
 * 				  one of the Following parameters :
 *												- LED_0
 *												- LED_1
 *												- LED_2
 *												- LED_3
 *	@return Function's Error Status
 */
extern ERROR_STATUS Led_Init(uint8_t u8_led_id);


/**
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be on
 * @param led_id: The led to be initialized and it takes
 * 				  one of the Following parameters :
 *												- LED_0
 *												- LED_1
 *												- LED_2
 *												- LED_3
 * @return Function's Error Status
 */
extern ERROR_STATUS Led_On(uint8_t u8_led_id);


/**
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be off
 * @param led_id: The led to be initialized and it takes
 * 				  one of the Following parameters :
 *												- LED_0
 *												- LED_1
 *												- LED_2
 *												- LED_3
 * @return Function's Error Status
 */
extern ERROR_STATUS Led_Off(uint8_t u8_led_id);


/**
 * Description: Toggle the LED_x state (where x 0, 1, 2, 3)
 * @param led_id: The led to be initialized and it takes
 * 				  one of the Following parameters :
 *												- LED_0
 *												- LED_1
 *												- LED_2
 *												- LED_3
 * @return Function's Error Status
 */
extern ERROR_STATUS Led_Toggle(uint8_t u8_led_id);



#endif /* LED_H_ */