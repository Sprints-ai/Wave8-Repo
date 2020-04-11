#ifndef __SYSCTRL_TYPES_H__
#define __SYSCTRL_TYPES_H__
#include "../../Services/includes/std_types.h"

typedef uint8_t SysCtl_Periph_Name_t;
typedef struct strSysCtlCfg_s_t{
	SysCtl_Periph_Name_t RegName;
	reg_type32_t  Reg;
}strSysCtlCfg_s_t;

#define RCGC_WD1                     0  
#define RCGC_WD2                     1 
#define RCGC_TIMER_16_32_0           0 
#define RCGC_TIMER_16_32_1           1 
#define RCGC_TIMER_16_32_2           2 
#define RCGC_TIMER_16_32_3           3 
#define RCGC_TIMER_16_32_4           4 
#define RCGC_TIMER_16_32_5           5 
#define RCGC_GPIOA                   0 
#define RCGC_GPIOB                   1 
#define RCGC_GPIOC                   2 
#define RCGC_GPIOD                   3 
#define RCGC_GPIOE                   4 
#define RCGC_GPIOF                   5 
#define RCGC_DMA                     0 
#define RCGC_HIB                     0 
#define RCGC_UART_MOD_0              0 
#define RCGC_UART_MOD_1              1 
#define RCGC_UART_MOD_2              2 
#define RCGC_UART_MOD_3              3 
#define RCGC_UART_MOD_4              4 
#define RCGC_UART_MOD_5              5 
#define RCGC_UART_MOD_6              6 
#define RCGC_UART_MOD_7              7 
#define RCGC_SSI_MOD_0               0 
#define RCGC_SSI_MOD_1               1 
#define RCGC_SSI_MOD_2               2 
#define RCGC_SSI_MOD_3               3 
#define RCGC_I2C_MOD_0               0 
#define RCGC_I2C_MOD_1               1 
#define RCGC_I2C_MOD_2               2 
#define RCGC_I2C_MOD_3               3 
#define RCGC_USB                     0 
#define RCGC_CAN_MOD_0               0 
#define RCGC_CAN_MOD_1               1 
#define RCGC_ADC_MOD_0               0 
#define RCGC_ADC_MOD_1               1 
#define RCGC_ACMP                    0 
#define RCGC_PWM_MOD_0               0 
#define RCGC_PWM_MOD_1               1
#define RCGC_QEI_MOD_0               0
#define RCGC_QEI_MOD_1               1
#define RCGC_EEPROM                  0
#define RCGC_WTIMER_32_64_0          0
#define RCGC_WTIMER_32_64_1          1
#define RCGC_WTIMER_32_64_2          2
#define RCGC_WTIMER_32_64_3          3
#define RCGC_WTIMER_32_64_4          4
#define RCGC_WTIMER_32_64_5          5

#endif
