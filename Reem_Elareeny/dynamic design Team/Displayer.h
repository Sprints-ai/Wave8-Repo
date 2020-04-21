/*
 * Displayer.h
 *
 * Created: 3/30/2020 10:56:26 AM
 *  Author: Reem el-Areeny
 */ 


#ifndef DISPLAYER_H_
#define DISPLAYER_H_

#include "../ECUAL/LCD.h"
#include "Displayer_config.h"

extern ERROR_STATUS Displayer_init();
extern ERROR_STATUS Displayer_write_digit(uint8_t u8_oneDigitVaue);
extern ERROR_STATUS Displayer_write_two_digit();
extern ERROR_STATUS Displayer_write_string();
extern void displayer_clear();

#endif /* DISPLAYER_H_ */