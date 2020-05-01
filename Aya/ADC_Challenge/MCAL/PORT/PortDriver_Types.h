/*
 * PortDriver_Types.h
 *
 * Created: 4/8/2020 6:27:22 PM
 *  Author: Khaled
 */ 


#ifndef PORTDRIVER_TYPES_H_
#define PORTDRIVER_TYPES_H_

#include "../../SL/ARM_STD_t.h"


//OK
typedef uint8_t PortDriver_Channel_DirectionType;
#define PORTDRIVER_CHANNEL_DIRECTION_INPUT			 	   0
#define PORTDRIVER_CHANNEL_DIRECTION_OUTPUT				   1
                                                           
                                                           
//OK                                                           
typedef uint8_t PortDriver_Channel_Current_mAType;         
#define PORTDRIVER_CHANNEL_CURRENT_mA_2			 		   0
#define PORTDRIVER_CHANNEL_CURRENT_mA_4			 		   1
#define PORTDRIVER_CHANNEL_CURRENT_mA_8			 		   2
                                                           
                                                           
//OK			                                               
typedef uint8_t PortDriver_Channel_SlewRateType;           
#define PORTDRIVER_CHANNEL_SLEWRATE_DISABLE				   0
#define PORTDRIVER_CHANNEL_SLEWRATE_ENABLE				   1


//OK
typedef uint8_t PortDriver_Channel_AttachmentType;
#define PORTDRIVER_CHANNEL_ATTACHMENT_NOTCONNECTED		   0
#define PORTDRIVER_CHANNEL_ATTACHMENT_PULLUPRES			   1
#define PORTDRIVER_CHANNEL_ATTACHMENT_PULLDOWNRES		   2
#define PORTDRIVER_CHANNEL_ATTACHMENT_OPENDRAIN			   3


//Ok 
typedef uint8_t PortDriver_Channel_FunctionType;
#define PORTDRIVER_CHANNEL_FUNCTION_X_DIO                  0

#define PORTDRIVER_CHANNEL_FUNCTION_F0_C0o                 9
#define PORTDRIVER_CHANNEL_FUNCTION_F1_C1o                 9

#define PORTDRIVER_CHANNEL_FUNCTION_F0_CAN0Rx              3
#define PORTDRIVER_CHANNEL_FUNCTION_B4_CAN0Rx              8
#define PORTDRIVER_CHANNEL_FUNCTION_E4_CAN0Rx              8
#define PORTDRIVER_CHANNEL_FUNCTION_F3_CAN0Tx              3
#define PORTDRIVER_CHANNEL_FUNCTION_B5_CAN0Tx              8
#define PORTDRIVER_CHANNEL_FUNCTION_E5_CAN0Tx              8
#define PORTDRIVER_CHANNEL_FUNCTION_A0_CAN1Rx              8
#define PORTDRIVER_CHANNEL_FUNCTION_A1_CAN1Tx              8

#define PORTDRIVER_CHANNEL_FUNCTION_B2_I2C0SCL             3
#define PORTDRIVER_CHANNEL_FUNCTION_B3_I2C0SDA             3
#define PORTDRIVER_CHANNEL_FUNCTION_A6_I2C1SCL             3
#define PORTDRIVER_CHANNEL_FUNCTION_A7_I2C1SDA             3
#define PORTDRIVER_CHANNEL_FUNCTION_E4_I2C2SCL             3
#define PORTDRIVER_CHANNEL_FUNCTION_E5_I2C2SDA             3
#define PORTDRIVER_CHANNEL_FUNCTION_D0_I2C3SCL             3
#define PORTDRIVER_CHANNEL_FUNCTION_D1_I2C3SDA             3

#define PORTDRIVER_CHANNEL_FUNCTION_F4_IDX0                6
#define PORTDRIVER_CHANNEL_FUNCTION_D3_IDX0                6
#define PORTDRIVER_CHANNEL_FUNCTION_C4_IDX1            	   6

#define PORTDRIVER_CHANNEL_FUNCTION_F2_M0FAULT0            4
#define PORTDRIVER_CHANNEL_FUNCTION_D6_M0FAULT0            4
#define PORTDRIVER_CHANNEL_FUNCTION_D2_M0FAULT0            4

