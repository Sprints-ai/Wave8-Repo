/*
 * port.c
 *
 * Created: 2020-04-12 4:20:42 PM
 *  Author: EbrahimOseif
 */
 
 
#include "port.h"
#include "port_lcfg.h"
#include "MCU_hw.h"


#define NUM_OF_CHANNELS_IN_PORT							8
#define GPIO_LOCK_MASK                      			0x4C4F434B

uint32_t BASEAddresses[]={
	GPIO_A_BASE,
	GPIO_B_BASE,
	GPIO_C_BASE,
	GPIO_D_BASE,
	GPIO_E_BASE,
	GPIO_F_BASE
	
};

void Port_Init(void)
{


	
	for(uint8_t i=0; i< NUM_OF_ACTIVATED_CHANNELS; i++)
	{
		/* 0 - get the port and the channle */
		
		uint8_t u8_PortNum= PortDriver_CfgArr[i].Channel / NUM_OF_CHANNELS_IN_PORT;
		uint8_t u8_ChannelOffset = PortDriver_CfgArr[i].Channel% NUM_OF_CHANNELS_IN_PORT;
		
		
		/* 1- Set the direction of the port */
		switch(PortDriver_CfgArr[i].PortDriver_Channel_Direction)
		{
			case PortDriver_Channel_Direction_INPUT:
				ClearBit( GPIOREG(BASEAddresses[u8_PortNum],GPIODIR_OFFSET), u8_ChannelOffset);
				break;
			
		  case PortDriver_Channel_Direction_OUTPUT:
	
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIODIR_OFFSET), u8_ChannelOffset);
				break; 
			default:
				break;
		}
		
		/* 2- set the attachment pull up/down */
		switch(PortDriver_CfgArr[i].PortDriver_Channel_Attachment)
		{
			case PortDriver_Channel_Attachment_NotConnected:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOODR_OFFSET), u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOPUR_OFFSET), u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOPDR_OFFSET), u8_ChannelOffset);
				break;
			
		  case PortDriver_Channel_Attachment_PullDownRes:
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOODR_OFFSET),   u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOPUR_OFFSET), u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOPDR_OFFSET), u8_ChannelOffset);
				break;
			
		  case PortDriver_Channel_Attachment_PullupRes:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOODR_OFFSET), u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOPUR_OFFSET),   u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOPDR_OFFSET), u8_ChannelOffset);
				break;
		  case PortDriver_Channel_Attachment_openDrain:		
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOODR_OFFSET), u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOPUR_OFFSET), u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOPDR_OFFSET),   u8_ChannelOffset);
				break; 
			default:
				break;
		}
		
		
		/* 3- Set the alternative function */
		GPIOREG(BASEAddresses[u8_PortNum], GPIOLOCK_OFFSET) = GPIO_LOCK_MASK;
		ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOCR_OFFSET), u8_ChannelOffset);
		
		/* check the function of the pin then set the corresponding bits  */
		
		if(PortDriver_CfgArr[i].PortDriver_Channel_Function == PortDriver_Channel_Function_X_DIO)
		{
			ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOAFSEL_OFFSET),u8_ChannelOffset);
		}
		else
		{
			SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOAFSEL_OFFSET),u8_ChannelOffset);
		}
		
		switch(PortDriver_CfgArr[i].PortDriver_Channel_Function)
		{
			
		  case PortDriver_Channel_Function_X_Analog:
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOADCCTL_OFFSET),u8_ChannelOffset);
				break;
				
		  case PortDriver_Channel_Function_X_DMA:		
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIODMACTL_OFFSET),u8_ChannelOffset);
				break; 
				
			default:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOADCCTL_OFFSET),u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIODMACTL_OFFSET),u8_ChannelOffset);
				GPIOREG(BASEAddresses[u8_PortNum],GPIOPCTL_OFFSET) |= PortDriver_CfgArr[i].PortDriver_Channel_Function <<u8_ChannelOffset*4;
		
				break;
		}
		
		/* 4- set the port strength */ 
		switch(PortDriver_CfgArr[i].PortDriver_Channel_Current_mA)
		{
			case PortDriver_Channel_Current_mA_2:
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIODR2R_OFFSET),   u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIODR4R_OFFSET), u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIODR8R_OFFSET), u8_ChannelOffset);
				break;                                                       
			case PortDriver_Channel_Current_mA_4:                            
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIODR2R_OFFSET), u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIODR4R_OFFSET),   u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIODR8R_OFFSET), u8_ChannelOffset);
				break;                                                       
			case PortDriver_Channel_Current_mA_8:                            
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIODR2R_OFFSET), u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIODR4R_OFFSET), u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIODR8R_OFFSET),   u8_ChannelOffset);
				break;
			default:
				break;
		}
		
		/* 5- Set the slew rate */
		switch(PortDriver_CfgArr[i].PortDriver_Channel_SlewRate)
		{
			case PortDriver_Channel_SlewRate_Disable:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOSLR_OFFSET), u8_ChannelOffset);
				break;
			
		  case PortDriver_Channel_SlewRate_Enable:
	
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOSLR_OFFSET), u8_ChannelOffset);
				break; 
			default:
				break;
		}
		
		
		/* 6 - set the interrupt sense */
		/* switch to the value and set the corresponding pins */
		switch(PortDriver_CfgArr[i].PortDriver_Channel_Exti)
		{
			case PortDriver_Channel_Exti_Disable:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIM_OFFSET),u8_ChannelOffset);
				break;
			
			case PortDriver_Channel_Exti_LevelSense:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIM_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIS_OFFSET),u8_ChannelOffset);
			    SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIEV_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIM_OFFSET),u8_ChannelOffset);
				break;
			
			case PortDriver_Channel_Exti_FallingEdge:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIM_OFFSET),u8_ChannelOffset);
			    SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIS_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIM_OFFSET),u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIEV_OFFSET),u8_ChannelOffset);
				break;
			
			case PortDriver_Channel_Exti_RisingEdge:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIM_OFFSET),u8_ChannelOffset);
			    SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIS_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIM_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIEV_OFFSET),u8_ChannelOffset);
				break;
			
			case PortDriver_Channel_Exti_BothEdge:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIM_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIS_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIBE_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNum],GPIOIM_OFFSET),u8_ChannelOffset);
				break;
			
			default:
				break;
		}
		
	}
}