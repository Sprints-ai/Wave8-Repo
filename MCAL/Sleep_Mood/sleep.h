/*
 * sleep.h
 *
 * Created: 09/03/2020 07:10:42 م
 *  Author: TOSHIBA
 */ 


#ifndef SLEEP_H_
#define SLEEP_H_
#include "../../Infrastructure/registers.h"
#include "../../Infrastructure/std_types.h"

// sleep mode //
#define IDLE    (0x00)

u8_ERROR_STATUS_t Sleep_Mode(uint8_t u8_SleepMode);
u8_ERROR_STATUS_t EN_Sleep(void);
u8_ERROR_STATUS_t DIS_EN_Sleep(void);







#endif /* SLEEP_H_ */