#define PORTDRIVER_CHANNEL_FUNCTION_B6_M0PWM0              4
#define PORTDRIVER_CHANNEL_FUNCTION_B7_M0PWM1              4
#define PORTDRIVER_CHANNEL_FUNCTION_B4_M0PWM2              4
#define PORTDRIVER_CHANNEL_FUNCTION_B5_M0PWM3              4
#define PORTDRIVER_CHANNEL_FUNCTION_E4_M0PWM4              4
#define PORTDRIVER_CHANNEL_FUNCTION_E5_M0PWM5              4
#define PORTDRIVER_CHANNEL_FUNCTION_C4_M0PWM6              4
#define PORTDRIVER_CHANNEL_FUNCTION_D0_M0PWM6              4
#define PORTDRIVER_CHANNEL_FUNCTION_C5_M0PWM7              4
#define PORTDRIVER_CHANNEL_FUNCTION_D1_M0PWM7              4                                                          

#define PORTDRIVER_CHANNEL_FUNCTION_F4_M1FAULT0            5

#define PORTDRIVER_CHANNEL_FUNCTION_D0_M1PWM0              5
#define PORTDRIVER_CHANNEL_FUNCTION_D1_M1PWM1              5
#define PORTDRIVER_CHANNEL_FUNCTION_A6_M1PWM2              5
#define PORTDRIVER_CHANNEL_FUNCTION_E4_M1PWM2              5
#define PORTDRIVER_CHANNEL_FUNCTION_A7_M1PWM3              5
#define PORTDRIVER_CHANNEL_FUNCTION_E5_M1PWM3              5
#define PORTDRIVER_CHANNEL_FUNCTION_F0_M1PWM4              5
#define PORTDRIVER_CHANNEL_FUNCTION_F1_M1PWM5              5
#define PORTDRIVER_CHANNEL_FUNCTION_F2_M1PWM6              5
#define PORTDRIVER_CHANNEL_FUNCTION_F3_M1PWM7              5

#define PORTDRIVER_CHANNEL_FUNCTION_D7_NMI                 8
#define PORTDRIVER_CHANNEL_FUNCTION_F0_NMI                 8

#define PORTDRIVER_CHANNEL_FUNCTION_F0_PhA0                6
#define PORTDRIVER_CHANNEL_FUNCTION_D6_PhA0                6
#define PORTDRIVER_CHANNEL_FUNCTION_C5_PhA1                6
#define PORTDRIVER_CHANNEL_FUNCTION_D7_PhB0                6
#define PORTDRIVER_CHANNEL_FUNCTION_F1_PhB0                6
#define PORTDRIVER_CHANNEL_FUNCTION_C6_PhB1                6

#define PORTDRIVER_CHANNEL_FUNCTION_A2_SSI0Clk             2          
#define PORTDRIVER_CHANNEL_FUNCTION_A3_SSI0Fss             2          
#define PORTDRIVER_CHANNEL_FUNCTION_A4_SSI0Rx              2          
#define PORTDRIVER_CHANNEL_FUNCTION_A5_SSI0Tx              2          
#define PORTDRIVER_CHANNEL_FUNCTION_F2_SSI1Clk             2          
#define PORTDRIVER_CHANNEL_FUNCTION_D0_SSI1Clk             2          
#define PORTDRIVER_CHANNEL_FUNCTION_F3_SSI1Fss             2          
#define PORTDRIVER_CHANNEL_FUNCTION_D1_SSI1Fss             2          
#define PORTDRIVER_CHANNEL_FUNCTION_F0_SSI1Rx              2          
#define PORTDRIVER_CHANNEL_FUNCTION_D2_SSI1Rx              2          
#define PORTDRIVER_CHANNEL_FUNCTION_F1_SSI1Tx              2          
#define PORTDRIVER_CHANNEL_FUNCTION_D3_SSI1Tx              2          
#define PORTDRIVER_CHANNEL_FUNCTION_B4_SSI2Clk             2          
#define PORTDRIVER_CHANNEL_FUNCTION_B5_SSI2Fss             2          
#define PORTDRIVER_CHANNEL_FUNCTION_B6_SSI2Rx              2          
#define PORTDRIVER_CHANNEL_FUNCTION_B7_SSI2Tx              2          
#define PORTDRIVER_CHANNEL_FUNCTION_D0_SSI3Clk             1
#define PORTDRIVER_CHANNEL_FUNCTION_D1_SSI3Fss             1
#define PORTDRIVER_CHANNEL_FUNCTION_D2_SSI3Rx              1
#define PORTDRIVER_CHANNEL_FUNCTION_D3_SSI3Tx              1

