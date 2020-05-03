#ifndef __MCU_HW_H__
#define __MCU_HW_H__

#include "../std_types.h"
/**************************************************************************************/
/*					MCU_hw.h		define all registers							  */
/**************************************************************************************/

//								NVIC REGISTER 											//

#define EN0_REG						*((reg_type32_t )0xE000E100)
#define EN1_REG						*((reg_type32_t )0xE000E104)
#define EN2_REG						*((reg_type32_t )0xE000E108)
#define EN3_REG						*((reg_type32_t )0xE000E10C)
#define EN4_REG						*((reg_type32_t )0xE000E110)

#define DIS0_REG					*((reg_type32_t )0xE000E180)
#define DIS1_REG					*((reg_type32_t )0xE000E184)
#define DIS2_REG					*((reg_type32_t )0xE000E188)
#define DIS3_REG					*((reg_type32_t )0xE000E18C)
#define DIS4_REG					*((reg_type32_t )0xE000E190)

#define PEND0_REG					*((reg_type32_t )0xE000E200)
#define PEND1_REG					*((reg_type32_t )0xE000E204)
#define PEND2_REG					*((reg_type32_t )0xE000E208)
#define PEND3_REG					*((reg_type32_t )0xE000E20C)
#define PEND4_REG					*((reg_type32_t )0xE000E210)

#define UNPEND0_REG					*((reg_type32_t )0xE000E280)
#define UNPEND1_REG					*((reg_type32_t )0xE000E284)
#define UNPEND2_REG					*((reg_type32_t )0xE000E288)
#define UNPEND3_REG					*((reg_type32_t )0xE000E28C)
#define UNPEND4_REG					*((reg_type32_t )0xE000E290)

#define ACTIVE0_REG					*((reg_type32_t )0xE000E300)
#define ACTIVE1_REG					*((reg_type32_t )0xE000E304)
#define ACTIVE2_REG					*((reg_type32_t )0xE000E308)
#define ACTIVE3_REG					*((reg_type32_t )0xE000E30C)
#define ACTIVE4_REG					*((reg_type32_t )0xE000E310)


#define PRI0_REG					*((reg_type32_t )0xE000E400)
#define PRI1_REG					*((reg_type32_t )0xE000E404)
#define PRI2_REG					*((reg_type32_t )0xE000E408)
#define PRI3_REG					*((reg_type32_t )0xE000E40C)

#define PRI4_REG					*((reg_type32_t )0xE000E410)
#define PRI5_REG					*((reg_type32_t )0xE000E414)
#define PRI6_REG					*((reg_type32_t )0xE000E418)
#define PRI7_REG					*((reg_type32_t )0xE000E41C)

#define PRI8_REG					*((reg_type32_t )0xE000E420)
#define PRI9_REG					*((reg_type32_t )0xE000E424)
#define PRI10_REG					*((reg_type32_t )0xE000E428)
#define PRI11_REG					*((reg_type32_t )0xE000E42C)

#define PRI12_REG					*((reg_type32_t )0xE000E430)
#define PRI13_REG					*((reg_type32_t )0xE000E434)
#define PRI14_REG					*((reg_type32_t )0xE000E438)
#define PRI15_REG					*((reg_type32_t )0xE000E43C)

#define PRI16_REG					*((reg_type32_t )0xE000E440)
#define PRI17_REG					*((reg_type32_t )0xE000E444)
#define PRI18_REG					*((reg_type32_t )0xE000E448)
#define PRI19_REG					*((reg_type32_t )0xE000E44C)

#define PRI20_REG					*((reg_type32_t )0xE000E450)
#define PRI21_REG					*((reg_type32_t )0xE000E454)
#define PRI22_REG					*((reg_type32_t )0xE000E458)
#define PRI23_REG					*((reg_type32_t )0xE000E45C)

#define PRI24_REG					*((reg_type32_t )0xE000E460)
#define PRI25_REG					*((reg_type32_t )0xE000E464)
#define PRI26_REG					*((reg_type32_t )0xE000E468)
#define PRI27_REG					*((reg_type32_t )0xE000E46C)

#define PRI28_REG					*((reg_type32_t )0xE000E470)
#define PRI29_REG					*((reg_type32_t )0xE000E474)
#define PRI30_REG					*((reg_type32_t )0xE000E478)
#define PRI31_REG					*((reg_type32_t )0xE000E47C)

#define PRI32_REG					*((reg_type32_t )0xE000E480)
#define PRI33_REG					*((reg_type32_t )0xE000E484)
#define PRI34_REG					*((reg_type32_t )0xE000E488)


#define SWTRIG_REG					*((reg_type32_t )0xE000EF00)

/* **************************************************************************************************** */

#define INTCTRL_REG					*((reg_type32_t )0xE000ED04)
#define VTABLE_REG					*((reg_type32_t )0xE000ED08)
#define APINT_REG					*((reg_type32_t )0xE000ED0C)


/***************************************************************************************************************/
/*									PortRegister 															*/
/*****************************************************************************/
/*					Mcu_Hw.h										         */	
/*****************************************************************************/

typedef struct
{
    uint32_t GPIODATA    ;
	uint8_t  REserved[0x3FC];
    uint32_t GPIODIR     ;
    uint32_t GPIOIS      ;
    uint32_t GPIOIBE     ;
    uint32_t GPIOIEV     ;
    uint32_t GPIOIM      ;
    uint32_t GPIORIS     ;
    uint32_t GPIOMIS     ;
    uint32_t GPIOICR     ;
    uint32_t GPIOAFSEL   ; /*offset : 0x420 -> 424 */

    uint8_t  Reserved_2[0xDC];
	
    uint32_t GPIODR2R    ; /*offset : 0x500 */
    uint32_t GPIODR4R    ;
    uint32_t GPIODR8R    ;
    uint32_t GPIOODR     ;
    uint32_t GPIOPUR     ;
    uint32_t GPIOPDR     ;
    uint32_t GPIOSLR     ;
    uint32_t GPIODEN     ;
    uint32_t GPIOLOCK    ;
    uint32_t GPIOCR      ;
    uint32_t GPIOAMSEL   ;
    uint32_t GPIOPCTL    ;
    uint32_t GPIOADCCTL  ;
    uint32_t GPIODMACTL  ;
}PORT_RegType;

					// FOR APB//
					
#define BASE_ADDRESS_A   0x40004000
#define BASE_ADDRESS_B   0x40005000
#define BASE_ADDRESS_C   0x40006000
#define BASE_ADDRESS_D   0x40007000
#define BASE_ADDRESS_E   0x40024000
#define BASE_ADDRESS_F   0x40025000
        

#define  ACTINATING_PORT(PORT_BASE_ADDR)     (*((volatile PORT_RegType*)PORT_BASE_ADDR))

#endif

