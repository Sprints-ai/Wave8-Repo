/*
 * BCM.h
 *
 * Created: 3/2/2020 1:17:48 AM
 *  Author: Abdallah & Amin
 */


#ifndef BCM_RX_H_
#define BCM_RX_H_

/* inclusions */
#include "std_types.h"
#include "Errors.h"

/*UART_Channels*/
#define Data_Size 8
#define UART_CH		0x01
#define SPI_CH		0x02
#define I2C_CH		0x03

/*Buffer Status*/
#define BUFFER_LOCKED		0
#define BUFFER_UNLOCKED		1

/*BCM RX States*/
#define BCM_IDLE                        0
#define BCM_RECEIVING_BYTE              1
#define BCM_RECEIVING_BYTE_COMPLETE     2

/*primitive types*/

uint8_t gu8_BUFF[54];
#define BCM_PAYLOAD_ID 0xA2

/*
function declarations
*/
/*
	Function Name: BCM_Init
	Discribtion: This function is used to initialize  the BCM Module for Specific Communication protocol
	Param: This function takes input value of BCM channel
	return: This function returns error status E_OK , E_NOK
	*/
ERROR_STATUS BCM_Init(uint8_t u8_bcm_id);
/*
	Function Name: BCM_Receive
	Discribtion: This function is used to set the buffer size the BCM Module for Specific Communication protocol ( buffer size + overhead)
	Param: This function takes input value of BCM channel and buffer size
	return: This function returns error status E_OK , E_NOK
	*/
extern ERROR_STATUS BCM_Receive(uint16_t u16_Size, uint8_t u8_Channel);
/*
	Function Name: BCM_RxDispatch
	Discribtion: This function is used to choose the state of the recieveing process and calculate the check sum
	Param: This function takes void
	return: This function returns void
	*/
extern void BCM_RxDispatch(void);

extern void BCM_UART_Tx_Call_Back(void);
extern void BCM_UART_Rx_Call_Back(void);
extern void BCM_SPI_Rx_Call_Back(void);


#endif /* BCM_RX_H_ */
