/*
 * SOS.c
 *
 * Created: 3/11/2020 9:52:12 AM
 * Author : Team 5
 */


#include "Service/SOS.h"
#include "util/interrupt.h"
#include <stdlib.h>
#include "Tasks.h"


/**=========================================================================*
 *								Main Function								*
 *==========================================================================*/

int main(void)
{
	SOS_Cfg_s SOS_cfg1;
	SOS_cfg1.Timer_channel = SOS_TIMER_CH2;
	SOS_cfg1.SOS_Reselution = reselution_one_mili;
	SOS_Init(&SOS_cfg1);
	
	SOS_tsak_s SosTask_InitializationTask;
	SosTask_InitializationTask.delay_time = 1;
	SosTask_InitializationTask.Priority = 1;
	SosTask_InitializationTask.Ptr_FunctionCall = System_Init_Task;
	SosTask_InitializationTask.Task_ID = 1;
	SosTask_InitializationTask.SOS_mode = ONESHOT;
	SOS_Create_Task(&SosTask_InitializationTask);
	
	sei();

	while(1)
	{
		SOS_Run();
	}
}
