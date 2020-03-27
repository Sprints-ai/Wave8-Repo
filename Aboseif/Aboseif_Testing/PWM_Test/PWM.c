/*
 * PWM.c
 *
 * Created: 2020-02-17 5:02:45 PM
 * Author: EbrahimOseif
 */ 

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "PWM.h"

/************************************************************************/
/*				 Global / Static Variables						       */
/************************************************************************/


uint16_t gu16_Prescaler;

 
  struct Pwm_Cfg_s pwm_cfg =
 {
	 PWM_CH1B,
	 PWM_PRESCALER_8
 };
 

/************************************************************************/
/*		         TIMER FUNCTIONS' implementation				        */
/************************************************************************/

/*********************************************************************************/
/* Function: Error_State Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);                           */
/* Type: public                                                                  */
/* Input parameters: Pwm_Cfg Structure (channel number, Prescaler)               */
/* Return type : void                                                            */
/*                                                                               */
/* Description: initialize the PWM configuration                                 */
/*********************************************************************************/
 

  ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg)
 {
	 DIO_Cfg_s a_PWM1A;
	 DIO_Cfg_s a_PWM1B;
	 
	 ERROR_STATUS u8_status = E_OK;
	 
	 if(Pwm_Cfg == NULL)
	 {
			u8_status = E_NOK;
	 }
	 else
	 {		 
		 	 // Set For inverting or non-inverting
		 	 TCCR1A |= (COM1B1 | COM1A1);
		 	 // Set the Mode
		 	 TCCR1B |= (WGM13);
		 	 // Stop The Timer
		 	 // Set the Initial Values
		 	 TCNT1 = 0x00;
		 	 switch(Pwm_Cfg->Channel)
		 	 {
			 	 case PWM_CH1A:
			 	             a_PWM1A.dir  = OUTPUT;
			 	             a_PWM1A.GPIO = PWM1A_GPIO;
			 	             a_PWM1A.pins = PWM1A_BIT;
			 	             DIO_init(&a_PWM1A);
			 	 break;
			 	 
			 	 case PWM_CH1B:
			 	 
			 	             a_PWM1B.dir  = OUTPUT;
			 	             a_PWM1B.GPIO = PWM1B_GPIO;
			 	             a_PWM1B.pins = PWM1B_BIT;
			 	             DIO_init(&a_PWM1B);
			 	 break;
			 	 
			 	 default:
			 			u8_status = E_NOK;
		 	 }
		 
	 }
	 return u8_status;
 }

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
 ERROR_STATUS Pwm_Start(uint8_t Channel, uint8_t a_u8_Duty, uint32_t a_u32_Frequency)
 {
	 ERROR_STATUS u8_status = E_OK;
	 /* top value of the timer on mode 8 */

	 ICR1 = (CPU_FREQ / a_u32_Frequency) >> 1;
	 switch(Channel)
	 {
		 case PWM_CH1A:
		 OCR1A = (a_u8_Duty / 100.0) * ICR1;
		 break;
		 case PWM_CH1B:
		 OCR1B = (a_u8_Duty / 100.0) * ICR1;
		 break;
		 default:
				u8_status = E_NOK;
	 }
	 TCCR1B |= TIMER_PRESCALER_8;
	 
	 return u8_status;
 }

 

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: updates the duty cycle and frequency of the dedicated channel    */
/*********************************************************************************/
 extern ERROR_STATUS Pwm_Update(uint8_t a_u8_Channel, uint8_t a_u8_Duty, uint32_t a_u32_Frequency)
 {
	 ERROR_STATUS u8_status = E_OK;
	 
	 /* top value of the timer on mode 8 */
	 
	 ICR1 = (CPU_FREQ / a_u32_Frequency) >> 1;
	 
	 switch(a_u8_Channel)
	 {
		 case PWM_CH1A:
		 OCR1A = (a_u8_Duty / 100.0) * ICR1;
		 break;
		 
		 case PWM_CH1B:
		 OCR1B = (a_u8_Duty / 100.0) * ICR1;
		 break;
		 
		 default:
		 u8_status = E_NOK;
	 }
	 return u8_status;
 }
 

/*********************************************************************************/
/* Function: Error_State Pwm_Stop(uint8_t channel);                              */
/* Type: public                                                                  */
/* Input parameters: channel ID                                                  */
/* Return type : Error state                                                     */
/*                                                                               */
/* Description: responsible of Stopping the PWM by clearing the prescaler		 */
/*				of the corresponding channel                                     */
/*********************************************************************************/
 
ERROR_STATUS Pwm_Stop(uint8_t Channel)
	 {
		 ERROR_STATUS u8_status = E_OK;
		 
		 switch(Channel)
		 {
			 case PWM_CH1A:
			 OCR1A = 0;
			 break;
			 
			 case PWM_CH1B:
			 OCR1B = 0;
			 break;
			 
			 default:
					u8_status = E_NOK;
		 }
		 return u8_status;
	 }