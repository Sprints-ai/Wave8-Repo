#ifndef __NVIC_LCFG_H__
#define __NVIC_LCFG_H__
#include "../../Services/includes/std_types.h"
#include "NVIC_types.h"

/**************************************************/
/*              Defines                           */
/**************************************************/

#define NUM_OF_ACTIVATED_INTERRUPTS        3
#define APINT_VECTKEY                      0X05FA0000
#define APINT_PRIGROUP                     0X00000500





extern NVIC_CfgType NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS];

#endif
