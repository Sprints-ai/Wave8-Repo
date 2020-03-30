/*
 * Steering.c
 *
 * Created: 2/16/2020 4:31:26 PM
 *  Author: Reem
 */ 
#include "../includes/Steering.h"

/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */

ERROR_STATUS Steering_Init(void){
	ERROR_STATUS ERR;
	
	ERR= Motor_Init(MOTOR_1);
	if (ERR == E_OK)
	{
		ERR= Motor_Init(MOTOR_2);
	}
	
	return ERR;
}

/**
 * Input: 
 * 	carDirection: The direction of the car from the predefined states of the module.
 * 	speed: The speed of the car from 0% to 100%.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function controls the command and the speed of the car.
 * 							
 */
ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed){
	ERROR_STATUS ERR;
	switch(Steering_CarCmd){
		case CAR_FORWARD:
		
		ERR = Motor_Direction(MOTOR_1,MOTOR_FORWARD);
		if (ERR == E_OK)
		{
			ERR = Motor_Direction(MOTOR_2,MOTOR_FORWARD);
		}
		
		break;
		
		case CAR_BACKWARD:

		ERR = Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
		if (ERR == E_OK)
		{
			ERR = Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
		}
		
		
		break;
		
		case CAR_LEFT:
		
		ERR = Motor_Direction(MOTOR_1,MOTOR_FORWARD);
		if (ERR == E_OK)
		{
			ERR = Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
		}
		break;
		
		case CAR_RIGHT:

		ERR = Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
		if (ERR == E_OK)
		{
			ERR = Motor_Direction(MOTOR_2,MOTOR_FORWARD);
		}
		break;
		
		case CAR_STOP:
		ERR = Motor_Direction(MOTOR_1,MOTOR_STOP);
		if (ERR == E_OK)
		{
			ERR = Motor_Direction(MOTOR_2,MOTOR_STOP);
		}
		break;
		
		default:
		ERR =  E_INVALID_PARAMETER;
		break;
	}
	if (ERR ==E_OK)
	{
		ERR = Motor_Start(MOTOR_1,speed);
		if (ERR ==E_OK)
		{
			ERR = Motor_Start(MOTOR_2,speed);
		}
	}
	return ERR;
}