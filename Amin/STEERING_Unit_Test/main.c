/*
*	File name: main.c
*	Author : Amin
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "Steering.h"
#define OK 0
#define NOK 1
#define TEST_CASES 5
unsigned char TESTING__Steering_Init(void);
unsigned char TESTING__Steering_SteerCar(unsigned char direction,unsigned char speed);
unsigned char Speed_Test_Values[TEST_CASES]={0,50,100,101,102};
unsigned char Direction_Test_Values[TEST_CASES]={0,1,4,5,6};
unsigned char actual=OK;
unsigned char expected=OK;
int main()
{
    unsigned char Check_Test=0;
    printf("****************************This is Unit Test for STEERING MODULE***************************************\n*******************************************_API_NO#_1_**************************************************\n*****************************************TEST_CASE_NO#_1***********************************************\n-FUNCTION NAME: Steering_Init\n-INPUT:VOID\n-EXPECTED OUTPUT:OK\n");
    Check_Test=TESTING__Steering_Init();
    expected=OK;
    actual=Check_Test;
    if(expected==actual){
           printf("-Actual OUTPUT: OK\n\n");
        printf("TEST CASE PASSED !\n\n");
    }
    else{
          printf("-Actual OUTPUT: NOK\n");
       printf("TEST CASE FAILED !\n\n");
    }
   printf("*********************************************************************************************************\n*********************************************************************************************************\n*******************************************_API_NO#_2_**************************************************\n");
   for(unsigned char i=1;i<TEST_CASES+1;i++){
   printf("*****************************************TEST_CASE_NO#_%d***********************************************\n",i);
   printf("-FUNCTION NAME: Steering_SteerCar\n");
   printf("-INPUT: Direction=%d , Speed=%d\n",Direction_Test_Values[i-1],Speed_Test_Values[i-1]);
 Check_Test=TESTING__Steering_SteerCar(Direction_Test_Values[i-1],Speed_Test_Values[i-1]);
 actual=Check_Test;
 switch(i){
 case 4:
    expected=NOK;
     if(expected==actual){
          printf("-Expected OUTPUT: NOK\n");
        printf("-Actual OUTPUT: NOK\n\n");
        printf("TEST CASE PASSED!\n\n");
    }
    else{
             printf("-Expected OUTPUT: NOK\n");
             printf("-Actual OUTPUT: OK\n\n");
       printf("TEST CASE FAILED!\n\n");
    }
    break;
   case 5:
      expected=NOK;
    if(expected==actual){
             printf("-Expected OUTPUT: NOK\n");
             printf("-Actual OUTPUT: NOK\n\n");
       printf("TEST CASE PASSED!\n\n");
    }
    else{
         printf("-Expected OUTPUT: NOK\n");
         printf("-Actual OUTPUT: OK\n\n");
       printf("TEST CASE FAILED!\n\n");
    }
    break;
   default:
    expected=OK;
     if(expected==actual){
        printf("-Expected OUTPUT: OK\n");
        printf("-Actual OUTPUT: OK\n\n");
       printf("TEST CASE PASSED!\n\n");
    }
    else{
             printf("-Expected OUTPUT: OK\n\n");
         printf("-Actual OUTPUT: NOK\n\n");
       printf("TEST CASE FAILED!\n\n");
    }
 }
   }
}
unsigned char TESTING__Steering_Init(){
   unsigned char Test_API_1 =OK;
   Test_API_1=Steering_Init();
return Test_API_1;
}

unsigned char TESTING__Steering_SteerCar(unsigned char test_direction_value,unsigned char test_speed_value){
unsigned direction,speed;
unsigned char Test_API_2=OK;
direction=test_direction_value;
speed=test_speed_value;
Test_API_2=Steering_SteerCar(direction,speed);
return Test_API_2;
}
