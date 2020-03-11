/*
 * BCM.h
 *
 *  Created on: Mar 2, 2020
 *      Author: Youssef Harby 
 */

#ifndef BCM_H_
#define BCM_H_

/**Last Edition**/
/*********************************************
 *				Includes  					 *
********************************************/

#include "SPI.h"
#include "UART.h"


/********************************************
*				Defines  					 *
********************************************/

/** Potocol ID: clarify the channel used to send or recieve data by BCM **/
#define BCM_ID					0x5A

#define BCM_UART_ID				0xA0
#define BCM_SPI_ID				0xA1
#define BCM_I2C_ID				0xA2

/** Protocol_Mode: clarify the Mode of sending data is sending or recieving it **/
#define BCM_TRANSMIT			0x00
#define BCM_RECEIVE				0x01
#define BCM_TRANSMIT_RECEIVE	0x02


/** Declaring pointer to function passing uint8_t **/
typedef void (*PointerToSenderFunction)(const uint8_t);

/** Declaring pointer to function return uint8_t **/
typedef uint8_t (*PointerToReceiverFunction)(void);

/** Declaring pointer to function passing ptr to funtion for call back function used later **/
typedef void (*PointerToSetCallBackFunction)(void(*ptr)(void));

/** Declaring pointer to function **/
typedef void (*PointerToApplicationFunction)(void);

/** Error Handling type **/
typedef uint8_t EnmBCMError_t;


/************************************************************************/
/*			  Structures Declaration		                            */
/************************************************************************/

/** BCM Configuration Structure passed to BCM _Init function **/
typedef struct BCM_ConfigType{
	uint8_t BCM_ProtocolID;
	uint8_t BCM_DataDirection;
}strBcmConfig_t;

/** BCM Configuration Structure passed to BCM _Send function **/
typedef struct BCM_SendConfigType{
	uint8_t BCM_ProtocolID;
	uint8_t* BCM_ArrayStartAddress;
	uint16_t BCM_ArraySize;
}strBcmSendConfig_t;


/*********************************************
 *	  	   Function prototypes				 *
 ********************************************/

/**
 * Func			: BCM_Init
 * Input		: Pointer to a structure of type strBcmConfig_t 
 *				contains the BCM_Channel or protocol and the mode sending or receiving.
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (BCM protocol,mode of data[Sending /Receiving])
 */
extern EnmBCMError_t BCM_Init(const strBcmConfig_t* ConfigPtr);

/**
 * Func			: BCM_DeInit
 * Input		: BCM_ProtocolID
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Uninitialized the BCM 
 */
extern EnmBCMError_t BCM_DeInit(uint8_t BCM_ProtocolID);
/**
 * Func			: BCM_Send
 * Input		: Pointer to a structure of type strBcmSendConfig_t 
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: function BCM_Send shall invoked by the user to send the stream of data,
				 it represent event creator in addition to constructing the packet/data frame{Module ID, No of Bytes, Data, CheckSum}.
**/
extern EnmBCMError_t BCM_Send(strBcmSendConfig_t* ConfigPtr);
/**
 * Func			: BCM_Receive
 * Input		: Pointer to a structure of type strBcmSendConfig_t 
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: function BCM_Receive to receive the stream of data and set call back function of uart/spi to receive data through ISR.
**/
extern EnmBCMError_t BCM_Receive(strBcmSendConfig_t* ConfigPtr);
/**
 * Func			: BCM_SetupRxBuffer
 * Input		:  ProtocolID, (first element in the array)ArrayFirstElementAddress, ArraySize.
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: function BCM_SetupRxBuffer represent event creator in receiver used by the user to initiate  the receiving proceess
**/
extern EnmBCMError_t BCM_SetupRxBuffer(uint8_t ProtocolID, uint8_t* ArrayFirstElementAddress, uint16_t ArraySize);
/**
 * Func			: BCM_RxDispatch
 * Input		: No Input
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Implement BCM_RxDispatch check the flag of ISR and move between Receiving complete
					and Receiving Byte states in addition to calculate check sum . 
**/
extern EnmBCMError_t BCM_RxDispatch(void);
/**
 * Func			: BCM_TxDispatch
 * Input		: No Input
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Implement BCM_TxDispatch check the flag of ISR and move between Transmitting complete 
					and Transmitting Byte states and compare check sum with the sending data. 
**/
extern EnmBCMError_t BCM_TxDispatch(void);
/**
 * Func			: BCM_TxSetCallBack
 * Input		: No Input
 *				
 * Output	
 * Return 		:				
 *
 * Description	: function BCM_TxSetCallBack shall assign the Tx call back function to be performed in ISR.
**/
extern void BCM_TxSetCallBack(void (*a_ptr)(void));
/**
 * Func			: BCM_RxSetCallBack
 * Input		: No Input
 *				
 * Output	
 * Return 		:				
 *
 * Description	: function BCM_RxSetCallBack shall assign the Rx call back function to be performed in ISR.
**/
extern void BCM_RxSetCallBack(void (*a_ptr)(void));

#endif /* BCM_H_ */
