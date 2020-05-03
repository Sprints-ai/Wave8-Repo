/**************************************************************************************/
/*					NVIC.c														      */
/**************************************************************************************/

#include "NVIC.h"




#define SUBPRIORITY_GROUP_NU_MOODE_0		0 
#define SUBPRIORITY_GROUP_NU_MOODE_1		1 
#define SUBPRIORITY_GROUP_NU_MOODE_2		3 
#define SUBPRIORITY_GROUP_NU_MOODE_3		7 

#define RIORITYNU_GROUP_NU_MOODE_0		7		
#define RIORITYNU_GROUP_NU_MOODE_1		3		
#define RIORITYNU_GROUP_NU_MOODE_2		1		
#define RIORITYNU_GROUP_NU_MOODE_3		0		

#define ZERO							0

#define ENABLE							1
#define PTI_MODE_ZERO 					0
#define PTI_MODE_ONE 					1
#define PTI_MODE_TWO 					2
#define PTI_MODE_THREE 					3


void NVIC_init(void)
{
	IntNumType NVIC_IntNum;
	Group_PriorityType NVIC_Group_Priority;
	
	SubGroup_PriorityType	NVIC_SubGroup_Priority;
	
	uint8_t u8_MaxPriorityGroupNu = RIORITYNU_GROUP_NU_MOODE_0, u8_MaxSubPriorityGroupNu = SUBPRIORITY_GROUP_NU_MOODE_0,
			u8_RegisterNU = ZERO , u8_BIT_NU =ZERO , u8_BYTE_NU =ZERO  , u8_PriorityValue = ZERO,u8_PRI_Mode = ZERO ,  INT_Index = ZERO ; 
	
	
	/*TODO Set Combination in APINT  xxx xxy xyy yyy*/
	
	#if ( INT_GR_MODE == INT_GR_MOODE_0 )	
		
		#define NTI_GR_PRI_MOODE	0x05FA0400
		u8_PRI_Mode = PTI_MODE_ZERO 	 ;
		
	#elif (INT_GR_MODE == INT_GR_MOODE_1)
		
		#define NTI_GR_PRI_MOODE	0x05FA0500
		
		u8_MaxPriorityGroupNu = RIORITYNU_GROUP_NU_MOODE_1;
		
		u8_MaxSubPriorityGroupNu = SUBPRIORITY_GROUP_NU_MOODE_1;
		
		u8_PRI_Mode = PTI_MODE_ONE 	 ;
		
	#elif (INT_GR_MODE == INT_GR_MOODE_2)
		
		#define NTI_GR_PRI_MOODE	0x05FA0600
		
		u8_MaxPriorityGroupNu = RIORITYNU_GROUP_NU_MOODE_2;
		
		u8_MaxSubPriorityGroupNu = SUBPRIORITY_GROUP_NU_MOODE_2;
		
		u8_PRI_Mode =  PTI_MODE_TWO ;
		
	#elif (INT_GR_MODE == INT_GR_MOODE_3)
		
		#define NTI_GR_PRI_MOODE	0x05FA0700
		
		u8_MaxPriorityGroupNu = RIORITYNU_GROUP_NU_MOODE_3;
		
		u8_MaxSubPriorityGroupNu = SUBPRIORITY_GROUP_NU_MOODE_3;
		
		u8_PRI_Mode =  PTI_MODE_THREE ;
		
	#else 
		
		#define NTI_GR_PRI_MOODE	0x05FA0000
		
		u8_PRI_Mode =  PTI_MODE_ZERO ;
		
	#endif
	
	APINT_REG=	NTI_GR_PRI_MOODE;

	for( ; INT_Index < NUM_OF_ACTIVATED_INTERRUPTS ; INT_Index++)
	{
		NVIC_IntNum = NVIC_CfgArr[INT_Index].IntNum ;
		
		NVIC_Group_Priority = NVIC_CfgArr[INT_Index].Group_Priority;
		
		NVIC_SubGroup_Priority = NVIC_CfgArr[INT_Index].SubGroup_Priority;
		
		u8_RegisterNU = NVIC_IntNum /32 ;
		
		u8_BIT_NU =  NVIC_IntNum % 32 ;
		
		/*TODO Enable Interrupt */
		
		*((&EN0_REG) + u8_RegisterNU) = (ENABLE << u8_BIT_NU ) ;
		/*TODO Set Priority Group/SubGroup*/
		if( NVIC_Group_Priority <= u8_MaxPriorityGroupNu)
		{
			if(NVIC_SubGroup_Priority <= u8_MaxSubPriorityGroupNu)
			{
				u8_PriorityValue = ((NVIC_Group_Priority<<u8_PRI_Mode) |NVIC_SubGroup_Priority )<<5;
				
				u8_RegisterNU = NVIC_IntNum /4 ;
		
				u8_BYTE_NU =  NVIC_IntNum % 4 ;
				*(( volatile uint8_t *)((&PRI0_REG) + u8_RegisterNU) +  u8_BYTE_NU) = u8_PriorityValue ;
			}
			else 
			{
				//sending wrong subpriority number
			}
		}
		
		else 
		{
			//sending wrong Group priority number
		}
			
		
	}	
}       

