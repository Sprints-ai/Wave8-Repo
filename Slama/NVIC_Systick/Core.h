/*Author : Ahmed Salama
*/

#ifndef NVIC_H
#define NVIC_H

#include "../std_types.h"

extern ERROR_STATUS NVIC_EnableIRQLink(void);

/*Enable IRQ_FUN
*Description : Function that enable the given interrupt number
*Input : Interrupt Number
*Output : ERROR_STATUS
*/
extern ERROR_STATUS NVIC_EnableIRQ(sint16_t IRQ_Num);

/*Disable IRQ_FUN
*Description : Used To disable any enabled IRQ
*Input : interrupt Number
*Output : Error_Status
*/
extern ERROR_STATUS NVIC_DisableIRQ(sint16_t IRQ_Num);

/*Enable setPeniding_FUN
*Description : Function that Pends any interrupt even if disabled irq
*Input : Interrupt Number
*Output : ERROR_STATUS
*/
extern ERROR_STATUS NVIC_PendingIRQ(uint8_t IRQ_Num);

/*Enable Clear Interrupts pending status
*Description : Function that clears the interrupt pending state
*Input : Interrupt Number
*Output : ERROR_STATUS
*/
extern ERROR_STATUS NVIC_ClearPendingIRQ(uint8_t IRQ_Num);

/*Setting interrupt priority
*Description : Function to set the irq_num periority
*Input : Interrupt Number
*Output : ERROR_STATUS
*/
extern ERROR_STATUS NVIC_SetPriority(sint16_t IRQ_Num , uint8_t Priority_Val);

/*Generating Software interrupt
*Description : Function to generate an software irq
*Input : Interrupt Number
*Output : Error_Status
*/
extern ERROR_STATUS NVIC_SoftwareIRQ(uint8_t IRQ_Num);

/*Enable Global IRQ
*Description : Function to enable all configurable irqs
*Input : NONE
*Output : None
*/
__attribute__((always_inline)) void inline enable_global_irq(void);

/*Enable Global Faults
*Description : Function to enable all configurable faults
*Input : NONE
*Output : None
*/
__attribute__((always_inline)) void inline enable_global_fault(void);

/*disable Global IRQ
*Description : Function to disable all configurable irqs
*Input : NONE
*Output : None
*/
__attribute__((always_inline)) void inline disable_global_irq(void);

/*Disable Global Faults
*Description : Function to disable all configurable faults
*Input : NONE
*Output : None
*/
__attribute__((always_inline)) void inline disable_global_fault(void);

/*Set BasePri Val
*Description : Function to set base priority value
*Input : BasePri Val
*Output : None
*/
__attribute__((always_inline)) inline void Set_BasePri(uint32_t BasePri_Val);

/*Supervisor Call 
*Description : Function to make supervisor call and mainly used
to change from unpriviliged to priviliged
*Input : None
*Output : None
*/
__attribute__((always_inline)) inline void Sv_Call(void);

/*Priority Grouping
*Description : Function to determine grouping and sub grouping of priorities
please note that only 4 bits are used for both and only 3 bits used for grouping
note : Writing VECTKEY value is a must to write to AIRCR
*/
ERROR_STATUS NVIC_PriorityGrouping(uint8_t Priority_Group_Val);

/*Systick Val
*Description : Function to set the tick value
*Input : Tick Value
*Output : NONE
*/

ERROR_STATUS Systick_Config(uint32_t Sys_Val);
#endif
