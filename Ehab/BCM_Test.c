#include <stdio.h>
#include "BCM.h"
#include "BCM_Test.h"
#include "Errors.h"


void BCM_Init_Test(void)
{
	ERROR_STATUS ERR = E_OK;
	ERR = BCM_Init();
		
	if (ERR == E_OK)
	{
		printf("Test case 1 for BCM_Init : Passed \n");
	}	
	else 
	{
		printf("Test case 1 for BCM_Init : Failed \n");
	}
		
	ERR = BCM_Init();
		
	if (ERR == (BCM_MODULE_ID + ERROR_MODULE_ALREADY_INITIALIZED))
	{
		printf("Test case 2 for BCM_Init : Passed \n");
	}
	else
	{
		printf("Test case 2 for BCM_Init : Failed \n");
	}
	BCM_DeInit();
	
printf("\n");
}
	
void BCM_DeInit_Test(void)
{
	
	ERROR_STATUS ERR = E_OK;
	
	/************** test case 1 ***********/
	
	ERR = BCM_DeInit();
	
	if (ERR == BCM_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED)
	{
		printf("Test case 1 for BCM_DeInit : Passed \n");
	}
	else
	{
		printf("Test case 1 for BCM_DeInit : Failed \n");
	}

	BCM_Init();
	
	/************** test case 2 ***********/
	
	ERR = BCM_DeInit();
	
	if (ERR == E_OK)
	{
		printf("Test case 2 for BCM_DeInit : Passed \n");
	}
	else
	{
		printf("Test case 2 for BCM_DeInit : Failed \n");
	}
printf("\n");
}
	
void BCM_Send_Test(void)
{
	ERROR_STATUS ERR = E_OK;
	/************** test case 1 ***********/
	
	ERR = BCM_Send(NULL,50);
	
	if (ERR == (BCM_MODULE_ID + ERROR_NULL_POINTER))
	{
		printf("Test case 1 for BCM_Send : Passed \n");
	}
	else
	{
		printf("Test case 1 for BCM_Send : Failed \n");
	}
	
	/************** test case 2 ***********/
	uint8_t au8_data[10];
	ERR = BCM_Send(au8_data,50);
	
	if (ERR == (BCM_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED))
	{
		printf("Test case 2 for BCM_Send : Passed \n");
	}
	else
	{
		printf("Test case 2 for BCM_Send : Failed \n");
	}
	
	/************** test case 3 ***********/
	BCM_Init();
	ERR = BCM_Send(au8_data,50);
	
	if (ERR == (E_OK))
	{
		printf("Test case 3 for BCM_Send : Passed \n");
	}
	else
	{
		printf("Test case 3 for BCM_Send : Failed \n");
	}
	BCM_DeInit();
printf("\n");
}

void BCM_Receive_Test(void)
{
	ERROR_STATUS ERR = E_OK;
	/************** test case 1 ***********/
	
	ERR = BCM_Receive(NULL);
	
	if (ERR == (BCM_MODULE_ID + ERROR_NULL_POINTER))
	{
		printf("Test case 1 for BCM_Receive : Passed \n");
	}
	else
	{
		printf("Test case 1 for BCM_Receive : Failed \n");
	}
	
	/************** test case 2 ***********/
	uint8_t au8_data[10];
	ERR = BCM_Receive(au8_data);
	
	if (ERR == (BCM_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED))
	{
		printf("Test case 2 for BCM_Receive : Passed \n");
	}
	else
	{
		printf("Test case 2 for BCM_Receive : Failed \n");
	}
	
	/************** test case 3 ***********/
	BCM_Init();
	ERR = BCM_Receive(au8_data);
	
	if (ERR == (E_OK))
	{
		printf("Test case 3 for BCM_Receive : Passed \n");
	}
	else
	{
		printf("Test case 3 for BCM_Receive : Failed \n");
	}
	BCM_DeInit();
printf("\n");
}

