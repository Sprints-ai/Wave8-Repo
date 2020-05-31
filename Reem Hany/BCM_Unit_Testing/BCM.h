/*
 * BCM.h
 *
 * Created: 3/2/2020 7:16:43 PM
 *  Author: Reem
 */


#ifndef BCM_H_
#define BCM_H_

/*************************************************************/
/************************* INCLUDES *************************/
/***********************************************************/
#include "std_types.h"
#include "UART.h"
#include "SPI__.h"
#include "ERROR-STORE.h"

/*************************************************************/
/*********************** GLOBAL MACROS **********************/
/***********************************************************/

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


/*TX buffer states*/
#define TX_BUFFER_UNLOCK  1
#define TX_BUFFER_READY_TO_SEND  2
#define TX_BUFFER_SEND_VALID 3
#define TX_BUFFER_SENDING 4




/*************************************************************/
/********************** STRUCT TYPEDEF **********************/
/***********************************************************/
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




/*************************************************************/
/***************** APIS FUNCTION PROTOTYPE ******************/
/***********************************************************/
extern ERROR_STATUS BCM_Init(strBCMCfg_t *BCMCfg);
extern ERROR_STATUS BCM_Send(strTxBuffer_t * TxRequest);
extern ERROR_STATUS BCM_SetupRxBuffer(uint8_t* PtrRxData,uint16_t size, void (*Notification)(uint8_t));
extern ERROR_STATUS BCM_RxUnlock(uint8_t Rxlock);
extern ERROR_STATUS BCM_GetTxBuffer(strTxBuffer_t * TxRequestID,uint8_t * TxBufferState);
extern ERROR_STATUS BCM_GetRxBufferLockState(uint8_t * BufferState);

extern void BCM_RxDispatcher(void);
extern void BCM_TxDispatcher(void);




#endif /* BCM_H_ */
