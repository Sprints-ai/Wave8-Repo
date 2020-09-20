/*
 * UART.c
 *
 *  Created on: Mar 5, 2020
 *      Author: Khaled
 */

#include "UART.h"

extern uint8_t gu8_UartTransmitNotification;
extern uint8_t gu8_UartReceiveData;

void UART_INIT (En_UartParity_t en_parity, En_UartStopBit_t en_stop_bit, En_UartDataFrameSize_t en_data_frame_size, En_UartBaudRate_t en_baud_rate,
                En_UartSpeed_t en_speed,En_UartMultiProcessorCommunication_t en_multi_processor_communication,En_UartInterrupt_t en_interrupt_mode,
                void(* ptr_RCBK)(uint8_t))
{

}


void UART_TRANSMIT_Char (uint8_t Data, uint8_t * not)
{
   *not = gu8_UartTransmitNotification;
}

void UART_TRANSMIT_String (uint8_t * Data)
{
;
}


uint8_t UART_RECEIVE (void)
{
return 0;
}

void UART_RECEIVE_String (uint8_t * Data)
{
   *Data = gu8_UartReceiveData;
}

