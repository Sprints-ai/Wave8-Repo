
#include "../../utils/Std_Types.h"
#include "../../utils/Bit_Math.h"


#include "../../config/nvic_cfg.h"
#include "../mcu_hw.h"
#include "nvic_types.h"
#include "nvic.h"

#define INIT_VALUE_ZERO                     (0)

#define VALUE_ZERO                          (0)
#define VALUE_ONE                           (1)
#define VALUE_TWO                           (2)
#define VALUE_THREE                         (3)

#define NVIC_EN_REG_ADD(INT_NO)             ((volatile uint32*)(((INT_NO/32) * 4) + (uint32)NVIC_EN_BASE_ADD))
#define NVIC_EN_INT_BIT(INT_NO)             (INT_NO % 32)

#define NVIC_PRI_REG_ADD(INT_NO)            (((volatile uint32*)((((INT_NO)/4) * 4) + (uint32)NVIC_PRI_BASE_ADD)))
#define NVIC_PRI_INT_BIT(INT_NO)            (INT_NO % 4)

extern NVIC_CfgType NVIC_CfgArr[];

uint32 NVIC_CfgPriGrp = NVIC_CHOSEN_GRP_SUB;

void NVIC_init(void)
{
    /*TODO : switch to privilege mode - use switch function in processor.h*/

    /*TODO :loop for NVIC_CfgArr configure each Interrupt
     *  as stated in Cfg (Enable/Priority/sub-priority)
     *
     */
    uint32 u32_NvicIterator = INIT_VALUE_ZERO;

    volatile uint32* ptr_IntReg = NULL;

    uint32 u32_Int_no = INIT_VALUE_ZERO;

    for (u32_NvicIterator = INIT_VALUE_ZERO;
            u32_NvicIterator < NVIC_NUM_OF_ENABLED_INT; u32_NvicIterator++)
    {

        ptr_IntReg = NVIC_EN_REG_ADD(
                NVIC_CfgArr[u32_NvicIterator].Interrupt_NO);

        u32_Int_no = NVIC_EN_INT_BIT(
                NVIC_CfgArr[u32_NvicIterator].Interrupt_NO);

        *ptr_IntReg = *ptr_IntReg | (VALUE_ONE << u32_Int_no);

        str_NVIC_PRI_REG* ptr_NvicPriReg = (str_NVIC_PRI_REG*)NVIC_PRI_REG_ADD(
                NVIC_CfgArr[u32_NvicIterator].Interrupt_NO);

        uint32 Nvic_GP = NVIC_CfgArr[u32_NvicIterator].Interrupt_PriorityGroup;
        uint32 Nvic_SP =
                NVIC_CfgArr[u32_NvicIterator].Interrupt_SubPriorityGroup;
        uint32 Nvic_PriorityConfg = INIT_VALUE_ZERO;
        if (NVIC_CfgPriGrp == NVIC_PRI_GRP_XXX)
        {
            Nvic_PriorityConfg = Nvic_GP;
        }

        else if (NVIC_CfgPriGrp == NVIC_PRI_GRP_XXY)
        {
            Nvic_PriorityConfg = Nvic_GP;
            Nvic_PriorityConfg = (Nvic_PriorityConfg << VALUE_ONE) | Nvic_SP;
        }

        else if (NVIC_CfgPriGrp == NVIC_PRI_GRP_XYY)
        {
            Nvic_PriorityConfg = Nvic_GP;
            Nvic_PriorityConfg = (Nvic_PriorityConfg << VALUE_TWO) | Nvic_SP;
        }

        else if (NVIC_CfgPriGrp == NVIC_PRI_GRP_YYY)
        {
            Nvic_PriorityConfg = Nvic_GP;
        }

        switch (NVIC_PRI_INT_BIT(NVIC_CfgArr[u32_NvicIterator].Interrupt_NO))
        {
        case VALUE_ZERO:
            (*ptr_NvicPriReg).INTA = Nvic_PriorityConfg;
            break;
        case VALUE_ONE:
            (*ptr_NvicPriReg).INTB = Nvic_PriorityConfg;
            break;
        case VALUE_TWO:
            (*ptr_NvicPriReg).INTC = Nvic_PriorityConfg;
            break;
        case VALUE_THREE:
            (*ptr_NvicPriReg).INTD = Nvic_PriorityConfg;
            break;
        }
        /*TODO : return to non-privilege mode */

    }

}
