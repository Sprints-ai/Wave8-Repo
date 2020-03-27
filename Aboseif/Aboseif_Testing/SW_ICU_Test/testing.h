/*
 * testing.h
 *
 * Created: 2020-03-26 11:05:40 AM
 *  Author: EbrahimOseif
 */ 

#include "ICU.h"


	/* testing API PROTOTYPES*/


ERROR_STATUS Testing_Icu_Init(Icu_cfg_s * Icu_Cfg);

ERROR_STATUS Testing_Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint16_t* Icu_Time);
