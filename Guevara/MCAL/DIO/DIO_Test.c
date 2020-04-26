#include "Mock_DIO.h"
#include "stdio.h"
#include "stdlib.h"
uint8_t test_Scinarios_Write (uint8_t test_Case_Num);
uint8_t test_Scinarios_Read(uint8_t test_Case_Num);
uint8_t test_Scinarios_Toggle (uint8_t test_Case_Num);
uint8_t test_Scinarios_INIT (uint8_t test_Case_Num);
/*****************************************************************************************************************************************************/
/*		Test Scinarios
1. DIO_INIT_1		Valid Port ... Valid Direction
2. DIO_INIT_2		inValid Port ... Valid Direction
3. DIO_INIT_3		Valid Port ... inValid Direction
4. DIO_INIT_4		NULL_PTR
5. DIO_INIT_5	  Multiple init	Valid Port ... Valid Direction
6. DIO_INIT_6		inValid Port ... inValid Direction
 */
/*****************************************************************************************************************************************************/
int main(){
	/************************************************************************************************/
	if(!test_Scinarios_INIT (1))
		printf("passed test case 1\n");
	else
		printf("failed test case 1\n");

	if(test_Scinarios_INIT (2)== E_NOK+DIO_MODULE+INVALID_PORT)
		printf("passed test case 2\n");
	else
		printf("failed test case 2\n");


	if(test_Scinarios_INIT (3)== E_NOK+DIO_MODULE+INVALID_DIRECTION)
		printf("passed test case 3\n");
	else
		printf("failed test case 3\n");


	if(test_Scinarios_INIT (4) == NULL_PTR+DIO_MODULE)
		printf("passed test case 4\n");
	else
		printf("failed test case 4\n");


	if(test_Scinarios_INIT (5) == MULTIPLE_INIT)
		printf("passed test case 5\n");
	else
		printf("failed test case 5\n");
/*NOte that it cant report both invalid port and direction in the same time*/
	if(test_Scinarios_INIT (6) == E_NOK+DIO_MODULE+INVALID_DIRECTION)
		printf("passed test case 6\n\n\n");
	else
		printf("failed test case 6\n\n");

	/************************************************************************************************/
	if(test_Scinarios_Write (1)==E_OK+DIO_MODULE)
		printf("passed test case Write 1\n");
	else
		printf("failed test case Write 1\n");

	if(test_Scinarios_Write (2) == DIO_MODULE+INVALID_VALUE)
		printf("passed test case Write 2\n");
	else
		printf("failed test case Write 2\n");
	
	if(test_Scinarios_Write (3)== DIO_MODULE+INVALID_PORT)
		printf("passed test case Write 3\n");
	else
		printf("failed test case Write 3\n");

	if(test_Scinarios_Write (4)== DIO_MODULE+INVALID_VALUE)
		printf("passed test case Write 4\n");
	else
		printf("failed test case Write 4\n");
	
	if(test_Scinarios_Write (5) == DIO_MODULE+NOT_INIT)
		printf("passed test case Write 5\n\n\n");
	else
		printf("failed test case Write 5\n\n\n");
	/************************************************************************************************/
	if(test_Scinarios_Read(1)==E_OK+DIO_MODULE)
		printf("passed test case Read 1\n");
	else
		printf("failed test case Read 1\n");
	if(test_Scinarios_Read(2) == DIO_MODULE+INVALID_PORT)
		printf("passed test case Read 2\n");
	else
		printf("failed test case Read 2\n");
	
	if(test_Scinarios_Read(3)== DIO_MODULE+NOT_INIT)
		printf("passed test case Read 3\n\n\n");
	else
		printf("failed test case Read 3\n\n\n");
	/************************************************************************************************/
	if(test_Scinarios_Toggle(1)==E_OK+DIO_MODULE)
		printf("passed test case Toggle 1\n");
	else
		printf("failed test case Toggle 1\n");

	if(test_Scinarios_Toggle(2) == DIO_MODULE+INVALID_PORT)
		printf("passed test case Toggle 2\n");
	else
		printf("failed test case Toggle 2\n");
	
	if(test_Scinarios_Toggle(3)== DIO_MODULE+NOT_INIT)
		printf("passed test case  Toggle 3\n\n\n");
	else
		printf("failed test case Toggle 3\n\n\n");
	/************************************************************************************************/
	
	
	return 0;
}
uint8_t test_Scinarios_INIT (uint8_t test_Case_Num)
{
	uint8_t ret=0;
	switch (test_Case_Num) {
	case 1:
	ret=DIO_init(&Dio_configurationA);
		printf("PORTA=%#X\n",PORTA_DIR);
		break;
		/*invalid port valid direction*/
	case 2:
		ret=DIO_init(&Dio_configurationB);
		break;
		/*DIO_INIT_3		Valid Port ... inValid Direction*/
	case 3:
		ret=DIO_init(&Dio_configurationC);
		break;
		/*NULL_PTR*/
	case 4:
		ret=DIO_init(0);
		break;
		/*5. DIO_INIT_5	Multiple init	Valid Port ... Valid Direction*/
	case 5:
	
		ret=DIO_init(&Dio_configurationA);
		ret=DIO_init(&Dio_configurationA);
		break;
		/* 6. DIO_INIT_6		inValid Port ... inValid Direction */
	case 6:
		ret=DIO_init(&Dio_configurationD);
		break;
	}
	return ret;
}

