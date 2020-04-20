/*
 * BCM_LCfg.h
 *
 * Created: 3/2/2020 1:25:47 PM
 *  Author: ahmed
 */ 


#ifndef BCM_LCFG_H_
#define BCM_LCFG_H_


#include "BCM.h"

typedef struct strBCM_Config_t
{
	uint8_t u8_SerialComType;
	uint8_t u8_SenderOrReceiver;
	
	
}strBCM_Config_t;

extern strBCM_Config_t BCM_Config;

#endif /* BCM_LCFG_H_ */