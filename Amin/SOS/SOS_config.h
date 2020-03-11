#ifndef SOS_CONFIG_H_
#define SOS_CONFIG_H_

#include "std_types.h"

typedef struct{
	uint8 Timer_ID;
	uint32 System_Tick;
}OS_ConfigType;

#define Tasks_NUM 5

#endif /* SOS_CONFIG_H_ */
