/*'
 * Tasks.c
 *
 * Created: 3/30/2020 1:04:41 AM
 *  Author: A_ayman
 */ 

#include "Service/std_types.h"
#include "Service/SOS.h"
#include "Tasks.h"



#define NOT_INITIALIZED 0
#define INITIALIZED 1

uint8_t gu8_System_Init_Flag = NOT_INITIALIZED; 

volatile uint16_t gu8_Distance;

static void GetDistance_Task();
static void Car_Task();
static void DisplayString_Task();

void System_Init_Task ()
{
	uint8_t au8_Ret_Status = E_OK;
	static uint8_t au8_System_Init_Counter = 0; 
	
	if (gu8_System_Init_Flag == NOT_INITIALIZED && au8_System_Init_Counter <3 )
	{
		au8_Ret_Status |= Us_Init();
		au8_Ret_Status |= Steering_Init();

		au8_System_Init_Counter ++;
	}
	
	if (au8_Ret_Status == E_OK)
	{
		gu8_System_Init_Flag = INITIALIZED;
		
		/* Task1 Creation Parameters*/
		SOS_tsak_s SosTask_UsTask;
		SosTask_UsTask.delay_time = 1;
		SosTask_UsTask.Priority = 2;
		SosTask_UsTask.Ptr_FunctionCall = GetDistance_Task;
		SosTask_UsTask.Task_ID = 2;
		SosTask_UsTask.SOS_mode = PERIODIC;
		SOS_Create_Task(&SosTask_UsTask);
		
		/* Task2 Creation Parameters*/
		SOS_tsak_s SosTask_CarTask;
		SosTask_CarTask.delay_time = 1;
		SosTask_CarTask.Priority = 3;
		SosTask_CarTask.Ptr_FunctionCall = Car_Task;
		SosTask_CarTask.Task_ID = 3;
		SosTask_CarTask.SOS_mode = PERIODIC;
		SOS_Create_Task(&SosTask_CarTask);
		
		/* Task3 Creation Parameters */
		SOS_tsak_s SosTask_LcdTask;
		SosTask_LcdTask.delay_time = 1;
		SosTask_LcdTask.Priority = 4;
		SosTask_LcdTask.Ptr_FunctionCall = DisplayString_Task;
		SosTask_LcdTask.Task_ID = 4;
		SosTask_LcdTask.SOS_mode = PERIODIC;
		SOS_Create_Task(&SosTask_LcdTask);
	}
	
	if (au8_System_Init_Counter == 3 && gu8_System_Init_Flag == NOT_INITIALIZED)
	{
		//system_reset;
	}	
}

void GetDistance_Task()
{
	Us_GetDistance(&gu16_US_Distance);
}

void Car_Task(void)
{
	Car_SM_Update();

}

void DisplayString_Task(void)
{
	LCD_init();
	if (init_done==TRUE)
	{
		LCD_displayInteger(gu16_US_Distance) ;
		if (sendStr_done==TRUE)
		{
			sendStr_done = FALSE ;
		}
	}
}