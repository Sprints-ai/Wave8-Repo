/*
 * SysCtr_Lcfg.c
 *
 * Created: 4/9/2020 2:50:46 AM
 *  Author: A_ayman
 */ 

/*
*** Inclusions
*/
#include "SysCtr_Lcfg.h"


/*
*** primitive Data Types
*/

uint8_t  Sys_CLK_CfgArr[NUM_OF_ENABLED_PRIPHERALS_GATES] = { ENABLE_I2C1_SYSCTL_GATE	, ENABLE_GPIOB_SYSCTL_GATE,ENABLE_TIMER0_SYSCTL_GATE,ENABLE_GPIOC_SYSCTL_GATE,ENABLE_TIMER2_SYSCTL_GATE};
uint32_t gu32_Clock_Value  =  SYSCTL_16_67MHZ;