#include <stdio.h>
#include <stdlib.h>
#include "motor.h"

signed char Testing___Motor_Init(uint8 Motor_Number);
signed char Testing___Motor_Direction(uint8 Motor_Number, uint8 Motor_Direction);
signed char Testing___Motor_Start(uint8 Motor_Number, uint8 Mot_Speed);
signed char Testing___Motor_SpeedUpdate(uint8 Motor_Number, uint8 Speed);
signed char Testing___Motor_Stop(uint8 Motor_Number);


uint8 Motor_init_Valid_Array_Values[2]={MOTOR_1,MOTOR_2};
uint8 Motor_init_INvalid_Array_Values[2]={-1,5};

uint8 Motor_Direction_Valid_Array_Values[3]={MOTOR_FORWARD,MOTOR_BACKWARD};
uint8 Motor_Direction_INvalid_Array_Values[3]={-1,5,};

uint8 Motor_Speed_Valid_Array_Values[3]={0,100};
uint8 Motor_Speed_INvalid_Array_Values[3]={-1,200};



int main()
{
    signed char Check_Test=0;
    signed char Expected=0;
    signed char Actual=0;

    for(uint8 i=0;i<2;i++){
             printf("****************************This is Unit Test for MOTOR MODULE***************************************\n*******************************************_API_NO#_1_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:Motor_Init\n-INPUT:%d\n",i+1,Motor_init_Valid_Array_Values[i]);
             Check_Test=Testing___Motor_Init(Motor_init_Valid_Array_Values[i]);
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
                printf("TEST CASE FAILED %d\n\n",Actual);
             }
    }
    for(uint8 i=0;i<2;i++){
             printf("****************************This is Unit Test for MOTOR MODULE***************************************\n*******************************************_API_NO#_1_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:Motor_Init\n-INPUT:%d\n",i+3,Motor_init_INvalid_Array_Values[i]);
             Check_Test=Testing___Motor_Init(Motor_init_INvalid_Array_Values[i]);
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
                printf("TEST CASE FAILED %d\n\n",Actual);
             }
    }

     for(uint8 i=0;i<2;i++){
             printf("****************************This is Unit Test for MOTOR MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:Motor_Direction\n-INPUT: motor_number %d----INPUT: direction %d\n",i+1,Motor_init_Valid_Array_Values[i],Motor_Direction_Valid_Array_Values[i]);
             Check_Test=Testing___Motor_Direction(Motor_init_Valid_Array_Values[i],Motor_Direction_Valid_Array_Values[i]);
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
                printf("TEST CASE FAILED %d\n\n",Actual);
             }
    }
    for(uint8 i=0;i<2;i++){
             printf("****************************This is Unit Test for MOTOR MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:Motor_Direction\n-INPUT: motor_number %d----INPUT: direction %d\n",i+3,Motor_init_INvalid_Array_Values[i],Motor_Direction_INvalid_Array_Values[i]);
             Check_Test=Testing___Motor_Direction(Motor_init_INvalid_Array_Values[i],Motor_Direction_INvalid_Array_Values[i]);
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
                printf("TEST CASE FAILED %d\n\n",Actual);
             }
    }
     for(uint8 i=0;i<2;i++){
             printf("****************************This is Unit Test for MOTOR MODULE***************************************\n*******************************************_API_NO#_3_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:Motor_Start\n-INPUT: motor_number %d----INPUT: speed %d\n",i+1,Motor_init_Valid_Array_Values[i],Motor_Speed_Valid_Array_Values[i]);
             Check_Test=Testing___Motor_Start(Motor_init_Valid_Array_Values[i],Motor_Speed_Valid_Array_Values[i]);
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
                printf("TEST CASE FAILED %d\n\n",Actual);
             }
    }
    for(uint8 i=0;i<2;i++){
             printf("****************************This is Unit Test for MOTOR MODULE***************************************\n*******************************************_API_NO#_3_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:Motor_Start\n-INPUT: motor_number %d----INPUT: speed %d\n",i+3,Motor_init_INvalid_Array_Values[i],Motor_Speed_INvalid_Array_Values[i]);
             Check_Test=Testing___Motor_Start(Motor_init_INvalid_Array_Values[i],Motor_Speed_INvalid_Array_Values[i]);
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
                printf("TEST CASE FAILED %d\n\n",Actual);
             }
    }
     for(uint8 i=0;i<2;i++){
             printf("****************************This is Unit Test for MOTOR MODULE***************************************\n*******************************************_API_NO#_4_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:Motor_Speed_Update\n-INPUT: motor_number %d----INPUT: speed %d\n",i+1,Motor_init_Valid_Array_Values[i],Motor_Speed_Valid_Array_Values[i]);
             Check_Test=Testing___Motor_SpeedUpdate(Motor_init_Valid_Array_Values[i],Motor_Speed_Valid_Array_Values[i]);
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
                printf("TEST CASE FAILED %d\n\n",Actual);
             }
    }
        for(uint8 i=0;i<2;i++){
             printf("****************************This is Unit Test for MOTOR MODULE***************************************\n*******************************************_API_NO#_4_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:Motor_Speed_Update\n-INPUT: motor_number %d----INPUT: speed %d\n",i+3,Motor_init_INvalid_Array_Values[i],Motor_Speed_INvalid_Array_Values[i]);
             Check_Test=Testing___Motor_SpeedUpdate(Motor_init_INvalid_Array_Values[i],Motor_Speed_INvalid_Array_Values[i]);
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
                printf("TEST CASE FAILED %d\n\n",Actual);
             }
    }
    for(uint8 i=0;i<2;i++){
             printf("****************************This is Unit Test for MOTOR MODULE***************************************\n*******************************************_API_NO#_5_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:Motor_Stop\n-INPUT:%d\n",i+1,Motor_init_Valid_Array_Values[i]);
             Check_Test=Testing___Motor_Stop(Motor_init_Valid_Array_Values[i]);
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
                printf("TEST CASE FAILED %d\n\n",Actual);
             }
    }
    for(uint8 i=0;i<2;i++){
             printf("****************************This is Unit Test for MOTOR MODULE***************************************\n*******************************************_API_NO#_5_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:Motor_Stop\n-INPUT:%d\n",i+3,Motor_init_INvalid_Array_Values[i]);
             Check_Test=Testing___Motor_Stop(Motor_init_INvalid_Array_Values[i]);
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
                printf("TEST CASE FAILED %d\n\n",Actual);
             }
    }

}


signed char Testing___Motor_Init(uint8 Motor_Number){
signed char Test_API_1=E_OK;
    Test_API_1=Motor_Init(Motor_Number);
    return Test_API_1;
}

signed char Testing___Motor_Direction(uint8 Motor_Number, uint8 motor_Direction){
signed char Test_API_2=E_OK;
Test_API_2=Motor_Direction(Motor_Number,motor_Direction);
return Test_API_2;
}

signed char Testing___Motor_Start(uint8 Motor_Number, uint8 Mot_Speed){
signed char Test_API_3=E_OK;
Test_API_3=Motor_Start(Motor_Number,Mot_Speed);
return Test_API_3;
}
signed char Testing___Motor_SpeedUpdate(uint8 Motor_Number, uint8 Speed){
signed char Test_API_4=E_OK;
Test_API_4=Motor_SpeedUpdate(Motor_Number,Speed);
return Test_API_4;
}
signed char Testing___Motor_Stop(uint8 Motor_Number){
signed char Test_API_5=E_OK;
Test_API_5=Motor_Stop(Motor_Number);
return Test_API_5;
}
