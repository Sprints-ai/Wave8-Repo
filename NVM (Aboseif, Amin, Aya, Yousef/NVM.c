/*
 * NVM.c
 *
 * Created: 06/05/2020 20:01:42
 *  Author: Aya Ayman
 */ 


/*
*** Inclusions
*/
#include "NVM.h"
#include "NVM_Cfg.h"
#include "MEM_IF.h"
#include <stdint.h>

/*
*** Local Macros 
*/

#define NOT_INITIALIZED          0x00
#define INITIALIZED              0x01

// NVM State Machine Values
#define STATE_IDLE					0x00
#define STATE_READING_BLOCK		0x01
#define STATE_WRITING_BLOCK	   0x02
#define STATE_READING_ALL        0x03
#define STATE_WRITING_ALL        0x04

// Flags Values
#define DONE						   0x01
#define IN_PROGRESS              0X00
#define IDLE                     0xff

/*
*** Global Static Variables
*/

static uint8_t gu8_Block_Id;
static uint8_t*  gu8ptr_Data;


static uint8_t gu8_State;
static uint8_t gu8_DateWriteBlockFlag;
static uint8_t gu8_DateReadBlockFlag;

static uint16_t CRC_ARR[NVM_NUM_OF_BLOCKS] = {0};   //array to store CRC Values For Each Block
static uint8_t u8_Block_Default_Value [NVM_NUM_OF_BLOCKS ];  //array to Save Default Values For Each Block

/* 
*** Static Functions Prototype
*/
unsigned short Gen_CRC16(const unsigned char* , unsigned char);

/*
*** Function Implementation
*/

/*
*** Function        : unsigned short Gen_CRC16(const unsigned char* data_p, unsigned char length)
*** Type            : Static
*** Input parameters: const unsigned char* data_p -> Poninter to the data we want to calculate it's CRC
***                 : unsigned char length -> Length of the data
*** Return type     : unsigned short
*** Description: This function is used To Calculate CRC 
*/

unsigned short Gen_CRC16(const unsigned char* data_p, unsigned char length)
{
	unsigned char u8_Temp;
	unsigned short crc = 0xFFFF;
	while (length--)
	{
		u8_Temp = crc >> 8 ^ *data_p++;
		u8_Temp ^= u8_Temp>>4;
		crc = (crc << 8) ^ ((unsigned short)(u8_Temp << 12)) ^ ((unsigned short)(u8_Temp <<5)) ^ ((unsigned short)u8_Temp);
	}
	return crc;
}

/*
*** Function        : void NVM_Init(void)
*** Type            : Public
*** Input parameters: None
*** Return type     : None
*** Description     : This function is used To Initialize NVM, initializing some variable,
                      besides storing default values of Each Ram MirrorBlock
*/
void NVM_Init()
{
	uint8_t u8_Loop_Counter = ZERO;
	
	for (u8_Loop_Counter = ZERO ; u8_Loop_Counter < NVM_NUM_OF_BLOCKS ; u8_Loop_Counter++)
	{
		u8_Block_Default_Value [u8_Loop_Counter] = *(NVM_BlocConfig [u8_Loop_Counter].BlockRamAddress);   // Save Default value in Case there are CRC error, we will Send it 
		
	}
	gu8_State = STATE_IDLE;
	gu8_DateWriteBlockFlag = IDLE;
	
}


/*
*** Function        : NVM_CheckType NVM_WriteBlock(unsigned char BlockId, const unsigned char* DataPtr)
*** Type            : Public
*** Input parameters: unsigned char BlockId -> ID Of the Block we want to write into
                    :  const unsigned char* DataPtr -> pointer to the data we want to write 
*** Return type     : NVM_CheckType -> Determine the status of our request 
*** Description     : This function is Responsible for Establishing a request For Writing data
*/
NVM_CheckType NVM_WriteBlock(unsigned char BlockId, const unsigned char* DataPtr)
{
	NVM_CheckType NVM_Check = NVM_OK;
	uint8_t au8_Loop_Counter = ZERO;
	uint8_t au8_Element_Flag = NOT_INITIALIZED;
	
	/* Check if NVM Not Busy */
	if (gu8_State == STATE_IDLE)
	{
		/* Check NULL Pointer */ 
		if ( DataPtr != NULL)
		{
			/* Check if it's a valid Block id */
			for (au8_Loop_Counter = ZERO ; au8_Loop_Counter < NVM_NUM_OF_BLOCKS && au8_Element_Flag == NOT_INITIALIZED ; au8_Loop_Counter++)
			{
				if (NVM_BlocConfig [au8_Loop_Counter].BlockId ==  BlockId )
				{
					NVM_Check = NVM_OK;
					gu8_Block_Id = BlockId;
					gu8ptr_Data = DataPtr;
					gu8_State = STATE_WRITING_BLOCK;
					au8_Element_Flag = INITIALIZED;  // To Terminate the loop
				}
				else
				{
					NVM_Check = NVM_NOK;
				}
			}
		}
		else
		{
			NVM_Check = NVM_NOK;
		}
	}
	else
	{
		NVM_Check = NVM_BUSY;
	}
	
	return NVM_Check;
}



/*
*** Function        : NVM_CheckType NVM_ReadBlock(unsigned char BlockId, unsigned char* DataPtr)
*** Type            : Public
*** Input parameters: unsigned char BlockId -> ID Of the Block we want to Read it's
                    :  const unsigned char* DataPtr -> pointer to Store the data we  Read
*** Return type     : NVM_CheckType -> Determine the status of our request
*** Description     : This function is Responsible for Establishing a request For Reading data
*/
NVM_CheckType NVM_ReadBlock(unsigned char BlockId, unsigned char* DataPtr)
{
	NVM_CheckType NVM_Check = NVM_OK;
	uint8_t au8_NVM_ReadBlock_LoopCounter = ZERO;
	uint8_t au8_Element_Flag = NOT_INITIALIZED;
	
	/* Check if NVM Not Busy */
	if (gu8_State == STATE_IDLE)
	{
		/* Check NULL Pointer */
		if ( DataPtr != NULL)
		{
			/* Check if it's a valid Block id */
			for (au8_NVM_ReadBlock_LoopCounter = ZERO ; au8_NVM_ReadBlock_LoopCounter < NVM_NUM_OF_BLOCKS && au8_Element_Flag == NOT_INITIALIZED ; au8_NVM_ReadBlock_LoopCounter++)
			{
				if (NVM_BlocConfig [au8_NVM_ReadBlock_LoopCounter].BlockId ==  BlockId )
				{
					NVM_Check = NVM_OK;
					gu8_Block_Id = BlockId;
					gu8ptr_Data = DataPtr;
					gu8_State = STATE_READING_BLOCK;
					au8_Element_Flag = INITIALIZED;
				}
				else
				{
					NVM_Check = NVM_NOK;
				}
			}
		}
		else
		{
			NVM_Check = NVM_NOK;
		}
	}
	else
	{
		NVM_Check = NVM_BUSY;
	}
	
	return NVM_Check;	
}


/*
*** Function        : void NVM_Main(void)
*** Type            : Public
*** Input parameters: None
*** Return type     : None
*** Description     : NVM Main Function
*/
void NVM_Main(void)
{
	uint8_t au8_NVM_Main_LoopCounter = ZERO;
	uint8_t au8_Flag_State = NOT_INITIALIZED;
	uint16_t u16_Flag_Count = ZERO;
///	uint8_t* au8_PtrData;
   MEMIF_CheckType MEM_Write_Check;
   MEMIF_CheckType MEM_Read_Check;
	
	switch (gu8_State)
	{
		case STATE_IDLE:
		{
			
			break;
		}
		case STATE_WRITING_BLOCK:
		{
			//Determine Which Block
			for ( au8_NVM_Main_LoopCounter = ZERO; au8_NVM_Main_LoopCounter < NVM_NUM_OF_BLOCKS && au8_Flag_State == NOT_INITIALIZED; au8_NVM_Main_LoopCounter++) 
			{
				if (NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockId == gu8_Block_Id )
				{
					//Save data into the corresponding Location
					*(NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockRamAddress) = *gu8ptr_Data;
					//Call the Consumer
					NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockWriteNotifPtr();
					au8_Flag_State = INITIALIZED; // to terminate the loop;
				}
				else 
				{
					//Do nothing
				}
			}
			
			au8_Flag_State = NOT_INITIALIZED;
			break;
		}
		
		case STATE_READING_BLOCK:
		{
			for ( au8_NVM_Main_LoopCounter = ZERO; au8_NVM_Main_LoopCounter < NVM_NUM_OF_BLOCKS && au8_Flag_State == NOT_INITIALIZED; au8_NVM_Main_LoopCounter++)
			{
				if (NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockId == gu8_Block_Id )
				{
					*gu8ptr_Data = *(NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockRamAddress);
					NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockReadNotifPtr();
					au8_Flag_State = INITIALIZED; // to terminate the loop;
				}
				else
				{
					//Do nothing
				}
			}
			au8_Flag_State = NOT_INITIALIZED;
			break;
		}
		case STATE_WRITING_ALL:
		{			
			for ( au8_NVM_Main_LoopCounter = ZERO; au8_NVM_Main_LoopCounter < NVM_NUM_OF_BLOCKS; )
			{
				if (gu8_DateWriteBlockFlag == IDLE || gu8_DateWriteBlockFlag == DONE)
				{
					MEM_Write_Check = MEMIF_ReqWriteBlock(NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockId, NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockRamAddress);
					if (MEM_Write_Check == MEMIF_OK)
					{
						CRC_ARR[au8_NVM_Main_LoopCounter] = Gen_CRC16( NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockRamAddress,  NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockLength);
						au8_NVM_Main_LoopCounter++; // Increment Counter to handle the Next Block
						gu8_DateWriteBlockFlag = IN_PROGRESS;
					}
					else
					{
						//MEMIF Is Busy or something went Wrong
					}
						
				}
				else
				{
					// MEM Is In progress Writing Data
				}
			}
			
			for ( au8_NVM_Main_LoopCounter = ZERO; au8_NVM_Main_LoopCounter < NVM_NUM_OF_BLOCKS ; au8_NVM_Main_LoopCounter++)
			{
				if (gu8_DateReadBlockFlag == IDLE || gu8_DateReadBlockFlag == DONE)
				{
					MEM_Read_Check = MEMIF_ReqReadBlock(NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockId, NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockRamAddress);
					if (MEM_Read_Check == MEMIF_OK)
					{
						//Check if the data written correctly or not using CRC
						if ( CRC_ARR[au8_NVM_Main_LoopCounter] == Gen_CRC16(  NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockRamAddress,  sizeof(char)))
						{
							u16_Flag_Count++;  // Count Number of Matched CRC Values
							gu8_DateReadBlockFlag = IN_PROGRESS;
							
						}
						else
						{
							//Do Nothing
						}
					}
					else
					{
						//MEMIF Is Busy or something went Wrong
					}
				}
				else
				{
					//MEM is In Progress Reading Data 
				}
			}
			
			// If Number of Matched CRC == Number OF Blocks
			if (u16_Flag_Count ==  NVM_NUM_OF_BLOCKS-1 )
			{
				//Data Written correctly
				
			}
			else
			{
				//Load RAM with the Default Values
				for ( au8_NVM_Main_LoopCounter = ZERO; au8_NVM_Main_LoopCounter < NVM_NUM_OF_BLOCKS;)
				{
					if (gu8_DateWriteBlockFlag == IDLE || gu8_DateWriteBlockFlag == DONE)
					{
						MEM_Write_Check = MEMIF_ReqWriteBlock(NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockId,u8_Block_Default_Value [au8_NVM_Main_LoopCounter]);
					
						if (MEM_Write_Check == MEMIF_OK)
						{
							 au8_NVM_Main_LoopCounter++;
							 gu8_DateWriteBlockFlag = IN_PROGRESS;
						}
						else
						{
							
						}
					}
					else
					{
						
					}
				}
			}
			break;
		}
		
		case STATE_READING_ALL:
		{
			for ( au8_NVM_Main_LoopCounter = ZERO; au8_NVM_Main_LoopCounter < NVM_NUM_OF_BLOCKS ;)
			{
				if (gu8_DateReadBlockFlag == IDLE || gu8_DateReadBlockFlag == DONE)
				{
					MEM_Read_Check = MEMIF_ReqReadBlock(NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockId, NVM_BlocConfig [au8_NVM_Main_LoopCounter].BlockRamAddress);
					if (MEM_Read_Check == MEMIF_OK)
					{
						gu8_DateReadBlockFlag = IN_PROGRESS;
						au8_NVM_Main_LoopCounter++;
							
					}
					else
					{
						//MEMIF Is Busy or something went Wrong
					}
				}
				else
				{
					//MEM is In Progress Reading Data
				}
			}
			break;
		}
		default :
		break;
		}
	
}


/*
*** Function        : void NVM_WriteBlockDoneNotif(void)
*** Type            : Public
*** Input parameters: None
*** Return type     : NOne 
*** Description     : This Function is Responsible to Give NVM Main Function indication that write block is done
*/

void NVM_WriteBlockDoneNotif(void)
{
	gu8_DateWriteBlockFlag = DONE;
}

/*
*** Function        : void NVM_ReadBlockDoneNotif(void)
*** Type            : Public
*** Input parameters: None
*** Return type     : NOne
*** Description     : This Function is Responsible to Give NVM Main Function indication that Read block is done
*/

void NVM_ReadBlockDoneNotif(void)
{
	gu8_DateReadBlockFlag = DONE;
}


/*
*** Function        : NVM_CheckType NVM_ReadAll(void)
*** Type            : Public
*** Input parameters: None
*** Return type     : NVM_CheckType
*** Description     : This Function is Responsible to Give NVM Main Function indication to Read Data from EEPROM and Store it in Ram Mirror
*/
NVM_CheckType NVM_ReadAll(void)
{
	
	NVM_CheckType NVM_Check = NVM_OK;
	/* Check if NVM Not Busy */
	if (gu8_State == STATE_IDLE)
	{
		gu8_State = STATE_READING_ALL;
	}
	else
	{
		NVM_Check = NVM_NOK;
	}
	return NVM_Check;
	
}

/*
*** Function        : NVM_CheckType NVM_WriteAll(void)
*** Type            : Public
*** Input parameters: None
*** Return type     : NVM_CheckType 
*** Description     : This Function is Responsible to Give NVM Main Function indication to Save Data from Ram Mirror to EEPROM
*/
NVM_CheckType NVM_WriteAll(void)
{
	NVM_CheckType NVM_Check = NVM_OK;
	
	/* Check if NVM Not Busy */
	if (gu8_State == STATE_IDLE)
	{
		gu8_State = STATE_WRITING_ALL;
	}
	else
	{
		 NVM_Check = NVM_NOK;
	}
	
	return NVM_Check;
}

