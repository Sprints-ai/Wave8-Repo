/*
 * MEMIF.c
 *
 * Created: 29/04/2020 00:17:25
 *  Author: Eman
 */ 

#include "MEM_IF.h"
#include "MEM_IF_Cfg.h"
#include "EEPROM_EXT.h"
#include "EEPROM_INT.h"
#include "std_types.h"

#define MEM_IF_WRITE	1
#define MEM_IF_READ		2
#define MEM_IF_BUSY		3
#define IDLE			0
#define ERROR			4
#define	CALLBCK			5

uint8_t MEM_IF_state = IDLE;
uint8_t MEM_type = EXTERNAL_MEM;
uint8_t memory_address = 0;
uint8_t dataLen = 0;
uint8_t* data_pointer = NULL;

void MEMIF_Init(void)
{
	EEEXT_Init();
	EEINT_Init();
}

MEMIF_CheckType MEMIF_ReqWriteBlock(unsigned char BlockId,const unsigned char* DataPtr)
{
	MEMIF_CheckType retVal = MEMIF_OK;
	
	if (MEM_IF_state == IDLE)
	{
		/* Save data from configuration according to the blockID
		 * memory type, the physical address, data length, data pointer
		 */
		MEM_type = MEMIF_ConfigParam.BlockConfigPtr[BlockId].BlockStoragePlace;
		memory_address = MEMIF_ConfigParam.BlockConfigPtr[BlockId].BlockPhyAddress;
		dataLen = MEMIF_ConfigParam.BlockConfigPtr[BlockId].BlockLength;
		data_pointer = DataPtr;
		
		MEM_IF_state = MEM_IF_WRITE;
	} 
	else
	{
		retVal = MEMIF_BUSY;
	}
	
	return retVal;
}

MEMIF_CheckType MEMIF_ReqReadBlock(unsigned char BlockId, unsigned char* DataPtr)
{
	MEMIF_CheckType retVal = MEMIF_OK;
	
	if (MEM_IF_state == IDLE)
	{
		/* Save data from configuration according to the blockID
		 * memory type, the physical address, data length, data pointer
		 */
		MEM_type = MEMIF_ConfigParam.BlockConfigPtr[BlockId].BlockStoragePlace;
		memory_address = MEMIF_ConfigParam.BlockConfigPtr[BlockId].BlockPhyAddress;
		dataLen = MEMIF_ConfigParam.BlockConfigPtr[BlockId].BlockLength;
		data_pointer = DataPtr;
		
		MEM_IF_state = MEM_IF_READ;
	}
	else
	{
		retVal = MEMIF_BUSY;
	}
	
	return retVal;
}

void MEMIF_Main(void)
{
	switch(MEM_type)
	{
		case EXTERNAL_MEM:
		{
			switch(MEM_IF_state)
			{
				case IDLE:
				break;
				case MEM_IF_WRITE:
				{
					EEEXT_ReqWrite(memory_address,data_pointer,dataLen);
				}
				break;
				case MEM_IF_READ:
				{
					EEEXT_ReqRead(memory_address,data_pointer,dataLen);
				}
				break;
				case ERROR:
				break;
				case CALLBCK:
				break;
				default:
				{
					MEM_IF_state = ERROR;
				}
				break;
			}
		}
		break;
		case INTERNAL_MEM:
		{
			switch(MEM_IF_state)
			{
				case IDLE:
				break;
				case MEM_IF_WRITE:
				{
					EEINT_ReqWrite(memory_address,data_pointer,dataLen);
				}
				break;
				case MEM_IF_READ:
				{
					EEINT_ReqRead(memory_address,data_pointer,dataLen);
				}
				break;
				case ERROR:
				break;
				case CALLBCK:
				break;
				default:
				{
					MEM_IF_state = ERROR;
				}
				break;
			}
		}
		break;
		default:
		break;
	}
	
}

void MEMIF_IntEepromWriteCbk(void)
{
	MEM_IF_state = CALLBCK;
}
void MEMIF_IntEepromReadCbk(void)
{
	MEM_IF_state = CALLBCK;
}
void MEMIF_ExtEepromWriteCbk(void)
{
	MEM_IF_state = CALLBCK;
}
void MEMIF_ExtEepromReadCbk(void)
{
	MEM_IF_state = CALLBCK;
}