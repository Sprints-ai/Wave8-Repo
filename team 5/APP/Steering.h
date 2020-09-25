/*
 * Steering.h
 *
 *  Created on: Dec 21, 2019
 *      Author: Zayed & Saad
 */


#ifndef STEERING_H_
#define STEERING_H_

/************************************************************************/
/*				 INCLUDES			        							*/
/************************************************************************/

#include "../Service/std_types.h"


/*
 *  INCLUDE MOTOR.H HERE
 */

/************************************************************************/
/*				 DEFINES			        							*/
/************************************************************************/

/*Command Macros to call the steering api*/
#define		CAR_STOP		0
#define		CAR_FORWARD		1
#define		CAR_BACKWARD	2
#define		CAR_RIGHT		3
#define		CAR_LEFT		4

/************************************************************************/
/*		      STEERING FUNCTIONS' PROTOTYPES		        			*/
/************************************************************************/


/**
 * Input: nothing
 * Output: nothing
 * In/Out:	nothing		
 * Return: The error status of the function.			
 * Description: Initiates the module , initialize MOTOR_1 & MOTOR_2 
 * 							
 */

ERROR_STATUS Steering_Init(void);

/**
 * Input: 
 * 	carDirection: The direction of the car from the predefined states of the module:
																					-> car_STOP
																					->CAR_FOTWARD
																					->CAR_BACKWARD
																					->CAR_RIGHT
																					->CAR_LEFT
 * 	speed: The speed of the car from 0% to 100%.
 * Output: nothing
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function controls the command and the speed of the car.
 * 							
 */
ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed);





#endif /* STEERING_H_ */
