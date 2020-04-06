/*
*	File name: main.c
*	Author : Ema
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "motor.h"


uint8_t *NULL_Ptr_check = NULL;
uint8_t Mot_status;

int main()
{
    signed char Check_Test=0;

    printf("/***********************************MOTOR_NOINIT/START***********************************/\n");
    Check_Test = Motor_Direction(MOTOR_1,MOTOR_FORWARD);
    printf("Motor_Direction Status for NO_INIT  ---> %d \n",Check_Test);

    Check_Test = Motor_Start(MOTOR_1,30);
    printf("Motor_Start Status for NO_INIT  ---> %d \n",Check_Test);

    Check_Test = Motor_SpeedUpdate(MOTOR_1,70);
    printf("Motor_SpeedUpdate Status for NO_INIT  ---> %d \n",Check_Test);

    Check_Test = Motor_Stop(MOTOR_1);
    printf("Motor_Stop Status for NO_INIT  ---> %d \n",Check_Test);


    printf("/***********************************MOTOR_INIT***********************************/\n");
    Check_Test = Motor_Init(MOTOR_1);
    printf("Motor_Init Status for Valid_PARAM  ---> %d \n",Check_Test);

    Check_Test = Motor_Init(5);
    printf("Motor_Init Status for INValid_PARAM  ---> %d \n",Check_Test);

    Check_Test = Motor_Init(MOTOR_1);           //change the DIO return in mock_DIO.c to test
    printf("Motor_Init Status for DIO_ERROR  ---> %d \n",Check_Test);


    printf("/***********************************MOTOR_DIRECTION***********************************/\n");
    Check_Test = Motor_Direction(MOTOR_1,MOTOR_FORWARD);
    printf("Motor_Direction Status for Valid_PARAM  ---> %d \n",Check_Test);

    Check_Test = Motor_Direction(5,MOTOR_FORWARD);
    printf("Motor_Direction Status for INValid_PARAM  ---> %d \n",Check_Test);

    Check_Test = Motor_Direction(MOTOR_1,7);           //change the DIO return in mock_DIO.c to test
    printf("Motor_Direction Status for DIO_ERROR  ---> %d \n",Check_Test);


    printf("/***********************************MOTOR_START***********************************/\n");
    Check_Test = Motor_Start(MOTOR_1,30);
    printf("Motor_Start Status for Valid_PARAM  ---> %d \n",Check_Test);

    Check_Test = Motor_Start(5,50);
    printf("Motor_Start Status for INValid_PARAM  ---> %d \n",Check_Test);

    Check_Test = Motor_Start(MOTOR_2,80);              //change the PWM return in mock_PWM.c to test
    printf("Motor_Start Status for PWM_ERROR  ---> %d \n",Check_Test);


    printf("/***********************************Motor_SpeedUpdate***********************************/\n");
    Check_Test = Motor_SpeedUpdate(MOTOR_1,20);
    printf("Motor_SpeedUpdate Status for Valid_PARAM  ---> %d \n",Check_Test);

    Check_Test = Motor_SpeedUpdate(5,70);
    printf("Motor_SpeedUpdate Status for INValid_PARAM  ---> %d \n",Check_Test);

    Check_Test = Motor_SpeedUpdate(MOTOR_1,80);         //change the PWM return in mock_PWM.c to test
    printf("Motor_SpeedUpdate Status for PWM_ERROR  ---> %d \n",Check_Test);


    printf("/***********************************Motor_Stop***********************************/\n");
    Check_Test = Motor_Stop(MOTOR_1);
    printf("Motor_Stop Status for Valid_PARAM  ---> %d \n",Check_Test);

    Check_Test = Motor_Stop(6);
    printf("Motor_Stop Status for INValid_PARAM  ---> %d \n",Check_Test);

    Check_Test = Motor_Stop(MOTOR_2);                  //change the PWM return in mock_PWM.c to test
    printf("Motor_Stop Status for PWM_ERROR  ---> %d \n",Check_Test);


    printf("/***********************************Motor_GetStatus***********************************/\n");
    Check_Test = Motor_GetStatus(MOTOR_1, &Mot_status);
    printf("Motor_GetStatus Status for Valid_PARAM  ---> %d \n",Check_Test);

    Check_Test = Motor_GetStatus(8, &Mot_status);
    printf("Motor_GetStatus Status for INValid_PARAM  ---> %d \n",Check_Test);

    Check_Test = Motor_GetStatus(MOTOR_1, NULL_Ptr_check);
    printf("Motor_GetStatus Status for NULL_PTR  ---> %d \n",Check_Test);


    return 0;
}
