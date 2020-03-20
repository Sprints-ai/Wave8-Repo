/*
 * sleep.c
 *
 * Created: 09/03/2020 07:11:16 م
 *  Author: TOSHIBA
 */ 

/* INCLUDE*/

#include "sleep.h"

/* DEFINE*/

#define SLEEP_EN_BIT  (0x80)
#define SLEEP_DIS_EN_BIT  (0x7F)

/*					FUNCTION IMPLEMENTAION				*/ 

u8_ERROR_STATUS_t Sleep_Mode(uint8_t u8_SleepMode)
{	u8_ERROR_STATUS_t u8_ErroeStatus = E_OK;
	MCUCR |= u8_SleepMode;
	return u8_ErroeStatus;
}
u8_ERROR_STATUS_t EN_Sleep(void)
{
	u8_ERROR_STATUS_t u8_ErroeStatus = E_OK;
	
	MCUCR |= SLEEP_EN_BIT;
	
	/* Assembly code that turn sleep mode */
	
	__asm__ __volatile__( "sleep" "\n\t" :: );

	return u8_ErroeStatus;
}
u8_ERROR_STATUS_t DIS_EN_Sleep(void)
{
	u8_ERROR_STATUS_t u8_ErroeStatus = E_OK;
	MCUCR |= SLEEP_DIS_EN_BIT;
	return u8_ErroeStatus;
}