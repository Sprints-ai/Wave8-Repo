/*
 * main.c
 *
 * Created: 3/3/2020 12:05:08 PM
 * Author : Abdallah & Amin
 */ 

#include "BCM.h"

int main(void)
{
	BCM_Init (SPI_CH);
	BCM_Receive(Data_Size,SPI_CH);
	
	//this is for test
	PORTC_DIR = 0xFF;
	PORTC_DATA = 0x00;
	
	while (1)
	{
		BCM_RxDispatch();
	}
}
