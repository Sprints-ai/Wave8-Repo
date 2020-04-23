#ifndef TMU_H_
#define TMU_H_

#include "Timer.h"
#include "TMU_confg.h"

#define ONESHOT 0
#define PERIODIC 1

typedef enum{NOT_OK,OKK}EnmTMUError_t;

extern EnmTMUError_t TMU_Init (const TMU_ConfigType * ConfigPtr );
static void TMU_cal(void);
extern EnmTMUError_t TMU_Start_Timer(uint16 time,void (*ptr)(void),uint8 periodicORoneshot);
extern void TMU_Stop_Timer(void (*ptr)(void));
extern void TMU_Dispatch(void);
extern EnmTMUError_t TMU_DeInit(void);



#endif /* TMU_H_ */
