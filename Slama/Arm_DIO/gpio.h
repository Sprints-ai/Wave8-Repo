/*Author : A7md Slama
*/

#ifndef GPIO_H
#define GPIO_H

/*Includes*/
#include "Error_table.h"
#include "std_types.h"

/*Defines*/
/*Ports Defines*/
#define GPIOA_PORT (0)
#define GPIOB_PORT (1)
#define GPIOC_PORT (2)
#define GPIOD_PORT (3)
#define GPIOE_PORT (4)
#define GPIOH_PORT (5)

/*Port Value*/
#define PORT_HIGH (0xFFFF)
#define PORT_LOW  (0x0000)

/*Pins Defines*/
#define PIN_0 (0)
#define PIN_1 (2)
#define PIN_2 (4)
#define PIN_3 (8)
#define PIN_4 (16)
#define PIN_5 (32)
#define PIN_6 (64)
#define PIN_7 (128)
#define PIN_8 (256)
#define PIN_9 (512)
#define PIN_10 (1024)
#define PIN_11 (2048)
#define PIN_12 (4096)
#define PIN_13 (8192)
#define PIN_14 (16384)
#define PIN_15 (32768)

/*Init Gpio
 * Description : Function to init  all gpio needed once
 * Input : None but getting an external array from gpiolcfg.h
 * Output : Error if found
 */
ERROR_STATUS  mygpio_init(void);

/*Dio_Read
 * Description : Function to read the input values at pins
 * Input : Port and Pins to read from , output Pointer to value
 * Output : Error if found
 */
ERROR_STATUS gpio_Write(uint8_t Port , uint16_t Pins, uint16_t Val);
#endif

