/*
 ============================================================================
 Name        : Testing.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include "Steering.h"


#define VALID_SPEED 50
#define NON_VALID_SPEED 105
#define VALID_DIRECTION CAR_FORWARD
#define NON_VALID_DIRECTION 9
extern uint8_t Motor_stub_return_value;


int main(void)
{
	Motor_stub_return_value=E_ok;
	uint8_t au8_ExpectedOutput=E_ok;
	uint8_t u8_status1=0;
	uint8_t u8_status2=0;
	uint8_t u8_status3=0;
	uint8_t u8_status4=0;
	uint8_t u8_status5=0;
	uint8_t u8_status6=0;


	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: valid calling to "Steering_Init" with E_ok return value from the Motor module
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_ok;
	Motor_stub_return_value=E_ok;
	u8_status1 |= Steering_Init();
	if(u8_status1==au8_ExpectedOutput)
	{
		printf("test case 1: PASSED\n");
	}
	else
	{
		printf("test case 1: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: valid calling to "Steering_Init" with E_NOk return value from the Motor module
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	Motor_stub_return_value=E_NOk;
	u8_status2 |= Steering_Init();
	Motor_stub_return_value=E_ok;
	if(u8_status2==au8_ExpectedOutput)
	{
		printf("test case 2: PASSED\n");
	}
	else
	{
		printf("test case 2: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: valid calling to "Steering_SteerCar"
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_ok;
	Motor_stub_return_value=E_ok;
	u8_status3 |= Steering_Init();
	u8_status3 |= Steering_SteerCar(VALID_DIRECTION,VALID_SPEED);
	if(u8_status3==au8_ExpectedOutput)
	{
		printf("test case 3: PASSED\n");
	}
	else
	{
		printf("test case 3: FAILED\n");
	}



	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: non valid calling to "Steering_SteerCar" (non valid direction)
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	Motor_stub_return_value=E_ok;
	u8_status4 |= Steering_Init();
	u8_status4 |= Steering_SteerCar(NON_VALID_DIRECTION,VALID_SPEED);
	if(u8_status4==au8_ExpectedOutput)
	{
		printf("test case 4: PASSED\n");
	}
	else
	{
		printf("test case43: FAILED\n");
	}



	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: non valid calling to "Steering_SteerCar" (speed greater than 100)
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	Motor_stub_return_value=E_ok;
	u8_status5 |= Steering_Init();
	u8_status5 |= Steering_SteerCar(VALID_DIRECTION,NON_VALID_SPEED);
	if(u8_status5==au8_ExpectedOutput)
	{
		printf("test case 5: PASSED\n");
	}
	else
	{
		printf("test case 5: FAILED\n");
	}



	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: valid calling to "Steering_SteerCar" with E_NOk return value from the Motor module
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	Motor_stub_return_value=E_ok;
	u8_status6 |= Steering_Init();
	Motor_stub_return_value=E_NOk;
	u8_status6 |= Steering_SteerCar(VALID_DIRECTION,VALID_SPEED);
	Motor_stub_return_value=E_ok;
	if(u8_status6==au8_ExpectedOutput)
	{
		printf("test case 6: PASSED\n");
	}
	else
	{
		printf("test case 6: FAILED\n");
	}


	return 0;
}
