#include "Tester.h"
#include "SOS.h"


void Test_SOS_Init(void){

    printf("Testing SOS_Init Function\n");
    printf("_______________________________________\n");

      /****************************
    * Target Function: SOS_Init
    * Test Case:  initialization Happy Scenario
    * Expected OUTPUT: E_OK
    ****************************/
    printf("Test case 1:  ");
    if(SOS_Init()==E_OK)
        printf("Passed\n");
     else
         printf("Failed\n");

    /****************************
    * Target Function: SOS_Init
    * Test Case: Multiple initialization
    * Expected OUTPUT: SOS_ERROR+E_MULTIPLE_INITIALIZION
    ****************************/
     printf("Test case 2:  ");
     SOS_Init();
     if(SOS_Init()!=E_OK)
        printf("Passed\n");
     else
         printf("Failed\n");



}
void Test_SOS_DeInit(void){


    printf("\nTesting SOS_DeInit Function\n");
    printf("_______________________________________\n");

    /****************************
    * Target Function: SOS_DeInit
    * Test Case: DeInit without Init
    * Expected OUTPUT: (E_UNINITIALIZED_MODULE + SOS_ERROR)
    ****************************/

     printf("Test case 1:  ");
     if(SOS_DeInit() != E_OK)
          printf("Passed\n");
     else
         printf("Failed\n");


    /****************************
    * Target Function: SOS_DeInit
    * Test Case: DeInit after Init
    * Expected OUTPUT: (E_OK)
    ****************************/

    SOS_Init();

     printf("Test case 2:  ");
     if(SOS_DeInit() == E_OK)
          printf("Passed\n");
     else
         printf("Failed\n");
}



void toggle1(void){

    printf("toggled") ;

}

void Test_SOS_Start(void){

    sint16_t state_error = E_OK ;
 printf("\n \n");

    printf("Testing SOS_Create_Task Function\n");
    printf("_____________\n");

    /************************************************************************************
    * Target Function: SOS_Create_Task
    * Test Case: start before init.
    * Expected OUTPUT: SOS_module_error + MODULE_UNINTIALIZED
    ************************************************************************************/

	SOS_Init();


    /************************************************************************************
    * Target Function: SOS_Create_Task
    * Test Case: null pointer to the struct
    * Expected OUTPUT: SOS_module_error +NULL_PTR_ERROR
    ************************************************************************************/
    SOS_TASK_Cfg *PTR_SOS_task1=NULL ;

    state_error = 	SOS_Create_Task(NULL) ;


    printf("Test case 1 : ");

    if(state_error != E_OK)
        printf("passed \n");
    else
        printf("failed \n");

    /************************************************************************************
    * Target Function: SOS_Create_Task
    * Test Case: invalid parameter (mode != periodic or mode != one shot )
    * Expected OUTPUT: SOS_module_error + INVALID__PARAMETER
    ************************************************************************************/
    SOS_TASK_Cfg SOS_task2 ;
   SOS_task2.Task_id = 1;
	SOS_task2.SOS_MODE = INVALID_PARAMETER_TEST;
	SOS_task2.SOS_Cbk_ptr =toggle1;
	SOS_task2.Delay_TimeMs = 20;
    state_error = 	SOS_Create_Task(&SOS_task2) ;


   printf("Test case 2 : ");

    if(state_error != E_OK)
        printf("passed \n");
    else
        printf("failed \n");




    /************************************************************************************
    * Target Function: SOS_Create_Task
    * Test Case: Null pointer in the parameter Ptr_FunctionCall
    * Expected OUTPUT: SOS_module_error + INVALID__PARAMETER
    ************************************************************************************/
    SOS_TASK_Cfg SOS_task3 ;
    SOS_task3.Delay_TimeMs = 1000;
	SOS_task3.SOS_Cbk_ptr = NULL;
	SOS_task3.Task_id = 3;
	SOS_task3.SOS_MODE = PERIODIC ;

    state_error = 	SOS_Create_Task(&SOS_task3) ;


    printf("Test case 3 : ");

    if(state_error != E_OK)
        printf("passed \n");
    else
        printf("failed \n");




    /************************************************************************************
    * Target Function: SOS_Create_Task
    * Test Case: valid parameters
    * Expected OUTPUT: E_OK
    ************************************************************************************/
    SOS_TASK_Cfg SOS_task4 ;
    SOS_task4.Delay_TimeMs = 1000;
	SOS_task4.SOS_Cbk_ptr = toggle1;
	SOS_task4.Task_id = 4;
	SOS_task4.SOS_MODE = PERIODIC ;

    state_error = 	SOS_Create_Task(&SOS_task4) ;


    printf("Test case 4 : ");

    if(state_error == E_OK)
        printf("passed \n");
    else
        printf("failed \n");


    /************************************************************************************
    * Target Function: SOS_Create_Task
    * Test Case: same task ID
    * Expected OUTPUT: SOS_module_error + INVALID__PARAMETER
    ************************************************************************************/
    SOS_TASK_Cfg SOS_task5 ;
    SOS_task5.Delay_TimeMs = 1000;
	SOS_task5.SOS_Cbk_ptr = toggle1;
	SOS_task5.Task_id = 4;
	SOS_task5.SOS_MODE = PERIODIC ;

    state_error = 	SOS_Create_Task(&SOS_task5) ;


    printf("Test case 5 : ");

    if(state_error != E_OK)
        printf("passed \n" );
    else
        printf("failed \n");



    /************************************************************************************
    * Target Function: SOS_Create_Task
    * Test Case: full buffer
    * Expected OUTPUT: SOS_module_error + FULL_BUFFER
    ************************************************************************************/
    SOS_TASK_Cfg SOS_task6 ;
    SOS_task6.Delay_TimeMs = 1000;
	SOS_task6.SOS_Cbk_ptr = toggle1;
	SOS_task6.Task_id = 6;
	SOS_task6.SOS_MODE = PERIODIC ;

    state_error = 	SOS_Create_Task(&SOS_task6) ;
    state_error = 	SOS_Create_Task(&SOS_task6) ;

    state_error = 	SOS_Create_Task(&SOS_task6) ;

    state_error = 	SOS_Create_Task(&SOS_task6) ;

    SOS_Delete_Task(&SOS_task6) ;
    SOS_Delete_Task(&SOS_task6) ;

    printf("Test case 6 : ");

    if(state_error != E_OK)
        printf("passed \n" );
    else
        printf("failed \n");


    SOS_DeInit();

}

