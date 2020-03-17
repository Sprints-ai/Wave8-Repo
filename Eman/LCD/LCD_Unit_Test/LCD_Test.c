/*
*	File name: main.c
*	Author : Ema
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "LCD.h"

signed char Testing__LCD_init(uint8_t OperationMode);
signed char Testing__LCD_sendCommand(uint8_t uint8_tCmdCpy , uint8_t OperationMode);
signed char Testing__LCD_DisplayChar(uint8_t u8_DataCpy, uint8_t OperationMode);
signed char Testing__LCD_displayStringRowColumn(uint8_t u8_Row , uint8_t u8_Column, uint8_t* puint8_tStringCpy, uint8_t uint8_tIndex, uint8_t* pu8_Notification);

signed char expected =E_OK;
signed char actual=E_OK;

uint8_t LCD_init_valid_test[2]={LCD_OS,LCD_NORMAL};
uint8_t LCD_init_invalid_test[2]={-5,9};

uint8_t LCD_sendCommand_valid_test1[2]={LCD_OS,LCD_NORMAL};
uint8_t LCD_sendCommand_valid_test2[2]={lcd_Home,lcd_Clear};
uint8_t LCD_sendCommand_invalid_test1[2]={9,-1};


uint8_t LCD_DisplayChar_valid_test1[2]={LCD_NORMAL,LCD_OS};
uint8_t LCD_DisplayChar_invalid_test1[2]={9,-1};

uint8_t LCD_displayStringRowColumn_valid_test1[2]={1,2};
uint8_t LCD_displayStringRowColumn_invalid_test1[2]={9,-1};
uint8_t Data_string[10]="TestString";
uint8_t Notification;

uint8_t *NULL_Pointer_Check=NULL;

int main()
{
     signed char Check_Test=0;

    for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_1_INIT VALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: LCD_Init\n-INPUT: Operation mode:=%d\n-EXPECTED OUTPUT:OK\n",i+1,LCD_init_valid_test[i]);
    Check_Test=Testing__LCD_init(&LCD_init_valid_test[i]);
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d !\n\n",Check_Test);
    }

    }

    for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_1_INIT_INVALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: LCD_Init\n-INPUT: Operation mode:=%d\n-EXPECTED OUTPUT:ERROR_INVALID_PARAMETER\n",i+1,LCD_init_invalid_test[i]);
    Check_Test=Testing__LCD_init(&LCD_init_invalid_test[i]);
      if(Check_Test==ERROR_INVALID_PARAMETER){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }

    }

     for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_2_SEND_COMMAND VALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: LCD_Send_command\n-INPUT: command:=%d----- Operation mode:=%d\n-EXPECTED OUTPUT:OK\n",i+1,lcd_Home,LCD_sendCommand_valid_test1[i]);
    Check_Test=Testing__LCD_sendCommand(lcd_Home,&LCD_sendCommand_valid_test1[i]);
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d !\n\n",Check_Test);
    }

    }

    for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_2_SEND_COMMAND VALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: LCD_Send_command\n-INPUT: command:=%d----- Operation mode:=%d\n-EXPECTED OUTPUT:OK\n",i+3,LCD_sendCommand_valid_test1[i],LCD_NORMAL);
    Check_Test=Testing__LCD_sendCommand(&LCD_sendCommand_valid_test1[i],LCD_NORMAL);
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d !\n\n",Check_Test);
    }

    }

    for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_2_SEND_COMMAND INVALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: LCD_Send_command\n-INPUT: command:=%d----- Operation mode:=%d\n-EXPECTED OUTPUT:OK\n",i+1,-1,LCD_sendCommand_invalid_test1[i]);
    Check_Test=Testing__LCD_sendCommand(-1,&LCD_sendCommand_invalid_test1[i]);
      if(Check_Test==ERROR_INVALID_PARAMETER){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d !\n\n",Check_Test);
    }

    }

    for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_2_SEND_COMMAND INVALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: LCD_Send_command\n-INPUT: command:=%d----- Operation mode:=%d\n-EXPECTED OUTPUT:OK\n",i+3,LCD_sendCommand_invalid_test1[i],9);
    Check_Test=Testing__LCD_sendCommand(&LCD_sendCommand_invalid_test1[i],9);
      if(Check_Test==ERROR_INVALID_PARAMETER){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d !\n\n",Check_Test);
    }

    }

    /*********************************************/

    for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_3_LCD_DisplayChar VALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: LCD_Display Char\n-INPUT: data:=%c----- Operation mode:=%d\n-EXPECTED OUTPUT:OK\n",i+1,'a',LCD_DisplayChar_valid_test1[i]);
    Check_Test=Testing__LCD_sendCommand('a',&LCD_DisplayChar_valid_test1[i]);
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d !\n\n",Check_Test);
    }

    }

    for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_3_LCD_DisplayChar INVALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: LCD_Display Char\n-INPUT: data:=%d----- Operation mode:=%d\n-EXPECTED OUTPUT:OK\n",i+1,5,LCD_DisplayChar_invalid_test1[i]);
    Check_Test=Testing__LCD_sendCommand(5,&LCD_DisplayChar_invalid_test1[i]);
      if(Check_Test==ERROR_INVALID_PARAMETER){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d !\n\n",Check_Test);
    }

    }

    /*********************************************/

    for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_4_LCD_displayStringRowColumn VALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: LCD_displayStringRowColumn\n-EXPECTED OUTPUT:OK\n",i+1);
    Check_Test=Testing__LCD_displayStringRowColumn(&LCD_displayStringRowColumn_valid_test1[i] ,&LCD_displayStringRowColumn_valid_test1[i],Data_string,10, &Notification);
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d !\n\n",Check_Test);
    }

    }

    for(unsigned i=0;i<2;i++){
    printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_4_LCD_displayStringRowColumn INVALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: LCD_displayStringRowColumn\n-EXPECTED OUTPUT:OK\n",i+1);
    Check_Test=Testing__LCD_displayStringRowColumn(&LCD_displayStringRowColumn_invalid_test1[i] ,&LCD_displayStringRowColumn_valid_test1[i],Data_string,10, &Notification);
      if(Check_Test==ERROR_INVALID_PARAMETER){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d !\n\n",Check_Test);
    }

    }


      printf("****************************This is Unit Test for SOS MODULE***************************************\n*******************************************_API_NO#_4_(NULL_PTR)**************************************************\n*****************************************TEST_CASE_NO#_5***********************************************\n-FUNCTION NAME: LCD_displayStringRowColumn\n-INPUT:NULL_PTR \n-EXPECTED OUTPUT:OK\n");
    Check_Test=Testing__LCD_displayStringRowColumn(&LCD_displayStringRowColumn_valid_test1[1] ,&LCD_displayStringRowColumn_valid_test1[0],NULL_Pointer_Check,10, &Notification);
     if(Check_Test==ERROR_NULL_POINTER){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED !\n\n");
    }


    return 0;
}


signed char Testing__LCD_init(uint8_t OperationMode){
    signed char Test_API_1=E_OK;
   Test_API_1=LCD_init(OperationMode);
return Test_API_1;
}

signed char Testing__LCD_sendCommand(uint8_t uint8_tCmdCpy , uint8_t OperationMode){
    signed char Test_API_2=E_OK;
   Test_API_2=LCD_sendCommand(uint8_tCmdCpy ,OperationMode);
return Test_API_2;
}

signed char Testing__LCD_DisplayChar(uint8_t u8_DataCpy, uint8_t OperationMode){
    signed char Test_API_3=E_OK;
   Test_API_3=LCD_DisplayChar(u8_DataCpy,OperationMode);
return Test_API_3;

}

signed char Testing__LCD_displayStringRowColumn(uint8_t u8_Row , uint8_t u8_Column, uint8_t* puint8_tStringCpy, uint8_t uint8_tIndex, uint8_t* pu8_Notification)
{
    signed char Test_API_4=E_OK;
   Test_API_4=LCD_displayStringRowColumn(u8_Row ,u8_Column,puint8_tStringCpy,uint8_tIndex,pu8_Notification);
return Test_API_4;

}

