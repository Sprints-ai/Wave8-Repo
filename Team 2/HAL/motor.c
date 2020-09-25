/*
 ============================================================================
 Name        : dcMotor.c
 Author      : Muhammed Gamal
 Description : this file include the implementation of the motor driver
 ============================================================================
 */


/*********************************includes**********************************/
#include "motor.h"
/***************************************************************************/


/*********************************definitions*******************************/

/***************************************************************************/


/******************************global variables*****************************/

/***************************************************************************/



/************************************************************************************
* Function Name: Motor_Init
* Parameters (in): motorNumber
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: Initialize (Enable, IN1, IN2) pins as digital outputs
************************************************************************************/
ERROR_STATUS Motor_Init(uint8_t Motor_Number)
{
	ERROR_STATUS u8_status;
	switch(Motor_Number)
	{
		case(MOTOR_1):
				u8_status=E_ok;
				DIO_Cfg_s Motor1_init=
				{
						Motor1_init.GPIO=MOTORS_PORT,
						Motor1_init.pins=MOTOR_EN_1_BIT | MOTOR_OUT_1A_BIT | MOTOR_OUT_1B_BIT,
						Motor1_init.dir=OUTPUT,
				};
				DIO_init (&Motor1_init);
				DIO_Write (MOTORS_PORT, MOTOR_EN_1_BIT | MOTOR_OUT_1A_BIT | MOTOR_OUT_1B_BIT, LOW);
				break;

		case(MOTOR_2):
				u8_status=E_ok;
				DIO_Cfg_s Motor2_init=
				{
						Motor2_init.GPIO=MOTORS_PORT,
						Motor2_init.pins=MOTOR_EN_2_BIT | MOTOR_OUT_2A_BIT | MOTOR_OUT_2B_BIT,
						Motor2_init.dir=OUTPUT,
				};
				DIO_init (&Motor2_init);
				DIO_Write (MOTORS_PORT, MOTOR_EN_2_BIT | MOTOR_OUT_2A_BIT | MOTOR_OUT_2B_BIT, LOW);
				break;

		default:
			u8_status=E_NOk;
	}
	return u8_status;
}



/************************************************************************************
* Function Name: Motor_Direction
* Parameters (in): motorNumber
*                  Motor_Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: Controls the motor direction from getting the motor number and the direction
************************************************************************************/
ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction)
{
	ERROR_STATUS u8_status;
	DIO_Cfg_s Motor1_DirInit=
	{
		Motor1_DirInit.GPIO=MOTORS_PORT,
		Motor1_DirInit.pins=MOTOR_EN_1_BIT | MOTOR_OUT_1A_BIT | MOTOR_OUT_1B_BIT,
		Motor1_DirInit.dir=OUTPUT,
	};
	DIO_Cfg_s Motor2_DirInit=
	{
		Motor2_DirInit.GPIO=MOTORS_PORT,
		Motor2_DirInit.pins=MOTOR_EN_2_BIT | MOTOR_OUT_2A_BIT | MOTOR_OUT_2B_BIT,
		Motor2_DirInit.dir=OUTPUT,
	};
	switch(Motor_Number)
	{
		case(MOTOR_1):
				u8_status=E_ok;
				DIO_init (&Motor1_DirInit);
				switch(Motor_Direction)
				{
				case MOTOR_STOP:
					DIO_Write (MOTORS_PORT, MOTOR_OUT_1A_BIT, LOW);
					DIO_Write (MOTORS_PORT, MOTOR_OUT_1B_BIT, LOW);
					u8_status=E_ok;
					break;

				case MOTOR_FORWARD:
					DIO_Write (MOTORS_PORT, MOTOR_OUT_1A_BIT, LOW);
					DIO_Write (MOTORS_PORT, MOTOR_OUT_1B_BIT, HIGH);
					u8_status=E_ok;
					break;

				case MOTOR_BACKWARD:
					DIO_Write (MOTORS_PORT, MOTOR_OUT_1A_BIT, HIGH);
					DIO_Write (MOTORS_PORT, MOTOR_OUT_1B_BIT, LOW);
					u8_status=E_ok;
					break;

				default:
					u8_status=E_NOk;
				}
				break;

		case(MOTOR_2):
				u8_status=E_ok;
				DIO_init (&Motor2_DirInit);
				switch(Motor_Direction)
				{
				case MOTOR_STOP:
					DIO_Write (MOTORS_PORT, MOTOR_OUT_2A_BIT, LOW);
					DIO_Write (MOTORS_PORT, MOTOR_OUT_2B_BIT, LOW);
					u8_status=E_ok;
					break;

				case MOTOR_FORWARD:
					DIO_Write (MOTORS_PORT, MOTOR_OUT_2A_BIT, LOW);
					DIO_Write (MOTORS_PORT, MOTOR_OUT_2B_BIT, HIGH);
					u8_status=E_ok;
					break;

				case MOTOR_BACKWARD:
					DIO_Write (MOTORS_PORT, MOTOR_OUT_2A_BIT, HIGH);
					DIO_Write (MOTORS_PORT, MOTOR_OUT_2B_BIT, LOW);
					u8_status=E_ok;
					break;

				default:
					u8_status=E_NOk;
				}
				break;

		default:
			u8_status=E_NOk;
	}
	return u8_status;
}



