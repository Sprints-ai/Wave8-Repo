/*
 * PWM.c
 *
 * Created: 2/16/2020 4:23:27 PM
 *  Author: Reem
 */ 
#include "../includes/PWM.h"

static uint8_t gu8_isStartedFlagCH1A =FALSE;
static uint8_t gu8_isStartedFlagCH1B =FALSE;
static uint8_t gu8_pwmPrescaleCH1A_MASK;
static uint16_t gu8_pwmPrescaleCH1A;
static uint8_t gu8_pwmPrescaleCH1B_MASK;
static uint16_t gu8_pwmPrescaleCH1B;
/*********************************************************************************/
/* Function: Error_State Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);                         */
/* Type: public                                                                  */
/* Input parameters: Pwm_Cfg Structure (channel number, Prescaler)               */
/* Return type : void                                                            */
/*                                                                               */
/* Description: initialize the PWM configuration                                 */
/*********************************************************************************/
ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg){
	switch(Pwm_Cfg->Channel){
		//Phase correct mode in timer 1 with top ICR1
		case PWM_CH1A:
			TCCR1 |= T1_PHASE_CORRECT_PWM | T1_OC1A_CLEAR;
			
			//Check the prescale value
			switch(Pwm_Cfg->Prescaler){
				
				//prescale 1
				case PWM_PRESCALER_NO:
				gu8_pwmPrescaleCH1A_MASK = T1_PWM_PRESCALE_NO_MASK;
				gu8_pwmPrescaleCH1A = T1_PWM_PRESCALE_NO;
				break;
				
				//prescale 8
				case PWM_PRESCALER_8:
				gu8_pwmPrescaleCH1A_MASK = T1_PWM_PRESCALE_8_MASK;
				gu8_pwmPrescaleCH1A = T1_PWM_PRESCALE_8;
				break;
				
				//prescale 64
				case PWM_PRESCALER_64:
				gu8_pwmPrescaleCH1A_MASK = T1_PWM_PRESCALE_64_MASK;
				gu8_pwmPrescaleCH1A = T1_PWM_PRESCALE_64;
				break;
				
				//prescale 256
				case PWM_PRESCALER_256:
				gu8_pwmPrescaleCH1A_MASK = T1_PWM_PRESCALE_256_MASK;
				gu8_pwmPrescaleCH1A = T1_PWM_PRESCALE_256;
				break;
				
				//prescale 1024
				case PWM_PRESCALER_1024:
				gu8_pwmPrescaleCH1A_MASK = T1_PWM_PRESCALE_1024_MASK;
				gu8_pwmPrescaleCH1A = T1_PWM_PRESCALE_1024;
				break;
				
				default:
				return E_INVALID_PARAMETER;
				
			}
			
		break;
		
		
		//Phase correct mode in timer 1 with top ICR1
		case PWM_CH1B:
			TCCR1 |= T1_PHASE_CORRECT_PWM | T1_OC1B_CLEAR;
			switch(Pwm_Cfg->Prescaler){
				
				//prescale 1
				case PWM_PRESCALER_NO:
				gu8_pwmPrescaleCH1B_MASK = T1_PWM_PRESCALE_NO;
				break;
				
				//prescale 8
				case PWM_PRESCALER_8:
				gu8_pwmPrescaleCH1B_MASK = T1_PWM_PRESCALE_8_MASK;
				gu8_pwmPrescaleCH1B = T1_PWM_PRESCALE_8;
				break;
				
				//prescale 64
				case PWM_PRESCALER_64:
				gu8_pwmPrescaleCH1B_MASK = T1_PWM_PRESCALE_64_MASK;
				gu8_pwmPrescaleCH1B = T1_PWM_PRESCALE_64;
				break;
				
				//prescale 256
				case PWM_PRESCALER_256:
				gu8_pwmPrescaleCH1B_MASK = T1_PWM_PRESCALE_256_MASK;
				gu8_pwmPrescaleCH1B = T1_PWM_PRESCALE_256;
				break;
				
				//prescale 1024
				case PWM_PRESCALER_1024:
				gu8_pwmPrescaleCH1B_MASK = T1_PWM_PRESCALE_1024_MASK;
				gu8_pwmPrescaleCH1B = T1_PWM_PRESCALE_1024;
				break;
				
				default:
				return E_INVALID_PARAMETER;
				
			}
			
		break;
		
		//Any thing else is error
		default:
		return E_INVALID_PARAMETER;
		break;
	}
	return E_OK;
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
ERROR_STATUS Pwm_Start(uint8_t Channel,uint8_t Duty,uint32_t Frequncy){
	switch(Channel){
		
		//Channel 1A
		case PWM_CH1A:			
			//According to phase correct equation in the datasheet Calculate the top 
			ICR1 = F_CPU/(2*gu8_pwmPrescaleCH1A * (Frequncy));
			//Set the flag
			gu8_isStartedFlagCH1A =TRUE;
			//Set the duty cycle 
			OCR1A =((ICR1*Duty)/100.0);
			//Start the timer
			TCCR1 |= gu8_pwmPrescaleCH1A_MASK;
		break;
		
		
		//Channel 1B
		case PWM_CH1B:
			
			//According to phase correct equation in the datasheet Calculate the top
			
			ICR1 = F_CPU/(2*gu8_pwmPrescaleCH1B * (Frequncy));
			//Set the flag
			gu8_isStartedFlagCH1B =TRUE;
			//Set the duty cycle
			OCR1B =((ICR1*Duty)/100.0);
			//Start the timer
			TCCR1 |= gu8_pwmPrescaleCH1B_MASK;
		break;
		
		default:
		return E_INVALID_PARAMETER;
		
	}
	return E_OK;
	
}

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: updates the duty cycle and frequency of the dedicated channel    */
/*********************************************************************************/
ERROR_STATUS Pwm_Update(uint8_t Channel,uint8_t Duty,uint32_t Frequncy){
	switch(Channel){
		//Channel 1A
		case PWM_CH1A:
		if (gu8_isStartedFlagCH1A ==TRUE)
		{
			//According to phase correct equation in the
			ICR1 = F_CPU/(2*gu8_pwmPrescaleCH1A * (Frequncy));
			//Set the flag
			gu8_isStartedFlagCH1A =TRUE;
			//Set the duty cycle
			OCR1A =((ICR1*Duty)/100.0);
			//Start the timer
			TCCR1 |= gu8_pwmPrescaleCH1A_MASK;
		}
		else{
			return E_NOT_STARTED;
		}
		
		break;
		
		
		//Channel 1B
		case PWM_CH1B:
		if(gu8_isStartedFlagCH1B == TRUE)
		{
			//According to phase correct equation in the
			ICR1 = F_CPU/(2*gu8_pwmPrescaleCH1B * (Frequncy));
			//Set the flag
			gu8_isStartedFlagCH1B =TRUE;
			//Set the duty cycle
			OCR1B =((ICR1*Duty)/100.0);
			//Start the timer
			TCCR1 |= gu8_pwmPrescaleCH1B_MASK;
		}
		else{
			return E_NOT_STARTED;
		}
		
		break;
		
		default:
		return E_INVALID_PARAMETER;
		
	}
	return E_OK;
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
ERROR_STATUS Pwm_Stop(uint8_t Channel){
	switch(Channel){
		//Channel 1A
		case PWM_CH1A:
		if (gu8_isStartedFlagCH1A ==TRUE)
		{	
			//Stop the timer
			TCCR1 &= T1_PWM_CLK_NO_MASK;
		}
		else{
			return E_STOP_WITHOUT_START;
		}
		
		break;
		
		
		//Channel 1B
		case PWM_CH1B:
		if(gu8_isStartedFlagCH1B == TRUE)
		{
			//Stop the timer
			TCCR1 &= T1_PWM_CLK_NO_MASK;
		}
		else{
			return E_STOP_WITHOUT_START;
		}
		
		break;
		
		default:
		return E_INVALID_PARAMETER;
		
	}
	return E_OK;
}