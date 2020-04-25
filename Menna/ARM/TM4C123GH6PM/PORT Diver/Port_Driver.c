/*****************************************************************************/
/*					Port.c												 */	
/*****************************************************************************/
#include "PortDriver_lCfg.h"
#include "MCU_HW.h"

#define NUM_OF_CHANNELS_IN_PORT							8
#define NUM_OF_PORTS 6
#define UNLOCK_KEY 0x4C4F434B

uint32_t BaseAddrArr[NUM_OF_PORTS] = {
									GPIO_PORT_A_APB,
									GPIO_PORT_B_APB,
									GPIO_PORT_C_APB,
									GPIO_PORT_D_APB,
									GPIO_PORT_E_APB,
									GPIO_PORT_F_APB};

void PortDriver_init(void)
{

	uint8_t counter = 0 , ChannelOffset;
	PortDriver_PortNumType PortNum;
	PortDriver_ChannelType ChannelNum;
	uint32_t GPIO_LOCK_Add , GPIOPCTL_Add , GPIOADCCTL_Add ,GPIODMACTL_Add  ;
	/* unlock the GPIOLOCK reg*/

	
	GPIOLOCK(BaseAddrArr[PortNum]) = UNLOCK_KEY ;
	
	for(counter = 0 ; counter <NUM_OF_ACTIVATED_CHANNELS ; counter ++){
	
		ChannelNum = PortDriver_CfgArr[counter].Channel;
		PortNum = ChannelNum / NUM_OF_CHANNELS_IN_PORT;
		ChannelOffset = ChannelNum% NUM_OF_CHANNELS_IN_PORT;
		
		/*UNLOCK the GPIOCR pin reg*/
		SET_BIT( GPIOCR(BaseAddrArr[PortNum]),ChannelOffset);
		
		/*gpio direction*/
		
		if(PortDriver_CfgArr[counter].PortDriver_Channel_Direction == PortDriver_Channel_Direction_INPUT )
		{		
			CLEAR_BIT(GPIODIR(BaseAddrArr[PortNum]),ChannelOffset);
		}
		else if(PortDriver_CfgArr[counter].PortDriver_Channel_Direction == PortDriver_Channel_Direction_OUTPUT)
		{
			SET_BIT(GPIODIR(BaseAddrArr[PortNum]),ChannelOffset);
		}	
		
		/*gpio current control GOIOR2R */
		
				if(PortDriver_CfgArr[counter].PortDriver_Channel_Current_mA == PortDriver_Channel_Current_mA_2 )
		{		
			SET_BIT(GPIODR2R(BaseAddrArr[PortNum]),ChannelOffset);
		}
		else if(PortDriver_CfgArr[counter].PortDriver_Channel_Current_mA == PortDriver_Channel_Current_mA_4)
		{
			SET_BIT(GPIODR4R(BaseAddrArr[PortNum]),ChannelOffset);
		}	
		else if(PortDriver_CfgArr[counter].PortDriver_Channel_Current_mA == PortDriver_Channel_Current_mA_8)
		{
			SET_BIT(GPIODR8R(BaseAddrArr[PortNum]),ChannelOffset);
		}	
		
		/*gpio slew rate GPIOSLR*/
		if(PortDriver_CfgArr[counter].PortDriver_Channel_SlewRate == PortDriver_Channel_SlewRate_Enable )
		{		
			SET_BIT(GPIOSLR(BaseAddrArr[PortNum]),ChannelOffset);
		}
		/* pull up OR pull down OR open drain */
		if(PortDriver_CfgArr[counter].PortDriver_Channel_Attachment == PortDriver_Channel_Attachment_PullupRes )
		{		
			SET_BIT(GPIOPUR(BaseAddrArr[PortNum]),ChannelOffset);
		}
		else if(PortDriver_CfgArr[counter].PortDriver_Channel_Attachment == PortDriver_Channel_Attachment_PullDownRes)
		{
			SET_BIT(GPIOPDR(BaseAddrArr[PortNum]),ChannelOffset);
		}	
		else if(PortDriver_CfgArr[counter].PortDriver_Channel_Attachment == PortDriver_Channel_Attachment_openDrain)
		{
			SET_BIT(GPIOODR(BaseAddrArr[PortNum]),ChannelOffset);
		}	
		
		
		/*******BASE FUNCTION or ALTERNATIVE FUNCTION REGISTERS******/
	
		if(PortDriver_CfgArr[counter].PortDriver_Channel_Function == PortDriver_Channel_Function_X_DIO)
				/*GPIO AFSEL*/
			CLEAR_BIT(GPIOAFSEL(BaseAddrArr[PortNum]),ChannelOffset);
		else if (PortDriver_CfgArr[counter].PortDriver_Channel_Function == PortDriver_Channel_Function_X_ANALOG)
		{	
			/*GPIO AFSEL*/
			SET_BIT(GPIOAFSEL(BaseAddrArr[PortNum]),ChannelOffset);
			/* GPIOAMSEL enable analog*/
			SET_BIT(GPIOAMSEL(BaseAddrArr[PortNum]),ChannelOffset);
		}
		else
		{
				/*GPIO AFSEL enable ultrnative */
			SET_BIT(GPIOAFSEL(BaseAddrArr[PortNum]),ChannelOffset);

		/*GPIOCTL the type of altirnative function*/
			
			GPIOPCTL(BaseAddrArr[PortNum]) = (PortDriver_CfgArr[counter].PortDriver_Channel_Function)<<ChannelOffset*4  ;
			
		/*GPIODDEN digital enable*/
			SET_BIT(GPIODEN(BaseAddrArr[PortNum]),ChannelOffset);
		}
		
		
		
		
		/*********INTERRUPTS************/
		/*MASK the GPIOIM*/
		CLEAR_BIT(GPIOAFSEL(BaseAddrArr[PortNum]),ChannelOffset);
		
		/*if want interrupts */
		if(PortDriver_CfgArr[counter].PortDriver_Channel_Exti != PortDriver_Channel_Exti_Disable ){
		
				if(PortDriver_CfgArr[counter].PortDriver_Channel_Exti == PortDriver_Channel_Exti_BothEdge )
					/*GPIOIBE*/
					SET_BIT(GPIOIBE(BaseAddrArr[PortNum]),ChannelOffset);
				else if (PortDriver_CfgArr[counter].PortDriver_Channel_Exti == PortDriver_Channel_Exti_RisingEdge)
					/*GPIOIEV raising*/
					SET_BIT(GPIOIEV(BaseAddrArr[PortNum]),ChannelOffset);
				else if (PortDriver_CfgArr[counter].PortDriver_Channel_Exti == PortDriver_Channel_Exti_FallingEdge)
					/*GPIOIEV failing*/
					SET_BIT(GPIOIEV(BaseAddrArr[PortNum]),ChannelOffset);
				else if (PortDriver_CfgArr[counter].PortDriver_Channel_Exti == PortDriver_Channel_Exti_LevelSense)
					/*GPIOIS*/
					SET_BIT(GPIOIS(BaseAddrArr[PortNum]),ChannelOffset);
					
					/*clear GPIORIS by writing 1 to GPIOICR */
					SET_BIT(GPIOICR(BaseAddrArr[PortNum]),ChannelOffset);

			
			/*unmask GPIOIM*/
			SET_BIT(GPIOAFSEL(BaseAddrArr[PortNum]),ChannelOffset);
				
		}
	
	}


}

/**/


