/*
 * motor.c
 *
 * Created: 2/16/2020 4:22:54 PM
 *  Author: Reem
 */ 
#include "../includes/motor.h"
#include "../includes/motor_Cfg.h"

/**
 * Func			: Motor_Init
 * Input		: motorNumber
 *	  	  		  #def
 *	  	  		  number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: ERROR_STATUS
 * Description	: Initialize (Enable, IN1, IN2) pins as digital outputs.
 */
ERROR_STATUS Motor_Init(uint8_t Motor_Number){
	DIO_Cfg_s astr_dioCfg;
	Pwm_Cfg_s astr_pwmCfg;
	switch(Motor_Number){
		case MOTOR_1:
			
			//Set the direction of the motor enable to output
			astr_dioCfg.GPIO=MOTOR1_EN_PORT;
			astr_dioCfg.pins=MOTOR1_EN_PIN;
			astr_dioCfg.dir=OUTPUT;
			
			DIO_init(&astr_dioCfg);
			
			//Set the direction of the motor directions to output
			
			astr_dioCfg.GPIO=MOTOR_OUT_1A_GPIO;
			astr_dioCfg.pins=MOTOR_OUT_1A_BIT;
			astr_dioCfg.dir=OUTPUT;
			
			DIO_init(&astr_dioCfg);
			
			astr_dioCfg.GPIO=MOTOR_OUT_1B_GPIO;
			astr_dioCfg.pins=MOTOR_OUT_1B_BIT;
			astr_dioCfg.dir=OUTPUT;
			
			DIO_init(&astr_dioCfg);
			
			// initializing the pwm
			
			astr_pwmCfg.Channel = PWM_CH1A;
			astr_pwmCfg.Prescaler =PWM_PRESCALER_1024;
			Pwm_Init(&astr_pwmCfg);
			
			
		break;
		
		case MOTOR_2:
			//Set the direction of the motor enable to output
			astr_dioCfg.GPIO=MOTOR2_EN_PORT;
			astr_dioCfg.pins=MOTOR2_EN_PIN;
			astr_dioCfg.dir=OUTPUT;
			
			DIO_init(&astr_dioCfg);
			
			//Set the direction of the motor directions to output
			
			astr_dioCfg.GPIO=MOTOR_OUT_2A_GPIO;
			astr_dioCfg.pins=MOTOR_OUT_2A_BIT;
			astr_dioCfg.dir=OUTPUT;
			
			DIO_init(&astr_dioCfg);
			
			astr_dioCfg.GPIO=MOTOR_OUT_2B_GPIO;
			astr_dioCfg.pins=MOTOR_OUT_2B_BIT;
			astr_dioCfg.dir=OUTPUT;
			
			DIO_init(&astr_dioCfg);
			
			// initializing the pwm
			
			astr_pwmCfg.Channel = PWM_CH1B;
			astr_pwmCfg.Prescaler =PWM_PRESCALER_1024;
			Pwm_Init(&astr_pwmCfg);
			
		break;
		
		default:
		return E_INVALID_PARAMETER;
		break;
	}
	return E_OK;
}

/**
 * Fun		 : Motor_Direction
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2

			   @param Motor_Direction
			   #define
			   Stop, Forward, Backward
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: Controls the motor direction from getting the motor number and the direction.
*/
ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction){
	switch(Motor_Number){
		//in case choosing motor 1
		case MOTOR_1:
			switch(Motor_Direction){
				//in case stop the motor
				case MOTOR_STOP:
				DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
				DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
				break;
				
				//in case move the motor forward
				case MOTOR_FORWARD:
				DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,HIGH);
				DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
				break;
				
				//in case move the motor backward
				case MOTOR_BACKWARD:
				DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
				DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,HIGH);
				break;
				
				default:
				return E_INVALID_PARAMETER;
				break;
			}
		break;
		
		case MOTOR_2:
		switch(Motor_Direction){
				//in case stop the motor
				case MOTOR_STOP:
				DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
				DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
				break;
			
				//in case move the motor forward
				case MOTOR_FORWARD:
				DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,HIGH);
				DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
				break;
			
				//in case move the motor backward
				case MOTOR_BACKWARD:
				DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
				DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,HIGH);
				break;
			
				default:
				return E_INVALID_PARAMETER;
				break;
			}
		
		break;
		
		default:
		return E_INVALID_PARAMETER;
		break;
	}
	return E_OK;
}

/**
 * Fun		 : Motor_Start
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: Start the motor.
*/
ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed){
	switch(Motor_Number){
		case MOTOR_1:
		Pwm_Start(PWM_CH1A,Mot_Speed,MOTOR_FREQ);
		break;
		
		case MOTOR_2:
		Pwm_Start(PWM_CH1B,Mot_Speed,MOTOR_FREQ);
		break;
		
		default:
		return E_INVALID_PARAMETER;
		break;
	}
	return E_OK;
}

/**
 * Fun		 : Motor_SpeedUpdate
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: Controls the motor speed from getting the motor number and the speed.
*/
ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed){
	switch(Motor_Number){
		case MOTOR_1:
			return Pwm_Update(PWM_CH1A,Speed,MOTOR_FREQ);
		break;
		
		case MOTOR_2:
			return Pwm_Update(PWM_CH1B,Speed,MOTOR_FREQ);
		break;
		
		default:
		return E_INVALID_PARAMETER;
		break;
	}
	return E_OK;
}

/**
 * Fun		 : Motor_Stop
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: stop the motor.
*/
ERROR_STATUS Motor_Stop(uint8_t Motor_Number){
	switch(Motor_Number){
		case MOTOR_1:
		Pwm_Stop(PWM_CH1A);
		break;
		
		case MOTOR_2:
		Pwm_Stop(PWM_CH1B);
		break;
		
		default:
		return E_INVALID_PARAMETER;
		break;
	}
	return E_OK;
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
ERROR_STATUS Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status);
