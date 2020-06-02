/*
 * gpiolcfg.c
 *
 *      Author: Abdallah Heidar
 */

#include "gpiolcfg.h"

str_PinConfig_t arr_PinCfg[PINS_NUM] =
{
    {GPIOD_CLK , GPIOD , Pin_12 , MEDIUM_SPEED , IO_OUTPUT , AF_0 , PULL_UP , PUSH_PULL},
	{GPIOD_CLK , GPIOD , Pin_13 , MEDIUM_SPEED , IO_OUTPUT , AF_0 , PULL_UP , PUSH_PULL}
};
