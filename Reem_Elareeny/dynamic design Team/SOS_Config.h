/*
 * SOS_Config.h
 *
 * Created: 2/25/2020 11:31:04 AM
 *  Author: Ehab & Reem
 */ 


#ifndef SOS_CONFIG_H_
#define SOS_CONFIG_H_

#include "SOS.h"

#define BUFFER_SIZE		50


typedef struct SOS_ConfigType
{
	uint8_t Timer_Channel;
	
}SOS_ConfigType;

extern SOS_ConfigType SOS_Config;

#endif /* SOS_CONFIG_H_ */