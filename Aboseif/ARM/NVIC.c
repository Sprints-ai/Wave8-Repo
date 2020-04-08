/*
 * NVIC.c
 *
 * Created: 2020-04-03 12:20:42 AM
 *  Author: EbrahimOseif
 */


/************************************************************************/
/*				               INCLUDES			                        */
/************************************************************************/

#include "MCU_hw.h"
#include "NVIC.h"


/************************************************************************/
/*				       function implementation			                */
/************************************************************************/

void NVIC_Init(void)
{
	uint8_t u8_counter=0, u8_priorityRegNum, u8_IntBitNum, u8_PriIntNum, u8_IntRegNum;
	
	uint32_t u32_priorityVal;
	volatile uint32_t * prioriy_ptr;
	volatile uint32_t * IntEN_ptr;
 
	prioriy_ptr = &NVIC_PRI0_R;
	IntEN_ptr   = &NVIC_EN0_R;



	if(NUM_OF_ACTIVATED_INTERRUPTS > 0)
	{
		
		
		__asm("MOV R0,#0X00000000");
		__asm("MSR BASEPRI,R0");
		__asm("MOV R1,#0X00000000");
		__asm("MSR PRIMASK,R1");

		NVIC_APINT_R |= APINT_VECTKEY | APINT_PRIGROUP;
		
		
		for(u8_counter = 0 ; u8_counter < NUM_OF_ACTIVATED_INTERRUPTS ; u8_counter++)
		{
			/* Enable the interrupt */
			
			/* calculate the interrupt register number and bit number */
			
			u8_IntRegNum = (NVIC_CfgArr[u8_i].IntNum / INT_EN_LENGTH);
			u8_IntBitNum = NVIC_CfgArr[u8_i].IntNum - (u8_IntRegNum * INT_EN_LENGTH);
			*(IntEN_ptr + ((u8_IntRegNum))) |= 1 << u8_IntBitNum;

			/* Set the priority of the interrupt */ 
			
			/*1-  calculate the priority register number and bit number */
			
			u8_priorityRegNum  = (NVIC_CfgArr[u8_i].IntNum / INT_PRI_LENGHT);
			u8_PriIntNum 	   = (NVIC_CfgArr[u8_i].IntNum - (u8_priorityRegNum * INT_PRI_LENGHT));
			u32_priorityVal    = (NVIC_CfgArr[u8_i].Group_Priority | NVIC_CfgArr[u8_i].SubGroup_Priority);

			switch(u8_PriIntNum)
			{
				case PRI_INTA:
					u32_priorityVal <<= PRI_START_INDEX_INTA;
					break;
				case PRI_INTB:
					u32_priorityVal <<= PRI_START_INDEX_INTB;
					break;
				case PRI_INTC:
					u32_priorityVal <<= PRI_START_INDEX_INTC;
					break;
			}
			/*2-  Set the priority of the interrupt */ 

		 *(prioriy_ptr + ((u8_priorityRegNum))) |= u32_priorityVal;


		}
	}
	else{
		
		
		/* nothing yet */
	}
	
}
