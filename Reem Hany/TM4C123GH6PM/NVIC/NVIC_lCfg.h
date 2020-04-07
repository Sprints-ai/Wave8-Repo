#ifndef __NVIC_LCFG_H__
#define __NVIC_LCFG_H__
#include "../../Services/includes/std_types.h"

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
	NVIC_INT0_GPIOA=0,
	NVIC_INT1_GPIOB,
	NVIC_INT2_GPIOC,
	NVIC_INT3_GPIOD,
	NVIC_INT4_GPIOE,
	NVIC_INT5_UART0,
	NVIC_INT6_UART1,
	NVIC_INT7_SSI0,
	NVIC_INT8_I2C0,
	NVIC_INT9_PWM0_FAULT,
	NVIC_INT10_PWM0_GENRATOR0,
	NVIC_INT11_PWM0_GENRATOR1,
	NVIC_INT12_PWM0_GENRATOR2,
	NVIC_INT13_QEI0,
	NVIC_INT14_ADC_SEQ_0,
	NVIC_INT15_ADC_SEQ_1,
	NVIC_INT16_ADC_SEQ_2,
	NVIC_INT17_ADC_SEQ_3,
	NVIC_INT18_WTD_TIM0_TIM1,
	NVIC_INT19_16_32BIT_TIMER0A,
	NVIC_INT20_16_32BIT_TIMER0B,
	NVIC_INT21_16_32BIT_TIMER1A,
	NVIC_INT22_16_32BIT_TIMER1B,
	NVIC_INT23_16_32BIT_TIMER2A,
	NVIC_INT24_16_32BIT_TIMER2B,
	NVIC_INT25_ANALOG_COM_0,
	NVIC_INT26_ANALOG_COM_1,
	NVIC_INT28_SYSCTRL,
	NVIC_INT29_FLASH_EEPROM_CTRL,
	NVIC_INT30_GPIOF,
	NVIC_INT33_UART2=33,
	NVIC_INT34_SSI1,
	NVIC_INT35_16_32BIT_TIMER3A,
	NVIC_INT36_16_32BIT_TIMER3B,
	NVIC_INT37_I2C1,
	NVIC_INT38_QEI1,
	NVIC_INT39_CAN0,
	NVIC_INT40_CAN1,
	
}IntNumType;
typedef struct
{
	IntNumType IntNum;
	Group_PriorityType Group_Priority;
	SubGroup_PriorityType	SubGroup_Priority;
}NVIC_CfgType;

extern NVIC_CfgType NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS];

#endif
