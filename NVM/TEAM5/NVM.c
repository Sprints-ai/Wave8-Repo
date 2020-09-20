/*
 * NVM.c
 *
 * Created: 29/04/2020 20:01:42
 *  Author: sony
 */ 
#include "NVM.h"
#include "NVM_Cfg.h"
#include "std_types.h"
#include "avr/io.h"

#define IDLE_STATE                  0
#define READ_ALL_STATE          	1
#define WRITE_ALL_STATE         	2
#define READ_ALL_DONE_STATE     	3
#define WRITE_ALL_DONE_STATE    	4
#define READ_BLOCK_STATE        	5
#define WRITE_BLOCK_STATE           6
#define READ_BLOCK_DONE_STATE       7
#define WRITE_BLOCK_DONE_STATE      8
#define WRITING_ALL_STATE           9
#define READING_ALL_STATE           10
#define INITIALIZED                 1
#define UN_INITIALIZED              0
#define BUSY                        1
#define FREE                        0
#define DONE                        1
#define NOT_YET                     0

static uint8_t gu8_NVM_SM;
static uint8_t gu8_NVM_INIT_Flag;
static uint8_t gu8_NVMbusy_flag;
static uint8_t gu8_Read_ID;
static uint8_t* gu8ptr_ReadData;
static uint8_t gu8_Write_ID;
static uint8_t* gu8ptr_WriteData;
static volatile uint8_t gu8_WriteDone;
static  volatile uint8_t gu8_ReadDone;


void NVM_Init(void)
{
	if(gu8_NVM_INIT_Flag==INITIALIZED)
	{

	}
	else
	{
		gu8_NVM_INIT_Flag=INITIALIZED;
		gu8_NVM_SM=IDLE_STATE;
		gu8_NVMbusy_flag=FREE;
	}
}


NVM_CheckType NVM_ReadAll(void)
{
	NVM_CheckType Error=NVM_OK;
	if(gu8_NVM_INIT_Flag==UN_INITIALIZED)
	{
		Error=NVM_NOK;
	}
	else
	{
		if(gu8_NVMbusy_flag==BUSY)
		{
			Error=NVM_BUSY;
		}
		else
		{
		
			gu8_NVM_SM=READ_ALL_STATE;
			gu8_NVMbusy_flag=BUSY;
		}

	}

	return Error;
}


NVM_CheckType NVM_WriteAll(void)
{
	NVM_CheckType Error=NVM_OK;
	if(gu8_NVM_INIT_Flag==UN_INITIALIZED)
	{
		Error=NVM_NOK;
	}
	else
	{
		if(gu8_NVMbusy_flag==BUSY)
		{
			Error=NVM_BUSY;
		}
		else
		{
			gu8_NVM_SM=WRITE_ALL_STATE;
			gu8_NVMbusy_flag=BUSY;
		}

	}

	return Error;
}


NVM_CheckType NVM_ReadBlock(unsigned char BlockId, unsigned char* DataPtr)
{
	NVM_CheckType Error=NVM_OK;
	if(NULL==DataPtr)
	{
		Error=NVM_NOK;
	}
	else
	{
		if(gu8_NVMbusy_flag==BUSY)
		{
			Error=NVM_BUSY;
		}
		else
		{
			gu8_Read_ID=BlockId;
			gu8ptr_ReadData=DataPtr;
			gu8_NVMbusy_flag=BUSY;
			gu8_NVM_SM=READ_BLOCK_STATE;

		}

	}

	return Error;
}
NVM_CheckType NVM_WriteBlock(uint8_t BlockId, uint8_t* DataPtr)
{
	NVM_CheckType Error=NVM_OK;
	if(NULL==DataPtr)
	{
		Error=NVM_NOK;
	}
	else
	{
		if(gu8_NVMbusy_flag==BUSY)
		{
			Error=NVM_BUSY;
		}
		else
		{
			gu8_Write_ID=BlockId;
			gu8ptr_WriteData=DataPtr;
			gu8_NVMbusy_flag=BUSY;
			gu8_NVM_SM=WRITE_BLOCK_STATE;
		}

	}
	return Error;
}


