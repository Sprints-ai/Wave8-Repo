/*
 * Sos_Test_Cases.c
 *
 * Created: 3/11/2020 2:07:45 AM
 * Author : A_ayman
 */

/*
*** Inclusions
*/
#include "Sos_Test_Cases.h"
#define RESULT_INITIAL_VALUE 5


/*
*** local functions Implementations
*/

//this function is used only for test
static void Test_Consumer (void)
{
	printf("\n Hello \n");
}

/*
***implementation of interface functions
*/

/*
*** Sos Init Test Cases
*/
void Sos_Init_Test(void)
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n");

   printf("choose 1 for Test happy scenario of initialization task \n");
   printf("choose 2 for Test NULL Pointer with taking into consideration timer is working will \n");
   printf("choose 3 for Test NULL Pointer with taking into consideration timer is not working will \n");
   printf("choose 4 for Test not NULL Pointer with taking into consideration timer is not working will \n");
   printf("\n\n");
   printf("The number of the desired function to test is ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
       case 1:SOS_Init_Test_Case1(); break;
       case 2:SOS_Init_Test_Case2(); break;
       case 3:SOS_Init_Test_Case3(); break;
       case 4:SOS_Init_Test_Case4(); break;
       default: printf("Invalid Test Case number"); break;
    }
}

/* Test not NULL Pointer with taking into consideration timer is working will*/
void SOS_Init_Test_Case1()
{
    uint8_t u8_Ret_Status = ZERO;
    gstr_SOS_InitConfig_t str_ConfigPtr ;
    gstr_SOS_InitConfig_t* pstr_ConfigPtr = &str_ConfigPtr;
    gu8_Timer_Init_Return = E_OK;
    u8_Ret_Status =  Sos_Init (pstr_ConfigPtr );
     if (u8_Ret_Status == E_OK)
       {
         printf(" Passed \n ");
       }
    else
       {
         printf(" Failed  \n ");
       }
    Error_Print();
}

/* Test NULL Pointer with taking into consideration timer is working will*/
void SOS_Init_Test_Case2()
{
    uint8_t u8_Ret_Status = 0;
    gstr_SOS_InitConfig_t str_ConfigPtr ;
    gstr_SOS_InitConfig_t * pstr_ConfigPtr = NULL;
    gu8_Timer_Init_Return = E_OK;
    u8_Ret_Status = Sos_Init (pstr_ConfigPtr );
    if (u8_Ret_Status == E_NOK)
       {
         printf(" Passed \n ");
       }
    else
       {
         printf(" Failed  \n ");
       }
    Error_Print();
}

/* Test NULL Pointer with taking into consideration timer is not working will*/
void SOS_Init_Test_Case3()
{
    uint8_t u8_Ret_Status = 0;
    gstr_SOS_InitConfig_t tstr_ConfigPtr ;
    gstr_SOS_InitConfig_t* pstr_ConfigPtr = NULL;
    gu8_Timer_Init_Return = E_NOK;
    u8_Ret_Status =  Sos_Init (pstr_ConfigPtr );
    if (u8_Ret_Status == E_NOK)
    {
       printf(" Passed \n ");
    }
    else
    {
       printf(" Failed  \n ");
    }
    Error_Print();
}

/* Test not NULL Pointer with taking into consideration timer is not working will*/
void SOS_Init_Test_Case4()
{
    uint8_t u8_Ret_Status = 0;
    gstr_SOS_InitConfig_t str_ConfigPtr ;
    gstr_SOS_InitConfig_t* pstr_ConfigPtr = &str_ConfigPtr;
    gu8_Timer_Init_Return = E_NOK;
    u8_Ret_Status =  Sos_Init (pstr_ConfigPtr );
    if (u8_Ret_Status == E_NOK)
    {
         printf(" Passed \n ");
    }
    else
    {
         printf(" Failed  \n ");
    }
    Error_Print();
}

/*
*** Sos Delete Test Cases
*/
void Sos_Delete_Task_Test(void)
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n");
   printf("choose 1 for Test happy scenario of deleting task \n");
   printf("choose 2 for Test Deleting Task without Initialization \n");
   printf("choose 3 for Test Deleting Task without creating it\n");
   printf("choose 4 for Test Deleting while the buffer is empty \n");

   printf("\n\n");
   printf("The number of the desired test case is ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
       case 1:Sos_Delete_Task_Test_Case1(); break;
       case 2:Sos_Delete_Task_Test_Case2(); break;
       case 3:Sos_Delete_Task_Test_Case3(); break;
       case 4:Sos_Delete_Task_Test_Case4(); break;
       default: printf("Invalid Test Case number"); break;


    }

}


