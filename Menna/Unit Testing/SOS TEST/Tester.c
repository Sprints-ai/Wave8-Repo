

#include "SOS.h"
#include"Tester.h"

#define SOS_BUFFER_SIZE  5

#define INVALID_PARAMETER_TEST 5


void Test_SOS_Init(void){

    SOS_Cfg_s SOSCfg;
    printf("Testing SOS_Init Function\n");
    printf("_______________________________________\n");

    /****************************
    * Target Function: SOS_Init
    * Test Case: Passing Null pointer
    * Expected OUTPUT: SOS_ERROR+E_NULL_PTR
    ****************************/
    printf("Test case 1:  ");
    if(SOS_Init(NULL)!=E_OK)
        printf("Passed\n");
    else
         printf("Failed\n");

     /****************************
    * Target Function: SOS_Init
    * Test Case: passing SOS_Cfg_s with timer Channel 0
    * Expected OUTPUT: E_OK
    ****************************/
     printf("Test case 2:  ");
     SOS_DeInit(&SOSCfg);
     SOSCfg.Timer_channel = SOS_TIMER_CH0;
     SOSCfg.SOS_Reselution = 5 ;
     if(SOS_Init(&SOSCfg)== E_OK)
        printf("Passed\n");
    else
         printf("Failed\n");

     /****************************
    * Target Function: SOS_Init
    * Test Case: passing SOS_Cfg_s with timer Channel 1
    * Expected OUTPUT: E_OK
    ****************************/
     printf("Test case 3:  ");
     SOS_DeInit(&SOSCfg);
     SOSCfg.Timer_channel = SOS_TIMER_CH1;
     SOSCfg.SOS_Reselution = 5 ;
     if(SOS_Init(&SOSCfg)==E_OK)
        printf("Passed\n");
    else
         printf("Failed\n");
     /****************************
    * Target Function: SOS_Init
    * Test Case: passing SOS_Cfg_s with timer Channel 2
    * Expected OUTPUT: E_OK
    ****************************/
     printf("Test case 4:  ");
     SOS_DeInit(&SOSCfg);
     SOSCfg.Timer_channel = SOS_TIMER_CH2;
     SOSCfg.SOS_Reselution = 5 ;
     if(SOS_Init(&SOSCfg)==E_OK)
        printf("Passed\n");
    else
         printf("Failed\n");
     /****************************
    * Target Function: SOS_Init
    * Test Case: passing SOS_Cfg_s with timer Channel 3
    * Expected OUTPUT: SOS_ERROR+E_INVALID_PARAMETER
    ****************************/
     printf("Test case 5:  ");
     SOS_DeInit(&SOSCfg);
     SOSCfg.Timer_channel = 3;
     if(SOS_Init(&SOSCfg)!=E_OK)
        printf("Passed\n");
     else
         printf("Failed\n");

      /****************************
    * Target Function: SOS_Init
    * Test Case: Multiple initialization
    * Expected OUTPUT: SOS_ERROR+E_MULTIPLE_INITIALIZION
    ****************************/
     printf("Test case 6:  ");
     SOSCfg.Timer_channel = SOS_TIMER_CH2;
     SOS_Init(&SOSCfg);
     SOSCfg.Timer_channel = SOS_TIMER_CH2;
     if(SOS_Init(&SOSCfg)!=E_OK)
        printf("Passed\n");
     else
         printf("Failed\n");
    SOS_DeInit(&SOSCfg);
}