#define PORTDRIVER_CHANNEL_FUNCTION_C0_SWCLK               1
#define PORTDRIVER_CHANNEL_FUNCTION_C1_SWDIO               1
#define PORTDRIVER_CHANNEL_FUNCTION_C3_SWO                 1

#define PORTDRIVER_CHANNEL_FUNCTION_B6_T0CCP0              7          
#define PORTDRIVER_CHANNEL_FUNCTION_F0_T0CCP0              7          
#define PORTDRIVER_CHANNEL_FUNCTION_B7_T0CCP1              7          
#define PORTDRIVER_CHANNEL_FUNCTION_F1_T0CCP1              7          
#define PORTDRIVER_CHANNEL_FUNCTION_F2_T1CCP0              7          
#define PORTDRIVER_CHANNEL_FUNCTION_B4_T1CCP0              7          
#define PORTDRIVER_CHANNEL_FUNCTION_F3_T1CCP1              7          
#define PORTDRIVER_CHANNEL_FUNCTION_B5_T1CCP1              7          
#define PORTDRIVER_CHANNEL_FUNCTION_F4_T2CCP0              7          
#define PORTDRIVER_CHANNEL_FUNCTION_B0_T2CCP0              7          
#define PORTDRIVER_CHANNEL_FUNCTION_B1_T2CCP1              7          
#define PORTDRIVER_CHANNEL_FUNCTION_B2_T3CCP0              7          
#define PORTDRIVER_CHANNEL_FUNCTION_B3_T3CCP1              7          
#define PORTDRIVER_CHANNEL_FUNCTION_C0_T4CCP0              7          
#define PORTDRIVER_CHANNEL_FUNCTION_C1_T4CCP1              7          
#define PORTDRIVER_CHANNEL_FUNCTION_C2_T5CCP0              7          
#define PORTDRIVER_CHANNEL_FUNCTION_C3_T5CCP1              7          

#define PORTDRIVER_CHANNEL_FUNCTION_C0_TCK                 1             

#define PORTDRIVER_CHANNEL_FUNCTION_C2_TDI                 1            
#define PORTDRIVER_CHANNEL_FUNCTION_C3_TDO                 1            

#define PORTDRIVER_CHANNEL_FUNCTION_C1_TMS                 1

#define PORTDRIVER_CHANNEL_FUNCTION_F3_TRCLK               14

#define PORTDRIVER_CHANNEL_FUNCTION_F2_TRD0                14
#define PORTDRIVER_CHANNEL_FUNCTION_F1_TRD1                14

#define PORTDRIVER_CHANNEL_FUNCTION_A0_U0Rx                1 
#define PORTDRIVER_CHANNEL_FUNCTION_A1_U0Tx                1
#define PORTDRIVER_CHANNEL_FUNCTION_C5_U1CTS               8
#define PORTDRIVER_CHANNEL_FUNCTION_F1_U1CTS               1
#define PORTDRIVER_CHANNEL_FUNCTION_C4_U1RTS               8
#define PORTDRIVER_CHANNEL_FUNCTION_F0_U1RTS               1
#define PORTDRIVER_CHANNEL_FUNCTION_C4_U1Rx                2 
#define PORTDRIVER_CHANNEL_FUNCTION_B0_U1Rx                1
#define PORTDRIVER_CHANNEL_FUNCTION_C5_U1Tx                2
#define PORTDRIVER_CHANNEL_FUNCTION_B1_U1Tx                1           
#define PORTDRIVER_CHANNEL_FUNCTION_D6_U2Rx                1
#define PORTDRIVER_CHANNEL_FUNCTION_D7_U2Tx                1           
#define PORTDRIVER_CHANNEL_FUNCTION_C6_U3Rx                1           
#define PORTDRIVER_CHANNEL_FUNCTION_C7_U3Tx                1
#define PORTDRIVER_CHANNEL_FUNCTION_C4_U4Rx                1
#define PORTDRIVER_CHANNEL_FUNCTION_C5_U4Tx                1
#define PORTDRIVER_CHANNEL_FUNCTION_E4_U5Rx                1
#define PORTDRIVER_CHANNEL_FUNCTION_E5_U5Tx                1           
#define PORTDRIVER_CHANNEL_FUNCTION_D4_U6Rx                1           
#define PORTDRIVER_CHANNEL_FUNCTION_D5_U6Tx                1
#define PORTDRIVER_CHANNEL_FUNCTION_E0_U7Rx                1
#define PORTDRIVER_CHANNEL_FUNCTION_E1_U7Tx                1   