/*for Test happy scenario of deleting task*/
void Sos_Delete_Task_Test_Case1()
{
    uint8_t u8_Ret_Status = ZERO;
    gstr_SOS_InitConfig_t  init = {Timer_0};
	gu8_Timer_Start_Return = E_OK;
	Sos_Init(&init);
    gstr_Task_Info_t str_Task_1 = {0,1,PERIODIC,Test_Consumer};
	Sos_Create_Task(&str_Task_1 );
    u8_Ret_Status = Sos_Delete_Task(0);
    if (u8_Ret_Status == E_OK)
    {
     printf(" Passed \n ");
    }
    else
    {
     printf(" Failed  \n ");
   }
    Error_Print();
}


/*for Test Deleting while Sos not initialized*/
void Sos_Delete_Task_Test_Case2()
{
    uint8_t u8_Ret_Status = ZERO;
    u8_Ret_Status = Sos_Delete_Task(1);
    if (u8_Ret_Status == E_NOK)
       {
         printf(" Passed \n ");
       }
    else
       {
         printf(" Failed  \n ");
       }
    Error_Print();
}

/*for Test Deleting Task without creating*/
void Sos_Delete_Task_Test_Case3()
{
    uint8_t u8_Ret_Status = ZERO;
    gstr_SOS_InitConfig_t str_ConfigPtr= {Timer_0} ;
    gstr_SOS_InitConfig_t* pstr_ConfigPtr = &str_ConfigPtr;
    gu8_Timer_Init_Return = E_OK;
    Sos_Init(pstr_ConfigPtr);
    gstr_Task_Info_t str_Task_1 = {2,1,PERIODIC,Test_Consumer};
	Sos_Create_Task(&str_Task_1 );
    u8_Ret_Status = Sos_Delete_Task(1);
    if (u8_Ret_Status == E_NOK)
    {
     printf(" Passed \n ");
    }
    else
    {
     printf(" Failed  \n ");
   }
    Error_Print();
}

/*for Test Deleting while the buffer is empty */
void Sos_Delete_Task_Test_Case4()
{
	uint8_t u8_Ret_Status = ZERO;
	gstr_SOS_InitConfig_t str_ConfigPtr ;
	gstr_SOS_InitConfig_t* pstr_ConfigPtr = &str_ConfigPtr;
	u8_Ret_Status = Sos_Init(pstr_ConfigPtr);
	u8_Ret_Status = Sos_Delete_Task(1);
	if (u8_Ret_Status == E_NOK)
	{
		printf(" Passed \n ");
	}
	else
	{
		printf(" Failed  \n ");
	}
	Error_Print();
}

/*
*** Sos Create Test Cases
*/

void Sos_Create_Task_Test(void)
{
	uint8_t au8_Test_Case_Number = ZERO;
	printf("Please Enter the number of the required Test case \n");
	printf("choose 1 for Test happy scenario \n");
	printf("choose 2 for Test NULL Pointer of the structure we insert\n");
	printf("choose 3 for Test NULL Pointer of the elements of structure we insert \n");
	printf("choose 4 for Test Invalid Parameter of the Periodicity like make it 0 \n");
	printf("choose 5 for Test Creating task without Initialization the module \n");
	printf("\n\n");
	printf("The number of the desired test case is ");
	scanf("%d",&au8_Test_Case_Number);
	printf("\n");
	switch (au8_Test_Case_Number)
	{
		case 1:Sos_Create_Task_Test_Case1(); break;
		case 2:Sos_Create_Task_Test_Case2(); break;
		case 3:Sos_Create_Task_Test_Case3(); break;
		case 4:Sos_Create_Task_Test_Case4(); break;
		case 5:Sos_Create_Task_Test_Case5(); break;

		default: printf("Invalid Test Case number"); break;


	}

}

/*for Test happy scenario*/
void Sos_Create_Task_Test_Case1()
{
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	gstr_SOS_InitConfig_t  init = {Timer_0};

	gu8_Timer_Start_Return = E_OK;
	Sos_Init(&init);
    gstr_Task_Info_t str_Task_1 = {2,1,PERIODIC,Test_Consumer};

	au8_Result =  Sos_Create_Task(&str_Task_1 );
	if (au8_Result == E_OK)
	{
		printf(" Passed \n ");
	}
	else
	{
		printf(" Failed  \n ");
	}
	Error_Print();
}

