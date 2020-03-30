/*
 * CarDynamicDesign.c
 *
 * Created: 3/30/2020 2:30:37 AM
 *  Author: Reem
 */ 

#include "Services/includes/SOS.h"
#include "Services/includes/CPU_load.h"
#include "ECUAL/includes/Us.h"
#include "App/includes/car_sm.h"
#include "ECUAL/includes/LCD.h"


void SystemInit(void);
void Toggle1(void);
void Toggle2(void);
int main(void)
{
	strSOS_TASK_Cfg_t Task1;
	strSOS_TASK_Cfg_t Task2;
	strSOS_TASK_Cfg_t Task3;
	strSOS_TASK_Cfg_t Task4;
	strSOS_TASK_Cfg_t Task5;
	DIO_Cfg_s dioCfg;
	dioCfg.GPIO = GPIOA;
	dioCfg.pins = BIT7|BIT6|BIT5;	
	dioCfg.dir = OUTPUT;
	DIO_init(&dioCfg);
	
	SharedRes_Init();
	SOS_Init();

//SystemInit();
	
	Task1.Delay_TimeMs = 12;
	Task1.Priority=1;
	Task1.SOS_Cbk_ptr =SystemInit;
	Task1.Task_id=1;
	Task1.SOS_MODE = ONE_SHOT;
	
	Task2.Delay_TimeMs = 12;
	Task2.Priority=2;
	Task2.SOS_Cbk_ptr =Us_Trigger;
	Task2.Task_id=2;
	Task2.SOS_MODE = PERIODIC;
	
	Task3.Delay_TimeMs = 12;
	Task3.Priority=3;
	Task3.SOS_Cbk_ptr =Us_GetDistance;
	Task3.Task_id=3;
	Task3.SOS_MODE = PERIODIC;
	
	Task4.Delay_TimeMs = 24;
	Task4.Priority=4;
	Task4.SOS_Cbk_ptr =LCD_Runnable;
	Task4.Task_id=4;
	Task4.SOS_MODE = PERIODIC;
	
	Task5.Delay_TimeMs = 144;
	Task5.Priority=5;
	Task5.SOS_Cbk_ptr =Car_SM_Update;
	Task5.Task_id=5;
	Task5.SOS_MODE = PERIODIC;
	

	SOS_Create_Task(&Task1);
	SOS_Create_Task(&Task2);
	SOS_Create_Task(&Task3);
	SOS_Create_Task(&Task4);
	SOS_Create_Task(&Task5);
	
    while(1)
    {
       SOS_Run();
	   CPU_Sleep();
    }
}
void SystemInit(void)
{
	Car_SM_Init();
	Us_Init();
	
}
