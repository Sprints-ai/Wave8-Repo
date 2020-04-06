/*Author : A7med Salama
*/
#include "NVIC_lcfg.h"


NVIC_CfgType NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS] =
{ /*IntNum				Group_Priority			SubGroup_Priority */
	{1,			2,						0					},
	{2,			1,						2					},
	{3,			0,						1					}
};
