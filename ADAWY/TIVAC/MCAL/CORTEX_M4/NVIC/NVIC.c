/*
 * NVIC.c
 *
 * Created: 4/3/2020 10:52:14 AM
 *  Author: Khaled
 */ 

#include "NVIC.h"

#define GET_REG(BASE,OFFSET) (*((volatile unsigned long *)(BASE + OFFSET)))

/*BASE ADDRESS OF CORETEX M4 PERIPHERALS (NVIC/SYSTICK/SCBMPU/FPU)*/
#define CORE_PERIPHERALS_BASE_ADDRESS       0xE000E000
#define NVIC_OFFSET                         0x00000100
#define NVIC_PRIORITY_OFFSET                0x400
#define NVIC_APINT_OFFSET                   0xD0C
#define REGSITER_SIZE_IN_BYTE               4
#define NUM_OF_INT_EN_IN_REG                32
#define NUM_OF_INT_PRIORTY_IN_REG           4


/*APINT REGSITER VALUES*/
#define PRIORTY_GROUP_MASK      0xFFFF0F00
#define xxx                     0x05FAF4FF


//extern NVIC_CfgType NVIC_CfgArr[];

void NVIC_Init(void)
{
    uint8_t i;
    uint32_t NVIC_RegOffset;
    uint32_t TempValue = 0x00;
    IntNumType NVIC_IntNum;
    Group_PriorityType NVIC_Group_Priority;
//    SubGroup_PriorityType    NVIC_SubGroup_Priority;
    
    /*SWITCH TO PRIVILAGED MODE TO ALLOW TO ACESS THR REGISTERS*/
    SWITCH_TO_PRIVILAGE ;
    
    /*** SET COMBINATION IN APINT  XXX XXY XYY YYY ***/
    TempValue  = GET_REG(CORE_PERIPHERALS_BASE_ADDRESS, NVIC_APINT_OFFSET);
    TempValue |= PRIORTY_GROUP_MASK;
    GET_REG(CORE_PERIPHERALS_BASE_ADDRESS, NVIC_APINT_OFFSET) = ((TempValue) & (xxx)); 


    for(i=0; i<NUM_OF_ACTIVATED_INTERRUPTS; i++)
    {    
        NVIC_IntNum = NVIC_CfgArr[i].IntNum;
        NVIC_Group_Priority = NVIC_CfgArr[i].Group_Priority;
        
//        NVIC_SubGroup_Priority = NVIC_CfgArr[i].SubGroup_Priority;

        /*** Enable Interrupt ***/ 
        /*get desired interrupt enable bit value (mask)*/
        TempValue = 1 << (NVIC_IntNum % NUM_OF_INT_EN_IN_REG);
        
        /*calculate offset of desired NVIC interrupt enable register*/
        NVIC_RegOffset = NVIC_OFFSET + ((NVIC_IntNum / NUM_OF_INT_EN_IN_REG) * REGSITER_SIZE_IN_BYTE);
        
        /*get desired NVEC interrupt register and set desired interrupt enable bit*/
        GET_REG(CORE_PERIPHERALS_BASE_ADDRESS, NVIC_RegOffset) |= TempValue;
   

        /*** SET PRIORITY GROUP/SUBGROUP ***/
        //user should choose priorty groupt/sub-group configeration (xxx,xxy,xyy,yyy) if
        //xxx      G<<5
        //xxy      (G<<6) + (s<<5)
        //xyy      (G<<7) + (s<<5)
        //yyy      s<<5
        /*get desired interrupt priorty value (mask)*/
        TempValue = NVIC_Group_Priority << (5 + ((NVIC_IntNum % NUM_OF_INT_PRIORTY_IN_REG) * 8));
        
        /*calculate offset of desired NVIC interrupt Priority register*/
        NVIC_RegOffset = NVIC_PRIORITY_OFFSET + ((NVIC_IntNum / NUM_OF_INT_PRIORTY_IN_REG) * REGSITER_SIZE_IN_BYTE);
        
        /*get desired NVEC interrupt register and set desired interrupt priorty value*/
        GET_REG(CORE_PERIPHERALS_BASE_ADDRESS,NVIC_RegOffset) |= TempValue;
    }    
}
