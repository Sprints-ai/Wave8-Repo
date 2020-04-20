/*
 * BCM.h
 *
 * Created: 3/2/2020 1:25:16 PM
 *  Author: ahmed
 */ 


#ifndef BCM_H_
#define BCM_H_

#include "USART.h"
#include "SPI.h"
#include "BCM_LCfg.h"

#define IDLE				(0xff)

#define START_SENDING		(1)
#define SENDING				(2)
#define SENDING_COMPLETE	(3)

#define START_RECEIVING		(4)
#define RECEIVING			(5)
#define RECEIVING_COMPLETE	(6)

#define UART				(0)
#define SPI					(1)
#define SENDER				(2)
#define RECEIVER			(3)

#define BCM_MODULE_ID		(200)
#define BCM_ID				'1'

/**
 * Description: initializes the BCM Module using linking configuration
 *
 * @return: function status
 */
ERROR_STATUS BCM_Init(void);

/**
 * Description: Deinitializes the BCM Module
 *
 * @return: function status
 */
ERROR_STATUS BCM_DeInit(void);

/**
 * Description: starts the receiver's dispatcher
 *
 * @return: function status
 */
ERROR_STATUS BCM_RxDispatch(void);

/**
 * Description: starts the sender's dispatcher
 *
 * @return: function status
 */
ERROR_STATUS BCM_TxDispatch(void);

/**
 * Description: sets the buffer and the number of bytes to be sent for the TxDispatcher and initiates it's state machine
 *
 * @param: pu8_Data: input parameter: the buffer that is required to be sent
 * @param: u16_BytesNumber: the size of the buffer (Number of bytes in the buffer)
 *
 * @return: function status
 */
ERROR_STATUS BCM_Send (uint8_t* pu8_Data , uint16_t u16_BytesNumber);

/**
 * Description: sets the buffer to receive the data in for the RxDispatcher and initiates it's state machine
 *
 * @param: pu8_Data: in out parameter: the buffer to receive the data in
 *
 * @return: function status
 */
ERROR_STATUS BCM_Receive(uint8_t* pu8_Data);




#endif /* BCM_H_ */