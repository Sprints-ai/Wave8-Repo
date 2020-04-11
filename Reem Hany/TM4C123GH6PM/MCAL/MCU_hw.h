#ifndef __MCU_HW_H_
#define __MCU_HW_H_
#include "../../Services/includes/std_types.h"


//NVIC Registers
#define NVIC_EN0_R              (*((reg_type32_t)0xE000E100))
#define NVIC_DIS0_R             (*((reg_type32_t)0xE000E180))
#define NVIC_PEND0_R            (*((reg_type32_t)0xE000E200))
#define NVIC_UNPEND0_R          (*((reg_type32_t)0xE000E280))
#define NVIC_ACTIVE0_R          (*((reg_type32_t)0xE000E300))
#define NVIC_PRI0_R             (*((reg_type32_t)0xE000E400))
#define NVIC_APINT_R            (*((reg_type32_t)0xE000ED0C))

//SysCtrl Registers

#define SYSCTL_RIS_R            (*((reg_type32_t)0x400FE050))
#define SYSCTL_RCC_R            (*((reg_type32_t)0x400FE060))
#define SYSCTL_RCC2_R           (*((reg_type32_t)0x400FE070))
#define SYSCTL_RCGCWD_R         (*((reg_type32_t)0x400FE600))
#define SYSCTL_RCGCTIMER_R      (*((reg_type32_t)0x400FE604))
#define SYSCTL_RCGCGPIO_R       (*((reg_type32_t)0x400FE608))
#define SYSCTL_RCGCDMA_R        (*((reg_type32_t)0x400FE60C))
#define SYSCTL_RCGCHIB_R        (*((reg_type32_t)0x400FE614))
#define SYSCTL_RCGCUART_R       (*((reg_type32_t)0x400FE618))
#define SYSCTL_RCGCSSI_R        (*((reg_type32_t)0x400FE61C))
#define SYSCTL_RCGCI2C_R        (*((reg_type32_t)0x400FE620))
#define SYSCTL_RCGCUSB_R        (*((reg_type32_t)0x400FE628))
#define SYSCTL_RCGCCAN_R        (*((reg_type32_t)0x400FE634))
#define SYSCTL_RCGCADC_R        (*((reg_type32_t)0x400FE638))
#define SYSCTL_RCGCACMP_R       (*((reg_type32_t)0x400FE63C))
#define SYSCTL_RCGCPWM_R        (*((reg_type32_t)0x400FE640))
#define SYSCTL_RCGCQEI_R        (*((reg_type32_t)0x400FE644))
#define SYSCTL_RCGCEEPROM_R     (*((reg_type32_t)0x400FE658))
#define SYSCTL_RCGCWTIMER_R     (*((reg_type32_t)0x400FE65C))

#endif
