#include "Tester.h"
#include "TMU.h"

void Test_TMU_Init(void){

    TMU_Cfg tmuCfg;
    printf("Testing TMU_Init Function\n");
    printf("_______________________________________\n");

    /****************************
    * Target Function: TMU_Init
    * Test Case: Passing Null pointer
    * Expected OUTPUT: TMU_ERROR+E_NULL_PTR
    ****************************/
    printf("Test case 1:  ");
    if(TMU_Init(NULL)!=E_OK)
        printf("Passed\n");
    else
         printf("Failed\n");

     /****************************
    * Target Function: TMU_Init
    * Test Case: passing TMU_Cfg with timer Channel 0
    * Expected OUTPUT: E_OK
    ****************************/
     printf("Test case 2:  ");
     TMU_DeInit();
     tmuCfg.TIM_Ch = TMU_TIMER_CH0;
     if(TMU_Init(&tmuCfg)==E_OK)
        printf("Passed\n");
    else
         printf("Failed\n");

     /****************************
    * Target Function: TMU_Init
    * Test Case: passing TMU_Cfg with timer Channel 1
    * Expected OUTPUT: E_OK
    ****************************/
     printf("Test case 3:  ");
     TMU_DeInit();
     tmuCfg.TIM_Ch = TMU_TIMER_CH1;
     if(TMU_Init(&tmuCfg)==E_OK)
        printf("Passed\n");
    else
         printf("Failed\n");
     /****************************
    * Target Function: TMU_Init
    * Test Case: passing TMU_Cfg with timer Channel 2
    * Expected OUTPUT: E_OK
    ****************************/
     printf("Test case 4:  ");
     TMU_DeInit();
     tmuCfg.TIM_Ch = TMU_TIMER_CH2;
     if(TMU_Init(&tmuCfg)==E_OK)
        printf("Passed\n");
    else
         printf("Failed\n");
     /****************************
    * Target Function: TMU_Init
    * Test Case: passing TMU_Cfg with timer Channel 3
    * Expected OUTPUT: TMU_ERROR+E_INVALID_PARAMETER
    ****************************/
     printf("Test case 5:  ");
     TMU_DeInit();
     tmuCfg.TIM_Ch = 3;
     if(TMU_Init(&tmuCfg)!=E_OK)
        printf("Passed\n");
     else
         printf("Failed\n");

      /****************************
    * Target Function: TMU_Init
    * Test Case: Multiple initialization
    * Expected OUTPUT: TMU_ERROR+E_MULTIPLE_INITIALIZION
    ****************************/
     printf("Test case 6:  ");
     tmuCfg.TIM_Ch = TMU_TIMER_CH2;
     TMU_Init(&tmuCfg);
     tmuCfg.TIM_Ch = TMU_TIMER_CH2;
     if(TMU_Init(&tmuCfg)!=E_OK)
        printf("Passed\n");
     else
         printf("Failed\n");

}


void Test_TMU_DeInit(void){

    TMU_Cfg tmuCfg;
    printf("\nTesting TMU_DeInit Function\n");
    printf("_______________________________________\n");

    /****************************
    * Target Function: TMU_DeInit
    * Test Case: DeInit without Init
    * Expected OUTPUT: (E_UNINITIALIZED_MODULE + TMU_ERROR)
    ****************************/

     printf("Test case 1:  ");
     if(TMU_DeInit() != E_OK)
          printf("Passed\n");
     else
         printf("Failed\n");


    /****************************
    * Target Function: TMU_DeInit
    * Test Case: DeInit after Init
    * Expected OUTPUT: (E_OK)
    ****************************/
    tmuCfg.TIM_Ch = TMU_TIMER_CH2;
    TMU_Init(&tmuCfg);

     printf("Test case 2:  ");
     if(TMU_DeInit() == E_OK)
          printf("Passed\n");
     else
         printf("Failed\n");
}



void toggle1(void){

    printf("toggled") ;

}

