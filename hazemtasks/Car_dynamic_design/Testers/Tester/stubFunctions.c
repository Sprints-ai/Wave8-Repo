/*
 * stubFunctions.c
 *
 * Created: 3/13/2020 12:08:44 PM
 *  Author: mahmo
 */ 

#ifdef GCC

#include "stubFunction.h"

sint16_t gu8_Timer_Init_fun_status;
sint16_t gu8_Timer_Start_fun_status;
sint16_t gu8_Timer_DeInit_status;
sint16_t gu8_testCaseNumber;
sint16_t gu8_SPI_returnStatus;
sint16_t gu8_UART_returnStatus;

uint8_t gu8_steeringInitState;
uint8_t gu8_steeringSteerCarState;
uint8_t gu8_usInitState;
uint8_t gu8_UsTriggerState;
uint8_t gu8_usGetDistanceState;

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

/*--------------------------------SPI------------------------------------------*/

ERROR_STATUS	SPI_init(gstrSPI_spi_satus_t * spi_status)
{
	return gu8_SPI_returnStatus;
}

ERROR_STATUS	spi_enable()
{
	return gu8_SPI_returnStatus;
}

ERROR_STATUS	SPI_sendData(uint8_t value)
{
	return gu8_SPI_returnStatus;
}
ERROR_STATUS	SPI_getData(uint8_t* value)
{
	return gu8_SPI_returnStatus;
}

/*-------------------------------UART--------------------------------------*/
void Uart_Init(gstr_uart_cfg_t* uart_cfg)
{
	//return gu8_UART_returnStatus;
}
/*-------------------------------STEERING--------------------------------------*/




ERROR_STATUS Steering_Init(void)
{
	return gu8_steeringInitState;
	
}

ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed)
{
	return gu8_steeringSteerCarState;
}

/*-------------------------------ULTRAsONIC--------------------------------------*/
ERROR_STATUS Us_Init(void)
{
	return gu8_usInitState;	
}

ERROR_STATUS Us_Trigger(void)
{
	return gu8_UsTriggerState;
}
ERROR_STATUS Us_GetDistance(uint64_t *Distance)
{
	return gu8_usGetDistanceState;
}
#endif