/*author : A7md Salama
*/

#ifndef NVIC_LCFG_H
#define NVIC_LCFG_H

#include "NVIC_Types.h"

/*enter the number of interrupts you want to use here*/
#define NUM_OF_ACTIVATED_INTERRUPTS							3

extern NVIC_CfgType NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS];

#endif
