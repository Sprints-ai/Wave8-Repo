/************************************************************************/
/*                              Includes                                */
/************************************************************************/

#include "std_types.h"
#include "registers.h"
#include "DIO.h"

/************************************************************************/
/*                         DIO functions                                */
/************************************************************************/
ERROR_STATUS DIO_init (uint8_t au8_port, uint8_t au8_pins, uint8_t au8_status)
{
	ERROR_STATUS err_var = E_OK;
	
	switch(au8_port)
	{
		case GPIOA:
			switch(au8_status)
			{
				case OUTPUT:
					PORTA_DIR |= au8_pins; /*Setting specified pins to output*/
					break;
				
				case INPUT:
					PORTA_DIR &= ~(au8_pins); /*Setting specified pins to input*/
					break;
				
				default: err_var = E_NOK;		
			}
			break;

		case GPIOB:
			switch(au8_status)
			{
				case OUTPUT:
					PORTB_DIR |= au8_pins; /*Setting specified pins to output*/
					break;
				
				case INPUT:
					PORTB_DIR &= ~(au8_pins); /*Setting specified pins to input*/
					break;
				
				default: err_var = E_NOK;		
			}
			break;

		case GPIOC:
			switch(au8_status)
			{
				case OUTPUT:
					PORTC_DIR |= au8_pins; /*Setting specified pins to output*/
					break;
				
				case INPUT:
					PORTC_DIR &= ~(au8_pins); /*Setting specified pins to input*/
					break;
				
				default: err_var = E_NOK;		
			}
			break;

		case GPIOD:
			switch(au8_status)
			{
				case OUTPUT:
					PORTD_DIR |= au8_pins; /*Setting specified pins to output*/
					break;
				
				case INPUT:
					PORTD_DIR &= ~(au8_pins); /*Setting specified pins to input*/
					break;
				
				default: err_var = E_NOK;		
			}
			break;
		
		default: err_var = E_NOK;
	}
	
	return err_var;
}

ERROR_STATUS DIO_Write (uint8_t au8_port, uint8_t au8_pins, uint8_t au8_value)
{
	ERROR_STATUS err_var = E_OK;

	switch(au8_port)
	{
		case GPIOA:
			switch(au8_value)
			{
				case HIGH:
					PORTA_DATA |= au8_pins; /*Setting specified pins to high*/
					break;
				
				case LOW:
					PORTA_DATA &= ~(au8_pins); /*Setting specified pins to low*/
					break;
				
				default: err_var = E_NOK;		
			}
			break;

		case GPIOB:
			switch(au8_value)
			{
				case HIGH:
					PORTB_DATA |= au8_pins; /*Setting specified pins to high*/
					break;
				
				case LOW:
					PORTB_DATA &= ~(au8_pins); /*Setting specified pins to low*/
					break;
				
				default: err_var = E_NOK;		
			}
			break;

		case GPIOC:
			switch(au8_value)
			{
				case HIGH:
					PORTC_DATA |= au8_pins; /*Setting specified pins to high*/
					break;
				
				case LOW:
					PORTC_DATA &= ~(au8_pins); /*Setting specified pins to low*/
					break;
				
				default: err_var = E_NOK;		
			}
			break;

		case GPIOD:
			switch(au8_value)
			{
				case HIGH:
					PORTD_DATA |= au8_pins; /*Setting specified pins to high*/
					break;
				
				case LOW:
					PORTD_DATA &= ~(au8_pins); /*Setting specified pins to low*/
					break;
				
				default: err_var = E_NOK;		
			}
			break;
		
		default: err_var = E_NOK;
	}
	
	return err_var;
}

ERROR_STATUS DIO_Read (uint8_t au8_port,uint8_t au8_pin, uint8_t *pu8_data)
{
	ERROR_STATUS err_var = E_OK;
	
	if (pu8_data != NULL)
	{
		switch(au8_port)
		{
			case GPIOA:
				if (PORTA_PIN & au8_pin)
				{
					*pu8_data = HIGH; /*Reading pin data as HIGH*/
				} 
				else
				{
					*pu8_data = LOW; /*Reading pin data as LOW*/
				}
				break;

			case GPIOB:
				if (PORTB_PIN & au8_pin)
				{
					*pu8_data = HIGH; /*Reading pin data as HIGH*/
				}
				else
				{
					*pu8_data = LOW; /*Reading pin data as LOW*/
				}
				break;

			case GPIOC:
				if (PORTC_PIN & au8_pin)
				{
					*pu8_data = HIGH; /*Reading pin data as HIGH*/
				}
				else
				{
					*pu8_data = LOW; /*Reading pin data as LOW*/
				}
				break;

			case GPIOD:
				if (PORTD_PIN & au8_pin)
				{
					*pu8_data = HIGH; /*Reading pin data as HIGH*/
				}
				else
				{
					*pu8_data = LOW; /*Reading pin data as LOW*/
				}
				break;
		
			default: err_var = E_NOK;
		}		
	} 
	else
	{
		/*The pointer is equal to NULL*/
		err_var = E_NOK;
	}
	
	return err_var;
}

ERROR_STATUS DIO_Toggle (uint8_t au8_port, uint8_t au8_pins)
{
	ERROR_STATUS err_var = E_OK;
	
	switch(au8_port)
	{
		case GPIOA:
			PORTA_DATA ^= au8_pins; /*Toggling pin data*/
			break;

		case GPIOB:
			PORTB_DATA ^= au8_pins; /*Toggling pin data*/
			break;

		case GPIOC:
			PORTC_DATA ^= au8_pins; /*Toggling pin data*/
			break;

		case GPIOD:
			PORTD_DATA ^= au8_pins; /*Toggling pin data*/
			break;
			
		default: err_var = E_NOK;	
	}
	
	return err_var;
}