void Test_SOS_DeInit(void){

    SOS_Cfg_s SOSCfg;
    printf("\nTesting SOS_DeInit Function\n");
    printf("_______________________________________\n");

    /****************************
    * Target Function: SOS_DeInit
    * Test Case: DeInit without Init
    * Expected OUTPUT: (E_UNINITIALIZED_MODULE + SOS_ERROR)
    ****************************/

     printf("Test case 1:  ");
     if(SOS_DeInit(&SOSCfg) != E_OK)
          printf("Passed\n");
     else
         printf("Failed\n");


    /****************************
    * Target Function: SOS_DeInit
    * Test Case: DeInit after Init
    * Expected OUTPUT: (E_OK)
    ****************************/
    SOSCfg.Timer_channel = SOS_TIMER_CH2;
    SOS_Init(&SOSCfg);

     printf("Test case 2:  ");
     if(SOS_DeInit(&SOSCfg) == E_OK)
          printf("Passed\n");
     else
         printf("Failed\n");
}






void toggle1(void){

    printf("toggled") ;

}

void Test_SOS_Create(void){

    sint16_t state_error = E_OK ;


    printf("Testing SOS_Start_Timer Function\n");
    printf("_____________\n");

    /************************************************************************************
    * Target Function: SOS_Start_Timer
    * Test Case: start before init.
    * Expected OUTPUT: SOS_module_error + MODULE_UNINTIALIZED
    ************************************************************************************/




    SOS_Cfg_s SOS_Cfg_s1 ;
	SOS_Cfg_s1.Timer_channel = SOS_TIMER_CH2 ;
	SOS_Cfg_s1.SOS_Reselution = reselution_one_mili ;

	SOS_Init(&SOS_Cfg_s1);


    /************************************************************************************
    * Target Function: SOS_Start_Timer
    * Test Case: null pointer to the struct
    * Expected OUTPUT: SOS_module_error +NULL_PTR_ERROR
    ************************************************************************************/
    SOS_tsak_s *PTR_SOS_task1=NULL ;

    state_error = 	SOS_Create_Task(PTR_SOS_task1) ;


    printf("Test case 1 : ");

    if(state_error != E_OK)
        printf("passed \n");
    else
        printf("failed \n");

    /************************************************************************************
    * Target Function: SOS_Start_Timer
    * Test Case: invalid parameter (mode != periodic or mode != one shot )
    * Expected OUTPUT: SOS_module_error + INVALID__PARAMETER
    ************************************************************************************/
    SOS_tsak_s SOS_task2 ;
    SOS_task2.delay_time = 1000;
	SOS_task2.Ptr_FunctionCall = toggle1;
	SOS_task2.Task_ID = 2;
	SOS_task2.SOS_mode = INVALID_PARAMETER_TEST ;

    state_error = 	SOS_Create_Task(&SOS_task2) ;


    printf("Test case 2 : ");

    if(state_error != E_OK)
        printf("passed \n");
    else
        printf("failed \n");




    /************************************************************************************
    * Target Function: SOS_Start_Timer
    * Test Case: Null pointer in the parameter Ptr_FunctionCall
    * Expected OUTPUT: SOS_module_error + INVALID__PARAMETER
    ************************************************************************************/
    SOS_tsak_s SOS_task3 ;
    SOS_task3.delay_time = 1000;
	SOS_task3.Ptr_FunctionCall = NULL;
	SOS_task3.Task_ID = 3;
	SOS_task3.SOS_mode = PERIODIC ;

    state_error = 	SOS_Create_Task(&SOS_task3) ;


    printf("Test case 3 : ");

    if(state_error != E_OK)
        printf("passed \n");
    else
        printf("failed \n");




    /************************************************************************************
    * Target Function: SOS_Start_Timer
    * Test Case: valid parameters
    * Expected OUTPUT: E_OK
    ************************************************************************************/
    SOS_tsak_s SOS_task4 ;
    SOS_task4.delay_time = 1000;
	SOS_task4.Ptr_FunctionCall = toggle1;
	SOS_task4.Task_ID = 4;
	SOS_task4.SOS_mode = PERIODIC ;

    state_error = SOS_Create_Task(&SOS_task4) ;


    printf("Test case 4 : ");

    if(state_error == E_OK)
        printf("passed \n");
    else
        printf("failed \n");


    /************************************************************************************
    * Target Function: SOS_Start_Timer
    * Test Case: same task ID
    * Expected OUTPUT: SOS_module_error + INVALID__PARAMETER
    ************************************************************************************/
    SOS_tsak_s SOS_task5 ;
    SOS_task5.delay_time = 1000;
	SOS_task5.Ptr_FunctionCall = toggle1;
	SOS_task5.Task_ID = 4;
	SOS_task5.SOS_mode = PERIODIC ;

    state_error = SOS_Create_Task(&SOS_task5) ;


    printf("Test case 5 : ");

    if(state_error != E_OK)
        printf("passed \n" );
    else
        printf("failed \n");



    /************************************************************************************
    * Target Function: SOS_Start_Timer
    * Test Case: full buffer
    * Expected OUTPUT: SOS_module_error + FULL_BUFFER
    ************************************************************************************/
    SOS_tsak_s SOS_task6 ;
    SOS_task6.delay_time = 1000;
	SOS_task6.Ptr_FunctionCall = toggle1;
	SOS_task6.Task_ID = 6;
	SOS_task6.SOS_mode = PERIODIC ;

    state_error = SOS_Create_Task(&SOS_task6) ;
    state_error = SOS_Create_Task(&SOS_task6) ;

    state_error = SOS_Create_Task(&SOS_task6) ;

    state_error = SOS_Create_Task(&SOS_task6) ;

    SOS_Remove_Task(&SOS_task6) ;
    SOS_Remove_Task(&SOS_task6) ;

    printf("Test case 6 : ");

    if(state_error != E_OK)
        printf("passed \n" );
    else
        printf("failed \n");



}


