/*
* MEMIF.c
*
* Created: 29/04/2020 00:17:25
*  Author: sony
*/

#include "MEM_IF.h"
#include "MEM_IF_Cfg.h"
#include "std_types.h"
#include "EEPROM_EXT.h"
#include "EEPROM_INT.h"


typedef enum {MEMIF_IDLE=0 , MEMIF_WRITING , MEMIF_READING  , MEMIF_DONE_WRITE , MEMIF_DONE_READING }MEMIF_StateType;
/*global state variable */

MEMIF_StateType MEMIF_state ;
unsigned char  gu8_BlockData_Write,*gu8_BlockData_Read,gu8_BlockID;

//This function is for initialization of global variables
void MEMIF_Init(void)
{
	MEMIF_state = MEMIF_IDLE ;
}

/*
* Input: Block ID and pointer to the data to be written
* Output: MEMIF_CheckType TO check the status of the function
* Description: This function for requesting a write operation for the given block in the E2prom
*/
MEMIF_CheckType MEMIF_ReqWriteBlock(unsigned char BlockId,const unsigned char* DataPtr)
{
	MEMIF_CheckType MEM_Ret;
	/*Check on the Parameters*/
	if(((BlockId >= 0u) && (BlockId < MEMIF_NUM_OF_BLOCKS)) && (DataPtr != 0))
	{
		/*Check whether it's idle to make an operation write to the block*/
		if(MEMIF_state == MEMIF_IDLE)
		{
			MEMIF_state = MEMIF_WRITING ;
			gu8_BlockData_Write = *DataPtr;
			gu8_BlockID = BlockId;
			MEM_Ret = MEMIF_OK;
		}
		else
		{
			MEM_Ret = MEMIF_BUSY;// Return that the module is busy
		}
	}
	else
	{
		MEM_Ret = MEMIF_NOK;// Return that the Function has errors
	}
	return MEM_Ret;
}

/*
* Input: Block ID
* In/Out: Address to be filled with the read data
* Output: MEMIF_CheckType TO check the status of the function
* Description: This function for requesting a read operation for the given block in the E2prom
*/
MEMIF_CheckType MEMIF_ReqReadBlock(unsigned char BlockId, unsigned char* DataPtr)
{
	
	MEMIF_CheckType MEM_Ret;
	/*Check on the Parameters*/
	if(((BlockId >= 0u) && (BlockId < MEMIF_NUM_OF_BLOCKS)) && (DataPtr != 0))
	{
		/*Check whether it's idle to make an operation read to the block*/
		if(MEMIF_state == MEMIF_IDLE)
		{
			MEMIF_state = MEMIF_READING ;
			gu8_BlockData_Read = DataPtr;
			gu8_BlockID = BlockId;
			MEM_Ret = MEMIF_OK;
		}
		else
		{
			MEM_Ret = MEMIF_BUSY;// Return that the module is busy
		}
	}
	else
	{
		MEM_Ret = MEMIF_NOK;// Return that the Function has errors
	}
	return MEM_Ret;
}

/*
* Description: This function for managing the whole module through the state machine
*/
void MEMIF_Main(void)
{
	unsigned char  u8_BlockPhysicalAdd;
	switch (MEMIF_state)
	{
		//In case the interface is IDLE no operation Read or Write is happening for now
		case MEMIF_IDLE :
		break;
		
		//In case there is a request for writing a block
		case MEMIF_WRITING:
		
		/*Calculate the Block physical address*/
		u8_BlockPhysicalAdd = (((unsigned char)MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockID].LogicalBlockId)
		+((unsigned char) MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockID].BlockPhyAddress));
		
		/*Routing the block write request to internal or external e2prom according to the MEM_Cfg.c*/
		if(MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockID].BlockStoragePlace ==  INTERNAL_MEM)
		{
			//routing write request to internal e2prom
			EEINT_ReqWrite(u8_BlockPhysicalAdd,&(gu8_BlockData_Write),MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockID].BlockLength);
		}
		else if(MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockID].BlockStoragePlace ==  EXTERNAL_MEM)
		{
			//routing write request to external e2prom
			EEEXT_ReqWrite(u8_BlockPhysicalAdd,&(gu8_BlockData_Write),MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockID].BlockLength);
		}
		else
		{
			//do nothing
		}
		break;
		
		//In case there is a request for reading a block
		case MEMIF_READING:
		
		/*Calculate the Block physical address*/
		u8_BlockPhysicalAdd = (((unsigned char)MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockID].LogicalBlockId)
		+((unsigned char) MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockID].BlockPhyAddress));
		
		/*Routing the block read request to internal or external e2prom according to the MEM_Cfg.c*/
		if(MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockID].BlockStoragePlace ==  INTERNAL_MEM)
		{
			//routing read request to internal e2prom
			EEINT_ReqRead(u8_BlockPhysicalAdd,gu8_BlockData_Read,MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockID].BlockLength);
		}
		else if(MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockID].BlockStoragePlace ==  EXTERNAL_MEM)
		{
			//routing read request to external e2prom
			EEEXT_ReqRead(u8_BlockPhysicalAdd,gu8_BlockData_Read,MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockID].BlockLength);
		}
		else
		{

		}
		break;
		// In case the writing operation is Done successfully
		case MEMIF_DONE_WRITE:
		//Call the write notification to inform the NVM that the interface can accept new requests
		MEMIF_ConfigParam.BlockWriteDoneNotif();
		MEMIF_state = MEMIF_IDLE ;//Jump to IDLE state
		
		break;
		// In case the reading operation is Done successfully
		case MEMIF_DONE_READING:
		//Call the read notification to inform the NVM that the interface can accept new requests
		MEMIF_ConfigParam.BlockReadDoneNotif();
		MEMIF_state = MEMIF_IDLE ;//Jump to IDLE state
		break;
		default:
		//do nothing
		break;

	}
}

//Callback function from the internal E2prom to notify that the write operation is done successfully
void MEMIF_IntEepromWriteCbk(void)
{
	MEMIF_state = MEMIF_DONE_WRITE;//Jump to Write Done State
}
//Callback function from the internal E2prom to notify that the read operation is done successfully
void MEMIF_IntEepromReadCbk(void)
{
	MEMIF_state = MEMIF_DONE_READING;//Jump to Read Done State
}
//Callback function from the external E2prom to notify that the write operation is done successfully
void MEMIF_ExtEepromWriteCbk(void)
{
	MEMIF_state = MEMIF_DONE_WRITE;//Jump to Write Done State
}
//Callback function from the external E2prom to notify that the read operation is done successfully
void MEMIF_ExtEepromReadCbk(void)
{
	MEMIF_state = MEMIF_DONE_READING;//Jump to Read Done State
}
