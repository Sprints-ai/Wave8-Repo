/*
 * LCD_APP.c
 *
 * Created: 3/15/2020 7:29:09 PM
 * Author : Reem el-Areeny
 */ 

#include "LCD.h"
#include "SOS.h"
#include "pushButton.h"

int main(void)
{
 	SOS_Init();
 	SOS_Create(1,LCD_init,1,PERIODIC);
	SOS_Create(2,pushButtonsInit,1,PERIODIC);
	SOS_Create(3,BTN0_GetStatus,1,PERIODIC);
	SOS_Create(4,BTN1_GetStatus,1,PERIODIC);
 	SOS_Create(5,LCD_writeString,1,PERIODIC);

	//SOS_Create(2,LCD_writeGlobalChar,1,PERIODIC);
 	//while(1){
	 SOS_Run();
 	//}
}
