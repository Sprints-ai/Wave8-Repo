/*
 * TMU.h
 *
 * Created: 2/24/2020 3:58:39 PM
 *  Author: hazem
 */ 
#ifndef _SOS_H__
#define _SOS_H__
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
typedef  sint8_t EnmSOSError_t;

/*- Extern --------------------------------------------------*/

extern SOS_Configtype gstr_OSCONFIG;


/*- FUNCTION DECLARATIONS ----------------------------------*/

/************************************************************************/
/* SOS_Init
EnmSOSError_t SOS_Init (const SOS_Configtype * ConfigPtr )
ConfigPtr Pointer to a selected configuration structure*/
/************************************************************************/
extern EnmSOSError_t SOS_Init (const PtrSOS_Configtype ConfigPtr );
/*
Function Name 	SOS_Start_Timer
Syntax:
Return:*/

extern EnmSOSError_t SOS_Start_Timer(uint16_t u16_time,ptrtotask pf_task,uint8_t u8_periodicORoneshot,uint8_t u8_priority);
/**
* @brief: SOS Stop
* @param: ptrFun: pointer to callback function
* @return: EnmSOSError_t status code with error code if one occurred
*/

extern EnmSOSError_t SOS_Stop_Timer(ptrtotask ptrtofun);

/**
* @brief: SOS Loops through task list and service each one as requested
* @param: void
* Input : void
* Output: None
* @return: EnmSOSError_t status code with error code if one occurred
*/
extern EnmSOSError_t SOS_Dispatch(void);

/**
* @brief: SOS DeInitialization
* @param: void
* Input : void
* Output: None
* @return: EnmSOSError_t status code with error code if one occurred
*/
extern EnmSOSError_t SOS_DeInit(void);

/**
* @brief: SOS_schadulertime
* @param: void
* Input : void
* Output: None
* @return: void
*/
extern void SOS_schedulertime(void);




#endif /* SOS_H_ */