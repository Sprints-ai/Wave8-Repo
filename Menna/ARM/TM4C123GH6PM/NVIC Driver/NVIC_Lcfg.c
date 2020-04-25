/**************************************************************************************/
/*					NVIC_lcfg.c														  */
/**************************************************************************************/

#include "NVIC_Lcfg.h"


NVIC_CfgType NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS] = 
{/*IntNum				Group_Priority			SubGroup_Priority */
	{NVIC_INT4,			2,						0					},
	{NVIC_INT1,			1,						1					},
	{NVIC_INT3,			1,						1					}
};

