/*
 * EEPROM_EXT.c
 *
 * Created: 28/04/2020 23:51:42
 *  Author: sony
 */ 
#define ENABLE         1
#define DISABLE        0
#define TEST           DISABLE
/*******************************************************************
 *--------------------------- INCLUDES ----------------------------*
 *******************************************************************/
#include "EEPROM_EXT.h"
#include "EEPROM_EXT_Cfg.h"
#include "I2C.h"
#if (TEST == ENABLE)
#include <stdio.h>
#endif
/*******************************************************************
 *------------------------- LOCLA MACROS --------------------------*
 *******************************************************************/
#define TOTAL_DATA_SIZE_INITIAL_VALUE    EEEXT_MAX_SIZE + 5u
#define LENGTH_INITIAL_VALUE             0u
#define PHY_ADDRESS_INITAIAL_VALUE       200u
#define EXTERNAL_EEPROM_ADDRESS          0xA0u
#define PHY_ADDRESS_LENGTH               1u
/*operation flag values*/
#define OPERATION_FLAG_READ              6u
#define OPERATION_FLAG_WRITE             7u
#define OPERATION_FLAG_CLEAR             8u
/*wait flag value*/
#define WAIT_FLAG_CONFG                  20u
#define WAIT_FLAG_OPERATION              21u
#define WAIT_FLAG_CLEAR                  22u
/*main function status*/
#define IDLE_STATUS                      10u
#define READ_STATUS                      11u
#define WRITE_STATUS                     12u
#define WAIT_OPERATION_STATUS             13u
#define CONFG_STATUS                     14u
#define WAIT_CONFIG_STATUS               15u

/*******************************************************************
 *----------------------- GLOBAL VARIABLES ------------------------*
 *******************************************************************/
static uint8_t gu8_PhyAddress;
static uint8_t gu8_Length;
static const uint8_t* gu8ptr_DataPtr;

static uint8_t gu8_OperationFlag;
static uint8_t gu8_WaitFlag;

/*******************************************************************
 *---------------------- API IMPLEMENTATIONS ----------------------*
 *******************************************************************/
void EEEXT_Init(void)
{
    #if (ENABLE == TEST)
    printf("Function: EEEXT_Init start \n");
    #endif
    /*initiate globla variables*/
    gu8_PhyAddress = PHY_ADDRESS_INITAIAL_VALUE; /*value out of scope to generate error*/
    gu8_Length = LENGTH_INITIAL_VALUE; /*value out of scope to generate error*/
    gu8ptr_DataPtr = NULL; /*null pointer*/

    gu8_OperationFlag = OPERATION_FLAG_CLEAR;
    gu8_WaitFlag = WAIT_FLAG_CLEAR;
    #if (ENABLE == TEST)
    printf("Function: EEEXT_Init finished \n");
    #endif
}

