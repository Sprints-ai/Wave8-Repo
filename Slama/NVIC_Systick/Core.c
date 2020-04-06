/*Author : Ahmed Salama
*/

/*Include*/
#include "MCU_hw.h"
#include "NVIC_lcfg.h"
#include "Core.h"
#include "../common_macros.h"
#include "../Error_table.h"

/*Defines*/
#define REG_SIZE (32)
#define VECTKEY_VAL (0x5FA)
#define VECTKEY_POS (16)
#define PRIORITY_GROUP_POS (8)
#define PRIORITY_GROUP_MAX (7)
#define VECTKEY_MASK (0xFFFF)
#define SYSTICK_MASK (0x00FFFFFF) 
#define SYSTICK_CONTROL_MASK (0x07)


/*ProtoTypes*/


ERROR_STATUS NVIC_EnableIRQLink(void)
{
    /*Create Error_Flag*/
    ERROR_STATUS ERR_STATE = E_OK;

    /*Create local variable to check the interrutps*/
    uint8_t u8_loop = ZERO;

    for(u8_loop = 0 ; u8_loop < NUM_OF_ACTIVATED_INTERRUPTS ; u8_loop ++)
    {
        /*Enable Interrupt*/
        NVIC_EnableIRQ(NVIC_CfgArr[u8_loop].IntNum);
        
        /*Set priority*/
        NVIC_SetPriority(NVIC_CfgArr[u8_loop].IntNum , NVIC_CfgArr[u8_loop].Group_Priority);
    }

    /*return ERROR_STATUS*/
    return ERR_STATE;
}

/*Enable IRQ_FUN
*Description : Function that enable the given interrupt number
*Input : Interrupt Number
*Output : ERROR_STATUS
*/
ERROR_STATUS NVIC_EnableIRQ(sint16_t IRQ_Num)
{
    /*Create Error flag*/
    ERROR_STATUS ERR_STATE = E_OK;

    /*check for the irq num*/
    if(IRQ_Num < 0)
    {
        if(IRQ_Num == UsageFault_IRQn)
        {
            /*set the third bit only*/
            SET_BIT(SCB->SHCSR , 3);
        }
        else{
            IRQ_Num = IRQ_Num + 12;

            SET_BIT(SCB->SHCSR , IRQ_Num);
        }
    }

    else{
        /*Create local variable to check the interrupt place*/
    uint8_t u8_interrupt_place;

    u8_interrupt_place = IRQ_Num / ((sint16_t)REG_SIZE);

    if(IRQ_Num >= REG_SIZE)
        IRQ_Num = IRQ_Num - REG_SIZE;

    /*Enable Selected IRQ*/
    NVIC->ISER[u8_interrupt_place] = 1 << (IRQ_Num);
    }
 
    /*Return error status*/
    return ERR_STATE;
}

/*Disable IRQ_FUN
*Description : Used To disable any enabled IRQ
*Input : interrupt Number
*Output : Error_Status
*/
ERROR_STATUS NVIC_DisableIRQ(sint16_t IRQ_Num)
{
    /*Create Error flag*/
    ERROR_STATUS ERR_STATE = E_OK;
    
     /*check for the irq num*/
    if(IRQ_Num < 0)
    {
        if(IRQ_Num == UsageFault_IRQn)
        {
            /*set the third bit only*/
            CLEAR_BIT(SCB->SHCSR , 3);
        }
        else{
            IRQ_Num = IRQ_Num + 12;

            CLEAR_BIT(SCB->SHCSR , IRQ_Num);
        }
    }
    else{
            /*Create local variable to check the interrupt place*/
        uint8_t u8_interrupt_place;

        u8_interrupt_place = IRQ_Num /((sint16_t) REG_SIZE);

        if(IRQ_Num >=REG_SIZE)
            IRQ_Num = IRQ_Num - REG_SIZE;

        /*Enable Selected IRQ*/
        NVIC->ICER[u8_interrupt_place] = 1 << (IRQ_Num);
    }
    
    
    /*Return error status*/
    return ERR_STATE;
}

/*Enable setPeniding_FUN
*Description : Function that Pends any interrupt even if disabled irq
*Input : Interrupt Number
*Output : ERROR_STATUS
*/
ERROR_STATUS NVIC_PendingIRQ(uint8_t IRQ_Num)
{
    /*Create Error flag*/
    ERROR_STATUS ERR_STATE = E_OK;

    /*Create local variable to check the interrupt place*/
    uint8_t u8_interrupt_place;

    u8_interrupt_place = IRQ_Num / REG_SIZE;

    /*Enable Selected IRQ*/
    NVIC->ISPR[u8_interrupt_place] = 1 << (IRQ_Num - REG_SIZE);
    
    /*Return error status*/
    return ERR_STATE;
}

/*Enable Clear Interrupts pending status
*Description : Function that clears the interrupt pending state
*Input : Interrupt Number
*Output : ERROR_STATUS
*/
ERROR_STATUS NVIC_ClearPendingIRQ(uint8_t IRQ_Num)
{
    /*Create Error flag*/
    ERROR_STATUS ERR_STATE = E_OK;

    /*Create local variable to check the interrupt place*/
    uint8_t u8_interrupt_place;

    u8_interrupt_place = IRQ_Num / REG_SIZE;

    /*Enable Selected IRQ*/
    NVIC->ICPR[u8_interrupt_place] = 1 << (IRQ_Num - REG_SIZE);
    
    /*Return error status*/
    return ERR_STATE;
}