/*Test NULL Pointer of the elements of structure we insert*/
void Sos_Create_Task_Test_Case3()
{
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	gstr_SOS_InitConfig_t init = {Timer_0};
	Sos_Init(&init);
	gstr_Task_Info_t str_Task_1 = {1,2,PERIODIC,NULL};
	au8_Result =  Sos_Create_Task(&str_Task_1 );
	if (au8_Result== E_NOK)
	{
		printf(" Passed \n ");
	}
	else
	{
		printf(" Failed  \n ");
	}
	Error_Print();
}

/*Test NULL Pointer of the elements of structure we insert*/
void Sos_Create_Task_Test_Case4()
{
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
    gstr_SOS_InitConfig_t init = {Timer_0};
	Sos_Init(&init);
	gstr_Task_Info_t str_Task_1 = {1,0,PERIODIC,Test_Consumer};
	au8_Result =  Sos_Create_Task(&str_Task_1 );
	if (au8_Result== E_NOK)
	{
		printf(" Passed \n ");
	}
	else
	{
		printf(" Failed  \n ");
	}
	Error_Print();
}


/*Test NULL Pointer of the structure we insert*/
void Sos_Create_Task_Test_Case2()
{
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	gstr_SOS_InitConfig_t init = {Timer_0};
	Sos_Init(&init);
	gstr_Task_Info_t* str_Task_1 = NULL ;
	au8_Result =  Sos_Create_Task( str_Task_1);
	if (au8_Result== E_NOK)
	{
		printf(" Passed \n ");
	}
	else
	{
		printf(" Failed  \n ");
	}
	//printf("The expected output is 1  and the actual output is %d \n", au8_Result);
	Error_Print();
}


/*for Test Creating task without Initialization the module*/
void Sos_Create_Task_Test_Case5()
{
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	gstr_SOS_InitConfig_t  init = {Timer_0};
	gu8_Timer_Start_Return = E_OK;
	gstr_Task_Info_t str_Task_1 = {1,2,PERIODIC,NULL};
	au8_Result =  Sos_Create_Task(&str_Task_1 );
	if (au8_Result == E_NOK)
	{
		printf(" Passed \n ");
	}
	else
	{
		printf(" Failed  \n ");
	}
	Error_Print();
}

/*
*** Deinit Test Cases
*/
void Sos_Deinit_Task_Test(void)
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n");
   printf("choose 1 for Test Happy scenario for Deinit \n");
   printf("choose 2 for Test Deinit SOS without initializing it  \n");
   printf("choose 3 for Test Deinit SOS while sos is serving tasks \n");

   printf("\n\n");
   printf("The number of the desired test case is ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
       case 1:Sos_Deinit_Task_Test_Case1(); break;
       case 2:Sos_Deinit_Task_Test_Case2(); break;
       case 3:Sos_Deinit_Task_Test_Case3(); break;
       default: printf("Invalid Test Case number"); break;
    }

}


/*for Test Happy scenario for Deinit*/
void Sos_Deinit_Task_Test_Case1()
{
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	gstr_SOS_InitConfig_t init = {Timer_0};
    Sos_Init(&init);
    au8_Result = Sos_DeInit();
    if (au8_Result == E_OK)
    {
        printf(" Passed \n ");
    }
    else
    {
        printf(" Failed  \n ");
    }
    Error_Print();

}

/*for Test Deinit SOS without initializing it */
void Sos_Deinit_Task_Test_Case2()
{
    uint8_t au8_Result = RESULT_INITIAL_VALUE;
    au8_Result = Sos_DeInit();
    if (au8_Result == E_NOK)
    {
        printf(" Passed \n ");
    }
    else
    {
        printf(" Failed  \n ");
    }
    //printf("The expected output is 1  and the actual output is %d \n", au8_Result);
    Error_Print();
}

/* Deinit SOS while sos is serving tasks*/
void Sos_Deinit_Task_Test_Case3()
{
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	gstr_SOS_InitConfig_t init = {Timer_0};
	Sos_Init(&init);
    gstr_Task_Info_t str_Task_1 = {5,1,PERIODIC,Test_Consumer};
	au8_Result =  Sos_Create_Task(&str_Task_1 );
	au8_Result = Sos_DeInit();
	if (au8_Result == E_NOK)
	{
		printf(" Passed \n ");
	}
	else
	{
		printf(" Failed  \n ");
	}
	//printf("The expected output is 1  and the actual output is %d \n", au8_Result);
	Error_Print();

}



