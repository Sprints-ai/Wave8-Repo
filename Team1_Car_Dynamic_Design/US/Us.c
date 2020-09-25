/************************************************************************/
/*                          Includes                                    */
/************************************************************************/

#include "std_types.h"
#include "registers.h"
#include "DIO.h"
#include "ICU.h"
#include "US.h"

#define F_CPU	16000000UL
#include "Util/delay.h"

/************************************************************************/
/*                          Ultrasonic basic configurations             */
/************************************************************************/

#define US_TRIG_PORT	(GPIOD)
#define US_ECHO_PORT	(GPIOB)
#define US_TRIG_PIN		(PIN0)
#define US_ECHO_PIN		(PIN2)

#define TRIG_DELAY_US	(10)
#define DISTANCE_CM_US	(58)

/************************************************************************/
/*                         Ultrasonic functions                         */
/************************************************************************/

ERROR_STATUS Us_Init(void)
{
	/*Error indication variables*/
	ERROR_STATUS err_var = E_OK;
	ERROR_STATUS err_1 = E_OK;
	ERROR_STATUS err_2 = E_OK;
	
	/*Initializing ultrasonic pins*/
	err_1 = DIO_init(US_TRIG_PORT , US_TRIG_PIN , OUTPUT);
	err_1 = DIO_init(US_ECHO_PORT , US_ECHO_PIN , INPUT);

	/*Initializing ICU module*/
	err_2 = Icu_Init(ICU_CH2 , ICU_TIMER_CH2);

	/*Error validation*/	
	if ( (err_1 == E_NOK) || (err_2 == E_NOK) )
	{
		err_var = E_NOK;
	} 
	else
	{
		err_var = E_OK;
	}
	return err_var;
}

ERROR_STATUS Us_Trigger(void)
{
	/*Error indication variable*/
	ERROR_STATUS err_var = E_OK;
	
	/*Setting trig pin to HIGH*/
	err_var = DIO_Write(US_TRIG_PORT , US_TRIG_PIN , HIGH);
	
	/*Delay for a specified time in us*/
	_delay_us(TRIG_DELAY_US);
	
	/*Setting trig pin to LOW*/	
	err_var = DIO_Write(US_TRIG_PORT , US_TRIG_PIN , LOW);
	
	return err_var;
}

ERROR_STATUS Us_GetDistance(uint32_t *pu32_Distance)
{
	/*Error indication variable*/
	ERROR_STATUS err_var = E_OK;
	
	if (pu32_Distance != NULL)
	{
		/*variable used in getting time in us*/
		uint32_t au32_time_us = ZERO;
	
		/*Getting the time in us*/
		err_var = Icu_ReadTime(ICU_CH2 , ICU_COUNT_CAPT_RISING , &au32_time_us);
	
		/*Calculating the distance value*/
		*pu32_Distance = au32_time_us/DISTANCE_CM_US;
	} 
	else
	{
		/*The used pointer is NULL*/
		err_var = E_NOK;
	}
	
	return err_var; 
}