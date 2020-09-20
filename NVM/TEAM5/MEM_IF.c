/*
 * MEMIF.c
 *
 * Created: 29/04/2020 00:17:25
 *  Author: sony
 */ 
#define ENABLE         1
#define DISABLE        0
#define TEST           DISABLE
/*******************************************************************
 *--------------------------- INCLUDES ----------------------------*
 *******************************************************************/
#include "avr/io.h"
#include "MEM_IF.h"
#include "MEM_IF_Cfg.h"
#include "std_types.h"
#include "EEPROM_EXT.h"
#include "EEPROM_INT.h"

#if (TEST == ENABLE)
#include <stdio.h>
#endif

/*******************************************************************
 *------------------------- LOCLA MACROS --------------------------*
 *******************************************************************/
#define COUNTER_INITIAL_VALUE     0u
#define CLEAR_BLOCK_FLAG     0u
#define SET_BLOCK_FLAG       1u

/* main function status */
#define IDLE_STATUS          5u
#define LOGIC_STATUS         6u
#define WAIT_STATUS          7u

/*******************************************************************
 *----------------------- GLOBAL VARIABLES ------------------------*
 *******************************************************************/
static uint8_t gu8_WriteBlockFlag;
static uint8_t gu8_READ_BLOCK_FLAG;

static  uint8_t* gu8_DataPtr;
static uint8_t gu8_BlockNum;

static uint8_t gu8_MainFuncStatus;

/*******************************************************************
 *---------------------- API IMPLEMENTATIONS ----------------------*
 *******************************************************************/
void MEMIF_Init(void)
{
    #if (ENABLE == TEST)
    printf("Function: MEMIF_Init start \n");
    #endif
    /*initiate globla variables*/
    gu8_WriteBlockFlag = CLEAR_BLOCK_FLAG;
    gu8_READ_BLOCK_FLAG = CLEAR_BLOCK_FLAG;
    gu8_MainFuncStatus = IDLE_STATUS;
    gu8_DataPtr = NULL;
    #if (ENABLE == TEST)
    printf("Function: MEMIF_Init finished \n");
    #endif
}


MEMIF_CheckType MEMIF_ReqWriteBlock(unsigned char BlockId, unsigned char* DataPtr)
{
    MEMIF_CheckType au8_Return = MEMIF_OK; /*consider the return ok as initial value*/
    uint8_t au8_Counter = COUNTER_INITIAL_VALUE;
    uint8_t au8_LogicalBlockId;
    /*check if the pointer is null*/
    if (NULL == DataPtr)
    {
        au8_Return = MEMIF_NOK;
        #if (ENABLE == TEST)
        printf("Invalid Data Pointer \n");
        #endif
    }
    else
    {
        #if (ENABLE == TEST) 
        printf("Valid Data Pointer \n");
        #endif 
    }
    
    #if (ENABLE == TEST)
    printf("Searching about Block ID ... \n");
    #endif
    
    for(au8_Counter = COUNTER_INITIAL_VALUE; au8_Counter < MEMIF_NUM_OF_BLOCKS; au8_Counter++)
    {
        au8_LogicalBlockId = MEMIF_ConfigParam.BlockConfigPtr[au8_Counter].LogicalBlockId;
        /*ensure that given block id exist*/
        if (BlockId == au8_LogicalBlockId)
        {
            break;
            #if (ENABLE == TEST)
            printf("Block Id %d exist number %d in Block Confg Array \n",BlockId, au8_Counter);
            #endif
        }
        
        if ( au8_Counter == (MEMIF_NUM_OF_BLOCKS - 1u) )
        {
            au8_Return = MEMIF_NOK;
            #if (ENABLE == TEST)
            printf("Block Id doesn't exist \n");
            #endif
        }
    }
    /*if the parameter is valid*/
    if (MEMIF_OK == au8_Return)
    {
        #if (ENABLE == TEST)
        printf("Function: MEMIF_ReqWriteBlock Parameters are valid \n");
        #endif
        /*ensure that the module is available*/
        if (IDLE_STATUS != gu8_MainFuncStatus)
        {
            au8_Return = MEMIF_BUSY;
            #if (ENABLE == TEST)
            printf("Function: MEMIF_ReqWriteBlock is Busy and can't execute now \n");
            #endif
        } 
        else
        {
            #if (ENABLE == TEST)
            printf("Function: MEMIF_ReqWriteBlock storing parameters...  \n");
            #endif
            /*stores the parameter in global variable to use it in main function*/
            gu8_DataPtr = DataPtr;
            gu8_BlockNum = au8_Counter;
            gu8_WriteBlockFlag = SET_BLOCK_FLAG; /*set write block flag*/
            gu8_MainFuncStatus = LOGIC_STATUS; /*change the main function status to logic status*/
        }
    }
    
    #if (ENABLE == TEST)
    printf("Function: MEMIF_ReqWriteBlock returns \n");
    #endif
    return au8_Return;
}

