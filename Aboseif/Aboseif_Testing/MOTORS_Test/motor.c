/*
 * motor.c
 *
 * Created: 2020-02-17 6:38:16 PM
 *  Author: EbrahimOseif
 */ 


/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/


#include "motor.h"




uint8_t gu8_initState[MOTORS_NUMBER]= { NOT_INITIALIZED};

/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/


/***********************************************************************
 * Func			: Motor_Init
 * Input		: motorNumber
 *	  	  		  #def
 *	  	  		  number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: ERROR_STATUS
 * Description	: Initialize (Enable, IN1, IN2) pins as digital outputs.
 ***********************************************************************/
ERROR_STATUS Motor_Init(uint8_t u8_Motor_Number)
{
	ERROR_STATUS u8_status = E_OK;
	
	DIO_Cfg_s Motor_En, Motor_Dir1, Motor_Dir2;
	
	switch(u8_Motor_Number)
	{
		case MOTOR_1:
		
			Motor_En.GPIO = M1EN_GPIO;
			Motor_En.pins = M1EN_BIT;
			Motor_En.dir = OUTPUT;
			DIO_init(&Motor_En);
			
			Motor_Dir1.GPIO = M1D1_GPIO;
			Motor_Dir1.pins = M1D1_BIT;
			Motor_Dir1.dir = OUTPUT;
			DIO_init(&Motor_Dir1);
			
			Motor_Dir2.GPIO = M1D2_GPIO;
			Motor_Dir2.pins = M1D2_BIT;
			Motor_Dir2.dir = OUTPUT;
			DIO_init(&Motor_Dir2);
			gu8_initState[MOTOR_1] = INITIALIZED;
			break;
			
		case MOTOR_2:
		
			Motor_En.GPIO = M2EN_GPIO;
			Motor_En.pins = M2EN_BIT;
			Motor_En.dir = OUTPUT;
			DIO_init(&Motor_En);
			
			Motor_Dir1.GPIO = M2D1_GPIO;
			Motor_Dir1.pins = M2D1_BIT;
			Motor_Dir1.dir = OUTPUT;
			DIO_init(&Motor_Dir1);
			
			Motor_Dir2.GPIO = M2D2_GPIO;
			Motor_Dir2.pins = M2D2_BIT;
			Motor_Dir2.dir = OUTPUT;
			DIO_init(&Motor_Dir2);
			gu8_initState[MOTOR_2] = INITIALIZED;

			break;
		default:
			u8_status = E_NOK;
	}
	return u8_status;
}
/******************************************************************************************
 * Fun		 : Motor_Direction
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2

			   @param Motor_Direction
			   #define
			   Stop, Forward, Backword
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Controls the motor direction from getting the motor number and the direction.
*******************************************************************************************/
ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction)
{
	ERROR_STATUS u8_status = E_OK;
	
	switch(Motor_Number)
	{
		case MOTOR_1:
			switch(Motor_Direction)
			{
				case MOTOR_FORWARD:
					DIO_Write(M1D1_GPIO, M1D1_BIT, HIGH);
					DIO_Write(M1D2_GPIO, M1D2_BIT, LOW);
					break;
				case MOTOR_BACKWARD:
					DIO_Write(M1D1_GPIO, M1D1_BIT, LOW);
					DIO_Write(M1D2_GPIO, M1D2_BIT, HIGH);
					break;
				case MOTOR_STOP:
					DIO_Write(M1D1_GPIO, M1D1_BIT, LOW);
					DIO_Write(M1D2_GPIO, M1D2_BIT, LOW);
					break;
				default:
					break;
			}
			break;
			
		case MOTOR_2:
		
			switch(Motor_Direction)
			{
				case MOTOR_FORWARD:
					DIO_Write(M2D1_GPIO, M2D1_BIT, HIGH);
					DIO_Write(M2D2_GPIO, M2D2_BIT, LOW);
					break;
				case MOTOR_BACKWARD:
					DIO_Write(M2D1_GPIO, M2D1_BIT, LOW);
					DIO_Write(M2D2_GPIO, M2D2_BIT, HIGH);
					break;
				case MOTOR_STOP:
					DIO_Write(M2D1_GPIO, M2D1_BIT, LOW);
					DIO_Write(M2D2_GPIO, M2D2_BIT, LOW);
					break;
				default:
					break;
			}
			break;
			
		default:
			u8_status = E_NOK;
	}
	return u8_status;
}
/******************************************************************************
 * Fun		 : Motor_Start
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Start the motor.
*******************************************************************************/
ERROR_STATUS Motor_Start(uint8_t u8_Motor_Number, uint8_t u8_Mot_Speed)
{
	ERROR_STATUS u8_status = E_OK;
	
	Pwm_Cfg_s a_Motor_PWM;
	
	switch(u8_Motor_Number)
	{
		case MOTOR_1:
			a_Motor_PWM.Channel = PWM_CH1A;
			Pwm_Init(&a_Motor_PWM);
			Pwm_Start(a_Motor_PWM.Channel, u8_Mot_Speed, MOTOR_FREQUENCY);
			break;
			
		case MOTOR_2:
			a_Motor_PWM.Channel = PWM_CH1B;
			Pwm_Init(&a_Motor_PWM);
			Pwm_Start(a_Motor_PWM.Channel, u8_Mot_Speed, MOTOR_FREQUENCY);
		
		default:
			u8_status = E_NOK;
	}
	return u8_status;
}

/**
 * Fun		 : Motor_Stop
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: stop the motor.
*/


ERROR_STATUS Motor_Stop(uint8_t Motor_Number)
{
	ERROR_STATUS u8_status = E_OK;
	
	switch(Motor_Number)
	{
		case MOTOR_1:
		          Pwm_Stop(PWM_CH1A);
					break;

		case MOTOR_2:
					Pwm_Stop(PWM_CH1B);
					break;
					
		default:
				u8_status=E_NOK;
	}
	return u8_status;
}




 /**
 * Func			: Motor_GetStatus
 * Input		: Motor_Number
 *	  	  		 #def
 *	  	  		 number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: Initialization_STATUS
 * Description	: Returns status of the motor whether intialized or not
 */
ERROR_STATUS Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status)
{
	
	 
	ERROR_STATUS u8_status = E_OK;
	switch(Motor_Number)
	{
		case MOTOR_1:
				*Mot_status = gu8_initState[MOTOR_1];
		break;

		case MOTOR_2:
				*Mot_status = gu8_initState[MOTOR_1];
		break;

		default:
				u8_status=E_NOK;
	}
	return u8_status;
}

