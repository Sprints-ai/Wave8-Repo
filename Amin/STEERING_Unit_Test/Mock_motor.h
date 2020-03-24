#ifndef MOCK_MOTOR_H_
#define MOCK_MOTOR_H_

#include "common_macros.h"
#include "std_types.h"

#define MOTOR_1			1
#define MOTOR_2 		2

#define MOTOR_STOP 		0
#define MOTOR_FORWARD 	1
#define MOTOR_BACKWARD 	2

 ERROR_STATUS Motor_Init(uint8 Motor_Number);
 ERROR_STATUS Motor_Direction(uint8 Motor_Number, uint8 Motor_Direction);
 ERROR_STATUS Motor_Start(uint8 Motor_Number, uint8 Mot_Speed);
 ERROR_STATUS Motor_SpeedUpdate(uint8 Motor_Number, uint8 Speed);
 ERROR_STATUS Motor_Stop(uint8 Motor_Number);




#endif /* MOCK_MOTOR_H_*/
