/*
 * softwareDelay.c
 *
 * Created: 18/01/2020 12:25:22 ص
 *  Author: TOSHIBA
 */ 
#include "softwareDelay.h"
void softwareDelayMs(uint32_t u32_delay_in_ms){
	uint32_t  s=0;
	for(;u32_delay_in_ms;u32_delay_in_ms--){
		        s=0;
		for (;s<2285; ){
			s++;
		}
	}
	
}