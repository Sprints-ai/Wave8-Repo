/*
 * BCM.c
 *
 * Created: 3/2/2020 1:17:31 AM
 *  Author: Abdallah & Amin
 */


/*Includes*/
#include "BCM_rx.h"

ERROR_STATUS BCM_Init(uint8_t u8_bcm_id)
{
	switch (u8_bcm_id)
	{
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
	}

	return E_NOK;
}
ERROR_STATUS BCM_Receive(uint16_t u16_Size, uint8_t u8_bcm_id)
{

	switch (u8_bcm_id)
	{
		case UART_CH:
		return E_OK;
		break;
		case SPI_CH:
		return E_OK;
		break;
		case I2C_CH:
		/*TO be Handelled */
		return E_OK;
		break;
		default:
        return ERROR_INVALID_PARAMETER;
        break;
	}
	return E_NOK;
}
