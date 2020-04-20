/*
 ============================================================================
 Name        : Testing.c
 Author      : Muhammed Gamal
 Description : this file test the ICU driver
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "TMU.h"

#define NONE_VALID_TIMER_CH_STATUS 3
#define NONE_VALID_RESOLUTIO_STATUS 3
#define NONE_VALID_REPETITION_STATUS 3
#define ONE_SEC 1000
#define HALF_SEC 500
#define INITIAL_VALUE 0


extern uint8_t timer_stup_return_value;


void func_call(void)
{

}

void func_call2(void)
{

}

void func_call3(void)
{

}

void func_call4(void)
{

}

int main(void)
{
	timer_stup_return_value=E_ok;
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
	uint8_t u8_status14=0;
	uint8_t u8_status15=0;
	uint8_t u8_status16=0;
	uint8_t u8_status17=0;
	uint8_t u8_status18=0;
	uint8_t u8_status19=0;
	uint8_t u8_status20=0;
	TMU_ConfigType InValid_TMU_Configuration_1=
	                                   {
									    NONE_VALID_TIMER_CH_STATUS,
										RESOLUTIO,REPETITION
									   };
	TMU_ConfigType InValid_TMU_Configuration_2=
	                                   {
									    TIMER_CH_NUM,
										NONE_VALID_RESOLUTIO_STATUS,REPETITION
									   };
	TMU_ConfigType InValid_TMU_Configuration_3=
	                                   {
									    TIMER_CH_NUM,
										RESOLUTIO,NONE_VALID_REPETITION_STATUS
									   };
	/************************************************************************************
	* Target Function: TMU_Init
	* Test Case: send NULL pointer to "TMU_Init"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status1 |=TMU_Init(NULL);
	u8_status1 |= TMU_DeInit();
	if(u8_status1==au8_ExpectedOutput)
	{
		printf("test case 1: PASSED\n");
	}
	else
	{
		printf("test case 1: FAILED\n");
	}


	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: module not_initialized to "TMU_Start_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status2 |=TMU_Start(func_call,0,1,ONE_SEC);
	u8_status2 |= TMU_DeInit();
	if(u8_status2==au8_ExpectedOutput)
	{
		printf("test case 2: PASSED\n");
	}
	else
	{
		printf("test case 2: FAILED\n");
	}




	/************************************************************************************
	* Target Function: TMU_Init
	* Test Case: multiple initialization to "TMU_Init"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status3 |=TMU_Init(&TMU_Configuration);
	u8_status3 |=TMU_Init(&TMU_Configuration);
	u8_status3 |= TMU_DeInit();
	if(u8_status3==au8_ExpectedOutput)
	{
		printf("test case 3: PASSED\n");
	}
	else
	{
		printf("test case 3: FAILED\n");
	}




	/************************************************************************************
	* Target Function: TMU_Stop_Timer
	* Test Case: stop without start "TMU_Stop_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status4 |=TMU_Stop(1);
	if(u8_status4==au8_ExpectedOutput)
	{
		printf("test case 4: PASSED\n");
	}
	else
	{
		printf("test case 4: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: invalid parameter (channel id) "TMU_Start_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status5 |=TMU_Start(func_call,15,1,ONE_SEC);
	if(u8_status5==au8_ExpectedOutput)
	{
		printf("test case 5: PASSED\n");
	}
	else
	{
		printf("test case 5: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: invalid parameter (repetition) "TMU_Start_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status6 |=TMU_Start(func_call,0,4,ONE_SEC);
	if(u8_status6==au8_ExpectedOutput)
	{
		printf("test case 6: PASSED\n");
	}
	else
	{
		printf("test case 6: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: invalid parameter (delay) "TMU_Start_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status7 |=TMU_Start(func_call,0,1,99999);
	if(u8_status7==au8_ExpectedOutput)
	{
		printf("test case 7: PASSED\n");
	}
	else
	{
		printf("test case 7: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: invalid parameter (called function is null) "TMU_Start_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status8 |=TMU_Start(NULL,0,1,ONE_SEC);
	if(u8_status8==au8_ExpectedOutput)
	{
		printf("test case 8: PASSED\n");
	}
	else
	{
		printf("test case 8: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: multiple stop to the same id "TMU_Stop_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status9 |=TMU_Init(&TMU_Configuration);
	u8_status9 |=TMU_Start(func_call,1,1,1000);
	u8_status9 |=TMU_Stop(1);
	u8_status9 |=TMU_Stop(1);
	u8_status9 |= TMU_DeInit();
	if(u8_status9==au8_ExpectedOutput)
	{
		printf("test case 9: PASSED\n");
	}
	else
	{
		printf("test case 9: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: multiple start to the same id "TMU_Start_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status10 |=TMU_Init(&TMU_Configuration);
	u8_status10 |=TMU_Start(func_call,1,1,ONE_SEC);
	u8_status10 |=TMU_Start(func_call,1,1,HALF_SEC);
	u8_status10 |= TMU_DeInit();
	if(u8_status10==au8_ExpectedOutput)
	{
		printf("test case 10: PASSED\n");
	}
	else
	{
		printf("test case 10: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: full buffer (buffer is 3)"TMU_Start_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status11 |=TMU_Init(&TMU_Configuration);
	u8_status11 |=TMU_Start(func_call,0,1,ONE_SEC);
	u8_status11 |=TMU_Start(func_call2,1,1,HALF_SEC);
	u8_status11 |=TMU_Start(func_call3,2,1,HALF_SEC);
	u8_status11 |=TMU_Start(func_call4,3,1,ONE_SEC);
	u8_status11 |= TMU_DeInit();
	if(u8_status11==au8_ExpectedOutput)
	{
		printf("test case 11: PASSED\n");
	}
	else
	{
		printf("test case 11: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Init
	* Test Case: invalid parameters in the passed structure "TMU_Init" (invalid timer channel)
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status12 |=TMU_Init(&InValid_TMU_Configuration_1);
	u8_status12 |= TMU_DeInit();
	if(u8_status12==au8_ExpectedOutput)
	{
		printf("test case 12: PASSED\n");
	}
	else
	{
		printf("test case 12: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Init
	* Test Case: invalid parameters in the passed structure "TMU_Init" (invalid resolution)
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status13 |=TMU_Init(&InValid_TMU_Configuration_2);
	u8_status13 |= TMU_DeInit();
	if(u8_status13==au8_ExpectedOutput)
	{
		printf("test case 13: PASSED\n");
	}
	else
	{
		printf("test case 13: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Init
	* Test Case: invalid parameters in the passed structure "TMU_Init" (invalid repetition)
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status14 |=TMU_Init(&InValid_TMU_Configuration_3);
	u8_status14 |= TMU_DeInit();
	if(u8_status14==au8_ExpectedOutput)
	{
		printf("test case 14: PASSED\n");
	}
	else
	{
		printf("test case 14: FAILED\n");
	}




	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: valid TMU calling with E_NOk return value from the "Timer_Init"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	timer_stup_return_value=E_NOk;   /*Enforce a E_NOk return value from the timer stub*/
	u8_status15 |=TMU_Init(&TMU_Configuration);
	timer_stup_return_value=E_ok;   /*Enforce a E_ok return value from the timer stub*/
	u8_status15 |=TMU_Start(func_call,0,1,ONE_SEC);
	u8_status15 |= TMU_DeInit();
	if(u8_status15==au8_ExpectedOutput)
	{
		printf("test case 15: PASSED\n");
	}
	else
	{
		printf("test case 15: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: valid TMU calling with E_NOk return value from the "Timer_Start"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	timer_stup_return_value=E_ok;   /*Enforce a E_ok return value from the timer stub*/
	au8_ExpectedOutput=E_NOk;
	u8_status16 |=TMU_Init(&TMU_Configuration);
	timer_stup_return_value=E_NOk;   /*Enforce a E_NOk return value from the timer stub*/
	u8_status16 |=TMU_Start(func_call,0,1,ONE_SEC);
	timer_stup_return_value=E_ok;   /*Enforce a E_ok return value from the timer stub*/
	u8_status16 |= TMU_DeInit();
	if(u8_status16==au8_ExpectedOutput)
	{
		printf("test case 16: PASSED\n");
	}
	else
	{
		printf("test case 16: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: valid TMU calling with E_NOk return value from the "Timer_DeInit"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	timer_stup_return_value=E_ok;   /*Enforce a E_ok return value from the timer stub*/
	au8_ExpectedOutput=E_NOk;
	u8_status17 |=TMU_Init(&TMU_Configuration);
	u8_status17 |=TMU_Start(func_call,0,1,ONE_SEC);
	timer_stup_return_value=E_NOk;   /*Enforce a E_NOk return value from the timer stub*/
	u8_status17 |= TMU_DeInit();
	if(u8_status17==au8_ExpectedOutput)
	{
		printf("test case 17: PASSED\n");
	}
	else
	{
		printf("test case 17: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: valid parameters"TMU_Start_Timer" (only on channel)
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/
	timer_stup_return_value=E_ok;
	au8_ExpectedOutput=E_ok;
	u8_status18 |=TMU_Init(&TMU_Configuration);
	u8_status18 |=TMU_Start(func_call,0,1,ONE_SEC);
	u8_status18 |=TMU_Stop(0);
	u8_status18 |= TMU_DeInit();
	if(u8_status18==au8_ExpectedOutput)
	{
		printf("test case 18: PASSED\n");
	}
	else
	{
		printf("test case 18: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: valid parameters"TMU_Start_Timer" (multiples channels)
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_ok;
	u8_status19 |=TMU_Init(&TMU_Configuration);
	u8_status19 |=TMU_Start(func_call,0,1,ONE_SEC);
	u8_status19 |=TMU_Start(func_call2,1,1,ONE_SEC);
	u8_status19 |=TMU_Start(func_call3,2,1,ONE_SEC);
	u8_status19 |=TMU_Stop(0);
	u8_status19 |=TMU_Stop(2);
	u8_status19 |= TMU_DeInit();
	if(u8_status19==au8_ExpectedOutput)
	{
		printf("test case 19: PASSED\n");
	}
	else
	{
		printf("test case 19: FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: valid parameters"TMU_Start_Timer" (multiples channels)
	* start channel 2 then stop channel 2 then start channel 2 again
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_ok;
	u8_status20 |=TMU_Init(&TMU_Configuration);
	u8_status20 |=TMU_Start(func_call,0,1,ONE_SEC);
	u8_status20 |=TMU_Start(func_call2,1,1,ONE_SEC);
	u8_status20 |=TMU_Start(func_call3,2,1,ONE_SEC);
	u8_status20 |=TMU_Stop(0);
	u8_status20 |=TMU_Stop(2);
	u8_status20 |=TMU_Start(func_call3,2,1,ONE_SEC);
	u8_status20 |= TMU_DeInit();
	if(u8_status20==au8_ExpectedOutput)
	{
		printf("test case 20: PASSED\n");
	}
	else
	{
		printf("test case 20: FAILED\n");
	}



	return 0;
}




