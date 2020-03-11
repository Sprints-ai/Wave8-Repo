/*BCM_Rx
 * main.c
 *
 *  Created on: Mar 2, 2020
 *      Author: Mohamed Ramadan
 */


/*********************************************
 *				Includes  					 *
 ********************************************/
#include "BCM.h"


/*********************************************
 *				Defines  					 *
 ********************************************/
#define OVERHEAD 					4
#define ELEMENTS(NO_OF_Data)		(NO_OF_Data + OVERHEAD)
#define NO_OF_Data					250

#define Zero						0
#define ONE							1 
#define Two							2

#define BCM_DONE		1
#define BCM_NOT_DONE	0
#define UART_DONE		1
#define UART_NOT_DONE	0

#define BCM_INITIALIZED			1
#define BCM_NOT_INITIALIZED		0

#define UART_NOT_INITIALIZED		0
#define UART_INITIALIZED			1



uint8_t uart_flag = ONE;

uint8_t bcm_flag = BCM_NOT_DONE;


/*********************************************
 *				cALL bACK fUNCTIONS  		 *
 ********************************************/
void Uart_SendingApp(void)
{
	uart_flag = ONE;
}

void Bcm_RxCallBack(void)
{
	bcm_flag = BCM_DONE;
}


int main(void)
{
	/****/
	uint8_t UART_InitOnce = UART_NOT_INITIALIZED;
	
	/**Transmitted Buffer Initializing**/
	sint8_t SendingString[ELEMENTS(NO_OF_Data)];
	
	/** uart status if uart sending the data completely or not yet**/
	uint8_t uart_status = UART_NOT_DONE;
	
	/**BCM not initialized**/
	uint8_t BCM_initOnce = BCM_NOT_INITIALIZED;
	
	/**Reinitialize the counter**/
	uint8_t counter = Zero;

	UART_ConfigType UART_cfg = {
			UART_ASYNCHRONOUS_MODE,
			UART_SENDER_MODE,
			UART_EIGHT_BITS,
			UART_PARITY_DISABLED,
			UART_ONE_STOP_BIT,
			UART_INTERRUPT_ENABLED
	};

	strBcmConfig_t BCM_cfg = {
			BCM_SPI_ID,
			BCM_RECEIVE
	};

	uint8_t uart_counter = Zero;

	/**Receiver Set call back **/
	BCM_RxSetCallBack(&Bcm_RxCallBack);

	
	/**Enable Global Interrupt**/
	sei();

	/**Super loop**/
	while(1)
	{
		if(bcm_flag == BCM_DONE && uart_flag == ONE && uart_status == UART_NOT_DONE)
		{
			
			if(UART_InitOnce == Zero)
			{
				UART_TXC_setCallBack(&Uart_SendingApp);
				UART_init(&UART_cfg);
				UART_InitOnce = UART_INITIALIZED;
			}

			if(uart_counter != (ELEMENTS(NO_OF_Data) - ONE) && uart_counter > Two)
			{
				UART_transmit(SendingString[uart_counter]);
				uart_flag = Zero;
			}

			uart_counter++;
			if(uart_counter == ELEMENTS(NO_OF_Data))
			{
				UART_transmit('\r');

				for(counter = Zero ; counter < ELEMENTS(50) ; counter++)
				{
					SendingString[counter] = ' ';
				}

				bcm_flag = BCM_NOT_DONE;
				BCM_initOnce = BCM_NOT_INITIALIZED;
			}
		}

		if(bcm_flag == BCM_NOT_DONE)
		{
			if(BCM_initOnce == BCM_NOT_INITIALIZED)
			{
				BCM_Init(&BCM_cfg);
				BCM_SetupRxBuffer(BCM_SPI_ID, (uint8_t*)SendingString, ELEMENTS(NO_OF_Data));

				BCM_initOnce = BCM_INITIALIZED;
			}

			BCM_RxDispatch();
		}
	}
}



