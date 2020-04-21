/*
 * car_sm.c
 *
 * Created: 3/30/2020 2:42:10 PM
 *  Author: Ehab , Ramadan , Reem , Eman
 */ 

#include "car_sm.h"
#include "Steering.h"
#include "../Services/DistanceReader.h"


/**
 * Description: Initializes the Car State Machine 
 *
 * @return function status 
 */
ERROR_STATUS Car_SM_Init(void)
{
	ERROR_STATUS ERR = E_OK;
	
	/*initialize distance reader*/
	ERR = DistanceReader_Init();

	if (ERR == E_OK)
	{
		/*if the distance reader is initialized successfully ; initialize Steering module*/
		ERR = Steering_Init();
	}
	
	if (ERR != E_OK)
	{
		/* if there is an error in initializing any of the past modules update error status to be internal error */
		ERR = ERROR_CAR_SM_MODULE_ID - ERROR_INTERNAL_ERROR;
	}
	
	
	return ERR;
}

/**
 * Description: updates the car status according to the distance between the car
 *				and the obstacle
 *
 * @return function status 
 */
ERROR_STATUS Car_SM_Update(uint16_t u16_Distance)
{
	UDR = u16_Distance;
	ERROR_STATUS ERR = E_OK;
	
	static uint8_t u8_state = FORWARD_STATE;
	static uint8_t u8_OS_Counter = COUNTER_START_VALUE;
	
	/* if u8_OS_Counter = 0 this means that the car is either in the forward or backward states*/
	if (u8_OS_Counter == COUNTER_START_VALUE)
	{


		/* Check on the distance and update the car state accordingly*/
		if (u16_Distance>=50 )
		{
			u8_state = FORWARD_STATE;
		}
		
		else if (u16_Distance<50 && u16_Distance>20)
		{
			u8_state = RIGHT_STATE;	
		}
		
		else if (u16_Distance<=20)
		{
			u8_state = BACK_STATE;
		}
	}
	
	/* Car state machine logic*/

	switch(u8_state)
	{
		case FORWARD_STATE:

			/*Move the car forward*/
// 			ERR = Steering_SteerCar(CAR_FORWARD,MOTORS_SPEED); //Reem
			/*Reem*/
			u8_OS_Counter += OS_RESOLUTION;
			if (u8_OS_Counter >= ACTION_DELAY)
			{
	 			ERR = Steering_SteerCar(CAR_FORWARD,MOTORS_SPEED);
				u8_OS_Counter = COUNTER_START_VALUE;
			}
			/*Reem*/
			break;
		
		case BACK_STATE:
			/*move the car backwards*/

			/*Reem*/
			u8_OS_Counter += OS_RESOLUTION;
			
			if (u8_OS_Counter >= ACTION_DELAY)
			{
				u8_OS_Counter = COUNTER_START_VALUE;
				ERR = Steering_SteerCar(CAR_BACKWARD,MOTORS_SPEED);
			}
			/*Reem*/
			break;
		
		case RIGHT_STATE:
			/*move the car to the right*/
			
			/*update the counter value to ignore distance readings for a while to be sure the car
			moved away from the obstacle then reset the counter after that to take new distance readings*/

// 		ERR = Steering_SteerCar(CAR_RIGHT,MOTORS_SPEED); // Reem
			u8_OS_Counter +=OS_RESOLUTION;
			if (u8_OS_Counter > ACTION_DELAY)
			{
				u8_OS_Counter = COUNTER_START_VALUE;
				ERR = Steering_SteerCar(CAR_RIGHT,MOTORS_SPEED);//Reem
			}
	}
	
	if (ERR != E_OK)
	{
		ERR = ERROR_CAR_SM_MODULE_ID + ERROR_INTERNAL_ERROR;
	}
	return ERR;
	
}