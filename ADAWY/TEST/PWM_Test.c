/*
 * PWM_Test.c
 *
 *  Created on: Mar 24, 2020
 *      Author: Khaled
 */


#include "PWM_Test.h"



#define RESULT_INITIAL_VALUE  6



static void Pwm_Init_Test (void);
static void Pwm_Start_Test (void);
static void Pwm_Update_Test (void);
static void Pwm_Stop_Test (void);

void PWM_Test (void)
{
	uint8_t au8_func=0;
	uint8_t au8_Exit ='c';
	//line to correct error in IDE related to printf and scanf functions
	setvbuf(stdout,NULL,_IONBF,0);

	printf("1-PWM INIT \n");
	printf("2-PWM START \n");
	printf("3-PWM UPDATE  \n");
	printf("4-PWM STOP \n");
	printf("choose number of function: ");
	scanf("%d",&au8_func);


	switch (au8_func)
	{
	case 1:
		Pwm_Init_Test();
		break;

	case 2:
		Pwm_Start_Test();
		break;

	case 3:
		Pwm_Update_Test();
		break;

	case 4:
		Pwm_Stop_Test();
		break;

	default:
		break;
	}

}


void Pwm_Init_Test (void)
{
	Pwm_Cfg_s PWM_Info;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;


	/*case 1*/


	au8_Result = Pwm_Init(&PWM_Info);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("        test case 1  passed \n");

	else
		printf("        test case 1  failed \n");

	Error_Dinit();
	/*********************************************************************************************/

	/*case 2*/
	PWM_Info.Channel = 0x50;
	PWM_Info.Prescaler = 0x100;

	au8_Result = Pwm_Init(&PWM_Info);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("            test case 2  passed \n");

	else
		printf("            test case 2  failed \n");

	Error_Dinit();
	/*********************************************************************************************/

	/*case 3*/
	PWM_Info.Channel = PWM_CH0;
	PWM_Info.Prescaler = 0x100;

	au8_Result = Pwm_Init(&PWM_Info);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("        test case 3  passed \n");

	else
		printf("        test case 3  failed \n");

	Error_Dinit();

	/*********************************************************************************************/

	/*case 4*/
	PWM_Info.Channel = 0x50;
	PWM_Info.Prescaler = PRESCALER_1;

	au8_Result = Pwm_Init(&PWM_Info);
	Error_Print();

	if(E_NOK == au8_Result)
		printf("            test case 4  passed \n");

	else
		printf("            test case 4  failed \n");

	Error_Dinit();
	/*********************************************************************************************/

	/*case 5*/
	PWM_Info.Channel = PWM_CH0;
	PWM_Info.Prescaler = PRESCALER_8;

	au8_Result = Pwm_Init(&PWM_Info);
	Error_Print();

	if(E_NOK == au8_Result)
		printf("        test case 5  passed \n");

	else
		printf("        test case 5  failed \n");

	Error_Dinit();
	/*********************************************************************************************/

	/*case 6*/
	PWM_Info.Channel = PWM_CH1A;
	PWM_Info.Prescaler = PRESCALER_32;

	au8_Result = Pwm_Init(&PWM_Info);
	Error_Print();

	if(E_NOK == au8_Result)
		printf("            test case 6  passed \n");

	else
		printf("            test case 6  failed \n");

	Error_Dinit();
	/*********************************************************************************************/

	/*case 7*/
	PWM_Info.Channel = PWM_CH0;
	PWM_Info.Prescaler = PRESCALER_64;

	au8_Result = Pwm_Init(&PWM_Info);
	Error_Print();

	if(E_NOK == au8_Result)
		printf("        test case 7  passed \n");

	else
		printf("        test case 7  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 8*/
	PWM_Info.Channel = PWM_CH1A;
	PWM_Info.Prescaler = PRESCALER_64;

	au8_Result = Pwm_Init(NULL);
	Error_Print();

	if(E_NOK == au8_Result)
		printf("                 test case 8  passed \n");

	else
		printf("                 test case 8  failed \n");

	Error_Dinit();
	/*********************************************************************************************/

	/*case 9*/
	PWM_Info.Channel = PWM_CH1A;
	PWM_Info.Prescaler = PRESCALER_64;

	au8_Result = Pwm_Init(&PWM_Info);
	Error_Print();

	if(E_OK == au8_Result)
		printf("                                                               test case 9  passed \n");

	else
		printf("                                                               test case 9  failed \n");

	Error_Dinit();
}


void Pwm_Start_Test (void)
{
	Pwm_Cfg_s PWM_Info;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;

	/*case 1*/
	au8_Result = Pwm_Start(PWM_CH1B,25,PWM_FREQUENCY_100);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("          test case 1  passed \n");

	else
		printf("          test case 1  failed \n");

	Error_Dinit();

	/*********************************************************************************************/

	/*case 2*/
	PWM_Info.Channel = PWM_CH1A;
	PWM_Info.Prescaler = PRESCALER_64;
	Pwm_Init(&PWM_Info);

	au8_Result = Pwm_Start(PWM_CH1A,25,50);
	Error_Print();

	if(E_NOK == au8_Result)
		printf("        test case 2  passed \n");

	else
		printf("        test case 2  failed \n");

	Error_Dinit();
	/*********************************************************************************************/


	/*case 3*/
	au8_Result = Pwm_Start(PWM_CH1A,25,50);
	Error_Print();

	if(E_NOK == au8_Result)
		printf("        test case 3  passed \n");

	else
		printf("        test case 3  failed \n");

	Error_Dinit();
	/*********************************************************************************************/

	/*case 4*/
	au8_Result = Pwm_Start(PWM_CH1A,200,PWM_FREQUENCY_100);
	Error_Print();

	if(E_NOK == au8_Result)
		printf("        test case 4  passed \n");

	else
		printf("        test case 4  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 5*/
	au8_Result = Pwm_Start(PWM_CH0,25,PWM_FREQUENCY_100);
	Error_Print();

	if(E_NOK == au8_Result)
		printf("    test case 5  passed \n");

	else
		printf("    test case 5  failed \n");

	Error_Dinit();
	/*********************************************************************************************/

	/*case 6*/
	au8_Result = Pwm_Start(PWM_CH1A,25,PWM_FREQUENCY_100);
	Error_Print();

	if(E_OK == au8_Result)
		printf("                                                           test case 6  passed \n");

	else
		printf("                                                           test case 6  failed \n");

	Error_Dinit();
	/*********************************************************************************************/

	/*case 7*/
	au8_Result = Pwm_Start(PWM_CH1A,25,PWM_FREQUENCY_100);
	Error_Print();

	if(E_NOK == au8_Result)
		printf("    test case 7  passed \n");

	else
		printf("    test case 7  failed \n");

	Error_Dinit();
}


void Pwm_Update_Test (void)
{
	Pwm_Cfg_s PWM_Info;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;

	/*case 1*/
	au8_Result = Pwm_Update(PWM_CH1B,25,PWM_FREQUENCY_100);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("          test case 1  passed \n");

	else
		printf("          test case 1  failed \n");

	Error_Dinit();

	/*********************************************************************************************/

	/*case 2*/
	PWM_Info.Channel = PWM_CH1A;
	PWM_Info.Prescaler = PRESCALER_64;
	Pwm_Init(&PWM_Info);

	au8_Result = Pwm_Update(PWM_CH1A,25,50);
	Error_Print();

	if(E_NOK == au8_Result)
		printf("          test case 2  passed \n");

	else
		printf("          test case 2  failed \n");

	Error_Dinit();
	/*********************************************************************************************/


	/*case 3*/
	Pwm_Start(PWM_CH1A,25,PWM_FREQUENCY_100);
	au8_Result = Pwm_Update(PWM_CH1A,25,50);
	Error_Print();

	if(E_NOK == au8_Result)
		printf(" test case 3  passed \n");

	else
		printf(" test case 3  failed \n");

	Error_Dinit();
	/*********************************************************************************************/

	/*case 4*/
	au8_Result = Pwm_Update(PWM_CH1A,200,PWM_FREQUENCY_100);
	Error_Print();

	if(E_NOK == au8_Result)
		printf(" test case 4  passed \n");

	else
		printf(" test case 4  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 5*/
	au8_Result = Pwm_Update(PWM_CH0,25,PWM_FREQUENCY_100);
	Error_Print();

	if(E_NOK == au8_Result)
		printf("   test case 5  passed \n");

	else
		printf("   test case 5  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 6*/

		au8_Result = Pwm_Update(PWM_CH1A,25,50);
		Error_Print();

		if(E_NOK == au8_Result)
			printf(" test case 6  passed \n");

		else
			printf(" test case 6  failed \n");

		Error_Dinit();
		/*********************************************************************************************/
	/*case 7*/
	au8_Result = Pwm_Update(PWM_CH1A,25,PWM_FREQUENCY_100);
	Error_Print();

	if(E_OK == au8_Result)
		printf("                                                    test case 7  passed \n");

	else
		printf("                                                    test case 7  failed \n");

	Error_Dinit();
}





void Pwm_Stop_Test (void)
{
	Pwm_Cfg_s PWM_Info;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;

	/*case 1*/
	au8_Result = Pwm_Stop(PWM_CH1B);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("          test case 1  passed \n");

	else
		printf("          test case 1  failed \n");

	Error_Dinit();

	/*********************************************************************************************/

	/*case 2*/
	PWM_Info.Channel = PWM_CH1A;
	PWM_Info.Prescaler = PRESCALER_64;
	Pwm_Init(&PWM_Info);
    Pwm_Start(PWM_CH1A,25,PWM_FREQUENCY_100);

	au8_Result = Pwm_Stop(PWM_CH1B);
	Error_Print();

	if(E_NOK == au8_Result)
		printf("          test case 2  passed \n");

	else
		printf("          test case 2  failed \n");

	Error_Dinit();
	/*********************************************************************************************/

	/*case 3*/
	au8_Result = Pwm_Stop(PWM_CH1A);
	Error_Print();

	if(E_OK == au8_Result)
		printf("                                                    test case 3  passed \n");

	else
		printf("                                                    test case 3  failed \n");

	Error_Dinit();
}
