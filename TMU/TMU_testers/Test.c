
#include "Test.h"
#include <stdio.h>

extern TMU_ConfigType TMU_Config;

void TMU_Init_Test(void)
{
	ERROR_STATUS ERR = E_OK;
	
	/********** TEST CASE 1 ***********/
	/*passing invalid parameter in the configuration struct
	expected output 202 which maps to module ID + Invalid parameter error ID */
	
	TMU_Config.Timer_Channel=TIMER_CH1;
	ERR = TMU_Init();

	if (ERR == 202)
	{
		printf("TMU_Init Test Case 1 : Passed \n");
	}
	else
	{
		printf("TMU_Init Test Case 1 : Failed \n");
	}
	
	/********** TEST CASE 2 ***********/
	/*reinitializing TMU 
	expected output 204 which maps to module ID + module already initialized */
	
	TMU_Config.Timer_Channel=TIMER_CH0;
	TMU_Init();
	ERR = TMU_Init();
	
	
	if (ERR == 204)
	{
		printf("TMU_Init Test Case 2 : Passed \n");
	}
	else
	{
		printf("TMU_Init Test Case 2 : Failed \n");
	}
	
	/********** TEST CASE 3 ***********/
	/* witting a valid code
	expected output 0 which maps to no error */
	
	TMU_DeInit();
	ERR = TMU_Init();
	
	if (ERR == 0)
	{
		printf("TMU_Init Test Case 3 : Passed \n");
	}
	else
	{
		printf("TMU_Init Test Case 3 : Failed \n");
	}
	/*********************************/
	TMU_DeInit();
	printf("\n");
}

void TMU_DeInit_Test(void){		
	ERROR_STATUS ERR = E_OK;
	
	/********** TEST CASE 1 ***********/
	/*de_initializing TMU before initializing it
	expected output 203 which maps to module ID + module not initialized */
	ERR = TMU_DeInit();
	if (ERR == 203)
	{
		printf("TMU_DeInit Test Case 1 : Passed \n");
	}
	else
	{
		printf("TMU_DeInit Test Case 1 : Failed \n");
	}
	/********** TEST CASE 2 ***********/
	/* writing a valid code 
	expected output 0 which maps to no error */
	
	TMU_Config.Timer_Channel = TIMER_CH0;
	TMU_Init();
	ERR = TMU_DeInit();
	if (ERR == 0)
	{
		printf("TMU_DeInit Test Case 2 : Passed \n");
	}
	else
	{
		printf("TMU_DeInit Test Case 2 : Failed \n");
	}
	printf("\n");
}

void TMU_Start_Timer_Test()
{
	ERROR_STATUS ERR = E_OK;
	
	/********** TEST CASE 1 ***********/
	/*starting TMU without initialization 
	expected output 203 which maps to module ID + module not initialized */

	ERR = TMU_Start_Timer(10,TMU_Init_Test,1000,PERIODIC);
	
	if (ERR == 203)
	{
		printf("TMU_Start_Timer Test Case 1 : Passed \n");
	}
	else
	{
		printf("TMU_Start_Timer Test Case 1 : Failed \n");
	}
	
	/********** TEST CASE 2 ***********/
	/* passing a null pointer as the function pointer 
	expected output 201 which maps to module ID + NULL pointer error */
	
	TMU_Config.Timer_Channel = TIMER_CH0;
	TMU_Init();
	ERR = TMU_Start_Timer(10,NULL,1000,PERIODIC);
	if (ERR == 201)
	{
		printf("TMU_Start_Timer Test Case 2 : Passed \n");
	}
	else
	{
		printf("TMU_Start_Timer Test Case 2 : Failed \n");
	}
	/********** TEST CASE 3 ***********/
	/* writing a valid code 
	expected output 0 which maps to no error */
	
	ERR = TMU_Start_Timer(10,TMU_Init_Test,1000,PERIODIC);
	
	if (ERR == 0)
	{
		printf("TMU_Start_Timer Test Case 3 : Passed \n");
	}
	else
	{
		printf("TMU_Start_Timer Test Case 3 : Failed \n");
	}
	
	/********** TEST CASE 4 ***********/
	/* adding a new value after the buffer is full 
	expected output 207 which maps to module ID + buffer is full */
	
	uint8_t u8_Iterator = 0;
	for(u8_Iterator = 0 ; u8_Iterator<(BUFFER_SIZE-1) ; u8_Iterator++)
	{
		TMU_Start_Timer(10,TMU_Init_Test,1000,PERIODIC);
	}
	ERR = TMU_Start_Timer(10,TMU_Init_Test,1000,PERIODIC);
	if (ERR == 207)
	{
		printf("TMU_Start_Timer Test Case 4 : Passed \n");
	}
	else
	{
		printf("TMU_Start_Timer Test Case 4 : Failed \n");
	}
	printf("\n");
}

void TMU_Stop_Timer_Test()
{
	ERROR_STATUS ERR = E_OK;
	TMU_DeInit();
	
	/********** TEST CASE 1 ***********/
	/* stopping a task that's not started (does not exist in the buffer)
	expected output 202 which maps to module ID + invalid parameter error */
	
	TMU_Config.Timer_Channel = TIMER_CH0;
	TMU_Init();
	TMU_Start_Timer(10,TMU_Init_Test,1000,PERIODIC);
	ERR = TMU_Stop_Timer(20);
	
	if (ERR == 202)
	{
		printf("TMU_Stop_Timer Test Case 1 : Passed \n");
	}
	else
	{
		printf("TMU_Stop_Timer Test Case 1 : Failed \n");
	}
	
	/********** TEST CASE 2 ***********/
	/* writing a valid code (stopping a task that exists in the buffer)
	expected output 0 which maps to no error */
	
	ERR = TMU_Stop_Timer(10);
	
	if (ERR == 0)
	{
		printf("TMU_Stop_Timer Test Case 2 : Passed \n");
	}
	else
	{
		printf("TMU_Stop_Timer Test Case 2 : Failed \n");
	}
	printf("\n");
}

void TMU_Dispatch_Test()
{
	ERROR_STATUS ERR = E_OK;
	TMU_DeInit();
	
	/********** TEST CASE 1 ***********/
	/* dispatching before initializing the TMU
	expected output 203 which maps module ID + module not initialized */
	
	ERR = TMU_Dispatch();
	if (ERR == 203)
	{
		printf("TMU_Dispatch Test Case 1 : Passed \n");
	}
	else
	{
		printf("TMU_Dispatch Test Case 1 : Failed \n");
	}
	
	/********** TEST CASE 2 ***********/
	/* dispatching before starting any task (buffer is empty) 
	expected output 0 which maps to no error */
	
	TMU_Init();
	ERR = TMU_Dispatch();
	if (ERR == 0)
	{
		printf("TMU_Dispatch Test Case 2 : Passed \n");
	}

	else
	{
		printf("TMU_Dispatch Test Case 2 : Failed \n");
	}
	
	/********** TEST CASE 3 ***********/
	/* writing a valid code 
	expected output 0 which maps to no error */
	
	TMU_Start_Timer(10,TMU_Init_Test,1000,PERIODIC);
	ERR = TMU_Dispatch();
	if (ERR == 0)
	{
		printf("TMU_Dispatch Test Case 3 : Passed \n");
	}
	else
	{
		printf("TMU_Dispatch Test Case 3 : Failed \n");
	}
	printf("\n");
}

void main (void)
{
	TMU_Init_Test();
	TMU_DeInit_Test();
	TMU_Start_Timer_Test();
	TMU_Stop_Timer_Test();
	TMU_Dispatch_Test();
	while(1);
}
