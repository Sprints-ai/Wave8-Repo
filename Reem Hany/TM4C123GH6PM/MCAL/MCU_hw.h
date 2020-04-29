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





//GPIO_Offset

#define GPIODATA_OFFSET              0x3FC
#define GPIODIR_OFFSET               0x400
#define GPIOIS_OFFSET                0x404
#define GPIOIBE_OFFSET               0x408
#define GPIOIEV_OFFSET               0x40C
#define GPIOIM_OFFSET                0x410
#define GPIORIS_OFFSET               0x414
#define GPIOMIS_OFFSET               0x418
#define GPIOICR_OFFSET               0x41C
#define GPIOAFSEL_OFFSET             0x420  
#define GPIODR2R_OFFSET              0x500 
#define GPIODR4R_OFFSET              0x504 
#define GPIODR8R_OFFSET              0x508 
#define GPIOODR_OFFSET               0x50C
#define GPIOPUR_OFFSET               0x510
#define GPIOPDR_OFFSET               0x514
#define GPIOSLR_OFFSET               0x518
#define GPIODEN_OFFSET               0x51C
#define GPIOLOCK_OFFSET              0x520 
#define GPIOCR_OFFSET                0x524
#define GPIOAMSEL_OFFSET             0x528  
#define GPIOPCTL_OFFSET              0x52C 
#define GPIOADCCTL_OFFSET            0x530   
#define GPIODMACTL_OFFSET            0x534   
#define GPIOPeriphID4_OFFSET         0xFD0      
#define GPIOPeriphID5_OFFSET         0xFD4      
#define GPIOPeriphID6_OFFSET         0xFD8      
#define GPIOPeriphID7_OFFSET         0xFDC      
#define GPIOPeriphID0_OFFSET         0xFE0      
#define GPIOPeriphID1_OFFSET         0xFE4      
#define GPIOPeriphID2_OFFSET         0xFE8      
#define GPIOPeriphID3_OFFSET         0xFEC  
#define GPIOPCellID0_OFFSET          0xFF0
#define GPIOPCellID1_OFFSET          0xFF4 
#define GPIOPCellID2_OFFSET          0xFF8 
#define GPIOPCellID3_OFFSET          0xFFC 

//GPIO BASE
#define GPIOPort_A_APB_BASE          0x40004000
#define GPIOPort_A_AHB_BASE          0x40058000
#define GPIOPort_B_APB_BASE          0x40005000
#define GPIOPort_B_AHB_BASE          0x40059000
#define GPIOPort_C_APB_BASE          0x40006000
#define GPIOPort_C_AHB_BASE          0x4005A000  
#define GPIOPort_D_APB_BASE          0x40007000
#define GPIOPort_D_AHB_BASE          0x4005B000
#define GPIOPort_E_APB_BASE          0x40024000
#define GPIOPort_E_AHB_BASE          0x4005C000
#define GPIOPort_F_APB_BASE          0x40025000
#define GPIOPort_F_AHB_BASE          0x4005D000

#define GPIOREG(BASE_ADDRESS,OFFSET)		(*((reg_type32_t)(BASE_ADDRESS + OFFSET)))



