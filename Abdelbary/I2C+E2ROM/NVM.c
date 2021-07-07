/*
 * NVM.c
 *
 * Created: 29/04/2020 20:01:42
 *  Author: sony
 */ 
#include "NVM_Cfg.h"
#include "MEM_IF.h"
#define FALSE 0
#define TRUE 1
#define NVM_IDLE		 0
#define NVM_WIRTE_ALL    1
#define NVM_READ_ALL	 2
#define NVM_WRITE_BLOCK  3
#define NVM_READ_BLOCK	 4
typedef unsigned char uint8_t;

uint8_t gu8_NVM_state;
uint8_t gu8_NVM_InitFlag = FALSE ;
uint8_t gu8_NVM_RAM_busy ;


void NVM_Init(void)
{
	if (gu8_NVM_InitFlag == FALSE)
	{
	gu8_NVM_state		= NVM_IDLE;	
	gu8_NVM_RAM_busy    = FALSE;
	gu8_NVM_InitFlag	= TRUE;
	}
}


NVM_CheckType NVM_ReadAll(void)
{
	NVM_CheckType u8_functionStatus = NVM_OK;
	if(gu8_NVM_InitFlag == FALSE)
	{
		u8_functionStatus = NVM_NOK;
	}
	else if(gu8_NVM_state != NVM_IDLE || gu8_NVM_RAM_busy == TRUE)
	{
		u8_functionStatus = NVM_BUSY;
	}
	else
	{
		gu8_NVM_state = NVM_READ_ALL;
		gu8_NVM_RAM_busy = FALSE;
	}
		return u8_functionStatus;

}
NVM_CheckType NVM_WriteAll(void)
{
	NVM_CheckType u8_functionStatus = NVM_OK;
	if(gu8_NVM_InitFlag == FALSE)
	{
		u8_functionStatus = NVM_NOK;
	}
	else if(gu8_NVM_state != NVM_IDLE || gu8_NVM_RAM_busy == TRUE)
	{
		u8_functionStatus = NVM_BUSY;
	}
	else
	{
		gu8_NVM_state = NVM_WIRTE_ALL;	
		gu8_NVM_RAM_busy = FALSE;
	}
		return u8_functionStatus;

}


NVM_CheckType NVM_ReadBlock(unsigned char BlockId, unsigned char* DataPtr)
{
	NVM_CheckType u8_functionStatus = NVM_OK;
	if(gu8_NVM_InitFlag == FALSE)
	{
		u8_functionStatus = NVM_NOK;
	}
	else if(gu8_NVM_state != NVM_IDLE || gu8_NVM_RAM_busy == TRUE)
	{
		u8_functionStatus = NVM_BUSY;
	}
	else
	{
		*DataPtr = *(NVM_BlocConfig[BlockId].BlockRamAddress);	
		gu8_NVM_state = NVM_READ_BLOCK;
	}
	
	return u8_functionStatus;
}



NVM_CheckType NVM_WriteBlock(unsigned char BlockId, const unsigned char* DataPtr)
{
	NVM_CheckType u8_functionStatus = NVM_OK;
	if(gu8_NVM_InitFlag == FALSE)
	{
		u8_functionStatus = NVM_NOK;
	}
	else if (gu8_NVM_state != NVM_IDLE || gu8_NVM_RAM_busy == TRUE)
	{
		u8_functionStatus = NVM_BUSY;
	}
	else
	{
		*(NVM_BlocConfig[BlockId].BlockRamAddress) = *DataPtr;
		gu8_NVM_state = NVM_WRITE_BLOCK;

	}
	
	return u8_functionStatus;
}




void NVM_Main(void)
{
	static uint8_t u8_writeCounter = 0;
	static uint8_t u8_readCounter  = 0;
	switch(gu8_NVM_state)
	{
		case NVM_IDLE:
		/*do nothing*/
		break;
		case NVM_READ_ALL:
			if (gu8_NVM_RAM_busy == FALSE)
			{
				MEMIF_ReqWriteBlock(NVM_BlocConfig[u8_readCounter].BlockId,NVM_BlocConfig[u8_readCounter].BlockRamAddress);
				u8_readCounter++;
				if (u8_readCounter == NVM_NUM_OF_BLOCKS)
				{
					u8_readCounter = 0;
					gu8_NVM_state = NVM_IDLE;
					NVM_GlobalCallbacks.ReadAllCallback();
				}
			}
			
		break;
		case NVM_WIRTE_ALL:
			if (gu8_NVM_RAM_busy == FALSE)
			{
				MEMIF_ReqWriteBlock(NVM_BlocConfig[u8_writeCounter].BlockId,NVM_BlocConfig[u8_writeCounter].BlockRamAddress);
				u8_writeCounter++;
				if (u8_writeCounter == NVM_NUM_OF_BLOCKS)
				{
					u8_writeCounter = 0;
					gu8_NVM_state = NVM_IDLE;
					NVM_GlobalCallbacks.WriteAllCallBack();
				}
			}
		break;
		case NVM_READ_BLOCK:
			gu8_NVM_RAM_busy = FALSE;
			gu8_NVM_state = NVM_IDLE;
		break;
		case NVM_WRITE_BLOCK:
			gu8_NVM_RAM_busy = FALSE;
			gu8_NVM_state = NVM_IDLE;
		break;
	}
}

void NVM_WriteBlockDoneNotif(void)
{
	gu8_NVM_RAM_busy = FALSE;
}
void NVM_ReadBlockDoneNotif(void)
{
	gu8_NVM_RAM_busy = FALSE;
}