/*
 * IdealPushButton.c
 *
 * Created: 3/16/2020 3:15:14 PM
 *  Author: ahmed
 */ 

#include "IdealPushButton.h"
#include "../MCAL/interrupt.h"
#include "../Infrastructure/Errors.h"

volatile static uint8_t gu8_IPB_PressedFlag0 = FALSE;
volatile static uint8_t gu8_IPB_PressedFlag1 = FALSE;
volatile static uint8_t gu8_IPB_PressedFlag2 = FALSE;

static void gu8_IPB_PressedFlag_Setter0 (void)
{
	gu8_IPB_PressedFlag0 = TRUE;
}
static void gu8_IPB_PressedFlag_Setter1 (void)
{
	gu8_IPB_PressedFlag1 = TRUE;
}
static void gu8_IPB_PressedFlag_Setter2 (void)
{
	gu8_IPB_PressedFlag2 = TRUE;
}
ERROR_STATUS IdealPushButton_Init(str_IPB_Config* IPB_Config)
{
	ERROR_STATUS ERR = E_OK;
	switch(IPB_Config->u8_EXTI_Channel)
	{
		case IPB_EXTI_INT0:
			EXTI_Init(INT0,INT0_RISING_EDGE,gu8_IPB_PressedFlag_Setter0);
			break;
		
		case IPB_EXTI_INT1:
			EXTI_Init(INT1,INT1_RISING_EDGE,gu8_IPB_PressedFlag_Setter1);
			break;
		
		case IPB_EXTI_INT2:
			EXTI_Init(INT2,INT2_RISING_EDGE,gu8_IPB_PressedFlag_Setter2);
			break;
		
		default:
			ERR = ERROR_INVALID_PARAMETER;
			break;
	}
	return ERR;
}

ERROR_STATUS IdealPushButton_GetStatus(uint8_t* u8_Status)
{
	ERROR_STATUS ERR = E_OK;
	
	if(u8_Status != NULL)
	{
		if (gu8_IPB_PressedFlag0)
		{
			*u8_Status = IPB_0_PRESSED;
			gu8_IPB_PressedFlag0 = FALSE;
		}
		if (gu8_IPB_PressedFlag1)
		{
			*u8_Status = IPB_1_PRESSED;
			gu8_IPB_PressedFlag1 = FALSE;
		}
		if (gu8_IPB_PressedFlag2)
		{
			*u8_Status = IPB_2_PRESSED;
			gu8_IPB_PressedFlag2 = FALSE;
		}
	}
	
	else
	{
		ERR = ERROR_NULL_POINTER;
	}
	
	return ERR;
}