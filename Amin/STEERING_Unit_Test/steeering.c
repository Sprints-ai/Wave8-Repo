#include "steering.h"
#define ERROR 1
#define NO_ERROR 0

 /*Describtion: this function initialize the steering*/
ERROR_STATUS Steering_Init(void)
{
	uint8 error=NO_ERROR;

	error=Motor_Init(MOTOR_1);
	error=Motor_Init(MOTOR_2);
	error=Motor_Start(MOTOR_1, 50);
	error=Motor_Start(MOTOR_2, 50);
	return error;
}


/*Describtion: this function initialize the steering with specific direction (forward,backward,left,right)*/
ERROR_STATUS Steering_SteerCar(uint8 carDirection, uint8 speed)
{
    uint8 eror=NO_ERROR;
	switch(carDirection)
	{
	case (CAR_STOP):
		Motor_Stop(MOTOR_1);
		Motor_Stop(MOTOR_2);
		return NO_ERROR;
		break;
	case (CAR_FORWARD):
		Motor_Direction(MOTOR_1, MOTOR_FORWARD);
		Motor_Direction(MOTOR_2, MOTOR_FORWARD);
		Motor_Start(MOTOR_1, speed);
		Motor_Start(MOTOR_2, speed);
		return NO_ERROR;
		break;
	case (CAR_BACKWARD):
		Motor_Direction(MOTOR_1, MOTOR_BACKWARD);
		Motor_Direction(MOTOR_2, MOTOR_BACKWARD);
		Motor_Start(MOTOR_1, speed);
		Motor_Start(MOTOR_2, speed);
		return NO_ERROR;
		break;
	case (CAR_RIGHT):
		Motor_Direction(MOTOR_1, MOTOR_FORWARD);
		Motor_Direction(MOTOR_2, MOTOR_STOP);
		Motor_Start(MOTOR_1, speed);
		Motor_Start(MOTOR_2, speed);
		return NO_ERROR;
		break;
	case (CAR_LEFT):
		Motor_Direction(MOTOR_1, MOTOR_STOP);
		Motor_Direction(MOTOR_2, MOTOR_FORWARD);
		Motor_Start(MOTOR_1, speed);
		Motor_Start(MOTOR_2, speed);
		return NO_ERROR;
		break;
	}
	return ERROR;
}