/*****************************************************************************************************************************************************/
/*		Test Scinarios
1. DIO_Write_1		init with valid configuration ....Valid Port ... Valid Value
2. DIO_Write_2		init with valid configuration ....Valid Port ... InValid Value
3. DIO_Write_3		init with valid configuration ....InValid Port ... Valid Value
4. DIO_Write_4		init with valid configuration ....InValid Port ... InValid Value
5. DIO_Write_5		Valid Port ... Valid Value without init
 */
/*****************************************************************************************************************************************************/


uint8_t test_Scinarios_Write (uint8_t test_Case_Num)
{	
	uint8_t ret=0;
	
	switch (test_Case_Num) {
	case 1:
		printf("PORTA_DATA=%#X\n",PORTA_DATA);
		DIO_init(&Dio_configurationA);
		ret=DIO_Write(GPIOA,BIT1|BIT2,HIGH);
		printf("PORTA_DATA=%#X\n",PORTA_DATA);
		break;
		/*Valid Port ... Valid Value*/
	case 2:
	DIO_init(&Dio_configurationA);
		ret=DIO_Write(GPIOA,BIT1|BIT2,5);
		break;
		/*Valid Port ... InValid Value*/
	case 3:
	DIO_init(&Dio_configurationA);
		ret=DIO_Write(6,BIT1|BIT2,HIGH);
		break;
		/*InValid Port ... Valid Value*/
	case 4:
	DIO_init(&Dio_configurationA);
		ret=DIO_Write(9,BIT1|BIT2,8);
		break;
		/*4. InValid Port ... InValid Value*/
	case 5:
		DIO_deinit();
		ret=DIO_Write(GPIOA,BIT1|BIT2,HIGH);
		break;
		/*Valid Port ... Valid Value without init*/
	}

return ret;
}
/*****************************************************************************************************************************************************/
/*		Test Scinarios
1. DIO_Read_1		init with valid configuration ....Valid Port
2. DIO_Read_2		init with valid configuration ....InValid Port
3. DIO_Read_3		Valid Port ...without init
 */
/*****************************************************************************************************************************************************/
uint8_t test_Scinarios_Read(uint8_t test_Case_Num){
	uint8_t ret=0;
	uint8_t Data;
	switch (test_Case_Num) {
	case 1:
	DIO_is_init();
	PORTC_PIN=150;
	ret=DIO_Read (GPIOC,BIT0|BIT5|BIT7,&Data);
	printf("read=%d\n",Data);
	break;
		/*Valid Port*/
	case 2:
	DIO_is_init();
		ret=DIO_Read (20,BIT0,&Data);
		break;
		/*InValid Port*/
	case 3:
	DIO_deinit();
		ret=DIO_Read (GPIOC,BIT0,&Data);
		break;
			/*Valid Port ...without init*/
	}
	
	return ret;
}

/*****************************************************************************************************************************************************/
/*		Test Scinarios
1. DIO_Toggle_1		init with valid configuration ....Valid Port
2. DIO_Toggle_2		init with valid configuration ....InValid Port
3. DIO_Toggle_3		Valid Port ...without init
 */
/*****************************************************************************************************************************************************/
uint8_t test_Scinarios_Toggle(uint8_t test_Case_Num){
	uint8_t ret=0;
	switch (test_Case_Num) {
	case 1:
DIO_is_init();	
	printf("PORTA_DATA=%#X\n",PORTA_DATA);
	ret=DIO_Toggle(GPIOA,BIT5);
		printf("PORTA_DATA=%#X\n",PORTA_DATA);
		break;
		/*Valid Port*/
	case 2:
		DIO_is_init();
		ret=DIO_Toggle(100,BIT6);
		break;
		/*InValid Port*/
	case 3:
		DIO_deinit();
		ret=DIO_Toggle(GPIOC,BIT0);
		break;
		/*Valid Port ...without init*/
	}
	
	return ret;		
}