/*
 * NVIC.c
 *
 * Created: 4/3/2020 2:23:35 PM
 *  Author: A_ayman
 */ 

/*
*** INCLUSIONS
*/
#include "NVIC.h"


/*
*** CONSTANTS
*/

#define REG_BIT_COUNT       32

/*
*** Local Macros
*/

/* NVIC priority Registers Mask values */
#define NVIC_PRI_P0_M       0x000000E0
#define NVIC_PRI_P1_M       0x0000E000  
#define NVIC_PRI_P2_M       0x00E00000 
#define NVIC_PRI_P3_M 		 0xE0000000 

/* NVIC priority Registers Shift values */
#define NVIC_PRI_P0_S		 5 			
#define NVIC_PRI_P1_S	  	 13
#define NVIC_PRI_P2_S		 21
#define NVIC_PRI_P3_S 		 29


//array of volatile unsigned long  contains Priority Registers//
volatile unsigned long*  u32_Priority_Reg_Arr[35]={&NVIC_PRI0_R, &NVIC_PRI1_R, &NVIC_PRI2_R, &NVIC_PRI3_R, &NVIC_PRI4_R, &NVIC_PRI5_R, &NVIC_PRI6_R, &NVIC_PRI7_R, &NVIC_PRI8_R, &NVIC_PRI9_R, &NVIC_PRI10_R, &NVIC_PRI11_R, &NVIC_PRI12_R, &NVIC_PRI13_R, &NVIC_PRI14_R, &NVIC_PRI15_R, &NVIC_PRI16_R, &NVIC_PRI17_R, &NVIC_PRI18_R, &NVIC_PRI19_R, &NVIC_PRI20_R, &NVIC_PRI21_R, &NVIC_PRI22_R, &NVIC_PRI23_R, &NVIC_PRI24_R, &NVIC_PRI25_R, &NVIC_PRI26_R, &NVIC_PRI27_R, &NVIC_PRI28_R, &NVIC_PRI29_R, &NVIC_PRI30_R, &NVIC_PRI31_R, &NVIC_PRI32_R, &NVIC_PRI33_R, &NVIC_PRI34_R};
//array of Priority Shift Values//
uint32_t u32_Priority_Shift_Arr[4]={NVIC_PRI_P0_S,NVIC_PRI_P1_S,NVIC_PRI_P2_S,NVIC_PRI_P3_S };
//array of Priority Mask Values//	
uint32_t u32_Priority_Mask_Arr[4]={NVIC_PRI_P0_M,NVIC_PRI_P1_M,NVIC_PRI_P2_M,NVIC_PRI_P3_M };

/* Local Function Prototypes */
static void NVIC_SetPrioroty_IRQ (uint8_t IRQ_Numb,uint8_t Priority_Level );
static void NVIC_Enable_IRQ (uint8_t IRQ_Numb);

/*
*** this function is responsible to initialize NVIC, By setting APINT combination
*** Enable Interrupt and set priority
*/

void NVIC_Init(void)
{
	uint8_t  au8_Loop_Counter;
	INT_Numb_t    NVIC_IntNum;
	Group_Priority_t    NVIC_Group_Priority;
	SubGroup_Priority_t   	NVIC_SubGroup_Priority;
	
	/*Set Combination in APINT  XXX XXY XYY YYY*/
	switch (APINT_Combination)
	{
		case bxxx_:                 /* this case is to set combination with 8 group and only 0 sub group*/
		NVIC_APINT_R = 0x05FA0000 ;
		break;
		default:
		break;
	}
		
	for(au8_Loop_Counter=0; au8_Loop_Counter<NUM_OF_ACTIVATED_INTERRUPTS; au8_Loop_Counter++)
	{
		NVIC_IntNum = NVIC_CfgArr[au8_Loop_Counter].u8_INT_Num;
		NVIC_Group_Priority = NVIC_CfgArr[au8_Loop_Counter].u8_Group_Priority;
		NVIC_SubGroup_Priority = NVIC_CfgArr[au8_Loop_Counter].u8_SubGroup_Priority;
		
		/*Enable Interrupt*/
		NVIC_Enable_IRQ (NVIC_IntNum );
		
		/*Set Priority Group/SubGroup*/
		switch (APINT_Combination)					/* to determine which mode we are going to apply*/
	   {
			case bxxx_:
			NVIC_SetPrioroty_IRQ (NVIC_IntNum,NVIC_Group_Priority);
			break;
			default:
			break;
	   }
	}	
}

