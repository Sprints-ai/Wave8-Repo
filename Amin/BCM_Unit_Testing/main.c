/*
*	File name: main.c
*	Author : Amin
*
*/


#include <stdio.h>
#include <stdlib.h>
#include "BCM_rx.h"
#include "BCM_tx.h"

signed char Testing__BCM_Send(uint8_t* ptr_Buffer, uint16_t u16_Size, uint8_t u8_Channel);
signed char Testing__BCM_Init(uint8_t u8_Channel);
signed char Testing__BCM_Receive(uint16_t u16_Size, uint8_t u8_bcm_id);

uint8_t test_BCM_Send_ptr[]={NULL,1,2};
uint8_t test_BCM_Send_size[]={1,2,3};
uint8_t test_BCM_Send_channel[]={UART_CH,SPI_CH,10};


int main()
{
    signed char Check_Test=0;
    signed char Expected=0;
    signed char Actual=0;
    for(int i=0;i<3;i++){
             printf("****************************This is Unit Test for BCM MODULE***************************************\n*******************************************_API_NO#_1_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:BCM_Send\n-INPUT:BufferPTR=%d------Size=%d------Channel=%d\n",i+1,test_BCM_Send_ptr[i],test_BCM_Send_size[i],test_BCM_Send_channel[i]);
             Check_Test=Testing__BCM_Send(test_BCM_Send_ptr[i],test_BCM_Send_size[i],test_BCM_Send_channel[i]);
             switch(i){
             case 0:
               Expected=ERROR_NULL_POINTER;
               Actual= Check_Test;
             if(Expected==Actual){
             printf("Expected Output:ERROR_NULL_POINTER\n");
             printf("Actual Output:ERROR_NULL_POINTER\n");
             printf("TEST CASE#NO_%d PASSED\n\n",i+1);
             }
             else{
                     printf("Expected Output:ERROR_NULL_POINTER\n");
             printf("Actual Output:%d\n",Actual);
                printf("TEST CASE#NO_%d FAILED\n\n",i+1);
             }
             break;
             case 1:
               Expected=E_OK;
               Actual= Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:EOK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE#NO_%d PASSED\n\n",i+1);
             }
             else{
                  printf("Expected Output:EOK\n");
             printf("Actual Output:%d\n",Actual);
                printf("TEST CASE#NO_%d FAILED\n\n",i+1);
             }
             break;
             case 2:
              Expected=ERROR_INVALID_PARAMETER;
              Actual= Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:ERROR_INVALID_PARAMETER\n");
             printf("Actual Output:ERROR_INVALID_PARAMETER\n");
                printf("TEST CASE#NO_%d PASSED\n\n",i+1);
             }
             else{
                  printf("Expected Output:ERROR_INVALID_PARAMETER\n");
             printf("Actual Output:%d\n",Actual);
                printf("TEST CASE#NO_%d FAILED\n\n",i+1);
             }
             break;
             }
        }

for(int i=0;i<3;i++){
printf("****************************This is Unit Test for BCM MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:BCM_Init\n-INPUT:-Channel=%d\n",i+1,test_BCM_Send_channel[i]);
Check_Test=Testing__BCM_Init(test_BCM_Send_channel[i]);
             switch(i){
             case 0:
               Expected=E_OK;
               Actual= Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:EOK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE#NO_%d PASSED\n\n",i+1);
             }
             else{
                  printf("Expected Output:EOK\n");
             printf("Actual Output:%d\n",Actual);
                printf("TEST CASE#NO_%d FAILED\n\n",i+1);
             }
             break;
             case 1:
               Expected=E_OK;
               Actual= Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:EOK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE#NO_%d PASSED\n\n",i+1);
             }
             else{
                  printf("Expected Output:EOK\n");
             printf("Actual Output:%d\n",Actual);
                printf("TEST CASE#NO_%d FAILED\n\n",i+1);
             }
             break;
             case 2:
              Expected=ERROR_INVALID_PARAMETER;
              Actual= Check_Test;
              if(Expected==Actual){
                  printf("Expected Output:ERROR_INVALID_PARAMETER\n");
             printf("Actual Output:ERROR_INVALID_PARAMETER\n");
                printf("TEST CASE#NO_%d PASSED\n\n",i+1);
             }
             else{
                  printf("Expected Output:ERROR_INVALID_PARAMETER\n");
             printf("Actual Output:%d\n",Actual);
                printf("TEST CASE#NO_%d FAILED\n\n",i+1);
             }
             break;
             }
}
 for(int i=0;i<3;i++){
             printf("****************************This is Unit Test for BCM MODULE***************************************\n*******************************************_API_NO#_3_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:BCM_Recieve\n-INPUT:Size=%d------Channel=%d\n",i+1,test_BCM_Send_size[i],test_BCM_Send_channel[i]);
             Check_Test=Testing__BCM_Receive(test_BCM_Send_size[i],test_BCM_Send_channel[i]);
             switch(i){
             case 0:
               Expected=ERROR_NULL_POINTER;
             Expected=E_OK;
               Actual= Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:EOK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE#NO_%d PASSED\n\n",i+1);
             }
             else{
                  printf("Expected Output:EOK\n");
             printf("Actual Output:%d\n",Actual);
                printf("TEST CASE#NO_%d FAILED\n\n",i+1);
             }
             break;
             case 1:
               Expected=E_OK;
               Actual= Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:EOK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE#NO_%d PASSED\n\n",i+1);
             }
             else{
                  printf("Expected Output:EOK\n");
             printf("Actual Output:%d\n",Actual);
                printf("TEST CASE#NO_%d FAILED\n\n",i+1);
             }
             break;
             case 2:
              Expected=ERROR_INVALID_PARAMETER;
              Actual= Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:ERROR_INVALID_PARAMETER\n");
             printf("Actual Output:ERROR_INVALID_PARAMETER\n");
                printf("TEST CASE#NO_%d PASSED\n\n",i+1);
             }
             else{
                  printf("Expected Output:ERROR_INVALID_PARAMETER\n");
             printf("Actual Output:%d\n",Actual);
                printf("TEST CASE#NO_%d FAILED\n\n",i+1);
             }
             break;
             }
        }
    }

signed char Testing__BCM_Send(uint8_t* ptr_Buffer, uint16_t u16_Size, uint8_t u8_Channel){
signed Test_Api=BCM_Send(ptr_Buffer,u16_Size,u8_Channel);
return Test_Api;
}
signed char Testing__BCM_Init(uint8_t u8_Channel){
signed Test_Api=BCM_Init(u8_Channel);
return Test_Api;
}
signed char Testing__BCM_Receive(uint16_t u16_Size, uint8_t u8_bcm_id){
signed Test_Api=BCM_Receive(u16_Size,u8_bcm_id);
return Test_Api;
}
