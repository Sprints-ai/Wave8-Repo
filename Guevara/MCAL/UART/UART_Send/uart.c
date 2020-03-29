﻿/*
 * uart.c
 *
 * Created: 10/02/2020 08:02:23 م
 *  Author: mo
 */
#include "uartconfig.h"
#include "uart.h"
#include "../../../Infrastructure/registers.h"
/*volatile uint8_t u8_Notification_TX=0;
volatile uint8_t gU8_Data_Recieved=0;
volatile uint8_t gU8_Data_transmited=0;
*/
extern volatile uint8_t u8_DATA;
uint8_t BufferRequested[Buffer_Size];
volatile uint8_t u8_index=0;
volatile uint8_t buf_is_full=0;
void Uart_Init(En_BAUD_Rate Baud_rate,En_Stop_config Stop_bits_num,
  EN_Parity parity_Bit,EN_Data_Size data_num_bits,EN_UartMode uart_mode)
{uint8_t Buffer=0;
switch (Baud_rate) {
  case Baud9600:
  UBRRL=Baud9600;
  break;
  case Baud14400:
  UBRRL=Baud14400;
  break;
  case Baud19200:
  UBRRL=Baud19200;
  break;
  case Baud38400:
  UBRRL=Baud38400;
  break;
}
switch (Stop_bits_num) {
case OneStopBit:
{ SET_BIT(Buffer,URSEL);
  CLEAR_BIT(Buffer,USBS);
  break;
}
case TwoStopBits:
{
  SET_BIT(Buffer,URSEL);
  SET_BIT(Buffer,USBS);
  break;
}
}
switch (data_num_bits)
{
case FiveBits:
{
SET_BIT(Buffer,URSEL);
CLEAR_BIT(Buffer,UCSZ0);
CLEAR_BIT(Buffer,UCSZ1);
CLEAR_BIT(UCSRB,UCSZ2);
break;
}
case SexBits:
{
  SET_BIT(Buffer,URSEL);
  SET_BIT(Buffer,UCSZ0);
  CLEAR_BIT(Buffer,UCSZ1);
  CLEAR_BIT(UCSRB,UCSZ2);
  break;
}
case SevenBits:
{
  SET_BIT(Buffer,URSEL);
  CLEAR_BIT(Buffer,UCSZ0);
  SET_BIT(Buffer,UCSZ1);
  CLEAR_BIT(UCSRB,UCSZ2);
  break;
}
case EightBits:
{   SET_BIT(Buffer,URSEL);
    SET_BIT(Buffer,UCSZ0);
    SET_BIT(Buffer,UCSZ1);
    CLEAR_BIT(UCSRB,UCSZ2);
break;
}

case NineBits:
{   SET_BIT(Buffer,URSEL);
	SET_BIT(Buffer,UCSZ0);
	SET_BIT(Buffer,UCSZ1);
	SET_BIT(UCSRB,UCSZ2);
	break;
}

}

switch (uart_mode) {
  case ASynchronous:
  {
  SET_BIT(Buffer,URSEL);
  CLEAR_BIT(Buffer,UMSEL);
  break;
  }
case Synchronous:
{
  SET_BIT(Buffer,URSEL);
  SET_BIT(Buffer,UMSEL);
  break;
}
}
switch (parity_Bit) {
  case NoParity:
{
SET_BIT(Buffer,URSEL);
CLEAR_BIT(Buffer,UPM0);
CLEAR_BIT(Buffer,UPM1);
  break;
}
case EvenParity:
{
SET_BIT(Buffer,URSEL);
CLEAR_BIT(Buffer,UPM0);
SET_BIT(Buffer,UPM1);
break;
}
case OddParity:
{
SET_BIT(Buffer,URSEL);
SET_BIT(Buffer,UPM1);
SET_BIT(Buffer,UPM0);
break;
}


}

UCSRC=Buffer;
SET_BIT(UCSRB,TXEN);/*TXEN*/
SET_BIT(UCSRB,RXEN);/*RXEN*/
}
void UartTransmitPooling(uint8_t Data)
{
while( !( UCSRA & (1<<UDRE)));
UDR=Data;
}
uint8_t UartRecievePooling(void)
{
	uint8_t data=0;
while (!( UCSRA & (1 << RXC)));/* Wait until new data receive*/
data=UDR;
return data;									/* Get and return received data */
}


void Enable_communication_interrupt(void)
{
G_interrupt_Enable();
SET_BIT(UCSRB,RXCIE);
SET_BIT(UCSRB,TXCIE);
SET_BIT(SPCR,SPIE);
}
void UartRecieveInterrupt(void)
{
/*The mechanism to access array*/
// BufferRequested[u16_index]=gU8_Data_Recieved;
//  if (u16_index < Buffer_Size){
//  u16_index++;
//  buf_is_full=0;
//  }
//  else{
//  buf_is_full=1;
//  u16_index=0;
//      }
/*if(u8_index<Buffer_Size)
{
  */u8_DATA=UDR;/*
  BufferRequested[u8_index]=u8_DATA;
  u8_index++;
}
  else{
    u8_index=0;
  }*/
}
void UartTransmitInterrupt(void)
{
/*When void Uart_tryansmitfirstbyte(uint8_t data) sends first byte before while(1) we start here sendine the next bytes
gU8_Data_transmited is shared with void UartTransmitdataInt(uint8_t data_to_transmit)
that changes its data
*/
UDR=u8_DATA;
//G_interrupt_Enable();
//u8_DATA ^=0xFF;
}
void UartTransmitdataInt(uint8_t data_to_transmit)
{
	  u8_DATA=data_to_transmit;
}

void Uart_tryansmitfirstbyte(uint8_t data)
{
UDR=data;
}
void Uart_De_Init(void)
{
  CLEAR_BIT(UCSRB,TXEN);/*TXEN*/
  CLEAR_BIT(UCSRB,RXEN);/*RXEN*/

}
