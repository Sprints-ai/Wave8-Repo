/************************************************************************/
/*                         Includes                                     */
/************************************************************************/

#include "std_types.h"
#include "Us.h"
#include "SOS.h"
#include "Steering.h"
#include "car_sm.h"

/************************************************************************/
/*                         General macros                               */
/************************************************************************/
#define CAR_SAFE_DISTANCE_CM	(45)
#define CAR_TURN_DISTANCE_CM	(25)
#define CAR_SPEED_0_255			(255)
#define TASK_PERIORITY			(0)
#define TASK_PERIODICITY		(6)

/************************************************************************/
/*	                        CAR_SM task configurations                  */
/************************************************************************/

/*Car_SM_Task function*/
static void Car_SM_Task(void)
{
	Car_SM_Update();
	return;
}

/*Creating task stack*/
Task_ConfigType	SOS_carSmTask = {TASK_PERIORITY,Car_SM_Task,PERIODIC_CALLING,TASK_PERIODICITY};

/************************************************************************/
/*                          CAR_SM functions                            */
/************************************************************************/

ERROR_STATUS Car_SM_Init(void)
{
	/*Error checking variables*/
	ERROR_STATUS err_var = E_OK;
	ERROR_STATUS err_1 = E_OK;
	ERROR_STATUS err_2 = E_OK;
	
	/*Initializing SOS*/
	SOS_Init();
	
	/*Adding task to SOS tasks pool*/
	SOS_addTask(&SOS_carSmTask);
	
	/*Initialization of ultrasonic module and validate it*/	
	err_1 = Us_Init();

	/*Initialization of steering module and validate it*/	
	err_2 = Steering_Init();
	
	/*Validate that any function is done successfully*/
	if ( (err_1 == E_NOK || err_2 == E_NOK) )
	{
		err_var = E_NOK;
	} 
	else
	{
		err_var = E_OK;
	}
	return err_var;
}

ERROR_STATUS Car_SM_Update(void)
{
	/*Error checking variables*/
	ERROR_STATUS err_var = E_OK;
	ERROR_STATUS err_1 = E_OK;
	ERROR_STATUS err_2 = E_OK;
	ERROR_STATUS err_3 = E_OK;
	
	/*Variable used to calculate ultrasonic distance*/
	uint32_t au32_distance = ZERO;
	
	/*Starting ultrasonic and validate it*/
	err_1 = Us_Trigger();
	
	/*Getting the distance of ultrasonic and validate it*/
	err_2 = Us_GetDistance(&au32_distance);
	
	/*Checking the distance exceeded the car safe distance or not to keep forward*/	
	if(au32_distance > CAR_SAFE_DISTANCE_CM)
	{
		err_3 = Steering_SteerCar(CAR_FORWARD , CAR_SPEED_0_255);
	}
	/*Turn right in case distance is less than safe distance but bigger than cat turn distance*/
	else if(au32_distance < CAR_SAFE_DISTANCE_CM && au32_distance > CAR_TURN_DISTANCE_CM)
	{
		err_3 = Steering_SteerCar(CAR_RIGHT , CAR_SPEED_0_255);
	}
	/*Go backward in case the distance is less than car turn distance*/
	else if(au32_distance < CAR_TURN_DISTANCE_CM)
	{
		err_3 = Steering_SteerCar(CAR_BACKWARD , CAR_SPEED_0_255);
	}
	else
	{
		/*Do nothing*/
	}
	
	/*Validate that any function is done successfully*/
	if((err_1 == E_NOK) || (err_2 == E_NOK) || (err_3 == E_NOK))
	{
		err_var = E_NOK;
	}
	else
	{
		err_var = E_OK;
	}
	
	return err_var;
}