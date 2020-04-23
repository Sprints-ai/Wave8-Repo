#include <stdio.h>
#include <stdlib.h>
#include "DIO.h"


signed char Testing___DIO_init (DIO_Cfg_s *DIO_info);
signed char Testing___DIO_Write(uint8 GPIO, uint8 pins, uint8 value);
signed char Testing___DIO_Read (uint8 GPIO,uint8 pins, uint8 *data);
signed char Testing___DIO_Toggle (uint8 GPIO, uint8 pins);


DIO_Cfg_s DIO_init_Valid_Array_Values[3]={{GPIOA,BIT0,HIGH},{GPIOB,BIT7,LOW},{GPIOD,BIT5,HIGH}};
DIO_Cfg_s DIO_init_IN_valid_Array_Values[3]={{7,BIT0,HIGH},{-8,-1,LOW},{9,12,-1}};
DIO_Cfg_s*null_ptr=NULL;

DIO_Cfg_s DIO_Write_Valid_Array_Values[3]={{GPIOA,BIT0,HIGH},{GPIOB,BIT7,LOW},{GPIOD,BIT5,HIGH}};
DIO_Cfg_s DIO_Write_IN_valid_Array_Values[3]={{7,BIT0,HIGH},{-8,-1,LOW},{9,12,-1}};

uint8 read_data=0;
DIO_Cfg_s DIO_Read_Valid_Array_Values[3]={{GPIOA,BIT0,0},{GPIOB,BIT7,0},{GPIOD,BIT5,0}};
DIO_Cfg_s DIO_Read_IN_valid_Array_Values[3]={{7,BIT0,0},{-8,-1,0},{9,12,0}};

DIO_Cfg_s DIO_Toggle_Valid_Array_Values[3]={{GPIOA,BIT0},{GPIOB,BIT7},{GPIOD,BIT5}};
DIO_Cfg_s DIO_Toggle_IN_valid_Array_Values[3]={{7,BIT0},{-8,-1},{9,12}};

