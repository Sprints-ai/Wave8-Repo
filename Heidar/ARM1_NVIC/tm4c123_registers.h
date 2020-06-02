/*
 * NVIC_lcfg.c
 *
 *      Author: Abdallah Heidar
 */

#ifndef TM4C123GH6PM_REGISTERS_H_
#define TM4C123GH6PM_REGISTERS_H_

#include "std_types.h"

#define ALIAS_BASE_ADDRESS				0x42000000
#define PERIPHERAL_REG_BASE_ADDRESS		0x40000000
#define REGISTER_SIZE_IN_BYTES			4
#define REGISTER_SIZE_IN_BITS			32
#define BYTE_WIDTH						8

#define WRITE_BIT(REG_ADDRESS, BIT_OFFSET)  (*((volatile uint32_t*)(ALIAS_BASE_ADDRESS +													\
											(REG_ADDRESS - PERIPHERAL_REG_BASE_ADDRESS + BIT_OFFSET / BYTE_WIDTH) * REGISTER_SIZE_IN_BITS +	\
											(BIT_OFFSET % BYTE_WIDTH) * REGISTER_SIZE_IN_BYTES)))
											
											
#define READ_BIT(REG_ADDRESS, BIT_OFFSET)	(REGISTER(REG_ADDRESS) & (1 << BIT_OFFSET)? 1 : 0)

#define REGISTER(REG_ADDRESS)				(*((volatile uint32_t*)(REG_ADDRESS)))

#define SYSCTL_RCC_R            0x400FE060

#define SYSCTL_RCC_MOSCDIS_B0		0
#define SYSCTL_RCC_OSCSRC_B4		4
#define SYSCTL_RCC_OSCSRC_B5		5
#define SYSCTL_RCC_XTAL_B6			6
#define SYSCTL_RCC_XTAL_B7			7
#define SYSCTL_RCC_XTAL_B8			8
#define SYSCTL_RCC_XTAL_B9			9
#define SYSCTL_RCC_XTAL_B10			10
#define SYSCTL_RCC_BYPASS_B11		11
#define SYSCTL_RCC_PWRDN_B13		13
#define SYSCTL_RCC_PWMDIV_B17		17
#define SYSCTL_RCC_PWMDIV_B18		18
#define SYSCTL_RCC_PWMDIV_B19		19
#define SYSCTL_RCC_USEPWMDIV_B20	20
#define SYSCTL_RCC_USESYSDIV_B22	22
#define SYSCTL_RCC_SYSDIV_B23		23
#define SYSCTL_RCC_SYSDIV_B24		24
#define SYSCTL_RCC_SYSDIV_B25		25
#define SYSCTL_RCC_SYSDIV_B26		26
#define SYSCTL_RCC_ACG_B27			27


#define SYSCTL_RCC2_R           0x400FE070

#define SYSCTL_RCC2_OSCSRC2_B4		4
#define SYSCTL_RCC2_OSCSRC2_B5		5
#define SYSCTL_RCC2_OSCSRC2_B6		6
#define SYSCTL_RCC2_BYPASS2_B11		11
#define SYSCTL_RCC2_PWRDN2_B13		13
#define SYSCTL_RCC2_USBPWRDN_B14	14
#define SYSCTL_RCC2_SYSDIV2LSB_B22	22
#define SYSCTL_RCC2_SYSDIV2_B23		23
#define SYSCTL_RCC2_SYSDIV2_B24		24
#define SYSCTL_RCC2_SYSDIV2_B25		25
#define SYSCTL_RCC2_SYSDIV2_B26		26
#define SYSCTL_RCC2_SYSDIV2_B27		27
#define SYSCTL_RCC2_SYSDIV2_B28		28
#define SYSCTL_RCC2_DIV400_B30		30
#define SYSCTL_RCC2_USERCC2_B31		31


#define SYSCTL_RIS_R			0x400FE050

