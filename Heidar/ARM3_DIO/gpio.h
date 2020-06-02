/*
 * gpio.c
 *
 *      Author: Abdallah Heidar
 */

#ifndef GPIOH
#define GPIOH

#include "std_types.h"
#include "Error_table.h"
 
#define GPIOA_PORT 		(0)
#define GPIOB_PORT 		(1)
#define GPIOC_PORT 		(2)
#define GPIOD_PORT 		(3)
#define GPIOE_PORT 		(4)
#define GPIOH_PORT 		(5)

#define PORT_HIGH 		(0xFFFF)
#define PORT_LOW  		(0x0000)

#define PIN_0 			(0)
#define PIN_1 			(2)
#define PIN_2 			(4)
#define PIN_3 			(8)
#define PIN_4 			(16)
#define PIN_5 			(32)
#define PIN_6 			(64)
#define PIN_7 			(128)
#define PIN_8 			(256)
#define PIN_9 			(512)
#define PIN_10 			(1024)
#define PIN_11 			(2048)
#define PIN_12 			(4096)
#define PIN_13 			(8192)
#define PIN_14 			(16384)
#define PIN_15 			(32768)

ERROR_STATUS  GPIO_Init(void);

ERROR_STATUS GPIO_Write(uint8_t port , uint16_t pins, uint16_t val);

ERROR_STATUS GPIO_Read(uint8_t port, uint16_t pins, uint16_t *ptrValue);

#endif

