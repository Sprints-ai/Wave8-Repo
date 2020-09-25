#include "std_types.h"
#include "DIO.h"
#include "PWM.h"
#include "Motor.h"
#include "Motor_cfg.h"

/*Initialization indication flags*/
static uint8_t gu8_motor1_init_flag = 0;
static uint8_t gu8_motor2_init_flag = 0;

ERROR_STATUS Motor_Init(uint8_t Motor_Number)
{
	ERROR_STATUS err_var = E_OK;
	
	/*Initialization of motor given ID pins as output*/	
	switch(Motor_Number)
	{
		case MOTOR_1:
			DIO_init (MOTOR1_GPIO_EN_PORT, MOTOR1_GPIO_EN_PIN | MOTOR1_GPIO_PINA | MOTOR1_GPIO_PINB, OUTPUT);
			gu8_motor1_init_flag++;
			break;

		case MOTOR_2:
			DIO_init (MOTOR2_GPIO_EN_PORT, MOTOR2_GPIO_EN_PIN | MOTOR2_GPIO_PINA | MOTOR2_GPIO_PINB, OUTPUT);
			gu8_motor2_init_flag++;		
			break;
			
		default: err_var = E_NOK;	
			
	}
	return err_var;
}

ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Mot_Direction)
{
	ERROR_STATUS err_var = E_OK;
	
	/*Setting direction for motor given ID as forward or backward*/
	switch(Motor_Number)
	{
		case MOTOR_1:
			switch(Mot_Direction)
			{
				case MOTOR_FORWARD:
					DIO_Write(MOTOR1_GPIO_PORT, MOTOR1_GPIO_PINA, HIGH);
					DIO_Write(MOTOR1_GPIO_PORT, MOTOR1_GPIO_PINB, LOW);					
					break;

				case MOTOR_BACKWARD:
					DIO_Write(MOTOR1_GPIO_PORT, MOTOR1_GPIO_PINA, LOW);
					DIO_Write(MOTOR1_GPIO_PORT, MOTOR1_GPIO_PINB, HIGH);
					break;

				case MOTOR_STOP:
					DIO_Write(MOTOR1_GPIO_PORT, MOTOR1_GPIO_PINA, LOW);
					DIO_Write(MOTOR1_GPIO_PORT, MOTOR1_GPIO_PINB, LOW);
					break;
			}
			break;

		case MOTOR_2:
			switch(Mot_Direction)
			{
				case MOTOR_FORWARD:
				DIO_Write(MOTOR2_GPIO_PORT, MOTOR2_GPIO_PINA, HIGH);
				DIO_Write(MOTOR2_GPIO_PORT, MOTOR2_GPIO_PINB, LOW);
				break;

				case MOTOR_BACKWARD:
				DIO_Write(MOTOR2_GPIO_PORT, MOTOR2_GPIO_PINA, LOW);
				DIO_Write(MOTOR2_GPIO_PORT, MOTOR2_GPIO_PINB, HIGH);
				break;

				case MOTOR_STOP:
				DIO_Write(MOTOR2_GPIO_PORT, MOTOR2_GPIO_PINA, LOW);
				DIO_Write(MOTOR2_GPIO_PORT, MOTOR2_GPIO_PINB, LOW);
				break;
			}
			break;

		default: err_var = E_NOK;
	}
	
	return err_var;
}

ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Motor_Speed)
{
	ERROR_STATUS err_var = E_OK;

	/*Starting motor given ID with specified speed*/
	switch(Motor_Number)
	{
		case MOTOR_1:
			pwm_Init(MOTOR1_PWM_CHANNEL);
			pwm_Start(MOTOR1_PWM_CHANNEL, Motor_Speed, MOTOR1_PWM_FREQ);
			break;

		case MOTOR_2:
			pwm_Init(MOTOR2_PWM_CHANNEL);
			pwm_Start(MOTOR2_PWM_CHANNEL, Motor_Speed, MOTOR2_PWM_FREQ);
			break;
			
		default: err_var = E_NOK;	
	}
	
	return err_var;
}

ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Motor_Speed)
{
	ERROR_STATUS err_var = E_OK;

	/*Updating the speed of motor given ID*/
	switch(Motor_Number)
	{
		case MOTOR_1:
			pwm_Update(MOTOR1_PWM_CHANNEL, Motor_Speed, MOTOR1_PWM_FREQ);
			break;

		case MOTOR_2:
			pwm_Update(MOTOR2_PWM_CHANNEL, Motor_Speed, MOTOR2_PWM_FREQ);
			break;
			
		default: err_var = E_NOK;	
	}
	
	return err_var;
	
}

ERROR_STATUS Motor_Stop(uint8_t Motor_Number)
{
	ERROR_STATUS err_var = E_OK;

	/*Stopping the motor given ID*/	
	switch(Motor_Number)
	{
		case MOTOR_1:
			pwm_Stop(MOTOR1_PWM_CHANNEL);
			DIO_Write(MOTOR1_GPIO_PORT, MOTOR1_GPIO_PINA, LOW);
			DIO_Write(MOTOR1_GPIO_PORT, MOTOR1_GPIO_PINB, LOW);
			break;

		case MOTOR_2:
			pwm_Stop(MOTOR2_PWM_CHANNEL);
			DIO_Write(MOTOR2_GPIO_PORT, MOTOR2_GPIO_PINA, LOW);
			DIO_Write(MOTOR2_GPIO_PORT, MOTOR2_GPIO_PINB, LOW);
			break;
			
		default: err_var = E_NOK;	
	}
	
	return err_var;	
}

ERROR_STATUS Motor_GetStatus(uint8_t Motor_Number, uint8_t* au8_Motor_Status)
{
	ERROR_STATUS err_var = E_OK;
	
	if (au8_Motor_Status != NULL)
	{
		/*Getting the status of the given motor ID whether it's initialized or not*/
		switch(Motor_Number)
		{
			case MOTOR_1:
				if (gu8_motor1_init_flag)
				{
					*au8_Motor_Status = MOTOR1_INIT_DONE;
				} 
				else
				{
					*au8_Motor_Status = MOTOR1_INIT_NOT_DONE;
				}
				break;

			case MOTOR_2:
				if (gu8_motor2_init_flag)
				{
					*au8_Motor_Status = MOTOR2_INIT_DONE;
				}
				else
				{
					*au8_Motor_Status = MOTOR2_INIT_NOT_DONE;
				}
				break;
			
			default: err_var = E_NOK;	
		}			
	} 
	else
	{
		/*The used pointer is NULL*/
		err_var = E_NOK;
	}
	
	return err_var;		
}
