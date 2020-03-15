#ifndef SOS_H_
#define SOS_H_

#include "SOS_config.h"
#include "Timer.h"

typedef void(*ptrToFunction)(void);

#define DELETED 0
#define WAITING   1
#define READY  2

typedef enum{
	FAILED,SUCCEED
}EnmOSError_t;


typedef struct{
	uint32 periodicity;
	uint16 priority;
	void (*g_function)(void);
	uint8 state;
	uint32 task_counter;
}Task_ConfigType;

Task_ConfigType Task_Config_arr[Tasks_NUM];



 EnmOSError_t SOS_Init (const OS_ConfigType * ConfigPtr);
 void SOS_Run(void);
EnmOSError_t SOS_Create_Task(uint32 periodicity,uint16 priority,ptrToFunction FuncName);
EnmOSError_t SOS_Delete_Task(ptrToFunction FuncName);
 void SOS_cal(void);

#endif /* SOS_H_ */
