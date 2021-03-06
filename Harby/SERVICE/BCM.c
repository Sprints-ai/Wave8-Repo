/*
 * BCMRx.c
 *
 *  Created on: Mar 2, 2020
 *      Author: Youssef Harby & Mohamed Ramadan
 */


/*- INCLUDES -----------------------------------------------*/

#include "BCM.h"
#include "BCM_cfg.h"


/*- DEFINITIONS --------------------------------------------*/

#define UNDETERMINED		0x00


/*- GLOBAL STATIC VARIABLES --------------------------------*/

static volatile uint8_t gu8_BCM_SENDING_SM = BCM_SENDER_IDLE;
static volatile uint8_t gu8_BCM_Receiving_SM = BCM_RECEIVER_IDLE;

static volatile uint8_t gu8_BCM_BufferState = BCM_BUFFER_UNLOCKED;

static strBcmSendConfig_t TxCfg;
static strBcmSendConfig_t RxCfg;

static volatile uint8_t gu8_TxDispatchCounter = 255;
static volatile uint8_t gu8_RxDispatchCounter = 255;

static uint8_t gu8_TxCheckSum = 0;


// locals to globals

static uint8_t gu8_RxCheckSum = 0;
static uint8_t gu8_TxCounter = 0;
static uint8_t gu8_RxCounter = 0;

static void (*BCM_RxCallBackPtr)(void) = NULL;
static void (*BCM_TxCallBackPtr)(void) = NULL;


/*- CALL BACK FUNCTIONS ------------------------------------*/

void RxApp(void)
{
	gu8_BCM_Receiving_SM = BCM_RECEIVING_BYTE;
	BCM_Receive(&RxCfg);
	gu8_BCM_Receiving_SM = BCM_RECEIVING_COMPLETE;
	gu8_RxDispatchCounter++;
}

void TxApp(void)
{
	gu8_BCM_SENDING_SM = BCM_SENDING_COMPLETE;
	gu8_TxDispatchCounter++;
}


/*- APIs IMPLEMENTATION ------------------------------------*/

