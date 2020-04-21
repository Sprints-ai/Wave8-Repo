#include <stdio.h>
#include <stdlib.h>
#include "PWM.h"

signed char Testing___Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);
signed char Testing___Pwm_Start(uint8 Channel,uint8 Duty,uint32 Frequncy);
signed char Testing___Pwm_Update(uint8 Channel,uint8 Duty,uint32 Frequncy);
signed char Testing___Pwm_Stop(uint8 Channel);

Pwm_Cfg_s PWM_init_Valid_Array_Values[3]={{PWM_CH1A,PWM_PRESCALER_NO},{PWM_CH0,PWM_PRESCALER_1024},{PWM_CH2,PWM_PRESCALER_256}};
Pwm_Cfg_s PWM_init_INvalid_Array_Values[3]={{-1,PWM_PRESCALER_NO},{PWM_CH0,10},{13,-1}};
Pwm_Cfg_s*null_ptr=NULL;


uint8 PWM_Start_ValidChannel_Array_Values[3]={PWM_CH0,PWM_CH1A,PWM_CH2};
uint8 PWM_Start_INvalidChannel_Array_Values[3]={-1,10,20};

uint8 PWM_Duty_Valid_Array_Values[3]={0,50,100};
uint8 PWM_Duty_INvalid_Array_Values[3]={-1,200,150};