EEEXT_CheckType EEEXT_ReqWrite(unsigned char StartAddress, const unsigned char* DataPtr, unsigned char Length)
{
    #if (ENABLE == TEST)
    printf("Function: EEEXT_ReqWrite start \n");
    #endif
    EEEXT_CheckType FuncReturn = EEEXT_OK; /*consider the return ok as initial value*/ 
    uint8_t au8_TotalDatasize = TOTAL_DATA_SIZE_INITIAL_VALUE; /*value out of scope to gereate error*/
    
    /*check if the pointer is null*/
    if (NULL == DataPtr) 
    {
        FuncReturn = EEEXT_NOK;
        #if (ENABLE == TEST)
        printf("Invalid Data pointer \n");
        #endif
    }
    else
    {
        ;
        #if (ENABLE == TEST)
        printf("Valid Data Pointer \n");
        #endif
    }
    
    /*calculate total data size*/
    au8_TotalDatasize = StartAddress * Length;
    #if (ENABLE == TEST)
    printf("Total Data Size is %d \n", au8_TotalDatasize);
    #endif
    /*make sure that total data size fit with external EEPROM size*/
    if (EEEXT_MAX_SIZE < au8_TotalDatasize)
    {
        FuncReturn = EEEXT_NOK;
        #if (ENABLE == TEST)
        printf("Invalid Data Size \n");
        #endif
    }
    
    /*if the parameter is valid*/
    if (EEEXT_OK == FuncReturn)
    {
        #if (ENABLE == TEST)
        printf("Valid Data Size \n");
        #endif
        /*ensure that the module is available*/
        if (OPERATION_FLAG_CLEAR == gu8_OperationFlag)
        {
            #if (ENABLE == TEST)
            printf("Function: EEEXT_ReqWrite storing parameters ... \n");
            #endif
            /*stores the parameter in global variable to use it in main function*/
            gu8_Length = Length;
            gu8_PhyAddress = StartAddress;
            gu8ptr_DataPtr = DataPtr;
            /*stores required operation*/
            gu8_OperationFlag = OPERATION_FLAG_WRITE;
        } 
        /*if the module unavailable*/
        else
        {
            FuncReturn = EEEXT_BUSY;
            #if (ENABLE == TEST)
            printf("Function: EEEXT_ReqWrite is BUSY \n");
            #endif
        }
    }
    #if (ENABLE == TEST)
    printf("Function: EEEXT_ReqWrite finished \n");
    #endif
    return FuncReturn;
}


EEEXT_CheckType EEEXT_ReqRead(unsigned char StartAddress,const unsigned char* DataPtr,unsigned char Length)
{
    #if (ENABLE == TEST)
    printf("Function: EEEXT_ReqRead start \n");
    #endif
    EEEXT_CheckType FuncReturn = EEEXT_OK; /*consider the return ok as initial value*/
    uint8_t au8_TotalDatasize = TOTAL_DATA_SIZE_INITIAL_VALUE; /*value out of scope to gereate error*/
    /*check if the pointer is null*/
    if (NULL == DataPtr)
    {
        FuncReturn = EEEXT_NOK;
        #if (ENABLE == TEST)
        printf("Invalid Data pointer \n");
        #endif
    }
    else
    {
        ;
        #if (ENABLE == TEST)
        printf("Valid Data Pointer \n");
        #endif
    }
    
    /*calculate total data size*/
    au8_TotalDatasize = StartAddress * Length;
    #if (ENABLE == TEST)
    printf("Total Data Size is %d \n", au8_TotalDatasize);
    #endif
    
    /*make sure that total data size fit with external EEPROM size*/
    if (EEEXT_MAX_SIZE < au8_TotalDatasize)
    {
        FuncReturn = EEEXT_NOK;
        #if (ENABLE == TEST)
        printf("Invalid Data Size \n");
        #endif
    }
    
    /*check if the parameter is valid*/
    if (EEEXT_OK == FuncReturn)
    {
        #if (ENABLE == TEST)
        printf("Valid Data Size \n");
        #endif
        /*ensure that the module is available*/
       if (OPERATION_FLAG_CLEAR == gu8_OperationFlag)
       {
           #if (ENABLE == TEST)
           printf("Function: EEEXT_ReqRead storing parameters ... \n");
           #endif
           /*stores the parameter in global variable to use it in main function*/
           gu8_Length = Length;
           gu8_PhyAddress = StartAddress;
           gu8ptr_DataPtr = DataPtr;
           /*stores required operation*/
           gu8_OperationFlag = OPERATION_FLAG_READ;
       } 
       /*if the module unavailable*/
       else
       {
           FuncReturn = EEEXT_BUSY;
           #if (ENABLE == TEST)
           printf("Function: EEEXT_ReqRead is BUSY \n");
           #endif
       }
    }
    #if (ENABLE == TEST)
    printf("Function: EEEXT_ReqRead finished \n");
    #endif
    return FuncReturn;
}



