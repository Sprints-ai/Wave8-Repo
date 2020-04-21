/*
 * CAR_SM.c
 *
 * Created: 2/19/2020 2:43:15 AM
 * Author : Ehab , Ramadan , Reem , Eman
 */ 

#include "Tasks.h"
#include "../Services/SOS.h"
#include "../ECUAL/motor.h"
int main(void)
{
	SOS_Init();
	SOS_Start_Timer(0,CAR_Init_Task,1,ONESHOT);
	SOS_Start_Timer(1,DistanceReaderTask,1,PERIODIC);
	SOS_Start_Timer(2,CarControlTask,1,PERIODIC);

	SOS_Start_Timer(3,DisplayerTask,10,PERIODIC);
	
	while(1)
	{
		SOS_Dispatch();
	}
	
}

