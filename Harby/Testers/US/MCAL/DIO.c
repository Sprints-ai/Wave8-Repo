/*
 * DIO.c
 *
 *  Created on: Mar 26, 2020
 *      Author: Youssef Harby
 */

#include "DIO.h"

ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info)
{
	return DIO_E_OK;
}

ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value)
{
	return DIO_E_OK;
}

ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t* data)
{
	return DIO_E_OK;
}

ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins)
{
	return DIO_E_OK;
}
