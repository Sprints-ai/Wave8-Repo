/*
 * Sleep.c
 *
 * Created: 3/9/2020 10:05:19 AM
 *  Author: Ehab
 */ 

#include "Sleep.h"

ERROR_STATUS Sleep_Mode()
{
	ERROR_STATUS ERR = E_OK;
	
	MCUCR |= 0x80;
	
	__asm__ __volatile__ ( "sleep" "\n\t" :: );
	
	return ERR;
}