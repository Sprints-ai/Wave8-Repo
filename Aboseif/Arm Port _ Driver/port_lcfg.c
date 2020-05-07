/*
 * port_lcfg.c
 *
 * Created: 2020-04-12 4:20:42 PM
 *  Author: EbrahimOseif
 */
 
#include "Port_lCfg.h"
#include "MCU_hw.h"




PortDriver_CfgType PortDriver_CfgArr[NUM_OF_ACTIVATED_CHANNELS] ={
	/* Channel		                 PortDriver_Channel_Direction             PortDriver_Channel_Current_mA                      PortDriver_Channel_SlewRate                PortDriver_Channel_Attachment                    PortDriver_Channel_Function             PortDriver_Channel_Exti  */
	{PortDriver_Channel_E1,      PortDriver_Channel_Direction_INPUT,      PortDriver_Channel_Current_mA_4,                   PortDriver_Channel_SlewRate_Disable,       PortDriver_Channel_Attachment_NotConnected,      PortDriver_Channel_Function_X_DIO,      PortDriver_Channel_Exti_Disable },
	{PortDriver_Channel_A0,      PortDriver_Channel_Direction_INPUT,      PortDriver_Channel_Current_mA_4,                   PortDriver_Channel_SlewRate_Disable,       PortDriver_Channel_Attachment_PullupRes,         PortDriver_Channel_Function_X_DIO,      PortDriver_Channel_Exti_Disable },
	{PortDriver_Channel_B3,      PortDriver_Channel_Direction_INPUT,      PortDriver_Channel_Current_mA_4,                   PortDriver_Channel_SlewRate_Disable,       PortDriver_Channel_Attachment_NotConnected,      PortDriver_Channel_Function_X_DIO,      PortDriver_Channel_Exti_Disable },
};