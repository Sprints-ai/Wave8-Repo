#include "std_types.h"
#include "SystemTick.h"

/******************************************************************/
/*					General macros								  */
/******************************************************************/

#define STCK_CLK_KHZ    (16000)
#define STCK_ENABLE_ENABLEINT_SYSCLK   (7)

/******************************************************************/
/*					SystemTick variables	            		  */
/******************************************************************/

/*Global pointer to function used in call back operation*/
static void (*gfptr)(void) = NULL;

/******************************************************************/
/*					SystemTick functions' definitions			  */
/******************************************************************/

void STICK_init(uint32_t au32_tickTimeMs)
{
    /*Load the value that timer will  begin its count from*/
    STCK_REG -> STRELOAD = STCK_CLK_KHZ * au32_tickTimeMs;
    
    /*Enable STCK peripheral with interrupt and its count clk is the system clk*/
    STCK_REG -> STCTRL = STCK_ENABLE_ENABLEINT_SYSCLK;

    return;
}

void STICK_setCallBack(void (*pcallback)(void))
{
    /*Passing application function address to the global pointer*/
    gfptr = pcallback;
    
    return;
}

/*SysTick handler for interrupt request on counter underflow*/
void SysTick_Handler(void)
{
    /*Validate that pointer contains a value not NULL*/
    if(gfptr == NULL)
    {
        /*DO nothing*/
    }
    else
    {
        /*Call back function execution*/
        gfptr();
    }  
}
