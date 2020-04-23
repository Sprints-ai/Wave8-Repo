#include <stdio.h>
#include <stdlib.h>

#include "LCD.h"

#define VALID_COMANDS 7
#define INVALID_COMANDS 4
#define DATA 1
#define VALID_ROWS 4
#define INVALID_ROWS 3

signed char Testing___LCD_init(void);
signed char Testing___LCD_sendCommand(uint8 command);
signed char Testing___LCD_displayCharacter(uint8 data);
signed char Testing___LCD_displayString(const sint8 *str);
signed char Testing___LCD_goToRowColumn(uint8 row, uint8 col);
signed char Testing___LCD_displayStringRowColumn(uint8 row, uint8 col, const sint8* str);
signed char Testing___LCD_displayInteger(uint8 num);
signed char Testing___LCD_clearScreen(void);


uint8 array_of_Valid_commands[VALID_COMANDS]={CLEAR_COMMAND,TWO_LINE_LCD_EIGHT_BIT_MODE,FOUR_BITS_DATA_MODE_ACTIVATED,TWO_LINE_LCD_FOUR_BIT_MODE,CURSOR_OFF,CURSOR_ON,SET_CURSOR_LOCATION};
uint8 array_of_Invalid_commands[INVALID_COMANDS]={0x26,0x10,0xFF,0x78};
sint8*null_ptr=NULL;
sint8 strr[]="Test_display_string_API";
sint8 array_of_Valid_rows[VALID_ROWS]={0,1,2,3};
sint8 array_of_Invalid_rows[INVALID_ROWS]={-1,10,20};
int main()
{
    signed char Check_Test=0;
    signed char Expected=0;
    signed char Actual=0;
    for(uint8 i=0;i<1;i++){
             printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_1_**************************************************\n*****************************************TEST_CASE_NO#_1***********************************************\n-FUNCTION NAME:LCD_Init\n-INPUT:Void\n");
             Check_Test=Testing___LCD_init();
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
    for(uint8 i=0;i<VALID_COMANDS;i++){
          printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:LCD_SendCommand\n-INPUT:=%d\n",i+1,array_of_Valid_commands[i]);
       Check_Test=Testing___LCD_sendCommand(array_of_Valid_commands[i]);
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
    for(uint8 i=0;i<INVALID_COMANDS;i++){
          printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:LCD_SendCommand\n-INPUT:=%d\n",i+1+VALID_COMANDS,array_of_Invalid_commands[i]);
       Check_Test=Testing___LCD_sendCommand(array_of_Invalid_commands[i]);
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

     for(uint8 i=DATA;i<DATA+1;i++){
             printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_3_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:LCD_displayCharacter\n-INPUT:data=%d\n",i,i);
             Check_Test=Testing___LCD_displayCharacter(i);
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
    for(uint8 i=0;i<1;i++){
             printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_4_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:LCD_displayString\n-INPUT:Null_PTR=%d\n",i+1);
             Check_Test=Testing___LCD_displayString(null_ptr);
             Expected= NULL_PTR_ERROR;
             Actual=Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:NULL_PTR_ERROR\n");
             printf("Actual Output:NULL_PTR_ERROR\n");
                printf("TEST CASE PASSED\n\n");
             }
             else{
                  printf("Expected Output:NULL_PTR_ERROR\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE FAILED\n\n");
             }
                printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_4_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:LCD_displayString\n-INPUT:String\n",i+2);
             Check_Test=Testing___LCD_displayString(&strr);
             Expected= E_OK;
             Actual=Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:E_OK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE PASSED\n\n");
             }
             else{
                  printf("Expected Output:E_OK\n");
             printf("Actual Output:NULL_PTR_ERROR\n");
                printf("TEST CASE FAILED \n\n");
             }
    }
        for(uint8 i=0;i<VALID_ROWS;i++){
          printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_5_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:LCD_goToRowColumn\n-INPUT:=%d\n",i+1,array_of_Valid_rows[i]);
       Check_Test=Testing___LCD_goToRowColumn(array_of_Valid_rows[i],0);
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
    for(uint8 i=0;i<INVALID_ROWS;i++){
          printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_5_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:LCD_goToRowColumn\n-INPUT:=%d\n",i+1+VALID_ROWS,array_of_Invalid_rows[i]);
       Check_Test=Testing___LCD_goToRowColumn(array_of_Invalid_rows[i],0);
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
    for(uint8 i=0;i<VALID_ROWS;i++){
          printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_6_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:LCD_displayStringRowColumn\n-INPUT:=%d\n",i+1,array_of_Valid_rows[i]);
       Check_Test=Testing___LCD_displayStringRowColumn(array_of_Valid_rows[i],0,&strr);
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
    for(uint8 i=0;i<INVALID_ROWS;i++){
         printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_6_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:LCD_displayStringRowColumn\n-INPUT:=%d\n",i+1+VALID_ROWS,array_of_Valid_rows[i]);
    Check_Test=Testing___LCD_displayStringRowColumn(array_of_Invalid_rows,0,null_ptr);
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

    for(uint8 i=0;i<1;i++){
             printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_7_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:LCD_displayInteger\n-INPUT:=%d\n",i+1);
             Check_Test=Testing___LCD_displayInteger(i);
             Expected= E_OK;
             Actual=Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:E_OK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE PASSED\n\n");
             }
             else{
                  printf("Expected Output:E_OK\n");
             printf("Actual Output:E_NOK\n");
                printf("TEST CASE FAILED\n\n");
             }
    }

     for(uint8 i=0;i<1;i++){
             printf("****************************This is Unit Test for LCD MODULE***************************************\n*******************************************_API_NO#_8_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:LCD_clearScreen\n-INPUT:=%d\n",i+1);
             Check_Test=Testing___LCD_clearScreen();
             Expected= E_OK;
             Actual=Check_Test;
             if(Expected==Actual){
                  printf("Expected Output:E_OK\n");
             printf("Actual Output:E_OK\n");
                printf("TEST CASE PASSED\n\n");
             }
             else{
                  printf("Expected Output:E_OK\n");
             printf("Actual Output:E_NOK\n");
                printf("TEST CASE FAILED\n\n");
             }
    }
    return 0;
}
signed char Testing___LCD_init(void){
    signed char Test_API_1 =E_OK;
    Test_API_1=LCD_init();
    return Test_API_1;
}

signed char Testing___LCD_sendCommand(uint8 command){
     signed char Test_API_2 =E_OK;
    Test_API_2=LCD_sendCommand(command);
    return Test_API_2;
}
signed char Testing___LCD_displayCharacter(uint8 data){
 signed char Test_API_3 =E_OK;
 Test_API_3=LCD_displayCharacter(data);
 return Test_API_3;
}

signed char Testing___LCD_displayString(const sint8 *str){
signed char Test_API_4 =E_OK;
 Test_API_4=LCD_displayString(&str);
 return Test_API_4;
}

signed char Testing___LCD_goToRowColumn(uint8 row, uint8 col){
signed char Test_API_5 =E_OK;
Test_API_5=LCD_goToRowColumn(row,col);
 return Test_API_5;
}
signed char Testing___LCD_displayStringRowColumn(uint8 row, uint8 col, const sint8* str){
signed char Test_API_6 =E_OK;
Test_API_6=LCD_displayStringRowColumn(row,col,&str);
return Test_API_6;
}
signed char Testing___LCD_displayInteger(uint8 num){
signed char Test_API_7=E_OK;
Test_API_7=LCD_displayInteger(num);
return Test_API_7;
}
signed char Testing___LCD_clearScreen(void){
signed char Test_API_8=E_OK;
Test_API_8=LCD_clearScreen();
return Test_API_8;
}

