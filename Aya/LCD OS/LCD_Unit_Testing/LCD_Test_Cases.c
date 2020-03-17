/*
 * LCD_Test_Cases.c
 *
 * Created: 3/16/2020 2:05:46 PM
 *  Author: A_ayman
 */

/*
*** Inclusions
*/
#include "LCD_Test_Cases.h"
#include "HAL/LCD/LCD.h"
#include "LCD_Mock.h"

void LCD_Init_Test(void)
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n");
   printf("choose 1 for Test happy scenario of initialization \n");
   printf("choose 2 for Test Function Behavior if something went wrong from the layer below (MCAL/DIO)\n");
   printf("\n\n");
   printf("The number of the desired function to test is ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
       case 1:LCD_Init_Test_Case1(); break;
       case 2:LCD_Init_Test_Case2(); break;
       default: printf("Invalid Test Case number"); break;
    }
}

/*check the happy scenario of the function*/
void LCD_Init_Test_Case1()
{
    uint8_t u8_Ret_Status = E_OK;
    gu8_DIO_Init_Return = E_OK;
    u8_Ret_Status |= LCD_Init ();
    if (u8_Ret_Status == E_OK)
    {
        printf(" Passed \n ");
    }
    else
    {
        printf(" Failed  \n ");
    }
    Error_Print();
}

/*check the behavior of the function if DIO went wrong*/
void LCD_Init_Test_Case2()
{
    uint8_t u8_Ret_Status = E_OK;
    gu8_DIO_Init_Return = E_NOK;
    u8_Ret_Status |= LCD_Init ();
    if (u8_Ret_Status == E_NOK)
    {
        printf(" Passed \n");
    }
    else
    {
        printf(" Failed  \n");
    }
    Error_Print();
}



void LCD_SendCMD_Test(void)
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n");
   printf("choose 1 for Test happy scenario of sending Command \n");
   printf("choose 2 for Test Sending Before Initializing LCD itself\n");
   printf("\n\n");
   printf("The number of the desired function to test is ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
       case 1:LCD_SendCMD_Test_Case1(); break;
       case 2:LCD_SendCMD_Test_Case2(); break;
       default: printf("Invalid Test Case number"); break;
    }
}
/*Test happy scenario of sending Command */
void LCD_SendCMD_Test_Case1()
{
    uint8_t u8_Ret_Status = E_OK;
    gu8_DIO_Init_Return = E_OK;
    u8_Ret_Status |= LCD_Init ();
    u8_Ret_Status |= LCD_sendCommand(0x00);
    if (u8_Ret_Status == E_OK)
    {
        printf(" Passed \n");
    }
    else
    {
        printf(" Failed  \n");
    }

    Error_Print();
}
/*Test Sending Before Initializing LCD itself*/
void LCD_SendCMD_Test_Case2()
{
    uint8_t u8_Ret_Status = E_OK;
    u8_Ret_Status |= LCD_sendCommand(0x00);
    if (u8_Ret_Status == E_NOK)
    {
        printf(" Passed \n");
    }
    else
    {
        printf(" Failed  \n");
    }

    Error_Print();
}

void LCD_SendChar_Test(void)
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n");
   printf("choose 1 for Test happy scenario of sending Character \n");
   printf("choose 2 for Test Sending Character Before Initializing LCD itself\n");
   printf("choose 3 for Test Sending null Character \n");
   printf("\n\n");
   printf("The number of the desired function to test is ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
       case 1:LCD_SendChar_Test_Case1(); break;
       case 2:LCD_SendChar_Test_Case2(); break;
       case 3:LCD_SendChar_Test_Case3(); break;
       default: printf("Invalid Test Case number"); break;
    }
}
/*Test happy scenario of sending Command */
void LCD_SendChar_Test_Case1()
{
    uint8_t u8_Ret_Status = E_OK;
    gu8_DIO_Init_Return = E_OK;
    u8_Ret_Status |= LCD_Init ();
    u8_Ret_Status |= LCD_displayChar('a');
    if (u8_Ret_Status == E_OK)
    {
        printf(" Passed \n");
    }
    else
    {
        printf(" Failed  \n");
    }

    Error_Print();
}

/*Test Sending Before Initializing LCD itself*/
void LCD_SendChar_Test_Case2()
{
    uint8_t u8_Ret_Status = E_OK;
    u8_Ret_Status |= LCD_displayChar('a');
    if (u8_Ret_Status == E_NOK)
    {
        printf(" Passed \n");
    }
    else
    {
        printf(" Failed  \n");
    }

    Error_Print();
}

/*Test Sending null Character*/
void LCD_SendChar_Test_Case3()
{
    uint8_t u8_Ret_Status = E_OK;
    gu8_DIO_Init_Return = E_OK;
    u8_Ret_Status |= LCD_Init ();
    u8_Ret_Status |= LCD_displayChar('\0');
    if (u8_Ret_Status == E_NOK)
    {
        printf(" Passed \n");
    }
    else
    {
        printf(" Failed  \n");
    }

    Error_Print();
}





void LCD_DisplayString_Test(void)
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n");
   printf("choose 1 for Test happy scenario of Displaying string \n");
   printf("choose 2 for Test Displaying String Before Initializing LCD itself\n");
   printf("choose 3 for Test Displaying null Pointer \n");
   printf("\n\n");
   printf("The number of the desired function to test is ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
       case 1: LCD_DisplayString_Test_Case1(); break;
       case 2:LCD_DisplayString_Test_Case2(); break;
       case 3:LCD_DisplayString_Test_Case3(); break;
       default: printf("Invalid Test Case number"); break;
    }
}

/*Test happy scenario of sending Command */
void LCD_DisplayString_Test_Case1()
{
    uint8_t u8_Ret_Status = E_OK;
    gu8_DIO_Init_Return = E_OK;
    u8_Ret_Status |= LCD_Init ();

    u8_Ret_Status |= LCD_displayString("aya");
    if (u8_Ret_Status == E_OK)
    {
        printf(" Passed \n");
    }
    else
    {
        printf(" Failed  \n");
    }

    Error_Print();
}

/*Test Sending Before Initializing LCD itself*/
void LCD_DisplayString_Test_Case2()
{
    uint8_t u8_Ret_Status = E_OK;
    u8_Ret_Status |= LCD_displayString("aya");
    if (u8_Ret_Status == E_NOK)
    {
        printf(" Passed \n");
    }
    else
    {
        printf(" Failed  \n");
    }

    Error_Print();
}


/*Test Sending null Pointer*/
void LCD_DisplayString_Test_Case3()
{
    uint8_t u8_Ret_Status = E_OK;
    gu8_DIO_Init_Return = E_OK;
    u8_Ret_Status |= LCD_Init ();
    u8_Ret_Status |= LCD_displayString('\0');
    if (u8_Ret_Status == E_NOK)
    {
        printf(" Passed \n");
    }
    else
    {
        printf(" Failed  \n");
    }

    Error_Print();
}
