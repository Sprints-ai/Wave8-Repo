/*
 * NVIC_Cfg.c
 *
 * Created: 4/7/2020 10:15 AM
 *  Author: Ema
 */

#include"NVIC_Cfg.h"
#include"NVIC_Types.h"


NVIC_CfgType NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS]
{/*IntNum				Group_Priority			SubGroup_Priority */
	{NVIC_INT0,			2,						0					},
	{NVIC_INT1,			1,						2					},
	{NVIC_INT5,			0,						1					}
};
