/*
* Steering.c
*
* Created: 2/18/2020 7:36:28 PM
*  Author: hazem
*/


/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "Steering.h"

/************************************************************************/
/*		      API Implementation 		        */
/************************************************************************/


ERROR_STATUS Steering_Init(void)
{
	ERROR_STATUS ERROR=E_OK;
	if(Motor_Init(MOTOR_1)!=E_OK)
	ERROR=E_NOK;
	if(Motor_Init(MOTOR_2)!=E_OK)
	ERROR=E_NOK;
	return ERROR;
}

ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed)
{
	ERROR_STATUS ERROR=E_OK;
	switch(Steering_CarCmd)
	{
		case CAR_STOP	:
                 Motor_Stop(MOTOR_1);
                 Motor_Stop(MOTOR_2);
                 Motor_Start(MOTOR_2,0);
                 Motor_Start(MOTOR_1,0);
                 break;
		case CAR_FORWARD :	
                Motor_Start(MOTOR_2,speed);
                Motor_Start(MOTOR_1,speed);
                Motor_Direction(MOTOR_1,MOTOR_FORWARD);
                Motor_Direction(MOTOR_2,MOTOR_FORWARD);
                break;  
		case CAR_BACKWARD : 
                  Motor_Start(MOTOR_2,50);
                  Motor_Start(MOTOR_1,50);
                  Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
                  Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
                  break;
		case CAR_RIGHT	:
                 Motor_Stop(MOTOR_1);
                 Motor_Start(MOTOR_2,50);
                 Motor_Direction(MOTOR_2,MOTOR_FORWARD);
                 break;
		case CAR_LEFT	:
                 Motor_Stop(MOTOR_2);
                 Motor_Start(MOTOR_1,50);
                 Motor_Direction(MOTOR_1,MOTOR_FORWARD);
		default:
		  ERROR=E_NOK;
		  break;
		
	}
	return ERROR;
}
