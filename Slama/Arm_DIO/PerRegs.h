/*Author : A7md Salama
*/
#ifndef PERREGS_H
#define PERREGS_H
#ifdef  PERREGS_H

/*includes*/
#include "std_types.h"

/*Adrs definitions*/
#define RCC_BASE (0x40023800)

/*GPIO Base Addrs*/
#define GPIOA_BASE (0x40020000)
#define GPIOB_BASE (0x40020400)
#define GPIOC_BASE (0x40020800)
#define GPIOD_BASE (0x40020C00)
#define GPIOE_BASE (0x40021000)
#define GPIOH_BASE (0x40021C00)


/*Rcc Regs*/
typedef struct{
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    volatile uint32_t reserved1;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t reserved2;
    volatile uint32_t reserved3;
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    volatile uint32_t reserved4;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t reserved5;
    volatile uint32_t reserved6;
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    volatile uint32_t reserved7;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    volatile uint32_t reserved8;
    volatile uint32_t reserved9;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t reserved10;
    volatile uint32_t reserved11;
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
    volatile uint32_t PLLSAICFGR;
    volatile uint32_t DCKCFGR;
}str_RCC_t;

/*Gpio Regs*/
typedef struct{

    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile const uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint8_t AFR[8];
}str_GPIO_t;

/*Define pointer to RCC*/
#define RCC ((str_RCC_t *) RCC_BASE)

/*this type to be indicator of constant pointer to GPIO struct*/
typedef volatile str_GPIO_t * GPIO_PTR;

/*Define GPIO Adress*/
#define GPIOA ((str_GPIO_t *) GPIOA_BASE)
#define GPIOB ((str_GPIO_t *) GPIOB_BASE)
#define GPIOC ((str_GPIO_t *) GPIOC_BASE)
#define GPIOD ((str_GPIO_t *) GPIOD_BASE)
#define GPIOE ((str_GPIO_t *) GPIOE_BASE)
#define GPIOH ((str_GPIO_t *) GPIOH_BASE)



#endif
#endif