void Test_SOS_Stop(void){

    sint16_t state_error = E_OK ;

    printf("\n \n");
     printf("Testing SOS_Delete_Task Function\n");
    printf("_____________\n");

	SOS_Init();



    /************************************************************************************
    * Target Function: SOS_Delete_Task
    * Test Case: stop task with valid ID
    * Expected OUTPUT: SOS_module_error + INVALID__PARAMETER
    ************************************************************************************/
    SOS_TASK_Cfg SOS_task5 ;
    SOS_task5.Delay_TimeMs = 1000;
	SOS_task5.SOS_Cbk_ptr = toggle1;
	SOS_task5.Task_id = 7;
	SOS_task5.SOS_MODE = PERIODIC ;

    state_error = 	SOS_Create_Task(&SOS_task5) ;

    state_error = 	SOS_Delete_Task(SOS_task5.Task_id) ;
    printf("Test case 7 : ");

    if(state_error == E_OK)
        printf("passed  \n" );
    else
        printf("failed \n");


    /************************************************************************************
    * Target Function: SOS_Delete_Task
    * Test Case: stop task with invalid ID
    * Expected OUTPUT: SOS_module_error + INVALID__PARAMETER
    ************************************************************************************/
    SOS_TASK_Cfg SOS_task6 ;
    SOS_task6.Delay_TimeMs = 1000;
	SOS_task6.SOS_Cbk_ptr = toggle1;
	SOS_task6.Task_id = 8;
	SOS_task6.SOS_MODE = PERIODIC ;

    state_error = 	SOS_Create_Task(&SOS_task6) ;

    SOS_TASK_Cfg SOS_task7 ;
    SOS_task7.Delay_TimeMs = 1000;
	SOS_task7.SOS_Cbk_ptr = toggle1;
	SOS_task7.Task_id = 10;
	SOS_task7.SOS_MODE = PERIODIC ;

    state_error = 	SOS_Delete_Task(&SOS_task7) ;
    printf("Test case 8 : ");

    if(state_error != E_OK)
        printf("passed \n" );
    else
        printf("failed \n");



}


