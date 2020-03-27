/*
 * testing.h
 *
 * Created: 2020-03-26 11:05:40 AM
 *  Author: EbrahimOseif
 */

#include "DIO.h"


	/* testing API PROTOTYPES*/


ERROR_STATUS Testing_DIO_init (DIO_Cfg_s *DIO_info);

ERROR_STATUS Testing_DIO_Write(uint8_t GPIO, uint8_t pins, uint8_t value);

ERROR_STATUS Testing_DIO_Read (uint8_t GPIO, uint8_t pins, uint8_t *data);

ERROR_STATUS Testing_DIO_Toggle (uint8_t GPIO, uint8_t pins);
