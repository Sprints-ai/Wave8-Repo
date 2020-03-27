/*
 * testing.h
 *
 * Created: 2020-03-26 11:05:40 AM
 *  Author: EbrahimOseif
 */ 

#include "motor.h"


	/* testing API PROTOTYPES*/


ERROR_STATUS Testing_Motor_Init(uint8_t u8_Motor_Number);

ERROR_STATUS Testing_Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction);

ERROR_STATUS Testing_Motor_Start(uint8_t u8_Motor_Number, uint8_t u8_Mot_Speed);

ERROR_STATUS Testing_Motor_Stop(uint8_t Motor_Number);

ERROR_STATUS Testing_Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status);
