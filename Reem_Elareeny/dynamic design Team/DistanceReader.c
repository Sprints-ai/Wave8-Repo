/*
 * DistanceReader.c
 *
 * Created: 3/30/2020 7:50:09 PM
 *  Author: M.Ramadan
 */ 

#include "DistanceReader.h"
#include "../Infrastructure/Errors.h"
#include "../Infrastructure/registers.h" //debug

uint16_t Distptr;
/********************************************
*				Structure Definition        *
*********************************************/

DistanceReader_Cfg DistanceReader_Cfg_UltraSonic = {ULTRASONIC,&Distptr};

 /********************************************
 *			  Function Implementation        *
 *********************************************/
/**
 * Func			: DistanceReader_Init
 * Input		: NoInput
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful
 *
 * Description	: Initialize Distance Reader 
 */
extern ERROR_STATUS DistanceReader_Init(void){
	
	/***Local variable storing the error number of the function***/
	ERROR_STATUS Err_Status = E_OK;
	
	
	/**Initialize ultrasonic***/
	Err_Status = Us_Init();
			UDR = Err_Status;
	switch (Err_Status){
		case NULL_PTR1:
			Err_Status = NULL_PTR1;
			break;
		case MULTIPLES_INIYIALIZATION:
			Err_Status = MULTIPLES_INIYIALIZATION;
			break;			
		case INVALID_PARAMETERS:
			Err_Status = INVALID_PARAMETERS;
			break;
		case E_OK:
			Err_Status = E_OK;
			break;
		default:
			Err_Status = ERROR_MODULE_NOT_INITIALIZED;
			break;	
	}
	
	/***return the value of the error function**/
	return Err_Status;
}

/**
 * Func			: DistanceReader_GetValue
 * Input		: Pointer to a structure of type contains the Sensor_Version ,pointer to variable Distance Reader Value
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful
 *
 * Description	: call the ICU read function to get the value of the distance
 */
extern ERROR_STATUS DistanceReader_GetValue(uint16_t *u16_Distance)
{
	
	/***Local variable storing the error number of the function***/
	ERROR_STATUS Err_Status = E_OK;
	
	if(u16_Distance==NULL)
	{
		
		Err_Status = ERROR_NULL_POINTER;
	}
	else
	{
		
		Us_GetDistance(u16_Distance);
			
	}
	
	/***return the value of the error function**/
	return Err_Status;	
}