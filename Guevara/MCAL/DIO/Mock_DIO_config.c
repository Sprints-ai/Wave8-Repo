/*
 * DIO_config.c
 *
 * Created: 17/02/2020 03:53:11 م
 *  Author: mo
 */

#include "Mock_DIO_config.h"
DIO_Cfg_s Dio_configurationA= {
	GPIOA,
FULL_PORT,
	OUTPUT
};

DIO_Cfg_s Dio_configurationB= {
	5,
	BIT2,
	INPUT
};

DIO_Cfg_s Dio_configurationC= {
	GPIOC,
	BIT4,
	2
};

DIO_Cfg_s Dio_configurationD= {
	12,
	BIT4|BIT3|BIT2,
	8
};
