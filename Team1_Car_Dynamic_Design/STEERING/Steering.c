/************************************************************************/
/*                            Includes                                  */
/************************************************************************/

#include "std_types.h"
#include "Motor.h"
#include "Steering.h"

/*Desired motor speed*/
#define MOTOR1_SPEED	(255)
#define MOTOR2_SPEED	(255)

/************************************************************************/
/*                          Steering functions                          */
/************************************************************************/

ERROR_STATUS Steering_Init(void)
{
	/*Error indication variables*/
	ERROR_STATUS err_var = E_OK;
	ERROR_STATUS err_1   = E_OK;
	ERROR_STATUS err_2   = E_OK;
	
	/*Initializing and starting each one of two motors with error checking*/
	err_1 = Motor_Init(MOTOR_1);
	err_1 = Motor_Init(MOTOR_2);
	err_2 = Motor_Start(MOTOR_1 , MOTOR1_SPEED);
	err_2 = Motor_Start(MOTOR_2 , MOTOR2_SPEED);
	
	/*Validating function errors*/
	if( (err_1 == E_NOK) || (err_2 == E_NOK) )
	{
		err_var = E_NOK;
	}
	else
	{
		err_var = E_OK;
	}
	
	return err_var;
}

ERROR_STATUS Steering_SteerCar(uint8_t au8_Steering_CarCmd, uint8_t au8_speed)
{
	/*Error indication variable*/
	ERROR_STATUS err_var = E_OK;
	
	/*Drives the two motors with specified user command*/
	switch(au8_Steering_CarCmd)
	{
		case CAR_STOP:
			Motor_Direction(MOTOR_1 , MOTOR_STOP);
			Motor_Direction(MOTOR_2 , MOTOR_STOP);
			break;
		
		case CAR_FORWARD:
			Motor_SpeedUpdate(MOTOR_1,au8_speed);
			Motor_Direction(MOTOR_1 , MOTOR_FORWARD);
			Motor_SpeedUpdate(MOTOR_2,au8_speed);
			Motor_Direction(MOTOR_2 , MOTOR_FORWARD);			
			break;

		case CAR_BACKWARD:
			Motor_SpeedUpdate(MOTOR_1,au8_speed);
			Motor_Direction(MOTOR_1 , MOTOR_BACKWARD);
			Motor_SpeedUpdate(MOTOR_2,au8_speed);
			Motor_Direction(MOTOR_2 , MOTOR_BACKWARD);		
			break;

		case CAR_RIGHT:
			Motor_SpeedUpdate(MOTOR_1,au8_speed);
			Motor_Direction(MOTOR_1 , MOTOR_FORWARD);
			Motor_SpeedUpdate(MOTOR_2,au8_speed);			
			Motor_Direction(MOTOR_2 , MOTOR_BACKWARD);			
			break;

		case CAR_LEFT:
			Motor_SpeedUpdate(MOTOR_1,au8_speed);
			Motor_Direction(MOTOR_1 , MOTOR_BACKWARD);
			Motor_SpeedUpdate(MOTOR_2,au8_speed);
			Motor_Direction(MOTOR_2 , MOTOR_FORWARD);
			break;

		default: err_var = E_NOK;	
	}
	return err_var;
}