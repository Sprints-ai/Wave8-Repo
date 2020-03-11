/*
 * BCMRx.c
 *
 *  Created on: Mar 2, 2020
 *      Author: Mohamed Ramadan
 */


/**Last Edition**/
/*********************************************
 *				Includes  					 *
********************************************/
#include "BCM.h"
#include "BCM_cfg.h"



/********************************************
*				Defines  					 *
********************************************/
#define UNDETERMINED		0x00


/** GLOBAL STATIC VARIABLES **/
/** State machine of the BCM **/
static volatile uint8_t gu8_BCM_SENDING_SM = BCM_SENDER_IDLE;
static volatile uint8_t gu8_BCM_Receiving_SM = BCM_RECEIVER_IDLE;

static volatile uint8_t gu8_BCM_BufferState = BCM_BUFFER_UNLOCKED;

/************************************************************************/
/*			  Structures Definition		                                */
/************************************************************************/
static strBcmSendConfig_t TxCfg;
static strBcmSendConfig_t RxCfg;

/************************************************************************/
/*			  global variable Declaration		                        */
/************************************************************************/
static volatile uint8_t gu8_TxDispatchCounter = 255;
static volatile uint8_t gu8_RxDispatchCounter = 255;

/** CheckSum for the Transmitter **/
static uint8_t gu8_TxCheckSum = 0;


// locals to globals

static uint8_t gu8_RxCheckSum = 0;
static uint8_t gu8_TxCounter = 0;
static uint8_t gu8_RxCounter = 0;

/** BCM Rx and Tx CallBack Function **/
static void (*BCM_RxCallBackPtr)(void) = NULL;
static void (*BCM_TxCallBackPtr)(void) = NULL;


/** Call back for Receiver Application **/ 
void RxApp(void)
{
	/**move the state to Receiving byte state**/
	gu8_BCM_Receiving_SM = BCM_RECEIVING_BYTE;
	/**calling the receive function and passing Receiver Buffer**/
	BCM_Receive(&RxCfg);
	/**move the state to complete receiving state**/
	gu8_BCM_Receiving_SM = BCM_RECEIVING_COMPLETE;
	/**Increment the index of receiving Buffer**/
	gu8_RxDispatchCounter++;
}

/** Call back for Transmitter Application **/
void TxApp(void)
{
	/**move the state to the Sending Complete state**/
	gu8_BCM_SENDING_SM = BCM_SENDING_COMPLETE;
	
	/**Increment the index counter of the transmitting Buffer**/
	gu8_TxDispatchCounter++;
}


