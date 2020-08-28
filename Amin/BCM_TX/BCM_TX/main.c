/*
 * B_C_M.c
 *
 * Created: 3/3/2020 12:05:08 PM
 * Author : Abdallah & Amin
 */ 

#include "BCM.h"

int main(void)
{

uint8_t send_str[] = "SendSend";
	BCM_Init (SPI_CH);
	BCM_Send(send_str, 8, SPI_CH);
	/*This is for Test
	PORTC_DIR = 0xFF;
	PORTC_DATA = 0x00;
	*/
	while (1)
	{
		BCM_TxDispatch();
	}
}