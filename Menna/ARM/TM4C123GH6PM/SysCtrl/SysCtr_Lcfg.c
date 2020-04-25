/*****************************************************************************/
/*					SysCtr_Lcfg.c												 */	
/*****************************************************************************/

#include "SysCtr_Lcfg.h"
#include "SysCtr_Types.h"

ClkFreq_type ClkFreq = FREQ_40MHz ;

#define CLOCK_FREQ 40

/* Clock Gates */

int CfgArr[NUM_OF_PRIPHERALS] =
{
	/*GpioA  */   ENABLE, 
	/*GpioB  */   DISABLE,
	/*GpioC  */   ENABLE,
	/*GpioD  */   DISABLE,
	/*GpioE  */   ENABLE,
	/*GpioF  */   ENABLE,
	/*TIMER0 */   DISABLE,
	/*TIMER1 */   DISABLE,
	/*TIMER2 */   DISABLE,
	/*TIMER3 */   DISABLE,
	/*TIMER4 */   ENABLE
};

