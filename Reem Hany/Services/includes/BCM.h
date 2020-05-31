/*
 * BCM.h
 *
 * Created: 3/2/2020 7:16:43 PM
 *  Author: Reem
 */ 


#ifndef BCM_H_
#define BCM_H_
#include "std_types.h"
#include "UART.h"
#include "SPI__.h"

#define BCM_ERROR   -800
#define UART_BCM    1
#define SPI_BCM     2  

#define RX_IDLE                            0
#define RX_RECIEVING_BYTE                  1
#define RX_RECIEVING_COMPLETE_FRAME        2

#define READING                            0
#define SENDING                            1

#define RX_UNLOCK                          0
#define RX_RECIEVING                       1  
#define RX_READY                           2

#define ZERO                               0

/*TX buffer states*/
#define TX_BUFFER_UNLOCK  1
#define TX_BUFFER_READY_TO_SEND  2
#define TX_BUFFER_SEND_VALID 3
#define TX_BUFFER_SENDING 4

/**/
typedef struct strBCMCfg_t{
	uint8_t Protocol;
	uint8_t Direction;
	
}strBCMCfg_t;

typedef struct strRecievedInfo_t{
	uint16_t RxDataSize;
	uint16_t RxCounter;
	uint8_t  CheckSum;
	uint8_t  CheckSumRecieved;
}strRecievedInfo_t;

typedef struct strBufferInfo_t{
	uint8_t* RxBuffer;
	uint16_t RxBufferSize;
	uint16_t RxBufferIndex;
}strBufferInfo_t;

typedef struct strTxBuffer_t{
	uint8_t * ptrTxBuffer;
	uint16_t Size;
	uint8_t Lock;
}strTxBuffer_t;

/**
* Input: Pointer to a structure contains the information needed to initialize the BCM.
* Output:
* In/Out:
* Return: The error status of the function.
* Description: Initiates the BCM.
*
*/
extern ERROR_STATUS BCM_Init(strBCMCfg_t *BCMCfg);

/**
* Input: Pointer to a structure contains the information of TX Buffer the BCM.
* Output:
* In/Out:
* Return: The error status of the function.
* Description: This function act as the creator for the BCM Transmission 
*
*/
extern ERROR_STATUS BCM_Send(strTxBuffer_t * TxRequest);

/**
* Input: Pointer to the RX Buffer, The size of RX Buffer,the pointer to the BCM Callback function.
* Output:
* In/Out:
* Return: The error status of the function.
* Description: This function act as the creator for the BCM Reception
*
*/
extern ERROR_STATUS BCM_SetupRxBuffer(uint8_t* PtrRxData,uint16_t size, void (*Notification)(uint8_t));

/**
* Input: the buffer lock state.
* Output:
* In/Out:
* Return: The error status of the function.
* Description: This function used to unlock the Rx buffer
*
*/
extern ERROR_STATUS BCM_RxUnlock(uint8_t Rxlock);

/**
* Input: the buffer lock state.
* Output:
* In/Out:
* Return: The error status of the function.
* Description: This function used to change the state of the Rx buffer locking state
*
*/
extern ERROR_STATUS BCM_GetTxBuffer(strTxBuffer_t * TxRequestID,uint8_t * TxBufferState);

/**
* Input: the buffer lock state.
* Output:
* In/Out:
* Return: The error status of the function.
* Description: This function act as the manager of the Rx BCM
*
*/
extern void BCM_RxDispatcher(void);

/**
* Input: the buffer lock state.
* Output:
* In/Out:
* Return: The error status of the function.
* Description: This function act as the manager of the Tx BCM
*
*/
extern void BCM_TxDispatcher(void);




#endif /* BCM_H_ */