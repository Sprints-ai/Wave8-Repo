#ifndef __MOTOR_H__
#define __MOTOR_H__
/*
 * File		: Motor.h
 * Author	: Ahmed Ashraf
 * Version	: 1.0
 */

/*********************************************
 *				General macros  		     *
 ********************************************/

#define MOTOR_1					(1)
#define MOTOR_2 				(2)

#define MOTOR_STOP 				(0)
#define MOTOR_FORWARD 			(1)
#define MOTOR_BACKWARD			(2)

#define MOTOR1_INIT_DONE		(1)
#define MOTOR1_INIT_NOT_DONE	(2)
#define MOTOR2_INIT_DONE		(3)
#define MOTOR2_INIT_NOT_DONE	(4)

#define E_OK					(1)
#define E_NOK					(-1)

/************************************************************************/
/*						User typedef defines                          	*/
/************************************************************************/

typedef sint8_t ERROR_STATUS;

/*********************************************
 *	  	   Function prototypes				 *
 ********************************************/

/**
 * Function		: Motor_Init
 * Input		: @param Motor_Number -> (MOTOR_1 , MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: ERROR_STATUS
 * Description	: Initialize (Enable, IN1, IN2) pins as digital outputs.
 */
 ERROR_STATUS Motor_Init(uint8_t Motor_Number);
 
/**
 * Function	  : Motor_Direction
 * input	  : @param Motor_Number -> (MOTOR_1 , MOTOR_2)
 *			    @param Mot_Direction -> (Stop, Forward, Backward)
 * output  	  : no output
 * return 	  : ERROR_STATUS
 * Description: Controls the motor direction from getting the motor number and the direction.
 */
ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Mot_Direction);

/**
 * Function	  : Motor_Start
 * input	  : @param Motor_Number -> (MOTOR_1 , MOTOR_2)
 *				@param Motor_Speed
 * output  	  : no output
 * return 	  : ERROR_STATUS
 * Description: Start the motor.
*/
ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Motor_Speed);

/**
 * Function	  : Motor_SpeedUpdate
 * input	  : @param Motor_Number -> (MOTOR_1, MOTOR_2)		       
 *			    @param Motor_Speed
 * output  	  : no output
 * return 	  : ERROR_STATUS
 * Description: Controls the motor speed from getting the motor number and the speed.
*/
ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Motor_Speed);

/**
 * Function	  : Motor_Stop
 * input	  : @param Motor_Number -> (MOTOR_1, MOTOR_2)
 * output  	  : no output
 * return 	  : ERROR_STATUS
 * Description: stop the motor.
*/
ERROR_STATUS Motor_Stop(uint8_t Motor_Number);

 /**
 * Function		: Motor_GetStatus
 * Input		: @param Motor_Number -> (MOTOR_1, MOTOR_2) 
 * output		: @param Motor_Status pointer
 * In out		: none
 * Return		: ERROR_STATUS
 * Description	: Returns status of the motor whether initialized or not
 */
 ERROR_STATUS Motor_GetStatus(uint8_t Motor_Number, uint8_t* Motor_Status);

#endif /*__MOTOR_H__*/