/*****************************************************************************/
/*					PortDriver_lCfg.c												 */	
/*****************************************************************************/
#include "PortDriver_Types.h"
#include "PortDriver_Cfg.h"

PortDriver_CfgType PortDriver_CfgArr[NUM_OF_ACTIVATED_CHANNELS] ={
	/* Channel		                 PortDriver_Channel_Direction             PortDriver_Channel_Current_mA                      PortDriver_Channel_SlewRate                PortDriver_Channel_Attachment                    PortDriver_Channel_Function             PortDriver_Channel_Exti  */
	{PortDriver_Channel_E5,      PortDriver_Channel_Direction_INPUT,      PortDriver_Channel_Current_mA_4,                   PortDriver_Channel_SlewRate_Disable,       PortDriver_Channel_Attachment_NotConnected,      PortDriver_Channel_Function_E5_ADC,      PortDriver_Channel_Exti_Disable },
	{PortDriver_Channel_D0,      PortDriver_Channel_Direction_OUTPUT,      PortDriver_Channel_Current_mA_4,                   PortDriver_Channel_SlewRate_Disable,       PortDriver_Channel_Attachment_NotConnected,     PortDriver_Channel_Function_X_DIO,      PortDriver_Channel_Exti_Disable },
	{PortDriver_Channel_D5,      PortDriver_Channel_Direction_OUTPUT,      PortDriver_Channel_Current_mA_4,                   PortDriver_Channel_SlewRate_Disable,       PortDriver_Channel_Attachment_NotConnected,     PortDriver_Channel_Function_X_DIO,      PortDriver_Channel_Exti_Disable },
	{PortDriver_Channel_D4,      PortDriver_Channel_Direction_OUTPUT,      PortDriver_Channel_Current_mA_4,                   PortDriver_Channel_SlewRate_Disable,       PortDriver_Channel_Attachment_NotConnected,     PortDriver_Channel_Function_X_DIO,      PortDriver_Channel_Exti_Disable }
};
