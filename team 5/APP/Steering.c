/*
 * Steering.c
 *
 * Created: 2/18/2020 7:32:11 PM
 *  Author: Joo
 */


/************************************************************************/
/*								Includes                               */
/************************************************************************/

#include "Steering.h"
#include "../ECUAl/motor.h"


/************************************************************************/
/*							API's Implementation                        */
/************************************************************************/

/**
 * Input: nothing
 * Output: nothing
 * In/Out:	nothing
 * Return: The error status of the function.
 * Description: Initiates the module , initialize MOTOR_1 & MOTOR_2
 *
 */

ERROR_STATUS Steering_Init(void)
{
	ERROR_STATUS as16_state_error = E_OK;

	as16_state_error |= Motor_Init(MOTOR_1);
	as16_state_error |= Motor_Init(MOTOR_2);

	return as16_state_error;
}


/**
 * Input:
 * 	carDirection: The direction of the car from the predefined states of the module:
																					-> car_STOP
																					->CAR_FOTWARD
																					->CAR_BACKWARD
																					->CAR_RIGHT
																					->CAR_LEFT
 * 	speed: The speed of the car from 0% to 100%.
 * Output: nothing
 * In/Out:
 * Return: The error status of the function.
 * Description: This function controls the command and the speed of the car.
 *
 */

ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed)
{
	ERROR_STATUS as16_state_error = E_OK;

	/****************************  set motor direction ********************************************/

	switch(Steering_CarCmd)
	{
	case CAR_STOP:
		as16_state_error |= Motor_Direction(MOTOR_1, MOTOR_STOP);
		as16_state_error |= Motor_Direction(MOTOR_2, MOTOR_STOP);
		break;
	case CAR_FORWARD:
		as16_state_error |= Motor_Direction(MOTOR_1, MOTOR_FORWARD);
		as16_state_error |= Motor_Direction(MOTOR_2, MOTOR_FORWARD);
		break;
	case CAR_BACKWARD:
		as16_state_error |= Motor_Direction(MOTOR_1, MOTOR_BACKWARD);
		as16_state_error |= Motor_Direction(MOTOR_2, MOTOR_BACKWARD);
		break;
	case CAR_RIGHT:
		as16_state_error |= Motor_Direction(MOTOR_1, MOTOR_FORWARD);
		as16_state_error |= Motor_Direction(MOTOR_2, MOTOR_BACKWARD);
		break;
	case CAR_LEFT:
		as16_state_error |= Motor_Direction(MOTOR_1, MOTOR_BACKWARD);
		as16_state_error |= Motor_Direction(MOTOR_2, MOTOR_FORWARD);
		break;
	default:
		as16_state_error |= E_NOK;
	}

	/****************************  start motor direction ********************************************/

	as16_state_error |= Motor_Start(MOTOR_1, speed);
	as16_state_error |= Motor_Start(MOTOR_2, speed);

	return as16_state_error;
}
