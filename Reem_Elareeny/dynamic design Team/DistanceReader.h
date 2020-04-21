/*
 * DistanceReader.h
 *
 * Created: 3/30/2020 7:30:01 PM
 *  Author: M.Ramadan
 */ 


#ifndef DISTANCEREADER_H_
#define DISTANCEREADER_H_





#include "../ECUAL/US.h"
#include "DistanceReader_config.h"

 /*********************************************
 *	  	   Function prototypes				 *
 ********************************************/
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
extern ERROR_STATUS DistanceReader_Init(void);
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
extern ERROR_STATUS DistanceReader_GetValue(uint16_t *u16_Distance);

#endif /* DISPLAYER_H_ */