/*Setting interrupt priority
*Description : Function to set the irq_num periority
*Input : Interrupt Number
*Output : ERROR_STATUS
*/
ERROR_STATUS NVIC_SetPriority(sint16_t IRQ_Num , uint8_t Priority_Val)
{
    /*Create error flag*/
    ERROR_STATUS ERR_STATE = E_OK;

    /*Check for number as System irq has negative num*/
    if(IRQ_Num < 0)
    {
        /*get the new value of irq
        12 choosed cause of alignment of irq in register
        register is byte accessed so for usage fault num = -12
        and used in first byte*/
        IRQ_Num = 12 + IRQ_Num;

        /*check for it*/
        SCB->SHPR[IRQ_Num] = ((uint8_t)(Priority_Val << 4));

    }

    else{
    /*Set the given priority to that num
    Please realise that register is byte accessible
    and lower 4 bits are reserved*/
    NVIC->IPR[IRQ_Num] = ((uint8_t)(Priority_Val << 4));
    }

    /*Return ERROR*/
    return ERR_STATE;
}

/*Generating Software interrupt
*Description : Function to generate an software irq
*Input : Interrupt Number
*Output : Error_Status
*/
ERROR_STATUS NVIC_SoftwareIRQ(uint8_t IRQ_Num)
{
    /*Create error flag*/
    ERROR_STATUS ERR_STATE = E_OK;

    /*Generate the following interrupt*/
    NVIC->STIR = IRQ_Num;

    return ERR_STATE;
}

/*Enable Global IRQ
*Description : Function to enable all configurable irqs
*Input : NONE
*Output : None
*/
__attribute__((always_inline)) void inline enable_global_irq(void){

    /*write asm instuction to enable IRQ*/
    __asm volatile ("cpsie i");
}

/*Enable Global Faults
*Description : Function to enable all configurable faults
*Input : NONE
*Output : None
*/
__attribute__((always_inline)) void inline enable_global_fault(void){

    /*write asm instuction to enable IRQ*/
    __asm volatile ("cpsie f");
}

/*disable Global IRQ
*Description : Function to disable all configurable irqs
*Input : NONE
*Output : None
*/
__attribute__((always_inline)) void inline disable_global_irq(void){

    /*write asm instuction to enable IRQ*/
    __asm volatile ("cpsid i");
}

/*Disable Global Faults
*Description : Function to disable all configurable faults
*Input : NONE
*Output : None
*/
__attribute__((always_inline)) void inline disable_global_fault(void){

    /*write asm instuction to enable IRQ*/
    __asm volatile ("cpsid f");
}

/*Set BasePri Val
*Description : Function to set base priority value
*Input : BasePri Val
*Output : None
*/
__attribute__((always_inline)) inline void Set_BasePri(uint32_t BasePri_Val)
{
    __asm volatile ("MSR basepri,%0" : : "r" (BasePri_Val));
}

/*Supervisor Call 
*Description : Function to make supervisor call and mainly used
to change from unpriviliged to priviliged
*Input : None
*Output : None
*/
__attribute__((always_inline)) inline void Sv_Call(void)
{
    __asm volatile ("svc");
}

/*Priority Grouping
*Description : Function to determine grouping and sub grouping of priorities
please note that only 4 bits are used for both and only 3 bits used for grouping
note : Writing VECTKEY value is a must to write to AIRCR
*/
ERROR_STATUS NVIC_PriorityGrouping(uint8_t Priority_Group_Val)
{
    /*Create Error Flag*/
    ERROR_STATUS ERR_STATE = E_OK;

    /*Set VECTKEY First to write to AIRCR Reg*/
    SCB->AIRCR &= ~((uint32_t) (VECTKEY_MASK << VECTKEY_POS) | ((uint32_t)(PRIORITY_GROUP_MAX << PRIORITY_GROUP_POS)));
    SCB->AIRCR |= ((uint32_t) (VECTKEY_VAL << VECTKEY_POS));

    /*write Priority Grouping*/
    SCB->AIRCR |= ((uint32_t ) (Priority_Group_Val << PRIORITY_GROUP_POS));

    return ERR_STATE;
}

/*Systick Val
*Description : Function to set the tick value
*Input : Tick Value
*Output : NONE
*/

ERROR_STATUS Systick_Config(uint32_t Sys_Val)
{
    ERROR_STATUS ERR_STATE = E_OK;

    /*check for inserted Value*/
    if(Sys_Val > SYSTICK_MASK)
    {
        ERR_STATE = ERROR_SYSTICK_BASE + ERROR_WRONG_SYSTICK_VAL;
    }
    else{
    /*First clear and set the value*/
    SYSTICK->STCK_RVR &= ~SYSTICK_MASK;
    SYSTICK->STCK_RVR |= Sys_Val;

    /*clear Control Register then enable it*/
    SYSTICK->STCK_CSR &= ~((uint32_t) SYSTICK_CONTROL_MASK);
    SYSTICK->STCK_CSR |= ((uint32_t) SYSTICK_CONTROL_MASK);
    }

    return ERR_STATE;
}