#define PORTDRIVER_CHANNEL_FUNCTION_F4_USB0EPEN            8
#define PORTDRIVER_CHANNEL_FUNCTION_C6_USB0EPEN            8
#define PORTDRIVER_CHANNEL_FUNCTION_D2_USB0EPEN            8
#define PORTDRIVER_CHANNEL_FUNCTION_C7_USB0PFLT            8
#define PORTDRIVER_CHANNEL_FUNCTION_D3_USB0PFLT            8               

#define PORTDRIVER_CHANNEL_FUNCTION_C4_WT0CCP0             7
#define PORTDRIVER_CHANNEL_FUNCTION_C5_WT0CCP1             7
#define PORTDRIVER_CHANNEL_FUNCTION_C6_WT1CCP0             7
#define PORTDRIVER_CHANNEL_FUNCTION_C7_WT1CCP1             7
#define PORTDRIVER_CHANNEL_FUNCTION_D0_WT2CCP0             7
#define PORTDRIVER_CHANNEL_FUNCTION_D1_WT2CCP1             7
#define PORTDRIVER_CHANNEL_FUNCTION_D2_WT3CCP0             7
#define PORTDRIVER_CHANNEL_FUNCTION_D3_WT3CCP1             7
#define PORTDRIVER_CHANNEL_FUNCTION_D4_WT4CCP0             7
#define PORTDRIVER_CHANNEL_FUNCTION_D5_WT4CCP1             7
#define PORTDRIVER_CHANNEL_FUNCTION_D6_WT5CCP0             7
#define PORTDRIVER_CHANNEL_FUNCTION_D7_WT5CCP1             7

#define PORTDRIVER_CHANNEL_FUNCTION_E3_AIN0                20
#define PORTDRIVER_CHANNEL_FUNCTION_E2_AIN1                20
#define PORTDRIVER_CHANNEL_FUNCTION_E1_AIN2                20
#define PORTDRIVER_CHANNEL_FUNCTION_E0_AIN3                20
#define PORTDRIVER_CHANNEL_FUNCTION_D3_AIN4                20
#define PORTDRIVER_CHANNEL_FUNCTION_D2_AIN5                20
#define PORTDRIVER_CHANNEL_FUNCTION_D1_AIN6                20
#define PORTDRIVER_CHANNEL_FUNCTION_D0_AIN7                20
#define PORTDRIVER_CHANNEL_FUNCTION_E5_AIN8                20
#define PORTDRIVER_CHANNEL_FUNCTION_E4_AIN9                20
#define PORTDRIVER_CHANNEL_FUNCTION_B4_AIN10               20
#define PORTDRIVER_CHANNEL_FUNCTION_B5_AIN11               20
#define PORTDRIVER_CHANNEL_FUNCTION_C6_C0POSITIVE          20
#define PORTDRIVER_CHANNEL_FUNCTION_C7_C0NEGATIVE          20
#define PORTDRIVER_CHANNEL_FUNCTION_C5_C1POSITIVE          20
#define PORTDRIVER_CHANNEL_FUNCTION_C4_C1NEGATIVE          20
#define PORTDRIVER_CHANNEL_FUNCTION_D4_USB0DM              20
#define PORTDRIVER_CHANNEL_FUNCTION_D5_USB0DP              20
#define PORTDRIVER_CHANNEL_FUNCTION_B0_USB0ID              20
#define PORTDRIVER_CHANNEL_FUNCTION_B1_USB0VBUS            20


//OK
typedef uint8_t PortDriver_Channel_ExtiType;
#define PORTDRIVER_CHANNEL_EXTI_DISABLE					   	0
#define PORTDRIVER_CHANNEL_EXTI_RISIN_GEDGE				   	11
#define PORTDRIVER_CHANNEL_EXTI_FALLIN_GEDGE		    	12
#define PORTDRIVER_CHANNEL_EXTI_BOTH_EDGE		        	13
#define PORTDRIVER_CHANNEL_EXTI_HIGH_LEVEL_SENSE		   	24
#define PORTDRIVER_CHANNEL_EXTI_LOW_LEVEL_SENSE	    	   	25


//OK
typedef uint8_t PortDriver_ChannelNumType;
#define	PORTDRIVER_CHANNEL_NUM_0                           0
#define	PORTDRIVER_CHANNEL_NUM_1                           1
#define	PORTDRIVER_CHANNEL_NUM_2                           2
#define	PORTDRIVER_CHANNEL_NUM_3                           3
#define	PORTDRIVER_CHANNEL_NUM_4                           4
#define	PORTDRIVER_CHANNEL_NUM_5                           5
#define	PORTDRIVER_CHANNEL_NUM_6                           6
#define	PORTDRIVER_CHANNEL_NUM_7                           7



