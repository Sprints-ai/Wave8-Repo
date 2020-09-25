/*
 ============================================================================
 Name        : CPU.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


#include "CPU.h"



void CPU_Sleep(uint8_t Sleep_Mood)
{
	switch(Sleep_Mood)
	{
	case IDLE_MODE:
		MCUCR &= ~(1<<SM0) & ~(1<<SM1) & ~(1<<SM2);
		MCUCR |= (1<<SE);
		__asm__ __volatile__ ( "sleep" "\n\t" :: );
		break;

	case ADC_NOISE_REDUCTION_MODE:
		MCUCR &= ~(1<<SM1) & ~(1<<SM2);
		MCUCR |= (1<<SE) | (1<<SM0);
		break;

	case POWER_DOWN_MODE:
		MCUCR &= ~(1<<SM0) & ~(1<<SM2);
		MCUCR |= (1<<SE) | (1<<SM1);
		break;

	case POWER_SAVE_MODE:
		MCUCR &= ~(1<<SM2);
		MCUCR |= MCUCR |= (1<<SE) | (1<<SM0) |(1<<SM1);
		break;

	case STANDBY_MODE:
		MCUCR &= ~(1<<SM0);
		MCUCR |= (1<<SE) | (1<<SM1) | (1<<SM2);
		break;

	case EXTENDED_STANDBY_MODE:
		MCUCR |= (1<<SE) | (1<<SM0) | (1<<SM1) | (1<<SM2);
		break;

	}
}




void CPU_WakeUp(uint8_t Sleep_Mood)
{
	MCUCR &= ~(1<<SE) & ~(1<<SM0) & ~(1<<SM1) & ~(1<<SM2);
}
