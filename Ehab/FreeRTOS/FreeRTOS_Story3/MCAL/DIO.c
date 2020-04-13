/*
 * DIO.c
 *
 * Created: 2/15/2020 4:40:41 PM
 *  Author: Ema
 */ 


#include "DIO.h"

ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info)
{
	ERROR_STATUS ERROR = E_OK;
	
	switch (DIO_info->dir)
	{
		case INPUT:
		switch (DIO_info->GPIO)
		{
			case GPIOA:
			PORTA_DIR &= ~(DIO_info->pins);
			break;
			case GPIOB:
			PORTB_DIR &= ~(DIO_info->pins);
			break;
			case GPIOC:
			PORTC_DIR &= ~(DIO_info->pins);
			break;
			case GPIOD:
			PORTD_DIR &= ~(DIO_info->pins);
			break;
		}
		break;
		case OUTPUT:
		switch (DIO_info->GPIO)
		{
			case GPIOA:
			PORTA_DIR |= (DIO_info->pins);
			break;
			case GPIOB:
			PORTB_DIR |= (DIO_info->pins);
			break;
			case GPIOC:
			PORTC_DIR |= (DIO_info->pins);
			break;
			case GPIOD:
			PORTD_DIR |= (DIO_info->pins);
			break;
		}
		break;
	}
	
	return ERROR;
}

ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value)
{
	ERROR_STATUS ERROR = E_OK;
	
	switch (value)
	{
		case LOW:
		switch (GPIO)
		{
			case GPIOA:
			PORTA_DATA &= ~pins;
			break;
			case GPIOB:
			PORTB_DATA &= ~pins;
			break;
			case GPIOC:
			PORTC_DATA &= ~pins;
			break;
			case GPIOD:
			PORTD_DATA &= ~pins;
			break;
		}
		break;
		default:
		switch (GPIO)
		{
			case GPIOA:
			{
				PORTA_DATA &= ~pins;
				pins &= value;
				PORTA_DATA |= pins;
			}
			break;
			case GPIOB:
			{
				PORTB_DATA &= ~pins;
				pins &= value;
				PORTB_DATA |= pins;
			}
			break;
			case GPIOC:
			{
				PORTC_DATA &= ~pins;
				pins &= value;
				PORTC_DATA |= pins;
			}
			break;
			case GPIOD:
			{
				PORTD_DATA &= ~pins;
				pins &= value;
				PORTD_DATA |= pins;
			}
			break;
		}
		break;
	}
	return ERROR;
}

ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data)
{
	ERROR_STATUS ERROR = E_OK;
		
	switch (GPIO)
	{
		case GPIOA:
		*data = (PORTA_PIN&pins);
		break;
		case GPIOB:
		*data = (PORTB_PIN&pins);
		break;
		case GPIOC:
		*data = (PORTC_PIN&pins);
		break;
		case GPIOD:
		*data = (PORTD_PIN&pins);
		break;
	}
	return ERROR;
}

ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins)
{
	ERROR_STATUS ERROR = E_OK;
	
	switch (GPIO)
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
	}
	return ERROR;
}