#define SYSCTL_RIS_BOR1RIS_B1		1
#define SYSCTL_RIS_MOFRIS_B3		3
#define SYSCTL_RIS_PLLLRIS_B6		6
#define SYSCTL_RIS_USBPLLLRIS_B7	7
#define SYSCTL_RIS_MOSCPUPRIS_B8	8
#define SYSCTL_RIS_VDDARIS_B10		10
#define SYSCTL_RIS_BOR0RIS_B11		11

#define SYSCTL_RCGCWD_R				0x400FE600
#define SYSCTL_RCGCTIMER_R			0x400FE604
#define SYSCTL_RCGCGPIO_R			0x400FE608
#define SYSCTL_RCGCDMA_R			0x400FE60C

#define SYSCTL_RCGCHIB_R			0x400FE614
#define SYSCTL_RCGCUART_R			0x400FE618
#define SYSCTL_RCGCSSI_R			0x400FE61C
#define SYSCTL_RCGCI2C_R			0x400FE620

#define SYSCTL_RCGCUSB_R			0x400FE628
#define SYSCTL_RCGCCAN_R			0x400FE634
#define SYSCTL_RCGCADC_R			0x400FE638
#define SYSCTL_RCGCACMP_R			0x400FE63C

#define SYSCTL_RCGCPWM_R			0x400FE640
#define SYSCTL_RCGCQEI_R			0x400FE644
#define SYSCTL_RCGCEEPROM_R			0x400FE658
#define SYSCTL_RCGCWTIMER_R			0x400FE65C

#define SCB_APINT_R					0xE000ED0C

#define SCB_APINT_PRIGROUP_B8		8
#define SCB_APINT_VECTKEY_B16		16
#define SCB_APINT_VECTKEY_VALUE		0x05FA

#define NVIC_PRI0_R					0xE000E400

typedef struct{
	uint32_t PRI0;
	uint32_t PRI1;
	uint32_t PRI2;
	uint32_t PRI3;
	uint32_t PRI4;
	uint32_t PRI5;
	uint32_t PRI6;
	uint32_t PRI7;
	uint32_t PRI8;
	uint32_t PRI9;
	uint32_t PRI10;
	uint32_t PRI11;
	uint32_t PRI12;
	uint32_t PRI13;
	uint32_t PRI14;
	uint32_t PRI15;
	uint32_t PRI16;
	uint32_t PRI17;
	uint32_t PRI18;
	uint32_t PRI19;
	uint32_t PRI20;
	uint32_t PRI21;
	uint32_t PRI22;
	uint32_t PRI23;
	uint32_t PRI24;
	uint32_t PRI25;
	uint32_t PRI26;
	uint32_t PRI27;
	uint32_t PRI28;
	uint32_t PRI29;
	uint32_t PRI30;
	uint32_t PRI31;
	uint32_t PRI32;
	uint32_t PRI33;
	uint32_t PRI34;
}PRI_RegType;

#define PRI_REGS					(*((volatile PRI_RegType*)NVIC_PRI0_R))

#define NVIC_EN0_R					0xE000E100

typedef struct{
	uint32_t EN0;
	uint32_t EN1;
	uint32_t EN2;
	uint32_t EN3;
	uint32_t EN4;
}EN_RegType;

#define EN_REGS					(*((volatile EN_RegType*)NVIC_EN0_R))

#define GPIOA_APB_BASE_ADDRESS		0x40004000
#define GPIOB_APB_BASE_ADDRESS		0x40005000
#define GPIOC_APB_BASE_ADDRESS		0x40006000
#define GPIOD_APB_BASE_ADDRESS		0x40007000
#define GPIOE_APB_BASE_ADDRESS		0x40024000
#define GPIOF_APB_BASE_ADDRESS		0x40025000

