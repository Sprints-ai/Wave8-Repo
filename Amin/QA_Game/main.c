#include "SOS.h"
#include "registers.h"
#include "LCD.h"
#include "Questions.h"


int main(void){
	
	PORTD_DIR=0x00;
	PORTD_DATA=0xFF;
	GICR|=(0x80|0x20);
	MCUCR|=0x00;
	SREG|=0x80;
	
	LCD_init();
	LCD_clearScreen();
	
	OS_ConfigType OS_Config = {TIMER0,1};
	OS_ConfigType *OS_Config_Ptr = &OS_Config;
	SOS_Init(OS_Config_Ptr);
	SOS_Create_Task(100,1, Question_1);
	SOS_Create_Task(200,2, Question_2);
	SOS_Create_Task(300,3, Question_3);
	SOS_Create_Task(400,1, Question_4);
	SOS_Create_Task(500,2, Result);
	while (1){
		SOS_Run();
	}
}