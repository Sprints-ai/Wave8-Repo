
#include "DIO_tester.h"
// #include "Errors.h"

void DIO_init_tester(void){
	ERROR_STATUS ERR = E_OK;
	
	/**************DIO_INIT_0**************/
	/*Passing a NULL pointer as the DIO struct.*/

 	ERR = DIO_init (NULL);
	if(ERR == ERROR_DIO_MODULE + ERROR_NULL_POINTER)
	{
		printf("DIO_INIT_0: Passed\n");
	}
	else
	{
		printf("DIO_INIT_0: Failed\n");
	}

	/**************DIO_INIT_1**************/
	/*Passing valid port and Invalid direction.*/
	
	DIO_Cfg_t DIO_1  = {GPIOA,BIT5,0x03 /*any random number other than INPUT/OUTPUT */};
	ERR = DIO_init (&DIO_1);
	if(ERR == ERROR_DIO_MODULE + ERROR_INVALID_DIR)
	{
		printf("DIO_INIT_1: Passed\n");
	}
	else
	{
		printf("DIO_INIT_1: Failed\n");
	}

	/**************DIO_INIT_2**************/
	/*Passing invalid port and valid direction.*/
	
	DIO_Cfg_t DIO_2  = {0x07/*any random number other than GPIOs: A,B,C or D */,BIT5,OUTPUT};
	ERR = DIO_init (&DIO_2);
	if(ERR == ERROR_DIO_MODULE + ERROR_INVALID_PORT)
	{
		printf("DIO_INIT_2: Passed\n");
	}
	else
	{
		printf("DIO_INIT_2: Failed\n");
	}

	/**************DIO_INIT_3**************/
	/*Passing invalid port and invalid direction.*/
		
	DIO_Cfg_t DIO_3  = {0x07,BIT5,0x05}; /*passing random numbers for both port and direction*/
	ERR = DIO_init (&DIO_3);
	if(ERR == ERROR_DIO_MODULE + ERROR_INVALID_DIR)
	{
		printf("DIO_INIT_3: Passed\n");
	}
	else
	{
		printf("DIO_INIT_3: Failed\n");
	}

	/**************DIO_INIT_4**************/
	/*Passing valid port and valid direction (Happy Senario).*/
		
	DIO_Cfg_t DIO_4  = {GPIOA,BIT5,INPUT}; /*passing correct values for both port and direction*/
	ERR = DIO_init (&DIO_4);
	if(ERR == ERROR_DIO_MODULE + E_OK)
	{
		printf("DIO_INIT_4: Passed\n");
	}
	else
	{
		printf("DIO_INIT_4: Failed\n");
	}

	/**************DIO_INIT_5**************/
	/*Init twice with valid configurations. (for the same PORT).*/
	
	DIO_Cfg_t DIO_5  = {GPIOA,BIT5,INPUT}; 
	ERR = DIO_init (&DIO_5);
	if(ERR == ERROR_DIO_MODULE + ERROR_MODULE_ALREADY_INITIALIZED)
	{
		printf("DIO_INIT_5: Passed\n");
	}
	else
	{
		printf("DIO_INIT_5: Failed\n");
	}
		printf("/////////////////////////////////////////////////\n");
}


void DIO_Write_tester(void){
	ERROR_STATUS ERR = E_OK;
	
	/**************DIO_Write_0**************/
	/*Write with valid parameters and without init.*/

	ERR = DIO_Write (0x07/*a random wrong value for port*/, BIT3 | BIT4, HIGH);
	if(ERR == ERROR_DIO_MODULE + ERROR_MODULE_NOT_INITIALIZED)
	{
		printf("DIO_WRITE_0: Passed\n");
	}
	else
	{
		printf("DIO_WRITE_0: Failed\n");
	}

	/**************DIO_Write_1**************/
	/*Init with valid configurations, write with valid port, and invalid value.*/

 	ERR = DIO_Write (GPIOA, BIT3 | BIT4, 0x07 /*a random wrong value for value*/);
	if(ERR == ERROR_DIO_MODULE + ERROR_INVALID_VALUE)
	{
		printf("DIO_WRITE_1: Passed\n");
	}
	else
	{
		printf("DIO_WRITE_1: Failed\n");
	}

	/**************DIO_Write_2**************/
	/*Init with valid configurations, write with valid port, and invalid value.*/

	ERR = DIO_Write (0x07/*a random wrong value for port*/, BIT3 | BIT4, HIGH);
	if(ERR == ERROR_DIO_MODULE + ERROR_INVALID_PORT)
	{
		printf("DIO_WRITE_2: Passed\n");
	}
	else
	{
		printf("DIO_WRITE_2: Failed\n");
	}

	/**************DIO_Write_3**************/
	/*Init with valid configurations, write with invalid port, and invalid value.*/

	ERR = DIO_Write (0x07, BIT3 | BIT4, 0x07);/*random wrong values for port & value*/
	if(ERR == ERROR_DIO_MODULE + ERROR_INVALID_VALUE)
	{
		printf("DIO_WRITE_3: Passed\n");
	}
	else
	{
		printf("DIO_WRITE_3: Failed\n");
	}

	
	/**************DIO_Write_4**************/
	/*Init with valid configurations, write with valid port, and valid value (HIGH/LOW).*/

	ERR = DIO_Write (GPIOB, BIT3 | BIT4, LOW);/*random wrong values for port & value*/
	if(ERR == ERROR_DIO_MODULE + E_OK)
	{
		printf("DIO_WRITE_4: Passed\n");
	}
	else
	{
		printf("DIO_WRITE_4: Failed\n");
	}
		printf("/////////////////////////////////////////////////\n");
}


