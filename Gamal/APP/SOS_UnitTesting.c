/*
 ============================================================================
 Name        : Testing.c
 Author      : Muhammed Gamal
 Description : this file test the ICU driver
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "../Service/SOS.h"


#define NONE_VALID_REPETITION_STATUS 3
#define ONE_SEC 1000
#define HALF_SEC 500
#define INITIAL_VALUE 0
#define INVALID_TASK_TIMER_CH_NUM 3



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

	SOS_Config SOS_InvalidConfigration =
									   {
										   INVALID_TASK_TIMER_CH_NUM,
										   SOS_TICK_RESOLUTIO
									   };
/************************************************************************************
	* Target Function: SOS_InitRunable
	* Test Case: send NULL pointer to "SOS_InitRunable"
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status1 |=SOS_InitRunable(NULL);
	u8_status1 |= SOS_DeInit();
	if(u8_status1==E_ok)
	{
		printf("NULL pointer (test case 1): PASSED\n");
	}
	else
	{
		printf("NULL pointer (test case 1): FAILED\n");
	}


	/************************************************************************************
	* Target Function: Task_Start
	* Test Case: module not_initialized to "Task_Start"
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status2 |=Task_Start(func_call,0,1,1000);
	if(u8_status2==E_ok)
	{
		printf("module not_initialized (test case 2): PASSED\n");
	}
	else
	{
		printf("module not_initialized (test case 2): FAILED\n");
	}

	/************************************************************************************
	* Target Function: SOS_InitRunable
	* Test Case: multiple initialization to "SOS_InitRunable"
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status3 |=SOS_InitRunable(&SOS_Configration);
	u8_status3 |=Task_Start(func_call,1,1,1000);
	u8_status3 |=SOS_InitRunable(&SOS_Configration);
	u8_status3 |= SOS_DeInit();
	if(u8_status3==E_ok)
	{
		printf("multiple initialization (test case 3): PASSED\n");
	}
	else
	{
		printf("multiple initialization (test case 3): FAILED\n");
	}




	/************************************************************************************
	* Target Function: Task_Stop
	* Test Case: stop without start
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status4 |=Task_Stop(1);
	if(u8_status4==E_ok)
	{
		printf("stop without start (test case 4): PASSED\n");
	}
	else
	{
		printf("stop without start (test case 4): FAILED\n");
	}



	/************************************************************************************
	* Target Function: Task_Start
	* Test Case: invalid parameter (repetition)
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status5 |=Task_Start(func_call,0,4,1000);
	if(u8_status5==E_ok)
	{
		printf("invalid parameter (test case 5): PASSED\n");
	}
	else
	{
		printf("invalid parameter (test case 5): FAILED\n");
	}



	/************************************************************************************
	* Target Function: Task_Start
	* Test Case: invalid parameter (called function is null)
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status6 |=Task_Start(NULL,0,1,1000);
	if(u8_status6==E_ok)
	{
		printf("invalid parameter (test case 6): PASSED\n");
	}
	else
	{
		printf("invalid parameter (test case 6): FAILED\n");
	}



	/************************************************************************************
	* Target Function: Task_Start
	* Test Case: invalid parameter (delay is larger than uint16_t)
	* Expected OUTPUT: FAILED
	* Real OUTPUT: PASSED
	************************************************************************************/
	u8_status7 |=Task_Start(NULL,0,1,10000);
	if(u8_status7==E_ok)
	{
		printf("invalid parameter (test case 7): PASSED\n");
	}
	else
	{
		printf("invalid parameter (test case 7): FAILED\n");
	}



	/************************************************************************************
	* Target Function: Task_Start
	* Test Case: multiple stop
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status8 |=SOS_InitRunable(&SOS_Configration);
	u8_status8 |=Task_Start(func_call,1,1,1000);
	u8_status8 |=Task_Stop(1);
	u8_status8 |=Task_Stop(1);
	u8_status8 |= SOS_DeInit();
	if(u8_status8==E_ok)
	{
		printf("multiple stop (test case 8): PASSED\n");
	}
	else
	{
		printf("multiple stop (test case 8): FAILED\n");
	}



	/************************************************************************************
	* Target Function: Task_Start
	* Test Case: multiple start to same the id
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status9 |=SOS_InitRunable(&SOS_Configration);
	u8_status9 |=Task_Start(func_call,1,1,ONE_SEC);
	u8_status9 |=Task_Start(func_call,1,1,HALF_SEC);
	u8_status9 |= SOS_DeInit();
	if(u8_status9==E_ok)
	{
		printf("multiple start (test case 9): PASSED\n");
	}
	else
	{
		printf("multiple start (test case 9): FAILED\n");
	}



	/************************************************************************************
	* Target Function: Task_Start
	* Test Case: valid parameters
	* Expected OUTPUT: PASSED
	* Real OUTPUT: PASSED
	************************************************************************************/
	u8_status10 |=SOS_InitRunable(&SOS_Configration);
	u8_status10 |=Task_Start(func_call,0,1,ONE_SEC);
	u8_status10 |= SOS_DeInit();
	if(u8_status10==E_ok)
	{
		printf("valid parameters (test case 10): PASSED\n");
	}
	else
	{
		printf("valid parameters (test case 10): FAILED\n");
	}



	/************************************************************************************
	* Target Function: Task_Start
	* Test Case: full buffer (buffer is 3)
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/

	u8_status11 |=SOS_InitRunable(&SOS_Configration);
	u8_status11 |=Task_Start(func_call,0,1,1000);
	u8_status11 |=Task_Start(func_call2,1,1,500);
	u8_status11 |=Task_Start(func_call3,2,1,500);
	u8_status11 |=Task_Start(func_call4,3,1,1000);
	u8_status11 |= SOS_DeInit();
	if(u8_status11==E_ok)
	{
		printf("full buffer (test case 11): PASSED\n");
	}
	else
	{
		printf("full buffer (test case 11): FAILED\n");
	}



	/************************************************************************************
	* Target Function: SOS_InitRunable
	* Test Case: invalid parameters in the passed structure "SOS_InitRunable"
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/

	u8_status12 |=SOS_InitRunable(&SOS_InvalidConfigration);
	if(u8_status12==E_ok)
	{
		printf("invalid parameters in the passed structure (test case 12): PASSED\n");
	}
	else
	{
		printf("invalid parameters in the passed structure (test case 12): FAILED\n");
	}


	return 0;
}




