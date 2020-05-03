
/*****************************************************************************/
/*					PortDriver_Types.h										 */	
/***************************************************************************/
#ifndef __PortDriver_Types_H__
#define __PortDriver_Types_H__


#include "../std_types.h"

typedef uint8_t PortDriver_Channel_DirectionType; //(GPIODIR) -> (GPIO Direction )
#define PortDriver_Channel_Direction_INPUT			 		0
#define PortDriver_Channel_Direction_OUTPUT					1

typedef uint8_t PortDriver_Channel_Current_mAType;
#define PortDriver_Channel_Current_mA_2			 			0   // (GPIODR2R)
#define PortDriver_Channel_Current_mA_4			 			1   // (GPIODR4R)
#define PortDriver_Channel_Current_mA_8			 			2   // (GPIODR8R)
			
typedef uint8_t PortDriver_Channel_SlewRateType ;				//(GPIOSLR) -> (GPIO SLEW Rate)
#define PortDriver_Channel_SlewRate_Disable					0
#define PortDriver_Channel_SlewRate_Enable					1

typedef uint8_t PortDriver_Channel_AttachmentType;
#define PortDriver_Channel_Attachment_NotConnected			0
#define PortDriver_Channel_Attachment_openDrain				1
#define PortDriver_Channel_Attachment_PullupRes				2//GPIOPUR)
#define PortDriver_Channel_Attachment_PullDownRes			3//GPIOPDR)
			

typedef uint32_t PortDriver_Channel_FunctionType; // (GPIOAFSEL) -> (GPIO Alternative Function Select),(GPIODEN) -> crosponding pin set to high (digital enable) ,(GPIOPCTL)(GPIO Prepherial Control) -> get one form hash define 
#define PortDriver_Channel_Function_X_DIO                   0x00000000//except (GPIOAFSEL),(GPIODEN) ->crosponding pin set to Low ,high
#define PortDriver_Channel_Function_B0_U1RX                 0x00000001
#define PortDriver_Channel_Function_B1_U1TX                 0x00000010
#define PortDriver_Channel_Function_A2_SSI0Clk              0x00000200
#define PortDriver_Channel_Function_A3_SSI0Fss              0x00002000
#define PortDriver_Channel_Function_A4_SSI0Rx               0x00020000
#define PortDriver_Channel_Function_A5_SSI0Tx               0x00200000
#define PortDriver_Channel_Function_B4_SSI2Clk              0x00020000
#define PortDriver_Channel_Function_B5_SSI2Fss              0x00200000
#define PortDriver_Channel_Function_B6_SSI2Rx               0x02000000
#define PortDriver_Channel_Function_B7_SSI2Tx               0x20000000
#define PortDriver_Channel_Function_D0_SSI1Clk              0x00000002
#define PortDriver_Channel_Function_D1_SSI1Fss              0x00000020
#define PortDriver_Channel_Function_D2_SSI1Rx               0x00000200
#define PortDriver_Channel_Function_D3_SSI1Tx               0x00002000
#define PortDriver_Channel_Function_D0_SSI3Clk              0x00000001
#define PortDriver_Channel_Function_D1_SSI3Fss              0x00000010
#define PortDriver_Channel_Function_D2_SSI3Rx               0x00000100
#define PortDriver_Channel_Function_D3_SSI3Tx               0x00001000
#define PortDriver_Channel_Function_F0_SSI1Rx             	0x00000002 ///*SSI1Clk_2*/
#define PortDriver_Channel_Function_F1_SSI1Tx               0x00000020
#define PortDriver_Channel_Function_F2_SSI1Clk              0x00000200
#define PortDriver_Channel_Function_F3_SSI1Fss              0x00002000//corrected //
#define PortDriver_Channel_Function_B2_I2C0SCL              0x00000300
#define PortDriver_Channel_Function_B3_I2C0SDA              0x00003000
#define PortDriver_Channel_Function_A6_I2C1SCL              0x03000000
#define PortDriver_Channel_Function_A7_I2C1SDA              0x30000000
#define PortDriver_Channel_Function_E4_I2C2SCL              0x00030000
#define PortDriver_Channel_Function_E5_I2C2SDA              0x00300000
#define PortDriver_Channel_Function_D0_I2C3SCL              0x00000003
#define PortDriver_Channel_Function_D1_I2C3SDA              0x00000030
/// add ADC part
#define PortDriver_Channel_Function_B4_ADC					0xffffffff
#define PortDriver_Channel_Function_B5_ADC					0xffffffff

