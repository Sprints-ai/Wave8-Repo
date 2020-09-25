/*
 ============================================================================
 Name        : Us.c
 Author      : Muhammed Gamal
 Description : this file include the implementation of the ULTRASONIC driver
 ============================================================================
 */


/*********************************includes**********************************/
#include "Us.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define ONE_MS 1
#define ULTRA_SONIC_SCALING 58
/***************************************************************************/


/******************************global variables*****************************/

/***************************************************************************/



/************************************************************************************
* Function Name: Us_Init
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: This function initiate the UltraSonic by set the value of the Dio_Dirction of
* the pin trigger as an output then initiate the ICU to use it to calculate the
* On time of the ECHO signal.
************************************************************************************/
ERROR_STATUS Us_Init(void)
{
	uint8_t u8_status;
	DIO_Cfg_s trigger_init=
	{
			trigger_init.GPIO=GPIOA,
			trigger_init.pins=BIT0,
			trigger_init.dir=OUTPUT,
	};
	DIO_init (&trigger_init);
	DIO_Write (GPIOA, BIT0, LOW);
	Icu_cfg_s echo_init={ICU_CH2,ICU_TIMER_CH2};    /*INT2,TIMER2*/
	Icu_Init(&echo_init);
	gu8_UltraSonic_Erro_Detection=FLAG_HIGH;
	u8_status=E_ok;
	return u8_status;

}



/************************************************************************************
* Function Name: Us_Trigger
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: This function send the  pulse, to trigger pin of the UltraSonic to enhance
* the  ECUO signal
************************************************************************************/
ERROR_STATUS Us_Trigger(void)
{
	uint8_t u8_status;
	_delay_us(1);
	DIO_Write (GPIOA, BIT0, HIGH);
	_delay_us(1);
	DIO_Write (GPIOA, BIT0, LOW);
	u8_status=E_ok;
	return u8_status;


}



/************************************************************************************
* Function Name: Us_GetDistance
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): Distance
* Return value: u8_error- variable that describe the error status
* Description: This function get the time of high signal of ECUO pulse, then               *
* use it to calculate the distance, then return the value in the
*  Distance parameter
************************************************************************************/
ERROR_STATUS Us_GetDistance(uint16_t *Distance)
{
	uint8_t u8_status;
	uint32_t u32_time;
	Icu_ReadTime(Timer_2,ICU_RISE_TO_FALL,&u32_time);   /*high time*/
	*Distance=u32_time/ULTRA_SONIC_SCALING;
	u8_status=E_ok;
	return u8_status;
}
