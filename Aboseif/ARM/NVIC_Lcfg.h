/*
 * NVIC_Lcfg.h
 *
 * Created: 2020-04-03 12:20:42 AM
 *  Author: EbrahimOseif
 */ 

#ifndef __NVIC_LCFG_H__
#define __NVIC_LCFG_H__

/**************************************************/
/*              includes                           */
/**************************************************/

#include "std_types.h"

/**************************************************/
/*              Defines                           */
/**************************************************/

#define NUM_OF_ACTIVATED_INTERRUPTS        3
#define APINT_VECTKEY                      0X05FA0000
#define APINT_PRIGROUP                     0X00000500

/**************************************************/
/*              TypeDefs                           */
/**************************************************/

typedef uint8_t SubGroup_PriorityType;
typedef uint8_t Group_PriorityType;

typedef enum
{
	NVIC_INT0_GPIOA,
	NVIC_INT1_GPIOB,
	NVIC_INT2_GPIOC,
	NVIC_INT3_GPIOD,
	NVIC_INT4_GPIOE,
	NVIC_INT5_UART0,
	NVIC_INT6_UART1,
	
}IntNumType;


typedef struct
{
	IntNumType IntNum;
	Group_PriorityType Group_Priority;
	SubGroup_PriorityType	SubGroup_Priority;
}NVIC_CfgType;

extern NVIC_CfgType NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS];

#endif