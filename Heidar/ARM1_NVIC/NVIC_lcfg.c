/*
 * NVIC_lcfg.c
 *
 *      Author: Abdallah Heidar
 */

#include "NVIC_lcfg.h"

NVIC_CfgType NVIC_cfgArr[NUM_OF_ACTIVATED_INTERRUPTS] = 
{/*IntNum				Group_Priority			SubGroup_Priority */
	{GPIOA_IRQn,			2,						0					},
	{GPIOB_IRQn,			1,						1					},
	{GPIOF_IRQn,			2,						1					},
	{UART0_IRQn,			0,						1					},
	{ADC0SS3_IRQn,			0,						1					},
};
