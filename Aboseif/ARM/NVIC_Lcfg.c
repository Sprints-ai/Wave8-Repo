/*
 * NVIC_Lcfg.c
 *
 * Created: 2020-04-03 12:20:42 AM
 *  Author: EbrahimOseif
 */
 
 /**************************************************/
/*              includes                           */
/**************************************************/

 #include "NVIC_lCfg.h"

/**************************************************/
/*              global vars                       */
/**************************************************/

NVIC_CfgType NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS] =

{       /*IntNum				Group_Priority			SubGroup_Priority */
	{NVIC_INT0_GPIOA,			2,						0					},
	{NVIC_INT1_GPIOB,			1,						2					},
	{NVIC_INT5_UART0,			0,						1					}
};