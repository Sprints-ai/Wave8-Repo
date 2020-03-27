/*
 * testing.c
 *
 * Created: 2020-03-26 11:05:40 AM
 *  Author: EbrahimOseif
 */ 


#include "testing.h"




/* Test Data preparation */
			
			/* MOTORS  DATA */
				
	uint8_t PWM_CHANNEL_Valid_Data[2] = { 1, 2};
	
	uint8_t PWM_CHANNEL_IN_Valid_Data[2] = { 0, 3};

	uint8_t DUTY_Valid_Data[3] = { 1, 50, 100};
	
	sint8_t DUTY_IN_Valid_Data[2] = { -1, 101};
	
	uint8_t FREQ_Valid_Data[3] = {  50, 100,200};
	
	sint8_t FREQ_IN_Valid_Data[2] = { -1, 0};
	
	/* testing API IMPLEMENTATION */

    
ERROR_STATUS Testing_Pwm_Init(Pwm_Cfg_s *Pwm_Cfg){
	
	return Pwm_Init(Pwm_Cfg);
}

ERROR_STATUS Testing_Pwm_Start(uint8_t a_u8_Channel, uint8_t a_u8_Duty, uint32_t a_u32_Frequency){
	
	return Pwm_Start( a_u8_Channel,  a_u8_Duty,  a_u32_Frequency);

}

ERROR_STATUS Testing_Pwm_Update(uint8_t a_u8_Channel, uint8_t a_u8_Duty, uint32_t a_u32_Frequency){
	
	 	return Pwm_Update( a_u8_Channel,  a_u8_Duty,  a_u32_Frequency);
}

ERROR_STATUS Testing_Pwm_Stop(uint8_t Channel){
	
	return Pwm_Stop( Channel);
}

