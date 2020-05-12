/*
* gpio.c
*
* Created: 17/01/2020 01:12:53 م
*  Author: mo
*/
#include "gpio.h"


ERROR_STATUS gpioPortDirection(uint8_t u8_port, uint8_t u8_direction)
{
	/**
	* Description: set the port Direction (which is PORT register)
	* @param port: portID and takes the following values
	* 				- 0 -> GPIOA
	* 				- 1 -> GPIOB
	* 				- 2 -> GPIOC
	* 				- 3 -> GPIOD
	* @param value: set the port Direction and takes the following values
	* 				- 0x00 -> OUTPUT
	* 				- 0xFF -> INPUT
	*
	* @return Function Error Status
	*/
	
	ERROR_STATUS ERR = E_OK;
	
	if (u8_direction == OUTPUT || u8_direction == INPUT)
	{
		switch (u8_port)
		{
			case GPIOA:
			PORTA_DIR = u8_direction;
			break;
			
			case GPIOB:
			PORTB_DIR = u8_direction;
			break;
			
			case GPIOC:
			PORTC_DIR = u8_direction;
			break;
			
			case GPIOD:
			PORTD_DIR = u8_direction;
			break;
			
			default:
			ERR = ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		ERR = ERROR_INVALID_PARAMETER;
	}
	
	return ERR;

}

ERROR_STATUS gpioPortWrite(uint8_t u8_port, uint8_t u8_value)
{
	/**
	* Description: set the port value (which is PORT register)
	* @param port: portID and takes the following values
	* 				- 0 -> GPIOA
	* 				- 1 -> GPIOB
	* 				- 2 -> GPIOC
	* 				- 3 -> GPIOD
	* @param value: set the port value and takes the following values
	* 				- 0x00 -> OUTPUT
	* 				- 0xFF -> INPUT
	*
	* @return Function Error Status
	*/
	ERROR_STATUS ERR = E_OK;
	
	if (u8_value == HIGH || u8_value== LOW)
	{
		switch (u8_port)
		{
			case GPIOA:
			PORTA_DIR = u8_value;
			break;
			
			case GPIOB:
			PORTB_DIR = u8_value;
			break;
			
			case GPIOC:
			PORTC_DIR = u8_value;
			break;
			
			case GPIOD:
			PORTD_DIR = u8_value;
			break;
			
			default:
			ERR = ERROR_INVALID_PARAMETER;
		}
	}
	else
	{
		ERR = ERROR_INVALID_PARAMETER;
	}
	
	return ERR;
	
}

ERROR_STATUS gpioPortToggle(uint8_t u8_port)
{
/**
 * Description: toggle the port value (which is PORT register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @return Function Error Status
 */
	ERROR_STATUS ERR = E_OK;
	
	switch (u8_port)
	{	
		case GPIOA:
		PORTA_DATA ^= HIGH;
		break;
		
		case GPIOB:
		PORTB_DATA ^= HIGH;
		break;
		
		case GPIOC:
		PORTC_DATA ^= HIGH;
		break;
		
		case GPIOD:
		PORTD_DATA ^= HIGH;
		break;
		
		default:
		ERR = ERROR_INVALID_PARAMETER;
	}
	
	return ERR;
}

ERROR_STATUS gpioPortRead(uint8_t u8_port , uint8_t* u8_PortValue)
{
/**
 * Description: read the current port value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param PortValue: Output parameter: pointer to return the port value in
 * @return Function Error Status
 */

	ERROR_STATUS ERR = E_OK;
	
	if (u8_PortValue != NULL)
	{
		switch (u8_port)
		{
			case GPIOA:
			*u8_PortValue = PORTA_PIN ;
			break;
			
			case GPIOB:
			*u8_PortValue = PORTB_PIN ;
			break;
			
			case GPIOC:
			*u8_PortValue = PORTC_PIN ;
			break;
			
			case GPIOD:
			*u8_PortValue = PORTD_PIN ;
			break;
			
			default:
			ERR = ERROR_INVALID_PARAMETER;
		}

	}
	
	else 
	{
		ERR = ERROR_NULL_POINTER;
	}
	
	return 	ERR;
}

ERROR_STATUS gpioPinDirection(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_direction)
{
	/**
	* Description: set selected pins (more than one pin [ORed]) direction
	*
	* @param port: portID and takes the following values
	* 				- 0 -> GPIOA
	* 				- 1 -> GPIOB
	* 				- 2 -> GPIOC
	* 				- 3 -> GPIOD
	* @param pins: the selected pins the user need to set its direction and takes
	* 				any of the following parameters:
	* 				- BIT0
	* 				- BIT1
	* 				- BIT2
	* 				- BIT3
	* 				- BIT4
	* 				- BIT5
	* 				- BIT6
	* 				- BIT7
	*
	* @param direction: set the pins direction and takes the following values
	* 				- 0x00 -> Input
	* 				- 0xFF -> Output
	*/
	
	ERROR_STATUS ERR = E_OK;
	
	switch(u8_port)
	{
		case GPIOA:
		{
			switch (u8_direction)
			{
				case INPUT:
				PORTA_DIR &=(~u8_pins);
				break;
				
				case OUTPUT:
				PORTA_DIR |=(u8_pins);
				
				default:
				ERR = ERROR_INVALID_PARAMETER;
			}
		}
		break;
		
		case GPIOB:
		{
			switch (u8_direction)
			{
				case INPUT:
				PORTB_DIR &=(~u8_pins);
				break;
				
				case OUTPUT:
				PORTB_DIR |=(u8_pins);
				
				default:
				ERR = ERROR_INVALID_PARAMETER;
			}
		}
		break;
		
		case GPIOC:
		{
			switch (u8_direction)
			{
				case INPUT:
				PORTC_DIR &=(~u8_pins);
				break;
				
				case OUTPUT:
				PORTC_DIR |=(u8_pins);
				
				default:
				ERR = ERROR_INVALID_PARAMETER;
			}
		}
		break;
		
		case GPIOD:
		{
			switch (u8_direction)
			{
				case INPUT:
				PORTD_DIR &=(~u8_pins);
				break;
				
				case OUTPUT:
				PORTD_DIR |=(u8_pins);
				
				default:
				ERR = ERROR_INVALID_PARAMETER;
			}
		}
		break;
		
		default:
		ERR = ERROR_INVALID_PARAMETER;
	}
	
	return ERR;
}


ERROR_STATUS gpioPinWrite(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_value)
{
	/**
 * Description: set selected pins (more than one pin [ORed]) values
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pins the user need to write its values and takes
 * 				any of the following parameters:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 * @param value
 */
	ERROR_STATUS ERR = E_OK;
	
	switch(u8_value)
	{
		case LOW:
		{
			switch (u8_port)
			{	
				case GPIOA:
				PORTA_DATA &= ~(u8_pins);   
				break;
				
				case GPIOB:
				PORTB_DATA &= ~(u8_pins);
				break;
				
				case GPIOC:
				PORTC_DATA &= ~(u8_pins);
				break;
				
				case GPIOD:
				PORTD_DATA &= ~(u8_pins);
				break;
				
				default:
				ERR = ERROR_INVALID_PARAMETER;
				
			}
			break;
		}
		case HIGH:
		{
			switch (u8_port)
			{	
				case GPIOA:
				PORTA_DATA |=(u8_pins);
				break;
				
				case GPIOB:
				PORTB_DATA |=(u8_pins);
				break;
				
				case GPIOC:
				PORTC_DATA |=(u8_pins);
				break;
				
				case GPIOD:
				PORTD_DATA |=(u8_pins);
				break;
				
				default:
				ERR = ERROR_INVALID_PARAMETER;
				
			}
			break;
		}
		
		default:
		ERR = ERROR_INVALID_PARAMETER;
	}
	
	return ERR;
}

ERROR_STATUS gpioPinToggle(uint8_t u8_port, uint8_t u8_pins)
{
	/**
 * Description: toggle selected pin (only one pin) direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pin the user need to toggle it's value and takes
 * 				only one of the following parameters:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 * @return Function's Error Status
 */
	ERROR_STATUS ERR = E_OK;
	
	switch (u8_port)
	{	
		case GPIOA:
		PORTA_DATA ^=(u8_pins);
		break;
		
		case GPIOB:
		PORTB_DATA ^=(u8_pins);
		break;
		
		case GPIOC:
		PORTC_DATA ^=(u8_pins);
		break;
		
		case GPIOD:
		PORTD_DATA ^=(u8_pins);
		break;
		
		default:
		ERR = ERROR_INVALID_PARAMETER;
	}
	
	return ERR;
	
}

ERROR_STATUS gpioPinRead(uint8_t u8_port, uint8_t u8_pin , uint8_t* u8_PinValue)
{
	/**
 * Description: read selected pin (only one pin) direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param pin: the selected pin the user need to read it's value and takes
 * 				only one of the following parameters:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 * @return Function's Error Status
 */
	ERROR_STATUS ERR = E_OK;
	
	if (u8_PinValue != NULL)
	{
		switch (u8_port)
		{
			case GPIOA:
			*u8_PinValue = PORTA_PIN & u8_pin;
			break;
			
			case GPIOB:
			*u8_PinValue = PORTB_PIN & u8_pin;
			break;
			
			case GPIOC:
			*u8_PinValue = PORTC_PIN & u8_pin;
			break;
			
			case GPIOD:
			*u8_PinValue = PORTD_PIN & u8_pin;
			break;
			
			default:
			ERR = ERROR_INVALID_PARAMETER;
			break;
		}
		
		if(*u8_PinValue)
		{
			*u8_PinValue = HIGH;
		}
	}
	
	else
	{
		ERR = ERROR_NULL_POINTER;
	}
	
	return ERR;
}