int main()
{
    signed char Check_Test=0;
    signed char Expected=0;
    signed char Actual=0;

    for(uint8 i=0;i<3;i++){
             printf("****************************This is Unit Test for DIO MODULE***************************************\n*******************************************_API_NO#_1_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:DIO_Init\n-INPUT:%d-- %d-- %d\n",i+1,DIO_init_Valid_Array_Values[i].GPIO,DIO_init_Valid_Array_Values[i].pins,DIO_init_Valid_Array_Values[i].dir);
             Check_Test=Testing___DIO_init(&DIO_init_Valid_Array_Values[i]);
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
             printf("****************************This is Unit Test for DIO MODULE***************************************\n*******************************************_API_NO#_1_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:DIO_Init\n-INPUT:%d-- %d-- %d\n",i+4,DIO_init_IN_valid_Array_Values[i].GPIO,DIO_init_IN_valid_Array_Values[i].pins,DIO_init_IN_valid_Array_Values[i].dir);
             Check_Test=Testing___DIO_init(&DIO_init_IN_valid_Array_Values[i]);
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
      printf("****************************This is Unit Test for DIO MODULE***************************************\n*******************************************_API_NO#_1_**************************************************\n*****************************************TEST_CASE_NO#_7***********************************************\n-FUNCTION NAME:DIO_Init\n-INPUT:Null_PTR\n");
     Check_Test=Testing___DIO_init(null_ptr);
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
             printf("****************************This is Unit Test for DIO MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:DIO_Init\n-INPUT:%d-- %d-- %d\n",i+1,DIO_Write_Valid_Array_Values[i].GPIO,DIO_Write_Valid_Array_Values[i].pins,DIO_Write_Valid_Array_Values[i].dir);
             Check_Test=Testing___DIO_Write(DIO_Write_Valid_Array_Values[i].GPIO,DIO_Write_Valid_Array_Values[i].pins,DIO_Write_Valid_Array_Values[i].dir);
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
             printf("****************************This is Unit Test for DIO MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:DIO_Init\n-INPUT:%d-- %d-- %d\n",i+4,DIO_Write_IN_valid_Array_Values[i].GPIO,DIO_Write_IN_valid_Array_Values[i].pins,DIO_Write_IN_valid_Array_Values[i].dir);
             Check_Test=Testing___DIO_Write(DIO_Write_IN_valid_Array_Values[i].GPIO,DIO_Write_IN_valid_Array_Values[i].pins,DIO_Write_IN_valid_Array_Values[i].dir);
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

      printf("****************************This is Unit Test for DIO MODULE***************************************\n*******************************************_API_NO#_3_**************************************************\n*****************************************TEST_CASE_NO#_1***********************************************\n-FUNCTION NAME:DIO_Read\n-INPUT:Null_PTR\n");
     Check_Test=Testing___DIO_Read(GPIOA,BIT2,null_ptr);
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
             printf("****************************This is Unit Test for DIO MODULE***************************************\n*******************************************_API_NO#_3_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:DIO_Read\n-INPUT:%d-- %d-- %d\n",i+2,DIO_Read_Valid_Array_Values[i].GPIO,DIO_Read_Valid_Array_Values[i].pins,0);
             Check_Test=Testing___DIO_Read(DIO_Read_Valid_Array_Values[i].GPIO,DIO_Read_Valid_Array_Values[i].pins,&read_data);
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
             printf("****************************This is Unit Test for DIO MODULE***************************************\n*******************************************_API_NO#_3_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:DIO_read\n-INPUT:%d-- %d-- %d\n",i+5,DIO_Read_IN_valid_Array_Values[i].GPIO,DIO_Write_IN_valid_Array_Values[i].pins,0);
             Check_Test=Testing___DIO_Read(DIO_Read_IN_valid_Array_Values[i].GPIO,DIO_Read_IN_valid_Array_Values[i].pins,&read_data);
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
             printf("****************************This is Unit Test for DIO MODULE***************************************\n*******************************************_API_NO#_4_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:DIO_Toggle\n-INPUT:%d-- %d-- %d\n",i+1,DIO_Toggle_Valid_Array_Values[i].GPIO,DIO_Toggle_Valid_Array_Values[i].pins);
             Check_Test=Testing___DIO_Toggle(DIO_Toggle_Valid_Array_Values[i].GPIO,DIO_Toggle_Valid_Array_Values[i].pins);
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
             printf("****************************This is Unit Test for DIO MODULE***************************************\n*******************************************_API_NO#_4_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME:DIO_read\n-INPUT:%d-- %d-- %d\n",i+4,DIO_Toggle_IN_valid_Array_Values[i].GPIO,DIO_Toggle_IN_valid_Array_Values[i].pins);
             Check_Test=Testing___DIO_Toggle(DIO_Toggle_IN_valid_Array_Values[i].GPIO,DIO_Toggle_IN_valid_Array_Values[i].pins);
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

signed char Testing___DIO_init(DIO_Cfg_s *DIO_info){
    signed char Test_API_1=E_OK;
    Test_API_1=DIO_init(DIO_info);
    return Test_API_1;
}
signed char Testing___DIO_Write (uint8 GPIO, uint8 pins, uint8 value){
  signed char Test_API_2 =E_OK;
  Test_API_2=DIO_Write(GPIO,pins,value);
  return Test_API_2;
}
signed char Testing___DIO_Read (uint8 GPIO,uint8 pins, uint8 *data){
    signed char Test_API_3=E_OK;
    Test_API_3=DIO_Read(GPIO,pins,data);
    return Test_API_3;
}
signed char Testing___DIO_Toggle (uint8 GPIO, uint8 pins){
   signed char Test_API_4=E_OK;
   Test_API_4=DIO_Toggle(GPIO,pins);
   return Test_API_4;
   }

