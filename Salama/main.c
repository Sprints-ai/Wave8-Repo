/*
 * Basic_Comm_Module.c
 *
 * Created: 2020-03-01 9:49:13 PM
 * Author : AHMED_SALAMA
 */ 

/************************************************************************/
/*							INCLUDES                                    */
/************************************************************************/
#include "bcm.h"
#include "uart.h"

/************************************************************************/
/*							DEFINES                                     */
/************************************************************************/
#define MAX_BUFFER_SIZE (30)


/*please change it to BCM_SEND if you want to use sending side*/
#define BCM_SEND

#ifdef BCM_SEND
/**First half of the project
	*Description : sending from pc to uart then from spi->spi
	**receiving data till '@' is received then we send that buffer to the other spi side
	*please define it to use it*/
	
/************************************************************************/
/*						DEFINES                                         */
/************************************************************************/
#define BCM_TERMINATION		('@')
	
/*BCM Buffer creation*/
uint8_t arr_BCM_Buffer[MAX_BUFFER_SIZE];

int main(void)
{
	uint8_t uart_counter = ZERO;
	
	/*init uart first and you can modify structure at uart_config.c file*/
	uart_init(&st_uart_init);
	
	/*saving everything received by uart to the buffer
	Terminates when receiving @*/
	while(1)
	{
		/*save data byte by byte in buffer*/
		arr_BCM_Buffer[uart_counter] = uart_rx();
		
		/*terminate when @ is received*/
		if(arr_BCM_Buffer[uart_counter] == BCM_TERMINATION)
		{
				break;
		}
		
		/*increment counter by one*/
		uart_counter++;
	}

	/*init the BCM module*/
	BCM_Init(&BCM_Cfg);

	/*enable global interrupt*/
	sei();
	
	/*send buffer by BCM*/
	BCM_Send(arr_BCM_Buffer , uart_counter);

    while (1) 
    {
		/*start bcm_dispatch*/
		BCM_TxDispatcher();
		
    }
}

/*Other side of project
*Description : here is the receiving spi side then sending data back to pc
**the data is sent at BCM after receiving it so please check it
***please make sure that spi is configure as a slave

*/

#else 

/*create receiving buffer*/
uint8_t arr_BCM_Buffer[MAX_BUFFER_SIZE];

/*receive function define*/
void BCM_Receive_Notification(uint16_t uart_size){
	
	/*first init uart*/
	uart_init(&st_uart_init);
	
	uint16_t u16_loop = ZERO;
	
	/*loop to send all bytes*/
	for(u16_loop = ZERO; u16_loop <= uart_size ; u16_loop++)
	{
		/*send data back to pc*/
		uart_tx_send(arr_BCM_Buffer[u16_loop]);
	}
}



int main(void)
{
	BCM_Cfg.Recieve_Cbk = BCM_Receive_Notification;
	
	/*init BCM*/
	BCM_Init(&BCM_Cfg);

	sei();
	/*setup you buffer settings*/
	BCM_SetupReceive(arr_BCM_Buffer,MAX_BUFFER_SIZE);

	while (1)
	{
		BCM_RxDispatcher();
	}
}
#endif
