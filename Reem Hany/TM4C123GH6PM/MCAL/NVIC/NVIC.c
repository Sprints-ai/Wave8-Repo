#include "../includes/MCU_hw.h"
#include "../includes/NVIC.h"
#include "../includes/NVIC_lCfg.h"

/**************************************************/
/*              Static Defines                    */
/**************************************************/
#define INT_EN_LEN                     32
#define INT_PRI_LEN                    4


#define PRI_INTA                       0
#define PRI_INTB                       1
#define PRI_INTC                       2
#define PRI_INTD                       3

#define PRI_START_INDEX_INTA           5
#define PRI_START_INDEX_INTB           13
#define PRI_START_INDEX_INTC           21
#define PRI_START_INDEX_INTD           29


void NVIC_Init(void)
{
	uint8_t u8_i=0, u8_priorityRegNum, u8_intBitNum,u8_PriIntNum, u8_intRegNum;
	uint32_t u32_priorityVal;
	volatile uint32_t * prioriy_ptr;
	volatile uint32_t * IntEN_ptr;
  prioriy_ptr = &NVIC_PRI0_R;
  IntEN_ptr = &NVIC_EN0_R;
	
	
	
	if(NUM_OF_ACTIVATED_INTERRUPTS>0)
	{
		
		/*Set the apint*/
		NVIC_APINT_R |= APINT_VECTKEY | APINT_PRIGROUP;
		/*EN the interrupt and set the priority*/
		for(u8_i = 0 ; u8_i < NUM_OF_ACTIVATED_INTERRUPTS ; u8_i++)
		{
			//EN the interrupt x
			u8_intRegNum = (NVIC_CfgArr[u8_i].IntNum / INT_EN_LEN);//Get the reg. number
			u8_intBitNum = NVIC_CfgArr[u8_i].IntNum - (u8_intRegNum * INT_EN_LEN);//Get the bit. number
			
			*(IntEN_ptr + ((u8_intRegNum))) |= ONE << u8_intBitNum;
			
			//Set the priority of the interrupt x
			u8_priorityRegNum  = (NVIC_CfgArr[u8_i].IntNum / INT_PRI_LEN);//Get the reg. number
			u8_PriIntNum = (NVIC_CfgArr[u8_i].IntNum - (u8_priorityRegNum * INT_PRI_LEN));//Get the INT. number inthe reg
			u32_priorityVal = (NVIC_CfgArr[u8_i].Group_Priority|NVIC_CfgArr[u8_i].SubGroup_Priority);
			
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
				case PRI_INTD:
					u32_priorityVal <<= PRI_START_INDEX_INTD;
					break;
			}
		 *(prioriy_ptr + ((u8_priorityRegNum))) |= u32_priorityVal;
			
			
		}
	}
}
