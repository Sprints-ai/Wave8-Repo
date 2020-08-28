/*
 * timers.h
 *
 *  Created on: Oct 22, 2019
 *      Author: Sprints
 */

#ifndef TIMER_H_
#define TIMER_H_

/*- INCLUDES -----------------------------------------------------------------------------------------------------------------------------------------*/
#include "../../registers.h"
#include "../DIO/DIO.h"
#include "../../common_macros.h"

/*- DEFINES-------------------------------------------------------------------------------------------------------------------------------------------*/
//#define CPU_F           16000000
#define MILLI_SECONDS   1000
#define MICRO_SECONDS   1000000
#define T1_OV_VAL       65536
#define T2_OV_VAL       256
#define T0_OV_VAL       256 		
#define T0_OCR_MAX      255      
#define T2_OCR_MAX      255      
#define KILO_HZ         1000
#define MEGA_HZ         1000000
#define PERCENT         100
/*-- calculating inverse tick time for different prescalers --*/
#define INVERSE_TICK_TIME_PRESCALE_1024  ((CPU_F)/(1024))
//#define INVERSE_TICK_TIME_PRESCALE_256   ((CPU_F)/(256))
//#define INVERSE_TICK_TIME_PRESCALE_64    ((CPU_F)/(64))
//#define INVERSE_TICK_TIME_PRESCALE_8     ((CPU_F)/(8))
//#define INVERSE_TICK_TIME_PRESCALE_NO    ((CPU_F)/(1))

/*---- Call Back Type ----*/
#define TOV_CALL_BACK 1    /* case of Over Flow ISR */
#define TOC_CALL_BACk 2    /* case of Output Compare ISR */

/*---- TIMER CHANNEL ----*/
#define  TIMER_0  0
#define  TIMER_1  1 
#define  TIMER_2  2

/*---- TIMER 0 ----*/
#define T0_NORMAL_MODE  0x00
#define T0_COMP_MODE    0x08

#define T0_OC0_DIS      0x00
#define T0_OC0_TOGGLE   0x10
#define T0_OC0_CLEAR    0x20
#define T0_OC0_SET      0x30

#define T0_NO_CLOCK        0x00
#define T0_PRESCALER_NO    0x01
#define T0_PRESCALER_8     0x02
#define T0_PRESCALER_64    0x03
#define T0_PRESCALER_256   0x04
#define T0_PRESCALER_1024  0x05

#define T0_POLLING            0x00
#define T0_INTERRUPT_NORMAL   0x01
#define T0_INTERRUPT_CMP      0x02

/*---- TIMER 1 ----*/
#define T1_NORMAL_MODE           0x0000
#define T1_COMP_MODE_OCR1A_TOP   0x0008 
#define T1_COMP_MODE_ICR1_TOP    0x0018
#define T1_FAST_PWM_NON_OCR1A    0X0318 
#define T1_COMP_MODE_ICR1_BOTTOM 0x0010

#define T1_OC1_DIS      0
#define T1_OC1A_TOGGLE  0x4000
#define T1_OC1B_TOGGLE  0x1000
#define T1_OC1A_CLEAR   0x8000
#define T1_OC1B_CLEAR   0x2000
#define T1_OC1A_SET     0xC000
#define T1_OC1B_SET     0x3000


#define T1_NO_CLOCK        0x0000
#define T1_PRESCALER_NO    0x0001
#define T1_PRESCALER_8     0x0002
#define T1_PRESCALER_64    0x0003
#define T1_PRESCALER_256   0x0004
#define T1_PRESCALER_1024  0x0005


#define T1_POLLING            0
#define T1_INTERRUPT_NORMAL   0x04
#define T1_INTERRUPT_CMP_1B   0x08
#define T1_INTERRUPT_CMP_1A   0x10
#define T1_INTERRUPT_ICAPTURE 0x20

/*---- TIMER 2 ----*/
#define T2_NORMAL_MODE  0
#define T2_COMP_MODE    0x08

#define T2_OC2_DIS      0  
#define T2_OC2_TOGGLE   0x10 
#define T2_OC2_CLEAR    0x20
#define T2_OC2_SET      0x30


#define T2_NO_CLOCK        0
#define T2_PRESCALER_NO    0x01
#define T2_PRESCALER_8     0x02
#define T2_PRESCALER_32    0x03
#define T2_PRESCALER_64    0x04
#define T2_PRESCALER_128   0x05
#define T2_PRESCALER_256   0x06
#define T2_PRESCALER_1024  0x07


#define T2_POLLING            0
#define T2_INTERRUPT_NORMAL   0x40
#define T2_INTERRUPT_CMP      0x80
/*- TYPEDEFS ----------------------------------------------------------------------------------------------------------------------------------------*/
typedef struct strTimerConfig{
   uint16_t u16_timer_ch;
   uint16_t u16_mode;
   uint16_t u16_oc;
   uint16_t u16_prescal;   
   uint16_t u16_interruptMask;
}strTimerConfig_t;

/*- FUNCTIONS PROTOTYPES -----------------------------------------------------------------------------------------------------------------------------*/
/*
*  Description : Sets Timer ISRs Call Backs
*
*  @param   uint8_t timer_channel
*  @param   uint8_t call_back_type
*  @param   void (*call_back)(void)
*
*  @return ERROR_STATUS
*/
extern ERROR_STATUS Timer_SetCallBack(uint8_t timer_channel , uint8_t call_back_type , void (*call_back)(void));

/**
 * Description: Initiates timer module. 
 * 
 * @param   strTimerConfig_t*  Timer_cfg
 * 
 * @return 	ERROR_STATUS						
 */
extern ERROR_STATUS Timer_Init(strTimerConfig_t * Timer_cfg);

/**
 * Description: This function is used to set the value of timer counter for a timer. 
 * 	
 * @param   uint8_t     Timer_CH_NO
 * @param 	uint16_t    Timer_value 	
 * 
 * @return	ERROR_STATUS						
 */
extern ERROR_STATUS Timer_SetValue(uint8_t Timer_CH_NO, uint16_t Timer_value);

/**
 * Description: This function is used to return the value of timer counter for a timer. 
 * 	
 * @param   uint8_t     Timer_CH_NO
 * @param 	uint16_t *  Timer_value 	(I/O paramter)		
 * 
 * @return	ERROR_STATUS						
 */
extern ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO, uint16_t * Timer_value);

/**
 * Description : This function starts the given timer. 
 * 	
 *	@param   uint8_t    Timer_CH_NO
 * @param   uint16_t   Timer_Count
 * 			
 * @return  ERROR_STATUS	
 */
extern ERROR_STATUS Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count);

/**
 * Description: This function stops the given timer. 
 * 	
 * @param   uint8_t  Timer_CH_NO
 * 			
 * @return  ERROR_STATUS							
 */
extern ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO);

/**
 * Description: This function is used to return if the flag of the timer is raised or not.
 * 
 * @param   uint8_t   Timer_CH_NO
 * @param   uint8_t * Timer_status
 *			
 * @return ERROR_STATUS	 						
 */
extern ERROR_STATUS Timer_GetStatus(uint8_t Timer_CH_NO, uint8_t * Timer_status);

#endif /* TIMER_H_ */