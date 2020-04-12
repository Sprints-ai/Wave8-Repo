/*
 * NVIC_Types.h
 *
 * Created: 4/3/2020 10:50:09 AM
 *  Author: Khaled
 */ 


#ifndef NVIC_TYPES_H_
#define NVIC_TYPES_H_

/*
*** INCLUSIONS
*/

#include "ARM_STD_t.h"

/* primitive types */
typedef uint8_t SubGroup_Priority_t;
typedef uint8_t Group_Priority_t;
typedef uint8_t INT_Numb_t;

/*NVIC INTURREPT NUMBER VALUES*/
#define NVIC_INT_GPIO_PORT_A                                 0 
#define NVIC_INT_GPIO_PORT_B                                 1 
#define NVIC_INT_GPIO_PORT_C                                 2 
#define NVIC_INT_GPIO_PORT_D                                 3 
#define NVIC_INT_GPIO_PORT_E                                 4 
#define NVIC_INT_UART0                                       5 
#define NVIC_INT_UART1                                       6 
#define NVIC_INT_SSI0                                        7 
#define NVIC_INT_I2C0                                        8 
#define NVIC_INT_PWM0_FAULT                                  9 
#define NVIC_INT_PWM0_GENERATOR_0                            10
#define NVIC_INT_PWM0_GENERATOR_1                            11
#define NVIC_INT_PWM0_GENERATOR_2                            12
#define NVIC_INT_QEI_0                                       13 
#define NVIC_INT_ADC_0_SEQUENCE_0                            14 
#define NVIC_INT_ADC_0_SEQUENCE_1                            15 
#define NVIC_INT_ADC_0_SEQUENCE_2                            16 
#define NVIC_INT_ADC_0_SEQUENCE_3                            17 
#define NVIC_INT_WATCHDOG TIMERS_0&1                         18  
#define NVIC_INT_16_32_BIT_TIMER_0A                          19 
#define NVIC_INT_16_32_BIT_TIMER_0B                          20 
#define NVIC_INT_16_32_BIT_TIMER_1A                          21 
#define NVIC_INT_16_32_BIT_TIMER_1B                          22 
#define NVIC_INT_16_32_BIT_TIMER_2A                          23 
#define NVIC_INT_16_32_BIT_TIMER_2B                          24 
#define NVIC_INT_ANALOG_COMPARATOR_0                         25  
#define NVIC_INT_ANALOG_COMPARATOR_1                         26  
#define NVIC_INT_SYSTEM CONTROL                              28 
#define NVIC_INT_FLASH_MEMORY_CONTROL_AND_EEPROM_CONTROL     29 
#define NVIC_INT_GPIO_PORT_F                                 30
#define NVIC_INT_UART2                                       33
#define NVIC_INT_SSI1                                        34
#define NVIC_INT_16_32_BIT_TIMER_3A                          35
#define NVIC_INT_16_32_BIT_TIMER_3B                          36
#define NVIC_INT_I2C1                                        37
#define NVIC_INT_QEI1                                        38
#define NVIC_INT_CAN0                                        39
#define NVIC_INT_CAN1                                        40
#define NVIC_INT_HIBERNATION_MODULE                          43
#define NVIC_INT_USB                                         44
#define NVIC_INT_PWM_GENERATOR_3                             45
#define NVIC_INT_DMA_SOFTWARE                                46
#define NVIC_INT_DMA_ERROR                                   47
#define NVIC_INT_ADC1_SEQUENCE_0                             48
#define NVIC_INT_ADC1_SEQUENCE_1                             49
#define NVIC_INT_ADC1_SEQUENCE_2                             50
#define NVIC_INT_ADC1_SEQUENCE_3                             51
#define NVIC_INT_SSI2                                        57
#define NVIC_INT_SSI3                                        58
#define NVIC_INT_UART3                                       59
#define NVIC_INT_UART4                                       60
#define NVIC_INT_UART5                                       61
#define NVIC_INT_UART6                                       62
#define NVIC_INT_UART7                                       63
#define NVIC_INT_I2C2                                        68
#define NVIC_INT_I2C3                                        69
#define NVIC_INT_16_32_BIT_TIMER_4A                          70    
#define NVIC_INT_16_32_BIT_TIMER_4B                          71
#define NVIC_INT_16_32_BIT_TIMER_5A                          92
#define NVIC_INT_16_32_BIT_TIMER_5B                          93
#define NVIC_INT_32_64_BIT_TIMER_0A                          94
#define NVIC_INT_32_64_BIT_TIMER_0B                          95
#define NVIC_INT_32_64_BIT_TIMER_1A                          96
#define NVIC_INT_32_64_BIT_TIMER_1B                          97 
#define NVIC_INT_32_64_BIT_TIMER_2A                          98 
#define NVIC_INT_32_64_BIT_TIMER_2B                          99 
#define NVIC_INT_32_64_BIT_TIMER_3A                          100
#define NVIC_INT_32_64_BIT_TIMER_3B                          101
#define NVIC_INT_32_64_BIT_TIMER_4A                          102
#define NVIC_INT_32_64_BIT_TIMER_4B                          103
#define NVIC_INT_32_64_BIT_TIMER_5A                          104
#define NVIC_INT_32_64_BIT_TIMER_5B                          105
#define NVIC_INT_SYSTEM_EXCEPTION                            106
#define NVIC_INT_PWM1_GENERATOR_0                            134
#define NVIC_INT_PWM1_GENERATOR_1                            135
#define NVIC_INT_PWM1_GENERATOR_2                            136
#define NVIC_INT_PWM1_GENERATOR_3                            137
#define NVIC_INT_PWM1_FAULT                                  138

    
typedef struct
{
	INT_Numb_t           u8_INT_Num;
	Group_Priority_t     u8_Group_Priority;
	SubGroup_Priority_t	u8_SubGroup_Priority;
}strNVIC_Cfg_t;

#endif /* NVIC_TYPES_H_ */
