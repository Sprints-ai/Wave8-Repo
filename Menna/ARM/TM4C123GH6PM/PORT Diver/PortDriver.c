
/*****************************************************************************/
/*					Port.c												 */	
/*****************************************************************************/


#define NUM_OF_CHANNELS_IN_PORT							8
#define NUM_OF_PORTS 6
PortDriver_CfgType PortDriver_CfgArr[];


uint32_t BaseAddrArr[NUM_OF_PORTS] = {
									BASE_ADDRESS_A,
									BASE_ADDRESS_B,
									BASE_ADDRESS_C,
									BASE_ADDRESS_D,
									BASE_ADDRESS_E,
									BASE_ADDRESS_F}		
PortDriver_init(void)
{
	uint8 i =0;
	PortDriver_PortNumType PortNum;
	PortDriver_ChannelType ChannelNum;
	uint8 ChannelOffset;		
	
	for(i=0;i<NUM_OF_ACTIVATED_CHANNELS;i++)
	{
		ChannelNum = PortDriver_CfgArr[i].Channel;
		PortNum = ChannelNum / NUM_OF_CHANNELS_IN_PORT;
		ChannelOffset = ChannelNum% NUM_OF_CHANNELS_IN_PORT;
		
		if(PortDriver_CfgArr[i].PortDriver_Channel_Direction == PortDriver_Channel_Direction_INPUT )
		{

						
			Clr_Bit(GPIODIR(BaseAddrArr[PortNum]),ChannelOffset);
			
		}
		else if(PortDriver_CfgArr[i].PortDriver_Channel_Direction == PortDriver_Channel_Direction_OUTPUT)
		{
			Set_Bit(GPIODIR(BaseAddrArr[PortNum]),ChannelOffset);
			
		}	
	}

}



/*****************************************************************************/
/*					Port.h											     	 */	
/*****************************************************************************/

#include "PortDriver_Types.h"

PortDriver_init(void);





/*****************************************************************************/
/*					Dio.h											     	 */	
/*****************************************************************************/
typedef enum
{
    STD_low=0,
    STD_high=!STD_low
}STD_levelType;

typedef enum
{
    Dio_Channel_A0,
    Dio_Channel_A1,
    Dio_Channel_A2,
    Dio_Channel_A3,
    Dio_Channel_A4,
    Dio_Channel_A5,
    Dio_Channel_A6,
    Dio_Channel_A7,

    Dio_Channel_B0,
    Dio_Channel_B1,
    Dio_Channel_B2,
    Dio_Channel_B3,
    Dio_Channel_B4,
    Dio_Channel_B5,
    Dio_Channel_B6,
    Dio_Channel_B7,


    Dio_Channel_C0,
    Dio_Channel_C1,
    Dio_Channel_C2,
    Dio_Channel_C3,
    Dio_Channel_C4,
    Dio_Channel_C5,
    Dio_Channel_C6,
    Dio_Channel_C7,


    Dio_Channel_D0,
    Dio_Channel_D1,
    Dio_Channel_D2,
    Dio_Channel_D3,
    Dio_Channel_D4,
    Dio_Channel_D5,
    Dio_Channel_D6,
    Dio_Channel_D7,

    Dio_Channel_E0,
    Dio_Channel_E1,
    Dio_Channel_E2,
    Dio_Channel_E3,
    Dio_Channel_E4,
    Dio_Channel_E5,
    Dio_Channel_E6_NA,
    Dio_Channel_E7_NA,

    Dio_Channel_F0,
    Dio_Channel_F1,
    Dio_Channel_F2,
    Dio_Channel_F3,
    Dio_Channel_F4

}Dio_ChannelType;

typedef enum
{
    Dio_Port_A,
    Dio_Port_B,
    Dio_Port_C,
    Dio_Port_D,
    Dio_Port_E,
    Dio_Port_F
}Dio_PortType;




STD_levelType Dio_ReadChannel(Dio_ChannelType ChannelId);
void Dio_WriteChannel(Dio_ChannelType ChannelId, STD_levelType Level);
uint8_t Dio_ReadPort(Dio_PortType PortId );
void Dio_WritePort( Dio_PortType PortId, uint8_t Level);
void Dio_FlipChannel( Dio_ChannelType ChannelId);


/*****************************************************************************/
/*					Mcu_Hw.h										         */	
/*****************************************************************************/
#define GPIODIR_OFFSET						0x400
#define GPIODIR(BASE_ADDRESS)				*((volatile uint32*)(BASE_ADDRESS + GPIODIR_OFFSET))


/*****************************************************************************/
/*					Mcu_Hw.h /*Another Methode (Don't Care)*/										         */	
/*****************************************************************************/

typedef union
{
	uint32 			R;
	struct
	{
		uint32 B0:1;
		uint32 B1:1;
		uint32 B2:1;
		uint32 XTAL:3;
		uint32 :2;
		uint32 DIV:4;
		uint32 B6:1;
		uint32 B7:1;
		uint32  :24;
	
	}B;
}GPIODIR_TAG;

#define GPIODIR_OFFSET						0x400
#define GPIODIR(BASE_ADDRESS)				(*((volatile GPIODIR_TAG*)(BASE_ADDRESS + GPIODIR_OFFSET)))
void Fun(void)
{
	GPIODIR(BASE_ADDR_A).B.XTAL = value;
}
/********************************************************************************************/
typedef struct
{
    uint32 GPIODATA    ;
	uint8 REserved[0x3FC];
    uint32 GPIODIR     ;
    uint32 GPIOIS      ;
    uint32 GPIOIBE     ;
    uint32 GPIOIEV     ;
    uint32 GPIOIM      ;
    uint32 GPIORIS     ;
    uint32 GPIOMIS     ;
    uint32 GPIOICR     ;
    uint32 GPIOAFSEL   ; /*offset : 0x420 -> 424 */

    uint8 Reserved_2[0xDC];
    uint32 GPIODR2R    ; /*offset : 0x500 */
    uint32 GPIODR4R    ;
    uint32 GPIODR8R    ;
    uint32 GPIOODR     ;
    uint32 GPIOPUR     ;
    uint32 GPIOPDR     ;
    uint32 GPIOSLR     ;
    uint32 GPIODEN     ;
    uint32 GPIOLOCK    ;
    uint32 GPIOCR      ;
    uint32 GPIOAMSEL   ;
    uint32 GPIOPCTL    ;
    uint32 GPIOADCCTL  ;
    uint32 GPIODMACTL  ;
}PORT_RegType;

#define  PORT_A     *((volatile PORT_RegType*)BASE_ADDR_A);
#define  PORT_B     *((volatile PORT_RegType*)BASE_ADDR_B);
#define  PORT_C     *((volatile PORT_RegType*)BASE_ADDR_C);
#define  PORT_D     *((volatile PORT_RegType*)BASE_ADDR_D);

void func(void)
{
	PORT_A.GPIORIS = value;
	
	
}
