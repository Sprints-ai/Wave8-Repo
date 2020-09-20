/*
 * tmuapp.c
 *
 * Created: 24-Feb-20 11:26:07 AM
 * Author : ahmed
 */ 

/************************************************************************/
/*							INCLUDES                                    */
/************************************************************************/
//#include <avr/io.h>
#include "/LCD_APP/SERVICE/SOS.h"
#include "/LCD_APP/MCAL/DIO.h"
#include "Error_table.h"
#include "/LCD_APP/MCAL/interrupt.h"
#include "/LCD_APP/SERVICE/LowPower.h"
#include "/LCD_APP/SERVICE/lcd.h"
/************************************************************************/
/*					MAIN                                                */
/************************************************************************/





int main(void)
{
	
  	Init_Create_tasks();

while(1)
{
// 
 	SOS_Dispatch();
// 	
 	Sleep_Mode();
	
}
}

