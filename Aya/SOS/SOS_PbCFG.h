/*
 * SOS_PbCFG.h
 *
 * Created: 3/11/2020 1:48:56 PM
 *  Author: A_ayman
 */ 


#ifndef SOS_PBCFG_H_
#define SOS_PBCFG_H_






#include "../Utilis/std_types.h"
#include "../../MCAL/TIMERS/timers.h"


typedef struct gstr_SOS_InitConfig_t
{
	uint8_t u8_Timer_Id;
	uint8_t u8_Tmu_Res;
}gstr_SOS_InitConfig_t;

typedef struct gstr_Task_Info_t
{
	uint8_t Task_Id;
	uint16_t Time_Delay;
	uint8_t Repeat;
	void(* Ptr_Func)(void);
}gstr_Task_Info_t;

extern gstr_SOS_InitConfig_t init;


#endif /* SOS_PBCFG_H_ */