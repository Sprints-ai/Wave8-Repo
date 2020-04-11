#include "../includes/SysCtrl_lCfg.h"
#include "../includes/MCU_hw.h"
strSysCtlCfg_s_t periph_Clk[NUM_OF_PRIPHERALS] ={
RCGC_GPIOA         ,         &SYSCTL_RCGCGPIO_R,
RCGC_GPIOB         ,         &SYSCTL_RCGCGPIO_R,
RCGC_UART_MOD_0    ,         &SYSCTL_RCGCUART_R,
};

