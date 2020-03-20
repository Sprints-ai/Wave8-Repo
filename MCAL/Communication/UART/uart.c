/*
 * uart.c
 *
 * Created: 3/1/2020 8:19:11 PM
 *  Author: mahmo
 */ 

#include "uart.h"

#define BAUD        9600
#define FCPU	  16000000UL
#define UBBR_VALUE (((FCPU)/(BAUD*16UL))-1)


/* UCSRA */
#define RXC     0x80
#define TXC     0x40
#define UDRE    0x20
#define FE      0x10
#define DOR     0x08
#define PE      0x04
#define U2X     0x02
#define MPCM    0x01

/* UCSRB */
#define RXCIE   0x80
#define TXCIE   0x40
#define UDRIE   0x20
#define RXEN    0x10
#define TXEN    0x08
#define UCSZ2   0x04
#define RXB8    0x02
#define TXB8    0x01

/* UCSRC */
#define URSEL   0x80
#define UMSEL   0x40
#define UPM1    0x20
#define UPM0    0x10
#define USBS    0x08
#define UCSZ1   0x04
#define UCSZ0   0x02
#define UCPOL   0x01

static volatile uint8_t u8_UDREmptyFlag = TRUE;

volatile static UartTX_CBF TX_CBF;
volatile static UartRX_CBF RX_CBF;


MY_ISR(USART_UDRE_vect)
{
	UDR  = TX_CBF();
	CLEAR_BIT(UCSRB,DATA_REGISTER_EMPTY_INT);
	u8_UDREmptyFlag = TRUE;
}
MY_ISR(USART_RXC_vect)
{
	RX_CBF(UDR);
}	

void Uart_Init(gstr_uart_cfg_t* uart_cfg)
{
	/*
	*	1-set baud rate
	*	2-set data size to 8 bit
	*	3-enabel RX/TX inturrpte and enable TX/RX
	*	3-set number of stop bits to 1 , no parity , asyn mode,normal speed , ucpol = 0 , 
	*/
	TX_CBF = uart_cfg->uartTXCBF;
	RX_CBF = uart_cfg->uartRXCBF;
	/*setting baud rate*/
	UBRRL = UBBR_VALUE;
	
	/*setting 8 bits data with no stop bit,asyn mode,parity disabled,cpol = zero*/
	UCSRC = (UCSRC_SEL | UART_8BIT);
	
	/*enable both receive and transmit , enable transmit interrupt and receive interrupt*/
	UCSRB = (RECIEVE_COMPLETE_INT | RECIEVE_EN | TRANSMIT_EN);
}


/*
*  Description : Write a character to TXB
*
*  @param uint8_t  ch
*  @return void
*/
void UartTX_Enable()
{
	/*	
	*	1-set udrEmptyFlag to false	
	*	2-enable UDRE interrupter
	*/
	u8_UDREmptyFlag = FALSE;
	UCSRB |= DATA_REGISTER_EMPTY_INT;
	
}

uint8_t UDR_ReadyStatus(void)
{
	return u8_UDREmptyFlag;
}
