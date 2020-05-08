/*
 * MEMIF.c
 *
 * Created: 29/04/2020 00:17:25
 *  Author: sony
 */ 

/************************************************************************/
/*						includes                                         */
/************************************************************************/
#include"MEM_IF.h"

/************************************************************************/
/*					global vars                                         */
/************************************************************************/


uint8_t MEM_IF_state ;
uint8_t MEM_type 	 ;
uint8_t MEM_address  ;
uint8_t dataLength 	 ;
uint8_t* data_pointer;


/************************************************************************/
/*				    	API IMPLEMENTATION                              */
/************************************************************************/


void MEMIF_Init(void){
	
	/* initialize the global vars */
	
	MEM_IF_state  = MEM_IF_IDLE;
	MEM_type 	  = EXTERNAL_MEM;
	MEM_address   = 0;
	dataLength 	  = 0;
	data_pointer = NULL;


	/* initialize the two memories */
	EEEXT_Init();
	EEINT_Init();
}

MEMIF_CheckType MEMIF_ReqWriteBlock(unsigned char BlockId,const unsigned char* DataPtr){
	
	MEMIF_CheckType status = MEMIF_OK;

	if (MEM_IF_state == MEM_IF_IDLE)
	{
		/* set the data configs */
		if(DataPtr != NULL){
		
		data_pointer = DataPtr;

		MEM_type    = MEMIF_ConfigParam.BlockConfigPtr[BlockId].BlockStoragePlace;
		
		MEM_address = MEMIF_ConfigParam.BlockConfigPtr[BlockId].BlockPhyAddress;
		
		dataLength  = MEMIF_ConfigParam.BlockConfigPtr[BlockId].BlockLength;
		
		/* change the mem_if state */
		MEM_IF_state = MEM_IF_WRITE;
		}else
		{
			status = MEMIF_NOK; /* null pointer*/
		} 	
	}
	else
	{
		status = MEMIF_BUSY;
	}

	return status;
}
	
MEMIF_CheckType MEMIF_ReqReadBlock(unsigned char BlockId, unsigned char* DataPtr)
{
	MEMIF_CheckType status = MEMIF_OK;

	if (MEM_IF_state == MEM_IF_IDLE)
	{
		/* set the data configs */
		if(DataPtr != NULL){
		
		data_pointer = DataPtr;

		MEM_type    = MEMIF_ConfigParam.BlockConfigPtr[BlockId].BlockStoragePlace;
		
		MEM_address = MEMIF_ConfigParam.BlockConfigPtr[BlockId].BlockPhyAddress;
		
		dataLength  = MEMIF_ConfigParam.BlockConfigPtr[BlockId].BlockLength;
		
		/* change the mem_if state */
		MEM_IF_state = MEM_IF_READ;
		}else
		{
			status = MEMIF_NOK; /* null pointer*/
		}
		
	} 
	else
	{
		status = MEMIF_BUSY;
	}
	
	return status;
}


void MEMIF_Main(void)
{
	
		if(MEM_type == EXTERNAL_MEM )
		{
			if(MEM_IF_state == MEM_IF_WRITE )
			{
					/* EXTERNAL EEPROM API */
					EEEXT_ReqWrite(MEM_address, data_pointer, dataLength);
			}
			else if (MEM_IF_WRITE == MEM_IF_READ)
				{
					/* EXTERNAL EEPROM API */
					EEEXT_ReqRead(MEM_address, data_pointer, dataLength);
				}else
				{
					/* nothing */
				}
				
		}	
		else if(MEM_type == INTERNAL_MEM)
		{
			if(MEM_IF_state == MEM_IF_WRITE )
			{
					/* INTERNAL EEPROM API */
					EEINTT_ReqWrite(MEM_address, data_pointer, dataLength);
			}
			else if (MEM_IF_WRITE == MEM_IF_READ)
				{
					/* INTERNAL EEPROM API */
					EEINT_ReqRead(MEM_address, data_pointer, dataLength);
				}else
				{
					/* nothing */
				}
			
	    }else
		{
			/* nothing */
		}

}

/* Reset the MEM_IF_state TO MEM_IF_IDLE and call the Callback functions */

void MEMIF_IntEepromWriteCbk(void)
{
	MEM_IF_state = MEM_IF_IDLE;
	MEMIF_ConfigParam.BlockWriteDoneNotif();
}

void MEMIF_IntEepromReadCbk(void)
{
	MEM_IF_state = MEM_IF_IDLE;

	MEMIF_ConfigParam.BlockReadDoneNotif();
}

void MEMIF_ExtEepromWriteCbk(void)
{
	MEM_IF_state = MEM_IF_IDLE;
	MEMIF_ConfigParam.BlockWriteDoneNotif();
}

void MEMIF_ExtEepromReadCbk(void)
{
	MEM_IF_state = MEM_IF_IDLE;

	MEMIF_ConfigParam.BlockReadDoneNotif();
}