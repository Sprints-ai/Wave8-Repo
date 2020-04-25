

/**************************************************************************************/
/*					NVIC.c														      */
/**************************************************************************************/

#include "NVIC.h"
#include "NVIC_Lcfg.h"
#include "MCU_HW.h"
#include "std_types.h"


#define GROUP_SUBGROUP_MASK1 0x05FA0700
#define GROUP_SUBGROUP_MASK2 0x05FA0600
#define GROUP_SUBGROUP_MASK3 0x05FA0500
#define GROUP_SUBGROUP_MASK4 0x05FA0400

#define APINT_CLEAR_MASK 0xFFFF0000


#define  INT_PARIORITY_FIRST_ADDRESS 0xE000E400

void NVIC_init(void)
{
	IntNumType NVIC_IntNum;
	Group_PriorityType NVIC_Group_Priority;
	SubGroup_PriorityType	NVIC_SubGroup_Priority;
	uint32_t counter , offset , reg_number ;
	uint32_t  * Periorty_start_offset , * Periorty_current_offset  ;
	uint8_t shift_bits_group , shift_bits_subgroup;
	

	/*TODO Set Combination in APINT  xxx xxy xyy yyy*/
	/* set the binary point to have xx.y then put 0x5 in the 10:8 bits*/
	/* set special 0x05FA in 31:16 bits before change in this register  */
	
	Periorty_start_offset = (uint32_t *)INT_PARIORITY_FIRST_ADDRESS  ;
		
	
	switch(NUM_OF_GROUP_PARIORITY/2)
		{
			/* 0x7 --- yyy , [] 0->group , [7:5]  8->subgroup  */
			case 0 :
			APINT = (APINT &(~(APINT_CLEAR_MASK)))| GROUP_SUBGROUP_MASK1 ;
			break;
			
			/* 0x6 --- x.yy , [7] 2->group , [6:5]  4->subgroup  */
			case 1 :
			APINT = (APINT &(~(APINT_CLEAR_MASK)))| GROUP_SUBGROUP_MASK2 ;
			break;
			
			/* 0x5 --- xx.y , [7:6] 4->group , [5]  2->subgroup  */
			case 2 :
			APINT = (APINT &(~(APINT_CLEAR_MASK)))| GROUP_SUBGROUP_MASK3 ;
			break ;
			
			/* 0x4 --- xxx , [7:5] 8->group , []  0->subgroup  */
			case 3 :
			APINT = (APINT &(~(APINT_CLEAR_MASK)))| GROUP_SUBGROUP_MASK4 ;
			break;
			
		}
	
	

	for(counter=0; counter < NUM_OF_ACTIVATED_INTERRUPTS ; counter++)
	{
		NVIC_IntNum = NVIC_CfgArr[counter].IntNum;
		NVIC_Group_Priority = NVIC_CfgArr[counter].Group_Priority;
		NVIC_SubGroup_Priority = NVIC_CfgArr[counter].SubGroup_Priority;
		
		/*TODO Enable Interrupt */
		switch(NVIC_IntNum/32)
		{
			case 0 :
				EN0 |=  (1<<(NVIC_IntNum%32));
				break;
			case 1 :
				EN1 |=  (1<<(NVIC_IntNum%32));
				break;
			case 2 :
				EN2 |=  (1<<(NVIC_IntNum%32));
				break;
			case 3 :
				EN3 |=  (1<<(NVIC_IntNum%32));
				break;
			case 4 :
				EN4 |=  (1<<(NVIC_IntNum%32));
				break;
			
		}
		
		/*TODO Set Priority Group/SubGroup*/
		
		reg_number = NVIC_IntNum/4 ;
		offset = reg_number ;
		Periorty_current_offset = Periorty_start_offset  + offset ;
		
		
		switch(NUM_OF_GROUP_PARIORITY/2)
		{
			/* 0x7 --- yyy , [] 0->group , [7:5]  8->subgroup  */
			case 0 :
			shift_bits_group = 5 ;
			shift_bits_subgroup = 2 ;
			break;
			
			/* 0x6 --- x.yy , [7] 2->group , [6:5]  4->subgroup  */
			case 1 :
			shift_bits_group = 0 ;
			shift_bits_subgroup = 2 ;
			break;
			
			/* 0x5 --- xx.y , [7:6] 4->group , [5]  2->subgroup  */
			case 2 :
			shift_bits_group = 1 ; //
			shift_bits_subgroup = 2 ;
			break ;
			
			/* 0x4 --- xxx , [7:5] 8->group , []  0->subgroup  */
			case 3 :
			shift_bits_group = 2 ;
			shift_bits_subgroup = 5 ;
			break;
			
		}
		
		
			
			if( NVIC_IntNum ==  reg_number*4) 
			{
				
				if (shift_bits_group<3)
					*Periorty_current_offset |= NVIC_Group_Priority<<(7-shift_bits_group) ;	
				if (shift_bits_subgroup<3)
					*Periorty_current_offset |= NVIC_SubGroup_Priority<<(7-shift_bits_subgroup) ;
					
			}
			else if(NVIC_IntNum == (reg_number*4)+1 )
			{
				if (shift_bits_group<3)
					*Periorty_current_offset |= NVIC_Group_Priority<<(15-shift_bits_group) ;
				if (shift_bits_subgroup<3)
					*Periorty_current_offset |= NVIC_SubGroup_Priority<<(15-shift_bits_subgroup) ;
			}
			
			else if (NVIC_IntNum == (reg_number*4)+2 )
			{ 
				if (shift_bits_group<3)
					*Periorty_current_offset |= NVIC_Group_Priority<<(23-shift_bits_group) ;
				if (shift_bits_subgroup<3)
					*Periorty_current_offset |= NVIC_SubGroup_Priority<<(23-shift_bits_subgroup) ;
			}
			
			else if (NVIC_IntNum == (reg_number*4)+3)
			{	
				if (shift_bits_group<3)
					*Periorty_current_offset|= NVIC_Group_Priority<<(31 -shift_bits_group) ;
				if (shift_bits_subgroup<3)
					*Periorty_current_offset|= NVIC_SubGroup_Priority<<(31 -shift_bits_subgroup) ;
			}
	}	
}




