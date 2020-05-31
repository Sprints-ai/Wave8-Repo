/*
 * SYSCTR.c
 *
 * Created: 4/6/2020 8:17:59 PM
 *  Author: Khaled
 */ 

#include "SYSCTR.h"



#define SYSCTL_RCC_R            (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RCC2_R           (*((volatile unsigned long *)0x400FE070))
#define SYSCTL_RIS_R            (*((volatile unsigned long *)0x400FE050))
#define SYSCTL_IMC_R            (*((volatile unsigned long *)0x400FE054))
#define SYSCTL_MISC_R           (*((volatile unsigned long *)0x400FE058))

#define GET_BIT(REG,BIT)        (REG & BIT)

/*write to spacefic bit in peripheral register using bit band feature
 *where Base: is register base address in data sheet
 *      Offset: is register offset in data sheet
 *      Bit: is desired bit number in the register (0:31)
 *      0x20: because each register is 32 bit(0x20) multiply by register adress offset 
 *      0x04: because each bit in bit band region (peripheral register) maping to 4-bytes in alias region
 */ 
#define BIT_BAND_PERIPHERAL_STARTING_ADDRESS           0x40000000
#define ALIAS_PERIPHERAL_STARTING_ADDRESS              0x42000000
#define PERIPHERAL_ALIAS_ADDRESS(Base, Offset, Bit)    (((Base + Offset - BIT_BAND_PERIPHERAL_STARTING_ADDRESS) * 0x20) + \
                                                       ((Bit * 0x04)) + ALIAS_PERIPHERAL_STARTING_ADDRESS) 
#define WRITE_PERIPHERAL_BIT_BAND(Base, Offset, Bit)   (*((volatile unsigned long *) PERIPHERAL_ALIAS_ADDRESS(Base, Offset, Bit)))    
    
/*BIT BAND SET/CLEAR VALUES*/
#define SET_BIT_BAND     0X01
#define CLEAR_BIT_BAND   0X00


/*BITS NUMBER*/
#define BIT0      0
#define BIT1      1
#define BIT2      2
#define BIT3      3
#define BIT4      4
#define BIT5      5
#define BIT6      6
#define BIT7      7
#define BIT8      8
#define BIT9      9
#define BIT10     10
#define BIT11     11
#define BIT12     12
#define BIT13     13
#define BIT14     14
#define BIT15     15
#define BIT16     16
#define BIT17     17
#define BIT18     18
#define BIT19     19
#define BIT20     20
#define BIT21     21
#define BIT22     22
#define BIT23     23
#define BIT24     24
#define BIT25     25
#define BIT26     26
#define BIT27     27
#define BIT28     28
#define BIT29     29
#define BIT30     30
#define BIT31     31

/* SYSTEM CONTROL REGISTER MAP VALUES*/
#define SYSTEM_CONTROL_BASE     0x400FE000
#define RIS_OFFSET              0x050
#define IMC_OFFSET              0x054
#define MISC_OFFSET             0x058
#define RCC_OFFSET              0x060   
#define RCC2_OFFSET             0x070

#define PLLLMIS_BIT            6
#define PLLLRIS_BIT            6

/*RCC/RCC2 register bits*/
#define OSCSRC0_BIT            4
#define OSCSRC1_BIT            5
#define OSCSRC2_BIT            6
#define BYPASS_BIT             11
#define PWRDN_BIT              13
#define USESYSDIV_BIT          22
#define SYSDIV2LSB_BIT         22
#define DIV400_BIT             30
#define USERCC2_BIT            31

#define PLLLRIS_BIT_MASK       0x040
#define SYSDIV2_MASK           0x1FC00000

#define PLL_LOCKED             1



void SysCtr_init(void)
{
	uint32_t i;
    uint32_t TempValue = 0x00;
    uint16_t SYSCTR_RCGC_Offset = 0x00;
    uint8_t SYSCTR_RCGC_BitNum  = 0;
  //  uint8_t RegisterIndex;
  //  uint8_t BitIndex;
    
    
    
    /*** CONFIGURING THE MICROCONTROLLER TO RUN OFF A "RAW" CLOCK SOURCE ***/
    /*set the BYPASS bit to select OSC clock source*/
    WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, RCC_OFFSET, BYPASS_BIT) = SET_BIT_BAND;
    
    
    /*clear the USESYS bit*/
    WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, RCC_OFFSET, USESYSDIV_BIT) = CLEAR_BIT_BAND;
    
    
    
    /*** SET DESIRED SYSTEM CLOCK ***/
    /*Select RCC2 register values for common field*/
    WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, RCC2_OFFSET, USERCC2_BIT) = SET_BIT_BAND;
    
	/*Selects PIOS input source for the OSC from OSCSRC bits*/
    /*RCC reg*/
	WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, RCC_OFFSET, OSCSRC0_BIT) = SET_BIT_BAND;
    WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, RCC_OFFSET, OSCSRC1_BIT) = CLEAR_BIT_BAND;
    /*RCC2 reg*/
	WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, RCC2_OFFSET, OSCSRC0_BIT) = SET_BIT_BAND;
    WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, RCC2_OFFSET, OSCSRC1_BIT) = CLEAR_BIT_BAND;
    WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, RCC2_OFFSET, OSCSRC2_BIT) = CLEAR_BIT_BAND;
    
    /*Select PLL operating normally*/
    /*RCC reg*/
//   WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, RCC_OFFSET, PWRDN_BIT) = CLEAR_BIT_BAND;
    /*RCC2 reg*/
    WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, RCC2_OFFSET, PWRDN_BIT) = CLEAR_BIT_BAND;
     
    /*Desable divide by 2*/
    WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, RCC2_OFFSET, DIV400_BIT) = CLEAR_BIT_BAND;
    
    /*Active sysdiv LSB*/
    WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, RCC2_OFFSET, SYSDIV2LSB_BIT) = SET_BIT_BAND;
    
    /*Select suitable sysdiv value according to desired clock frequency*/
    TempValue  = SYSCTL_RCC2_R;
    SYSCTL_RCC2_R |= SYSDIV2_MASK;
    SYSCTL_RCC2_R = (TempValue & SysCtr_Clock_Hz);
    
    /*Set the USESYS bit to devide by sysdiv*/
    WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, RCC_OFFSET, USESYSDIV_BIT) = SET_BIT_BAND;
    
    /*wait till PLL tobe locked*/
    while (GET_BIT(SYSCTL_RIS_R, PLLLRIS_BIT_MASK) == PLL_LOCKED) ;//it should to be != but that because of debug and simulation
    
    /*Clear bit PLLLMIS*/
    WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, MISC_OFFSET, PLLLMIS_BIT) = SET_BIT_BAND;
    
    /*Enable use of PLL*/
    WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, RCC_OFFSET, BYPASS_BIT) = CLEAR_BIT_BAND;
    
    
    
    
    /*TODO: Enable Clock Gates */
    for(i=0; i < NUMBER_OF_PERIPHERALS ;i++)
	{
        SYSCTR_RCGC_Offset = garrstr_SYSCTR_Cfg[i].Peripheral;
        SYSCTR_RCGC_BitNum = garrstr_SYSCTR_Cfg[i].Channel;
        WRITE_PERIPHERAL_BIT_BAND(SYSTEM_CONTROL_BASE, SYSCTR_RCGC_Offset, SYSCTR_RCGC_BitNum);
	}
	
}
