/*
 * DIO_Test.c
 *
 *  Created on: Mar 23, 2020
 *      Author: Khaled
 */

#include "DIO_Test.h"



#define RESULT_INITIAL_VALUE  6



static void DIO_init_Test (void);
static void DIO_Write_Test (void);
static void DIO_Read_Test (void);
static void DIO_Toggle_Test (void);



void DIO_Test (void)
{
	uint8_t au8_func=0;
	uint8_t au8_Exit ='c';
	//line to correct error in IDE related to printf and scanf functions
	setvbuf(stdout,NULL,_IONBF,0);

		printf("1-DIO INIT \n");
		printf("2-DIO WRITE \n");
		printf("3-DIO READ  \n");
		printf("4-DIO TOGGLE \n");
		printf("choose number of function: ");
		scanf("%d",&au8_func);


		switch (au8_func)
		{
		case 1:
			DIO_init_Test();
			break;

		case 2:
			DIO_Write_Test();
			break;

		case 3:
			DIO_Read_Test();
			break;

		case 4:
			DIO_Toggle_Test();
			break;

		default:
			break;
		}

}


void DIO_init_Test (void)
{
	DIO_Cfg_s DIO_Info;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;


	/*case 1*/
	DIO_Info.GPIO = 10;
	DIO_Info.dir = OUTPUT;
	DIO_Info.pins = FULL_PORT;

	au8_Result = DIO_init(&DIO_Info);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("  test case 1  passed \n");

	else
		printf("  test case 1  failed \n");

	Error_Dinit();
	/*********************************************************************************************/

	/*case 2*/
	DIO_Info.GPIO = GPIOA;
	DIO_Info.dir = 0x52;
	DIO_Info.pins = FULL_PORT;

	au8_Result = DIO_init(&DIO_Info);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("  test case 2  passed \n");

	else
		printf("  test case 2  failed \n");

	Error_Dinit();
	/*********************************************************************************************/

	/*case 3*/
	DIO_Info.GPIO = 12;
	DIO_Info.dir = 55;
	DIO_Info.pins = 0x11;

	au8_Result = DIO_init(&DIO_Info);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("  test case 3  passed \n");

	else
		printf("  test case 3  failed \n");

	Error_Dinit();

	/*********************************************************************************************/

	/*case 4*/
	DIO_Info.GPIO = GPIOA;
	DIO_Info.dir = OUTPUT;
	DIO_Info.pins = BIT2;

	au8_Result = DIO_init(NULL);
	Error_Print();

	if(E_NOK == au8_Result)
		printf("       test case 4  passed \n");

	else
		printf("       test case 4  failed \n");

	Error_Dinit();
	/*********************************************************************************************/

	/*case 5*/
	DIO_Info.GPIO = GPIOA;
	DIO_Info.dir = OUTPUT;
	DIO_Info.pins = BIT2;

	au8_Result = DIO_init(&DIO_Info);
	Error_Print();

	if(E_OK == au8_Result)
		printf("                                                     test case 5  passed \n");

	else
		printf("                                                     test case 5  failed \n");

	Error_Dinit();
}

void DIO_Write_Test (void)
{
	DIO_Cfg_s DIO_Info;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;


	/*case 1*/
	au8_Result = DIO_Write(GPIOA,BIT2,HIGH);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("    test case 1  passed \n");

	else
		printf("    test case 1  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 2*/
	DIO_Info.GPIO = GPIOA;
	DIO_Info.dir = OUTPUT;
	DIO_Info.pins = FULL_PORT;
	DIO_init(&DIO_Info);

	au8_Result = DIO_Write(0x20,BIT2,HIGH);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("  test case 2  passed \n");

	else
		printf("  test case 2  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 3*/

	au8_Result = DIO_Write(GPIOA,BIT2,0x55);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("  test case 3  passed \n");

	else
		printf("  test case 3  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 4*/
	au8_Result = DIO_Write(GPIOA,BIT2,HIGH);
	Error_Print();

	if((E_OK == au8_Result) && ((GET_BIT(PORTA_DATA,BIT2)) == 0x4))
		printf("               and write correct data                test case 4  passed \n");

	else
		printf("                                                     test case 4  failed \n");

	Error_Dinit();
}

void DIO_Read_Test (void)
{
	DIO_Cfg_s DIO_Info;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	uint8_t au8_Data;

	/*case 1*/
	au8_Result = DIO_Read(GPIOA,BIT1,&au8_Data);
	Error_Print();
	if(E_NOK == au8_Result)
		printf("    test case 1  passed \n");

	else
		printf("    test case 1  failed \n");
	Error_Dinit();
	/*********************************************************************************************************/
	/*case 2*/
	DIO_Info.GPIO = GPIOA;
	DIO_Info.dir = OUTPUT;
	DIO_Info.pins = FULL_PORT;
	DIO_init(&DIO_Info);

	au8_Result = DIO_Read(0x30,BIT1,&au8_Data);
	Error_Print();
	if(E_NOK == au8_Result)
		printf("  test case 2  passed \n");

	else
		printf("  test case 2  failed \n");
	Error_Dinit();
	/*********************************************************************************************************/
	/*case 3*/
	au8_Result = DIO_Read(GPIOA,BIT1,NULL);
	Error_Print();
	if(E_NOK == au8_Result)
		printf("       test case 3  passed \n");

	else
		printf("       test case 3  failed \n");
	Error_Dinit();
	/*********************************************************************************************************/
	/*case 4*/
	PORTA_PIN = HIGH;
	au8_Result = DIO_Read(GPIOA,BIT1,&au8_Data);
	Error_Print();
	if((E_OK == au8_Result) && (au8_Data == HIGH))
		printf("        and return correct data                      test case 4  passed \n");

	else
		printf("                                                     test case 4  failed \n");
	Error_Dinit();

}

void DIO_Toggle_Test (void)
{
	DIO_Cfg_s DIO_Info;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;

	/*case 1*/
	au8_Result = DIO_Toggle(GPIOA,BIT1);
	Error_Print();
	if(E_NOK == au8_Result)
		printf("    test case 1  passed \n");

	else
		printf("    test case 1  failed \n");
	Error_Dinit();
	/*******************************************************************************************************************/
	/*case 2*/
	DIO_Info.GPIO = GPIOA;
	DIO_Info.dir = OUTPUT;
	DIO_Info.pins = FULL_PORT;
	DIO_init(&DIO_Info);

	au8_Result = DIO_Toggle(0x20,BIT2);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("  test case 2  passed \n");

	else
		printf("  test case 2  failed \n");

	Error_Dinit();

	/*********************************************************************************************/
	/*case 3*/
	PORTA_DATA = LOW;
	au8_Result = DIO_Toggle(GPIOA,BIT2);
	Error_Print();

	if((E_OK == au8_Result) && ((GET_BIT(PORTA_DATA,BIT2)) == 0x4))
		printf("                   and write correct data            test case 3  passed \n");

	else
		printf("                                                     test case 3  failed \n");

	Error_Dinit();
}