void DIO_Read_tester(void){
	ERROR_STATUS ERR = E_OK;
	uint8_t data = 0;
	
	/**************DIO_READ_0**************/
	/*Read with valid parameters and without init.*/
	ERR = DIO_Read(GPIOB, BIT3 | BIT4, &data);
	if(ERR == ERROR_DIO_MODULE + ERROR_MODULE_NOT_INITIALIZED)
	{
		printf("DIO_READ_0: Passed\n");
	}
	else
	{
		printf("DIO_READ_0: Failed\n");
	}

	/**************DIO_READ_1**************/
	/*Passing a NULL pointer as data variable.*/
	ERR = DIO_Read(GPIOB, BIT3 | BIT4, NULL);
	if(ERR == ERROR_DIO_MODULE + ERROR_NULL_POINTER)
	{
		printf("DIO_READ_1: Passed\n");
	}
	else
	{
		printf("DIO_READ_1: Failed\n");
	}
	
	/**************DIO_READ_2**************/
	/*ERROR_DIO_MODULE + ERROR_INVALID_PORT*/
	ERR = DIO_Read(0x05/*any random number other than GPIOs: A,B,C or D */, BIT3 | BIT4, &data);
	if(ERR == ERROR_DIO_MODULE + ERROR_INVALID_PORT)
	{
		printf("DIO_READ_2: Passed\n");
	}
	else
	{
		printf("DIO_READ_2: Failed\n");
	}

	/**************DIO_READ_3**************/
	/*Init with valid configurations, read invalid port, and invalid data pointer.*/
	ERR = DIO_Read(GPIOB, BIT3 | BIT4, NULL);
	if(ERR == ERROR_DIO_MODULE + ERROR_NULL_POINTER)
	{
		printf("DIO_READ_3: Passed\n");
	}
	else
	{
		printf("DIO_READ_3: Failed\n");
	}

	/**************DIO_READ_4**************/
	/*Init with valid configurations, read valid port, valid pins in valid pointer.*/
	ERR = DIO_Read(GPIOB, BIT3 | BIT4, &data);
	if(ERR == ERROR_DIO_MODULE + E_OK)
	{
		printf("DIO_READ_4: Passed\n");
	}
	else
	{
		printf("DIO_READ_4: Failed\n");
	}
	printf("/////////////////////////////////////////////////\n");
}

void DIO_Toggle_tester(void)
{
	ERROR_STATUS ERR = E_OK;

	/**************DIO_TOGGLE_0**************/
	/*Toggle with valid parameters and without init.*/
	ERR = DIO_Toggle(GPIOB, BIT3 | BIT4);
	if(ERR == ERROR_DIO_MODULE + ERROR_MODULE_NOT_INITIALIZED)
	{
		printf("DIO_TOGGLE_0: Passed\n");
	}
	else
	{
		printf("DIO_TOGGLE_0: Failed\n");
	}

	/**************DIO_TOGGLE_1**************/
	/*Init with valid configurations, toggle with invalid port.*/
	ERR = DIO_Toggle(0x06, BIT3 | BIT4);
	if(ERR == ERROR_DIO_MODULE + ERROR_INVALID_PORT)
	{
		printf("DIO_TOGGLE_1: Passed\n");
	}
	else
	{
		printf("DIO_TOGGLE_1: Failed\n");
	}

	/**************DIO_TOGGLE_2**************/
	/*Init with valid configurations, toggle with Valid port.*/
	ERR = DIO_Toggle(GPIOB, BIT3 | BIT4);
	if(ERR == ERROR_DIO_MODULE + E_OK)
	{
		printf("DIO_TOGGLE_2: Passed\n");
	}
	else
	{
		printf("DIO_TOGGLE_2: Failed\n");
	}
	printf("/////////////////////////////////////////////////\n");
}

int main(void){
	DIO_init_tester();
	DIO_Write_tester();
	DIO_Read_tester();
	DIO_Toggle_tester();
	return 0;
}
