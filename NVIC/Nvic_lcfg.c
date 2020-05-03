
/**************************************************************************************/
/*					NVIC_lcfg.c														  */
/**************************************************************************************/
#include "NVIC_Types.h"

#include "NVIC_cfg.h"




  NVIC_CfgType NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS]=

{  /*  IntNum				Group_Priority			SubGroup_Priority */
	{NVIC_GPIO_PORT_A,		2,						0					},
	{NVIC_GPIO_PORT_B,		1,						1				},
	{NVIC_GPIO_PORT_C,	    0,						1				},
	{NVIC_16_32_BIT_TIMER_2A,	    3,						1					}
};











