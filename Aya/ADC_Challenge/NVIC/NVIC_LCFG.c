/*
 * NVIC_LCFG.c
 *
 * Created: 4/3/2020 6:55:40 PM
 * Author : A_ayman
 */ 

/*
*** INCLUSIONS 
*/
#include "NVIC_LCFG.h"

/*
***Non Primitive types
*/

/*structures*/

strNVIC_Cfg_t NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS]=
{   /*IntNu 	Group_Priority 		SubGroup_Priority */
	{NVIC_INT_GPIO_PORT_A  ,		    	2,						0},
	{NVIC_INT_GPIO_PORT_B  ,			    1,						0},
	{NVIC_INT_GPIO_PORT_C  ,			    0,						0}
};

