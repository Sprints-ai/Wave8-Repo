/*
 * motor.c
 *
 * Created: 2/18/2020 10:07:19 AM
 *  Author: MENA
 */ 

#include "motor.h"
#include "PWM.h"

#define CAR_FREQUANCY 100

/*
 * Fun			: Motor_Init
 * Input		: motorNumber
 *	  	  		  #def
 *	  	  		  number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: ERROR_STATUS
 * Description	: Initialize (Enable, IN1, IN2) pins as digital outputs.
 */


 ERROR_STATUS Motor_Init(uint8_t Motor_Number){
	 
	 uint8_t a_u8_error_state = E_OK ;
	 
	 DIO_Cfg_s dioCfg_M;
	  Pwm_Cfg_s pwm_cfgA ;
	 Pwm_Cfg_s pwm_cfgB ;
	 
	 	switch (Motor_Number)
	 	{
		 	case MOTOR_1:
			
			 pwm_cfgA.Channel = PWM_CH1A ;
			 pwm_cfgA.Prescaler = PWM_PRESCALER_1024 ;
			 a_u8_error_state |= Pwm_Init(&pwm_cfgA);
			 dioCfg_M.GPIO=MOTOR_OUT_1A_GPIO;
			 dioCfg_M.pins=MOTOR_OUT_1A_BIT|MOTOR_OUT_1B_BIT|MOTOR_EN_1_BIT;
			 dioCfg_M.dir=OUTPUT;
			 
			 
		 	 a_u8_error_state |=  DIO_init (&dioCfg_M);

		 	 a_u8_error_state |= DIO_Write (dioCfg_M.GPIO, dioCfg_M.pins , LOW);

		 	
		 	break;
		 	
		 	case MOTOR_2:
			 
			 pwm_cfgB.Channel = PWM_CH1B ;
			 pwm_cfgB.Prescaler = PWM_PRESCALER_1024 ;
			 a_u8_error_state |= Pwm_Init(&pwm_cfgB);
			 dioCfg_M.GPIO=MOTOR_OUT_2A_GPIO;
			 dioCfg_M.pins=MOTOR_OUT_2A_BIT|MOTOR_OUT_2B_BIT|MOTOR_EN_2_BIT;
			 dioCfg_M.dir=OUTPUT;
			 
			 
			 a_u8_error_state |= DIO_init (&dioCfg_M);

			 a_u8_error_state |= DIO_Write (dioCfg_M.GPIO, dioCfg_M.pins , LOW);

			 break;

			 default:
			 a_u8_error_state |=  E_NOK ;
			 break;
	 	}
	 return a_u8_error_state  ;
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
	
		 uint8_t a_u8_error_state = E_OK ;
	
		switch (Motor_Number)
		{
			//////////motor1///////////
			case MOTOR_1:
			switch (Motor_Direction)
			{
				case MOTOR_FORWARD:
				a_u8_error_state |= DIO_Write (MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT , LOW);
				a_u8_error_state |= DIO_Write (MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT , HIGH);
				break;
				
				case MOTOR_BACKWARD:
				
				a_u8_error_state |= DIO_Write (MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT , HIGH);
				a_u8_error_state |= DIO_Write (MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT , LOW);
				break;
				
				case MOTOR_STOP:
				
				a_u8_error_state |= DIO_Write (MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT , LOW);
				a_u8_error_state |= DIO_Write (MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT , LOW);
				break;
				
				default:
				a_u8_error_state |= E_NOK ;
				break;
			}
			break;
			
			////////motor2//////////
			case MOTOR_2:
			switch (Motor_Direction)
			{
				case MOTOR_FORWARD:
				a_u8_error_state |= DIO_Write (MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT , HIGH);
				a_u8_error_state |= DIO_Write (MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT , LOW);
				break;
				case MOTOR_BACKWARD:
				a_u8_error_state |= DIO_Write (MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT , LOW);
				a_u8_error_state |= DIO_Write (MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT , HIGH);
				break;
				case MOTOR_STOP:
				a_u8_error_state |= DIO_Write (MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT , LOW);
				a_u8_error_state |= DIO_Write (MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT , LOW);
				break;
				default:
				a_u8_error_state |=  E_NOK ;
				break;
			}
			break;
			
			default:
			a_u8_error_state |=  E_NOK ;
			break;
		}
		
		return a_u8_error_state  ;
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
	
	 uint8_t a_u8_error_state = E_OK ;
	
	switch(Motor_Number){
		
		case MOTOR_1 :
		a_u8_error_state |= Pwm_Start(PWM_CH1A,Mot_Speed,CAR_FREQUANCY);
		case MOTOR_2 :
		a_u8_error_state |= Pwm_Start(PWM_CH1B,Mot_Speed,CAR_FREQUANCY);
		default :
		a_u8_error_state |= E_NOK ;
	}
	return a_u8_error_state  ;
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
		uint8_t a_u8_error_state = E_OK ;

	
		switch(Motor_Number){
			
			case MOTOR_1 :
			a_u8_error_state |= Pwm_Update(PWM_CH1A,Speed,CAR_FREQUANCY);
			case MOTOR_2 :
			a_u8_error_state |= Pwm_Update(PWM_CH1B,Speed,CAR_FREQUANCY);
			default: 
			a_u8_error_state |= E_NOK ;
		}
		
		return a_u8_error_state  ;
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
		 uint8_t a_u8_error_state = E_OK ;

	switch(Motor_Number){
		
		case MOTOR_1 :
		a_u8_error_state |= Pwm_Stop(PWM_CH1A);
		case MOTOR_2 :
		a_u8_error_state |= Pwm_Stop( PWM_CH1B);
		default:
		a_u8_error_state |= E_NOK ;
	}
	return a_u8_error_state ;
	
}