//ADC
/*
typedef struct stADC_Reg_t{
	volatile uint32_t ADCACTSS             ;  
	volatile uint32_t ADCRIS               ;
	volatile uint32_t ADCIM                ;
	volatile uint32_t ADCISC               ;
	volatile uint32_t ADCOSTAT             ; 
	volatile uint32_t ADCEMUX              ;
	volatile uint32_t ADCUSTAT             ;
	volatile uint32_t ADCTSSEL             ;
	volatile uint32_t ADCSSPRI             ;
	volatile uint32_t ADCSPC               ;
	volatile uint32_t ADCPSSI              ;
	volatile uint32_t Reserved             ;
	volatile uint32_t ADCSAC               ;
	volatile uint32_t ADCDCISC             ;
	volatile uint32_t ADCCTL               ;
	volatile uint32_t Reserved_            ;
	volatile uint32_t ADCSSMUX0            ;
	volatile uint32_t ADCSSCTL0            ;
	volatile uint32_t ADCSSFIFO0           ;
	volatile uint32_t ADCSSFSTAT0          ;
	volatile uint32_t ADCSSOP0             ;
	volatile uint32_t ADCSSDC0             ;
	volatile uint32_t Reserved__[2]        ;
	volatile uint32_t ADCSSMUX1            ;
	volatile uint32_t ADCSSCTL1            ;
	volatile uint32_t ADCSSFIFO1           ;
	volatile uint32_t ADCSSFSTAT1          ;
	volatile uint32_t ADCSSOP1             ;
	volatile uint32_t ADCSSDC1             ;
	volatile uint32_t Reserved___[2]       ;
	volatile uint32_t ADCSSMUX2            ;
	volatile uint32_t ADCSSCTL2            ;
	volatile uint32_t ADCSSFIFO2           ;
	volatile uint32_t ADCSSFSTAT2          ;
	volatile uint32_t ADCSSOP2             ;
	volatile uint32_t ADCSSDC2             ;
	volatile uint32_t reserved___[2]       ;
	volatile uint32_t ADCSSMUX3            ;
	volatile uint32_t ADCSSCTL3            ;
	volatile uint32_t ADCSSFIFO3           ;
	volatile uint32_t ADCSSFSTAT3          ;
	volatile uint32_t ADCSSOP3             ;
	volatile uint32_t ADCSSDC3             ;
	volatile uint32_t reserved_[786]       ;
	volatile uint32_t ADCDCRIC             ;
	volatile uint32_t reserved__[63]       ;
	volatile uint32_t ADCDCCTL0            ;
	volatile uint32_t ADCDCCTL1            ;
	volatile uint32_t ADCDCCTL2            ;
	volatile uint32_t ADCDCCTL3            ;
	volatile uint32_t ADCDCCTL4            ;
	volatile uint32_t ADCDCCTL5            ;
	volatile uint32_t ADCDCCTL6            ;
	volatile uint32_t ADCDCCTL7            ;
	volatile uint32_t reserved____[8]      ;
	volatile uint32_t ADCDCCMP0            ;
	volatile uint32_t ADCDCCMP1            ;
	volatile uint32_t ADCDCCMP2            ;
	volatile uint32_t ADCDCCMP3            ;
	volatile uint32_t ADCDCCMP4            ;
	volatile uint32_t ADCDCCMP5            ;
	volatile uint32_t ADCDCCMP6            ;
	volatile uint32_t ADCDCCMP7            ;
	volatile uint32_t reservedd___[88]     ;
	volatile uint32_t ADCPP                ;
	volatile uint32_t ADCPC                ;
	volatile uint32_t ADCCC                ;
}stADC_Reg_t;*/



#define ADC0           0x40038000
#define ADC1           0x40039000


#define ADCACTSS       0x00
#define ADCRIS         0x004
#define ADCIM          0x008
#define ADCISC         0x00C
#define ADCOSTAT       0x10
#define ADCEMUX        0x14
#define ADCUSTAT       0x18
#define ADCTSSEL       0x1C
#define ADCSSPRI       0x20
#define ADCSPC         0x24
#define ADCPSSI        0x28
#define ADCSAC         0x30
#define ADCDCISC       0x34
#define ADCCTL         0x38
#define ADCSSMUX0      0x40
#define ADCSSCTL0      0x44
#define ADCSSFIFO0     0x48
#define ADCSSFSTAT0    0x4C
#define ADCSSOP0       0x50
#define ADCSSDC0       0x54
#define ADCSSMUX1      0x60
#define ADCSSCTL1      0x64
#define ADCSSFIFO1     0x68
#define ADCSSFSTAT1    0x6C
#define ADCSSOP1       0x70
#define ADCSSDC1       0x74
#define ADCSSMUX2      0x80
#define ADCSSCTL2      0x84
#define ADCSSFIFO2     0x88
#define ADCSSFSTAT2    0x8C
#define ADCSSOP2       0x90
#define ADCSSDC2       0x94
#define ADCSSMUX3      0xA0
#define ADCSSCTL3      0xA4
#define ADCSSFIFO3     0xA8
#define ADCSSFSTAT3    0xAC
#define ADCSSOP3       0xB0
#define ADCSSDC3       0xB4
#define ADCDCRIC       0xD00
#define ADCDCCTL0      0xE00
#define ADCDCCTL1      0xE04
#define ADCDCCTL2      0xE08
#define ADCDCCTL3      0xE0C
#define ADCDCCTL4      0xE10
#define ADCDCCTL5      0xE14
#define ADCDCCTL6      0xE18
#define ADCDCCTL7      0xE1C
#define ADCDCCMP0      0xE40
#define ADCDCCMP1      0xE44
#define ADCDCCMP2      0xE48
#define ADCDCCMP3      0xE4C
#define ADCDCCMP4      0xE50
#define ADCDCCMP5      0xE54
#define ADCDCCMP6      0xE58
#define ADCDCCMP7      0xE5C
#define ADCPP          0xFC0
#define ADCPC          0xFC4
#define ADCCC          0xFC8

#define ADCREG(BASE_ADDRESS,OFFSET)		(*((reg_type32_t)(BASE_ADDRESS + OFFSET)))


#endif
