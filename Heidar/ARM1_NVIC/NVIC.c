/*
 * NVIC.c
 *
 *      Author: Abdallah Heidar
 */


/********************************************************************************
 * 								  Include Files		    						*
 ********************************************************************************/

#include "NVIC.h"
#include "NVIC_lcfg.h"
#include "privilege.h"
#include "tm4c123gh6pm_registers.h"

/********************************************************************************
 * 								Preprocessor Definitions Macros					*
 ********************************************************************************/

#define USE_COMBINATION(COMB)		(COMB + 4)

/********************************************************************************
 * 								 API Definitions								*
 ********************************************************************************/

void NVIC_Init(void)
{
	uint8_t au8_Counter;
	
	uint8_t au8_numberOfReservedBlocks;
	uint8_t au8_numberOfIntPriBlocks;
	uint8_t au8_numberOfShifts;
	uint8_t au8_priorityBits;

	uint32_t* pu8_PointerToEN_Reg;
	uint32_t* pu8_PointerToPRI_Reg;
	
	IntNumType 				NVIC_IntNum;
	Group_PriorityType 		NVIC_Group_Priority;
	SubGroup_PriorityType	NVIC_SubGroup_Priority;
	
	System_SwitchToPrivileged();
	
	REGISTER(SCB_APINT_R) |= (SCB_APINT_VECTKEY_VALUE << SCB_APINT_VECTKEY_B16)| USE_COMBINATION(REQUIRED_COMBINATION);
	
	for(au8_Counter = 0 ; au8_Counter < NUM_OF_ACTIVATED_INTERRUPTS ; au8_Counter++)
	{
		NVIC_IntNum = NVIC_cfgArr[au8_Counter].IntNum;
		NVIC_Group_Priority = NVIC_cfgArr[au8_Counter].Group_Priority;
		NVIC_SubGroup_Priority = NVIC_cfgArr[au8_Counter].SubGroup_Priority;
		
		pu8_PointerToEN_Reg = (uint32_t*)(&EN_REG) + (NVIC_IntNum / REGISTER_SIZE_IN_BITS);
		
		REGISTER(pu8_PointerToEN_Reg) |= (1 << (NVIC_IntNum % REGISTER_SIZE_IN_BITS));		
		
		pu8_PointerToPRI_Reg = (uint32_t*)(&PRI_REG) + (NVIC_IntNum / REGISTER_SIZE_IN_BYTES);
		
		au8_numberOfIntPriBlocks = NVIC_IntNum % REGISTER_SIZE_IN_BYTES;
		au8_numberOfReservedBlocks = au8_numberOfIntPriBlocks + 1;
		
		au8_numberOfShifts = (au8_numberOfIntPriBlocks * 3) + (au8_numberOfReservedBlocks * 5);
		
		au8_priorityBits = NVIC_SubGroup_Priority | (NVIC_Group_Priority << REQUIRED_COMBINATION);
		
		REGISTER(pu8_PointerToPRI_Reg) |= (au8_priorityBits << au8_numberOfShifts);
	}
	System_SwitchToPrivileged();	
}
