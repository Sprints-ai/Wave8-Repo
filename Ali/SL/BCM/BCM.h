/*
 * BCM.h
 *
 * Created: 3/4/2020 7:11:57 PM
 *  Author: Az
 */ 


#ifndef BCM_H_
#define BCM_H_
/*- INCLUDES -------------------------------------------------------------------------------------------------------*/
#include "../../std_types.h"

/*- DEFINES --------------------------------------------------------------------------------------------------------*/
/* Protocol */
#define SPI    1
#define I2C    2

/* Data Direction */
#define TRANSMIT  1
#define RECIEVE   2

/* Buffer Size */
#define  MAX_BUFFER_SIZE 65535

/* BCM_ID */
#define BCM_ID    0xA5

/* Buffer Status */
#define BUFFER_LOCKED   0
#define BUFFER_UNLOCKED 1

/* BCM TX/RX Dispatch States */
#define  IDLE                 0
#define  SENDING_BYTES        1
#define  SENDING_COMPLETE     2
#define  RECIEVING_BYTES      3
#define  RECIEVING_COMPLETE   4

/* BCM Notifications */
#define  BCM_BYTE_TRANSMIT_SUCCESS 0
#define  BCM_BYTE_TRANSMIT_FAIL    1
#define  BCM_BYTE_RECIEVE_SUCCESS  2
#define  BCM_BYTE_RECIEVE_FAIL     3
#define  BCM_TRANSMIT_COMPLETE     4
#define  BCM_TRANSMIT_FAIL         5
#define  BCM_RECIEVE_COMPLETE      6
#define  BCM_RECIEVE_FAIL          7

/*- TYPEDEFS -------------------------------------------------------------------------------------------------------*/

/* BCM Configuration Struct*/
typedef struct str_BCM_Cfg
{
   uint8_t dataDirection;
   uint8_t protocol;     
}str_BCM_Cfg_t;

/* BCM Error Enum */
typedef enum EnmBCMError
{
   BCM_ERROR_UNDEFINED = 0,
   BCM_INVALID_INPUT_PARAMS = 1,
   BCM_PACKET_SEND_SUCCESS = 2,
   BCM_INVALID_BUFFER_SIZE = 3,
   BCM_READ_TX_BUFFER_STATUS_SUCCESS = 4,
   BCM_READ_TX_BUFFER_STATUS_FAIL = 5,
   BCM_READ_RX_BUFFER_STATUS_SUCCESS = 6,
   BCM_READ_RX_BUFFER_STATUS_FAIL = 7,
   BCM_SETUP_RX_BUFFER_SUCCESS = 8,
   BCM_SETUP_TX_BUFFER_SUCCESS = 10,
   BCM_READ_STATE_SUCCESS = 11  
}EnmBCMError_t;

/* TX/Rx Buffer configuration */ 
typedef struct StrBuffer
{
   uint8_t * bufferAddress;
   uint16_t bufferSize;  
   uint8_t check_sum;
   uint8_t buffer_state;
}StrBuffer_t;

/*- FUNCTIONS PROTOTYPES -------------------------------------------------------------------------------------------*/

/*
*  Description : Get Rx State machine's state.
*
*  @param uint8_t * state  (output param)
*
*  @return EnmBCMError_t
*/
extern EnmBCMError_t  BCM_GetRxState(uint8_t * state);

/*
*  Description : Get Tx State machine's state.
*
*  @param uint8_t * state  (output param)
*
*  @return EnmBCMError_t
*/
extern EnmBCMError_t  BCM_GetTxState(uint8_t * state);

/*
*  Description : Responsible for initialization process of BCM. 
*
*  @param str_BCM_Cfg_t * strBCM_Init
*
*  @return EnmBCMError_t
*/
extern EnmBCMError_t BCM_Init(str_BCM_Cfg_t * strBCM_Init);

/*
*  Description : Starts or triggers Tx state machines , Locks Tx buffer in order to start the process , Sends the first byte which is (BCM_ID,Data length)
*
*  @param void
*
*  @return void
*/
extern void BCM_Send(void);

/*
*  Description : Starts or triggers Rx state machines , Locks Rx buffer in order to start the process , Receives the first byte which is (BCM_ID,Data length)
*
*  @param void
*
*  @return void
*/
extern void BCM_Read(void);

/*
*  Description : Navigates between the states of BCM packets Transmission state machine.
*                (IDLE , SENDING_BYTES)
*
*  @param void
*  @return void
*/
extern void BCM_TxDispatcher(void);

/*
*  Description : Receives Data packets
*
*  @param str_BCM_Cfg_t * strBCM_Init
*
*  @return void
*/
extern void BCM_RxDispatcher(void);

/*
*  Description : Setups External Buffer -provided by the application- for receiving data
*
*  @param uint8_t * rxBuffer
*  @param uint16_t rxBufferSize
*
*  @return EnmBCMError_t
*/
extern EnmBCMError_t BCM_SetupRxBuffer(uint8_t * rxBuffer, uint16_t rxBufferSize);

/*
*  Description : Setups External Buffer -provided by the application- for Transmitting data
*
*  @param uint8_t * txBuffer
*  @param uint16_t txBufferSize
*
*  @return EnmBCMError_t
*/
extern EnmBCMError_t BCM_SetupTxBuffer(uint8_t * txBuffer, uint16_t txBufferSize);

/*
*  Description : Gets BCM TX buffer status - whether locked or unlocked -
*
*  @param uint8_t * getStatus
*
*  @return EnmBCMError_t
*/
extern EnmBCMError_t BCM_GetTxBufferStatus(uint8_t * getStatus);

/*
*  Description : Gets BCM Rx buffer status - whether locked or unlocked -
*
*  @param uint8_t * getStatus
*
*  @return EnmBCMError_t
*/
extern EnmBCMError_t BCM_GetRxBufferStatus(uint8_t * getStatus);

#endif /* BCM_H_ */