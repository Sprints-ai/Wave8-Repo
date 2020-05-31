#include "OS_Test_Casses.h"


#define RESULT_INITIAL_VALUE 5

uint8_t gu8_Timer_Init_Return;
uint8_t gu8_Timer_Start_Return;
uint8_t gu8_Timer_Stop_Return;
uint8_t gu8_Timer_Get_Value_Return;
uint8_t gu8_Timer_Set_Value_Return;
uint8_t gu8_Timer_Get_Status_Return;


void Test_Consumer (void)
{
	printf("\n Hello \n");
}


void OS_Init_Test(void)
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n");
   printf("choose 1 for Test NULL Pointer with taking into consideration timer is working will \n");
   printf("choose 2 for Test NULL Pointer with taking into consideration timer is not working will \n");
   printf("choose 3 for Test not NULL Pointer with taking into consideration timer is working will \n");
   printf("choose 4 for Test not NULL Pointer with taking into consideration timer is not working will \n");
   printf("\n\n");
   printf("The number of the desired function to test is ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
       case 1:OS_Init_Test_Case1(); break;
       case 2:OS_Init_Test_Case2(); break;
       case 3:OS_Init_Test_Case3(); break;
       case 4:OS_Init_Test_Case4(); break;
       default: printf("Invalid Test Case number"); break;
    }
}

