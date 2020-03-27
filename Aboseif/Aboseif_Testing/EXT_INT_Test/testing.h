/*
 * testing.h
 *
 * Created: 2020-03-26 11:05:40 AM
 *  Author: EbrahimOseif
 */ 

#include "EXT_Interrupts.h"


	/* testing API PROTOTYPES*/


ERROR_STATUS Testing_EXT_INT_SetEdge(uint8_t EXT_INT_EDGE);

ERROR_STATUS Testing_EXT_INT_Enable(uint8_t EXT_INT_CH);

ERROR_STATUS Testing_EXT_INT_Disable (uint8_t EXT_INT_CH);

ERROR_STATUS Testing_EXT_INT_IsTriggered (uint8_t EXT_INT_CH, uint8_t* state);
