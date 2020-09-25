/*
 * gpio.c
 *
 * Created: 1/17/2020 2:26:19 PM
 * Author: Joo
 */


/************************************************************************/
/*								Includes                               */
/************************************************************************/

#include "DIO.h"
#include "registers.h"


/************************************************************************/
/*							API's Implementation                        */
/************************************************************************/

ERROR_STATUS DIO_WriteValue (uint8_t GPIO, uint8_t pins, uint8_t value)
{
	sint16_t as16_state_error = E_OK ;
	/* A pointer to register in which the required register address will be stored */
	uint8_t* pau8_gpioDataPointer = NULL;

	/* A switch case to determine which Port to change its data */
	switch(GPIO)
	{
	case GPIOA:
		pau8_gpioDataPointer = (uint8_t*)(&PORTA_DATA);
		break;
	case GPIOB:
		pau8_gpioDataPointer = (uint8_t*)(&PORTB_DATA);
		break;
	case GPIOC:
		pau8_gpioDataPointer = (uint8_t*)(&PORTC_DATA);
		break;
	case GPIOD:
		pau8_gpioDataPointer = (uint8_t*)(&PORTD_DATA);
		break;
	default:
		as16_state_error = E_NOK;
		break;
	}

	if(as16_state_error == E_OK)
	{
		*pau8_gpioDataPointer = (*pau8_gpioDataPointer & ~pins) | (value & pins);
	}

	return as16_state_error;
}

/*
 *Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
 *Output: No output
 *In/Out:
 *Description: This function can set the direction of a full port, a nibble
 * 			 or even one pin.
 */
ERROR_STATUS DIO_init(DIO_Cfg_s *DIO_info)
{
	sint16_t as16_state_error = E_OK ;

	if (DIO_info->dir == HIGH)
	{
		switch(DIO_info->GPIO)
		{
		case GPIOA:
			PORTA_DIR = PORTA_DIR | DIO_info->pins;
			break;
		case GPIOB:
			PORTB_DIR = PORTB_DIR | DIO_info->pins;
			break;
		case GPIOC:
			PORTC_DIR = PORTC_DIR | DIO_info->pins;
			break;
		case GPIOD:
			PORTD_DIR = PORTD_DIR | DIO_info->pins;
			break;
		default:
			as16_state_error |= E_NOK;
		}
	}else if (DIO_info->dir == LOW)
	{
		switch(DIO_info->GPIO)
		{
		case GPIOA:
			PORTA_DIR = PORTA_DIR & ~(DIO_info->pins);
			break;
		case GPIOB:
			PORTB_DIR = PORTB_DIR & ~(DIO_info->pins);
			break;
		case GPIOC:
			PORTC_DIR = PORTC_DIR & ~(DIO_info->pins);
			break;
		case GPIOD:
			PORTD_DIR = PORTD_DIR & ~(DIO_info->pins);
			break;
		default:
			as16_state_error |= E_NOK;
		}
	}else
	{
		as16_state_error |= E_NOK;
	}

	return as16_state_error;
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
 * 			 or even one pin.
 */

ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value)
{
	sint16_t as16_state_error = E_OK ;

	if (value == HIGH )
	{
		switch(GPIO)
		{
		case GPIOA:
			PORTA_DATA |= pins;
			break;
		case GPIOB:
			PORTB_DATA |= (PORTB_DATA & ~(pins) )| (value& pins);
			break;
		case GPIOC:
			PORTC_DATA |= pins;
			break;
		case GPIOD:
			PORTD_DATA |= pins;
			break;
		default:
			as16_state_error |= E_NOK;
		}
	}else if(value == LOW)
	{
		switch(GPIO)
		{
		case GPIOA:
			PORTA_DATA &= ~(pins);
			break;
		case GPIOB:
			PORTB_DATA &= ~(pins);
			break;
		case GPIOC:
			PORTC_DATA &= ~(pins);
			break;
		case GPIOD:
			PORTD_DATA &= ~(pins);
			break;
		default:
			as16_state_error |= E_NOK;
		}
	}else
	{
		switch(GPIO)
		{
		case GPIOA:
			PORTA_DATA = (PORTA_DATA & ~(pins) )| (value& pins);
			break;
		case GPIOB:
			PORTB_DATA = (PORTB_DATA & ~(pins) )| (value& pins);
			break;
		case GPIOC:
			PORTC_DATA = (PORTC_DATA & ~(pins) )| (value& pins);
			break;
		case GPIOD:
			PORTD_DATA = (PORTD_DATA & ~(pins) )| (value& pins);
			break;
		default:
			as16_state_error |= E_NOK;
		}
	}

	return as16_state_error;
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
 * 			 or even one pin.
 */
ERROR_STATUS DIO_Read(uint8_t GPIO,uint8_t pins, uint8_t *data)
{
	sint16_t as16_state_error = E_OK ;

	if (data == NULL) 
		as16_state_error |= E_NOK;

	switch(GPIO)
	{
	case GPIOA:
		*data = PORTA_PIN & pins;
		break;
	case GPIOB:
		*data = PORTB_PIN & pins;
		break;
	case GPIOC:
		*data = PORTC_PIN & pins;
		break;
	case GPIOD:
		*data = PORTD_PIN & pins;
		break;
	default:
		as16_state_error |= E_NOK;
	}

	return as16_state_error;
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
 * 			 or even one pin.
 */
ERROR_STATUS DIO_Toggle(uint8_t GPIO, uint8_t pins)
{
	sint16_t as16_state_error = E_OK ;

	switch(GPIO)
	{
	case GPIOA:
		PORTA_DATA ^= (pins);
		break;
	case GPIOB:
		PORTB_DATA ^= (pins);
		break;
	case GPIOC:
		PORTC_DATA ^= (pins);
		break;
	case GPIOD:
		PORTD_DATA ^= (pins);
		break;
	default:
		as16_state_error |= E_NOK;
	}

	return as16_state_error;
}
