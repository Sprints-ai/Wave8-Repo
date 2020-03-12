/*
 * TMU_cfg.h
 *
 * Created: 2/24/2020 2:16:38 PM
 *  Author: Ema
 */ 


#ifndef TMU_CFG_H_
#define TMU_CFG_H_

/************************************************************************/
/*							 DEFINES							        */
/************************************************************************/
#define TASKS_MAX_NUM		10
#define COMP_VALUE			250

#define IDLE_TASK			0

/************************************************************************/
/*					GLOBAL VARIABLES                                    */
/************************************************************************/

static uint8_t tasks_counter = 0;
static sint16_t Tasks_buffer[TASKS_MAX_NUM] = {0};
static void (*arrTask_CallBackfun[TASKS_MAX_NUM])(void)={NULL};

static volatile uint16_t Tick_count = 0;	
static uint8_t SOS_flag = 0;
static sint8_t guSOS_TIMER = -1;

/************************************************************************/
/*					  TIMER FUNCTIONS' PROTOTYPES				        */
/************************************************************************/
static void SOS_Set_Tick_Flag(void);

#endif /* TMU_CFG_H_ */