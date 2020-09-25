/*
 ============================================================================
 Name        : CPU.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef CPU_H_
#define CPU_H_

#include "registers.h"


#define IDLE_MODE 0
#define ADC_NOISE_REDUCTION_MODE 1
#define POWER_DOWN_MODE 2
#define POWER_SAVE_MODE 3
#define STANDBY_MODE 4
#define EXTENDED_STANDBY_MODE 5


void CPU_Sleep(uint8_t Sleep_Mood);
void CPU_WakeUp(uint8_t Sleep_Mood);


#endif /* CPU_H_ */