MEMIF_CheckType MEMIF_ReqReadBlock(unsigned char BlockId, unsigned char* DataPtr)
{
    MEMIF_CheckType au8_Return = MEMIF_OK;/*consider the return ok as initial value*/
    uint8_t au8_Counter,
            au8_LogicalBlockId;
    /*check if the pointer is null*/
    if (NULL == DataPtr)
    {
        au8_Return = MEMIF_NOK;
        #if (ENABLE == TEST)
        printf("Invalid Data Pointer \n");
        #endif
    }
    else
    {
        #if (ENABLE == TEST)
        printf("Valid Data Pointer \n");
        #endif
    }
            
     #if (ENABLE == TEST)
     printf("Searching about Block ID ... \n");
     #endif    
    
    for(au8_Counter = COUNTER_INITIAL_VALUE; au8_Counter < MEMIF_NUM_OF_BLOCKS; au8_Counter++)
    {
        au8_LogicalBlockId = MEMIF_ConfigParam.BlockConfigPtr[au8_Counter].LogicalBlockId;
        /*ensure that given block id exist*/
        if (BlockId == au8_LogicalBlockId)
        {
            break;
             #if (ENABLE == TEST)
             printf("Block Id %d exist number %d in Block Confg Array \n",BlockId, au8_Counter);
             #endif
        }
        
        if ( au8_Counter == (MEMIF_NUM_OF_BLOCKS - 1u) )
        {
            au8_Return = MEMIF_NOK;
            #if (ENABLE == TEST)
            printf("Block Id doesn't exist \n");
            #endif
        }
    }
    /*if the parameter is valid*/
    if (MEMIF_OK == au8_Return)
    {
         #if (ENABLE == TEST)
         printf("Function: MEMIF_ReqWriteBlock Parameters are valid \n");
         #endif
        /*ensure that the module is available*/
        if (IDLE_STATUS != gu8_MainFuncStatus)
        {
            au8_Return = MEMIF_BUSY;
             #if (ENABLE == TEST)
             printf("Function: MEMIF_ReqWriteBlock is Busy and can't execute now \n");
             #endif
        }
        
        else
        {
            #if (ENABLE == TEST)
            printf("Function: MEMIF_ReqWriteBlock storing parameters...  \n");
            #endif
            /*stores the parameter in global variable to use it in main function*/
            gu8_DataPtr = DataPtr;
            gu8_BlockNum = au8_Counter;
            gu8_READ_BLOCK_FLAG = SET_BLOCK_FLAG; /*set read block flag*/
            gu8_MainFuncStatus = LOGIC_STATUS; /*change the main function status to logic status*/
        }
    }
     #if (ENABLE == TEST)
     printf("Function: MEMIF_ReqWriteBlock returns \n");
     #endif
    return au8_Return;
}


void MEMIF_Main(void)
{
    #if (ENABLE == TEST)
    printf("Function: MEMIF_Main start \n");
    #endif
    uint8_t au8_StartAddress,
            au8_Length,
            au8_StorageType,
            au8_FuncReturn = EEINT_NOK; /*consider the return of called function is ok as initial value*/
            
    switch (gu8_MainFuncStatus)
    {
        case IDLE_STATUS:
        ;
        #if (ENABLE == TEST)
        printf("Function: MEMIF_Main in IDLE Status \n");
        #endif
        break;
        
        case LOGIC_STATUS:
        #if (ENABLE == TEST)
        printf("Function: MEMIF_Main in LOGICAL Status \n");
        #endif
        /*** get data from config structure ***/
        #if (ENABLE == TEST)
        printf("Function: MEMIF_Main storing Parameters ... \n");
        #endif
        au8_StartAddress = MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockNum].BlockPhyAddress;
        
        au8_Length = MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockNum].BlockLength;
        
        au8_StorageType = MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockNum].BlockStoragePlace;
        /*check if the desired operation is write operation*/
        if (SET_BLOCK_FLAG == gu8_WriteBlockFlag) 
        {
            #if (ENABLE == TEST)
            printf("Function: MEMIF_Main in IDLE Status, Write mode \n");
            #endif
            /*check if the operation occurs on external or internal EEPROM*/
            if (INTERNAL_MEM == au8_StorageType)
            {
                #if (ENABLE == TEST)
                printf("Function: MEMIF_Main writing in internal EEPROM ... \n");
                #endif
                /*write the desired data on internal EEPROM*/
                au8_FuncReturn = EEINT_ReqWrite(au8_StartAddress,gu8_DataPtr, au8_Length);
            } 
            
            else if (EXTERNAL_MEM == au8_StorageType)
            {
                #if (ENABLE == TEST)
                printf("Function: MEMIF_Main writing in external EEPROM ... \n");
                #endif
                /*write the desired data on external EEPROM*/
                au8_FuncReturn = EEEXT_ReqWrite(au8_StartAddress, gu8_DataPtr, au8_Length);
            }
            else
            {
                ;
                #if (ENABLE == TEST)
                printf("Function: MEMIF_Main Error in storage type !!! \n");
                #endif
            }
        } 
        /*check if the desired operation is read operation*/
        else if (SET_BLOCK_FLAG == gu8_READ_BLOCK_FLAG)
        {
            #if (ENABLE == TEST)
            printf("Function: MEMIF_Main in IDLE Status, Read mode \n");
            #endif
            /*check if the operation occurs on external or internal EEPROM*/
            if (INTERNAL_MEM == au8_StorageType)
            {
                #if (ENABLE == TEST)
                printf("Function: MEMIF_Main Reading from internal EEPROM \n");
                #endif
                /*read the desired data from internal EEPROM*/
                au8_FuncReturn = EEINT_ReqRead(au8_StartAddress, gu8_DataPtr, au8_Length);
				
            }
            else if (EXTERNAL_MEM == au8_StorageType)
            {
                #if (ENABLE == TEST)
                printf("Function: MEMIF_Main Reading from external EEPROM \n");
                #endif
                /*read the desired data from external EEPROM*/
                au8_FuncReturn = EEEXT_ReqRead(au8_StartAddress, gu8_DataPtr, au8_Length);
            }
            else
            {
                
                #if (ENABLE == TEST)
                printf("Function: MEMIF_Main Error in storage type !!! \n");
                #endif
            }
        }
        else
        {
           
            #if (ENABLE == TEST)
            printf("Function: MEMIF_Main Error in R/W operation mode !!! \n");
            #endif
        }
        
        if (  (EEINT_OK == au8_FuncReturn) || (EEEXT_OK == au8_FuncReturn) )
        {
            gu8_MainFuncStatus = WAIT_STATUS; /*move the status if the called function retrun ok*/
            #if (ENABLE == TEST)
            printf("Function: MEMIF_Main R/W operation Done \n");
            #endif
        }
        else
        {
            gu8_MainFuncStatus = LOGIC_STATUS;
            #if (ENABLE == TEST)
            printf("Function: MEMIF_Main R/W operation Failed !!! \n");
            #endif
        }
        break;
        
        case WAIT_STATUS:
        ;
        #if (ENABLE == TEST)
        printf("Function: MEMIF_Main in WAIT Status \n");
        printf("Function: MEMIF_Main waiting for R/W operation to Complete and return notification .... \n");
        #endif
        break;

        default:
        break;
    } 
    #if (ENABLE == TEST)
    printf("Function: MEMIF_Main Finished \n");
    #endif
          
}


