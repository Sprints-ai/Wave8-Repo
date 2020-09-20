/*
 * stubFunctions.c
 *
 * Created: 3/13/2020 12:08:44 PM
 *  Author: mahmo
 */ 

#ifdef GCC

#include "stubFunction.h"

uint8_t gu8_Timer_Init_fun_status;
uint8_t gu8_Timer_Start_fun_status;
uint8_t gu8_Timer_DeInit_status;
uint8_t gu8_testCaseNumber;

ERROR_STATUS    Timer_Init(Timer_cfg_s* Timer_cfg)
{
	return gu8_Timer_Init_fun_status;
}
ERROR_STATUS	Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count)
{
	return gu8_Timer_Start_fun_status;
}
ERROR_STATUS	Timer_DeInit(uint8_t timer_Ch)
{
	return gu8_Timer_DeInit_status;
}

/*
`SPI_getData'
`SPI_sendData'
`Uart_Init'
`SPI_init'
`spi_enable'
`SPI_init'
`spi_enable'
`SPI_sendData'
`SPI_sendData'*/

#endif