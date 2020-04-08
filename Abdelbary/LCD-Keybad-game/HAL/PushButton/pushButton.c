/*
 * pushButton.c
 *
 * Created: 1/17/2020 9:21:54 AM
 *  Author: mahmo
 */ 
#include "pushButton.h"

#define PRESS_CONFIRM  4

static uint8_t gu8_b0Confidenss;
static uint8_t gu8_b1Confidenss;
static uint8_t gu8_button0Lock;
static uint8_t gu8_button1Lock;
static uint8_t gu8_ModuleInitFlag = FALSE;
ERROR_STATUS pushButtonInit(uint8_t u8_butotn_id)
{
	ERROR_STATUS s16_funStatus = OK;
	if (gu8_ModuleInitFlag == TRUE)
	{
		s16_funStatus = PB_MODULE_ERR + MULTIPLE_INITALIZATION;
	}
	else
	{
		switch(u8_butotn_id)
		{
			case BTN_0:
			gpioPinDirection(BTN_0_GPIO,BTN_0_BIT,INPUT);
			break;
			case BTN_1:
			gpioPinDirection(BTN_1_GPIO,BTN_1_BIT,INPUT);
			break;
		}
		/*initialize global variables*/
		gu8_b0Confidenss = ZERO;
		gu8_b1Confidenss = ZERO;
		gu8_button0Lock = UNLOCK;
		gu8_button1Lock = UNLOCK;
		gu8_ModuleInitFlag = TRUE;
	}
	return s16_funStatus;
}

ERROR_STATUS pushButtonGetStatus(uint8_t u8_butotn_id,uint8_t* state)
{
	/*get current button status*/
	ERROR_STATUS s16_funStatus = OK ;
	if (gu8_ModuleInitFlag == FALSE)
	{
		s16_funStatus = PB_MODULE_ERR + MODULE_NOT_INITALIZED;
	}
	else
	{
		uint8_t u8_value = LOW;/*assume the default is LOW*/
		*state = Released;/*assume the button currently released*/
		switch(u8_butotn_id)
		{
			case BTN_0:
			DIO_Read(BTN_0_GPIO,BTN_0_BIT,&u8_value);
			if(u8_value != LOW)
			{
				*state = Pressed;
			}
			else/*unblock button to count press again*/
			{
				gu8_button0Lock = UNLOCK;
			}
			break;
			case BTN_1:
			DIO_Read(BTN_1_GPIO,BTN_1_BIT,&u8_value);
			if(u8_value != LOW)
			{
				*state = Pressed;
			}
			else/*unblock button to count press again*/
			{
				gu8_button1Lock = UNLOCK;
			}
			break;
		}
	}
	
	return s16_funStatus;
}

ERROR_STATUS pushButtonUpdate(void)
{
	ERROR_STATUS s16_funStatus = OK;
	if (gu8_ModuleInitFlag == FALSE)
	{
		s16_funStatus = PB_MODULE_ERR + MODULE_NOT_INITALIZED;
	}
	else
	{
		uint8_t state = Released;
		
		/*get first button state*/
		pushButtonGetStatus(BTN_0,&state);
		if (state == Pressed && gu8_button0Lock == UNLOCK)
		gu8_b0Confidenss++;
		
		/*get second button state*/
		pushButtonGetStatus(BTN_1,&state);
		if (state == Pressed && gu8_button1Lock == UNLOCK)
		gu8_b1Confidenss++;
	}
	return s16_funStatus;
}

ERROR_STATUS pushButtonPressed(uint8_t u8_butotn_id,uint8_t* flag)
{
	ERROR_STATUS s16_funStatus =OK;
	if (gu8_ModuleInitFlag == FALSE)
	{
		s16_funStatus = PB_MODULE_ERR + MODULE_NOT_INITALIZED;
	}
	else
	{
		/*update button state*/
		pushButtonUpdate();
		switch(u8_butotn_id)
		{
			case BTN_0:
			if(gu8_b0Confidenss >= PRESS_CONFIRM)
			{
				*flag = Pressed;
				gu8_b0Confidenss = ZERO;
				gu8_button0Lock = LOCK;
			}
			else
			*flag = Released;
			break;
			case BTN_1:
			if(gu8_b1Confidenss >= PRESS_CONFIRM)
			{
				*flag = Pressed;
				gu8_b1Confidenss = ZERO;
				gu8_button1Lock = LOCK;
			}
			else
			*flag = Released;
			break;
		}
	}
	
	return s16_funStatus;
}

