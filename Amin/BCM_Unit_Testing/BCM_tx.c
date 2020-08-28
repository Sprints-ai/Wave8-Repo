/*
* BCM.c
*
* Created: 3/2/2020 1:17:31 AM
*  Author: Abdallah & Amin
*/

#include "BCM_tx.h"
ERROR_STATUS BCM_Send(uint8_t* ptr_Buffer, uint16_t u16_Size, uint8_t u8_Channel)
{
	ERROR_STATUS E_STAT = E_NOK;
	if (ptr_Buffer!=NULL)
	{
	    switch(u8_Channel){
    case UART_CH:
        return E_OK;
        break;
     case SPI_CH:
        return E_OK;
        break;
     case I2C_CH:
     return E_OK;
     break;

     default:
        return ERROR_INVALID_PARAMETER;
        break;
	}}
	return ERROR_NULL_POINTER;
}