void Test_SOS_Remove(void){

    sint16_t state_error = E_OK ;

    printf("\n \n");
     printf("Testing SOS_Stop_Timer Function\n");
    printf("_____________\n");


    SOS_Cfg_s SOS_Cfg_s1 ;
	SOS_Cfg_s1.Timer_channel = SOS_TIMER_CH2 ;
	SOS_Cfg_s1.SOS_Reselution = reselution_one_mili ;

	SOS_Init(&SOS_Cfg_s1);



    /************************************************************************************
    * Target Function: SOS_Stop_Timer
    * Test Case: stop task with valid ID
    * Expected OUTPUT: SOS_module_error + INVALID__PARAMETER
    ************************************************************************************/
    SOS_tsak_s SOS_task5 ;
    SOS_task5.delay_time = 1000;
	SOS_task5.Ptr_FunctionCall = toggle1;
	SOS_task5.Task_ID = 7;
	SOS_task5.SOS_mode = PERIODIC ;

    state_error = 	SOS_Create_Task(&SOS_task5) ;

    //state_error = 	SOS_Stop_Timer(&SOS_task5) ;
    printf("Test case 7 : ");

    if(state_error == E_OK)
        printf("passed  \n" );
    else
        printf("failed \n");


    /************************************************************************************
    * Target Function: SOS_Stop_Timer
    * Test Case: stop task with invalid ID
    * Expected OUTPUT: SOS_module_error + INVALID__PARAMETER
    ************************************************************************************/
    SOS_tsak_s SOS_task6 ;
    SOS_task6.delay_time = 1000;
	SOS_task6.Ptr_FunctionCall = toggle1;
	SOS_task6.Task_ID = 8;
	SOS_task6.SOS_mode = PERIODIC ;

    state_error = 	SOS_Create_Task(&SOS_task6) ;

    SOS_tsak_s SOS_task7 ;
    SOS_task7.delay_time = 1000;
	SOS_task7.Ptr_FunctionCall = toggle1;
	SOS_task7.Task_ID = 10;
	SOS_task7.SOS_mode = PERIODIC ;

    state_error = SOS_Remove_Task(&SOS_task7) ;
    printf("Test case 8 : ");

    if(state_error != E_OK)
        printf("passed \n" );
    else
        printf("failed \n");



}


