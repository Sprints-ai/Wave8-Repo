/*
 * testing.h
 *
 * Created: 2020-03-26 11:05:40 AM
 *  Author: EbrahimOseif
 */ 

#include "US.h"


	/* testing API PROTOTYPES*/


ERROR_STATUS Testing_Us_Init(void);

ERROR_STATUS Testing_Us_Trigger(void);

ERROR_STATUS Testing_Us_GetDistance(uint8_t *Distance);
