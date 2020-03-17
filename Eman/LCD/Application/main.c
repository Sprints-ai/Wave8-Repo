/*
 * LCD.c
 *
 * Created: 3/12/2020 11:22:04 AM
 * Author : ahmed and eman
 */ 


#include "../ECUAL/LCD.h"
#include "../Services/SOS.h"
#include "../ECUAL/IdealPushButton.h"


uint8_t question1[] = "1 3 5 7 -> 9   ?";
uint8_t question2[] = "sound is a wave?";
uint8_t question3[] = "earth is a ball?";
uint8_t question4[] = "pluto is planet?";
uint8_t question5[] = "corona is virus?";
uint8_t scoreBuff[] = "Score:";

uint8_t answers[]	  =	"1)YES 2)NO";  // display from col 2
uint8_t right[] = "/CONGRATS/";
uint8_t wrong[] = "/WRONG/   ";
str_IPB_Config IPB_Config0 = {IPB_EXTI_INT0};
str_IPB_Config IPB_Config1 = {IPB_EXTI_INT1};
void LCD_Task(void)
{
	
	static uint8_t x = 0;
	static uint8_t score = 0;
	static uint8_t u8_PushButtonFlag = IPB_0_RELEASED;
	static uint8_t u8_FirstTimeFlag = TRUE;
	
	if (u8_FirstTimeFlag)
	{
		IdealPushButton_Init(&IPB_Config0);
		IdealPushButton_Init(&IPB_Config1);
		u8_FirstTimeFlag = FALSE;
	}
	LCD_init(LCD_OS);
		switch (x)
		{
			case 0:
				LCD_displayStringRowColumn(1,0,question1,16,&x);
				break;
				
			case 1:
				LCD_displayStringRowColumn(2,0,answers,10,&x);
				break;
					
			case 2:
				IdealPushButton_GetStatus(&u8_PushButtonFlag);

				if (u8_PushButtonFlag == IPB_0_PRESSED)
				{
					LCD_displayStringRowColumn(2,0,right,10,&x);
					score++;
				}
				else if (u8_PushButtonFlag == IPB_1_PRESSED)
				{
					LCD_displayStringRowColumn(2,0,wrong,10,&x);
				}
				break;
				
			
			case 4:
				LCD_displayStringRowColumn(1,0,question2,16,&x);
				break;
				
			case 5:
				LCD_displayStringRowColumn(2,0,answers,10,&x);
				break;
				
			case 6:
				IdealPushButton_GetStatus(&u8_PushButtonFlag);

				if (u8_PushButtonFlag == IPB_0_PRESSED)
				{
					LCD_displayStringRowColumn(2,0,right,10,&x);
					score++;
				}
				else if (u8_PushButtonFlag == IPB_1_PRESSED)
				{
					LCD_displayStringRowColumn(2,0,wrong,10,&x);
				}
				break;
				
			case 8:
				LCD_displayStringRowColumn(1,0,question3,16,&x);
				break;
				
			case 9:
				LCD_displayStringRowColumn(2,0,answers,10,&x);
				break;
				
			case 10:
				IdealPushButton_GetStatus(&u8_PushButtonFlag);

				if (u8_PushButtonFlag == IPB_0_PRESSED)
				{
					LCD_displayStringRowColumn(2,0,wrong,10,&x);
				}
				else if (u8_PushButtonFlag == IPB_1_PRESSED)
				{
					LCD_displayStringRowColumn(2,0,right,10,&x);
					score++;
				}
				break;
				
			case 12:
				LCD_displayStringRowColumn(1,0,question4,16,&x);
				break;
				
			case 13:
				LCD_displayStringRowColumn(2,0,answers,10,&x);
				break;
				
			case 14:
				IdealPushButton_GetStatus(&u8_PushButtonFlag);

				if (u8_PushButtonFlag == IPB_0_PRESSED)
				{
					LCD_displayStringRowColumn(2,0,wrong,10,&x);
				}
				else if (u8_PushButtonFlag == IPB_1_PRESSED)
				{
					LCD_displayStringRowColumn(2,0,right,10,&x);
					score++;
				}
				break;
				
			case 15:
				LCD_displayStringRowColumn(1,0,question3,16,&x);
				break;
				
			case 16:
				LCD_displayStringRowColumn(2,0,answers,10,&x);
				break;
				
			case 17:
				IdealPushButton_GetStatus(&u8_PushButtonFlag);

				if (u8_PushButtonFlag == IPB_0_PRESSED)
				{
					LCD_displayStringRowColumn(2,0,right,10,&x);
					score++;
				}
				else if (u8_PushButtonFlag == IPB_1_PRESSED)
				{
					LCD_displayStringRowColumn(2,0,wrong,10,&x);
				}
				break;
			
			case 18:
				LCD_displayStringRowColumn(2,0,scoreBuff,6,&x);
				break;
			
			case 19:
				LCD_DisplayChar((score+NULL_CHAR),LCD_OS);
				break;
				
			default:
				u8_PushButtonFlag = IPB_0_RELEASED;
				x++;
		}
}

int main(void)
{
	
    SOS_Init();
	SOS_Start_Timer(1,LCD_Task,1,PERIODIC);
    while (1) 
    {
		SOS_Dispatch();
    }
	while(1);
}

