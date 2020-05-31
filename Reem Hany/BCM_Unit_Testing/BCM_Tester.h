#ifndef _BCM_TESTER_H
#define _BCM_TESTER_H
#include "std_types.h"
#include <stdio.h>
#include "BCM.h"

#define RESULT_INITIAL_VALUE 5
#define ZERO 0;


uint8_t gu8_UartTransmitNotification;
uint8_t gu8_UartReceiveData;

void BCM_Init_Test (void);

void BCM_Send_Test (void);
void BCM_SetupRxBuffer_Test (void);
void BCM_RxUnlock_Test (void);
void BCM_GetTxBuffer_Test (void);

void NotificationMockPtrFunction(uint8_t);


#endif // _BCM_TESTER_H
