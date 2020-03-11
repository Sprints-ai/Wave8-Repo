/*BCM Sender
 * main.c
 *
 *  Created on: Mar 2, 2020
 *      Author: Youssef Harby 
 */


/*- INCLUDES -----------------------------------------------*/

#include "BCM.h"
#include "util/delay.h"
#include <string.h>


/*- DEFINITIONS --------------------------------------------*/

#define OVERHEAD 		4
#define ELEMENTS(X)		(X + OVERHEAD)

#define UART_DONE		1
#define UART_NOT_DONE	0

#define BCM_INITIALIZED			1
#define BCM_NOT_INITIALIZED		0

#define BCM_DONE		1
#define BCM_NOT_DONE	0

/*- GLOBAL STATIC VARIABLES --------------------------------*/

//static uint8_t testing_arr[ELEMENTS(21)] = {1, 2, 3, 4, 5, 6, 7,
//		8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};

static volatile sint8_t ReceivedString[ELEMENTS(250)];
static volatile uint8_t counter = 0;

static uint8_t UART_status = UART_NOT_DONE;
uint8_t BCM_InitOnce = BCM_NOT_INITIALIZED;

//static uint8_t i = 0;

void Bcm_TxCallBack(void)
{
	UART_status = UART_NOT_DONE;
	BCM_InitOnce = BCM_NOT_INITIALIZED;

	for(counter = 0 ; counter < ELEMENTS(50) ; counter++)
	{
		ReceivedString[counter] = ' ';
	}
}

int main(void)
{

	UART_ConfigType UART_cfg = {
			UART_ASYNCHRONOUS_MODE,
			UART_RECEIVER_MODE,
			UART_EIGHT_BITS,
			UART_PARITY_DISABLED,
			UART_ONE_STOP_BIT,
			UART_INTERRUPT_DISABLED
	};

	strBcmConfig_t BCM_cfg = {
			BCM_SPI_ID,
			BCM_TRANSMIT
	};

	strBcmSendConfig_t BCM_startCfg = {
			BCM_SPI_ID,
			(uint8_t*)ReceivedString,
			ELEMENTS(250)
	};

	

	UART_init(&UART_cfg);

	BCM_TxSetCallBack(&Bcm_TxCallBack);

	sei();

	while(1)
	{
		if(UART_status == UART_DONE)
		{
			if(BCM_InitOnce == BCM_NOT_INITIALIZED)
			{
				BCM_Init(&BCM_cfg);

				BCM_Send(&BCM_startCfg);

				BCM_InitOnce = BCM_INITIALIZED;
			}

			BCM_TxDispatch();
		}
		else if(UART_status == UART_NOT_DONE)
		{
			UART_receiveString((sint8_t*)ReceivedString);

			UART_status = UART_DONE;
		}
	}
}


