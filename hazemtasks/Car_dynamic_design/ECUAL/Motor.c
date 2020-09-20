/*
 * Motor.c
 *
 * Created: 2/18/2020 6:32:08 PM
 *  Author: hazem
 */
 
/*********************************************
 *				Includes  					 *
 ********************************************/

#include "motor.h"



/*********************************************
 *	  	   API IMPLEMENTATION 				 *
 ********************************************/

/********************************************/
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
 ERROR_STATUS Motor_Init(uint8_t Motor_Number)
 {ERROR_STATUS ERROR=E_OK;
	 DIO_Cfg_s instance={GPIOD,FULL_PORT,OUTPUT};
		 Pwm_Cfg_s instance_pwm={PWM_CH1A,PWM_PRESCALER_1024};
			 Pwm_Init(&instance_pwm);
			 instance_pwm.Channel=PWM_CH1B;
			  Pwm_Init(&instance_pwm);
	 switch(Motor_Number)
	 {   
		 case MOTOR_1:
		      DIO_init(&instance);
		      break;      
		 case MOTOR_2:
		     DIO_init(&instance);
		     break;
		 default:
		     ERROR=E_NOK;
		     break;     	 
		 
	 }
return ERROR;	 
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
 * DescriptioN: Controls the motor direction from getting the motor number and the direction.
*/

ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction)
{
ERROR_STATUS ERROR=E_OK;
	switch(Motor_Number)
	{
		case MOTOR_1:
		      switch(Motor_Direction)
			  {
				  case MOTOR_STOP:
				        DIO_Write(GPIOD,BIT2,LOW);
						DIO_Write(GPIOD,BIT3,LOW);
						break;
				  case MOTOR_FORWARD:
				        DIO_Write(GPIOD,BIT2,LOW);
				        DIO_Write(GPIOD,BIT3,HIGH);
				        break;
				  case MOTOR_BACKWARD:
				        DIO_Write(GPIOD,BIT2,HIGH);
				        DIO_Write(GPIOD,BIT3,LOW);
				        break;
				  default:
				        ERROR=E_NOK;
				        break;
			  }
			  
		      break;
		case MOTOR_2:
              switch(Motor_Direction)
              {
	              case MOTOR_STOP:
	              DIO_Write(GPIOD,BIT6,LOW);
	              DIO_Write(GPIOD,BIT7,LOW);
	              break;
	              case MOTOR_FORWARD:
	              DIO_Write(GPIOD,BIT6,LOW);
	              DIO_Write(GPIOD,BIT7,HIGH);
	              break;
	              case MOTOR_BACKWARD:
	              DIO_Write(GPIOD,BIT6,HIGH);
	              DIO_Write(GPIOD,BIT7,LOW);
	              break;
	              default:
				      ERROR=E_NOK;
	                  break;
              }
              break;		      
		default:
		      ERROR=E_NOK;
		      break;
		
	}
	
	
	return ERROR;
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
ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed)
{
ERROR_STATUS ERROR=E_OK; 
switch(Motor_Number)
{
    case MOTOR_1:
	     Pwm_Start(PWM_CH1B,Mot_Speed,62);
		 break;
	case MOTOR_2:
	     Pwm_Start(PWM_CH1A,Mot_Speed,62);
	     break;	
	default:
		ERROR=E_NOK;
		break;
}
return ERROR;
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
ERROR_STATUS Motor_Stop(uint8_t Motor_Number)
{
	ERROR_STATUS ERROR=E_OK;
switch(Motor_Number)
{	
case MOTOR_1:
     DIO_Write(GPIOD,BIT4,LOW);
	  DIO_Write(GPIOD,BIT3,LOW);
     DIO_Write(GPIOD,BIT2,LOW);
	  break;
case MOTOR_2:
     DIO_Write(GPIOD,BIT5,LOW);
     DIO_Write(GPIOD,BIT6,LOW);
     DIO_Write(GPIOD,BIT7,LOW);
     break;
default:
    ERROR=E_NOK;
	break;
}
return ERROR;
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
 * Descriptio: Controls the motor speed from getting the motor number and the speed.
*/
ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed)
{
	ERROR_STATUS ERROR=E_OK;
	switch(Motor_Number)
	{
		case MOTOR_1:
		Pwm_Start(PWM_CH1A,Speed,62);
		break;
		case MOTOR_2:
		Pwm_Start(PWM_CH1B,Speed,62);
		break;
		default:
		ERROR=E_NOK;
		break;
		
	}
	return ERROR;
}


