/*
*	File name: main.c
*	Author : Ema
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "Steering.h"


uint8_t *NULL_Ptr_check = NULL;
uint8_t Mot_status;

int main()
{
    signed char Check_Test=0;

    printf("/***********************************Steering_SteerCar_NOINIT***********************************/\n");
    Check_Test = Steering_SteerCar(CAR_FORWARD, 40);
    printf("Steering_SteerCar Status for NO_INIT  ---> %d \n",Check_Test);


    printf("/***********************************STEERING_INIT***********************************/\n");
    Check_Test = Steering_Init();
    printf("Steering_Init Status ---> %d \n",Check_Test);

    Check_Test = Steering_Init();                            //change the MOTOR return in mock_motor.c to test
    printf("Steering_Init Status for MOTOR_ERROR ---> %d \n",Check_Test);


    printf("/***********************************Steering_SteerCar***********************************/\n");
    Check_Test = Steering_SteerCar(CAR_BACKWARD, 40);
    printf("Steering_SteerCar Status for Valid_PARAM  ---> %d \n",Check_Test);

    Check_Test = Steering_SteerCar(9, 40);
    printf("Steering_SteerCar Status for INValid_PARAM  ---> %d \n",Check_Test);

    Check_Test = Steering_SteerCar(CAR_BACKWARD, 40);        //change the MOTOR return in mock_motor.c to test
    printf("Steering_SteerCar Status for MOTOR_ERROR  ---> %d \n",Check_Test);


    return 0;
}
