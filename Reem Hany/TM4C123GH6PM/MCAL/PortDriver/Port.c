#include "../includes/Port.h"
#include "../includes/Port_lCfg.h"
#include "../includes/MCU_hw.h"
#include "../../Services/includes/common_macros.h"

#define NUM_OF_CHANNELS_IN_PORT							8
#define GPIO_LOCK_MASK                      0x4C4F434B

uint32_t BASEAddresses[]={
	GPIOPort_A_APB_BASE,
	GPIOPort_B_APB_BASE,
	GPIOPort_C_APB_BASE,
	GPIOPort_D_APB_BASE,
	GPIOPort_E_APB_BASE,
	GPIOPort_F_APB_BASE
	
};

void Port_Init(void)
{
	uint8_t i =ZERO,PORT_NUM,ChannelOffset; 

	for(i=ZERO; i< NUM_OF_ACTIVATED_CHANNELS; i++)
	{
		PORT_NUM= PortDriver_CfgArr[i].Channel / NUM_OF_CHANNELS_IN_PORT;
		ChannelOffset = PortDriver_CfgArr[i].Channel% NUM_OF_CHANNELS_IN_PORT;
		//Set the direction
		if(PortDriver_CfgArr[i].PortDriver_Channel_Direction == PortDriver_Channel_Direction_INPUT)
		{
			CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODIR_OFFSET),ChannelOffset);
		}
		else if(PortDriver_CfgArr[i].PortDriver_Channel_Direction == PortDriver_Channel_Direction_OUTPUT)
		{
			SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODIR_OFFSET),ChannelOffset);
		}
		//Set the alternative function
		GPIOREG(BASEAddresses[PORT_NUM],GPIOLOCK_OFFSET) = GPIO_LOCK_MASK;//UNLOCK the gpio commit
		CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOCR_OFFSET),ChannelOffset);// gpio Commit
		
		//Set af select val
		if(PortDriver_CfgArr[i].PortDriver_Channel_Function == PortDriver_Channel_Function_X_DIO)
		{
			CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOAFSEL_OFFSET),ChannelOffset);
		}
		else
		{
			SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOAFSEL_OFFSET),ChannelOffset);
		}
		
		//Set the channel function
		if(PortDriver_CfgArr[i].PortDriver_Channel_Function == PortDriver_Channel_Function_X_Analog)
		{
			SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOADCCTL_OFFSET),ChannelOffset);
		}
		else if(PortDriver_CfgArr[i].PortDriver_Channel_Function == PortDriver_Channel_Function_X_DMA)
		{
			SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODMACTL_OFFSET),ChannelOffset);
		}
		else
		{
			CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOADCCTL_OFFSET),ChannelOffset);
			CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODMACTL_OFFSET),ChannelOffset);
			GPIOREG(BASEAddresses[PORT_NUM],GPIOPCTL_OFFSET) |= PortDriver_CfgArr[i].PortDriver_Channel_Function <<ChannelOffset*4;
		}
		
		//current
		switch(PortDriver_CfgArr[i].PortDriver_Channel_Current_mA)
		{
			case PortDriver_Channel_Current_mA_2:
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR2R_OFFSET),ChannelOffset);
			  CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR4R_OFFSET),ChannelOffset);
	  		CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR8R_OFFSET),ChannelOffset);
				break;
			case PortDriver_Channel_Current_mA_4:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR2R_OFFSET),ChannelOffset);
			  SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR4R_OFFSET),ChannelOffset);
	  		CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR8R_OFFSET),ChannelOffset);
				break;
			case PortDriver_Channel_Current_mA_8:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR2R_OFFSET),ChannelOffset);
			  CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR4R_OFFSET),ChannelOffset);
	  		SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR8R_OFFSET),ChannelOffset);
				break;
			default:
				//ERR
				break;
		}
		//Set the slew rate
		if(PortDriver_CfgArr[i].PortDriver_Channel_SlewRate == PortDriver_Channel_SlewRate_Disable)
		{
			 CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOSLR_OFFSET),ChannelOffset);
		}
		else if(PortDriver_CfgArr[i].PortDriver_Channel_SlewRate == PortDriver_Channel_SlewRate_Enable)
		{
			SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOSLR_OFFSET),ChannelOffset);
		}
		else
		{
			//ERR
		}
		//attachment pull up/down
		switch(PortDriver_CfgArr[i].PortDriver_Channel_Attachment)
		{
			case PortDriver_Channel_Attachment_NotConnected:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOODR_OFFSET),ChannelOffset);
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPUR_OFFSET),ChannelOffset);
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPDR_OFFSET),ChannelOffset);
				break;
			
		  case PortDriver_Channel_Attachment_PullDownRes:
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOODR_OFFSET),ChannelOffset);
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPUR_OFFSET),ChannelOffset);
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPDR_OFFSET),ChannelOffset);
				break;
			
		  case PortDriver_Channel_Attachment_PullupRes:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOODR_OFFSET),ChannelOffset);
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPUR_OFFSET),ChannelOffset);
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPDR_OFFSET),ChannelOffset);
				break;
		  case PortDriver_Channel_Attachment_openDrain:		
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOODR_OFFSET),ChannelOffset);
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPUR_OFFSET),ChannelOffset);
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPDR_OFFSET),ChannelOffset);
				break;
			default:
			//ERR
			break;
		}
		//interrupt
		switch(PortDriver_CfgArr[i].PortDriver_Channel_Exti)
		{
			case PortDriver_Channel_Exti_Disable:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),ChannelOffset);//Mask the pin
				break;
			
			case PortDriver_Channel_Exti_LevelSense:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),ChannelOffset);//Mask the pin
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIS_OFFSET),ChannelOffset);//Level sense
			  SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIEV_OFFSET),ChannelOffset);//HIGH LEVEL sense
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),ChannelOffset);//unmask the pin
				break;
			
			case PortDriver_Channel_Exti_FallingEdge:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),ChannelOffset);//Mask the pin
			  SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIS_OFFSET),ChannelOffset);//EDGE sense
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),ChannelOffset);//unmask the pin
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIEV_OFFSET),ChannelOffset);//Falling EDGE sense
				break;
			
			case PortDriver_Channel_Exti_RisingEdge:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),ChannelOffset);//Mask the pin
			  SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIS_OFFSET),ChannelOffset);//EDGE sense
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),ChannelOffset);//unmask the pin
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIEV_OFFSET),ChannelOffset);//Rising EDGE sense
				break;
			
			case PortDriver_Channel_Exti_BothEdge:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),ChannelOffset);//Mask the pin
			  SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIS_OFFSET),ChannelOffset);//EDGE sense
			  SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIBE_OFFSET),ChannelOffset);//BOTH Edge
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),ChannelOffset);//unmask the pin
				break;
			
			default:
				break;
		}
		
	}
}