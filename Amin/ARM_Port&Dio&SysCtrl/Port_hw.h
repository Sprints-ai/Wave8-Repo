#ifndef E15_ARM_REPO_MCAL_PORT_DRIVER_PORT_HW_H_
#define E15_ARM_REPO_MCAL_PORT_DRIVER_PORT_HW_H_

#include "../utils/STD_Types.h"
#include "../utils/Bit_Math.h"

#define NVIC_REG    (*((volatile NVIC_TagType*)0xE000E100))

typedef struct
{
    uint32 B0:1;
    uint32 B1:1;
    uint32 B2:1;
    uint32 B3:1;
    uint32 B4:1;
    uint32 B5:1;
    uint32 B6:1;
    uint32 B7:1;
    uint32 B8:1;
    uint32 B9:1;
    uint32 B10:1;
    uint32 B11:1;
    uint32 B12:1;
    uint32 B13:1;
    uint32 B14:1;
    uint32 B15:1;
    uint32 B16:1;
    uint32 B17:1;
    uint32 B18:1;
    uint32 B19:1;
    uint32 B20:1;
    uint32 B21:1;
    uint32 B22:1;
    uint32 B23:1;
    uint32 B24:1;
    uint32 B25:1;
    uint32 B26:1;
    uint32 B27:1;
    uint32 B28:1;
    uint32 B29:1;
    uint32 B30:1;
    uint32 B31:1;

}bit_field_Type;


typedef struct
{
    bit_field_Type EN0 ;
    bit_field_Type EN1 ;
    bit_field_Type EN2 ;
    bit_field_Type EN3 ;
    bit_field_Type EN4 ;

}  NVIC_TagType;

typedef union
{
    uint32 R;
    struct
    {
        uint32 Access               :1;
        uint32 Prog                 :1;
        uint32 EEPROM               :1;
        uint32                      :6;
        uint32 VoltErr              :1;
        uint32 InvalidData          :1;
        uint32 EraseVerErr          :1;
        uint32                      :1;
        uint32 ProgVerErr           :1;
        uint32                      :18;
    }B;
}FLASH_INT_TAG;


#define FLASH_FMA_R             (*((volatile uint32 *)0x400FD000))
#define FLASH_FMD_R             (*((volatile uint32 *)0x400FD004))
#define FLASH_FMC_R             (*((volatile uint32 *)0x400FD008))
#define FLASH_FCRIS             (*((volatile FLASH_INT_TAG *)0x400FD00C))
#define FLASH_FCIM_R            (*((volatile uint32 *)0x400FD010))
#define FLASH_FCMISC            (*((volatile FLASH_INT_TAG *)0x400FD014))
#define FLASH_FMC2_R            (*((volatile uint32 *)0x400FD020))
#define FLASH_FWBVAL_R          (*((volatile uint32 *)0x400FD030))
#define FLASH_FWBN_R            (*((volatile uint32 *)0x400FD100))
#define FLASH_FSIZE_R           (*((volatile uint32 *)0x400FDFC0))
#define FLASH_SSIZE_R           (*((volatile uint32 *)0x400FDFC4))
#define FLASH_ROMSWMAP_R        (*((volatile uint32 *)0x400FDFCC))
#define FLASH_RMCTL_R           (*((volatile uint32 *)0x400FE0F0))
#define FLASH_BOOTCFG_R         (*((volatile uint32 *)0x400FE1D0))
#define FLASH_USERREG0_R        (*((volatile uint32 *)0x400FE1E0))
#define FLASH_USERREG1_R        (*((volatile uint32 *)0x400FE1E4))
#define FLASH_USERREG2_R        (*((volatile uint32 *)0x400FE1E8))
#define FLASH_USERREG3_R        (*((volatile uint32 *)0x400FE1EC))
#define FLASH_FMPRE0_R          (*((volatile uint32 *)0x400FE200))
#define FLASH_FMPRE1_R          (*((volatile uint32 *)0x400FE204))
#define FLASH_FMPRE2_R          (*((volatile uint32 *)0x400FE208))
#define FLASH_FMPRE3_R          (*((volatile uint32 *)0x400FE20C))
#define FLASH_FMPPE0_R          (*((volatile uint32 *)0x400FE400))
#define FLASH_FMPPE1_R          (*((volatile uint32 *)0x400FE404))
#define FLASH_FMPPE2_R          (*((volatile uint32 *)0x400FE408))
#define FLASH_FMPPE3_R          (*((volatile uint32 *)0x400FE40C))



typedef struct
{
    uint32 GPIODATA    ;
    uint32 GPIODIR     ;
    uint32 GPIOIS      ;
    uint32 GPIOIBE     ;
    uint32 GPIOIEV     ;
    uint32 GPIOIM      ;
    uint32 GPIORIS     ;
    uint32 GPIOMIS     ;
    uint32 GPIOICR     ;
    uint32 GPIOAFSEL   ; 

    uint8 Reserved_2[0xDC];
    uint32 GPIODR2R    ; 
    uint32 GPIODR4R    ;
    uint32 GPIODR8R    ;
    uint32 GPIOODR     ;
    uint32 GPIOPUR     ;
    uint32 GPIOPDR     ;
    uint32 GPIOSLR     ;
    uint32 GPIODEN     ;
    uint32 GPIOLOCK    ;
    uint32 GPIOCR      ;
    uint32 GPIOAMSEL   ;
    uint32 GPIOPCTL    ;
    uint32 GPIOADCCTL  ;
    uint32 GPIODMACTL  ;

} PORT_RegType;


#define PORTA_REG     (*((volatile PORT_RegType*)0x400043FC))
#define PORTB_REG     (*((volatile PORT_RegType*)0x400053FC))
#define PORTC_REG     (*((volatile PORT_RegType*)0x400063FC))
#define PORTD_REG     (*((volatile PORT_RegType*)0x400073FC))
#define PORTE_REG     (*((volatile PORT_RegType*)0x400243FC))
#define PORTF_REG     (*((volatile PORT_RegType*)0x400253FC))


typedef struct
{
    uint32 R0:1;
    uint32 R1:1;
    uint32 R2:1;
    uint32 R3:1;
    uint32 R4:1;
    uint32 R5:1;
    uint32 R6:1;
    uint32 R7:1;

} RCGC_TagType;

#define RCGCGPIO_REG    (*((volatile RCGC_TagType*)0x400FE608))
#define RCGCUART_REG    (*((volatile RCGC_TagType*)0x400FE618))
#define RCGCSSI_REG     (*((volatile RCGC_TagType*)0x400FE61C))
#define RCGCI2C_REG     (*((volatile RCGC_TagType*)0x400FE620))


#endif /* E15_ARM_REPO_MCAL_PORT_DRIVER_PORT_HW_H_ */