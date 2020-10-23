/*
 * EEPROM_EXT.c
 *
 * Created: 28/04/2020 23:51:42
 *  Author: sony
 */ 

/************************************************************************/
/*                           Includes                                   */
/************************************************************************/

#include "std_types.h"
#include "I2C.h"
#include "EEPROM_EXT.h"
#include "EEPROM_EXT_Cfg.h"

/*
 * Important external EEPROM macros
 */
#define EEEXT_ADDRESS         (0xA0)
#define EEEXT_NOT_AVAILABLE   (0u)
#define EEEXT_AVAILABLE       (1u)
#define EEEXT_READ_REQ        (1u)
#define EEEXT_WRITE_REQ       (0u)
#define MAIN_LOCK             (0u)
#define MAIN_UNLOCK           (1u)
#define DATA_FIRST_BYTE       (1u)
#define EEPROM_DATA           (129u)
#define FIRST_READ_STEP       (0u)
#define SECOND_READ_STEP      (1u)

/*
 * Important external EEPROM operation variables 
 */

/*External EEPROM availability variable*/
static unsigned char gu8_readWriteVar = 0;

/*External EEPROM availability variable*/
static unsigned char gu8_availableVar = 0;

/*External EEPROM pointer to the write data*/
static unsigned char gu8_writeDataArr[EEPROM_DATA] = {0};

/*External EEPROM write data length*/
static unsigned char gu8_writeLength = 0;

/*External EEPROM write start address*/
static unsigned char gu8_readStartAddress = 0;

/*External EEPROM pointer to the write data*/
static unsigned char* gu8_readDataPtr = NULL;

/*External EEPROM write data length*/
static unsigned char gu8_readLength = 0;

/*Locking variable for main function*/
static unsigned char gu8_mainLock = 0;

/*
 * External EEPROM functions' definitions 
 */
void EEEXT_Init(void)
{
    /*Initialization of I2C*/
    I2C_Init();
	
	/*External EEPROM is available*/
	gu8_availableVar = EEEXT_AVAILABLE;
	
	/*Lock the main function*/
	gu8_mainLock = MAIN_LOCK;
	
    return;
}
EEEXT_CheckType EEEXT_ReqWrite(unsigned char StartAddress, const unsigned char* DataPtr, unsigned char Length)
{
    /*External EEPROM error status variable*/
    EEEXT_CheckType EEEXT_errVar = EEEXT_OK;

    /*Parameters validation*/
    if( ((StartAddress+Length) > EEEXT_MAX_SIZE) || (DataPtr == NULL) || (Length > EEEXT_MAX_SIZE))
    {
        /*Pass NOK status if there's a parameter error*/
        EEEXT_errVar = EEEXT_NOK;
    }
    else if(gu8_availableVar == EEEXT_NOT_AVAILABLE)
    {
        /*Pass BUSY status if the EEPROM is in read or write operation*/
        EEEXT_errVar = EEEXT_BUSY;
    }
    else
    {
	   /*Variable used in looping operations*/
	   unsigned char au8_loopingVar = 0;
       
	   /*Passing the start address of EEPROM*/
	   gu8_writeDataArr[au8_loopingVar] = StartAddress;  
       
	   /*Passing the data of EEPROM*/
	   for(au8_loopingVar = DATA_FIRST_BYTE ; au8_loopingVar <= Length ; au8_loopingVar++)
	   {
		   gu8_writeDataArr[au8_loopingVar] = DataPtr[au8_loopingVar - DATA_FIRST_BYTE];   
	   }

	   /*Increase the length of the data*/
	   gu8_writeLength = Length + DATA_FIRST_BYTE;
	    
       /*Passing write request to the main function*/
       gu8_readWriteVar = EEEXT_WRITE_REQ;

       /*Setting the EEPROM to be unavailable*/
       gu8_availableVar = EEEXT_NOT_AVAILABLE;
	   
	   /*Unlock the main function*/
	   gu8_mainLock = MAIN_UNLOCK;
    }

    /*Return the error status*/
    return EEEXT_errVar;
}

