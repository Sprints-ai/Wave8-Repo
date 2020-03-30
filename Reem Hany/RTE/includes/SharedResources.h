/*
 * SharedResources.h
 *
 * Created: 3/30/2020 12:44:57 PM
 *  Author: Reem
 */ 


#ifndef SHAREDRESOURCES_H_
#define SHAREDRESOURCES_H_

#include "../../Services/includes/std_types.h"
extern void SharedRes_Init(void);
extern void SharedRes_setDistanceVal(uint16_t Distance);
extern void SharedRes_getDistanceVal(uint16_t * Distance);



#endif /* SHAREDRESOURCES_H_ */