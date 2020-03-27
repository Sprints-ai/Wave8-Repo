/*
 * testing.c
 *
 * Created: 2020-03-26 11:05:40 AM
 *  Author: EbrahimOseif
 */ 


#include "testing.h"




/* Test Data preparation */
			
			/* MOTORS  DATA */
				
	uint8_t MOTORS_Valid_Data[2] = { 1, 2};
	
	uint8_t MOTORS_IN_Valid_Data[2] = { 0, 3};

	uint8_t Direction_Valid_Data[3] = { MOTOR_FORWARD, MOTOR_BACKWARD, MOTOR_STOP};
	
	sint8_t Direction_IN_Valid_Data[2] = { -1, 3};

	uint8_t Speed_Valid_Data[3] = { 1, 100, 255};
	
	sint8_t Speed_IN_Valid_Data[2] = { -1, 256};
	
	/* testing API IMPLEMENTATION */

    
ERROR_STATUS Testing_Motor_Init(uint8_t u8_Motor_Number){
		
		return Motor_Init( u8_Motor_Number);
}

ERROR_STATUS Testing_Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction){
	
	return Motor_Direction( Motor_Number,  Motor_Direction);
}

ERROR_STATUS Testing_Motor_Start(uint8_t u8_Motor_Number, uint8_t u8_Mot_Speed){
	
	 Motor_Start( u8_Motor_Number,  u8_Mot_Speed);
}

ERROR_STATUS Testing_Motor_Stop(uint8_t Motor_Number){
	
	return  Motor_Stop( Motor_Number);
}

ERROR_STATUS Testing_Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status){
	
	return Motor_GetStatus( Motor_Number,  Mot_status);
}