/********************************************
 *			  Function Implementation        *
 *********************************************/
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
EnmBCMError_t BCM_Init(const strBcmConfig_t* ConfigPtr)
{
	/**  Error number of the function **/
	static uint8_t au8_Ret = E_OK;
	
	/** UART configuration structure**/
	UART_ConfigType UART_cfg = {
			UART_ASYNCHRONOUS_MODE,
			UNDETERMINED,
			UART_EIGHT_BITS,
			UART_PARITY_DISABLED,
			UART_ONE_STOP_BIT,
			UART_INTERRUPT_ENABLED
	};

	/** SPI configuration structure**/
	SPI_ConfigType SPI_cfg = {
			UNDETERMINED,
			SPI_INTERRUPT_ENABLED,
			SPI_F_OSC_4
	};

	/** switch case for setting mode of communication receiving or transmiting**/
	switch(ConfigPtr->BCM_DataDirection)
	{
		/**BCM channel Transmitting mode**/
	case BCM_TRANSMIT:
		UART_cfg.communicationMode = UART_SENDER_MODE;
		SPI_cfg.MasterSlaveSelect = SPI_MASTER;
		break;
		/**BCM channel Receiving mode**/
	case BCM_RECEIVE:
		UART_cfg.communicationMode = UART_RECEIVER_MODE;
		SPI_cfg.MasterSlaveSelect = SPI_SLAVE;
		break;
		/**BCM channel Trnasmitting Receiving mode**/
	case BCM_TRANSMIT_RECEIVE:
		UART_cfg.communicationMode = UART_SENDER_RECEIVER_MODE;
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	/** switching between uart/spi initialization according to protocol ID**/
	switch(ConfigPtr->BCM_ProtocolID)
	{
	case BCM_UART_ID:
		UART_init(&UART_cfg);
		break;
	case BCM_SPI_ID:
		SPI_init(&SPI_cfg);
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}
	
	/** return error number of the function**/
	return au8_Ret;
}
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
EnmBCMError_t BCM_DeInit(uint8_t BCM_ProtocolID)
{	
	/**  Error number of the function **/
	uint8_t au8_Ret = E_OK;

	/** switch case for deinitialization the module and set call back function to NULL**/
	switch(BCM_ProtocolID)
	{
		/**DeInitialize the UART channel**/
	case BCM_UART_ID:
		UART_deInit();
		UART_RXC_setCallBack(NULL);
		UART_TXC_setCallBack(NULL);
		break;
		/**DeInitialize the SPI channel**/
	case BCM_SPI_ID:
		SPI_deInit();
		SPI_setCallBack(NULL);
		break;
		/**In Case not of them used**/
	default:
		au8_Ret = E_NOK;
		break;
	}
	
	/** return error number of the function**/
	return au8_Ret;
}

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
EnmBCMError_t BCM_RxDispatch(void)
{
	/**  Error number of the function **/
	uint8_t au8_Ret = E_OK;
	
	/**check the state of the BCM Receiver and the index is still in the range of the array receiving then modify checksum variable**/
	if(gu8_BCM_Receiving_SM == BCM_RECEIVING_COMPLETE && gu8_RxDispatchCounter < (RxCfg.BCM_ArraySize - 1) && gu8_RxDispatchCounter >= 3)
	{
		gu8_RxCheckSum += RxCfg.BCM_ArrayStartAddress[gu8_RxDispatchCounter];

		gu8_BCM_Receiving_SM = BCM_RECEIVING_BYTE;
	}
	
	/**if we reach the end of the receiver array check the checksum variable and call the call back function of the uart to receive the array on the PC **/
	if(gu8_RxDispatchCounter == RxCfg.BCM_ArraySize - 1)
	{
		/**check if the checksum variable is updated or not**/
		if(gu8_RxCheckSum != RxCfg.BCM_ArrayStartAddress[gu8_RxDispatchCounter])
			au8_Ret = E_NOK;
		gu8_BCM_Receiving_SM = BCM_RECEIVER_IDLE;
		gu8_RxCounter = 0;
		gu8_RxDispatchCounter = 255;
		gu8_RxCheckSum = 0;
	
		/**checking the BCM call back ptr to function to satrt receive**/
		if(BCM_RxCallBackPtr != NULL)
		{
			BCM_RxCallBackPtr();
		}
	}

	/** return error number of the function**/
	return au8_Ret;
}

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
EnmBCMError_t BCM_TxDispatch(void)
{	
	/**  Error number of the function **/
	static uint8_t au8_Ret = E_OK;
	
	/**check if the sending of the first byte is done**/
	if(gu8_BCM_SENDING_SM == BCM_SENDING_COMPLETE)
	{
		/** still the data is not completed transmitted yet**/
		if(gu8_TxDispatchCounter < TxCfg.BCM_ArraySize - 4)
		{
			/** Accumulate the checksum variable**/
			gu8_TxCheckSum += TxCfg.BCM_ArrayStartAddress[gu8_TxDispatchCounter];
		}
		
		/**move the state to Sending Byte state **/
		gu8_BCM_SENDING_SM = BCM_SENDING_BYTE;

		/**sending the next byte of the Transmitter Buffer **/
		BCM_Send(&TxCfg);
	}

	/**Check if the Transmitter Buffer is completely transmitted or not**/
	if(gu8_TxDispatchCounter == TxCfg.BCM_ArraySize - 1)
	{
		/** Buffer is transmitted completeley and the state will be moved to IDLE**/
		gu8_BCM_SENDING_SM = BCM_SENDER_IDLE;
		/**All variables will Deinitialized**/
		gu8_TxCounter = 0;
		gu8_TxDispatchCounter = 255;
		gu8_TxCheckSum = 0;
	
		/** Check the Transmitter callingback function of the BCM**/
		if(BCM_TxCallBackPtr != NULL)
		{
			BCM_TxCallBackPtr();
		}
	}
	
	/** return error number of the function**/
	return au8_Ret;
}
/**
 * Func			: BCM_Send
 * Input		:  Pointer to a structure of type strBcmConfig_t 
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: function BCM_Send shall invoked by the user to send the stream of data, it represent event creator.
**/
EnmBCMError_t BCM_Send(strBcmSendConfig_t* ConfigPtr)
{
	/**  Error number of the function **/
	static uint8_t au8_Ret = E_OK;
	
	/**  Defining a static local ppointer to function by NULL **/
	static PointerToSenderFunction apf_SenderFunction = NULL;
	
	/** At the first index of the transmitted buffer**/
	if(gu8_TxCounter == 0)
	{
		/**switch between bcm channel**/
		switch(ConfigPtr->BCM_ProtocolID)
		{
		case BCM_UART_ID:
			UART_TXC_setCallBack(&TxApp);
			/**assign uart transmit function to the local PointerToSenderFunction **/
			apf_SenderFunction = UART_transmit;
			break;
		case BCM_SPI_ID:
			/**Setcallback function of the transmitter which move the state and increment the index of the transmitting buffer **/
			SPI_setCallBack(&TxApp);
			/**assign SPI sendByte function to the local PointerToSenderFunction **/
			apf_SenderFunction = SPI_sendByte;
			break;
		default:
			/**in another case it ill return an error**/
			au8_Ret = E_NOK;
			break;
		}
	
		/**Constructing the data acket by adding [handler ID, no of bytes, Data, check sum]**/
		ConfigPtr->BCM_ArrayStartAddress[ConfigPtr->BCM_ArraySize - 4] = BCM_ID;
		
		/**Setting the address (higher nibble) of the transmitting Buffer**/
		ConfigPtr->BCM_ArrayStartAddress[ConfigPtr->BCM_ArraySize - 3] = (uint8_t)((ConfigPtr->BCM_ArraySize-4) >> 8);
		/**adjust the lower niobble **/
		ConfigPtr->BCM_ArrayStartAddress[ConfigPtr->BCM_ArraySize - 2] =
				(uint8_t)((ConfigPtr->BCM_ArraySize-4) & 0x00FF);
	}

	/**constructing the checksum of the buffer **/
	ConfigPtr->BCM_ArrayStartAddress[ConfigPtr->BCM_ArraySize - 1] = gu8_TxCheckSum;

	/**check if the index of the transmitted buffer is still in the range **/
	if(gu8_TxCounter < ConfigPtr->BCM_ArraySize)
	{
		/**index less than 2 --- 0,1,2**/
		if(gu8_TxCounter <= 2)
			{
				/**Sending the ID and no of bytes in the first**/
				apf_SenderFunction(ConfigPtr->BCM_ArrayStartAddress[ConfigPtr->BCM_ArraySize - 4 + gu8_TxCounter]);
			}
				/** else the index was at the last send the checksum**/	
		else if(gu8_TxCounter == ConfigPtr->BCM_ArraySize - 1)
			{apf_SenderFunction(ConfigPtr->BCM_ArrayStartAddress[gu8_TxCounter]);}
				/**else send the data start from index zero**/
		else
			{apf_SenderFunction(ConfigPtr->BCM_ArrayStartAddress[gu8_TxCounter - 3]);}
		gu8_TxCounter++;
	}

	/**assigning the passing structure after reconstructing the packet to the Tx configuration structure to be sending in the next byte**/
	TxCfg = *ConfigPtr;
	
	/** return error number of the function**/
	return au8_Ret;
}

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
 * Description	: function BCM_SetupRxBuffer represent event creator in receiver used by the user to initiate  the receiving process
**/
EnmBCMError_t BCM_SetupRxBuffer(uint8_t ProtocolID, uint8_t* ArrayFirstElementAddress, uint16_t ArraySize)
{
	/**  Error number of the function **/
	static uint8_t au8_Ret = E_OK;

	/**Setting the parameters of the RX Buffer **/
	RxCfg.BCM_ArraySize = ArraySize;
	RxCfg.BCM_ArrayStartAddress = ArrayFirstElementAddress;
	RxCfg.BCM_ProtocolID = ProtocolID;
	
	/**switch between Protocols**/
	switch(ProtocolID)
	{
	case BCM_UART_ID:
		/**Set callback of the RX Buffer**/
		UART_RXC_setCallBack(&RxApp);
		break;
	case BCM_SPI_ID:
		/**Set callback of the RX Buffer**/
		SPI_setCallBack(&RxApp);
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	/** return error number of the function**/
	return au8_Ret;
}

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
EnmBCMError_t BCM_Receive(strBcmSendConfig_t* ConfigPtr)
{
	/**  Error number of the function **/
	static uint8_t au8_Ret = E_OK;
	
	/**  Defining a static local ppointer to function by NULL **/
	PointerToReceiverFunction apf_ReceiverFunction = NULL;

	/**switch between Protocols**/
	switch(ConfigPtr->BCM_ProtocolID)
	{
	case BCM_UART_ID:
		/**Set callback of the RX Buffer**/
		UART_RXC_setCallBack(&RxApp);
		/**assign UART_receive function to the local PointerToSenderFunction **/
		apf_ReceiverFunction = UART_receive;
		break;
	case BCM_SPI_ID:
		/**Set callback of the RX Buffer**/
		SPI_setCallBack(&RxApp);
		/**assign SPI receiveByte function to the local PointerToSenderFunction**/
		apf_ReceiverFunction = SPI_receiveByte;
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	/**check if still less tahn the buffer **/
	if(gu8_RxCounter < ConfigPtr->BCM_ArraySize && au8_Ret == E_OK)
	{
		/**store the receiving byte in the buffer**/
		ConfigPtr->BCM_ArrayStartAddress[gu8_RxCounter] = apf_ReceiverFunction();

		/**In case the ID is not identical**/
		if(ConfigPtr->BCM_ArrayStartAddress[0] != BCM_ID)
		{
			/**Error**/
			au8_Ret = E_NOK;
			
			/**move the state to IDLE**/
			gu8_BCM_Receiving_SM = BCM_RECEIVER_IDLE;
			gu8_RxCounter = 0;
			gu8_RxDispatchCounter = 255;
			gu8_RxCheckSum = 0;
		}else
		{
			/**if ID identical Lock the Buffer**/
			gu8_BCM_BufferState = BCM_BUFFER_LOCKED;
		}

		/**Increment the index of the receiving buffer**/
		gu8_RxCounter++;
	}
	
	/** return error number of the function**/
	return au8_Ret;
}

/**
 * Func			: BCM_TxSetCallBack
 * Input		: No Input
 *				
 * Output	
 * Return 		:				
 *
 * Description	: function BCM_TxSetCallBack shall assign the Tx call back function to be performed in ISR.
**/
void BCM_RxSetCallBack(void (*a_ptr)(void))
{
	BCM_RxCallBackPtr = a_ptr;
}
/**
 * Func			: BCM_RxSetCallBack
 * Input		: No Input
 *				
 * Output	
 * Return 		:				
 *
 * Description	: function BCM_RxSetCallBack shall assign the Rx call back function to be performed in ISR.
**/
void BCM_TxSetCallBack(void (*a_ptr)(void))
{
	BCM_TxCallBackPtr = a_ptr;
}
