/*
 * testing.c
 *
 * Created: 2020-03-26 11:05:40 AM
 *  Author: EbrahimOseif
 */ 


#include "testing.h"




/* Test Data preparation */
			
			/* MOTORS  DATA */
				
	uint8_t CHANNEL_Valid_Data[2] = { 0, 1, 2 };
	
	uint8_t CHANNEL_IN_Valid_Data[2] = { -1, 3};

	uint8_t EDGE_Valid_Data[3] = { ICU_RISE_TO_RISE, ICU_RISE_TO_FALL, ICU_FALE_TO_RISE};
	
	sint8_t EDGE_IN_Valid_Data[2] = { -1, 3};
	
	/* testing API IMPLEMENTATION */

    


ERROR_STATUS Testing_Icu_Init(Icu_cfg_s * Icu_Cfg){
	
	return Icu_Init(Icu_cfg_s * Icu_Cfg);
}

ERROR_STATUS Testing_Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint16_t* Icu_Time){
	
	return Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint16_t* Icu_Time);
}