void BCM_RxDispatch_Test(void)
{
	/*	test case 1 : calling the function without calling the BCM_Init and BCM_Send
		test case 2 : calling the function without calling the BCM_Send and with BCM_Init
		test case 3 : calling the function without calling the BCM_Init and with BCM_Send
		test case 4 : Happy scenario!
	*/
	
	ERROR_STATUS ERR = E_OK;
	uint8_t au8_data[10];
	/************** test case 1 ***********/
	ERR = BCM_RxDispatch();
	if (ERR == (BCM_MODULE_ID  + ERROR_MODULE_NOT_INITIALIZED))
	{
		printf("Test case 1 for BCM_RxDispatch : Passed \n");
	}
	else
	{
		printf("Test case 1 for BCM_RxDispatch : Failed \n");
	}	
	 
	/************** test case 2 ***********/
	BCM_Init();
	ERR = BCM_RxDispatch();
	if (ERR == (BCM_MODULE_ID  + ERROR_MODULE_NOT_INITIALIZED))
	{
		printf("Test case  for BCM_RxDispatch : Passed \n");
	}
	else
	{
		printf("Test case 2 for BCM_RxDispatch : Failed \n");
	}
	
	/************** test case 3 ***********/
	
	BCM_DeInit();
	BCM_Receive(au8_data);
	ERR = BCM_RxDispatch();
	if (ERR == (BCM_MODULE_ID  + ERROR_MODULE_NOT_INITIALIZED))
	{
		printf("Test case 3 for BCM_RxDispatch : Passed \n");
	}
	else
	{
		printf("Test case 3 for BCM_RxDispatch : Failed \n");
	}
	
	/************** test case 4 ***********/
	BCM_Init();
	BCM_Receive(au8_data);
	ERR = BCM_RxDispatch();
	if (ERR == (E_OK))
	{
		printf("Test case 4 for BCM_RxDispatch : Passed \n");
	}
	else
	{
		printf("Test case 4 for BCM_RxDispatch : Failed \n");
	}	
	BCM_DeInit();  
printf("\n");
}

void BCM_TxDispatch_Test(void)
{
	/*	test case 1 : calling the function without calling the BCM_Init and BCM_Send
		test case 2 : calling the function without calling the BCM_Send and with BCM_Init
		test case 3 : calling the function without calling the BCM_Init and with BCM_Send
		test case 4 : Happy scenario!
	*/
	ERROR_STATUS ERR = 0;	
	uint8_t au8_data[10];
	/************** test case 1 ***********/
	ERR = BCM_TxDispatch();
	
	if (ERR == (BCM_MODULE_ID  + ERROR_MODULE_NOT_INITIALIZED))
	{
		printf("Test case 1 for BCM_TxDispatch : Passed \n");
		
	}
	else
	{
		printf("Test case 1 for BCM_TxDispatch : Failed \n");
	}
	
	/************** test case 2 ***********/
	BCM_Init();
	ERR = BCM_TxDispatch();
	if (ERR == (BCM_MODULE_ID  + ERROR_MODULE_NOT_INITIALIZED))
	{
		printf("Test case 3 for BCM_TxDispatch : Passed \n");
	}
	else
	{
		printf("Test case 3 for BCM_TxDispatch : Failed \n");
	}
	
	/************** test case 3 ***********/
	BCM_DeInit();
	BCM_Send(au8_data,10);
	ERR = BCM_TxDispatch();
	if (ERR == (BCM_MODULE_ID  + ERROR_MODULE_NOT_INITIALIZED))
	{
		printf("Test case 3 for BCM_TxDispatch : Passed \n");
	}
	else
	{
		printf("Test case 3 for BCM_TxDispatch : Failed \n");
	}
	
	/************** test case 4 ***********/
	BCM_Init();
	BCM_Send(au8_data,10);
	ERR = BCM_TxDispatch();
	if (ERR == (E_OK))
	{
		printf("Test case 4 for BCM_TxDispatch : Passed \n");
	}
	else
	{
		printf("Test case 4 for BCM_TxDispatch : Failed \n");
	}
printf("\n");
}

int main(){
	BCM_TxDispatch_Test();

	BCM_RxDispatch_Test();
	
	BCM_Init_Test();

	BCM_DeInit_Test();

	BCM_Send_Test();

	BCM_Receive_Test();

	while(1);

	 	
	return 0;
}