void NVM_Main(void)
{
	static uint8_t au8_ID_count=0;
	static uint8_t au8_LEN_Count=0;
	switch(gu8_NVM_SM)
	{
		case IDLE_STATE:
		gu8_NVMbusy_flag=FREE;
		au8_LEN_Count=0;
		au8_ID_count=0;
		break;
		case WRITE_ALL_STATE:
		if(au8_ID_count==NVM_NUM_OF_BLOCKS)
		{
			gu8_NVM_SM=WRITE_ALL_DONE_STATE;
		}
		else
		{
			MEMIF_ReqWriteBlock(NVM_BlocConfig[au8_ID_count].BlockId,NVM_BlocConfig[au8_ID_count].BlockRamAddress);
			au8_ID_count++;
			gu8_NVM_SM=WRITING_ALL_STATE;
		}
		break;
		case  WRITING_ALL_STATE:
		if(gu8_WriteDone==DONE)
		{
			gu8_WriteDone=NOT_YET;
			gu8_NVM_SM=WRITE_ALL_STATE;
		}
		break;
		case READ_ALL_STATE:   
			if(au8_ID_count==NVM_NUM_OF_BLOCKS)
			{
				gu8_NVM_SM=READ_ALL_DONE_STATE;
				
			}
			else
			{

				MEMIF_ReqReadBlock(NVM_BlocConfig[au8_ID_count].BlockId,NVM_BlocConfig[au8_ID_count].BlockRamAddress);
				au8_ID_count++;
				gu8_NVM_SM=READING_ALL_STATE;
			}
			break;
		case  WRITE_BLOCK_STATE:
				for(au8_ID_count=0;au8_ID_count<NVM_NUM_OF_BLOCKS;au8_ID_count++)
				{
					if(NVM_BlocConfig[au8_ID_count].BlockId==gu8_Write_ID)
					{
						for(au8_LEN_Count=0;au8_LEN_Count<NVM_BlocConfig[au8_ID_count].BlockLength;au8_LEN_Count++)
						NVM_BlocConfig[au8_ID_count].BlockRamAddress[au8_LEN_Count]=gu8ptr_WriteData[au8_LEN_Count];
						break;
					}
				}
				gu8_NVM_SM=WRITE_BLOCK_DONE_STATE;
				break;
		case  WRITE_BLOCK_DONE_STATE:
				gu8_NVMbusy_flag=FREE;
				NVM_BlocConfig[au8_ID_count].BlockWriteNotifPtr();
				au8_ID_count=0;
				au8_LEN_Count=0;
				gu8_NVM_SM=IDLE_STATE;
				break;
		case  READ_BLOCK_STATE:
		for(au8_ID_count=0;au8_ID_count<NVM_NUM_OF_BLOCKS;au8_ID_count++)
		{
			if(NVM_BlocConfig[au8_ID_count].BlockId==gu8_Read_ID)
			{
				for(au8_LEN_Count=0;au8_LEN_Count<NVM_BlocConfig[au8_ID_count].BlockLength;au8_LEN_Count++)
				gu8ptr_ReadData[au8_LEN_Count]=NVM_BlocConfig[au8_ID_count].BlockRamAddress[au8_LEN_Count];
				break;
			}
		}
		gu8_NVM_SM=READ_BLOCK_DONE_STATE;
		break;
		case  READ_BLOCK_DONE_STATE:
		gu8_NVMbusy_flag=FREE;
		NVM_BlocConfig[au8_ID_count].BlockReadNotifPtr();
		au8_ID_count=0;
		au8_LEN_Count=0;
		gu8_NVM_SM=IDLE_STATE;
		break;
		case  READING_ALL_STATE:
		if(gu8_ReadDone==DONE)
		{

			gu8_ReadDone=NOT_YET;
			gu8_NVM_SM=READ_ALL_STATE;
			
		}
		break;
		case  READ_ALL_DONE_STATE:
				gu8_NVMbusy_flag=FREE;
				au8_ID_count=0;
				NVM_GlobalCallbacks.ReadAllCallback();
				gu8_NVM_SM=IDLE_STATE;
		break;
		case  WRITE_ALL_DONE_STATE:
				gu8_NVMbusy_flag=FREE;
				au8_ID_count=0;
				NVM_GlobalCallbacks.WriteAllCallBack();
				gu8_NVM_SM=IDLE_STATE;
				break;
		default:
			  break;
	}

}




void NVM_WriteBlockDoneNotif(void)
{
	gu8_WriteDone=DONE;
}

void NVM_ReadBlockDoneNotif(void)
{
	gu8_ReadDone=DONE;
}