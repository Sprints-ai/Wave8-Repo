/*
 * main.c
 *
 *  Created on: Mar 2, 2020
 *      Author: Youssef Harby & Mohamed Ramadan
 */


/*- INCLUDES -----------------------------------------------*/

#include "BCM.h"


/*- DEFINITIONS --------------------------------------------*/

#define OVERHEAD 		4
#define ELEMENTS(X)		(X + OVERHEAD)

#define UART_DONE		1
#define UART_NOT_DONE	0

/*- GLOBAL STATIC VARIABLES --------------------------------*/

//static uint8_t testing_arr[ELEMENTS(21)] = {1, 2, 3, 4, 5, 6, 7,
//		8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};

volatile sint8_t ReceivedString[ELEMENTS(20)];

volatile uint8_t uart_counter = 0;

static uint8_t i = 0;

void Uart_receivingApp(void)
{
	ReceivedString[i] = UART_receive();
	uart_counter++;
	i++;
}

int main(void)
{
	uint8_t UART_status = 0;
	UART_ConfigType UART_cfg = {
			UART_ASYNCHRONOUS_MODE,
			UART_RECEIVER_MODE,
			UART_INTERRUPT_ENABLED,
			UART_EIGHT_BITS,
			UART_PARITY_DISABLED,
			UART_ONE_STOP_BIT
	};

	strBcmConfig_t BCM_cfg = {
			BCM_SPI_ID,
			BCM_TRANSMIT
	};

	strBcmSendConfig_t BCM_startCfg = {
			BCM_SPI_ID,
			(uint8_t*)ReceivedString,
			ELEMENTS(20)
	};


	BCM_Init(&BCM_cfg);

	UART_RXC_setCallBack(&Uart_receivingApp);

	UART_init(&UART_cfg);

	sei();

	while(1)
	{
		if(uart_counter == ELEMENTS(20))
			UART_status = UART_DONE;

		if(UART_status == UART_DONE)
		{
			if(uart_counter == ELEMENTS(20))
			{
				BCM_Send(&BCM_startCfg);
				uart_counter++;
			}

			BCM_TxDispatch();
		}
	}
}


//strBcmConfig_t BCM_cfg = {
//		BCM_SPI_ID,
//		BCM_TRANSMIT
//};
//
//strBcmSendConfig_t BCM_startCfg = {
//		BCM_SPI_ID,
//		(uint8_t*)testing_arr,
//		ELEMENTS(21)
//};
//
//BCM_Init(&BCM_cfg);
//
//sei();
//
//BCM_Send(&BCM_startCfg);
//
//while(1)
//{
//	BCM_TxDispatch();
//}