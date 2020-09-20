/*
 ============================================================================
 Name        : DIO.h
 Author      : Muhammed Gamal
 Description : this file includes the functions implementation of the DIO driver.
 ============================================================================
 */

/*********************************includes**********************************/
#include "DIO.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define NULL_Ptr ((void*)0)
/***************************************************************************/


/******************************global variables*****************************/

/***************************************************************************/




/************************************************************************************
* Function Name: Dio_WriteChannel
* Parameters (in): DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: This function can set the direction of a full port, a nibble
* or even one pin.
************************************************************************************/
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info)
{
	uint8_t u8_error;
	if(DIO_info == NULL_Ptr)
	{
		u8_error = E_NOk;
	}
	else
	{
		switch(DIO_info->GPIO)
		{
		case GPIOA:
			if(DIO_info->dir == INPUT)
			{
				PORTA_DIR &= ~(DIO_info->pins);
			}
			else
			{
				PORTA_DIR |= DIO_info->pins;
			}
			u8_error = E_ok;
			break;

		case GPIOB:
			if(DIO_info->dir == INPUT)
			{
				PORTB_DIR &= ~(DIO_info->pins);
			}
			else
			{
				PORTB_DIR |= DIO_info->pins;
			}
			u8_error = E_ok;
			break;
		case GPIOC:
			if(DIO_info->dir == INPUT)
			{
				PORTC_DIR &= ~(DIO_info->pins);
			}
			else
			{
				PORTC_DIR |= DIO_info->pins;
			}
			u8_error = E_ok;
			break;

		case GPIOD:
			if(DIO_info->dir == INPUT)
			{
				PORTD_DIR &= ~(DIO_info->pins);
			}
			else
			{
				PORTD_DIR |= DIO_info->pins;
			}
			u8_error = E_ok;
			break;

		default:
			u8_error = E_NOk;
			break;
		}
	}
	return u8_error;
}



/************************************************************************************
* Function Name: DIO_Write
* Parameters (in): GPIO -> to get PORT name
*                  pins -> pins to be written at
*                  value-> The desired value
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error-> variable that describe the error status
* Description: This function can set the value of a full port, a nibble
* or even one pin.
************************************************************************************/
ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value)
{
	uint8_t u8_error;
	switch(GPIO)
	{
	case GPIOA:

		if(value == LOW)
		{
			PORTA_DATA &= ~(pins);
		}
		else
		{
			PORTA_DATA |= (pins&value);
		}
		u8_error = E_ok;
		break;

	case GPIOB:
		if(value == LOW)
		{
			PORTB_DATA &= ~(pins);
		}
		else
		{
			PORTB_DATA |= (pins&value);
		}
		u8_error = E_ok;
		break;
	case GPIOC:
		if(value == LOW)
		{
			PORTC_DATA &= ~(pins);
		}
		else
		{
			PORTC_DATA |= (pins&value);
		}
		u8_error = E_ok;
		break;

	case GPIOD:
		if(value == LOW)
		{
			PORTD_DATA &= ~(pins);
		}
		else
		{
			PORTD_DATA |= (pins&value);
		}
		u8_error = E_ok;
		break;

	default:
		u8_error = E_NOk;
		break;
	}
	return u8_error;
}



/************************************************************************************
* Function Name: DIO_Read
* Parameters (in): GPIO -> to get PORT name
*                  pins -> pins to be written at
*                  value-> The desired value
* Parameters (inout): None
* Parameters (out): data -> the acquired data either it was PORT data or pins data
* Return value: u8_error-> variable that describe the error status
* Description: This function can read the value of a full port, a nibble
* or even one pin.
************************************************************************************/
ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data)
{
	uint8_t u8_error;
	switch(GPIO)
	{
	case GPIOA:
		*data= (PORTA_PIN & pins);
		u8_error = E_ok;
		break;

	case GPIOB:
		*data= (PORTB_PIN & pins);
		u8_error = E_ok;
		break;

	case GPIOC:
		*data= (PORTC_PIN & pins);
		u8_error = E_ok;
		break;
	case GPIOD:
		*data= (PORTD_PIN & pins);
		u8_error = E_ok;
		break;
	default:
		u8_error = E_NOk;
		break;
	}
	if(*data!=LOW)
	{
		*data=HIGH;
	}
	return u8_error;
}



/************************************************************************************
* Function Name: DIO_Toggle
* Parameters (in): GPIO -> to get PORT name
*                  pins -> pins to be written at
* Parameters (inout): None
* Parameters (out): data -> the acquired data either it was PORT data or pins data
* Return value: u8_error-> variable that describe the error status
* Description: This function toggles the value of a full port, a nibble
* or even one pin.
************************************************************************************/
ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins)
{
	uint8_t u8_error;
	switch(GPIO)
	{
	case GPIOA:
			PORTA_DATA ^= pins;
			u8_error = E_ok;
		break;

	case GPIOB:
			PORTB_DATA ^= (pins);
			u8_error = E_ok;
		break;
	case GPIOC:
			PORTC_DATA ^= (pins);
			u8_error = E_ok;
		break;

	case GPIOD:
			PORTD_DATA ^= (pins);
			u8_error = E_ok;
		break;

	default:
		u8_error = E_NOk;
		break;
	}
	return u8_error;
}

