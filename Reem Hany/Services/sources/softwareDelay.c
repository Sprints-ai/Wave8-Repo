/*
 * softwaredelay.c
 *
 * Created: 1/20/2020 5:04:26 PM
 *  Author: Hazem
 */ 

#include "../includes/softwareDelay.h"

/* this is the implementation of software delay function*/

void softwareDelayMs(uint32_t u32_delay_in_ms){
	
	for (uint16_t counter=0;counter<u32_delay_in_ms;counter++){
		for(uint16_t internalcounter=0;internalcounter<1000;internalcounter++){
				
		}		
	}
}


void softwareDelayUS(uint32_t u32_delay_in_US){
	
	for (uint16_t counter=0;counter<u32_delay_in_US;counter++){
		for(uint16_t internalcounter=0;internalcounter<40;internalcounter++){
			
		}
	}
}
