/*
 * TMU.h
 *
 * Created: 2/24/2020 3:58:39 PM
 *  Author: hazem
 */ 
#ifndef _TMU_H__
#define _TMU_H__
/*- INCLUDES -----------------------------------------------*/

#include "SOS_confg.h"
#include "..\mcal\Timer.h"
#include "..\common\Error_handling.h"

/*- CONSTANTS ----------------------------------------------*/

#define ONESHOT            0
#define PERIODIC           1
#define INITIALIZED        1
#define NOTINITIALIZED     0
#define CLEAR              0
#define START              0
#define TCNT_INITIAL_VALUE 6
#define MAX_NOTASKS        BUFFER_SIZE
#define FIRST_TASK         0
#define NOTASKTOSTOP       0
#define NOT_FOUND          0
#define FOUND              1
#define LAST_TASK         BUFFER_SIZE-1 
/*- PRIMITIVE TYPES ----------------------------------------*/

typedef struct SOS_Configtype
{
	uint8_t u8_res;
	uint8_t u8_SOS_timerid;
}SOS_Configtype;
typedef   SOS_Configtype *  PtrSOS_Configtype;
typedef void(*ptrtotask)(void);
typedef  sint8_t EnmTMUError_t;

/*- Extern --------------------------------------------------*/

extern SOS_Configtype gstr_OSCONFIG;


/*- FUNCTION DECLARATIONS ----------------------------------*/

/************************************************************************/
/* TMU_Init
EnmTMUError_t TMU_Init (const SOS_Configtype * ConfigPtr )
ConfigPtr Pointer to a selected configuration structure*/
/************************************************************************/
extern EnmTMUError_t SOS_Init (const PtrSOS_Configtype ConfigPtr );
/*
Function Name 	TMU_Start_Timer
Syntax:
Return:*/

extern EnmTMUError_t SOS_Start_Timer(uint16_t u16_time,ptrtotask pf_task,uint8_t u8_periodicORoneshot);
/**
* @brief: TMU Stop
* @param: ptrFun: pointer to callback function
* @return: EnmTMUError_t status code with error code if one occurred
*/

extern EnmTMUError_t SOS_Stop_Timer(ptrtotask ptrtofun);

/**
* @brief: TMU Loops through task list and service each one as requested
* @param: void
* Input : void
* Output: None
* @return: EnmTMUError_t status code with error code if one occurred
*/
extern EnmTMUError_t SOS_Dispatch(void);

/**
* @brief: TMU DeInitialization
* @param: void
* Input : void
* Output: None
* @return: EnmTMUError_t status code with error code if one occurred
*/
extern EnmTMUError_t SOS_DeInit(void);

/**
* @brief: SOS_schadulertime
* @param: void
* Input : void
* Output: None
* @return: void
*/
extern void SOS_schedulertime(void);




#endif /* TMU_H_ */