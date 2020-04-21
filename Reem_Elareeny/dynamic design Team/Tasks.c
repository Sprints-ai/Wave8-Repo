/*
 * Tasks.c
 *
 * Created: 3/30/2020 4:13:59 PM
 *  Author: Ehab , Ramadan , Reem , Eman
 */ 

#include "Tasks.h"


uint16_t gu16_Distance = 0;

void CAR_Init_Task(void)
{
	Car_SM_Init();
	
	Displayer_init();
	
	DistanceReader_Init();
}
void DistanceReaderTask(void)
{
	DistanceReader_GetValue(&gu16_Distance);

}

void CarControlTask(void)
{
	
// 	static uint16_t u16_Distance = 0;
//	if (u16_Distance != gu16_Distance)
//	{
//		u16_Distance = gu16_Distance;
	//}

//	Car_SM_Update(u16_Distance);
	Car_SM_Update(gu16_Distance);

}

void DisplayerTask(void)
{
	//displayer_clear();

	Displayer_write_digit(gu16_Distance);
}

