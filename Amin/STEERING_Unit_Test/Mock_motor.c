#include "Mock_motor.h"

 ERROR_STATUS Motor_Init(uint8 Motor_Number){
	 switch(Motor_Number){
		  case (MOTOR_1):
			return NO_ERROR;
			break;
			case (MOTOR_2):
			return NO_ERROR;
			break;
	 }
			return ERROR;

 }


	   ERROR_STATUS Motor_Direction(uint8 Motor_Number, uint8 Motor_Direction){
	switch(Motor_Number)
		{
		case (MOTOR_1):
			if(Motor_Direction >=MOTOR_STOP &&Motor_Direction<=MOTOR_BACKWARD)
			{
        	return NO_ERROR;
			}
            break;
			case (MOTOR_2):
			if(Motor_Direction >=MOTOR_STOP &&Motor_Direction<=MOTOR_BACKWARD)
			{
			return NO_ERROR;
			}
			break;
		}


 return ERROR;
 }


 /*Describtion: this function choose motor and set its direction and speed */
 ERROR_STATUS Motor_Start(uint8 Motor_Number, uint8 Mot_Speed){
	switch(Motor_Number)
		{
		case (MOTOR_1):
			if(Mot_Speed>=0&&Mot_Speed<=100)
			{
			return NO_ERROR;
			}
			break;
		case (MOTOR_2):
		   if(Mot_Speed>=0&&Mot_Speed<=100)
		   {
			return NO_ERROR;
		   }
			break;

		}
return ERROR;
 }


 /*Describtion: this function choose motor and update its direction and speed */
 ERROR_STATUS Motor_SpeedUpdate(uint8 Motor_Number, uint8 Speed){
switch(Motor_Number)
		{
		case (MOTOR_1):
			if(Speed>=0&&Speed<=100)
			{
			return NO_ERROR;
			}
			break;
		case (MOTOR_2):
		   if(Speed>=0&&Speed<=100)
		   {
			return NO_ERROR;
		   }
			break;

		}
return ERROR;
 }




 /*Describtion: this function choose motor and stop it */

 ERROR_STATUS Motor_Stop(uint8 Motor_Number){
	switch(Motor_Number)
		{
		case MOTOR_1:
			return NO_ERROR;
			break;
		case MOTOR_2:
			return NO_ERROR;
			break; }
         return ERROR;
 }


