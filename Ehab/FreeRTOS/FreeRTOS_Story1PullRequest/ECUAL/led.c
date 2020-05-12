/*
* led.c
*
* Created: 17/01/2020 04:40:59 م
*  Author: mo
*/
#include "led.h"
#include "ledConfig.h"
#include "../Infrastructure/Errors.h"

ERROR_STATUS Led_Init(uint8_t u8_led_id)
{
/**
 * Description: Initialize the LED_x (where x 0, 1, 2, 3) as output
 * @param led_id: The led to be initialized and it takes
 * 				  one of the Following parameters :
 *												- LED_0
 *												- LED_1
 *												- LED_2
 *												- LED_3
 * @return Function's Error Status
 */
	ERROR_STATUS ERR = E_OK;
	
	switch(u8_led_id)
	{
		case LED_0:
		gpioPinDirection(LED_0_GPIO,LED_0_BIT,OUTPUT);
		break;

		case LED_1:
		gpioPinDirection(LED_1_GPIO,LED_1_BIT,OUTPUT);
		break;

		case LED_2:
		gpioPinDirection(LED_2_GPIO,LED_2_BIT,OUTPUT);
		break;

		case LED_3:
		gpioPinDirection(LED_3_GPIO,LED_3_BIT,OUTPUT);
		break;
		
		default:
		ERR = ERROR_INVALID_PARAMETER;
		break;
	}

	return ERR;
	
}

ERROR_STATUS Led_On(uint8_t u8_led_id)
{
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

	ERROR_STATUS ERR = E_OK;
	
	switch(u8_led_id)
	{
		case LED_0:
		gpioPinWrite(LED_0_GPIO,LED_0_BIT,HIGH);
		break;

		case LED_1:
		gpioPinWrite(LED_1_GPIO,LED_1_BIT,HIGH);
		break;

		case LED_2:
		gpioPinWrite(LED_2_GPIO,LED_2_BIT,HIGH);
		break;

		case LED_3:
		gpioPinWrite(LED_3_GPIO,LED_3_BIT,HIGH);
		break;
		
		default:
		ERR = ERROR_INVALID_PARAMETER;
		break;
	}

	return ERR;
	
}

ERROR_STATUS Led_Off(uint8_t u8_led_id)
{
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

	ERROR_STATUS ERR = E_OK;
	
	switch(u8_led_id)
	{
		case LED_0:
		gpioPinWrite(LED_0_GPIO,LED_0_BIT,LOW);
		break;

		case LED_1:
		gpioPinWrite(LED_1_GPIO,LED_1_BIT,LOW);
		break;

		case LED_2:
		gpioPinWrite(LED_2_GPIO,LED_2_BIT,LOW);
		break;

		case LED_3:
		gpioPinWrite(LED_3_GPIO,LED_3_BIT,LOW);
		break;
		
		default:
		ERR = ERROR_INVALID_PARAMETER;
		break;
		
	}
	
	return ERR;
}

ERROR_STATUS Led_Toggle(uint8_t u8_led_id)
{
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
	ERROR_STATUS ERR = E_OK;
	
	switch(u8_led_id)
	{
		case LED_0:
		gpioPinToggle(LED_0_GPIO,LED_0_BIT);
		break;

		case LED_1:
		gpioPinToggle(LED_1_GPIO,LED_1_BIT);
		break;

		case LED_2:
		gpioPinToggle(LED_2_GPIO,LED_2_BIT);
		break;

		case LED_3:
		gpioPinToggle(LED_3_GPIO,LED_3_BIT);
		break;
		
		default:
		ERR = ERROR_INVALID_PARAMETER;
	}

	return ERR;
}