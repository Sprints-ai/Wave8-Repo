#include <stdio.h>
#include <stdlib.h>
#include "DIO_unit_test.h"
int main (void)
{
	uint8_t au8_Test_Func_Number = ZERO;
	//line to correct error in IDE related to printf and scanf functions
	setvbuf(stdout,NULL,_IONBF,0);
	printf("Please, Enter The number of the desired function to test...\n");
	printf("        Choose 1 for DIO_Init_Test \n");
	printf("        Choose 2 for DIO_Write_Test \n");
	printf("        Choose 3 for DIO_Read_Test \n");
	printf("        Choose 4 for DIO_Toggle_Test \n");
    printf("\n\n");
	printf("The number of the desired function to test is... ");
	scanf("%d",&au8_Test_Func_Number);
	printf("\n\n");

	switch (au8_Test_Func_Number)
	{
        case 1: DIO_Init_Test(); break;
        case 2: DIO_Write_Test(); break;
        case 3: DIO_Read_Test(); break;
        case 4: DIO_Toggle_Test(); break;
        default: printf("Invalid function number"); break;
	}
	return 0;
}
