/*Author : A7md Salama
*/

#include "gpiolcfg.h"


str_PinConfig_t arr_PinCfg[PINS_NUM] =
{
    {GPIOD_CLOCK , GPIOD , Pin12 , MEDIUM_SPEED , IO_OUTPUT , AF_0 , PULL_UP , PUSH_PULL},
	{GPIOD_CLOCK , GPIOD , Pin13 , MEDIUM_SPEED , IO_OUTPUT , AF_0 , PULL_UP , PUSH_PULL}
};
