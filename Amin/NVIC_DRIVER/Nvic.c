#include "Nvic.h"

#define NVIC_BASE         0xE000E000 
#define NVIC_OFFSET                        0x00000100
#define NVIC_PRI_OFFSET                0x400
#define APINT_OFFSET                   0xD0C
#define PRIG_VALUE      0xFFFF0F00  
#define GROUB_MASK_ADDRESS                     0x05FAF4FF
#define FOUR_BYTE_LENGTH_REG               4
#define FOUR_INT_PRI           4
#define FIFTH_BIT 5
#define EIGHT_BIT_LENGTH 8
#define INTERRUPT_ENABLE_BITS                32

void NVIC_Init(void)
{
    uint8_t Iterations;
    Group_PriorityType NVIC_Group_Priority;
	uint32_t Offset_Regester,Mask_Address;
	 IntNumType Int_Num;
	  
    Mask_Address  =(*((volatile unsigned long *)(NVIC_BASE|APINT_OFFSET)))|PRIG_VALUE;
    (*((volatile unsigned long *)(NVIC_BASE|APINT_OFFSET))) = ((Mask_Address) & (GROUB_MASK_ADDRESS)); 

/*TODO Set Combination in APINT  xxx xxy xyy yyy*/
    for(Iterations=0; Iterations<NUM_OF_ACTIVATED_INTERRUPTS; Iterations++)
    {    
        Int_Num = NVIC_CfgArr[Iterations].IntNum;
        NVIC_Group_Priority = NVIC_CfgArr[Iterations].Group_Priority;

	/*TODO Enable Interrupt */
        Mask_Address = 1 << (Int_Num % INTERRUPT_ENABLE_BITS);
        //obtain offset of NVIC interrupt register
        Offset_Regester = NVIC_OFFSET + ((Int_Num/INTERRUPT_ENABLE_BITS)*FOUR_BYTE_LENGTH_REG);
        // set interrupt enable 
        (*((volatile unsigned long *)(NVIC_BASE|Offset_Regester)))|= Mask_Address;

        /*TODO Set Priority Group/SubGroup*/
        Mask_Address = NVIC_Group_Priority << (((Int_Num % FOUR_INT_PRI)*EIGHT_BIT_LENGTH)+FIFTH_BIT);
        // get offset for nvic priority regester
        Offset_Regester = NVIC_PRI_OFFSET + ((Int_Num / FOUR_INT_PRI) * FOUR_BYTE_LENGTH_REG);
		//set priority for specific nvic regester
        (*((volatile unsigned long *)(NVIC_BASE|Offset_Regester))) |= Mask_Address;
    }    
}