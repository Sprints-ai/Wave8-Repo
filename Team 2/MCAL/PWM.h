/*
 ============================================================================
 Name        : PWM.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef PWM_H_
#define PWM_H_


/*********************************/
/*            MACROS             */
/*********************************/

#include "DIO.h"
#include "registers.h"
#include "../Common/std_types.h"



#define PWM_CH0        (0)
#define PWM_CH1A       (1)
#define PWM_CH1B       (2)
#define PWM_CH2        (3)
#define PWM_CH1A_CH1B  (4)


#define PWM_NO_CLOCK                     0
#define PWM_PRESCALER_NO                 0x01
#define PWM_PRESCALER_8                  0x02
#define PWM_PRESCALER_64                 0x03
#define PWM_PRESCALER_256                0x04
#define PWM_PRESCALER_1024               0x05


#define PWM1_NO_CLOCK                     0x0000
#define PWM1_PRESCALER_NO                 0x0001
#define PWM1_PRESCALER_8                  0x0002
#define PWM1_PRESCALER_64                 0x0003
#define PWM1_PRESCALER_256                0x0004
#define PWM1_PRESCALER_1024               0x0005


#define PWM2_NO_CLOCK                     0
#define PWM2_PRESCALER_NO                 0x01
#define PWM2_PRESCALER_8                  0x02
#define PWM2_PRESCALER_64                 0x03
#define PWM2_PRESCALER_256                0x04
#define PWM2_PRESCALER_1024               0x05

#define T0_PHASE_CORRECT_FREQUENCY_31KHZ         0x01
#define T0_PHASE_CORRECT_FREQUENCY_4KHZ          0x02
#define T0_PHASE_CORRECT_FREQUENCY_500HZ         0x03
#define T0_PHASE_CORRECT_FREQUENCY_122HZ         0x04
#define T0_PHASE_CORRECT_FREQUENCY_31HZ          0x05

#define T1_PHASE_CORRECT_FREQUENCY_3KHZ          0x01
#define T1_PHASE_CORRECT_FREQUENCY_400HZ         0x02
#define T1_PHASE_CORRECT_FREQUENCY_50HZ          0x03
#define T1_PHASE_CORRECT_FREQUENCY_13HZ          0x04
#define T1_PHASE_CORRECT_FREQUENCY_3HZ           0x05

#define T2_PHASE_CORRECT_FREQUENCY_31KHZ         0x01
#define T2_PHASE_CORRECT_FREQUENCY_4KHZ          0x02
#define T2_PHASE_CORRECT_FREQUENCY_1KHZ          0x03
#define T2_PHASE_CORRECT_FREQUENCY_500HZ         0x04
#define T2_PHASE_CORRECT_FREQUENCY_245KHZ        0x05
#define T2_PHASE_CORRECT_FREQUENCY_122HZ         0x06
#define T2_PHASE_CORRECT_FREQUENCY_31HZ          0x07

typedef struct Pwm_Cfg_s
{
	uint8_t Channel;
	uint8_t Prescaler;
}Pwm_Cfg_s;

/*********************************/
/*    FUNCTIONS DECLARATION      */
/*********************************/

/*********************************************************************************/
/* Function: Error_State Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);                         */
/* Type: public                                                                  */
/* Input parameters: Pwm_Cfg Structure (channel number, Prescaler)               */
/* Return type : void                                                            */
/*                                                                               */
/* Description: initialize the PWM configuration                                 */
/*********************************************************************************/
extern ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: starts the PWM on the dedicated channel with the required duty   */
/*				cycle and frequency                                              */
/*-------------------------------------------------------                        */
/*(IN timer 0) there are only 5 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ                                          */
/*Frequency (Prescaler 8) --> 3,921HZ                                            */
/*Frequency (Prescaler 64) --> 490HZ                                             */
/*Frequency (Prescaler 256) --> 122HZ                                            */
/*Frequency (Prescaler 1024) --> 31HZ                                            */
/*--------------------------------------------------------                       */
/*(IN timer 2) there are only 7 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ                                          */
/*Frequency (Prescaler 8) --> 3,921HZ                                            */
/*Frequency (Prescaler 32) --> 980HZ                                             */
/*Frequency (Prescaler 64) --> 490HZ                                             */
/*Frequency (Prescaler 128) --> 245HZ                                            */
/*Frequency (Prescaler 256) --> 122HZ                                            */
/*Frequency (Prescaler 1024) --> 31HZ                                            */
/*-------------------------------------------------------                        */
/*((all this calculations are for phase correct mode))                           */
/*all this calculation for F_CPU 16MHz                                           */
/*********************************************************************************/
extern ERROR_STATUS Pwm_Start(uint8_t Channel,uint8_t Duty,uint32_t Frequncy);

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: updates the duty cycle and frequency of the dedicated channel    */
/*********************************************************************************/
extern ERROR_STATUS Pwm_Update(uint8_t Channel,uint8_t Duty,uint32_t Frequncy);

/*********************************************************************************/
/* Function: Error_State Pwm_Stop(uint8_t channel);                              */
/* Type: public                                                                  */
/* Input parameters: channel ID                                                  */
/* Return type : Error state                                                     */
/*                                                                               */
/* Description: responsible of Stopping the PWM by clearing the prescaler		 */
/*				of the corresponding channel                                     */
/*********************************************************************************/
extern ERROR_STATUS Pwm_Stop(uint8_t Channel);

#endif /* PWM_H_ */
