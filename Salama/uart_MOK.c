/*
 * uart.c
 *

 * Created: 10-Feb-20 2:21:06 PM
 *  Author: ahmed
 */
#include "uart.h"




volatile static ptr_Function UART_Callback_TxC_Function;
volatile static ptr_Function UART_Callback_RxC_Function;

/************************************************************************/
/*			Uart_init, takes a structure of inits                       */
/************************************************************************/
ERROR_STATUS uart_init(init_uart *uart){



	return E_OK;
}

/*send a byte to tx pin*/
void uart_tx_send(uint8_t data_send){


}

/*Rec byte from uart receive*/
uint8_t uart_rx(void){


}

/*void set_callback(void (*local_ptr)(void))
{
	global_ptr = (volatile void(*)(void))local_ptr;
}
*/

ISR(USART_RXC_vect){



}
