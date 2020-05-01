/*
 * NVIC_LCFG.h
 *
 * Created: 4/3/2020 6:55:40 PM
 * Author : A_ayman
 */ 

/*
*** INCLUSIONS 
*/
#include "NVIC_Types.h"

/*
*** CONSTANTS
*/

#define bxxx_ 0
#define bxx_y 1
#define bx_yy 2
#define b_yyy 3

/* CONFIGURABLE the value could be changed by user*/

#define NUM_OF_ACTIVATED_INTERRUPTS		3
#define APINT_Combination              bxxx_

/*
*** Function Declaration
*/
extern strNVIC_Cfg_t NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS];
