/*
 * DIO.c
 *
 * Created: 2/17/2020 4:31:34 PM
 *  Author: ahmed
 */ 

#include "DIO.h"


/**
 * Description: set the whole port , a nibble ,a group of random pins or a single pin's direction 
 * @param DIO_Info: Pointer to the pre_configured struct
 *
 * @return function status :
 *				- 0 -> E_NOK
 *				- 1 -> E_OK
 */
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info)
{
	ERROR_STATUS ERR = E_OK;
	
	if (DIO_info == NULL)
	{
		ERR = E_NOK;
	}
	
	else 
	{
		switch (DIO_info->GPIO)
		{
			case GPIOA:
			{
				switch (DIO_info->dir)
				{
					case INPUT:
					PORTA_DIR &= (~(DIO_info->pins));
					
					case OUTPUT:
					PORTA_DIR |= (DIO_info->pins);
					
				}
			}
			break;
			
			case GPIOB:
			{
				switch (DIO_info->dir)
				{
					case INPUT:
					PORTB_DIR &= (~(DIO_info->pins));
					
					case OUTPUT:
					PORTB_DIR |= (DIO_info->pins);
					
				}
			}
			break;
			
			case GPIOC:
			{
				switch (DIO_info->dir)
				{
					case INPUT:
					PORTC_DIR &= (~(DIO_info->pins));
					
					case OUTPUT:
					PORTC_DIR |= (DIO_info->pins);
					
				}
			}
			break;
			
			case GPIOD:
			{
				switch (DIO_info->dir)
				{
					case INPUT:
					PORTD_DIR &= (~(DIO_info->pins));
					
					case OUTPUT:
					PORTD_DIR |= (DIO_info->pins);
					
				}
			}
			break;
			
			default:
			ERR = E_NOK;
			break;
		}
	}
	return ERR;
}

/**
 * Description: set the value of a whole port , a nibble , a group of random pins or a single pin
 * @param GPIO: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pin the user need to toggle it's value and takes
 * 				a single value of the following values or a group of them ORed together:
 * 				- 0x01-> PIN0
 * 				- 0x02-> PIN1
 * 				- 0x04-> PIN2
 * 				- 0x08-> PIN3
 * 				- 0x10-> PIN4
 * 				- 0x20-> PIN5
 * 				- 0x40-> PIN6
 * 				- 0x80-> PIN7
 * @param value: set the value and takes the following values
 * 				- 0x00 -> LOW
 * 				- 0xFF -> HIGH
 * @return function status :
 *				- 0 -> E_NOK
 *				- 1 -> E_OK
 */
ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value)
{
	ERROR_STATUS ERR = E_OK;
	
	switch(value){
		case LOW:
		{
			switch (GPIO)
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
				ERR = E_NOK;
				break;
				
			}
			break;
		}
		
		case HIGH:
		{
			switch (GPIO)
			{
				case GPIOA:
				PORTA_DATA |= (pins);
				break;
				
				case GPIOB:
				PORTB_DATA |= (pins);
				break;
				
				case GPIOC:
				PORTC_DATA |= (pins);
				break;
				
				case GPIOD:
				PORTD_DATA |= (pins);
				break;
				
				default:
				ERR = E_NOK;
				break;
				
			}
			break;
		}
		
		default:
		ERR = E_NOK;
		break;
	}
	
	return ERR ;
}

/**
 * Description: reads the mask value of a whole port , a nibble , a group of random pins or a single pin
 * @param GPIO: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pin the user need to toggle it's value and takes
 * 				a single value of the following values or a group of them ORed together:
 * 				- 0x01-> PIN0
 * 				- 0x02-> PIN1
 * 				- 0x04-> PIN2
 * 				- 0x08-> PIN3
 * 				- 0x10-> PIN4
 * 				- 0x20-> PIN5
 * 				- 0x40-> PIN6
 * 				- 0x80-> PIN7
 * @param data: output parameter : returns the mask value
 * 	
 * @return function status :
 *				- 0 -> E_NOK
 *				- 1 -> E_OK
 */
ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data)
{
	ERROR_STATUS ERR = E_OK;
	
	
	switch (GPIO)
	{
		case GPIOA:
		if (data != NULL)
		*data =PORTA_PIN & pins;
		
		else
		ERR = E_NOK;
		break;
		
		case GPIOB:
		if (data != NULL)
		*data =PORTB_PIN & pins;
		
		else
		ERR = E_NOK;
		break;
		
		case GPIOC:
		if (data != NULL)
		*data =PORTC_PIN & pins;
		
		else
		ERR = E_NOK;
		break;
		
		case GPIOD:
		if (data != NULL)
		*data =PORTD_PIN & pins;
		
		else
		ERR = E_NOK;
		break;
		
		default:
		ERR = E_NOK;
		break;
	}
	
	return ERR;
}

/**
 * Description: toggles the value of a whole port , a nibble , a group of random pins or a single pin
 * @param GPIO: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pin the user need to toggle it's value and takes
 * 				a single value of the following values or a group of them ORed together:
 * 				- 0x01-> PIN0
 * 				- 0x02-> PIN1
 * 				- 0x04-> PIN2
 * 				- 0x08-> PIN3
 * 				- 0x10-> PIN4
 * 				- 0x20-> PIN5
 * 				- 0x40-> PIN6
 * 				- 0x80-> PIN7
 *
 * @return function status :
 *				- 0 -> E_NOK
 *				- 1 -> E_OK
 */
ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins)
{
	ERROR_STATUS ERR = E_OK;
	
	switch (GPIO)
	{
		case GPIOA:
		PORTA_DATA ^=(pins);
		break;
		
		case GPIOB:
		PORTB_DATA ^=(pins);
		break;
		
		case GPIOC:
		PORTC_DATA ^=(pins);
		break;
		
		case GPIOD:
		PORTD_DATA ^=(pins);
		break;
		
		default:
		ERR = E_NOK;
		break;
	}
	return ERR;
}