/************************************************************************************
* Function Name: Motor_Start
* Parameters (in): motorNumber
*                  Mot_Speed
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: Start the motor
************************************************************************************/
ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed)
{
	ERROR_STATUS u8_status;
	Pwm_Cfg_s instans={PWM_CH1A_CH1B,PWM_PRESCALER_256};
	Pwm_Init(&instans);
	switch(Motor_Number)
	{
	case MOTOR_1:
		Pwm_Start(PWM_CH1A,Mot_Speed,T1_PHASE_CORRECT_FREQUENCY_50HZ);
		u8_status=E_ok;
		break;

	case MOTOR_2:
		Pwm_Start(PWM_CH1B,Mot_Speed,T1_PHASE_CORRECT_FREQUENCY_50HZ);
		u8_status=E_ok;
		break;

	case (MOTOR_1_2):
		Pwm_Start(PWM_CH1A_CH1B,Mot_Speed,T1_PHASE_CORRECT_FREQUENCY_50HZ);
		u8_status=E_ok;
		break;

	default:
		u8_status=E_NOk;
	}
	return u8_status;
}



/************************************************************************************
* Function Name: Motor_SpeedUpdate
* Parameters (in): motorNumber
*                  Speed
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: Controls the motor speed from getting the motor number and the speed
************************************************************************************/
ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed)
{
	ERROR_STATUS u8_status;
	Pwm_Cfg_s instans={PWM_CH1A_CH1B,PWM_PRESCALER_256};
	Pwm_Init(&instans);
	switch(Motor_Number)
	{
	case MOTOR_1:
		Pwm_Start(PWM_CH1A,Speed,T1_PHASE_CORRECT_FREQUENCY_50HZ);
		u8_status=E_ok;
		break;

	case MOTOR_2:
		Pwm_Start(PWM_CH1B,Speed,T1_PHASE_CORRECT_FREQUENCY_50HZ);
		u8_status=E_ok;
		break;

	case (MOTOR_1_2):
		Pwm_Start(PWM_CH1A_CH1B,Speed,T1_PHASE_CORRECT_FREQUENCY_50HZ);
		u8_status=E_ok;
		break;

	default:
		u8_status=E_NOk;
	}
	return u8_status;
}



/************************************************************************************
* Function Name: Motor_Stop
* Parameters (in): motorNumber
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: stop the motor
************************************************************************************/
ERROR_STATUS Motor_Stop(uint8_t Motor_Number)
{
	ERROR_STATUS u8_status;
	Pwm_Cfg_s instans={PWM_CH1A_CH1B,PWM_PRESCALER_256};
	Pwm_Init(&instans);
	switch(Motor_Number)
	{
	case MOTOR_1:
		Pwm_Stop(PWM_CH1A);
		u8_status=E_ok;
		break;

	case MOTOR_2:
		Pwm_Stop(PWM_CH1B);
		u8_status=E_ok;
		break;
	case (MOTOR_1_2):
		Pwm_Stop(PWM_CH1A_CH1B);
		u8_status=E_ok;
		break;
	default:
		u8_status=E_NOk;
	}
	return u8_status;
}



/************************************************************************************
* Function Name: Motor_GetStatus
* Parameters (in): motorNumber
*                  Mot_status
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: Returns status of the motor whether initialized or not
************************************************************************************/
ERROR_STATUS Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status)
{
	ERROR_STATUS u8_status;
	switch(Motor_Number)
	{
	case MOTOR_1:

		u8_status=E_ok;
		break;

	case MOTOR_2:

		u8_status=E_ok;
		break;

	default:
		u8_status=E_NOk;
	}
	return u8_status;
}


/******************************************************************************************/
