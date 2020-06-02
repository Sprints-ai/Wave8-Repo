/*
 * port_lcfg.c
 *
 *      Author: Abdallah Heidar
 */
 
#include "Port_lCfg.h"
#include "MCU_hw.h"

PortDriver_CfgType PortDriver_CfgArr[NUM_OF_ACTIVATED_CHANNELS] ={
	{PortDriver_Ch_E1,      PortDriver_Ch_Direction_INPUT,      PortDriver_Ch_Current_mA_4,                   PortDriver_Ch_SlewRate_Disable,       PortDriver_Ch_Attachment_NotConnected,      PortDriver_Ch_Function_X_DIO,      PortDriver_Ch_Exti_Disable },
	{PortDriver_Ch_A0,      PortDriver_Ch_Direction_INPUT,      PortDriver_Ch_Current_mA_4,                   PortDriver_Ch_SlewRate_Disable,       PortDriver_Ch_Attachment_PullupRes,         PortDriver_Ch_Function_X_DIO,      PortDriver_Ch_Exti_Disable },
	{PortDriver_Ch_B3,      PortDriver_Ch_Direction_INPUT,      PortDriver_Ch_Current_mA_4,                   PortDriver_Ch_SlewRate_Disable,       PortDriver_Ch_Attachment_NotConnected,      PortDriver_Ch_Function_X_DIO,      PortDriver_Ch_Exti_Disable },
};