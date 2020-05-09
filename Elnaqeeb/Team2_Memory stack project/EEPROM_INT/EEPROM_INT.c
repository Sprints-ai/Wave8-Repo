/*
 * EEPROM_INT.c
 *
 * Created: 28/04/2020 23:37:28
 *  Author: sony
 */ 

/*Includes*/
#include "EEPROM_INT.h"
#include "EEPROM_INT_CFG.h"

/*
 * Internal EEPROM important macros 
 */
#define NULL                  ((void*)0)
#define EEINT_AVAILABLE       (1u)
#define EEINT_NOT_AVAILABLE   (0u)
#define EEINT_READ_REQ        (1u)
#define EEINT_WRITE_REQ       (0u)
#define EEINT_SET_ADDRESS     (0u)
#define EEINT_START_OPERATION (1u)

/*Important register bits*/
#define SPMCR_SPMEN_BIT       (0)
#define EECR_EERE_BIT         (0)
#define EECR_EEWE_BIT         (1)
#define EECR_EEMWE_BIT        (2)
#define GLOBAL_INT_BIT        (7)

/*
 * Important internal EEPROM operation variables 
 */

/*Internal EEPROM availability variable*/
static unsigned char gu8_readWriteVar = 0;

/*Internal EEPROM availability variable*/
static unsigned char gu8_availableVar = 0;

/*Internal EEPROM state machine variable*/
static unsigned char gu8_stateMachineVar = 0;

/*Internal EEPROM write start address*/
static unsigned char gu8_writeStartAddress = 0;

/*Internal EEPROM pointer to the write data*/
static const unsigned char* gu8_writeDataPtr = NULL;

/*Internal EEPROM write data length*/
static unsigned char gu8_writeLength = 0;

/*Internal EEPROM write start address*/
static unsigned char gu8_readStartAddress = 0;

/*Internal EEPROM pointer to the write data*/
static unsigned char* gu8_readDataPtr = NULL;

/*Internal EEPROM write data length*/
static unsigned char gu8_readLength = 0;

/*Internal EEPROM Functions' definitions*/
void EEINT_Init(void)
{
    /*Setting the availability of EEPROM and its state machine*/
    gu8_availableVar = EEINT_AVAILABLE;
    gu8_stateMachineVar = EEINT_SET_ADDRESS;
    return;
}

EEINT_CheckType EEINT_ReqWrite(unsigned char StartAddress, const unsigned char* DataPtr, unsigned char Length)
{
    /*Internal EEPROM error status variable*/
    EEINT_CheckType EEINT_errVar = EEINT_OK;
    
    /*Parameters validation*/
    if( ((StartAddress+Length) > EEINT_MAX_SIZE) || (DataPtr == NULL) || (Length > EEINT_MAX_SIZE))
    {
        /*Pass NOK status if there's a parameter error*/
        EEINT_errVar = EEINT_NOK;
    }
    else if(gu8_availableVar == EEINT_NOT_AVAILABLE)
    {
        /*Pass BUSY status if the EEPROM is in read or write operation*/
        EEINT_errVar = EEINT_BUSY;
    }
    else
    {
       /*Passing the EEPROM parameters to be used in main function*/ 
       gu8_writeStartAddress = StartAddress;
       gu8_writeDataPtr = DataPtr;
       gu8_writeLength = Length;

       /*Passing write request to the main function*/
       gu8_readWriteVar = EEINT_WRITE_REQ;

       /*Setting the EEPROM to be unavailable*/
       gu8_availableVar = EEINT_NOT_AVAILABLE;

       /*Start the first step in EEPROM state machine*/
       gu8_stateMachineVar = EEINT_SET_ADDRESS; 
    }
    
    return EEINT_errVar;
}