int main()
{
    signed char Check_Test=0;
    signed char Expected=0;
    signed char Actual=0;

    for(uint8 i=0;i<3;i++){
             printf("****************************This is Unit Test for PWM MODULE***************************************\n*******************************************_API_NO#_1_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:PWM_Init\n-INPUT:%d-- %d-- \n",i+1,PWM_init_Valid_Array_Values[i].Channel,PWM_init_Valid_Array_Values[i].Prescaler);
             Check_Test=Testing___Pwm_Init(&PWM_init_Valid_Array_Values[i]);
             Expected=E_OK;
             Actual=Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:EOK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE PASSED\n\n");
             }
             else{
                  printf("Expected Output:EOK\n");
             printf("Actual Output:E_NOK\n");
                printf("TEST CASE FAILED\n\n");
             }
    }
      for(uint8 i=0;i<3;i++){
             printf("****************************This is Unit Test for PWM MODULE***************************************\n*******************************************_API_NO#_1_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:PWM_Init\n-INPUT:%d-- %d-- \n",i+4,PWM_init_INvalid_Array_Values[i].Channel,PWM_init_INvalid_Array_Values[i].Prescaler);
             Check_Test=Testing___Pwm_Init(&PWM_init_INvalid_Array_Values[i]);
             Expected=E_NOK;
             Actual=Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:E_NOK\n");
             printf("Actual Output:E_NOK\n");
                printf("TEST CASE PASSED\n\n");
             }
             else{
                  printf("Expected Output:E_NOK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE FAILED\n\n");
             }
    }
      printf("****************************This is Unit Test for PWM MODULE***************************************\n*******************************************_API_NO#_1_**************************************************\n*****************************************TEST_CASE_NO#_7***********************************************\n-FUNCTION NAME:PWM_Init\n-INPUT:Null_PTR\n");
     Check_Test=Testing___Pwm_Init(null_ptr);
     Expected=NULL_PTR_ERROR;
     Actual=Check_Test;
     if(Actual==Expected){
           printf("Expected Output: NULL_PTR_ERROR\n");
             printf("Actual Output: NULL_PTR_ERROR\n");
        printf("Tese case PASSED\n \n");
     }
     else{
        printf("Tese case FAILED\n \n");
     }

 for(uint8 i=0;i<3;i++){
             printf("****************************This is Unit Test for PWM MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:PWM_Start\n-INPUT:%d-- %d-- %d\n",i+1,PWM_Start_ValidChannel_Array_Values[i],PWM_Duty_Valid_Array_Values[i],1);
             Check_Test=Testing___Pwm_Start(PWM_Start_ValidChannel_Array_Values[i],PWM_Duty_Valid_Array_Values[i],1);
             Expected=E_OK;
             Actual=Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:EOK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE PASSED\n\n");
             }
             else{
                  printf("Expected Output:EOK\n");
             printf("Actual Output:E_NOK\n");
                printf("TEST CASE FAILED\n\n");
             }
    }

    for(uint8 i=0;i<3;i++){
             printf("****************************This is Unit Test for PWM MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:PWM_Start\n-INPUT:%d-- %d-- %d\n",i+4,PWM_Start_INvalidChannel_Array_Values[i],PWM_Duty_INvalid_Array_Values[i],1);
             Check_Test=Testing___Pwm_Start(PWM_Start_INvalidChannel_Array_Values[i],PWM_Duty_INvalid_Array_Values[i],1);
             Expected=E_NOK;
             Actual=Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:E_NOK\n");
             printf("Actual Output:E_NOK\n");
                printf("TEST CASE PASSED\n\n");
             }
             else{
                  printf("Expected Output:E_NOK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE FAILED\n\n");
             }
    }

     for(uint8 i=0;i<3;i++){
             printf("****************************This is Unit Test for PWM MODULE***************************************\n*******************************************_API_NO#_3_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:PWM_Update\n-INPUT:%d-- %d-- %d\n",i+1,PWM_Start_ValidChannel_Array_Values[i],PWM_Duty_Valid_Array_Values[i],1);
             Check_Test=Testing___Pwm_Update(PWM_Start_ValidChannel_Array_Values[i],PWM_Duty_Valid_Array_Values[i],1);
             Expected=E_OK;
             Actual=Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:EOK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE PASSED\n\n");
             }
             else{
                  printf("Expected Output:EOK\n");
             printf("Actual Output:E_NOK\n");
                printf("TEST CASE FAILED\n\n");
             }
    }

    for(uint8 i=0;i<3;i++){
             printf("****************************This is Unit Test for PWM MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:PWM_Update\n-INPUT:%d-- %d-- %d\n",i+4,PWM_Start_INvalidChannel_Array_Values[i],PWM_Duty_INvalid_Array_Values[i],1);
             Check_Test=Testing___Pwm_Update(PWM_Start_INvalidChannel_Array_Values[i],PWM_Duty_INvalid_Array_Values[i],1);
             Expected=E_NOK;
             Actual=Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:E_NOK\n");
             printf("Actual Output:E_NOK\n");
                printf("TEST CASE PASSED\n\n");
             }
             else{
                  printf("Expected Output:E_NOK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE FAILED\n\n");
             }
    }

        for(uint8 i=0;i<3;i++){
             printf("****************************This is Unit Test for PWM MODULE***************************************\n*******************************************_API_NO#_4_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:PWM_Stop\n-INPUT:%d-- \n",i+1,PWM_Start_ValidChannel_Array_Values[i]);
             Check_Test=Testing___Pwm_Stop(PWM_Start_ValidChannel_Array_Values[i]);
             Expected=E_OK;
             Actual=Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:EOK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE PASSED\n\n");
             }
             else{
                  printf("Expected Output:EOK\n");
             printf("Actual Output:E_NOK\n");
                printf("TEST CASE FAILED\n\n");
             }
    }

    for(uint8 i=0;i<3;i++){
             printf("****************************This is Unit Test for PWM MODULE***************************************\n*******************************************_API_NO#_4_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:PWM_Update\n-INPUT:%d--\n",i+4,PWM_Start_INvalidChannel_Array_Values[i]);
             Check_Test=Testing___Pwm_Stop(PWM_Start_INvalidChannel_Array_Values[i]);
             Expected=E_NOK;
             Actual=Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:E_NOK\n");
             printf("Actual Output:E_NOK\n");
                printf("TEST CASE PASSED\n\n");
             }
             else{
                  printf("Expected Output:E_NOK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE FAILED\n\n");
             }
    }
    return 0;
}

signed char Testing___Pwm_Init(Pwm_Cfg_s *Pwm_Cfg){
 signed char Test_API_1=E_OK;
    Test_API_1=Pwm_Init(Pwm_Cfg);
    return Test_API_1;
}
signed char Testing___Pwm_Start(uint8 Channel,uint8 Duty,uint32 Frequncy){
signed char Test_API_2=E_OK;
    Test_API_2=Pwm_Start(Channel,Duty,Frequncy);
    return Test_API_2;
}

signed char Testing___Pwm_Update(uint8 Channel,uint8 Duty,uint32 Frequncy){
signed char Test_API_3=E_OK;
    Test_API_3=Pwm_Update(Channel,Duty,Frequncy);
    return Test_API_3;

}
signed char Testing___Pwm_Stop(uint8 Channel){
signed char Test_API_4=E_OK;
    Test_API_4=Pwm_Stop(Channel);
    return Test_API_4;

}
