/*
 * main.c
 *
 *  Created on: Mar 26, 2020
 *      Author: Youssef Harby
 */


#include <stdio.h>
#include "APP/Steering.h"


/*- PREPROCESSOR MACROS ------------------------------------*/

#define SKIP_LINE		printf("\n")


/*- APIs PROTOTYPES ----------------------------------------*/

void Steering_Init_Tester(void);
void Steering_SteerCar_Tester(uint8_t Steering_CarCmd, uint8_t speed);


/*- MAIN FUNCTION ------------------------------------------*/

int main(void)
{
//	REMOVE "//" FOR STEERING_INIT FUNCTION TEST SCENARIOS
//
//	Steering_Init_Tester();
//	SKIP_LINE;
//
//	Steering_Init_Tester();
//	Steering_Init_Tester();

//		SKIP_LINE;
//		SKIP_LINE;

//	REMOVE "//" FOR STEERING_STEERCAR FUNCTION TEST SCENARIOS
//
//	Steering_Init_Tester();
//	Steering_SteerCar_Tester(CAR_FORWARD, 50);
//	SKIP_LINE;
//
//	Steering_Init_Tester();
//	Steering_SteerCar_Tester(CAR_FORWARD, 101);
//	SKIP_LINE;
//
//	Steering_Init_Tester();
//	Steering_SteerCar_Tester(7, 100);
//	SKIP_LINE;
//
//	Steering_Init_Tester();
//	Steering_SteerCar_Tester(7, 101);
//	SKIP_LINE;
//
//	Steering_SteerCar_Tester(CAR_FORWARD, 100);
//	SKIP_LINE;

	return 0;
}


/*- APIs IMPLEMENTATION ------------------------------------*/

void Steering_Init_Tester(void)
{
	sint8_t as8_ErrorValue = Steering_Init();

	if(as8_ErrorValue == STEERING_E_ALREADY_INIT)
	{
		printf("Steering Init Error Detected - Steering Already Initialized\n");
	}else if(as8_ErrorValue == STEERING_E_OK)
	{
		printf("Steering Init Error-Free\n");
	}
}


void Steering_SteerCar_Tester(uint8_t Steering_CarCmd, uint8_t speed)
{
	sint8_t as8_ErrorValue = Steering_SteerCar(Steering_CarCmd, speed);

	if(as8_ErrorValue == STEERING_E_NOT_INIT)
	{
		printf("Steering Steer Car Error Detected - Steering Not Initialized\n");
	}else if(as8_ErrorValue == STEERING_E_INVALID_CAR_CMD)
	{
		printf("Steering Steer Car Error Detected - Invalid Car Command\n");
	}else if(as8_ErrorValue == STEERING_E_INVALID_SPEED)
	{
		printf("Steering Steer Car Error Detected - Invalid Speed\n");
	}else if(as8_ErrorValue == STEERING_E_OK)
	{
		printf("Steering Steer Car Error-Free\n");
	}
}
