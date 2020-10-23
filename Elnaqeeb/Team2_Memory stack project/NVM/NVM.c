/*
 * NVM.c
 *
 * Created: 29/04/2020 20:01:42
 *  Author: sony
 */ 
#include "NVM.h"
#include "NVM_Cfg.h"
#include "std_types.h"

/****************STATIC Typedefs**************************/
typedef enum {NVM_IDLE=0u ,
			  NVM_WRITING_ALL , 
			  NVM_READING_ALL , 
			  NVM_WRITING_BLOCK , 
			  NVM_READING_BLOCK , 
			  NVM_DONE_WRITEINR_BLOCK_FROM_ALL , 
			  NVM_DONE_READING_BLOCK_FROM_ALL ,
			  NVM_DONE_WRITEINR_ALL ,
			  NVM_DONE_READING_ALL }NVM_StateType;

/****************STATIC Globals**************************/
/*global state variable */

static NVM_StateType NVM_state ;


static unsigned char gu8_NVM_ReadBlock_BlockId ;
static unsigned char* gu8_NVM_ReadBlock_DataPtr ;

static unsigned char gu8_NVM_WriteBlock_BlockId ;
static unsigned char* gu8_NVM_WriteBlock_DataPtr ;

static unsigned char gu8Data;
static volatile uint8_t  gu8_Reading_Block_To_Check_Flag = FALSE ;

#define CRC16 0x8005

/****************STATIC PROTOTYPES**************************/
static unsigned short Gen_CRC16(const unsigned char* data_p, unsigned char length);

/*******************Function implementation*****************/
/*
 * Description: this function used to calculate the CRC error checking value
 */
unsigned short Gen_CRC16(const unsigned char* data_p, unsigned char length)
{
	unsigned char x;
	unsigned short crc = 0xFFFF;
	while (length--)
	{
		x = crc >> 8 ^ *data_p++;
		x ^= x>>4;
		crc = (crc << 8) ^ ((unsigned short)(x << 12)) ^ ((unsigned short)(x <<5)) ^ ((unsigned short)x);
	}
	return crc;
}
/*
 * Description: this function used to initialize globals
 */

void NVM_Init(void)
{
	NVM_state = NVM_IDLE ;
}


/*read from physical to ram mirror*/
NVM_CheckType NVM_ReadAll(void)
{
	NVM_CheckType Error_State ;
	if (NVM_state == NVM_IDLE)
	{
		NVM_state = NVM_READING_ALL ;
		Error_State = NVM_OK;
	}
	else
	{
	    Error_State = NVM_BUSY ;
	}
	
	return Error_State ;
}

/* write into physical from ram*/
NVM_CheckType NVM_WriteAll(void)
{
	NVM_CheckType Error_State ;
	if (NVM_state == NVM_IDLE)
	{
		NVM_state = NVM_WRITING_ALL ;
		Error_State = NVM_OK ;
	}
	else
	{
		Error_State = NVM_BUSY ;
	}

	return Error_State ;
}

/* from ram to client */

NVM_CheckType NVM_ReadBlock(unsigned char BlockId, unsigned char* DataPtr)
{
	
	NVM_CheckType Error_State ;
	if(((BlockId >= 0u) && (BlockId < NVM_NUM_OF_BLOCKS)) && (DataPtr != 0))
	{
		if (NVM_state == NVM_IDLE)
		{
			gu8_NVM_ReadBlock_BlockId = BlockId ;
			gu8_NVM_ReadBlock_DataPtr = DataPtr ;
			NVM_state = NVM_READING_BLOCK  ;
			Error_State = NVM_OK ;
		}
		else
		{
		    Error_State = NVM_BUSY ;
		}
	}
	else
	{
		Error_State = NVM_NOK;
	}
	return Error_State ;
}

/*from client to ram*/