/*
*** this function is used to Enable Interrupt for a given interrupt
*/
static void NVIC_Enable_IRQ (uint8_t IRQ_Numb)
{
	uint8_t IRQ_REG_Enalble ;
	uint8_t Bit_Shift;
	uint8_t IRQ_Bit_Enable;
	
	/*Determine The Reg We want to Enable */
	IRQ_REG_Enalble  = IRQ_Numb / REG_BIT_COUNT;   /* for example 2/32 = 0*/
	Bit_Shift = IRQ_REG_Enalble * REG_BIT_COUNT;  
	IRQ_Bit_Enable = IRQ_Numb - Bit_Shift ;
	switch (IRQ_REG_Enalble )
	{
		case 0: SET_BIT(NVIC_EN0_R ,IRQ_Bit_Enable ); break;
		case 1: SET_BIT(NVIC_EN1_R ,IRQ_Bit_Enable ); break;
		case 2: SET_BIT(NVIC_EN2_R ,IRQ_Bit_Enable ); break;
		case 3: SET_BIT(NVIC_EN3_R ,IRQ_Bit_Enable ); break;
		case 4: SET_BIT(NVIC_EN4_R ,IRQ_Bit_Enable ); break;
	}
}


/*
	PRIx provide 3-bit priority fields for each interrupt.
	These registers are byte accessible. 
	Each register holds four priority field
	so for each Interrupt we have to determine 
	1- the corresponding priority register 
	2- the accurate position 
*/
static void NVIC_SetPrioroty_IRQ (uint8_t IRQ_Numb,uint8_t Priority_Level )
{
	uint8_t IRQ_Pri_REG;
	uint8_t IRQ_Pri_Mask;
	uint8_t IRQ_Pri_Shift;
	
	IRQ_Pri_REG = IRQ_Numb/4;    // to get the the corresponding priority register 
	IRQ_Pri_Mask = IRQ_Numb%4;   // to get the accurate position
	IRQ_Pri_Shift = IRQ_Numb%4;
	
	*u32_Priority_Reg_Arr[IRQ_Pri_REG] &= ~ u32_Priority_Mask_Arr[IRQ_Pri_Mask ];   //clear the corresponding bits for the  determined priority bits
	*u32_Priority_Reg_Arr[IRQ_Pri_REG] |= (Priority_Level<<u32_Priority_Shift_Arr[IRQ_Pri_Shift]);

	// another way to access priority registers//
	/*switch (IRQ_Pri_REG)
	{
		//case 0: IRQ_Pri_REG = NVIC_PRI0_R; break;
		case 0: //PRI0
		{
			switch (IRQ_Pri_Mask)
			{
				case 0:
				{
					NVIC_PRI0_R &= ~ NVIC_PRI_P0_M;
					NVIC_PRI0_R |= (Priority_Level << NVIC_PRI_P0_S);
					break;
				}
				case 1:
				{
					NVIC_PRI0_R &= ~ NVIC_PRI_P1_M;
					NVIC_PRI0_R |= (Priority_Level << NVIC_PRI_P1_S);
					break;
				}
				case 2:
				{
					NVIC_PRI0_R &= ~ NVIC_PRI_P2_M;
					NVIC_PRI0_R |= (Priority_Level << NVIC_PRI_P2_S);
					break;
				}
				case 3:
				{
					NVIC_PRI0_R &= ~ NVIC_PRI_P3_M;
					NVIC_PRI0_R |= (Priority_Level << NVIC_PRI_P3_S);
					break;
				}
				default:
				break;
			}	
		}*/
}
	
	
	


