/*
 * port.c
 *
 *      Author: Abdallah Heidar
 */
 
#include "port.h"
#include "port_lcfg.h"
#include "MCU_hw.h"

#define NUM_OF_CHANNELS_IN_PORT			8
#define GPIO_LOCK_MASK            		0x4C4F434B

uint32_t BASEAddresses[] = {
	GPIOA_BASE,
	GPIOB_BASE,
	GPIOC_BASE,
	GPIOD_BASE,
	GPIOE_BASE,
	GPIOF_BASE
};

void Port_Init(void)
{
	for(uint8_t idx=0; idx< NUM_OF_ACTIVATED_CHANNELS; idx++)
	{
		uint8_t u8_PortNumber= PortDriver_CfgArr[idx].Channel / NUM_OF_CHANNELS_IN_PORT;
		uint8_t u8_ChannelOffset = PortDriver_CfgArr[idx].Channel% NUM_OF_CHANNELS_IN_PORT;
		
		switch(PortDriver_CfgArr[idx].PortDriver_Channel_Direction)
		{
			case PortDriver_Channel_Direction_INPUT:
				ClearBit( GPIOREG(BASEAddresses[u8_PortNumber],GPIODIR_OFFSET), u8_ChannelOffset);
				break;
		  case PortDriver_Channel_Direction_OUTPUT:
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIODIR_OFFSET), u8_ChannelOffset);
				break; 
			default:
				break;
		}
		
		switch(PortDriver_CfgArr[idx].PortDriver_Channel_Attachment)
		{
			case PortDriver_Ch_Attachment_NotConnected:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOODR_OFFSET), u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOPUR_OFFSET), u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOPDR_OFFSET), u8_ChannelOffset);
				break;
		  case PortDriver_Ch_Attachment_PullDownRes:
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOODR_OFFSET),   u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOPUR_OFFSET), u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOPDR_OFFSET), u8_ChannelOffset);
				break;
		  case PortDriver_Ch_Attachment_PullupRes:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOODR_OFFSET), u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOPUR_OFFSET),   u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOPDR_OFFSET), u8_ChannelOffset);
				break;
		  case PortDriver_Ch_Attachment_openDrain:		
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOODR_OFFSET), u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOPUR_OFFSET), u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOPDR_OFFSET),   u8_ChannelOffset);
				break; 
			default:
				break;
		}
		
		GPIOREG(BASEAddresses[u8_PortNumber], GPIOLOCK_OFFSET) = GPIO_LOCK_MASK;
		ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOCR_OFFSET), u8_ChannelOffset);
		
		if(PortDriver_CfgArr[idx].PortDriver_Channel_Function == PortDriver_Channel_Function_X_DIO)
		{
			ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOAFSEL_OFFSET),u8_ChannelOffset);
		}
		else
		{
			SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOAFSEL_OFFSET),u8_ChannelOffset);
		}
		
		
		switch(PortDriver_CfgArr[idx].PortDriver_Channel_Function)
		{
		  case PortDriver_Ch_Function_X_Analog:
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOADCCTL_OFFSET),u8_ChannelOffset);
				break;
		  case PortDriver_Ch_Function_X_DMA:		
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIODMACTL_OFFSET),u8_ChannelOffset);
				break; 
			default:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOADCCTL_OFFSET),u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIODMACTL_OFFSET),u8_ChannelOffset);
				GPIOREG(BASEAddresses[u8_PortNumber],GPIOPCTL_OFFSET) |= PortDriver_CfgArr[idx].PortDriver_Channel_Function <<u8_ChannelOffset*4;
				break;
		}
		
		switch(PortDriver_CfgArr[idx].PortDriver_Channel_Current_mA)
		{
			case PortDriver_Ch_Current_mA_2:
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIODR2R_OFFSET),   u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIODR4R_OFFSET), u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIODR8R_OFFSET), u8_ChannelOffset);
				break;                                                       
			case PortDriver_Ch_Current_mA_4:                            
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIODR2R_OFFSET), u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIODR4R_OFFSET),   u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIODR8R_OFFSET), u8_ChannelOffset);
				break;                                                       
			case PortDriver_Ch_Current_mA_8:                            
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIODR2R_OFFSET), u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIODR4R_OFFSET), u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIODR8R_OFFSET),   u8_ChannelOffset);
				break;
			default:
				break;
		}
		
		switch(PortDriver_CfgArr[idx].PortDriver_Channel_SlewRate)
		{
			case PortDriver_Ch_SlewRate_Disable:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOSLR_OFFSET), u8_ChannelOffset);
				break;
			
		  case PortDriver_Ch_SlewRate_Enable:
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOSLR_OFFSET), u8_ChannelOffset);
				break; 
			default:
				break;
		}
		
		switch(PortDriver_CfgArr[idx].PortDriver_Channel_Exti)
		{
			case PortDriver_Ch_Exti_Disable:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIM_OFFSET),u8_ChannelOffset);
				break;
			case PortDriver_Ch_Exti_LevelSense:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIM_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIS_OFFSET),u8_ChannelOffset);
			    SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIEV_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIM_OFFSET),u8_ChannelOffset);
				break;
			case PortDriver_Ch_Exti_FallingEdge:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIM_OFFSET),u8_ChannelOffset);
			    SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIS_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIM_OFFSET),u8_ChannelOffset);
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIEV_OFFSET),u8_ChannelOffset);
				break;
			case PortDriver_Ch_Exti_RisingEdge:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIM_OFFSET),u8_ChannelOffset);
			    SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIS_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIM_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIEV_OFFSET),u8_ChannelOffset);
				break;
			case PortDriver_Ch_Exti_BothEdge:
				ClearBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIM_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIS_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIBE_OFFSET),u8_ChannelOffset);
				SetBit(GPIOREG(BASEAddresses[u8_PortNumber],GPIOIM_OFFSET),u8_ChannelOffset);
				break;
			default:
				break;
		}
	}
}