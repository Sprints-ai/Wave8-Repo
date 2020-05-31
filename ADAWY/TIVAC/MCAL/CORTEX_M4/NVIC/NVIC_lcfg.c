/*
 * NVIC_lcfg.c
 *
 * Created: 4/3/2020 10:51:38 AM
 *  Author: Khaled
 */ 

#include "NVIC_lcfg.h"

NVIC_CfgType NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS]=
{/*     IntNum			   Group_Priority	    SubGroup_Priority */
{NVIC_INT_GPIO_PORT_A,			3,						0					},
{NVIC_INT_GPIO_PORT_E,	        4,						0					},
{NVIC_INT_GPIO_PORT_F,	        5,						0					}
};
