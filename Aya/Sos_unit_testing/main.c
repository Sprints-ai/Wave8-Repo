/*
 * Sos_unit_testing.c
 *
 * Created: 3/11/2020 2:07:45 AM
 * Author : A_ayman
 */

/*
***Inclusions
*/
#include <stdio.h>
#include <stdlib.h>
#include "SOS/SOS.h"
#include "Sos_Test_Cases.h"




int main (void)
{
	uint8_t au8_Test_Func_Number = ZERO;
	//line to correct error in IDE related to printf and scanf functions
	setvbuf(stdout,NULL,_IONBF,0);
	printf("Please, Enter The number of the desired function to test...\n");
	printf("choose 1 for SOS_Init_Test \n");
	printf("choose 2 for Sos_Create_Task_Test \n");
	printf("choose 3 for Sos_Delete_Task_Test\n");
	printf("choose 4 for SOS_Deinit_Test\n");
    printf("\n\n");
	printf("The number of the desired function to test is ");
	scanf("%d",&au8_Test_Func_Number);
	printf("\n\n");

	switch (au8_Test_Func_Number)
	{
        case 1: Sos_Init_Test(); break;
        case 2: Sos_Create_Task_Test(); break;
        case 3: Sos_Delete_Task_Test(); break;
        case 4: Sos_Deinit_Task_Test(); break;
        default: printf("Invalid function number"); break;
	}
	return 0;
}


