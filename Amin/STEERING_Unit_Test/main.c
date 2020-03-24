/*
*	File name: main.c
*	Author : Amin
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "TMU.h"
#include "TMU_cfg.h"

signed char Testing__TMU_Dispatch(void);
signed char Testing__TMU_DeInit (void);
signed char Testing__TMU_Init(const TMU_ConfigType * ConfigPtr);
signed char Testing__TMU_Start_Timer(const TMU_SW_Timer * SW_Timer);
signed char Testing__TMU_Stop_Timer(const TMU_SW_Timer * SW_Timer);

signed char expected =E_OK;
signed char actual=E_OK;

TMU_ConfigType valid_test[3]={{TIMER_CH0,1},{TIMER_CH1,2},{TIMER_CH2,3}};
TMU_ConfigType invalid_test[2]={{3,1},{-1,5}};

TMU_SW_Timer Start_valid_test[2]={{0,32767,ONESHOOT},{1,1,ONESHOOT}};
TMU_SW_Timer Start_invalid_test[4]={{0,1,3},{1,-1,1},{1,3000000000,1},{1,1,-1}};

TMU_SW_Timer Stop_valid_test[2]={{0,32767,ONESHOOT},{1,1,ONESHOOT}};
TMU_SW_Timer Stop_invalid_test[2]={{0,1,3},{1,1,-1}};

TMU_SW_Timer Stop_invalid_test_NoStart = {2,1,1};
TMU_SW_Timer *SW_NULL_Pointer_Check=NULL;

TMU_ConfigType*NULL_Pointer_Check=NULL;
int main()
{
     signed char Check_Test=0;
     printf("****************************This is Unit Test for TMU MODULE***************************************\n*******************************************_API_NO#_1_**************************************************\n*****************************************TEST_CASE_NO#_1***********************************************\n-FUNCTION NAME: TMU_Dispatch\n-INPUT:VOID\n-EXPECTED OUTPUT:OK\n");
     Check_Test=Testing__TMU_Dispatch();
     expected=E_OK;
    actual=Check_Test;
    if(expected==actual){
           printf("-Actual OUTPUT: OK\n\n");
        printf("TEST CASE PASSED !\n\n");
    }
    else{
          printf("-Actual OUTPUT: NOK\n");
       printf("TEST CASE FAILED !\n\n");
    }


     printf("****************************This is Unit Test for TMU MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_1***********************************************\n-FUNCTION NAME: TMU_DeInit\n-INPUT:VOID\n-EXPECTED OUTPUT:NO_INIT\n");
    Check_Test=Testing__TMU_DeInit();
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
    printf("****************************This is Unit Test for TMU MODULE***************************************\n*******************************************_API_NO#_3_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: TMU_Init\n-INPUT: timer_CH:=%d---- resolution=%d\n-EXPECTED OUTPUT:OK\n",i+1,valid_test[i].Timer_CH,valid_test[i].resloution);
    Check_Test=Testing__TMU_Init(&valid_test[i]);
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }

    }

         printf("****************************This is Unit Test for TMU MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_1***********************************************\n-FUNCTION NAME: TMU_DeInit\n-INPUT:VOID\n-EXPECTED OUTPUT:OK\n");
    Check_Test=Testing__TMU_DeInit();
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
    printf("****************************This is Unit Test for TMU MODULE***************************************\n*******************************************_API_NO#_3_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: TMU_Init\n-INPUT: timer_CH:=%d---- resolution=%d\n-EXPECTED OUTPUT:NOK\n",i+1,invalid_test[i].Timer_CH,invalid_test[i].resloution);
    Check_Test=Testing__TMU_Init(&invalid_test[i]);
      if(Check_Test==E_NOK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }

    }



      printf("****************************This is Unit Test for TMU MODULE***************************************\n*******************************************_API_NO#_3_(NULL_PTR)**************************************************\n*****************************************TEST_CASE_NO#_4***********************************************\n-FUNCTION NAME: TMU_Init\n-INPUT:NULL_PTR \n-EXPECTED OUTPUT:OK\n");
    Check_Test=Testing__TMU_Init(NULL_Pointer_Check);
     if(Check_Test==NULL_PTR){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }


for(int j=0; j<5; j++)
{
     for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for TMU MODULE***************************************\n*******************************************_API_NO#_4_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: TMU_Start_Timer\n-INPUT: Task_ID:=%d---- Task_Delay=%d------Delay_Type=%d\n-EXPECTED OUTPUT:OK\n",i+1,Start_valid_test[i].TaskID,Start_valid_test[i].Task_delay,Start_valid_test[i].Delay_type);
    Check_Test=Testing__TMU_Start_Timer(&Start_valid_test[i]);
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }

    }
}


    for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for TMU MODULE***************************************\n*******************************************_API_NO#_4_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: TMU_Start_Timer\n-INPUT: Task_ID:=%d---- Task_Delay=%d------Delay_Type=%d\n-EXPECTED OUTPUT:FULL_BUFFER\n",i+1,Start_valid_test[i].TaskID,Start_valid_test[i].Task_delay,Start_valid_test[i].Delay_type);
    Check_Test=Testing__TMU_Start_Timer(&Start_valid_test[i]);
      if(Check_Test==FULL_BUFFER){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }

    }


        for(unsigned i=0;i<4;i++){
    printf("****************************This is Unit Test for TMU MODULE***************************************\n*******************************************_API_NO#_4_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: TMU_Start_Timer\n-INPUT: Task_ID:=%d---- Task_Delay=%d------Delay_Type=%d\n-EXPECTED OUTPUT:NOK\n",i+1,Start_invalid_test[i].TaskID,Start_invalid_test[i].Task_delay,Start_invalid_test[i].Delay_type);
    Check_Test=Testing__TMU_Start_Timer(&Start_invalid_test[i]);
      if(Check_Test==E_NOK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d!\n\n",Check_Test);
    }

    }

printf("****************************This is Unit Test for TMU MODULE***************************************\n*******************************************_API_NO#_4_(NULL_PTR)**************************************************\n*****************************************TEST_CASE_NO#_4***********************************************\n-FUNCTION NAME: TMU_Start\n-INPUT:NULL_PTR \n-EXPECTED OUTPUT:NULL_PTR\n");
     Check_Test=Testing__TMU_Init(NULL_Pointer_Check);
     if(Check_Test==NULL_PTR){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }


   for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for TMU MODULE***************************************\n*******************************************_API_NO#_5_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: TMU_Stop_Timer\n-INPUT: Task_ID:=%d---- Task_Delay=%d------Delay_Type=%d\n-EXPECTED OUTPUT:OK\n",i+1,Stop_valid_test[i].TaskID,Stop_valid_test[i].Task_delay,Stop_valid_test[i].Delay_type);
    Check_Test=Testing__TMU_Stop_Timer(&Stop_valid_test[i]);
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }

    }




        for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for TMU MODULE***************************************\n*******************************************_API_NO#_5_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: TMU_Stop_Timer\n-INPUT: Task_ID:=%d---- Task_Delay=%d------Delay_Type=%d\n-EXPECTED OUTPUT:NOK\n",i+1,Stop_invalid_test[i].TaskID,Stop_invalid_test[i].Task_delay,Stop_invalid_test[i].Delay_type);
    Check_Test=Testing__TMU_Stop_Timer(&Stop_invalid_test[i]);
      if(Check_Test==E_NOK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d!\n\n",Check_Test);
    }

    }


    printf("****************************This is Unit Test for TMU MODULE***************************************\n*******************************************_API_NO#_5_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: TMU_Stop_Timer\n-INPUT: Task_ID:=%d---- Task_Delay=%d------Delay_Type=%d\n-EXPECTED OUTPUT:START_NO_STOP\n",3,Stop_invalid_test_NoStart.TaskID,Stop_invalid_test_NoStart.Task_delay,Stop_invalid_test_NoStart.Delay_type);
    Check_Test=Testing__TMU_Stop_Timer(&Stop_invalid_test_NoStart);
      if(Check_Test==STOP_NO_START){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d!\n\n",Check_Test);
    }


    printf("****************************This is Unit Test for TMU MODULE***************************************\n*******************************************_API_NO#_5_(NULL_PTR)**************************************************\n*****************************************TEST_CASE_NO#_4***********************************************\n-FUNCTION NAME: TMU_Stop\n-INPUT:NULL_PTR \n-EXPECTED OUTPUT:NULL_PTR\n");
     Check_Test=Testing__TMU_Stop_Timer(SW_NULL_Pointer_Check);
     if(Check_Test==NULL_PTR){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }

    return 0;
}
signed char Testing__TMU_Dispatch(void){
  signed char Test_API_1 =E_OK;
   Test_API_1=TMU_Dispatch();
return Test_API_1;
}

signed char Testing__TMU_DeInit (void){
 signed char Test_API_2 =E_OK;
   Test_API_2=TMU_DeInit();
return Test_API_2;

}
signed char Testing__TMU_Init(const TMU_ConfigType * ConfigPtr){
     TMU_ConfigType*config;
    config=ConfigPtr;
    signed char Test_API_3=E_OK;
   Test_API_3=TMU_Init(config);
return Test_API_3;
}
signed char Testing__TMU_Start_Timer(const TMU_SW_Timer * SW_Timer){
 TMU_SW_Timer*config;
    config=SW_Timer;
    signed char Test_API_4=E_OK;
   Test_API_4=TMU_Start_Timer(config);
return Test_API_4;
}

signed char Testing__TMU_Stop_Timer(const TMU_SW_Timer * SW_Timer){
 TMU_SW_Timer*config;
    config=SW_Timer;
    signed char Test_API_5=E_OK;
   Test_API_5=TMU_Stop_Timer(config);
return Test_API_5;

}
