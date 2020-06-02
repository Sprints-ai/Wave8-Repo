/*
 * gpiolcfg.h
 *
 *      Author: Abdallah Heidar
 */

#ifndef GPIOLCFG_H
#define GPIOLCFG_H

#include "PerRegs.h"

#define PINS_NUM 			2

#define IO_INPUT			(0)
#define IO_OUTPUT 			(1)
#define IO_AF 				(2)
#define IO_ANALOG 			(3)

#define PUSH_PULL 			(0)
#define OPEN_DRAIN 			(1)

#define LOW_SPEED 			(0)
#define MEDIUM_SPEED 		(1)
#define HIGH_SPEED 			(2)
#define VERY_HIGH_SPEED 	(3)

#define NO_PULL 			(0)
#define PULL_UP 			(1)
#define PULL_DOWN 			(2)

#define AF0 				(0)
#define AF1 				(1)
#define AF2 				(2)
#define AF3 				(3)
#define AF4 				(4)
#define AF5 				(5)
#define AF6 				(6)
#define AF7 				(7)
#define AF8 				(8)
#define AF9 				(9)
#define AF10 				(10)
#define AF11 				(11)
#define AF12 				(12)
#define AF13 				(13)
#define AF14 				(14)
#define AF15 				(15)

#define GPIOA_CLK 			(1)
#define GPIOB_CLK 			(2)
#define GPIOC_CLK 			(4)
#define GPIOD_CLK 			(8)
#define GPIOE_CLK 			(16)
#define GPIOF_CLK 			(32)
#define GPIOG_CLK 			(64)
#define GPIOH_CLK 			(128)

typedef enum{
    pin_0,
    pin_1,
    pin_2,
    pin_3,
    pin_4,
    pin_5,
    pin_6,
    pin_7,
    pin_8,
    pin_9,
    pin_10,
    pin_11,
    pin_12,
    pin_13,
    pin_14,
    pin_15
}IO_pins;

typedef struct{
	uint8_t GPIO_CLK;
    GPIO_PTR GPIO_Used;
    uint8_t GPIO_pin;
    uint8_t GPIO_Speed;
    uint8_t GPIO_Mode;
    uint8_t GPIO_AF;
    uint8_t GPIO_pullDirection;
    uint8_t GPIO_OD_PP;
}str_pinConfig_t;


extern str_pinConfig_t arr_pinCfg[PINS_NUM];

#endif

