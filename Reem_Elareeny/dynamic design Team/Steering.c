/*
 * Steering.c
 *
 * Created: 2/18/2020 6:49:57 PM
 *  Author: Ema
 */

 #include "Steering.h"

static uint8_t steering_Init_flag = FALSE;

 ERROR_STATUS Steering_Init(void)
 {
    ERROR_STATUS ERROR = E_OK;

	 ERROR = Motor_Init(MOTOR_1);
	 ERROR = Motor_Init(MOTOR_2);

	 if(ERROR == E_OK)
     {
         steering_Init_flag = TRUE;
     }

	 return ERROR;
 }

 ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed)
 {
    ERROR_STATUS ERROR = E_OK;

     if(steering_Init_flag == FALSE)
     {
         ERROR = ERROR_MODULE_NOT_INITIALIZED;
     }
     else
     {
        switch (Steering_CarCmd)
        {
            case CAR_STOP:
             {
                 ERROR = Motor_Stop(MOTOR_1);
                 ERROR = Motor_Stop(MOTOR_2);
             }
             break;
             case CAR_FORWARD:
             {
                 ERROR = Motor_Direction(MOTOR_1,MOTOR_FORWARD);
                 ERROR = Motor_Direction(MOTOR_2,MOTOR_FORWARD);
                 ERROR = Motor_Start(MOTOR_1,speed);
                 ERROR = Motor_Start(MOTOR_2,speed);
             }
             break;
             case CAR_BACKWARD:
             {
                 ERROR = Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
                 ERROR = Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
                 ERROR = Motor_Start(MOTOR_1,speed);
                 ERROR = Motor_Start(MOTOR_2,speed);
             }
             break;
             case CAR_RIGHT:
             {
                 ERROR = Motor_Direction(MOTOR_1,MOTOR_FORWARD);
                 ERROR = Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
                 ERROR = Motor_Start(MOTOR_1,speed);
                 ERROR = Motor_Start(MOTOR_2,speed);
             }
             break;
             case CAR_LEFT:
             {
                 ERROR = Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
                 ERROR = Motor_Direction(MOTOR_2,MOTOR_FORWARD);
                 ERROR = Motor_Start(MOTOR_1,speed);
                 ERROR = Motor_Start(MOTOR_2,speed);
             }
             break;
             default:
             ERROR = ERROR_INVALID_PARAMETER;
             break;
        }

     }

	 return ERROR;
 }
