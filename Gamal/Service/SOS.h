/*
 ============================================================================
 Name        : TMU.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef SOS_H_
#define SOS_H_

/*********************************includes**********************************/
#include "../Common/std_types.h"
#include "../MCAL/registers.h"
#include "../MCAL/interrupt.h"
#include "SOS_Cfg.h"
#include "../MCAL/Timer.h"
/***************************************************************************/


/*******************************definitions********************************/
#define SOS_INITIALIZED                (1U)
#define SOS_NOT_INITIALIZED            (0U)

#define ONE_SHOOT                      0
#define PERIODIC                       1

#define TASK_REPETITION                1   /*  0=>one shoot   1=>infinite */
/************************************************************************/
/*			          Structures Definitions	                        */
/************************************************************************/


typedef struct
{
	uint8_t Timer_CH_NO;
	uint8_t Resolution;
} SOS_Config;

typedef struct
{
	uint8_t Repetition;
} SOS_ConfigChannel;

typedef struct
{
	SOS_ConfigChannel Tasks[NUMBER_OF_TASKS];
} SOS_ConfigType;

/***************************************************************************/


/******************************global variables*****************************/
/* Extern structures to be used by TMU and other modules */
extern const SOS_ConfigType SOS_TasksConfiguration;
extern const SOS_Config SOS_Configration;
/***************************************************************************/


/***************************functions prototypes****************************/
ERROR_STATUS SOS_InitRunable(SOS_Config* ConfigPtr);
ERROR_STATUS Task_Start(void (*ptr)(void), uint8_t channel_id, uint8_t repetition, uint16_t delay);
void SOS_Runable(void);
ERROR_STATUS SOS_DeInit(void);
ERROR_STATUS Task_Stop(uint8_t Channel_ID);
ERROR_STATUS SOS_SetIdleTask(void (*callback)(void));
/***************************************************************************/

#endif /* SOS_H_ */
