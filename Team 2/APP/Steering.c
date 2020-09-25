/*
 ============================================================================
 Name        : steering.c
 Author      : Muhammed Gamal
 Description : this file include the functions implementation of the steering application
 ============================================================================
 */


/*********************************includes**********************************/
#include "Steering.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define INITIAL_SPEED 0
/***************************************************************************/


/******************************global variables*****************************/

/***************************************************************************/



/************************************************************************************
* Function Name: Steering_Init
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: Initiates the module
************************************************************************************/
ERROR_STATUS Steering_Init(void)
{
	ERROR_STATUS u8_status;
	u8_status=Motor_Init(MOTOR_1);
	u8_status=Motor_Init(MOTOR_2);
	u8_status=Motor_Start(MOTOR_1,INITIAL_SPEED);
	u8_status=Motor_Start(MOTOR_2,INITIAL_SPEED);
	return u8_status;
}



/************************************************************************************
* Function Name: Steering_SteerCar
* Parameters (in): carDirection: The direction of the car from the predefined states of the module.
* 	               speed: The speed of the car from 0% to 100%
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: This function controls the command and the speed of the car
************************************************************************************/
ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed)
{
	ERROR_STATUS u8_status;
	switch(Steering_CarCmd)
	{
	case CAR_STOP:
		Motor_Stop(MOTOR_1);
		Motor_Stop(MOTOR_2);
		u8_status=E_ok;
		break;

	case CAR_FORWARD:
		Motor_Direction(MOTOR_1, MOTOR_FORWARD);
		Motor_Direction(MOTOR_2, MOTOR_FORWARD);
		Motor_SpeedUpdate(MOTOR_1_2,speed);
		u8_status=E_ok;
		break;

	case CAR_BACKWARD:
		Motor_Direction(MOTOR_1, MOTOR_BACKWARD);
		Motor_Direction(MOTOR_2, MOTOR_BACKWARD);
		Motor_SpeedUpdate(MOTOR_1_2,speed);
		u8_status=E_ok;
		break;

	case CAR_RIGHT:
		Motor_Direction(MOTOR_1, MOTOR_BACKWARD);
		Motor_Direction(MOTOR_2, MOTOR_FORWARD);
		Motor_SpeedUpdate(MOTOR_1_2,speed);
		u8_status=E_ok;
		break;

	case CAR_LEFT:
		Motor_Direction(MOTOR_1, MOTOR_FORWARD);
		Motor_Direction(MOTOR_2, MOTOR_BACKWARD);
		Motor_SpeedUpdate(MOTOR_1_2,speed);
		u8_status=E_ok;
		break;

	default:
		u8_status=E_NOk;
	}
	return u8_status;
}
