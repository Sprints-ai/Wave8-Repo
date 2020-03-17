/*
 * main.c
 *
 * Created: 3/16/2020 2:05:46 PM
 *  Author: A_ayman
 */



/*
*** Inclusions
*/
#include <stdio.h>
#include <stdlib.h>
#include "LCD_Test_Cases.h"
int main()
{
	uint8_t au8_Test_Func_Number = ZERO;
	//line to correct error in IDE related to printf and scanf functions
	setvbuf(stdout,NULL,_IONBF,0);
	printf("Please, Enter The number of the desired function to test...\n");
	printf("choose 1 for LCD_Init_Test \n");
	printf("choose 2 for LCD_SendCommand_Test \n");
	printf("choose 3 for LCD_SendChar_Test\n");
	printf("choose 4 for LCD_DisplayString_Test\n");
    printf("\n\n");
	printf("The number of the desired function to test is ");
	scanf("%d",&au8_Test_Func_Number);
	printf("\n\n");

	switch (au8_Test_Func_Number)
	{
        case 1: LCD_Init_Test(); break;
        case 2: LCD_SendCMD_Test(); break;
        case 3: LCD_SendChar_Test(); break;
        case 4: LCD_DisplayString_Test(); break;
        default: printf("Invalid function number"); break;
	}
	return 0;
}

