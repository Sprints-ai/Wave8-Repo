/*
 * Steering.h
 *
 *      Author: Ahmed Ashraf
 *		Version : 1.0
 */

#ifndef __STEERING_H__
#define __STEERING_H__

/*
 *  INCLUDE MOTOR.H HERE
 */

/************************************************************************/
/*				 General macros									        */
/************************************************************************/

/*Command Macros to call the steering API*/
#define		CAR_STOP		(0)
#define		CAR_FORWARD		(1)
#define		CAR_BACKWARD	(2)
#define		CAR_RIGHT		(3)
#define		CAR_LEFT		(4)

#define		E_OK			(1)
#define		E_NOK			(-1)

/************************************************************************/
/*                        USer defined data types                       */
/************************************************************************/

typedef sint8_t	ERROR_STATUS;

/************************************************************************/
/*		      STEERING FUNCTIONS' PROTOTYPES						    */
/************************************************************************/

/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 */
ERROR_STATUS Steering_Init(void);

/**
 * Input: 
 * 	carDirection: The direction of the car from the predefined states of the module.
 * 	speed: The speed of the car from 0% to 100%.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function controls the command and the speed of the car. 							
 */
ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed);

#endif /* STEERING_H_ */