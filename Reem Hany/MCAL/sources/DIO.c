/*
 * DIO.c
 *
 * Created: 2/16/2020 4:22:20 PM
 *  Author: Reem
 */ 
#include "../includes/DIO.h"
/*
*Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
*Output: No output
*In/Out:
*Description: This function can set the direction of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info){
	//check whether the pointer is NULL
	if(DIO_info == NULL){
		return E_NULL_PTR;
	}
	else{
		switch(DIO_info->GPIO){
			// Set the direction of the given pins with the given direction (INPUT or OUTPUT) in GPIOA
			case GPIOA:
			//Direction OUTPUT
			if(DIO_info->dir == OUTPUT){
				SET_BIT_MASK(PORTA_DIR,DIO_info->pins);
			}
			//Direction INPUT
			else if(DIO_info->dir == INPUT){
				CLR_BIT_MASK(PORTA_DIR,DIO_info->pins);
			}
			//Invalid direction
			else{
				return E_INVALID_PARAMETER;
			}
			break;
			
			// Set the direction of the given pins with the given direction (INPUT or OUTPUT) in GPIOB
			case GPIOB:
			//Direction OUTPUT
			if(DIO_info->dir == OUTPUT){
				SET_BIT_MASK(PORTB_DIR,DIO_info->pins);
			}
			//Direction INPUT
			else if(DIO_info->dir == INPUT){
				CLR_BIT_MASK(PORTB_DIR,DIO_info->pins);
			}
			//Invalid direction
			else{
				return E_INVALID_PARAMETER;
			}
			break;
			
			// Set the direction of the given pins with the given direction (INPUT or OUTPUT) in GPIOC
			case GPIOC:
			//Direction OUTPUT
			if(DIO_info->dir == OUTPUT){
				SET_BIT_MASK(PORTC_DIR,DIO_info->pins);
			}
			//Direction INPUT
			else if(DIO_info->dir == INPUT){
				CLR_BIT_MASK(PORTC_DIR,DIO_info->pins);
			}
			//Invalid direction
			else{
				return E_INVALID_PARAMETER;
			}
			break;
			
			// Set the direction of the given pins with the given direction (INPUT or OUTPUT) in GPIOD
			case GPIOD:
			//Direction OUTPUT
			if(DIO_info->dir == OUTPUT){
				SET_BIT_MASK(PORTD_DIR,DIO_info->pins);
			}
			//Direction INPUT
			else if(DIO_info->dir == INPUT){
				CLR_BIT_MASK(PORTD_DIR,DIO_info->pins);
			}
			//Invalid direction
			else{
				return E_INVALID_PARAMETER;
			}
			break;
			//Invalid GPIO PORT
			default:
			return E_INVALID_PARAMETER;
			break;
		}
		return E_OK;
	}
	
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
	switch(GPIO){
		// Set the VALUE of the given pins with the given value (HIGH or LOW) in GPIOA
		case GPIOA:
		//Value High
		if(value == HIGH){
			SET_BIT_MASK(PORTA_DATA,pins);
		}
		//Value Low
		else if(value == LOW){
			CLR_BIT_MASK(PORTA_DATA,pins);
		}
		//Invalid value
		else{
			return E_INVALID_PARAMETER;
		}
		break;
		
		// Set the VALUE of the given pins with the given value (HIGH or LOW) in GPIOB
		case GPIOB:
		//Value High
		if(value == HIGH){
			SET_BIT_MASK(PORTB_DATA,pins);
		}
		//Value Low
		else if(value == LOW){
			CLR_BIT_MASK(PORTB_DATA,pins);
		}
		else{
			return E_INVALID_PARAMETER;
		}
		
		break;
		// Set the VALUE of the given pins with the given value (HIGH or LOW) in GPIOC
		case GPIOC:
		//Value High
		if(value == HIGH){
			SET_BIT_MASK(PORTC_DATA,pins);
		}
		//Value Low
		else if(value == LOW){
			CLR_BIT_MASK(PORTC_DATA,pins);
		}
		else{
			return E_INVALID_PARAMETER;
		}
		
		break;
		// Set the VALUE of the given pins with the given value (HIGH or LOW) in GPIOD
		case GPIOD:
		//Value High
		if(value == HIGH){
			SET_BIT_MASK(PORTD_DATA,pins);
		}
		//Value Low
		else if(value == LOW){
			CLR_BIT_MASK(PORTD_DATA,pins);
		}
		else{
			return E_INVALID_PARAMETER;
		}
		
		break;
		
		default:
		 return E_INVALID_PARAMETER;
		break;
	}
	return E_OK;
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
	if (data == NULL)
	{
		return E_NULL_PTR;
	}
	else{
		switch(GPIO){
			//reading the pin in portA
			case GPIOA:
			(*data) =GET_BIT(PORTA_PIN,pins);		
			break;
			
			//reading the pin in portB
			case GPIOB:
			(*data) =GET_BIT(PORTB_PIN,pins);
			break;
			
			//reading the pin in portC
			case GPIOC:
			(*data) =GET_BIT(PORTC_PIN,pins);	
			break;
			
			//reading the pin in portD
			case GPIOD:
			(*data) =GET_BIT(PORTD_PIN,pins);
			break;
			
			//Invalid GPIO Port
			default:
				return E_INVALID_PARAMETER;
			break;
		}
		
		return E_OK;
	}
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
	switch(GPIO){
		//toggle pins in port A
		case GPIOA:
		TOGGLE_BIT_MASK(PORTA_DATA,pins);
		break;
		
		//toggle pins in port B
		case GPIOB:
		TOGGLE_BIT_MASK(PORTB_DATA,pins);
		break;
		
		//toggle pins in port C
		case GPIOC:
		TOGGLE_BIT_MASK(PORTC_DATA,pins);
		break;
		
		//toggle pins in port D
		case GPIOD:
		TOGGLE_BIT_MASK(PORTD_DATA,pins);
		break;
		
		//Invalid port returning error
		default:
		return E_INVALID_PARAMETER;
		break;
	}
	return E_OK;
}