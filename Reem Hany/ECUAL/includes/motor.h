#ifndef MOTOR_H_
#define MOTOR_H_
/*
 * File		: Motor.h
 * Author	: Sharaf & Osama
 * Version	: 1.1
 */

/*********************************************
 *				Includes  					 *
 ********************************************/
#include "../../Services/includes/common_macros.h"
#include "../../Services/includes/std_types.h"
#include "../../Services/includes/ERROR.h"
#include "../../MCAL/includes/PWM.h"

/*********************************************
 *				Defines  					 *
 ********************************************/

#define MOTOR_1			1
#define MOTOR_2 		2

#define MOTOR_STOP 		0
#define MOTOR_FORWARD 	1
#define MOTOR_BACKWARD 	2

#define MOTOR_FREQ      100

/*********************************************
 *	  	   Function prototypes				 *
 ********************************************/

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
extern ERROR_STATUS Motor_Init(uint8_t Motor_Number);
 
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
extern ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction);

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
extern ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed);

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
extern ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed);

/**
 * Fun		 : Motor_Stop
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: stop the motor.
*/
extern ERROR_STATUS Motor_Stop(uint8_t Motor_Number);

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
extern ERROR_STATUS Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status);

#endif // MOTOR_H_