NVM_CheckType NVM_WriteBlock(unsigned char BlockId, const unsigned char* DataPtr)
{
	NVM_CheckType Error_State ;
	if(((BlockId >= 0u) && (BlockId < NVM_NUM_OF_BLOCKS)) && (DataPtr != 0))
	{
		if (NVM_state == NVM_IDLE)
		{
			gu8_NVM_WriteBlock_BlockId = BlockId ;
			gu8Data = *DataPtr;
			gu8_NVM_WriteBlock_DataPtr = &gu8Data ;
			NVM_state = NVM_WRITING_BLOCK;
			Error_State = NVM_OK ;
		}
		else
		{
		    Error_State = NVM_BUSY ;
		}
	}
	else
	{
		Error_State =NVM_NOK;
	}
	return Error_State ;
}

/*
 * Description: This function for managing the whole module through the state machine 
 */

void NVM_Main(void)
{
	uint8_t au8_counter1 = 0u ;
	static NVM_ConfigType Current_Block ;
	static uint8_t au8_NUM_OF_OPERATED_BLOCKS = 0u  ;
	static uint16_t au16_Actual_CRC ;
	static uint16_t au16_calculated_CRC ;
	static uint8_t au8_Data_after_Write ;
	static uint8_t au8_Send_Next_Block_Flag = FALSE ;
	
	unsigned char u8BlockID;
	switch (NVM_state)
	{
	case NVM_IDLE :
		break;
		
	case NVM_WRITING_ALL:
	    u8BlockID = NVM_BlocConfig[au8_NUM_OF_OPERATED_BLOCKS].BlockId;
		/*write one block */
		MEMIF_ReqWriteBlock(u8BlockID,
		                    ((const unsigned char*) NVM_BlocConfig[au8_NUM_OF_OPERATED_BLOCKS].BlockRamAddress)) ;
		break;
		
	case NVM_READING_ALL:
	    u8BlockID = NVM_BlocConfig[au8_NUM_OF_OPERATED_BLOCKS].BlockId;
		/*read one block*/
		MEMIF_ReqReadBlock(u8BlockID,
		                   ((unsigned char*)NVM_BlocConfig[au8_NUM_OF_OPERATED_BLOCKS].BlockRamAddress )) ;

		break;
		
	case NVM_WRITING_BLOCK:
		/**************************/
		
		/*first b for loop alf 3la el blocks w ageb el block pointer*/
		for (au8_counter1 = 0u ; au8_counter1 < NVM_NUM_OF_BLOCKS ; au8_counter1 ++)
		{
			if (NVM_BlocConfig[au8_counter1].BlockId== gu8_NVM_WriteBlock_BlockId )
			{
				Current_Block = NVM_BlocConfig[au8_counter1] ;
				break;
			}
		}
		
		/* for loop t7ot kol data b el blocklength*/
		
		for (au8_counter1 = 0u ; au8_counter1 < Current_Block.BlockLength ; au8_counter1 ++)
		{
			Current_Block.BlockRamAddress[au8_counter1] = gu8_NVM_WriteBlock_DataPtr[au8_counter1] ;
			
		}
		
		NVM_state = NVM_IDLE ;
		Current_Block.BlockWriteNotifPtr();
		/**************************/
		
		break;
		
	case NVM_READING_BLOCK:
	
		/**************************/
		
		/*first for loop alf 3la el blocks w ageb el block pointer*/
		for (au8_counter1 = 0u ; au8_counter1 < NVM_NUM_OF_BLOCKS ; au8_counter1 ++)
		{
			if (NVM_BlocConfig[au8_counter1].BlockId== gu8_NVM_ReadBlock_BlockId )
			{
				Current_Block = NVM_BlocConfig[au8_counter1] ;
				break;
			}
			else
			{

			}
		}
		
		/* for loop t7ot kol data b el block length*/
		
		for (au8_counter1 = 0u ; au8_counter1 < Current_Block.BlockLength ; au8_counter1 ++)
		{
			gu8_NVM_ReadBlock_DataPtr[au8_counter1] = Current_Block.BlockRamAddress[au8_counter1] ;
		}
		Current_Block.BlockReadNotifPtr();
		NVM_state = NVM_IDLE ;
		/**************************/
		
		break;	
		
	case NVM_DONE_WRITEINR_BLOCK_FROM_ALL:
		/*check first by CRC*/
		/*calculate actual data CRC*/
		
		au16_Actual_CRC = (uint16_t)(Gen_CRC16(
		((unsigned char*) NVM_BlocConfig[au8_NUM_OF_OPERATED_BLOCKS].BlockRamAddress)
		,(NVM_BlocConfig[au8_NUM_OF_OPERATED_BLOCKS].BlockLength)));
		
		
		if (gu8_Reading_Block_To_Check_Flag == FALSE)
		{
			/*read the written data again to validate it */
			
			MEMIF_ReqReadBlock(NVM_BlocConfig[au8_NUM_OF_OPERATED_BLOCKS].BlockId,&au8_Data_after_Write);
			
		}
		/*wait for the data */
		else if(gu8_Reading_Block_To_Check_Flag == TRUE )
		{
			au16_calculated_CRC = Gen_CRC16(
			(( unsigned char*) &au8_Data_after_Write)
			,NVM_BlocConfig[au8_NUM_OF_OPERATED_BLOCKS].BlockLength);
			if (au16_Actual_CRC==au16_calculated_CRC)
			{
				/*set the sending next block flag */
				au8_Send_Next_Block_Flag = TRUE ;
			}
			else
			{
			    /*send same block again*/
			    NVM_state = NVM_WRITING_ALL ;
			}

				
		gu8_Reading_Block_To_Check_Flag = FALSE ;
		}
		
		
		
		/**** send next block ****/
		
		if(au8_Send_Next_Block_Flag == TRUE)
		{
			au8_NUM_OF_OPERATED_BLOCKS ++ ;
			
			/* if still block go to send next block */
			if ( au8_NUM_OF_OPERATED_BLOCKS < NVM_NUM_OF_BLOCKS )
			{
				NVM_state = NVM_WRITING_ALL ;
			}
			/*if blocks done */
			else
			{
				NVM_state = NVM_DONE_WRITEINR_ALL ;
				
			}
			au8_Send_Next_Block_Flag = FALSE ;	
		}	
			
		break;	
	case NVM_DONE_READING_BLOCK_FROM_ALL:
	
		au8_NUM_OF_OPERATED_BLOCKS ++ ;
		
		if ( au8_NUM_OF_OPERATED_BLOCKS < NVM_NUM_OF_BLOCKS )
		{
			/* if still block go to send next block */
			NVM_state = NVM_READING_ALL ;
		}
		else
		{
			/*if blocks done */
			NVM_state = NVM_DONE_READING_ALL ;
			au8_NUM_OF_OPERATED_BLOCKS = 0u ;
		}
		
		break;
		
	case NVM_DONE_WRITEINR_ALL :
		NVM_GlobalCallbacks.WriteAllCallBack();
		NVM_state = NVM_IDLE ;
		break ;
		
	case NVM_DONE_READING_ALL :
		NVM_GlobalCallbacks.ReadAllCallback ();
		NVM_state = NVM_IDLE ;
		break;
	default:
	break;
	}
}

/************Callbacks**************************/

void NVM_WriteBlockDoneNotif(void)
{
	NVM_state = NVM_DONE_WRITEINR_BLOCK_FROM_ALL ;
}
void NVM_ReadBlockDoneNotif(void)
{
	if (NVM_state==NVM_DONE_WRITEINR_BLOCK_FROM_ALL)
	{
		/*set flag */
		
		gu8_Reading_Block_To_Check_Flag = TRUE ;
		
	}
	else
	{
	    NVM_state = NVM_DONE_READING_BLOCK_FROM_ALL ;
	}
}
