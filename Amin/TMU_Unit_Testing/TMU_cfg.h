#ifndef TMU_CFG_H_
#define TMU_CFG_H_

/************************************************************************/
/*							 DEFINES							        */
/************************************************************************/
#define BUFFER_SIZE			10
#define COMP_VALUE			250

/************************************************************************/
/*					GLOBAL VARIABLES                                    */
/************************************************************************/

static uint8_t Oneshoot_tasks_counter = 0;
static uint8_t Periodic_tasks_counter = 0;
static sint16_t Tasks_buffer[2][BUFFER_SIZE] = {{0}};
static void (*arrTask_CallBackfun[2][BUFFER_SIZE])(void)={{NULL}};

static volatile uint16_t Tick_count = 0;
static uint8_t TMU_flag = 0;
static sint8_t guTMU_TIMER = -1;

/************************************************************************/
/*					  TIMER FUNCTIONS' PROTOTYPES				        */
/************************************************************************/
static void TMU_Set_Tick_Flag(void);

#endif /* TMU_CFG_H_ */