typedef struct{
	uint8_t Reserved0[0x3FC]	;
	uint32_t GPIODATA			;
	uint32_t GPIODIR			;
	uint32_t GPIOIS				;
	uint32_t GPIOIBE			;
	uint32_t GPIOIEV			;
	uint32_t GPIOIM				;
	uint32_t GPIORIS			;
	uint32_t GPIOMIS			;
	uint32_t GPIOICR			;
	uint32_t GPIOAFSEL			;
	uint8_t Reserved1[0xDC]		;
	uint32_t GPIODR2R    		;
	uint32_t GPIODR4R    		;
	uint32_t GPIODR8R    		;
	uint32_t GPIOODR     		;
	uint32_t GPIOPUR     		;
	uint32_t GPIOPDR     		;
	uint32_t GPIOSLR     		;
	uint32_t GPIODEN     		;
	uint32_t GPIOLOCK    		;
	uint32_t GPIOCR      		;
	uint32_t GPIOAMSEL   		;
	uint32_t GPIOPCTL    		;
	uint32_t GPIOADCCTL  		;
	uint32_t GPIODMACTL  		;
}PORT_RegType;

#define	PORT_A		((volatile PORT_RegType*)GPIOA_APB_BASE_ADDRESS)
#define	PORT_B		((volatile PORT_RegType*)GPIOB_APB_BASE_ADDRESS)
#define	PORT_C		((volatile PORT_RegType*)GPIOC_APB_BASE_ADDRESS)
#define	PORT_D		((volatile PORT_RegType*)GPIOD_APB_BASE_ADDRESS)
#define	PORT_E		((volatile PORT_RegType*)GPIOE_APB_BASE_ADDRESS)
#define	PORT_F		((volatile PORT_RegType*)GPIOF_APB_BASE_ADDRESS)

typedef PORT_RegType* PointerToPortRegisters;

#define ADC0_BASE_ADDRESS		0x40038000
#define ADC1_BASE_ADDRESS		0x40039000

typedef struct{
	uint32_t ADCACTSS			;
	uint32_t ADCRIS				;
	uint32_t ADCIM				;
	uint32_t ADCISC				;
	uint32_t ADCOSTAT			;
	uint32_t ADCEMUX			;
	uint32_t ADCUSTAT			;
	uint32_t ADCTSSEL			;
	uint32_t ADCSSPRI			;
	uint32_t ADCSPC				;
	uint32_t ADCPSSI			;
	uint32_t Reserved0[0x01]	;
	uint32_t ADCSAC				;
	uint32_t ADCDCISC			;
	uint32_t ADCCTL				;
	uint32_t Reserved1[0x01]	;
	uint32_t ADCSSMUX0			;
	uint32_t ADCSSCTL0			;
	uint32_t ADCSSFIFO0			;
	uint32_t ADCSSFSTAT0		;
	uint32_t ADCSSOP0			;
	uint32_t ADCSSDC0			;
	uint32_t Reserved2[0x02]	;
	uint32_t ADCSSMUX1			;
	uint32_t ADCSSCTL1			;
	uint32_t ADCSSFIFO1			;
	uint32_t ADCSSFSTAT1		;
	uint32_t ADCSSOP1			;
	uint32_t ADCSSDC1			;
	uint32_t Reserved3[0x02]	;
	uint32_t ADCSSMUX2			;
	uint32_t ADCSSCTL2			;
	uint32_t ADCSSFIFO2			;
	uint32_t ADCSSFSTAT2		;
	uint32_t ADCSSOP2			;
	uint32_t ADCSSDC2			;
	uint32_t Reserved4[0x02]	;
	uint32_t ADCSSMUX3			;
	uint32_t ADCSSCTL3			;
	uint32_t ADCSSFIFO3			;
	uint32_t ADCSSFSTAT3		;
	uint32_t ADCSSOP3			;
	uint32_t ADCSSDC3			;
}ADC_RegType;

#define	ADC_0		((volatile ADC_RegType*)ADC0_BASE_ADDRESS)
#define	ADC_1		((volatile ADC_RegType*)ADC1_BASE_ADDRESS)

typedef	ADC_RegType* PointerToADCRegisters;


#endif /* TM4C123GH6PM_REGISTERS_H_ */
