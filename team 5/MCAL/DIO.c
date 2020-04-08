/*
* gpio.c
*
* Created: 1/17/2020 2:26:19 PM
*  Author: MENA
*/
#include "DIO.h"
#include "std_types.h"

/*
*Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
*Output: No output
*In/Out:
*Description: This function can set the direction of a full port, a nibble
* 			  or even one pin.
*/

ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info){
	
	 uint8_t a_u8_error_state = E_OK ;
	 
	 if (DIO_info->dir == HIGH )
	{
		switch(DIO_info->GPIO){
			
			case GPIOA :
			
			PORTA_DIR = PORTA_DIR | DIO_info->pins ;
			break;
			
			case GPIOB :
			
			PORTB_DIR = PORTB_DIR | DIO_info->pins ;
			break;
			
			case GPIOC :
			
			PORTC_DIR = PORTC_DIR | DIO_info->pins ;
			break;

			case GPIOD :
			
			PORTD_DIR = PORTD_DIR | DIO_info->pins ;
			break;
			
			default :
			a_u8_error_state |= E_NOK ;
		}
		
	} else if (DIO_info->dir == LOW)
	{
		switch(DIO_info->GPIO){
		PORTA_DIR = PORTA_DIR & ~(DIO_info->pins) ;
		break;
		
		case GPIOB :
		
		PORTB_DIR = PORTB_DIR & ~(DIO_info->pins) ;
		break;
		
		case GPIOC :
		
		PORTC_DIR = PORTC_DIR & ~(DIO_info->pins) ;
		break;

		case GPIOD :
		
		PORTD_DIR = PORTD_DIR & ~(DIO_info->pins) ;
		break;	
		
		default :
		a_u8_error_state |= E_NOK ;	
			
		}
		
	}else
		a_u8_error_state |= E_NOK;
	
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
	
	if (value == HIGH ){
		switch(GPIO)
		{
			case GPIOA :
			
			PORTA_DATA  |=  pins ;
			break;
			
			case GPIOB :
			PORTB_DATA |=  (PORTB_DATA  & ~(pins) )| (value& pins) ;
			 
			 //PORTB_DATA =value;
			break;
			
			case GPIOC :
			
			PORTC_DATA |= pins ;
			break;

			case GPIOD :
			
			PORTD_DATA |=  pins ;
			break;
			
			 default :
			a_u8_error_state |= E_NOK ;

		}
		}else if(value == LOW) {
			
		switch(GPIO){	
		
		case GPIOA :
		
		PORTA_DATA &= ~(pins) ;
		break;
		
		case GPIOB :
		
		PORTB_DATA &=  ~(pins) ;
		break;
		
		case GPIOC :
		
		PORTC_DATA &= ~(pins) ;
		break;

		case GPIOD :
		
		PORTD_DATA &= ~(pins) ;
		break;
		
		 default :
		a_u8_error_state |= E_NOK ;
		
			} 
		}else 
		a_u8_error_state |= E_NOK ;
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
	
	if (data == NULL) 
	 a_u8_error_state |= E_NOK;  
	
	switch(GPIO)
	{
		case GPIOA : 
			*data = PORTA_PIN &  (pins) ;
			break;
		case GPIOB : 
			*data = (PORTB_PIN &  (pins)) ;
			break;
		case GPIOC : 
			*data = PORTC_PIN &  (pins) ;
			break;
		case GPIOD : 
			*data = PORTD_PIN &  (pins) ;
			break;
		 default:
			a_u8_error_state |= E_NOK ;
	}
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
	
	switch(GPIO)
	{
		case GPIOA : PORTA_DATA ^= (pins) ;
		break;
		case GPIOB : PORTB_DATA ^= (pins) ;
		break;
		case GPIOC : PORTC_DATA ^= (pins) ;
		break;
		case GPIOD : PORTD_DATA ^= (pins) ;
		break;
		 default :
		a_u8_error_state |= E_NOK ;
	}
	
	return a_u8_error_state ;
}


