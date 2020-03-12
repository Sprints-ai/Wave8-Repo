#include "MCAL/TIMERS/Timers.h"

uint8_t gu8_Timer_Init_Return;
uint8_t gu8_Timer_Start_Return;
uint8_t gu8_Timer_Stop_Return;
uint8_t gu8_Timer_Get_Value_Return;
uint8_t gu8_Timer_Set_Value_Return;
uint8_t gu8_Timer_Get_Status_Return;

uint8_t Timer_Init(gstr_TimerCfg_t *Timer_Info)
{
	return gu8_Timer_Init_Return;
}
uint8_t Timer_Start (uint8_t Timer_Chan, uint16_t Timer_Count_No)
{
	return gu8_Timer_Start_Return;
}
uint8_t Timer_Stop (uint8_t Timer_Chan)
{
	return gu8_Timer_Stop_Return;
}
uint8_t Timer_GetValue (uint8_t Timer_Chan, uint16_t *Timer_Value)
{
	return gu8_Timer_Get_Value_Return;
}
uint8_t Timer_SetValue (uint8_t Timer_Chan, uint16_t Timer_Value)
{
	return gu8_Timer_Set_Value_Return;
}


