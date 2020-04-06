/*
*	File name: main.c
*	Author : Ema
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "SOS.h"
#include "SOS_cfg.h"

signed char Testing__SOS_DeInit (void);
signed char Testing__SOS_Init(const SOS_ConfigType * ConfigPtr);
signed char Testing__SOS_Create_Task(const SOS_SW_Task * SW_Task);
signed char Testing__SOS_Delete_Task(const SOS_SW_Task * SW_Task);

signed char expected =E_OK;
signed char actual=E_OK;

SOS_ConfigType valid_test[3]={{TIMER_CH0,1},{TIMER_CH1,2},{TIMER_CH2,3}};
SOS_ConfigType invalid_test[2]={{3,1},{-1,5}};

SOS_SW_Task Create_valid_test[2]={{2,4},{1,1}};
SOS_SW_Task Create_invalid_test[2]={{1,-1},{1,3000000000}};

SOS_SW_Task Delete_valid_test[2]={{2,4},{1,1}};
SOS_SW_Task Delete_invalid_test[2]={{0,1},{1,0}};

SOS_SW_Task Delete_invalid_test_NoStart = {2,1};
SOS_SW_Task *SW_NULL_Pointer_Check=NULL;

SOS_ConfigType*NULL_Pointer_Check=NULL;
int main()
{
     signed char Check_Test=0;

     printf("****************************This is Unit Test for SOS MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_1***********************************************\n-FUNCTION NAME: SOS_DeInit\n-INPUT:VOID\n-EXPECTED OUTPUT:NO_INIT\n");
    Check_Test=Testing__SOS_DeInit();
    expected=NO_INIT;
    actual=Check_Test;
    if(expected==actual){
           printf("-Actual OUTPUT: NO_INIT\n\n");
        printf("TEST CASE PASSED !\n\n");
    }
    else{
          printf("-Actual OUTPUT: NOK\n");
       printf("TEST CASE FAILED !\n\n");
    }




    for(unsigned i=0;i<3;i++){
    printf("****************************This is Unit Test for SOS MODULE***************************************\n*******************************************_API_NO#_3_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: SOS_Init\n-INPUT: timer_CH:=%d---- resolution=%d\n-EXPECTED OUTPUT:OK\n",i+1,valid_test[i].Timer_CH,valid_test[i].Sys_Tick);
    Check_Test=Testing__SOS_Init(&valid_test[i]);
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }

    }

         printf("****************************This is Unit Test for SOS MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_1***********************************************\n-FUNCTION NAME: SOS_DeInit\n-INPUT:VOID\n-EXPECTED OUTPUT:OK\n");
    Check_Test=Testing__SOS_DeInit();
    expected=E_OK;
    actual=Check_Test;
    if(expected==actual){
           printf("-Actual OUTPUT: OK n\n");
        printf("TEST CASE PASSED !\n\n");
    }
    else{
          printf("-Actual OUTPUT: NOK\n");
       printf("TEST CASE FAILED !\n\n");
    }





  for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for SOS MODULE***************************************\n*******************************************_API_NO#_3_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: SOS_Init\n-INPUT: timer_CH:=%d---- resolution=%d\n-EXPECTED OUTPUT:INVALID_PARAM\n",i+1,invalid_test[i].Timer_CH,invalid_test[i].Sys_Tick);
    Check_Test=Testing__SOS_Init(&invalid_test[i]);
      if(Check_Test==INVALID_PARAM){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }

    }



      printf("****************************This is Unit Test for SOS MODULE***************************************\n*******************************************_API_NO#_3_(NULL_PTR)**************************************************\n*****************************************TEST_CASE_NO#_4***********************************************\n-FUNCTION NAME: SOS_Init\n-INPUT:NULL_PTR \n-EXPECTED OUTPUT:OK\n");
    Check_Test=Testing__SOS_Init(NULL_Pointer_Check);
     if(Check_Test==NULL_PTR){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }


for(int j=0; j<5; j++)
{
     for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for SOS MODULE***************************************\n*******************************************_API_NO#_4_VALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: SOS_Create_Task\n-INPUT: Task_delay:=%d---- Task_Priority=%d\n-EXPECTED OUTPUT:OK\n",i+1,Create_valid_test[i].Task_delay,Create_valid_test[i].Task_priority);
    Check_Test=Testing__SOS_Create_Task(&Create_valid_test[i]);
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d!\n\n",Check_Test);
    }

    }
}


    for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for SOS MODULE***************************************\n*******************************************_API_NO#_4_VALID_PARAMS_FULL_BUFFER**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: SOS_Create_Task\n-INPUT: Task_delay:=%d---- Task_Priority=%d\n-EXPECTED OUTPUT:FULL_BUFFER\n",i+1,Create_valid_test[i].Task_delay,Create_valid_test[i].Task_priority);
    Check_Test=Testing__SOS_Create_Task(&Create_valid_test[i]);
      if(Check_Test==FULL_BUFFER){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }

    }


        for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for SOS MODULE***************************************\n*******************************************_API_NO#_4_INVALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: SOS_Create_Task\n-INPUT: Task_delay:=%d---- Task_Priority=%d\n-EXPECTED OUTPUT:INVALID_PARAM\n",i+1,Create_invalid_test[i].Task_delay,Create_invalid_test[i].Task_priority);
    Check_Test=Testing__SOS_Create_Task(&Create_invalid_test[i]);
      if(Check_Test==INVALID_PARAM){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d!\n\n",Check_Test);
    }

    }

printf("****************************This is Unit Test for SOS MODULE***************************************\n*******************************************_API_NO#_4_(NULL_PTR)**************************************************\n*****************************************TEST_CASE_NO#_4***********************************************\n-FUNCTION NAME: SOS_Start\n-INPUT:NULL_PTR \n-EXPECTED OUTPUT:NULL_PTR\n");
     Check_Test=Testing__SOS_Init(NULL_Pointer_Check);
     if(Check_Test==NULL_PTR){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }


   for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for SOS MODULE***************************************\n*******************************************_API_NO#_5_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: SOS_Delete_Task\n-INPUT: Task_delay:=%d---- Task_Priority=%d\n-EXPECTED OUTPUT:OK\n",i+1,Delete_valid_test[i].Task_delay,Delete_valid_test[i].Task_priority);
    Check_Test=Testing__SOS_Delete_Task(&Delete_valid_test[i]);
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d !\n\n", Check_Test);
    }

    }




        for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for SOS MODULE***************************************\n*******************************************_API_NO#_5_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: SOS_Delete_Task\n-INPUT: Task_delay:=%d---- Task_Priority=%d\n-EXPECTED OUTPUT:STOP_NO_START\n",i+1,Delete_invalid_test[i].Task_delay,Delete_invalid_test[i].Task_priority);
    Check_Test=Testing__SOS_Delete_Task(&Delete_invalid_test[i]);
      if(Check_Test==STOP_NO_START){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d!\n\n",Check_Test);
    }

    }


    printf("****************************This is Unit Test for SOS MODULE***************************************\n*******************************************_API_NO#_5_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: SOS_Delete_Task\n-INPUT: Task_delay:=%d---- Task_Priority=%d------\n-EXPECTED OUTPUT:STOP_NO_START\n",3,Delete_invalid_test_NoStart.Task_delay,Delete_invalid_test_NoStart.Task_priority);
    Check_Test=Testing__SOS_Delete_Task(&Delete_invalid_test_NoStart);
      if(Check_Test==STOP_NO_START){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d!\n\n",Check_Test);
    }


    printf("****************************This is Unit Test for SOS MODULE***************************************\n*******************************************_API_NO#_5_(NULL_PTR)**************************************************\n*****************************************TEST_CASE_NO#_4***********************************************\n-FUNCTION NAME: SOS_Stop\n-INPUT:NULL_PTR \n-EXPECTED OUTPUT:NULL_PTR\n");
     Check_Test=Testing__SOS_Delete_Task(SW_NULL_Pointer_Check);
     if(Check_Test==NULL_PTR){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }

    return 0;
}

signed char Testing__SOS_DeInit (void){
 signed char Test_API_2 =E_OK;
   Test_API_2=SOS_DeInit();
return Test_API_2;

}
signed char Testing__SOS_Init(const SOS_ConfigType * ConfigPtr){
     SOS_ConfigType*config;
    config=ConfigPtr;
    signed char Test_API_3=E_OK;
   Test_API_3=SOS_Init(config);
return Test_API_3;
}
signed char Testing__SOS_Create_Task(const SOS_SW_Task * SW_Task){
 SOS_SW_Task*config;
    config=SW_Task;
    signed char Test_API_4=E_OK;
   Test_API_4=SOS_Create_Task(config);
return Test_API_4;
}

signed char Testing__SOS_Delete_Task(const SOS_SW_Task * SW_Task){
 SOS_SW_Task*config;
    config=SW_Task;
    signed char Test_API_5=E_OK;
   Test_API_5=SOS_Delete_Task(config);
return Test_API_5;

}
