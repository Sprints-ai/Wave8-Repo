/*
 ============================================================================
 Name        : Car_sm.c
 Author      : Muhammed Gamal
 Description : this file include the functions implementation of the car simulation application
 ============================================================================
 */

/*********************************includes**********************************/
#include "car_sm.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define CLEAR 0
#define ENTRY_NUMBER 10
/***************************************************************************/


/******************************global variables*****************************/
uint16_t Distance;
uint8_t u8_state;
/***************************************************************************/



/************************************************************************************
* Function Name: Car_SM_Init
* Parameters (in): Icu_cfg : None
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: Initiate the car state machine with state"forward at speed 80%",
* And initiate steering and ultrasonic functions
************************************************************************************/
ERROR_STATUS Car_SM_Init(void)
{
	uint8_t u8_status;
	u8_status |= Us_Init();
	u8_status |= Steering_Init();
	u8_status |= Steering_SteerCar(CAR_FORWARD,INITIAL_SPEED);
	u8_status |= E_ok;
	/*initialize global variables*/
	Distance=CLEAR;
	u8_state=NEAR;
	if(u8_status == E_ok)
	{
		u8_status=E_ok;
	}
	else
	{
		u8_status = E_NOk;
	}
	return u8_status;
}



/************************************************************************************
* Function Name: Car_SM_Update
* Parameters (in): Icu_cfg : None
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: changes car state according to the ultrasonic input
* and represents the motors output for each state
************************************************************************************/
ERROR_STATUS Car_SM_Update(void)
{
	uint8_t au8_status;
	static uint8_t au8_EntryCounter;
	if(gu8_UltraSonic_Erro_Detection==FLAG_HIGH)
	{
		au8_status |= Us_Trigger();
		gu8_UltraSonic_Erro_Detection=FLAG_LOW;
	}
	au8_status |= Us_GetDistance(&Distance);

	if(Distance>NEAR_DISTANCE && Distance<=INTERMEDIATE_DISTANCE)
	{
		u8_state=NEAR;
	}
	else if(Distance>INTERMEDIATE_DISTANCE && Distance<=FAR_DISTANCE)
	{
		u8_state=INTERMEDIATE;
	}
	else if(Distance>FAR_DISTANCE)
	{
		u8_state=FAR;
	}

	/*
	 * -if this task called ten times, this means a 500ms delay is performed
	 * since this task is called by the SOS every 50ms
	 * -500ms is the appropriate delay for the car to turn right
	 **/
	if(au8_EntryCounter==ENTRY_NUMBER)
	{
		u8_state=INTERMEDIATE;
	}
	else
	{
		au8_EntryCounter=CLEAR;
	}
	switch(u8_state)
	{
		case NEAR:
			au8_status |= Steering_SteerCar(CAR_BACKWARD,MEDIUM_SPEED);
			break;
		case INTERMEDIATE:
			au8_status |= Steering_SteerCar(CAR_RIGHT,FULL_SPEED);
			/* I use this counter here to let the car rotates to right for an appropriate time*/
			au8_EntryCounter++;
			break;
		case FAR:
			au8_status |= Steering_SteerCar(CAR_FORWARD,MEDIUM_SPEED);
			break;
		default:
			break;
	}


	if(au8_status == E_ok)
	{
		au8_status=E_ok;
	}
	else
	{
		au8_status = E_NOk;
	}
	return au8_status;
}
