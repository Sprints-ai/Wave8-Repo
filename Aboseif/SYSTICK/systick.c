/*
 * systick.c
 *
 * Created: 2020-04-03 12:20:42 AM
 *  Author: EbrahimOseif
 */


#include "std_types.h"
#include "systick.h"


/******************************************************************/
/*					global  variables	                		  */
/******************************************************************/

/*Global pointer to function used in call back operation*/
static void (*gfptr)(void) = NULL;

/******************************************************************/
/*					 functions' definitions						  */
/******************************************************************/

void SYSTICK_init(uint32_t au32_Ms_Counts)
{
	SYSTICK_REG->SYSTICK_CURRENT = 0;
	
    SYSTICK_REG->SYSTICK_RELOAD = SYSTICK_CLK_KHZ * au32_Ms_Counts;

    SYSTICK_REG->SYSTICK_CTRL = ( SYSTICK_ENABLE | SYSTICK_ENABLE_INT | SYSTICK_CLK_SRC_SYS);
}

void SYSTICK_setCallBack(void (*CBK_func)(void))
{
    gfptr = CBK_func;
}

void SYSTICK_INT_Handler(void)
{
    /*check that pointer contains a value not NULL*/
    if(gfptr == NULL)
    {
    }
    else
    {
        gfptr();
    }  
}