/*
* pushButton.c
*
* Created: 17/01/2020 05:27:05 pm
*  Author: mo
*/
#include "pushButton.h"
#include "pushButtonConfig.h"
#include "../../MCAL/gpio.h"
/*
#define BTN_0_GPIO	GPIOC
#define BTN_0_BIT	BIT4

#define BTN_1_GPIO	GPIOB
#define BTN_1_BIT	BIT2

#define BTN_2_GPIO	GPIOA
#define BTN_2_BIT	BIT2

#define BTN_3_GPIO 	GPIOA
#define BTN_3_BIT	BIT3
BTN_0,
BTN_1,
BTN_2,
BTN_3
*/
ERROR_STATUS pushButtonInit(uint8_t u8_butotn_id)
{
	ERROR_STATUS ERR = E_OK;
	switch(u8_butotn_id)
	{
		case BTN_0:
		gpioPinDirection(BTN_0_GPIO,BTN_0_BIT,INPUT);
		break;

		case BTN_1:
		gpioPinDirection(BTN_1_GPIO,BTN_1_BIT,INPUT);
		break;

		case BTN_2:
		gpioPinDirection(BTN_2_GPIO,BTN_2_BIT,INPUT);
		break;

		case BTN_3:
		gpioPinDirection(BTN_3_GPIO,BTN_3_BIT,INPUT);
		break;
		
		default:
		ERR = ERROR_INVALID_PARAMETER;
	}
	
	return ERR;
}

ERROR_STATUS pushButtonGetStatus(uint8_t u8_butotn_id , uint8_t* pu8_ButtonStatus)
{
	ERROR_STATUS ERR = E_OK;
	uint8_t u8_gpioPinRead_Return;
	
	switch(u8_butotn_id)
	{
		case BTN_0:
		gpioPinRead(BTN_0_GPIO,BTN_0_BIT,&u8_gpioPinRead_Return);
		break;
		
		case BTN_1:
		gpioPinRead(BTN_1_GPIO,BTN_1_BIT,&u8_gpioPinRead_Return);
		break;
		
		case BTN_2:
		gpioPinRead(BTN_2_GPIO,BTN_2_BIT,&u8_gpioPinRead_Return);
		break;
		
		case BTN_3:
		gpioPinRead(BTN_3_GPIO,BTN_3_BIT,&u8_gpioPinRead_Return);
		break;
		
		default:
		ERR = ERROR_INVALID_PARAMETER;
	}
	if (u8_gpioPinRead_Return)
	{
		*pu8_ButtonStatus = Pressed;
	}
	else
	{
		*pu8_ButtonStatus = Released;
	}
	
	return ERR;
}