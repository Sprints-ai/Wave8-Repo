/*
 * Steering.c
 *
 *  Created on: Feb 18, 2020
 *      Author: Youssef Harby
 */


/*- INCLUDES -----------------------------------------------*/

#include "Steering.h"
#include "../ECUAL/motor.h"

/*- PREPROCESSOR MACROS ------------------------------------*/

#define STEERING_NOT_INITIALIZED			0
#define STEERING_INITIALIZED				1

/*- STATIC GLOBAL VARIABLES --------------------------------*/

uint8_t gu8_Us_InitStatus = STEERING_NOT_INITIALIZED;


/*- APIs IMPLEMENTATION ------------------------------------*/

ERROR_STATUS Steering_Init(void)
{
	sint8_t as8_Ret = STEERING_E_OK;

	if(gu8_Us_InitStatus == STEERING_NOT_INITIALIZED)
	{
		/* Initialization of the required motors */
		as8_Ret = Motor_Init(MOTOR_1 | MOTOR_2);

		gu8_Us_InitStatus = STEERING_INITIALIZED;
	}else
	{
		as8_Ret = STEERING_E_ALREADY_INIT;
	}

	return as8_Ret;
}

ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed)
{
	sint8_t as8_Ret = STEERING_E_OK;

	if(gu8_Us_InitStatus == STEERING_INITIALIZED)
	{
		/* A switch case to determine the required state of the car motors */
		switch(Steering_CarCmd)
		{
		case CAR_STOP:
			/* Stop the car in the case of stop */
			if(speed > 100)
			{
				as8_Ret = STEERING_E_INVALID_SPEED;
			}else
			{
				as8_Ret = Motor_Stop(MOTOR_1 | MOTOR_2);
			}
			break;
		case CAR_FORWARD:
			if(speed > 100)
			{
				as8_Ret = STEERING_E_INVALID_SPEED;
			}else
			{
				/* The two motors are driven in the same direction (forward) */
				as8_Ret = Motor_Direction((MOTOR_1 | MOTOR_2), MOTOR_FORWARD);
				as8_Ret = Motor_Start((MOTOR_1 | MOTOR_2), speed);
			}
			break;
		case CAR_BACKWARD:
			if(speed > 100)
			{
				as8_Ret = STEERING_E_INVALID_SPEED;
			}else
			{
				/* The two motors are driven in the other direction (backward) */
				as8_Ret = Motor_Direction((MOTOR_1 | MOTOR_2), MOTOR_BACKWARD);
				as8_Ret = Motor_Start((MOTOR_1 | MOTOR_2), speed);
			}
			break;
		case CAR_RIGHT:
			if(speed > 100)
			{
				as8_Ret = STEERING_E_INVALID_SPEED;
			}else
			{
				/* The two motors are driven in different directions (right) */
				as8_Ret = Motor_Direction(MOTOR_1, MOTOR_BACKWARD);
				as8_Ret = Motor_Start(MOTOR_1, speed);
				as8_Ret = Motor_Direction(MOTOR_2, MOTOR_FORWARD);
				as8_Ret = Motor_Start(MOTOR_2, speed);
			}
			break;
		case CAR_LEFT:
			if(speed > 100)
			{
				as8_Ret = STEERING_E_INVALID_SPEED;
			}else
			{
				/* the two motors are driven in different directions (left) */
				as8_Ret = Motor_Direction(MOTOR_1, MOTOR_FORWARD);
				as8_Ret = Motor_Start(MOTOR_1, speed);
				as8_Ret = Motor_Direction(MOTOR_2, MOTOR_BACKWARD);
				as8_Ret = Motor_Start(MOTOR_2, speed);
			}
			break;
		default:
			as8_Ret = STEERING_E_INVALID_CAR_CMD;
			break;
		}
	}else
	{
		as8_Ret = STEERING_E_NOT_INIT;
	}

	return as8_Ret;
}