/* Test NULL Pointer with taking into consideration timer is working will*/
void OS_Init_Test_Case1()
{
    uint8_t u8_Ret_Status = 0;
    str_OS_InitConfig_t str_ConfigPtr ;
    str_OS_InitConfig_t* pstr_ConfigPtr = NULL;
    gu8_Timer_Init_Return = E_OK;
    u8_Ret_Status = OS_Init (pstr_ConfigPtr );
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
void OS_Init_Test_Case2()
{
    uint8_t u8_Ret_Status = 0;
    str_OS_InitConfig_t str_ConfigPtr ;
    str_OS_InitConfig_t* pstr_ConfigPtr = NULL;
    gu8_Timer_Init_Return = E_NOK;
    u8_Ret_Status = OS_Init (pstr_ConfigPtr );
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

/* Test not NULL Pointer with taking into consideration timer is working will*/
void OS_Init_Test_Case3()
{
    uint8_t u8_Ret_Status = ZERO;
    str_OS_InitConfig_t str_ConfigPtr ;
    str_OS_InitConfig_t* pstr_ConfigPtr = &str_ConfigPtr;
    gu8_Timer_Init_Return = E_OK;
    u8_Ret_Status = OS_Init (pstr_ConfigPtr );
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

/* Test not NULL Pointer with taking into consideration timer is not working will*/
void OS_Init_Test_Case4()
{
    uint8_t u8_Ret_Status = 0;
    str_OS_InitConfig_t str_ConfigPtr ;
    str_OS_InitConfig_t* pstr_ConfigPtr = &str_ConfigPtr;
    gu8_Timer_Init_Return = E_NOK;
    u8_Ret_Status = OS_Init (pstr_ConfigPtr );
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

void Task_Delet_Test(void)
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n");
   printf("choose 1 for Test NULL Pointer \n");
   printf("choose 2 for Test Non NULL Pointer \n");
   printf("choose 3 for Test Stop OS without OS Initialization \n");
   printf("choose 4 for Test Stop OS without OS Start \n");
   printf("\n\n");
   printf("The number of the desired test case is ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
       case 1:Task_Delet_Test_Case1(); break;
       case 2:Task_Delet_Test_Case2(); break;
       case 3:Task_Delet_Test_Case3(); break;
       case 4:Task_Delet_Test_Case4(); break;
       default: printf("Invalid Test Case number"); break;


    }

}

void Task_Delet_Test_Case1()
{
    uint8_t u8_Ret_Status = ZERO;
    void (* p2func)(void) = NULL;
    u8_Ret_Status = Task_Delet(1,p2func);
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

void Task_Delet_Test_Case2()
{
    uint8_t u8_Ret_Status = ZERO;
    str_OS_InitConfig_t str_ConfigPtr ;
    str_OS_InitConfig_t* pstr_ConfigPtr = &str_ConfigPtr;
    OS_Init(pstr_ConfigPtr);
    Task_Creat(2,1,PERIODIC,Test_Consumer);
    Task_Delet(1,Test_Consumer);
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
void Task_Delet_Test_Case3()
{
    uint8_t u8_Ret_Status = ZERO;
    Task_Creat(1,1,PERIODIC,Test_Consumer);
    Task_Delet(1,Test_Consumer);
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


void Task_Delet_Test_Case4()
{
    uint8_t u8_Ret_Status = ZERO;
    str_OS_InitConfig_t str_ConfigPtr ;
    str_OS_InitConfig_t* pstr_ConfigPtr = &str_ConfigPtr;
    OS_Init(pstr_ConfigPtr);
   // Task_Creat(2,1,PERIODIC,Test_Consumer);
    Task_Delet(1,Test_Consumer);
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

/**********************************************************************************************************/
void Task_Creat_Test(void)
{

	uint8_t au8_TestNumber = ZERO;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	uint8_t au8_repeat = ZERO;
    str_OS_InitConfig_t init = {Timer_0};

	while (TRUE)
	{

		printf("Please enter test number: ");

		scanf("%d",&(au8_TestNumber));

		switch (au8_TestNumber)
		{
		/*happy scenario */
		case 1:
			gu8_Timer_Start_Return = E_OK;
			OS_Init(&init);
			au8_Result =  Task_Creat(2,1,PERIODIC,Test_Consumer);
			if (au8_Result == E_OK)
               {
                 printf(" Passed \n ");
               }
            else
               {
                 printf(" Failed  \n ");
               }
			//printf("The expected output is 0  and the actual output is %d \n", au8_Result);
			Error_Print();
			break;


		case 2:
			gu8_Timer_Start_Return = E_OK;
			OS_Init(&init);
			au8_Result =  Task_Creat(2,1,3,Test_Consumer);
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
			break;


		case 3:
			gu8_Timer_Start_Return = E_OK;
			OS_Init(&init);
			au8_Result =  Task_Creat(2,1,ONE_SHOT,NULL);
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
			break;

		case 4:
			gu8_Timer_Start_Return = E_OK;
			au8_Result =  Task_Creat(0,1,3,Test_Consumer);
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
			break;


		case 5:
			gu8_Timer_Start_Return = E_NOK;
			OS_Init(&init);
			au8_Result =  Task_Creat(2,1,ONE_SHOT,Test_Consumer);
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
			break;

		case 6:
            gu8_Timer_Start_Return = E_OK;
            OS_Init(&init);
            Task_Creat(2,1,ONE_SHOT,Test_Consumer);
            au8_Result =  Task_Creat(2,1,PERIODIC,Test_Consumer);
            if (au8_Result == E_NOK)
               {
                 printf(" Passed \n ");
               }
            else
               {
                 printf(" Failed  \n ");
               }
           // printf("The expected output is 1  and the actual output is %d \n", au8_Result);
            Error_Print();
            break;

		default:
			printf("invalid test number");
			break;
		}

		printf("\nTo exit Task_Creat test press E or any char to continue ");
		scanf("%c", &au8_repeat);

		printf(" ");
		scanf("%c", &au8_repeat);

		if ('E'  == au8_repeat)
		{

			break;
		}

		printf(" ");
		scanf("%c", &au8_repeat);
	}

}

/**********************************************************************************************************/
/**************************************************************************************/
void OS_Dinit_Test(void)
{
	uint8_t au8_TestNumber = ZERO;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	uint8_t au8_repeat = ZERO;
	str_OS_InitConfig_t init = {Timer_0};

	while (TRUE)
	{

		printf("Please enter test number: ");

		scanf("%d",&(au8_TestNumber));

		switch (au8_TestNumber)
		{
		case 1:
			OS_Init(&init);
			au8_Result = OS_DeInit();
			if (au8_Result == E_OK)
               {
                 printf(" Passed \n ");
               }
            else
               {
                 printf(" Failed  \n ");
               }

			//printf("The expected output is 0  and the actual output is %d \n", au8_Result);
			Error_Print();
			break;

		case 2:
			au8_Result = OS_DeInit();
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
			break;

		case 3:
			OS_Init(&init);
			Task_Creat(5,1,PERIODIC,Test_Consumer);
			au8_Result = OS_DeInit();
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
			break;


		default:
			printf("invalid test number");
			break;
		}

		printf("\nTo exit Task_Creat test press E or any char to continue ");
		scanf("%c", &au8_repeat);

		printf(" ");
		scanf("%c", &au8_repeat);

		if ('E'  == au8_repeat)
		{

			break;
		}

		printf(" ");
		scanf("%c", &au8_repeat);
	}

}


/***************************************************************************************/