#define PortDriver_Channel_Function_D0_ADC					0xffffffff
#define PortDriver_Channel_Function_D1_ADC					0xffffffff
#define PortDriver_Channel_Function_D2_ADC					0xffffffff
#define PortDriver_Channel_Function_D3_ADC					0xffffffff

#define PortDriver_Channel_Function_E0_ADC					0xffffffff
#define PortDriver_Channel_Function_E1_ADC					0xffffffff
#define PortDriver_Channel_Function_E2_ADC					0xffffffff
#define PortDriver_Channel_Function_E3_ADC					0xffffffff
#define PortDriver_Channel_Function_E4_ADC					0xffffffff
#define PortDriver_Channel_Function_E5_ADC					0xffffffff

/*		Interrupt control */
typedef uint8_t PortDriver_Channel_ExtiType ;  

#define PortDriver_Channel_Exti_Disable						0 //(GPIOIM) 
#define PortDriver_Channel_Exti_RisingEdge					1 //(GPIOIS),(GPIOIEV),(GPIOIM),(GPIOICR),
#define PortDriver_Channel_Exti_FallingEdge					2 //(GPIOIS),(GPIOIEV),(GPIOIM)  ,(GPIOICR),
#define PortDriver_Channel_Exti_BothEdge					3 //(GPIOIS),(GPIOIBE),(GPIOIM) ,(GPIOICR),
#define PortDriver_Channel_Exti_LowLevel					4 //(GPIOIS),(GPIOIEV),(GPIOIM)  ,(GPIOICR),
#define PortDriver_Channel_Exti_HighLevel					5 //(GPIOIS),(GPIOIEV),(GPIOIM)   ,(GPIOICR),

typedef enum
{
	PortDriver_PortNum_A,
	PortDriver_PortNum_B,
	PortDriver_PortNum_C,
	PortDriver_PortNum_D,
	PortDriver_PortNum_E,
	PortDriver_PortNum_F
}PortDriver_PortNumType;

typedef enum
{
	PortDriver_Channel_A0,
	PortDriver_Channel_A1,
	PortDriver_Channel_A2,
	PortDriver_Channel_A3,
	PortDriver_Channel_A4,
	PortDriver_Channel_A5,
	PortDriver_Channel_A6,
	PortDriver_Channel_A7,
	
	PortDriver_Channel_B0,//8
	PortDriver_Channel_B1,
	PortDriver_Channel_B2,
	PortDriver_Channel_B3,
	PortDriver_Channel_B4,
	PortDriver_Channel_B5,
	PortDriver_Channel_B6,
	PortDriver_Channel_B7,
	
	PortDriver_Channel_C0,//16
	PortDriver_Channel_C1,
	PortDriver_Channel_C2,
	PortDriver_Channel_C3,
	PortDriver_Channel_C4,
	PortDriver_Channel_C5,
	PortDriver_Channel_C6,
	PortDriver_Channel_C7,
	
	PortDriver_Channel_D0,//24
	PortDriver_Channel_D1,
	PortDriver_Channel_D2,
	PortDriver_Channel_D3,
	PortDriver_Channel_D4,
	PortDriver_Channel_D5,
	PortDriver_Channel_D6,
	PortDriver_Channel_D7,
	
	PortDriver_Channel_E0,//32
	PortDriver_Channel_E1,
	PortDriver_Channel_E2,
	PortDriver_Channel_E3,
	PortDriver_Channel_E4,
	PortDriver_Channel_E5,
	PortDriver_Channel_E6_Reserved,
	PortDriver_Channel_E7_Reserved,
	
	PortDriver_Channel_F0,//40
	PortDriver_Channel_F1,
	PortDriver_Channel_F2,
	PortDriver_Channel_F3,
	PortDriver_Channel_F4,
	PortDriver_Channel_F5_Reserved,
	PortDriver_Channel_F6_Reserved,
	PortDriver_Channel_F7_Reserved,
	
	
}PortDriver_ChannelType;
typedef struct
{
	PortDriver_ChannelType				Channel;
	PortDriver_Channel_DirectionType	PortDriver_Channel_Direction;
	PortDriver_Channel_Current_mAType	PortDriver_Channel_Current_mA;
	PortDriver_Channel_SlewRateType		PortDriver_Channel_SlewRate;
	PortDriver_Channel_AttachmentType	PortDriver_Channel_Attachment;
	PortDriver_Channel_FunctionType		PortDriver_Channel_Function;
	PortDriver_Channel_ExtiType			PortDriver_Channel_Exti;
}PortDriver_CfgType;

#endif
