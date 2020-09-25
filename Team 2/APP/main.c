/*
 ============================================================================
 Name        : main.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#include "../APP/car_sm.h"
#include "../APP/LCD_Application.h"
#include "../Service/SOS.h"
#include "../MCAL/CPU.h"
/*********************************definitions*******************************/
#define ID_0 0
#define ID_1 1
#define TRUE 1
#define FALSE 0
#define FIFTY_MS 50
#define HALF_SECOND 500
/****************************************************************************/

void Idle_Task(void)
{
	 CPU_Sleep(IDLE_MODE);
}
int main(void)
{
	sei();
	Car_SM_Init();
	LCD_init();
	SOS_InitRunable(&SOS_Configration);
	Task_Start(Car_SM_Update,ID_0,PERIODIC,FIFTY_MS);
	Task_Start(LCD_Print,ID_1,PERIODIC,HALF_SECOND);
	while(TRUE)
	{
		SOS_Runable();
	}
}
