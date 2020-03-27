/*
 * testing.h
 *
 * Created: 2020-03-26 11:05:40 AM
 *  Author: EbrahimOseif
 */ 

#include "PWM.h"


	/* testing API PROTOTYPES*/


ERROR_STATUS Testing_Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);

ERROR_STATUS Testing_Pwm_Start(uint8_t a_u8_Channel, uint8_t a_u8_Duty, uint32_t a_u32_Frequency);

ERROR_STATUS Testing_Pwm_Update(uint8_t a_u8_Channel, uint8_t a_u8_Duty, uint32_t a_u32_Frequency);

ERROR_STATUS Testing_Pwm_Stop(uint8_t Channel);
