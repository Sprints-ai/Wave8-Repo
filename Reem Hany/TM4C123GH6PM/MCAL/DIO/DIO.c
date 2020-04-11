#include "../includes/DIO.h"
#include "../includes/MCU_hw.h"
#include "../../Services/includes/common_macros.h"


#define NUM_OF_CHANNELS_IN_PORT							8

static uint32_t GPIO_Data[6]={GPIOPort_A_APB_BASE,
						            						           GPIOPort_B_APB_BASE,
						            						           GPIOPort_C_APB_BASE,
						            						           GPIOPort_D_APB_BASE,
						            						           GPIOPort_E_APB_BASE,
						            						           GPIOPort_F_APB_BASE
};
STD_levelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	uint8_t ChannelOffset,PortNum,val;
	PortNum = ChannelId/NUM_OF_CHANNELS_IN_PORT;
	ChannelOffset = ChannelId% NUM_OF_CHANNELS_IN_PORT;
	val = GET_BIT(GPIOREG(GPIO_Data[PortNum],GPIODATA_OFFSET),ChannelOffset);
	if(val)
		return STD_high;
	else
		return STD_low;
}
void Dio_WriteChannel(Dio_ChannelType ChannelId, STD_levelType Level)
{
	uint8_t ChannelOffset,PortNum,val;
	PortNum = ChannelId/NUM_OF_CHANNELS_IN_PORT;
	ChannelOffset = ChannelId% NUM_OF_CHANNELS_IN_PORT;
	
	if(Level == STD_low)
	{
		CLR_BIT(GPIOREG(GPIO_Data[PortNum],GPIODATA_OFFSET),ChannelOffset);
	}
	else
	{
		GPIOREG(GPIO_Data[PortNum],GPIODATA_OFFSET)=0X00000002;
		//SET_BIT(GPIOREG(GPIO_Data[PortNum],GPIODATA_OFFSET),ChannelOffset);
	}
}
uint8_t Dio_ReadPort(Dio_PortType PortId )
{
	return GPIOREG(GPIO_Data[PortId],GPIODATA_OFFSET);
}
void Dio_WritePort( Dio_PortType PortId, uint8_t Level)
{
	if(Level == STD_low)
	{
		 GPIOREG(GPIO_Data[PortId],GPIODATA_OFFSET) = 0X0;
	}
	else
	{
		 GPIOREG(GPIO_Data[PortId],GPIODATA_OFFSET) = 0xFFFFFFFF;
	}
}
void Dio_FlipChannel( Dio_ChannelType ChannelId)
{
	uint8_t ChannelOffset,PortNum,val;
	PortNum = ChannelId/NUM_OF_CHANNELS_IN_PORT;
	ChannelOffset = ChannelId% NUM_OF_CHANNELS_IN_PORT;
	TOGGLE_BIT(GPIOREG(GPIO_Data[PortNum],GPIODATA_OFFSET),ChannelOffset);
}