void EEEXT_Main(void)
{
    #if (ENABLE == TEST)
    printf("Function: EEEXT_Main start \n");
    #endif
    I2C_CheckType I2C_Return = I2C_OK; /*consider the return of called function is ok as initial value*/
    static uint8_t gu8_MainFuncStatus = IDLE_STATUS; /*begain the function from idle state*/
    
    switch(gu8_MainFuncStatus)
    {
        case IDLE_STATUS:
        #if (ENABLE == TEST)
        printf("Function: EEEXT_Main in IDLE Status \n");
        #endif
        /*check if there is a required operation or not*/
        if (OPERATION_FLAG_CLEAR != gu8_OperationFlag)
        {
            gu8_MainFuncStatus = CONFG_STATUS; /*if there is operation move the state to config*/
        }  
        else
        {
            gu8_MainFuncStatus = IDLE_STATUS;
        }
        break;
        /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         */
        case CONFG_STATUS:
        #if (ENABLE == TEST)
        printf("Function: EEEXT_Main in CONFG Status \n");
        #endif
        /*Configure the EEPROM by sending the required address to read from or write to*/
        #if (ENABLE == TEST)
        printf("Function: EEEXT_Main write start address in EEPROM ... \n");
        #endif
        I2C_Return = I2C_ReqWrite(EXTERNAL_EEPROM_ADDRESS, &gu8_PhyAddress, PHY_ADDRESS_LENGTH);
        if (I2C_OK == I2C_Return)
        {
            gu8_MainFuncStatus = WAIT_CONFIG_STATUS; /*move the status if the call occurs correctly*/
            #if (ENABLE == TEST)
            printf("Start address write function executed and Status change to WAIT CONFIG \n");
            #endif
        }
        else
        {
            gu8_MainFuncStatus = CONFG_STATUS;
            #if (ENABLE == TEST)
            printf("Start address wrote operation Failed \n");
            #endif
        }
        break;
        /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         */
        case WAIT_CONFIG_STATUS:
        #if (ENABLE == TEST)
        printf("Function: EEEXT_Main in WAIT CONFG Status \n");
        #endif
        /*wait until EEPROM configure correctly*/
        if (WAIT_FLAG_CONFG == gu8_WaitFlag)
        {
            #if (ENABLE == TEST)
            printf("Start Address Write operation Finished \n");
            #endif
            /*move the status according to the desired operation (R/W)*/
            if (OPERATION_FLAG_READ == gu8_OperationFlag)
            {
                gu8_MainFuncStatus = READ_STATUS;
                #if (ENABLE == TEST)
                printf("Function: EEEXT_Main status change to READ Status \n");
                #endif 
            } 
            else if (OPERATION_FLAG_WRITE == gu8_OperationFlag)
            {
                gu8_MainFuncStatus = WRITE_STATUS;
                #if (ENABLE == TEST)
                printf("Function: EEEXT_Main status change to WRITE Status \n");
                #endif
            }
            else
            {
                ;
                #if (ENABLE == TEST)
                printf("Function: EEEXT_Main Error in changing Status !!! \n");
                #endif
            }                
        } 
        else
        {
            gu8_MainFuncStatus = WAIT_CONFIG_STATUS;
            #if (ENABLE == TEST)
            printf("Start Address Write operation still executing \n");
            #endif
        }
        break;
        /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         */
        case READ_STATUS:
        #if (ENABLE == TEST)
        printf("Function: EEEXT_Main in READ Status \n");
        #endif
        /*read data from external EEPROM through I2C*/
        #if (ENABLE == TEST)
        printf("Function: EEEXT_Main Reading from I2C ... \n");
        #endif
        I2C_Return = I2C_ReqRead(EXTERNAL_EEPROM_ADDRESS, gu8ptr_DataPtr, gu8_Length);
        if (I2C_OK == I2C_Return)
        {
            gu8_MainFuncStatus = WAIT_OPERATION_STATUS; /*move the status if the read occurred*/
            #if (ENABLE == TEST)
            printf("Function: EEEXT_Main change status to WAIT OPERATION Status \n");
            #endif
        }
        else
        {
            gu8_MainFuncStatus = READ_STATUS;
            #if (ENABLE == TEST)
            printf("Reading operation Failed and will Repeated !!! \n");
            #endif
        }
        break;
        /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         */
        case WRITE_STATUS:
        #if (ENABLE == TEST)
        printf("Function: EEEXT_Main in WRITE Status \n");
        #endif
        /*write data from external EEPROM through I2C*/
        #if (ENABLE == TEST)
        printf("Function: EEEXT_Main Writing through I2C ... \n");
        #endif
        I2C_Return = I2C_ReqWrite(EXTERNAL_EEPROM_ADDRESS, gu8ptr_DataPtr, gu8_Length);
        if (I2C_OK == I2C_Return)
        {
            gu8_MainFuncStatus = WAIT_OPERATION_STATUS; /*move the status if the write occurred*/
            #if (ENABLE == TEST)
            printf("Function: EEEXT_Main change status to WAIT OPERATION Status \n");
            #endif
        }
        else
        {
            gu8_MainFuncStatus = WRITE_STATUS;
            #if (ENABLE == TEST)
            printf("writing operation Failed and will Repeated !!! \n");
            #endif
        }
        break;
        /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         */
        case WAIT_OPERATION_STATUS:
        #if (ENABLE == TEST)
        printf("Function: EEEXT_Main in WAIT OPERATION Status \n");
        #endif
        /*wait until the operation complete*/
        if (WAIT_FLAG_OPERATION == gu8_WaitFlag)
        {
            #if (ENABLE == TEST)
            printf("Desired Operation Finished \n");
            printf("Reset Flags \n");
            #endif
            
            /*configure the variables to new operation*/
            gu8_MainFuncStatus = IDLE_STATUS;
            gu8_WaitFlag = WAIT_FLAG_CLEAR;
            /*notify the memory interface that operation is done*/
            if (OPERATION_FLAG_READ == gu8_OperationFlag)
            {
                #if (ENABLE == TEST)
                printf("Call ReadDoneCbkPtr function \n");
                #endif
                EEXT_ConfigParam.ReadDoneCbkPtr();
            } 
            else if (OPERATION_FLAG_WRITE == gu8_OperationFlag)
            {
                #if (ENABLE == TEST)
                printf("Call WriteDoneCbkPtr function \n");
                #endif
                EEXT_ConfigParam.WriteDoneCbkPtr();
            }
            else
            {
                ;
                #if (ENABLE == TEST)
                printf("Operation Flag Value invalid \n");
                #endif
                
            }
            gu8_OperationFlag = OPERATION_FLAG_CLEAR;
        } 
        else
        {
            gu8_MainFuncStatus = WAIT_OPERATION_STATUS;
            #if (ENABLE == TEST)
            printf("Desired Operation still executing ... \n");
            #endif
        }
        break;
        /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         *>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         */
        default:
        break;
    }
    #if (ENABLE == TEST)
    printf("Function: EEEXT_Main Finished \n");
    #endif
}


void EEXT_ACtionDoneCallback(void)
{
    #if (ENABLE == TEST)
    printf("Function: EEXT_ACtionDoneCallback start \n");
    #endif
    if (WAIT_FLAG_CLEAR == gu8_WaitFlag)
    {
        /*change the flag status when EEPROM confg complete*/
        gu8_WaitFlag = WAIT_FLAG_CONFG;
        #if (ENABLE == TEST)
        printf("Wait Flag changed to CONFIG \n");
        #endif
    }
    else if (WAIT_FLAG_CONFG == gu8_WaitFlag)
    {
        /*change the flag status when the operation complete*/
        gu8_WaitFlag = WAIT_FLAG_OPERATION;
        #if (ENABLE == TEST)
        printf("Wait Flag changed to OPERATION \n");
        #endif
    }
    else
    {
        #if (ENABLE == TEST)
        printf("Wait Flag Error \n");
        #endif
        ;
    }
    #if (ENABLE == TEST)
    printf("Function: EEXT_ACtionDoneCallback Finished \n");
    #endif
}
