/*
 * systick.c
 *
 *      Author: Abdallah Heidar
 */

#include "std_types.h"
#include "systick.h"

static void (*gfptr)(void) = NULL;

void SYSTICK_Init(uint32_t au32_msCounts)
{
	SYSTICK_REG->SYSTICK_CURRENT = 0;
    SYSTICK_REG->SYSTICK_RELOAD = SYSTICK_CLK_KHZ * au32_msCounts;
    SYSTICK_REG->SYSTICK_CTRL = ( SYSTICK_ENABLE | SYSTICK_ENABLE_INT | SYSTICK_CLK_SRC_SYS);
}

void SYSTICK_setCallBack(void (*CBK_func)(void))
{
    gfptr = CBK_func;
}

void SYSTICK_INT_Handler(void)
{
    if(gfptr == NULL)
    {
    }
    else
    {
        gfptr();
    }  
}