/*
 * TEST.c
 *
 *  Created on: Mar 23, 2020
 *      Author: Khaled
 */

#include "DIO_Test.h"
#include "PWM_Test.h"

int main (void)
{
	uint8_t au8_Module=0;
		uint8_t au8_Exit ='c';
		//line to correct error in IDE related to printf and scanf functions
		setvbuf(stdout,NULL,_IONBF,0);

			printf("1-DIO MODULE \n");
			printf("2-PWM MODULE \n");
			printf("choose number of function: ");
			scanf("%d",&au8_Module);


			switch (au8_Module)
			{
			case 1:
				DIO_Test();
				break;

			case 2:
				PWM_Test();
				break;

			case 3:

				break;

			case 4:

				break;

			default:
				break;
			}

			printf("Press any key to exit");
			scanf("%C",&au8_Exit);
			scanf("%C",&au8_Exit);


}