EEINT_CheckType EEINT_ReqRead(unsigned char StartAddress,unsigned char* DataPtr,unsigned char Length)
{
    /*Internal EEPROM error status variable*/
    EEINT_CheckType EEINT_errVar = EEINT_OK;

    if( ((StartAddress+Length) > EEINT_MAX_SIZE) || (DataPtr == NULL) || (Length > EEINT_MAX_SIZE))
    {
        /*Pass NOK status if there's a parameter error*/
        EEINT_errVar = EEINT_NOK;
    }
    else if(gu8_availableVar == EEINT_NOT_AVAILABLE)
    {
        /*Pass BUSY status if the EEPROM is in read or write operation*/
        EEINT_errVar = EEINT_BUSY;
    }
    else
    {
       /*Passing the EEPROM parameters to be used in main function*/ 
       gu8_readStartAddress = StartAddress;
       gu8_readDataPtr = DataPtr;
       gu8_readLength = Length;

       /*Passing read request to the main function*/
       gu8_readWriteVar = EEINT_READ_REQ;

       /*Setting the EEPROM to be unavailable*/
       gu8_availableVar = EEINT_NOT_AVAILABLE; 
      
       /*Start the first step in EEPROM state machine*/
       gu8_stateMachineVar = EEINT_SET_ADDRESS; 
    }
    
    /*Return the error status*/
    return EEINT_errVar;
}

void EEINT_Main(void)
{
    /*Validating EEPROM is in operation or not*/
    if(gu8_availableVar == EEINT_NOT_AVAILABLE)
    {
        /*Variable used in looping operations*/
        unsigned char au8_loopingVar = 0;
        
        /*Switch between state machine steps*/
        switch(gu8_stateMachineVar)
        {   
            /*Set the address of EEPROM step*/
            case EEINT_SET_ADDRESS:
				if(gu8_readWriteVar == EEINT_WRITE_REQ)
                {
                    /*Set the write address*/
                    EEARL = gu8_writeStartAddress;
                }
                else if(gu8_readWriteVar == EEINT_READ_REQ)
                {
                    /*Set the read address*/
                    EEARL = gu8_readStartAddress; 
                }
                else
                {
                    /*Do nothing*/
                }
                
                /*Go to the next state*/
                gu8_stateMachineVar = EEINT_START_OPERATION;
                break;

            /*Start reading or writing operation*/
            case EEINT_START_OPERATION:
				if(gu8_readWriteVar == EEINT_WRITE_REQ)
                {
                    /*Setting the looping to zero and start looping over data*/
                    au8_loopingVar = 0;
                    while(au8_loopingVar < gu8_writeLength)
                    {
                        /*Wait for memory writing operations to be done*/
                        while(GET_BIT(SPMCR , SPMCR_SPMEN_BIT));
                        while(GET_BIT(EECR ,  EECR_EEWE_BIT));

                        /*Pass the data to EEDR register*/
                        EEDR = gu8_writeDataPtr[au8_loopingVar];
                        
                        /*Disable the global interrupts to write the data over EEPROM*/
                        CLEAR_BIT(SREG , GLOBAL_INT_BIT);

                        /*Enable the write operation*/
                        EECR = (1 << EECR_EEMWE_BIT);
                        EECR |= (1 << EECR_EEWE_BIT);

                        /*Enable the global interrupts*/
                        SET_BIT(SREG , GLOBAL_INT_BIT);
                        
                        /*increase the address register by one*/
                        EEARL++;

                        /*Go to the next data byte*/
                        au8_loopingVar++;    
                    }
                }
                else if(gu8_readWriteVar == EEINT_READ_REQ)
                {
                    /*Setting the looping to zero and start looping over data*/
                    au8_loopingVar = 0;
                    while(au8_loopingVar < gu8_readLength)
                    {
                        /*Wait if there's a writing operation*/
                        while(GET_BIT(EECR ,  EECR_EEWE_BIT));
                        
                        /*Enable the read operation*/
                        EECR = (1 << EECR_EERE_BIT);

                        /*Get the data of the EEPROM*/
                        gu8_readDataPtr[au8_loopingVar] = EEDR;
                        
                        /*increase the address register by one*/
                        EEARL++;

                        /*Go the next data byte*/
                        au8_loopingVar++;    
                    }
                }
                else
                {
                    /*Do nothing*/
                }

                /*The EEPROM becomes available*/
                gu8_availableVar = EEINT_AVAILABLE;
                break;
        }
    }
    else
    {
        /*Do nothing*/
    }
    
    return;
}