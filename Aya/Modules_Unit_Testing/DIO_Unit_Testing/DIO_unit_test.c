#include "DIO_unit_test.h"
#include "MCAL/DIO/DIO.h"

void DIO_Init_Test()
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n");

   printf("Choose 1 for Test happy scenario of DIO initialization function \n");
   printf("Choose 3 for Test Invalid Port Value \n");
   printf("Choose 4 for Test Invalid Port Value with invalid direction \n");
   printf("Choose 5 for Test Multiple Initialization \n");
   printf("\n\n");
   printf("The number of the desired function to test is ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
       case 1:DIO_Init_Test_Case1(); break;
       case 3:DIO_Init_Test_Case3(); break;
       case 4:DIO_Init_Test_Case4(); break;
       case 5:DIO_Init_Test_Case5(); break;
       default: printf("Invalid Test Case number"); break;
    }
}

void DIO_Init_Test_Case1()
{
    uint8_t Ret_Status = E_NOK;
    strDIOCfg_t strDIO_info ={GPIOA,UPPER_NIBBLE,OUTPUT};
    Ret_Status = DIO_Init(&strDIO_info);
    if (Ret_Status == E_OK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}

void DIO_Init_Test_Case3()
{
    uint8_t Ret_Status = E_NOK;
    strDIOCfg_t strDIO_info ={6,UPPER_NIBBLE,OUTPUT};
    Ret_Status = DIO_Init(&strDIO_info);
    if (Ret_Status == E_NOK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}
void DIO_Init_Test_Case4()
{
    uint8_t Ret_Status = E_NOK;
    strDIOCfg_t strDIO_info ={6,UPPER_NIBBLE,OUTPUT};
    Ret_Status = DIO_Init(&strDIO_info);
    if (Ret_Status == E_NOK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}

void DIO_Init_Test_Case5()
{
    uint8_t Ret_Status = E_NOK;
    strDIOCfg_t strDIO_info ={GPIOA,UPPER_NIBBLE,OUTPUT};
    DIO_Init(&strDIO_info);
    Ret_Status = DIO_Init(&strDIO_info);
    if (Ret_Status == E_NOK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}

/*
*** DIO_Write_TEST_CASES
*/

void DIO_Write_Test()
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n");

   printf("Choose 1 for Test happy scenario of DIO Write function \n");
   printf("Choose 2 for Test Invalid Value \n");
   printf("Choose 3 for Test Invalid Port \n");
   printf("Choose 4 for Test Invalid Port with invalid Value \n");
   printf("Choose 5 for Test Write without Initialization \n");
   printf("\n\n");
   printf("The number of the desired function to test is ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
       case 1:DIO_Write_Test_Case1(); break;
       case 2:DIO_Write_Test_Case2(); break;
       case 3:DIO_Write_Test_Case3(); break;
       case 4:DIO_Write_Test_Case4(); break;
       case 5:DIO_Write_Test_Case5(); break;
       default: printf("Invalid Test Case number"); break;
    }
}
void DIO_Write_Test_Case1()
{
    uint8_t Ret_Status = E_NOK;
    strDIOCfg_t strDIO_info ={GPIOA,UPPER_NIBBLE,OUTPUT};
    DIO_Init(&strDIO_info);
    Ret_Status = DIO_Write (GPIOA, UPPER_NIBBLE, HIGH);
    if (Ret_Status == E_OK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}
void DIO_Write_Test_Case2()
{
    uint8_t Ret_Status = E_NOK;
    strDIOCfg_t strDIO_info ={GPIOA,UPPER_NIBBLE,OUTPUT};
    DIO_Init(&strDIO_info);
    Ret_Status = DIO_Write (GPIOA, UPPER_NIBBLE, NULL);
    if (Ret_Status == E_NOK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}

void DIO_Write_Test_Case3()
{
    uint8_t Ret_Status = E_NOK;
    strDIOCfg_t strDIO_info ={GPIOA,UPPER_NIBBLE,OUTPUT};
    DIO_Init(&strDIO_info);
    Ret_Status = DIO_Write (6, UPPER_NIBBLE, NULL);
    if (Ret_Status == E_NOK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}

void DIO_Write_Test_Case4()
{
    uint8_t Ret_Status = E_NOK;
    strDIOCfg_t strDIO_info ={GPIOA,UPPER_NIBBLE,OUTPUT};
    DIO_Init(&strDIO_info);
    Ret_Status = DIO_Write (6, UPPER_NIBBLE, NULL);
    if (Ret_Status == E_NOK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}
void DIO_Write_Test_Case5()
{
    uint8_t Ret_Status = E_NOK;
    Ret_Status = DIO_Write (GPIOA, UPPER_NIBBLE, HIGH);
    if (Ret_Status == E_NOK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}


/*
*** DIO_Read_TEST_CASES
*/

void DIO_Read_Test()
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n");

   printf("Choose 1 for Test happy scenario of DIO Read function \n");
   printf("Choose 2 for Test Invalid Port \n");
   printf("Choose 3 for Test Read without Initialization \n");
   printf("\n\n");
   printf("The number of the desired function to test is ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
       case 1:DIO_Read_Test_Case1(); break;
       case 2:DIO_Read_Test_Case2(); break;
       case 3:DIO_Read_Test_Case3(); break;
       default: printf("Invalid Test Case number"); break;
    }
}

void DIO_Read_Test_Case1()
{
    uint8_t Ret_Status = E_NOK;
    uint8_t Rec_data =0;
    strDIOCfg_t strDIO_info ={GPIOA,UPPER_NIBBLE,OUTPUT};
    DIO_Init(&strDIO_info);
    Ret_Status = DIO_Read(GPIOA, UPPER_NIBBLE, &Rec_data);
    if (Ret_Status == E_OK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}

void DIO_Read_Test_Case2()
{
    uint8_t Ret_Status = E_NOK;
    uint8_t Rec_data =0;
    strDIOCfg_t strDIO_info ={GPIOA,UPPER_NIBBLE,OUTPUT};
    DIO_Init(&strDIO_info);
    Ret_Status = DIO_Read(6, UPPER_NIBBLE, &Rec_data);
    if (Ret_Status == E_NOK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}

void DIO_Read_Test_Case3()
{
    uint8_t Ret_Status = E_NOK;
    uint8_t Rec_data =0;
    Ret_Status = DIO_Read(GPIOA, UPPER_NIBBLE, &Rec_data);
    if (Ret_Status == E_NOK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}


/*
*** DIO_Toggle_TEST_CASES
*/

void DIO_Toggle_Test()
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n");

   printf("Choose 1 for Test happy scenario of DIO Toggle function \n");
   printf("Choose 2 for Test Invalid Port \n");
   printf("Choose 3 for Test Toggle without Initialization \n");
   printf("\n\n");
   printf("The number of the desired function to test is ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
       case 1:DIO_Toggle_Test_Case1(); break;
       case 2:DIO_Toggle_Test_Case2(); break;
       case 3:DIO_Toggle_Test_Case3(); break;
       default: printf("Invalid Test Case number"); break;
    }
}

void DIO_Toggle_Test_Case1()
{
    uint8_t Ret_Status = E_NOK;
    uint8_t Rec_data =0;
    strDIOCfg_t strDIO_info ={GPIOA,UPPER_NIBBLE,OUTPUT};
    DIO_Init(&strDIO_info);
    Ret_Status = DIO_Toggle(GPIOA, UPPER_NIBBLE);
    if (Ret_Status == E_OK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}

void DIO_Toggle_Test_Case2()
{
    uint8_t Ret_Status = E_NOK;
    uint8_t Rec_data =0;
    strDIOCfg_t strDIO_info ={GPIOA,UPPER_NIBBLE,OUTPUT};
    DIO_Init(&strDIO_info);
    Ret_Status = DIO_Toggle(6, UPPER_NIBBLE);
    if (Ret_Status == E_NOK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}

void DIO_Toggle_Test_Case3()
{
    uint8_t Ret_Status = E_NOK;
    uint8_t Rec_data =0;
    Ret_Status = DIO_Toggle(GPIOA, UPPER_NIBBLE);
    if (Ret_Status == E_NOK)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }
    Error_Print();

}
