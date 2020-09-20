/*
 * EEPROM_INT.c
 *
 * Created: 28/04/2020 23:37:28
 *  Author: sony
 */ 

#include "EEPROM_INT_CFG.h"
#include "std_types.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#define  INITIALIZED    1
#define  UN_INITIALIZED 0 
#define  IDLE_STATE     0
#define  WRITE_STATE    1
#define  READ_STATE     2
#define  WRITING_STATE  3
#define  WRITEN_COMPLETE 4
#define  READ_COMPLETE   5
#define  READING_STATE   6
#define  FREE           0 
#define  BUSY           1
#define  DONE           1
#define  NOT_YET        0

static uint8_t gu8_initfalg;
static uint8_t gu8_stateflag;
static uint8_t gu8_buzyflag;
static uint8_t gu8_READCOMPLETED;
static unsigned char gu8_startadress;
static  unsigned char *gau8_DataPtr;
static unsigned char *gu8_readptr;
static unsigned char gu8_Length;

void EEINT_Init(void)
{
	/*set interrupt*/ 
	EECR|=(1<<EERIE);
	/*raise init_flag*/
	gu8_initfalg=INITIALIZED;
}

EEINT_CheckType EEINT_ReqWrite(unsigned char StartAddress,unsigned char* DataPtr,unsigned char Length)
{
EEINT_CheckType au8_errorstate=EEINT_OK;
	/*CHECK FOR  VOID POINTER AND MOODULE INITIALIZED*/
	if((DataPtr==NULL)||(gu8_initfalg==UN_INITIALIZED))
	{
		au8_errorstate=EEINT_NOK;
	}
	else
	{
		/*CHECK FOR VAILD ADRESS*/
		if((StartAddress+Length)>=EEINT_MAX_SIZE)
		{
			au8_errorstate=EEINT_NOK;
		}
		else
		{
			/*CHECK FOR AVAILBILITY*/	
			if(gu8_buzyflag==BUSY)
			{
				au8_errorstate=EEINT_BUSY;
			}
			else
			{
				/*SAVE THE DATA ,ADRESS AND LENGTH TO USE THEM IN MAIN_FUNC*/
				gu8_startadress=StartAddress;
				gau8_DataPtr=DataPtr;
				gu8_Length=Length;
			    /*CHANGE SM FOR WRITING STATE*/
				gu8_stateflag=WRITE_STATE;
				gu8_buzyflag=BUSY;
			}
		}
		
	}
return au8_errorstate;	
}

EEINT_CheckType EEINT_ReqRead(unsigned char StartAddress, unsigned char* DataPtr,unsigned char Length)
{
EEINT_CheckType au8_errorstate=EEINT_OK;
/*CHECK FOR  VOID POINTER AND MOODULE INITIALIZED*/
if((DataPtr==NULL)||(gu8_initfalg==UN_INITIALIZED))
{
	au8_errorstate=EEINT_NOK;
}
else
{
	/*CHECK FOR VAILD ADRESS*/
	if((StartAddress+Length)>=EEINT_MAX_SIZE)
	{
		au8_errorstate=EEINT_NOK;
	}
	else
	{
		/*CHECK FOR AVAILBILITY*/
		if(gu8_buzyflag==BUSY)
		{
			au8_errorstate=EEINT_BUSY;
		}
		else
		{
			/*SAVE THE DATA ,ADRESS AND LENGTH TO USE THEM IN MAIN_FUNC*/
			gu8_startadress=StartAddress;
			gu8_readptr=DataPtr;
			gu8_Length=Length;
			/*CHANGE SM FOR WRITING STATE*/
			gu8_stateflag=READ_STATE;
			gu8_buzyflag=BUSY;
		}
	}
	
}
return au8_errorstate;
}
void EEINT_Main(void)
{
	static uint8_t au8_writecounter=0;
	static  uint8_t au8_readcounter=0;
	
	
	switch(gu8_stateflag)
	{
		case IDLE_STATE:
				  gu8_buzyflag=FREE;
				 
				  break;
		case WRITE_STATE:
		     if(au8_writecounter==gu8_Length)
			 {
				 au8_writecounter=0;
				 gu8_stateflag=WRITEN_COMPLETE;
			 }
			 else
			 {
				 cli(); 
				 EEDR=gau8_DataPtr[au8_writecounter]; 
				 au8_writecounter++;
				 EEAR=gu8_startadress;
				 EECR &=~(1<<EEWE);
				 EECR |= (1<<EEMWE);
				 /* Write logical one to EEMWE */
				 /* Start eeprom write by setting EEWE */
				 EECR |= (1<<EEWE);
				 gu8_stateflag=WRITING_STATE;
				 sei();
			 }
		     break;
		case WRITING_STATE:
		     break;	 
	    case WRITEN_COMPLETE:
		     EEINT_ConfigParam.WriteDoneCbkPtr();
			 gu8_stateflag=IDLE_STATE;
			  break;
	    case READ_STATE:
		    
			if(au8_readcounter==gu8_Length)
			{
				au8_readcounter=0;
				gu8_stateflag=READ_COMPLETE;
			}
			else
			{
				EEAR=gu8_startadress;
				EECR &=~(1<<EEMWE);
				EECR &=~(1<<EEWE);
				EECR |=(1<<EERE);		
				gu8_stateflag=READING_STATE;
			}
			break;
	   case READING_STATE:      
	        if(gu8_READCOMPLETED==DONE)
			{
				gu8_READCOMPLETED=NOT_YET;
				au8_readcounter++;
				gu8_stateflag=READ_STATE;
			}
			break;
     case  READ_COMPLETE:
			EEINT_ConfigParam.ReadDoneCbkPtr();
			gu8_stateflag=IDLE_STATE;
			break;
	    	  
	}
}
 ISR(EE_RDY_vect)
{
	if((gu8_stateflag==WRITING_STATE)||(gu8_stateflag==WRITE_STATE))
	{
		gu8_stateflag=WRITE_STATE;
	}
	else if(gu8_stateflag==READING_STATE)
	{ 
		*gu8_readptr=EEDR;
		gu8_READCOMPLETED=DONE;	
	}
	
}