void MEMIF_IntEepromWriteCbk(void)
{
    #if (ENABLE == TEST)
    printf("Function: MEMIF_IntEepromWriteCbk start \n");
    #endif
    /*reset the flags and notify the MEMIF*/
    gu8_WriteBlockFlag = CLEAR_BLOCK_FLAG;
    
    gu8_MainFuncStatus = IDLE_STATUS;
    
    #if (ENABLE == TEST)
    printf("Function: BlockWriteDoneNotif call \n");
    #endif
    MEMIF_ConfigParam.BlockWriteDoneNotif();
    
    #if (ENABLE == TEST)
    printf("Function: MEMIF_IntEepromWriteCbk finished \n");
    #endif
}

void MEMIF_IntEepromReadCbk(void)
{
    #if (ENABLE == TEST)
    printf("Function: MEMIF_IntEepromReadCbk start \n");
    #endif
    /*reset the flags and notify the MEMIF*/
    gu8_READ_BLOCK_FLAG = CLEAR_BLOCK_FLAG;
    
    gu8_MainFuncStatus = IDLE_STATUS;
    #if (ENABLE == TEST)
    printf("Function: BlockReadDoneNotif call \n");
    #endif
    MEMIF_ConfigParam.BlockReadDoneNotif();
    #if (ENABLE == TEST)
    printf("Function: MEMIF_IntEepromReadCbk finished \n");
    #endif
	
}

void MEMIF_ExtEepromWriteCbk(void)
{
    #if (ENABLE == TEST)
    printf("Function: MEMIF_ExtEepromWriteCbk start \n");
    #endif
    /*reset the flags and notify the MEMIF*/
    gu8_WriteBlockFlag = CLEAR_BLOCK_FLAG;
    
    gu8_MainFuncStatus = IDLE_STATUS;
    #if (ENABLE == TEST)
    printf("Function: BlockWriteDoneNotif call \n");
    #endif
    MEMIF_ConfigParam.BlockWriteDoneNotif();
    #if (ENABLE == TEST)
    printf("Function: MEMIF_ExtEepromWriteCbk finished \n");
    #endif
}

void MEMIF_ExtEepromReadCbk(void)
{
    #if (ENABLE == TEST)
    printf("Function: MEMIF_ExtEepromReadCbk start \n");
    #endif
    /*reset the flags and notify the MEMIF*/
    gu8_READ_BLOCK_FLAG = CLEAR_BLOCK_FLAG;
    
    gu8_MainFuncStatus = IDLE_STATUS;
    #if (ENABLE == TEST)
    printf("Function: BlockReadDoneNotif call \n");
    #endif
    MEMIF_ConfigParam.BlockReadDoneNotif();
    #if (ENABLE == TEST)
    printf("Function: MEMIF_ExtEepromReadCbk finished \n");
    #endif
}
