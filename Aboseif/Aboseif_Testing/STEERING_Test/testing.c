/*
 * testing.c
 *
 * Created: 2020-03-26 11:05:40 AM
 *  Author: EbrahimOseif
 */ 


#include "testing.h"




/* Test Data preparation */
			
			/* MOTORS  DATA */
				
	uint8_t Direction_Valid_Data[] = { CAR_STOP, CAR_FORWARD, CAR_BACKWARD, CAR_RIGHT, CAR_LEFT  };
	
	uint8_t Direction_IN_Valid_Data[2] = { -1, 5};

	uint8_t DUTY_Valid_Data[3] = { 1, 50, 100};
	
	sint8_t DUTY_IN_Valid_Data[2] = { -1, 101};
	
	/* testing API IMPLEMENTATION */

    
ERROR_STATUS Testing_Steering_Init(){
	
	return Steering_Init();
}

ERROR_STATUS Testing_Steering_SteerCar(uint8_t Steering_direction, uint8_t speed){
	
	return  Steering_SteerCar( Steering_direction,  speed);

}

