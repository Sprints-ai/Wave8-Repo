/*
 * PWM.c
 *
 * Created: 2/17/2020 7:07:19 PM
 *  Author: MENA
 */ 

#include "PWM.h"
#include "PWMconfig.h"

uint16_t g_Prescale_mask = 0 ;
#define PWM_PRE_SCALE 1024
#define PWM_PRE_scale_MASK T1_PRESCALER_1024


/*********************************************************************************/
/* Function: Error_State Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);                         */
/* Type: public                                                                  */
/* Input parameters: Pwm_Cfg Structure (channel number, Prescaler)               */
/* Return type : void                                                            */
/*                                                                               */
/* Description: initialize the PWM configuration                                 */
/*********************************************************************************/

extern ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg){
	
	
	uint8_t a_u8_error_state = E_OK ;
	
		if (Pwm_Cfg==NULL)
		{
			 a_u8_error_state |= E_NOK ;
		}
	
	
	/// set two oc pins output 
	
		DIO_Cfg_s dioCfg;
		dioCfg.GPIO=PWM_GPIO1;
		dioCfg.pins=PWM_BIT1|PWM_BIT2;
		dioCfg.dir=OUTPUT;
		a_u8_error_state |= DIO_init(&dioCfg);
		
		
	
	
	switch(Pwm_Cfg->Prescaler){
		case PWM_PRESCALER_NO :
		break;
		case PWM_PRESCALER_8:
		break;
		case PWM_PRESCALER_32 :
		break;
		case PWM_PRESCALER_64 :
		break;
		case PWM_PRESCALER_128 :
		break; 
		case PWM_PRESCALER_256 :
		
		break;
		case PWM_PRESCALER_1024 :
		//set prescale mask global to use in start
		
		g_Prescale_mask = TIMER1_PRESCALER_1024_MASK ;
		break;
		default: 
		a_u8_error_state |= E_NOK ;
	}
	
	switch(Pwm_Cfg->Channel){
		case PWM_CH0:
		
		break;
		case PWM_CH1A :
		
		TCCR1 |= T1_PHASE_CORRECT_ICR1 ;
		TCCR1 |= T1_OC1A_CLEAR ;
		
		
		break;
		case PWM_CH1B :
		
		TCCR1 |= T1_PHASE_CORRECT_ICR1 ;
		TCCR1 |= T1_OC1B_CLEAR ;
		
		break;
		case PWM_CH2 :
		
		break;
		default:
		a_u8_error_state |= E_NOK ;
		
		
	}
	
	return a_u8_error_state  ;
	
	
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
/*-------------------------------------------------------                        */
/*((all this calculations are for phase correct mode))                           */
/*all this calculation for F_CPU 16MHz                                           */
/*********************************************************************************/



extern ERROR_STATUS Pwm_Start(uint8_t Channel,uint8_t Duty,uint32_t Frequncy){
	
	uint8_t a_u8_error_state = E_OK ;
		
	uint16_t ICR_TOP ;
	uint16_t duty_cycle_tick ;
	
	//function to calculate the icr top from the freq and pre scale (fromdata sheet)
	
	ICR_TOP = F_CPU / (2.0 * PWM_PRE_SCALE * Frequncy) ;
	
	//to calculate ticks needed to add in the OCR to reach the required duty 
	//ticks for high 
	
	duty_cycle_tick = ICR_TOP *Duty/100.0 ;
	
		
		switch(Channel){
			case PWM_CH0:
			
			break;
			case PWM_CH1A :
			
			ICR1 = ICR_TOP ;
			OCR1A = duty_cycle_tick ;
			
			TCCR1|=g_Prescale_mask ;
			
			
			break;
			case PWM_CH1B :
			
			ICR1 = ICR_TOP ;
			OCR1B = duty_cycle_tick ;
			TCCR1|=g_Prescale_mask ;
			
			break;
			case PWM_CH2 :
			
			break;
			default:
			a_u8_error_state |= E_NOK ;
			
			
		}
		return a_u8_error_state  ;
	
	
}

/*********************************************************************************/
/* Function: Error_State Pwm_Update(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: updates the duty cycle and frequency of the dedicated channel    */
/*********************************************************************************/

extern ERROR_STATUS Pwm_Update( uint8_t Channel, uint8_t Duty, uint32_t Frequncy){
	
	uint8_t a_u8_error_state = E_OK ;

	
	uint16_t ICR_TOP ;
	uint16_t duty_cycle_tick ;
	
		//function to calculate the icr top from the freq and pre scale (fromdata sheet)

	
	ICR_TOP = F_CPU / (2.0 * PWM_PRE_SCALE * Frequncy) ;
	
		//to calculate ticks needed to add in the OCR to reach the required duty
		//ticks for high
	
	duty_cycle_tick = ICR_TOP *Duty/100.0 ;
	
	
	switch(Channel){
		case PWM_CH0:
		
		break;
		case PWM_CH1A :
		
		ICR1 = ICR_TOP ;
		OCR1A = duty_cycle_tick ;
		
		TCCR1|=g_Prescale_mask ;
		
		
		break;
		case PWM_CH1B :
		
		ICR1 = ICR_TOP ;
		OCR1B = duty_cycle_tick ;
		TCCR1|=g_Prescale_mask ;
		
		break;
		case PWM_CH2 :
		
		break;
		default:
		a_u8_error_state |= E_NOK ;
		
		
	}
	return a_u8_error_state ;
	
	
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


extern ERROR_STATUS Pwm_Stop( uint8_t Channel){
	uint8_t a_u8_error_state = E_OK ;
	
	switch(Channel){
		case PWM_CH0:
		
		break;
		case PWM_CH1A :
		
		TCCR1 &= TIMER1_NO_CLOCK_MASK ;
		
		
		
		break;
		case PWM_CH1B :
		
		TCCR1 &= TIMER1_NO_CLOCK_MASK ;
		
		break;
		case PWM_CH2 :
		
		break;
		default:
		a_u8_error_state |= E_NOK ;
			
	}
	
	return a_u8_error_state  ;
	
}
