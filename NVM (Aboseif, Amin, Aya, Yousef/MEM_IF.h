/*
* MEM_IF.h
*
* Created: 29/04/2020 00:01:36
*  Author: sony
*/


#ifndef MEM_IF_H_
#define MEM_IF_H_

/************************************************************************/
/*						includes                                         */
/************************************************************************/

#include"MEM_IF_Cfg.h"


/************************************************************************/
/*						DEFINES                                         */
/************************************************************************/
/* MEM_IF_States */

#define MEM_IF_WRITE	1
#define MEM_IF_READ		2
#define MEM_IF_BUSY		3
#define MEM_IF_IDLE		0
#define MEM_IF_ERROR	4
#define	MEM_IF_CBK		5



typedef enum{MEMIF_OK,
			 MEMIF_NOK,
			 MEMIF_BUSY
			 
		}MEMIF_CheckType;
		
typedef enum{INTERNAL_MEM,
			 EXTERNAL_MEM
			 
		}MEMIF_StorageType;
		
typedef void(*MEMIF_CbkType)(void);

typedef struct
{
	unsigned char LogicalBlockId;
	unsigned char BlockLength;
	MEMIF_StorageType BlockStoragePlace;
	unsigned short int BlockPhyAddress;
	
}MEMIF_BlockConfigType;

typedef struct
{
	const MEMIF_BlockConfigType* BlockConfigPtr;
	MEMIF_CbkType BlockWriteDoneNotif;
	MEMIF_CbkType BlockReadDoneNotif;
	
}MEMIF_ConfigType;


/************************************************************************/
/*				    	API PROTOTYPES                                 */
/************************************************************************/

void MEMIF_Init(void);

MEMIF_CheckType MEMIF_ReqWriteBlock(unsigned char BlockId,const unsigned char* DataPtr);

MEMIF_CheckType MEMIF_ReqReadBlock(unsigned char BlockId, unsigned char* DataPtr);

void MEMIF_Main(void);

void MEMIF_IntEepromWriteCbk(void);

void MEMIF_IntEepromReadCbk(void);

void MEMIF_ExtEepromWriteCbk(void);

void MEMIF_ExtEepromReadCbk(void);



#endif /* MEM_IF_H_ */