/*
 * SOS_Config.h
 *
 * Created: 3/10/2020 5:34:41 PM
 *  Author: Reem el-Areeny
 */ 


#ifndef SOS_CONFIG_H_
#define SOS_CONFIG_H_

#include "SOS.h"

/************************************************************************/
/*								  Structures Definition 	                     */
/************************************************************************/
typedef struct SOS_ConfigType
{
	uint8_t Timer_Channel;
	
}SOS_ConfigType;


//review:should include the extern here: extern SOS_ConfigType SOS_Config;

#endif /* SOS_CONFIG_H_ */