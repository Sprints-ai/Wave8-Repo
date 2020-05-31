/*
 * timers_Mock.c
 *
 *  Created on: Feb 26, 2020
 *      Author: Khaled
 */


#include "timers.h"


extern uint8_t gu8_Timer_Init_Return;
extern uint8_t gu8_Timer_Start_Return;
extern uint8_t gu8_Timer_Stop_Return;
extern uint8_t gu8_Timer_Get_Value_Return;
extern uint8_t gu8_Timer_Set_Value_Return;
extern uint8_t gu8_Timer_Get_Status_Return;


uint8_t Timer_Init (Timer_Cfg_ST *Timer_Info)
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
uint8_t Timer_Get_Value (uint8_t Timer_Chan, uint16_t *Timer_Value)
{
	return gu8_Timer_Get_Value_Return;
}
uint8_t Timer_Set_Value (uint8_t Timer_Chan, uint16_t Timer_Value)
{
	return gu8_Timer_Set_Value_Return;
}


uint8_t Timer_Get_Status (uint8_t Timer_Chan, uint8_t *Timer_Status)
{
	return gu8_Timer_Get_Status_Return;
}
