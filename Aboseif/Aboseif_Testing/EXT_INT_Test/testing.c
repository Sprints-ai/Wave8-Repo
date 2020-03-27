/*
 * testing.c
 *
 * Created: 2020-03-26 11:05:40 AM
 *  Author: EbrahimOseif
 */ 


#include "testing.h"



/* Test Data preparation */
			
			/* EXT INT  DATA */
				
	uint8_t EXT_INT_Valid_Data[3] = {0, 1, 2};
	
	sint8_t EXT_INT_IN_Valid_Data[2] = {-1, 3};

	
	/* testing API IMPLEMENTATION */


	ERROR_STATUS Testing_EXT_INT_SetEdge(uint8_t EXT_INT_EDGE){
		return EXT_INT_SetEdge( EXT_INT_EDGE);
	}


    
    ERROR_STATUS Testing_EXT_INT_Enable(uint8_t EXT_INT_CH){
    	
    	return EXT_INT_Enable( EXT_INT_CH);
    }
    
    ERROR_STATUS Testing_EXT_INT_Disable (uint8_t EXT_INT_CH){
    	
    		return EXT_INT_Disable( EXT_INT_CH);
    
    }
    
    ERROR_STATUS Testing_EXT_INT_IsTriggered (uint8_t EXT_INT_CH, uint8_t* state){
    	
    	return EXT_INT_isTriggered( EXT_INT_CH, state);
    }
    