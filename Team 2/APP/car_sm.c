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

/***************************************************************************/


/******************************global variables*****************************/

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
	uint8_t u8_status;
	uint16_t Distance;
	uint8_t u8_state;
	u8_status |= Us_Trigger();
	u8_status |= Us_GetDistance(&Distance);

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

	switch(u8_state)
	{
		case NEAR:
			u8_status |= Steering_SteerCar(CAR_FORWARD,LOW_SPEED);
			break;
		case INTERMEDIATE:
			u8_status |= Steering_SteerCar(CAR_RIGHT,FULL_SPEED);
			softwareDelayMs(DELAY_FOR_TURN);
			break;
		case FAR:
			u8_status |= Steering_SteerCar(CAR_BACKWARD,LOW_SPEED);
			break;
	}

	softwareDelayMs(DELAY_FOR_GET_NEW_READING);

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
