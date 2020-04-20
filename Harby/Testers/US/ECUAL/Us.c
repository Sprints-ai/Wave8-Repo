/*
 * Us.c
 *
 *  Created on: Feb 18, 2020
 *      Author: Youssef Harby
 */


/*- INCLUDES -----------------------------------------------*/

#include "Us.h"


/*- DEFINES ------------------------------------------------*/

#define US_TRIGGER_GPIO		GPIOD
#define US_TRIGGER_BIT		BIT0

#define US_CONSTANT_PRESCALER_1024		1.088

#define US_NOT_INITIALIZED		0
#define US_INITIALIZED		1


/*- APIs IMPLEMENTATION ------------------------------------*/

uint8_t gu8_Us_InitStatus = US_NOT_INITIALIZED;


/*- APIs IMPLEMENTATION ------------------------------------*/

ERROR_STATUS Us_Init(void)
{
	sint8_t as8_Ret = E_OK;
	/* A structure to initialize the DIO trigger bit as output */
	DIO_Cfg_s Dio_InitializationConfig = {US_TRIGGER_GPIO, US_TRIGGER_BIT, OUTPUT};
	/* A structure to initialize the ICU module */
	Icu_cfg_s Icu_InitializationConfig = {ICU_CH2, ICU_TIMER_CH2};

	if(gu8_Us_InitStatus == US_NOT_INITIALIZED)
	{
		/* Initialization */
		as8_Ret |= DIO_init(&Dio_InitializationConfig);
		as8_Ret |= Icu_Init(&Icu_InitializationConfig);

		gu8_Us_InitStatus = US_INITIALIZED;
	}else if(gu8_Us_InitStatus == US_INITIALIZED)
	{
		as8_Ret = US_E_ALREADY_INIT;
	}

	return as8_Ret;
}

ERROR_STATUS Us_Trigger(void)
{
	sint8_t as8_Ret = E_OK;

	if(gu8_Us_InitStatus == US_INITIALIZED)
	{
		/* Sending trigger by putting the pin to high level then to low level after >1 msec delay */
		as8_Ret |= DIO_Write(US_TRIGGER_GPIO, US_TRIGGER_BIT, HIGH);
		softwareDelayMs(5);
		as8_Ret |= DIO_Write(US_TRIGGER_GPIO, US_TRIGGER_BIT, LOW);
	}else
	{
		as8_Ret = US_E_NOT_INIT;
	}

	return as8_Ret;
}

ERROR_STATUS Us_GetDistance(uint16_t* Distance)
{
	sint8_t as8_Ret = E_OK;

	/* The value to be returned from the Icu_ReadTime function and contains the timer counter value */
	uint32_t au32_CounterValue = 0;

	if(gu8_Us_InitStatus == US_INITIALIZED)
	{
		/* Reading the timer counter value required to calculate the edge detection time */
		as8_Ret |= Icu_ReadTime(ICU_CH2, ICU_RISE_TO_FALL, &au32_CounterValue);

		if(Distance != NULL)
		{
			*Distance = (uint16_t)((au32_CounterValue) * US_CONSTANT_PRESCALER_1024);
		}else
		{
			as8_Ret = US_E_NULL_POINTER;
		}
	}else
	{
		as8_Ret = US_E_NOT_INIT;
	}

	return as8_Ret;
}
