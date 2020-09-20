#ifndef MOCK_TIMER_H_
#define MOCK_TIMER_H_

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "mock_registers.h"
#include "mock_registers.h"
#include "common_macros.h"
//#include "avr/interrupt.h"

/************************************************************************/
/*				 DEFINES			        */
/************************************************************************/

#define		TIMER_CH0						0
#define		TIMER_CH1						1
#define		TIMER_CH2						2

#define		TIMER_MODE						0
#define		COUNTER_RISING_MODE				1
#define		COUNTER_FALLING_MODE			2

#define		TIMER_POLLING_MODE				0
#define		TIMER_INTERRUPT_MODE			1

#define		TIMER_NO_CLOCK					0
#define		TIMER_PRESCALER_NO				1
#define		TIMER_PRESCALER_8				2
#define		TIMER_PRESCALER_32				3
#define		TIMER_PRESCALER_64				4
#define		TIMER_PRESCALER_128				5
#define		TIMER_PRESCALER_256				6
#define		TIMER_PRESCALER_1024			7

// for timer0
#define T0_MAX_VALUE		256

#define T0_NORMAL_MODE		0
#define T0_COMP_MODE		0x08
#define T0_OC0_DIS			0
#define T0_NO_CLOCK			0
#define T0_PRESCALER_NO		0x01
#define T0_PRESCALER_8		0x02
#define T0_PRESCALER_64		0x03
#define T0_PRESCALER_256	0x04
#define T0_PRESCALER_1024	0x05
#define T0_POLLING			0
#define T0_INTERRUPT_NORMAL 0x01
#define T0_INTERRUPT_CMP	0x02


// for timer1
#define T1_MAX_VALUE			65536

#define T1_NORMAL_MODE			0x0000
#define T1_COMP_MODE_OCR1A_TOP	0x0008
#define T1_COMP_MODE_ICR1_TOP	0x0018
#define T1_NO_CLOCK				0x0000
#define T1_PRESCALER_NO			0x0001
#define T1_PRESCALER_8			0x0002
#define T1_PRESCALER_64			0x0003
#define T1_PRESCALER_256		0x0004
#define T1_PRESCALER_1024		0x0005
#define T1_POLLING				0
#define T1_INTERRUPT_NORMAL		0x04
#define T0_INTERRUPT_CMP_1B		0x08
#define T1_INTERRUPT_CMP_1A		0x10


// for timer2
#define T2_MAX_VALUE			256

#define T2_NORMAL_MODE			0
#define T2_COMP_MODE			0x08
#define T2_NO_CLOCK				0
#define T2_PRESCALER_NO			0x01
#define T2_PRESCALER_8			0x02
#define T2_PRESCALER_32			0x03
#define T2_PRESCALER_64			0x04
#define T2_PRESCALER_128		0x05
#define T2_PRESCALER_256		0x06
#define T2_PRESCALER_1024		0x07
#define T2_POLLING				0
#define T2_INTERRUPT_NORMAL		0x40
#define T2_INTERRUPT_CMP		0x80

//boolean for getting the timer flag status 1 or 0
#define BOOL	uint8_t
#define ONE		1
#define ZERO	0


/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/

typedef struct Timer_cfg_s{
	uint8_t Timer_Ch;
	uint8_t Timer_Mode;
	uint8_t Timer_PreScaler;
	uint8_t Timer_Interrupt_Mode;
	void (*Timer_Cbk_ptr)(void);
}Timer_cfg_s;


/************************************************************************/
/*		         TIMER FUNCTIONS' PROTOTYPES		        */
/************************************************************************/


/**
 * Input: Pointer to a structure contains the information needed to initialize the timer.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Initiates the module.
 *
 */
ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg);

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to be started.
 *	Timer_Count: The start value of the timer.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function strats the needed timer.
 *
 */
ERROR_STATUS Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count);

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to be stopped.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function stops the needed timer.
 *
 */
ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO);

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its status.
 * Output:
 * 	Data: A variable of type bool returns if the flag of the timer is raised or not.
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to return if the flag of the timer is raised or not.
 *
 */
ERROR_STATUS Timer_GetStatus(uint8_t Timer_CH_NO, BOOL* Data);

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 	Data: This is the output variable of the function which holds the value of the timer.
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to return the value of the timer.
 *
 */
ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO, uint16_t* Data);









#endif /* MOCK_TIMER_H_ */
