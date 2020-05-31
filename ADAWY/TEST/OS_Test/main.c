#include <stdio.h>
#include <stdlib.h>
#include "SERVICE/OS/OS.h"

#include "OS_Test_Casses.h"




int main (void)
{
	uint8_t au8_Test_Func_Number = ZERO;
	//line to correct error in IDE related to printf and scanf functions
	setvbuf(stdout,NULL,_IONBF,0);
	//Test_Consumer();
	printf("Please, Enter The number of the desired function to test...\n");
	printf("choose 1 for OS_Init \n");
	printf("choose 2 for Task_CReat \n");
	printf("choose 3 for Task_Delet \n");
	printf("choose 4 for OS_Dinit \n");
    printf("\n\n");
	printf("The number of the desired function to test is ");
	scanf("%d",&au8_Test_Func_Number);
	printf("\n\n");

	switch (au8_Test_Func_Number)
	{
        case 1: OS_Init_Test(); break;
        case 2: Task_Creat_Test(); break;
        case 3: Task_Delet_Test(); break;
        case 4: OS_Dinit_Test(); break;
        default: printf("Invalid function number"); break;
	}
	return 0;
}