EEEXT_CheckType EEEXT_ReqRead(unsigned char StartAddress,unsigned char* DataPtr,unsigned char Length)
{
    /*External EEPROM error status variable*/
    EEEXT_CheckType EEEXT_errVar = EEEXT_OK;

    /*Parameters validation*/
    if( ((StartAddress+Length) > EEEXT_MAX_SIZE) || (DataPtr == NULL) || (Length > EEEXT_MAX_SIZE))
    {
        /*Pass NOK status if there's a parameter error*/
        EEEXT_errVar = EEEXT_NOK;
    }
    else if(gu8_availableVar == EEEXT_NOT_AVAILABLE)
    {
        /*Pass BUSY status if the EEPROM is in read or write operation*/
        EEEXT_errVar = EEEXT_BUSY;
    }
    else
    {
       /*Passing the EEPROM parameters to be used in main function*/ 
       gu8_readStartAddress = StartAddress;
       gu8_readDataPtr = DataPtr;
       gu8_readLength = Length;

       /*Passing write request to the main function*/
       gu8_readWriteVar = EEEXT_READ_REQ;

       /*Setting the EEPROM to be unavailable*/
       gu8_availableVar = EEEXT_NOT_AVAILABLE;
	   
	   /*Unlock the main function*/
	   gu8_mainLock = MAIN_UNLOCK;
    }

    /*Return the error status*/
    return EEEXT_errVar;
}

void EEEXT_Main(void)
{
    /*Validating EEPROM is in operation or not*/
    if( (gu8_availableVar == EEEXT_NOT_AVAILABLE) && (gu8_mainLock == MAIN_UNLOCK) )
    {   
		/*Variable used in arrangement of reading steps*/
		static unsigned char au8_readSteps = 0;
		     		
        /*Switch between state machine steps*/
        switch(gu8_readWriteVar)
        {   
            /*Set the address of EEPROM step*/
            case EEEXT_WRITE_REQ:
				I2C_ReqWrite(EEEXT_ADDRESS, gu8_writeDataArr, gu8_writeLength);
				
				/*Lock the main function*/
				gu8_mainLock = MAIN_LOCK;
                break;

            /*Start reading or writing operation*/
            case EEEXT_READ_REQ:
				if(au8_readSteps == FIRST_READ_STEP)
				{
					/*Sending the address of EEPROM*/
					I2C_ReqWrite(EEEXT_ADDRESS, (const unsigned char*)&gu8_readStartAddress, DATA_FIRST_BYTE);
					au8_readSteps = SECOND_READ_STEP;
				} 
				else if (au8_readSteps == SECOND_READ_STEP)
				{
					/*Read the data of EEPROM*/
					I2C_ReqRead(EEEXT_ADDRESS, gu8_readDataPtr, gu8_readLength);
					
					/*Lock the main function*/
					gu8_mainLock = MAIN_LOCK;
					au8_readSteps = FIRST_READ_STEP;
				}
                break;
        }
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

void EEXT_ACtionDoneCallback(void)
{
	/*variable used in reading steps*/
	static unsigned char au8_readSteps = 0;
	switch(gu8_readWriteVar)
	{
		/*In writing operation*/
		case EEEXT_WRITE_REQ:
			/*Executing writing call back function*/
			EEXT_ConfigParam.WriteDoneCbkPtr();
			
			/*After writing finish enable the EEPROM*/
			gu8_availableVar = EEEXT_AVAILABLE;
			break;
		
		/*In reading operation*/
		case EEEXT_READ_REQ:
				if(au8_readSteps == FIRST_READ_STEP)
				{
					/*Move to the second step*/
					au8_readSteps = SECOND_READ_STEP;
				}
				else
				{
					/*Executing reading call back function*/
					EEXT_ConfigParam.ReadDoneCbkPtr();
					
					/*After reading finish enable the EEPROM*/
					gu8_availableVar = EEEXT_AVAILABLE;
					au8_readSteps = FIRST_READ_STEP;
				}
				break;
		
		default:
			/*Do nothing*/
			break;			
	}
	return;
}