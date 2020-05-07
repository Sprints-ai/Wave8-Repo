/*
 * port_types.h
 *
 * Created: 2020-04-12 4:20:42 PM
 *  Author: EbrahimOseif
 */
 
#ifndef __PORT_TYPES_H__
#define __PORT_TYPES_H__


/*****************************************************************/
/*        		  includes		                 */
/*****************************************************************/



#include "std_types.h"


/*****************************************************************/
/*          typedefs and defines of every type	                 */
/*****************************************************************/


/************* Direction types *********************/

typedef uint8_t PortDriver_Channel_DirectionType;

#define PortDriver_Channel_Direction_INPUT			 		          0
#define PortDriver_Channel_Direction_OUTPUT					          1
															          
															          
/**************** Driver Strength **********************/             
typedef uint8_t PortDriver_Channel_Current_mAType;                    
															          
#define PortDriver_Channel_Current_mA_2			 			          0
#define PortDriver_Channel_Current_mA_4			 			          1
#define PortDriver_Channel_Current_mA_8			 			          2
															          
/************** SLew Rate********************************/            
typedef uint8_t PortDriver_Channel_SlewRateType;                      
															          
#define PortDriver_Channel_SlewRate_Disable					          0
#define PortDriver_Channel_SlewRate_Enable					          0


/************* port attachment type *********************/

typedef uint8_t PortDriver_Channel_AttachmentType;

#define PortDriver_Channel_Attachment_NotConnected				      0
#define PortDriver_Channel_Attachment_PullupRes					      1
#define PortDriver_Channel_Attachment_PullDownRes				      2
#define PortDriver_Channel_Attachment_openDrain					      3



/************* special functions *********************/

typedef uint8_t PortDriver_Channel_FunctionType;

#define PortDriver_Channel_Function_X_Analog               			 16
#define PortDriver_Channel_Function_X_DMA                  			 17
#define PortDriver_Channel_Function_X_DIO                            0
#define PortDriver_Channel_Function_A0_U0RX                          1
#define PortDriver_Channel_Function_A0_CANRX                         8
#define PortDriver_Channel_Function_A1_U0TX                          1
#define PortDriver_Channel_Function_A1_CANTX                         8
#define PortDriver_Channel_Function_A2_SSI0Clk                       2
#define PortDriver_Channel_Function_A3_SSI0Fss                       2
#define PortDriver_Channel_Function_A4_SSI0Rx                        2
#define PortDriver_Channel_Function_A5_SSI0Tx                        2
#define PortDriver_Channel_Function_A6_I2C1SCL                       3
#define PortDriver_Channel_Function_A6_M1PWM2                        5
#define PortDriver_Channel_Function_A7_I2C1SDA                       3
															         
#define PortDriver_Channel_Function_B0_U1RX                          1
#define PortDriver_Channel_Function_B1_U1TX                          1
#define PortDriver_Channel_Function_B2_I2C0SCL                       3
#define PortDriver_Channel_Function_B3_I2C0SDA                       3
#define PortDriver_Channel_Function_B4_SSI2Clk                       2
#define PortDriver_Channel_Function_B5_SSI2Fss                       2
#define PortDriver_Channel_Function_B6_SSI2Rx                        2
#define PortDriver_Channel_Function_B7_SSI2Tx                        2
															         
#define PortDriver_Channel_Function_D0_SSI3Clk                       1
#define PortDriver_Channel_Function_D0_SSI1Clk                       2
#define PortDriver_Channel_Function_D0_I2C3SCL                       3
#define PortDriver_Channel_Function_D1_SSI3Fss                       1
#define PortDriver_Channel_Function_D1_SSI1Fss                       2
#define PortDriver_Channel_Function_D1_I2C3SDA                       3
#define PortDriver_Channel_Function_D2_SSI3Rx                        1
#define PortDriver_Channel_Function_D2_SSI1Rx                        2
#define PortDriver_Channel_Function_D3_SSI3Tx                        1
#define PortDriver_Channel_Function_D3_SSI1Tx                        2

#define PortDriver_Channel_Function_E4_I2C2SCL                       3
#define PortDriver_Channel_Function_E5_I2C2SDA                       3
															         
#define PortDriver_Channel_Function_F0_SSI1Clk                       2
#define PortDriver_Channel_Function_F1_SSI1Fss                       2
#define PortDriver_Channel_Function_F2_SSI1Rx                        2
#define PortDriver_Channel_Function_F3_SSI1Tx                        2




/************* interrupts sense *********************/

typedef uint8_t PortDriver_Channel_ExtiType;

#define PortDriver_Channel_Exti_Disable						  		 0
#define PortDriver_Channel_Exti_RisingEdge							 1
#define PortDriver_Channel_Exti_FallingEdge							 2
#define PortDriver_Channel_Exti_BothEdge						     3
#define PortDriver_Channel_Exti_LevelSense							 4


/*****************************************************************/
/*                  Port num type                                */
/*****************************************************************/
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
	
	PortDriver_Channel_B0,
	PortDriver_Channel_B1,
	PortDriver_Channel_B2,
	PortDriver_Channel_B3,
	PortDriver_Channel_B4,
	PortDriver_Channel_B5,
	PortDriver_Channel_B6,
	PortDriver_Channel_B7,
	
	PortDriver_Channel_C0,
	PortDriver_Channel_C1,
	PortDriver_Channel_C2,
	PortDriver_Channel_C3,
	PortDriver_Channel_C4,
	PortDriver_Channel_C5,
	PortDriver_Channel_C6,
	PortDriver_Channel_C7,
	
	PortDriver_Channel_D0,
	PortDriver_Channel_D1,
	PortDriver_Channel_D2,
	PortDriver_Channel_D3,
	PortDriver_Channel_D4,
	PortDriver_Channel_D5,
	PortDriver_Channel_D6,
	PortDriver_Channel_D7,
	
	PortDriver_Channel_E0,
	PortDriver_Channel_E1,
	PortDriver_Channel_E2,
	PortDriver_Channel_E3,
	PortDriver_Channel_E4,
	PortDriver_Channel_E5,
	PortDriver_Channel_E6_Reserved,
	PortDriver_Channel_E7_Reserved,
	
	PortDriver_Channel_F0,
	PortDriver_Channel_F1,
	PortDriver_Channel_F2,
	PortDriver_Channel_F3,
	PortDriver_Channel_F4,
	PortDriver_Channel_F5,
	PortDriver_Channel_F6_Reserved,
	PortDriver_Channel_F7_Reserved,
	
	
}PortDriver_ChannelType;


/*****************************************************************/
/*               Port Diver  Struct                              */
/*****************************************************************/
typedef struct
{
	
	PortDriver_ChannelType			    	  PortDriver_Channel;
	PortDriver_Channel_DirectionType	      PortDriver_Channel_Direction;
	PortDriver_Channel_Current_mAType	      PortDriver_Channel_Current_mA;
	PortDriver_Channel_SlewRateType		      PortDriver_Channel_SlewRate;
	PortDriver_Channel_AttachmentType	      PortDriver_Channel_Attachment;
	PortDriver_Channel_FunctionType		      PortDriver_Channel_Function;
	PortDriver_Channel_ExtiType		    	  PortDriver_Channel_Exti;
	
}PortDriver_CfgType;


#endif