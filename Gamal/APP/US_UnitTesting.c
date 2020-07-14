/*
 ============================================================================
 Name        : Testing.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include "../HAL/US.h"



extern uint8_t DIO_stub_return_value;
extern uint8_t ICU_stub_return_value;
extern uint8_t Delay_stub_return_value;
int main(void)
{
	DIO_stub_return_value=E_ok;
	ICU_stub_return_value=E_ok;
	uint8_t au8_ExpectedOutput=E_ok;
	uint8_t u8_status1=0;
	uint8_t u8_status2=0;
	uint8_t u8_status3=0;
	uint8_t u8_status4=0;
	uint8_t u8_status5=0;
	uint8_t u8_status6=0;
	uint8_t u8_status7=0;
	uint8_t u8_status8=0;
	uint8_t u8_status9=0;
	uint8_t u8_status10=0;
	uint8_t u8_status11=0;
	uint8_t u8_status12=0;
	uint8_t u8_status13=0;
	uint16_t u16_distance;
	uint32_t u32_non_valid_distance=9999;
	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: valid calling to "Us_Init"
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/

	au8_ExpectedOutput=E_ok;
	DIO_stub_return_value=E_ok;
	u8_status1 |= Us_Init();
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
	* Test Case: valid calling to "Us_Init" with E_NOK return value from the DIO module
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/

	au8_ExpectedOutput=E_NOk;
	DIO_stub_return_value=E_NOk;
	u8_status2 |= Us_Init();
	DIO_stub_return_value=E_ok;
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
	* Test Case: valid calling to "Us_Init" with E_NOK return value from the ICU module
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/

	au8_ExpectedOutput=E_NOk;
	ICU_stub_return_value=E_NOk;
	u8_status4 |= Us_Init();
	ICU_stub_return_value=E_ok;
	if(u8_status4==au8_ExpectedOutput)
	{
		printf("test case 4: PASSED\n");
	}
	else
	{
		printf("test case 4: FAILED\n");
	}


 /****************************************************************************************/


	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: valid calling to "Us_Trigger" without initialization
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/

	au8_ExpectedOutput=E_NOk;
	u8_status6 |= Us_Trigger();
	if(u8_status6==au8_ExpectedOutput)
	{
		printf("test case 6: PASSED\n");
	}
	else
	{
		printf("test case 6: FAILED\n");
	}



	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: valid calling to "Us_Trigger" with initialization
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/

	au8_ExpectedOutput=E_ok;
	u8_status7 |= Us_Init();
	u8_status7 |= Us_Trigger();
	if(u8_status7==au8_ExpectedOutput)
	{
		printf("test case 7: PASSED\n");
	}
	else
	{
		printf("test case 7: FAILED\n");
	}



	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: valid calling to "Us_Trigger" with E_NOK return value from the DIO module
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/

	au8_ExpectedOutput=E_NOk;
	Us_Init();
	DIO_stub_return_value=E_NOk;
	u8_status8 |= Us_Trigger();
	DIO_stub_return_value=E_ok;
	if(u8_status8==au8_ExpectedOutput)
	{
		printf("test case 8: PASSED\n");
	}
	else
	{
		printf("test case 8: FAILED\n");
	}



	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: valid calling to "Us_Trigger" with E_NOK return value from the softwareDelay module
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/

	au8_ExpectedOutput=E_NOk;
	Us_Init();
	Delay_stub_return_value=E_NOk;
	u8_status9 |= Us_Trigger();
	Delay_stub_return_value=E_ok;
	if(u8_status9==au8_ExpectedOutput)
	{
		printf("test case 9: PASSED\n");
	}
	else
	{
		printf("test case 9: FAILED\n");
	}


  /***********************************************************************************/


	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: valid calling to "Us_GetDistance" without initialization
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/

	au8_ExpectedOutput=E_NOk;
	u8_status10 |= Us_GetDistance(&u16_distance);
	if(u8_status10==au8_ExpectedOutput)
	{
		printf("test case 10: PASSED\n");
	}
	else
	{
		printf("test case 10: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: non valid calling to "Us_GetDistance" passing an address of a variable
	* from a different data type.
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/


	au8_ExpectedOutput=E_NOk;
	Us_Init();
	u8_status11 |= Us_GetDistance(&u32_non_valid_distance);
	if(u8_status11==au8_ExpectedOutput)
	{
		printf("test case 11: PASSED\n");
	}
	else
	{
		printf("test case 11: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: non valid calling to "Us_GetDistance" passing NULL as an argument
	* from a different data type.
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	* NOTE: this test case should be commented during the running of the reset test cases
	* since it may cause a code crash if it fails
	************************************************************************************/

	au8_ExpectedOutput=E_NOk;
	Us_Init();
	u8_status12 |= Us_GetDistance(NULL);
	if(u8_status12==au8_ExpectedOutput)
	{
		printf("test case 12: PASSED\n");
	}
	else
	{
		printf("test case 12: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Steering_Init
	* Test Case: valid calling to "Us_GetDistance" with E_NOK return value from the ICU module
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/


	au8_ExpectedOutput=E_NOk;
	Us_Init();
	ICU_stub_return_value=E_NOk;
	u8_status13 |= Us_GetDistance(&u16_distance);
	ICU_stub_return_value=E_ok;
	if(u8_status13==au8_ExpectedOutput)
	{
		printf("test case 13: PASSED\n");
	}
	else
	{
		printf("test case 13: FAILED\n");
	}

	return 0;
}