void Test_TMU_Start(void){

    sint16_t state_error = E_OK ;
 printf("\n \n");

    printf("Testing TMU_Start_Timer Function\n");
    printf("_____________\n");

    /************************************************************************************
    * Target Function: TMU_Start_Timer
    * Test Case: start before init.
    * Expected OUTPUT: TMU_module_error + MODULE_UNINTIALIZED
    ************************************************************************************/




    TMU_Cfg TMU_cfg1 ;
	TMU_cfg1.TIM_Ch = TMU_TIMER_CH2 ;

	TMU_Init(&TMU_cfg1);


    /************************************************************************************
    * Target Function: TMU_Start_Timer
    * Test Case: null pointer to the struct
    * Expected OUTPUT: TMU_module_error +NULL_PTR_ERROR
    ************************************************************************************/
    TMU_TASK_Cfg *PTR_TMU_task1=NULL ;

    state_error = 	TMU_Start_Timer(NULL) ;


    printf("Test case 1 : ");

    if(state_error != E_OK)
        printf("passed \n");
    else
        printf("failed \n");

    /************************************************************************************
    * Target Function: TMU_Start_Timer
    * Test Case: invalid parameter (mode != periodic or mode != one shot )
    * Expected OUTPUT: TMU_module_error + INVALID__PARAMETER
    ************************************************************************************/
    TMU_TASK_Cfg TMU_task2 ;
   TMU_task2.Task_id = 1;
	TMU_task2.TMU_MODE = INVALID_PARAMETER_TEST;
	TMU_task2.TMU_Cbk_ptr =toggle1;
	TMU_task2.Delay_TimeMs = 20;
    state_error = 	TMU_Start_Timer(&TMU_task2) ;


   printf("Test case 2 : ");

    if(state_error != E_OK)
        printf("passed \n");
    else
        printf("failed \n");




    /************************************************************************************
    * Target Function: TMU_Start_Timer
    * Test Case: Null pointer in the parameter Ptr_FunctionCall
    * Expected OUTPUT: TMU_module_error + INVALID__PARAMETER
    ************************************************************************************/
    TMU_TASK_Cfg TMU_task3 ;
    TMU_task3.Delay_TimeMs = 1000;
	TMU_task3.TMU_Cbk_ptr = NULL;
	TMU_task3.Task_id = 3;
	TMU_task3.TMU_MODE = PERIODIC ;

    state_error = 	TMU_Start_Timer(&TMU_task3) ;


    printf("Test case 3 : ");

    if(state_error != E_OK)
        printf("passed \n");
    else
        printf("failed \n");




    /************************************************************************************
    * Target Function: TMU_Start_Timer
    * Test Case: valid parameters
    * Expected OUTPUT: E_OK
    ************************************************************************************/
    TMU_TASK_Cfg TMU_task4 ;
    TMU_task4.Delay_TimeMs = 1000;
	TMU_task4.TMU_Cbk_ptr = toggle1;
	TMU_task4.Task_id = 4;
	TMU_task4.TMU_MODE = PERIODIC ;

    state_error = 	TMU_Start_Timer(&TMU_task4) ;


    printf("Test case 4 : ");

    if(state_error == E_OK)
        printf("passed \n");
    else
        printf("failed \n");


    /************************************************************************************
    * Target Function: TMU_Start_Timer
    * Test Case: same task ID
    * Expected OUTPUT: TMU_module_error + INVALID__PARAMETER
    ************************************************************************************/
    TMU_TASK_Cfg TMU_task5 ;
    TMU_task5.Delay_TimeMs = 1000;
	TMU_task5.TMU_Cbk_ptr = toggle1;
	TMU_task5.Task_id = 4;
	TMU_task5.TMU_MODE = PERIODIC ;

    state_error = 	TMU_Start_Timer(&TMU_task5) ;


    printf("Test case 5 : ");

    if(state_error != E_OK)
        printf("passed \n" );
    else
        printf("failed \n");



    /************************************************************************************
    * Target Function: TMU_Start_Timer
    * Test Case: full buffer
    * Expected OUTPUT: TMU_module_error + FULL_BUFFER
    ************************************************************************************/
    TMU_TASK_Cfg TMU_task6 ;
    TMU_task6.Delay_TimeMs = 1000;
	TMU_task6.TMU_Cbk_ptr = toggle1;
	TMU_task6.Task_id = 6;
	TMU_task6.TMU_MODE = PERIODIC ;

    state_error = 	TMU_Start_Timer(&TMU_task6) ;
    state_error = 	TMU_Start_Timer(&TMU_task6) ;

    state_error = 	TMU_Start_Timer(&TMU_task6) ;

    state_error = 	TMU_Start_Timer(&TMU_task6) ;

    TMU_Stop_Timer(&TMU_task6) ;
    TMU_Stop_Timer(&TMU_task6) ;

    printf("Test case 6 : ");

    if(state_error != E_OK)
        printf("passed \n" );
    else
        printf("failed \n");


    TMU_DeInit();

}

void Test_TMU_Stop(void){

    sint16_t state_error = E_OK ;

    printf("\n \n");
     printf("Testing TMU_Stop_Timer Function\n");
    printf("_____________\n");


    TMU_Cfg TMU_cfg1 ;
	TMU_cfg1.TIM_Ch = TMU_TIMER_CH2 ;

	TMU_Init(&TMU_cfg1);



    /************************************************************************************
    * Target Function: TMU_Stop_Timer
    * Test Case: stop task with valid ID
    * Expected OUTPUT: TMU_module_error + INVALID__PARAMETER
    ************************************************************************************/
    TMU_TASK_Cfg TMU_task5 ;
    TMU_task5.Delay_TimeMs = 1000;
	TMU_task5.TMU_Cbk_ptr = toggle1;
	TMU_task5.Task_id = 7;
	TMU_task5.TMU_MODE = PERIODIC ;

    state_error = 	TMU_Start_Timer(&TMU_task5) ;

    state_error = 	TMU_Stop_Timer(TMU_task5.Task_id) ;
    printf("Test case 7 : ");

    if(state_error == E_OK)
        printf("passed  \n" );
    else
        printf("failed \n");


    /************************************************************************************
    * Target Function: TMU_Stop_Timer
    * Test Case: stop task with invalid ID
    * Expected OUTPUT: TMU_module_error + INVALID__PARAMETER
    ************************************************************************************/
    TMU_TASK_Cfg TMU_task6 ;
    TMU_task6.Delay_TimeMs = 1000;
	TMU_task6.TMU_Cbk_ptr = toggle1;
	TMU_task6.Task_id = 8;
	TMU_task6.TMU_MODE = PERIODIC ;

    state_error = 	TMU_Start_Timer(&TMU_task6) ;

    TMU_TASK_Cfg TMU_task7 ;
    TMU_task7.Delay_TimeMs = 1000;
	TMU_task7.TMU_Cbk_ptr = toggle1;
	TMU_task7.Task_id = 10;
	TMU_task7.TMU_MODE = PERIODIC ;

    state_error = 	TMU_Stop_Timer(&TMU_task7) ;
    printf("Test case 8 : ");

    if(state_error != E_OK)
        printf("passed \n" );
    else
        printf("failed \n");



}


