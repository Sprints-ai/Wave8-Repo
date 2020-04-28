#include "Nvic_lcfg.h"

NVIC_CfgType NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS]=
{/*IntNum				Group_Priority			SubGroup_Priority */
	{NVIC_INT0_GPIOA,			2,						0					},
	{NVIC_INT1_GPIOB,			1,						2					},
	{NVIC_INT2_GPIOC,			0,						1					}
};
