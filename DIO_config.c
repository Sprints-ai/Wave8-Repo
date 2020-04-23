/*
 * DIO_config.c
 *
 * Created: 17/02/2020 03:53:11 م
 *  Author: mo
 */ 
#include "registers.h"
#include "DIO.h" 
DIO_Cfg_s Dio_configurationA= {
	GPIOA,
FULL_PORT,
	OUTPUT
};

DIO_Cfg_s Dio_configurationB= {
	GPIOB,
	BIT2,
	INPUT
};

DIO_Cfg_s Dio_configurationC= {
	GPIOC,
	BIT4,
	INPUT
};

DIO_Cfg_s Dio_configurationD= {
	GPIOD,
	BIT4|BIT3|BIT2,
	OUTPUT
};
