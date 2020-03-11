
#include "Test.h"
#include <stdio.h>

extern SOS_ConfigType SOS_Config;

void SOS_Init_Test(void)
{
	ERROR_STATUS ERR = E_OK;
	
	/********** TEST CASE 1 ***********/
	/*passing invalid parameter in the configuration struct
	expected output 202 which maps to module ID + Invalid parameter error ID */
	
	SOS_Config.Timer_Channel = TIMER_CH1;
	ERR = SOS_Init();

	if (ERR == 202)
	{
		printf("SOS_Init Test Case 1 : Passed \n");
	}
	else
	{
		printf("SOS_Init Test Case 1 : Failed \n");
	}
	
	/********** TEST CASE 2 ***********/
	/*reinitializing SOS 
	expected output 204 which maps to module ID + module already initialized */
	
	SOS_Config.Timer_Channel=TIMER_CH0;
	SOS_Init();
	ERR = SOS_Init();
	
	
	if (ERR == 204)
	{
		printf("SOS_Init Test Case 2 : Passed \n");
	}
	else
	{
		printf("SOS_Init Test Case 2 : Failed \n");
	}
	
	/********** TEST CASE 3 ***********/
	/* witting a valid code
	expected output 0 which maps to no error */
	
	SOS_DeInit();
	ERR = SOS_Init();
	
	if (ERR == 0)
	{
		printf("SOS_Init Test Case 3 : Passed \n");
	}
	else
	{
		printf("SOS_Init Test Case 3 : Failed \n");
	}
	/*********************************/
	SOS_DeInit();
	printf("\n");
}

void SOS_DeInit_Test(void){		
	ERROR_STATUS ERR = E_OK;
	
	/********** TEST CASE 1 ***********/
	/*de_initializing SOS before initializing it
	expected output 203 which maps to module ID + module not initialized */
	ERR = SOS_DeInit();
	if (ERR == 203)
	{
		printf("SOS_DeInit Test Case 1 : Passed \n");
	}
	else
	{
		printf("SOS_DeInit Test Case 1 : Failed \n");
	}
	/********** TEST CASE 2 ***********/
	/* writing a valid code 
	expected output 0 which maps to no error */
	
	SOS_Config.Timer_Channel = TIMER_CH0;
	SOS_Init();
	ERR = SOS_DeInit();
	if (ERR == 0)
	{
		printf("SOS_DeInit Test Case 2 : Passed \n");
	}
	else
	{
		printf("SOS_DeInit Test Case 2 : Failed \n");
	}
	printf("\n");
}

void SOS_Create_Test()
{
	ERROR_STATUS ERR = E_OK;
	
	/********** TEST CASE 1 ***********/
	/*starting SOS without initialization 
	expected output 203 which maps to module ID + module not initialized */

	ERR = SOS_Create(10,SOS_Init_Test,1000,PERIODIC);
	
	if (ERR == 203)
	{
		printf("SOS_Create Test Case 1 : Passed \n");
	}
	else
	{
		printf("SOS_Create Test Case 1 : Failed \n");
	}
	
	/********** TEST CASE 2 ***********/
	/* passing a null pointer as the function pointer 
	expected output 201 which maps to module ID + NULL pointer error */
	
	SOS_Config.Timer_Channel = TIMER_CH0;
	SOS_Init();
	ERR = SOS_Create(10,NULL,1000,PERIODIC);
	if (ERR == 201)
	{
		printf("SOS_Create Test Case 2 : Passed \n");
	}
	else
	{
		printf("SOS_Create Test Case 2 : Failed \n");
	}
	/********** TEST CASE 3 ***********/
	/* writing a valid code 
	expected output 0 which maps to no error */
	
	ERR = SOS_Create(10,SOS_Init_Test,1000,PERIODIC);
	
	if (ERR == 0)
	{
		printf("SOS_Create Test Case 3 : Passed \n");
	}
	else
	{
		printf("SOS_Create Test Case 3 : Failed \n");
	}
	
	/********** TEST CASE 4 ***********/
	/* adding a new value after the buffer is full 
	expected output 207 which maps to module ID + buffer is full */
	
	uint8_t u8_Iterator = 0;
	for(u8_Iterator = 0 ; u8_Iterator<(BUFFER_SIZE-1) ; u8_Iterator++)
	{
		SOS_Create(10,SOS_Init_Test,1000,PERIODIC);
	}
	ERR = SOS_Create(10,SOS_Init_Test,1000,PERIODIC);
	if (ERR == 207)
	{
		printf("SOS_Create Test Case 4 : Passed \n");
	}
	else
	{
		printf("SOS_Create Test Case 4 : Failed \n");
	}
	printf("\n");
}

void SOS_Delete_Test()
{
	ERROR_STATUS ERR = E_OK;
	SOS_DeInit();
	
	/********** TEST CASE 1 ***********/
	/* stopping a task that's not started (does not exist in the buffer)
	expected output 202 which maps to module ID + invalid parameter error */
	
	SOS_Config.Timer_Channel = TIMER_CH0;
	SOS_Init();
	SOS_Create(10,SOS_Init_Test,1000,PERIODIC);
	ERR = SOS_Delete(20);
	
	if (ERR == 202)
	{
		printf("SOS_Delete Test Case 1 : Passed \n");
	}
	else
	{
		printf("SOS_Delete Test Case 1 : Failed \n");
	}
	
	/********** TEST CASE 2 ***********/
	/* writing a valid code (stopping a task that exists in the buffer)
	expected output 0 which maps to no error */
	
	ERR = SOS_Delete(10);
	
	if (ERR == 0)
	{
		printf("SOS_Delete Test Case 2 : Passed \n");
	}
	else
	{
		printf("SOS_Delete Test Case 2 : Failed \n");
	}
	printf("\n");
}

void main (void)
{
	SOS_Init_Test();
	SOS_DeInit_Test();
	SOS_Create_Test();
	SOS_Delete_Test();
	while(1);
}
