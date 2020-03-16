/*
 * DIO.c
 *
 *  Created on: Feb 17, 2020
 *      Author: Youssef Harby
 */


/*- INCLUDES -----------------------------------------------*/

#include "DIO.h"


/*- APIs IMPLEMENTATION ------------------------------------*/

ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info)
{
	uint8_t au8_Ret = E_OK;
	/* A local pointer to register in which the required register address will be stored */
	uint8_t* pau8_gpioDirectionPointer = NULL;

	/* A switch case to determine which Port to change its direction */
	switch(DIO_info->GPIO)
	{
	case GPIOA:
		pau8_gpioDirectionPointer = (uint8_t*)(&PORTA_DIR);
		break;
	case GPIOB:
		pau8_gpioDirectionPointer = (uint8_t*)(&PORTB_DIR);
		break;
	case GPIOC:
		pau8_gpioDirectionPointer = (uint8_t*)(&PORTC_DIR);
		break;
	case GPIOD:
		pau8_gpioDirectionPointer = (uint8_t*)(&PORTD_DIR);
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	if(au8_Ret == E_OK)
	{
		/* A switch case to determine which direction to be configured in the port */
		switch(DIO_info->dir)
		{
		case INPUT:
			*pau8_gpioDirectionPointer &= ~(DIO_info->pins);
			break;
		case OUTPUT:
			*pau8_gpioDirectionPointer |= (DIO_info->pins);
			break;
		default:
			au8_Ret = E_NOK;
			break;
		}
	}

	return au8_Ret;
}

ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value)
{
	uint8_t au8_Ret = E_OK;
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
		au8_Ret = E_NOK;
		break;
	}

	if(au8_Ret == E_OK)
	{
		/* A switch case to determine which value to be configured in the port */
		switch(value)
		{
		case LOW:
			*pau8_gpioDataPointer &= ~(pins);
			break;
		case HIGH:
			*pau8_gpioDataPointer |= (pins);
			break;
		default:
			au8_Ret = E_NOK;
			break;
		}
	}

	return au8_Ret;
}

ERROR_STATUS DIO_WriteValue (uint8_t GPIO, uint8_t pins, uint8_t value)
{
	uint8_t au8_Ret = E_OK;
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
		au8_Ret = E_NOK;
		break;
	}

	if(au8_Ret == E_OK)
	{
		*pau8_gpioDataPointer = (*pau8_gpioDataPointer & ~pins) | (value & pins);
	}

	return au8_Ret;
}


ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t* data)
{
	uint8_t au8_Ret = E_OK;

	if(data != NULL)
	{
		/* A switch case to determine which port will be read from */
		switch(GPIO)
		{
		case GPIOA:
			*data = PORTA_PIN & pins? 1:0;
			break;
		case GPIOB:
			*data = PORTB_PIN & pins? 1:0;
			break;
		case GPIOC:
			*data = PORTC_PIN & pins? 1:0;
			break;
		case GPIOD:
			*data = PORTD_PIN & pins? 1:0;
			break;
		default:
			au8_Ret = E_NOK;
			break;
		}
	}else
	{
		au8_Ret = E_NOK;
	}

	return au8_Ret;
}

ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins)
{
	uint8_t au8_Ret = E_OK;

	/* A switch case to determine which port value to be toggled */
	switch(GPIO)
	{
	case GPIOA:
		PORTA_DATA ^= pins;
		break;
	case GPIOB:
		PORTB_DATA ^= pins;
		break;
	case GPIOC:
		PORTC_DATA ^= pins;
		break;
	case GPIOD:
		PORTD_DATA ^= pins;
		break;
	default:
		au8_Ret = E_NOK;
	}

	return au8_Ret;
}


