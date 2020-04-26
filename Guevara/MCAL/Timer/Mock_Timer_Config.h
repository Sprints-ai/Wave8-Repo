/*
 * TimersConfig.h
 *
 * Created: 14/02/2020 04:58:38 ص
 *  Author: mo
 */


#ifndef TIMERSCONFIG_H_
#define TIMERSCONFIG_H_
/*INCLUDES**/

#include "../../Infrastructure/Mock_registers.h"
#include "../../Infrastructure/Error.h"
#include "../../Infrastructure/std_types.h"


/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/

typedef struct Timer_cfg_s
{
	uint8_t Timer_CH_NO;/*TIMER_CH0 0 or TIMER_CH1 1 or TIMER_CH2 2*/
	uint8_t Timer_Mode;/*Timer mode 0, COUNTER_RISING_MODE 1 COUNTER_FALLING_MODE 2*/
	uint8_t Timer_Polling_Or_Interrupt;/*TIMER_POLLING_MODE 0,TIMER_INTERRUPT_MODE 1*/
	uint8_t Timer_Prescaler;/*No 0,8 1 ,16 2,32 3,64 4,128 5,256 6,1024 7*/
	void (*Timer_Cbk_ptr)(void);/*call back for TIMER_INTERRUPT_MODE*/
}Timer_cfg_s;

/************************************************************************/
/*				 DEFINES			        */
/************************************************************************/


#define		TIMER_CH0					0
#define		TIMER_CH1					1
#define		TIMER_CH2					2
#define     MAX0     255
#define     MAX1     65536
#define     MAX2     255

#define		TIMER_MODE					        0
#define		COUNTER_RISING_MODE					1
#define		COUNTER_FALLING_MODE				2


#define T0_COUNTER_RISING_MODE_CONFIG  0x07
#define T0_COUNTER_FALLING_MODE_CONFIG 0x06

#define T2_COUNTER_RISING_MODE_CONFIG  0x0D
#define T2_COUNTER_FALLING_MODE_CONFIG  0x0C


#define T1_COUNTER_RISING_MODE_CONFIG  0x0007
#define T1_COUNTER_FALLING_MODE_CONFIG  0x0006


#define   T0_NORMAL_MODE              0

#define		TIMER_POLLING_MODE				0
#define		TIMER_INTERRUPT_MODE			1

#define   T0_INTERRUPT_NORMAL     0x01
#define   T0_INTERRUPT_DISABLE    0xFC

#define   T1_INTERRUPT_DISABLE    0xC3
#define   T1_INTERRUPT_NORMAL     0x04
#define   T1_NORMAL_MODE_CONFIG  0x0000

#define   T2_INTERRUPT_DISABLE    0x3F
#define 	T2_INTERRUPT_NORMAL     0xC0
#define   T2_NORMAL_MODE_CONFIG  	0x00


#define		TIMER_NO_CLOCK					0
#define		TIMER_PRESCALER_NO				1
#define		TIMER_PRESCALER_8				2
#define		TIMER_PRESCALER_32				3
#define		TIMER_PRESCALER_64				4
#define		TIMER_PRESCALER_128				5
#define		TIMER_PRESCALER_256				6
#define		TIMER_PRESCALER_1024			7
/***********************************************/
#define TIMER0_PRESCALER_1024_CONFIG		5
#define	TIMER0_PRESCALER_256_CONFIG		4
#define TIMER0_PRESCALER_64_CONFIG   3
#define TIMER0_PRESCALER_8_CONFIG   0x02

/***********************************************/

/***********************************************/
#define TIMER1_PRESCALER_1024_CONFIG 0x0005
#define	TIMER1_PRESCALER_256_CONFIG	 0x0004
#define TIMER1_PRESCALER_64_CONFIG   0x0003
#define TIMER1_PRESCALER_8_CONFIG    0x0002
#define TIMER1_PRESCALER_NO_CONFIG   0x0001
/***********************************************/
typedef unsigned char ERROR_STATUS;   
#define E_OK   0
#define E_NOK  1
#define TOV0      0
#define OCF0      1
#define TOV1      2
#define OCF1B     3
#define OCF1A     4
#define ICF1      5
#define TOV2      6
#define OCF2      7
/***************************************************/
/* OCF2 TOV2 ICF1 OCF1A OCF1B TOV1 OCF0 TOV0<<TIFRReg */
/***************************************************/

/********************************************************/
/********Extern Configuration Structure******************/
extern Timer_cfg_s Timer_Configuration0;
extern Timer_cfg_s Timer_Configuration2;
extern Timer_cfg_s Timer_Deinit_Configuration0;

extern Timer_cfg_s testcase2 ;
extern Timer_cfg_s testcase3;

extern Timer_cfg_s testcase4;
extern Timer_cfg_s testcase5 ;
extern Timer_cfg_s testcase6 ;
extern Timer_cfg_s testcase7 ;
extern Timer_cfg_s testcase8;
extern Timer_cfg_s testcase9;
extern Timer_cfg_s testcase10;
extern Timer_cfg_s testcase11;
extern Timer_cfg_s testcase12;
extern Timer_cfg_s testcase13;
extern Timer_cfg_s testcase14;
extern Timer_cfg_s testcase15;
extern Timer_cfg_s testcase16;
extern Timer_cfg_s testcase17;


#endif /* TIMERSCONFIG_H_ */
