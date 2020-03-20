/*
 * LCD_Project.c
 *
 * Created: 14/03/2020 06:38:48 م
 * Author : TOSHIBA
 */ 



#include "Infrastructure/registers.h" 
#include "MCAL/DIO/DIO.h"
#include "HAL/pushButton/pushButton.h"
#include "Service/SOS/SOS.h"
#include "Service/SOS/SOS_PbCfg.h"
#include "HAL/LCD/LCD.h"
#include "Application/LCD_APP.h"


#define INIT_TASK_ID			0
#define GAME_TASK_ID			1
#define INIT_TASK_PERIODECITY	1
#define GAME_TASK_PERIODECITY	5
#define UNII_TASK				0

static uint8_t u8_InitTaskStatus = UNII_TASK;


void INIT_TASK(void)
{
	
	if (u8_InitTaskStatus !=INIT_DONE)
	{
	
		u8_InitTaskStatus = QuestionGame_Init();
		
	}
	
	else 
	{
		SOS_Delete_Task(INIT_TASK_ID) ;
	}

}

void Game_TASK(void){
	if (u8_InitTaskStatus == INIT_DONE)
		QuestionGame_RUN();
}
int main(void)
{
	


	strSOS_CreatTask_t INIT_task={INIT_TASK_PERIODECITY,PERUDIC,INIT_TASK_ID,INIT_TASK};
	strSOS_CreatTask_t LCD_Write_task = {GAME_TASK_PERIODECITY,PERUDIC,GAME_TASK_ID,Game_TASK};
	SOS_Init(&gstr_SOS_PbCfg);
	SOS_Create_Task(&INIT_task);
	SOS_Create_Task(&LCD_Write_task);
	
    SOS_Run();
}