EnmBCMError_t BCM_Init(const strBcmConfig_t* ConfigPtr)
{
	uint8_t au8_Ret = E_OK;

	UART_ConfigType UART_cfg = {
			UART_ASYNCHRONOUS_MODE,
			UNDETERMINED,
			UART_EIGHT_BITS,
			UART_PARITY_DISABLED,
			UART_ONE_STOP_BIT,
			UART_INTERRUPT_ENABLED
	};

	SPI_ConfigType SPI_cfg = {
			UNDETERMINED,
			SPI_INTERRUPT_ENABLED,
			SPI_F_OSC_4
	};

	switch(ConfigPtr->BCM_DataDirection)
	{
	case BCM_TRANSMIT:
		UART_cfg.communicationMode = UART_SENDER_MODE;
		SPI_cfg.MasterSlaveSelect = SPI_MASTER;
		break;
	case BCM_RECEIVE:
		UART_cfg.communicationMode = UART_RECEIVER_MODE;
		SPI_cfg.MasterSlaveSelect = SPI_SLAVE;
		break;
	case BCM_TRANSMIT_RECEIVE:
		UART_cfg.communicationMode = UART_SENDER_RECEIVER_MODE;
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

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

	return au8_Ret;
}

EnmBCMError_t BCM_DeInit(uint8_t BCM_ProtocolID)
{
	uint8_t au8_Ret = E_OK;

	switch(BCM_ProtocolID)
	{
	case BCM_UART_ID:
		UART_deInit();
		UART_RXC_setCallBack(NULL);
		UART_TXC_setCallBack(NULL);
		break;
	case BCM_SPI_ID:
		SPI_deInit();
		SPI_setCallBack(NULL);
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

EnmBCMError_t BCM_RxDispatch(void)
{
	uint8_t au8_Ret = E_OK;

	if(gu8_BCM_Receiving_SM == BCM_RECEIVING_COMPLETE && gu8_RxDispatchCounter < (RxCfg.BCM_ArraySize - 1) && gu8_RxDispatchCounter >= 3)
	{
		gu8_RxCheckSum += RxCfg.BCM_ArrayStartAddress[gu8_RxDispatchCounter];

		gu8_BCM_Receiving_SM = BCM_RECEIVING_BYTE;
	}

	if(gu8_RxDispatchCounter == RxCfg.BCM_ArraySize - 1)
	{
		if(gu8_RxCheckSum != RxCfg.BCM_ArrayStartAddress[gu8_RxDispatchCounter])
			au8_Ret = E_NOK;
		gu8_BCM_Receiving_SM = BCM_RECEIVER_IDLE;
		gu8_RxCounter = 0;
		gu8_RxDispatchCounter = 255;
		gu8_RxCheckSum = 0;

		if(BCM_RxCallBackPtr != NULL)
		{
			BCM_RxCallBackPtr();
		}
	}

	return au8_Ret;
}

EnmBCMError_t BCM_TxDispatch(void)
{
	if(gu8_BCM_SENDING_SM == BCM_SENDING_COMPLETE)
	{
		if(gu8_TxDispatchCounter < TxCfg.BCM_ArraySize - 4)
		{
			gu8_TxCheckSum += TxCfg.BCM_ArrayStartAddress[gu8_TxDispatchCounter];
		}

		gu8_BCM_SENDING_SM = BCM_SENDING_BYTE;

		BCM_Send(&TxCfg);
	}

	if(gu8_TxDispatchCounter == TxCfg.BCM_ArraySize - 1)
	{
		gu8_BCM_SENDING_SM = BCM_SENDER_IDLE;
		gu8_TxCounter = 0;
		gu8_TxDispatchCounter = 255;
		gu8_TxCheckSum = 0;

		if(BCM_TxCallBackPtr != NULL)
		{
			BCM_TxCallBackPtr();
		}
	}

	return E_OK;
}

EnmBCMError_t BCM_Send(strBcmSendConfig_t* ConfigPtr)
{
	uint8_t au8_Ret = E_OK;
	static PointerToSenderFunction apf_SenderFunction = NULL;

	if(gu8_TxCounter == 0)
	{
		switch(ConfigPtr->BCM_ProtocolID)
		{
		case BCM_UART_ID:
			UART_TXC_setCallBack(&TxApp);
			apf_SenderFunction = UART_transmit;
			break;
		case BCM_SPI_ID:
			SPI_setCallBack(&TxApp);
			apf_SenderFunction = SPI_sendByte;
			break;
		default:
			au8_Ret = E_NOK;
			break;
		}

		ConfigPtr->BCM_ArrayStartAddress[ConfigPtr->BCM_ArraySize - 4] = BCM_ID;
		ConfigPtr->BCM_ArrayStartAddress[ConfigPtr->BCM_ArraySize - 3] = (uint8_t)((ConfigPtr->BCM_ArraySize-4) >> 8);
		ConfigPtr->BCM_ArrayStartAddress[ConfigPtr->BCM_ArraySize - 2] =
				(uint8_t)((ConfigPtr->BCM_ArraySize-4) & 0x00FF);
	}

	ConfigPtr->BCM_ArrayStartAddress[ConfigPtr->BCM_ArraySize - 1] = gu8_TxCheckSum;

	if(gu8_TxCounter < ConfigPtr->BCM_ArraySize)
	{
		if(gu8_TxCounter <= 2)
			apf_SenderFunction(ConfigPtr->BCM_ArrayStartAddress[ConfigPtr->BCM_ArraySize - 4 + gu8_TxCounter]);
		else if(gu8_TxCounter == ConfigPtr->BCM_ArraySize - 1)
			apf_SenderFunction(ConfigPtr->BCM_ArrayStartAddress[gu8_TxCounter]);
		else
			apf_SenderFunction(ConfigPtr->BCM_ArrayStartAddress[gu8_TxCounter - 3]);
		gu8_TxCounter++;
	}

	TxCfg = *ConfigPtr;

	return au8_Ret;
}

EnmBCMError_t BCM_SetupRxBuffer(uint8_t ProtocolID, uint8_t* ArrayFirstElementAddress, uint16_t ArraySize)
{
	uint8_t au8_Ret = E_OK;

	RxCfg.BCM_ArraySize = ArraySize;
	RxCfg.BCM_ArrayStartAddress = ArrayFirstElementAddress;
	RxCfg.BCM_ProtocolID = ProtocolID;

	switch(ProtocolID)
	{
	case BCM_UART_ID:
		UART_RXC_setCallBack(&RxApp);
		break;
	case BCM_SPI_ID:
		SPI_setCallBack(&RxApp);
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

EnmBCMError_t BCM_Receive(strBcmSendConfig_t* ConfigPtr)
{
	static uint8_t au8_Ret = E_OK;
	PointerToReceiverFunction apf_ReceiverFunction = NULL;

	switch(ConfigPtr->BCM_ProtocolID)
	{
	case BCM_UART_ID:
		UART_RXC_setCallBack(&RxApp);
		apf_ReceiverFunction = UART_receive;
		break;
	case BCM_SPI_ID:
		SPI_setCallBack(&RxApp);
		apf_ReceiverFunction = SPI_receiveByte;
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	if(gu8_RxCounter < ConfigPtr->BCM_ArraySize && au8_Ret == E_OK)
	{
		ConfigPtr->BCM_ArrayStartAddress[gu8_RxCounter] = apf_ReceiverFunction();

		if(ConfigPtr->BCM_ArrayStartAddress[0] != BCM_ID)
		{
			au8_Ret = E_NOK;
			gu8_BCM_Receiving_SM = BCM_RECEIVER_IDLE;
			gu8_RxCounter = 0;
			gu8_RxDispatchCounter = 255;
			gu8_RxCheckSum = 0;
		}else
		{
			gu8_BCM_BufferState = BCM_BUFFER_LOCKED;
		}

//		PORTD_DIR = ConfigPtr->BCM_ArrayStartAddress[gu8_RxCounter];
		gu8_RxCounter++;
	}

	return au8_Ret;
}

void BCM_RxSetCallBack(void (*a_ptr)(void))
{
	BCM_RxCallBackPtr = a_ptr;
}

void BCM_TxSetCallBack(void (*a_ptr)(void))
{
	BCM_TxCallBackPtr = a_ptr;
}
