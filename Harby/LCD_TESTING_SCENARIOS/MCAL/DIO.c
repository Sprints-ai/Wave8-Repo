

/*
* gpio.c
*
* Created: 1/17/2020 2:26:19 PM
*  Author: MENA
*/
#include "DIO.h"
#include "../std_types.h"

/*
*Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
*Output: No output
*In/Out:
*Description: This function can set the direction of a full port, a nibble
* 			  or even one pin.
*/

ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info){

	 uint8_t a_u8_error_state = E_OK ;

	return a_u8_error_state  ;



}



/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: No output
*In/Out: No In/Out
*Description: This function can set the value of a full port, a nibble
* 			  or even one pin.
*/

ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value){

	uint8_t a_u8_error_state = E_OK ;


	return a_u8_error_state  ;
}

ERROR_STATUS DIO_WriteValue (uint8_t GPIO, uint8_t pins, uint8_t value){

	uint8_t a_u8_error_state = E_OK ;


	return a_u8_error_state  ;
}



/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: data -> the acquired data wether it was PORT data or pins data
*In/Out:
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
*/


ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data){
	uint8_t a_u8_error_state = E_OK ;


	return a_u8_error_state  ;

}


/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a full port, a nibble
* 			  or even one pin.
*/


ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins){

	uint8_t a_u8_error_state = E_OK ;


	return a_u8_error_state ;
}


