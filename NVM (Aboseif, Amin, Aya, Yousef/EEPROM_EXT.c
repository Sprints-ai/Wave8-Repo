/*
 * EEPROM_EXT.c
 *
 * Created: 28/04/2020 23:51:42
 *  Author: sony
 */ 
 
 /*******Includes************/
#include "EEPROM_EXT.h"
#include "EEPROM_EXT_Cfg.h"
#include "I2C.h"

/********Macros**************/
#define EEPROM_NOT_INITIALIZED 0
#define EEPROM_INITIALIZED 1
#define READ_STATE 3
#define WRITE_STATE 4
#define EEPROM_NOT_READY 5
#define EEPROM_READY 6
#define INIT_DONE 7
#define Wait_new_Operation 8
#define NULL	((void *)0)
#define NEW_DATA_TO_PROCESS 9
#define OLD 10

/***********Global Variables************/
/*This is for further check of eeprom current state in eeprom main function */
unsigned char Eeprom_Current_State=EEPROM_NOT_INITIALIZED;
unsigned char Eeprom_Address;
const unsigned char* gu8ptr_COPY_DataPtr;
unsigned char gu8Length;
unsigned char Init_for_once;
unsigned char CBK;

void EEPROM_Init(void)
{
	/*set global variable for further check in main fun to init the i2c */
	Eeprom_Current_State=EEPROM_INITIALIZED;
}

EEEXT_CheckType EEINT_ReqWrite(unsigned char StartAddress, const unsigned char* DataPtr, unsigned char Length){
	
	EEEXT_CheckType Function_Return_State=EEEXT_OK;
	 if (DataPtr!=NULL&&(StartAddress+Length)<EEEXT_MAX_SIZE)
	 {
		if(Eeprom_Current_State==EEPROM_INITIALIZED)
		{
		/* save the parameters in global variables to be used in main function*/
		Eeprom_Current_State=WRITE_STATE;	
		Eeprom_Address=StartAddress;
		gu8ptr_COPY_DataPtr=DataPtr;
		gu8Length=Length;
		}
		else{
			Function_Return_State=EEEXT_BUSY;
		}
	 }else{
		 Function_Return_State=EEEXT_NOK;
	 }
	 
	return Function_Return_State;	
}

EEEXT_CheckType EEEXT_ReqRead(unsigned char StartAddress,unsigned char* DataPtr,unsigned char Length){
	
	EEEXT_CheckType Function_Return_State=EEEXT_OK;
	if (DataPtr!=NULL&&(StartAddress+Length)<EEEXT_MAX_SIZE)
	 {
		if(Eeprom_Current_State==EEPROM_INITIALIZED)
		{
		/* save the parameters in global variables to be used in main function*/
		Eeprom_Current_State=READ_STATE;	
		Eeprom_Address=StartAddress;
		gu8ptr_COPY_DataPtr=DataPtr;
		gu8Length=Length;
		}
		else{
			Function_Return_State=EEEXT_BUSY;
		}
	 }else{
		 Function_Return_State=EEEXT_NOK;
	 }
	 
	return Function_Return_State;	
}

void EEEXT_Main(void){
	 I2C_CheckType I2C_Function_Return = I2C_OK;
	 
	switch(Eeprom_Current_State){
		case EEPROM_INITIALIZED:
		/*use this check to initialize the i2c for only once by changing state of global variable */
		if(Init_for_once==0)
		{
			Init_for_once=INIT_DONE;
			I2C_Init();
		}
		break;
		
		case WRITE_STATE:
		I2C_Function_Return = I2C_ReqWrite(Eeprom_Address,gu8ptr_COPY_DataPtr,gu8Length);
		if(I2C_Function_Return==I2C_OK&&CBK==NEW_DATA_TO_PROCESS){
			Eeprom_Current_State=Wait_new_Operation;
			CBK=OLD;
			/*if writing operation is failed repeat the it*/
		}else{
			Eeprom_Current_State=WRITE_STATE;
		}
		break;
		
		case READ_STATE:
		I2C_Function_Return =I2C_ReqRead(Eeprom_Address,gu8ptr_COPY_DataPtr,gu8Length);
		if(I2C_Function_Return==I2C_OK&&CBK==NEW_DATA_TO_PROCESS){
			Eeprom_Current_State=Wait_new_Operation;
			CBK=OLD;
			/*if reading operation is failed repeat the it*/
		}else{
			Eeprom_Current_State=READ_STATE;
		}
		break;
		
		default:
        break;
	}
	
}

void EEXT_ACtionDoneCallback(void){
	
	CBK=NEW_DATA_TO_PROCESS;
}