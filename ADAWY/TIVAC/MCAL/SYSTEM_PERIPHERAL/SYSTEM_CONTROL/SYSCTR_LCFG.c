/*
 * SYSCTR_LCFG.c
 *
 * Created: 4/6/2020 8:18:23 PM
 *  Author: Khaled
 */ 


#include "SYSCTR_LCFG.h"



#define GPIO_RUN_NODE_CLOCK_GATE            0x608
#define GPIO_PORTA                          0
#define GPIO_PORTB                          1
#define GPIO_PORTC                          2
#define GPIO_PORTD                          3
#define GPIO_PORTE                          4
#define GPIO_PORTF                          5



SYSCL_Type garrstr_SYSCTR_Cfg[NUMBER_OF_PERIPHERALS];