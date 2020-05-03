#include "Dio.h"
#include "MCU_hw.h"
#define PORT_DATA_REGESTER 0x000003FC

#define NUM_OF_PORTS 									6
#define NUM_OF_CHANNELS_IN_PORT							8

#include <stdio.h>
static uint32_t au32_BaseAddr[NUM_OF_PORTS] = {BASE_ADDRESS_A,   
										BASE_ADDRESS_B,
										BASE_ADDRESS_C,
										BASE_ADDRESS_D,
										BASE_ADDRESS_E,
				  					    BASE_ADDRESS_F};

STD_levelType Dio_ReadChannel(Dio_ChannelType ChannelId){
	STD_levelType Value=0;
	
	Dio_PortType PortId;
	
	Dio_ChannelType  ChannelOfset;
	
	PortId = ChannelId / NUM_OF_CHANNELS_IN_PORT ;
	
	ChannelOfset= 1<<(2+ChannelId % NUM_OF_CHANNELS_IN_PORT );
	
	Value = *( volatile uint32_t *)(((uint8_t *)(&(ACTINATING_PORT(au32_BaseAddr[PortId]).GPIODATA)))+(ChannelOfset));
	
	if(Value > STD_low )
		Value = STD_high;
	
	return Value;
}

void Dio_WriteChannel(Dio_ChannelType ChannelId, STD_levelType Level){
	uint32_t y =0;
	Dio_PortType PortId;
	Dio_ChannelType ChannelOfset1;
	uint8_t u8_BitOrder;
	ChannelOfset1 = 1<<(2+ChannelId % NUM_OF_CHANNELS_IN_PORT );
	PortId = ChannelId / NUM_OF_CHANNELS_IN_PORT ;
	u8_BitOrder = (ChannelId % NUM_OF_CHANNELS_IN_PORT) ;
	
	*((volatile uint32_t *)(((uint8_t *)(&(ACTINATING_PORT(au32_BaseAddr[PortId]).GPIODATA)))+(ChannelOfset1)))= Level;

}

void Dio_FlipChannel( Dio_ChannelType ChannelId){
	
	Dio_PortType PortId;
	
	Dio_ChannelType  ChannelOfset;
	uint8_t u8_BitOrder;
	
	u8_BitOrder = (1<<(ChannelId % NUM_OF_CHANNELS_IN_PORT)) ;
	PortId = ChannelId / NUM_OF_CHANNELS_IN_PORT ;
	
	ChannelOfset= 1<<(2+ChannelId % NUM_OF_CHANNELS_IN_PORT );
	
	*( volatile uint32_t *)(((uint8_t *)(&(ACTINATING_PORT(au32_BaseAddr[PortId]).GPIODATA)))+ChannelOfset) ^= u8_BitOrder;
	
	
	
}

uint8_t Dio_ReadPort(Dio_PortType PortId ){
	uint8_t u8_Value=0;
	
	u8_Value = *( volatile uint32_t *)(((uint8_t *)(&(ACTINATING_PORT(au32_BaseAddr[PortId]).GPIODATA)))+PORT_DATA_REGESTER);
	
	return u8_Value;
}

void Dio_WritePort( Dio_PortType PortId, uint8_t Level){
	
	*( volatile uint32_t *)(((uint8_t *)(&(ACTINATING_PORT(au32_BaseAddr[PortId]).GPIODATA)))+PORT_DATA_REGESTER) = Level;
}


/*void main (){
	//printf("%x",(uint32_t)0x01|0x10);
	//printf("%x",(((uint8_t *)(&(ACTINATING_PORT(au32_BaseAddr[0]).GPIODATA)))+(1<<(2+3)) ));

}*/
