//OK
typedef uint8_t PortDriver_PortNumType;
#define	PORTDRIVER_PORTNUM_A                               0                    
#define	PORTDRIVER_PORTNUM_B                               1                    
#define	PORTDRIVER_PORTNUM_C                               2                    
#define	PORTDRIVER_PORTNUM_D                               3                    
#define	PORTDRIVER_PORTNUM_E                               4                    
#define	PORTDRIVER_PORTNUM_F                               5                    


//OK
typedef uint8_t PortDriver_ChannelType;
#define	PORTDRIVER_CHANNEL_A0                              0
#define	PORTDRIVER_CHANNEL_A1                              1
#define	PORTDRIVER_CHANNEL_A2                              2
#define	PORTDRIVER_CHANNEL_A3                              3
#define	PORTDRIVER_CHANNEL_A4                              4
#define	PORTDRIVER_CHANNEL_A5                              5
#define	PORTDRIVER_CHANNEL_A6                              6
#define	PORTDRIVER_CHANNEL_A7                              7

#define	PORTDRIVER_CHANNEL_B0                              8
#define	PORTDRIVER_CHANNEL_B1                              9
#define	PORTDRIVER_CHANNEL_B2                              10
#define	PORTDRIVER_CHANNEL_B3                              11
#define	PORTDRIVER_CHANNEL_B4                              12
#define	PORTDRIVER_CHANNEL_B5                              13
#define	PORTDRIVER_CHANNEL_B6                              14
#define	PORTDRIVER_CHANNEL_B7                              15

#define	PORTDRIVER_CHANNEL_C0                              16
#define	PORTDRIVER_CHANNEL_C1                              17
#define	PORTDRIVER_CHANNEL_C2                              18
#define	PORTDRIVER_CHANNEL_C3                              19
#define	PORTDRIVER_CHANNEL_C4                              20
#define	PORTDRIVER_CHANNEL_C5                              21
#define	PORTDRIVER_CHANNEL_C6                              22
#define	PORTDRIVER_CHANNEL_C7                              23

#define	PORTDRIVER_CHANNEL_D0                              24
#define	PORTDRIVER_CHANNEL_D1                              25
#define	PORTDRIVER_CHANNEL_D2                              26
#define	PORTDRIVER_CHANNEL_D3                              27
#define	PORTDRIVER_CHANNEL_D4                              28
#define	PORTDRIVER_CHANNEL_D5                              29
#define	PORTDRIVER_CHANNEL_D6                              30 
#define	PORTDRIVER_CHANNEL_D7                              31

#define	PORTDRIVER_CHANNEL_E0                              32
#define	PORTDRIVER_CHANNEL_E1                              33
#define	PORTDRIVER_CHANNEL_E2                              34
#define	PORTDRIVER_CHANNEL_E3                              35
#define	PORTDRIVER_CHANNEL_E4                              36
#define	PORTDRIVER_CHANNEL_E5                              37
#define	PORTDRIVER_CHANNEL_E6_RESERVED                     38
#define	PORTDRIVER_CHANNEL_E7_RESERVED                     39

#define	PORTDRIVER_CHANNEL_F0                              40
#define	PORTDRIVER_CHANNEL_F1                              41
#define	PORTDRIVER_CHANNEL_F2                              42
#define	PORTDRIVER_CHANNEL_F3                              43
#define	PORTDRIVER_CHANNEL_F4                              44
#define	PORTDRIVER_CHANNEL_F5_RESERVED                     45
#define	PORTDRIVER_CHANNEL_F6_RESERVED                     46
#define	PORTDRIVER_CHANNEL_F7_RESERVED	                   47




typedef struct
{
	PortDriver_ChannelType				       Channel;
	PortDriver_Channel_DirectionType	   PortDriver_Channel_Direction;
	PortDriver_Channel_Current_mAType	   PortDriver_Channel_Current_mA;
	PortDriver_Channel_SlewRateType		   PortDriver_Channel_SlewRate;
	PortDriver_Channel_AttachmentType	   PortDriver_Channel_Attachment;
	PortDriver_Channel_FunctionType		   PortDriver_Channel_Function;
	PortDriver_Channel_ExtiType			     PortDriver_Channel_Exti;
}PortDriver_CfgType;



#endif /* PORTDRIVER_TYPES_H_ */
