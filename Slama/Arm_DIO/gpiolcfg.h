/*Author : A7md Salama
*/

#ifndef GPIOLCFG_H
#define GPIOLCFG_H


#include "PerRegs.h"
//#include "stm32f4xx.h"
#define PINS_NUM 2

/*Define input Parameters*/
#define IO_INPUT (0)
#define IO_OUTPUT (1)
#define IO_AF (2)
#define IO_ANALOG (3)

/*Output Type Defines*/
#define PUSH_PULL (0)
#define OPEN_DRAIN (1)

/*Speed Defines*/
#define LOW_SPEED (0)
#define MEDIUM_SPEED (1)
#define HIGH_SPEED (2)
#define VERY_HIGH_SPEED (3)

/*PuLL Up/Down*/
#define NO_PULL (0)
#define PULL_UP (1)
#define PULL_DOWN (2)

/*Alternate Function Defines*/
#define AF_0 (0)
#define AF_1 (1)
#define AF_2 (2)
#define AF_3 (3)
#define AF_4 (4)
#define AF_5 (5)
#define AF_6 (6)
#define AF_7 (7)
#define AF_8 (8)
#define AF_9 (9)
#define AF_10 (10)
#define AF_11 (11)
#define AF_12 (12)
#define AF_13 (13)
#define AF_14 (14)
#define AF_15 (15)

/*GPIO_Clock Defines*/
#define GPIOA_CLOCK (1)
#define GPIOB_CLOCK (2)
#define GPIOC_CLOCK (4)
#define GPIOD_CLOCK (8)
#define GPIOE_CLOCK (16)
#define GPIOF_CLOCK (32)
#define GPIOG_CLOCK (64)
#define GPIOH_CLOCK (128)


/*Enum of pins*/
typedef enum{
    Pin0,
    Pin1,
    Pin2,
    Pin3,
    Pin4,
    Pin5,
    Pin6,
    Pin7,
    Pin8,
    Pin9,
    Pin10,
    Pin11,
    Pin12,
    Pin13,
    Pin14,
    Pin15
}IO_Pins;

typedef struct{

	uint8_t GPIO_CLOCK;
    GPIO_PTR GPIO_USED;
    //uint8_t GPIO_CK;
    uint8_t Gpio_Pin;
    uint8_t Gpio_Speed;
    uint8_t Gpio_Mode;
    uint8_t Gpio_Af;
    uint8_t Gpio_PullDirection;
    uint8_t Gpio_OpenD_PushPull;
}str_PinConfig_t;


extern str_PinConfig_t arr_PinCfg[PINS_NUM];

#endif

