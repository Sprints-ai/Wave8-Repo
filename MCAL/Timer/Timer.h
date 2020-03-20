/*
 * Timer.h
 *
 * Created: 16/02/2020 09:34:17 م
 *  Author: TOSHIBA
 */ 


#ifndef __TIMER_H__
#define __TIMER_H__
/*****************************************************************************************************/
/*                                        INCLUDES                                                  */
/***************************************************************************************************/
#include "../../Infrastructure/std_types.h"
#include "../../Infrastructure/registers.h"
#include "../../Infrastructure/common_macros.h"
#include "../interrupt\interrupt.h"

/*****************************************************************************************************/
/*                                        DEFINES                                                   */
/***************************************************************************************************/

    /*    TIMER_CHANEELS     */
#define TIMER_CH_0     (0)
#define TIMER_CH_1     (1)
#define TIMER_CH_2     (2)
 
   /*   TIMER_MOODES        */
#define TIMER_MODE     (0)
#define COUNTER_MODE_FALLING_EDGE   (1)
#define COUNTER_MODE_RISSING_EDGE   (2)

  /* TIMER_INTERRUPT_MODE  */
#define TIMER_MODE_INT   (0)
#define TIMER_MODE_POOLING (1)

/*TIMER_PRESCALER*/

#define		TIMER_NO_CLOCK					0
#define		TIMER_PRESCALER_NO				1
#define		TIMER_PRESCALER_8				2
#define		TIMER_PRESCALER_32				3
#define		TIMER_PRESCALER_64				4
#define		TIMER_PRESCALER_128				5
#define		TIMER_PRESCALER_256				6
#define		TIMER_PRESCALER_1024			7


/*****************************************************************************************************/
/*                                       STRUCTS                                                    */
/***************************************************************************************************/
typedef struct{
	uint8_t u8_TimerCh;
	uint8_t u8_TimerMode;
	uint8_t u8_TimerPrescaler;
	uint8_t u8_Timer_INT_Mode;
	void (* p_TOV_INT) (void);
		} gstrTimerConfig_t;
			
/*****************************************************************************************************/
/*                                       TIMER FUNCTIONS' PROTOTYPES	                            */
/***************************************************************************************************/
/*
 * @param: input:  gstrTimerConfig_t *
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description :  Initializes the Timer   
 */
extern u8_ERROR_STATUS_t Timer_Init(gstrTimerConfig_t* pstrTimerConf);

/*
 * @param: input: u8_TimerCh  :Timer Channel 
 * @param: input: u16_CountNO : Number of ticks 
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description :  Sets timer prescaler  and initials value     
 */
extern u8_ERROR_STATUS_t Timer_Start (uint8_t u8_TimerCh,uint16_t u16_CountNO);
/*
 * @param: input: u8_TimerCh  :Timer Channel  
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description :  Stops the timer      
 */
extern u8_ERROR_STATUS_t Timer_Stop(uint8_t u8_TimerCh);
/*
 * @param: input: u8_TimerCh  :Timer Channel  
 * @param: output: Timer count value 
 * @param :Input/output :None 
 * @Return : Error status 
 * Description : Gets timer value      
 */
extern u8_ERROR_STATUS_t Timer_GetValue(uint8_t u8_TimerCh,uint16_t *pu16_TimerValue);
/*
 * @param: input: u8_TimerCh  :Timer Channel  
 * @param: input: u16_TimerValue :Timer value 
 * @param: output: None
 * @param :Input/output :None 
 * @Return : Error status 
 * Description : Sets timer value      
 */

extern u8_ERROR_STATUS_t Timer_SetValue(uint8_t TimerCh,uint16_t u16_TimerValue);
/*
 * @param: input: u8_TimerCh  :Timer Channel  
 * @param: output: *pu8_TimerStatus :Timer overflow Interrupt status 
 * @param :Input/output :None 
 * @Return : Error status 
 * Description : Timer overflow Interrupt status      
 */
extern u8_ERROR_STATUS_t Timer_GetStatus(uint8_t u8_TimerCh,uint8_t *pu8_TimerStatus);
#endif /* __TIMER_H__ */