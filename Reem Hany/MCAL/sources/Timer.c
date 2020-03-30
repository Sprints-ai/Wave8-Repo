/*
 * Timer.c
 *
 * Created: 2/16/2020 4:31:50 PM
 *  Author: Reem
 */ 
#include "../includes/Timer.h"
#include "../includes/Timer_Cfg.h"
#include "../includes/DIO.h"

/**************************Global variables*****************************/
static volatile uint32_t gu32_NoOfOvfs0;
static volatile void (*OVF0_CallBack_Fun)(void) = NULL;
static volatile void (*OVF1_CallBack_Fun)(void) = NULL;
static volatile void (*CTC2_CallBack_Fun)(void) = NULL;
static uint8_t gu8_T0PrescaleMask,gu8_T1PrescaleMask,gu8_T2PrescaleMask;

/**************************ISRs*****************************/
_ISR__(TIMER0_OVF_vect){
	gu32_NoOfOvfs0++;
	if(OVF0_CallBack_Fun != NULL){
		OVF0_CallBack_Fun();
	}
}

_ISR__(TIMER1_OVF_vect){
	//gu32_NoOfOvfs0++;
	if(OVF1_CallBack_Fun != NULL){
		OVF1_CallBack_Fun();
	}
}
_ISR__(TIMER2_COMP_vect){
	
	if(CTC2_CallBack_Fun != NULL){
		CTC2_CallBack_Fun();
	}
}



/**
 * Input: Pointer to a structure contains the information needed to initialize the timer. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */
ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg){
	if (Timer_cfg == NULL)
	{
		return E_NULL_PTR;
	}
	else{
		switch(Timer_cfg->Timer_CH_NO){
			
			/*Timer 0 configurations*/
			case TIMER_CH0:
			TCCR0 |= T0_WGMODE_MASK | T0_OC0_MASK;
			#if TIMER0_OVF_WMODE == ENABLE
			OVF0_CallBack_Fun = ( volatile void*)Timer_cfg->Timer_Cbk_ptr;
			#endif
			
			//Configure the prescale 
			switch(Timer_cfg->Timer_Prescaler){
				case TIMER_PRESCALER_NO:
				gu8_T0PrescaleMask = T0_PRESCALER_NO;
				break;
				
				case TIMER_PRESCALER_8:
				gu8_T0PrescaleMask = T0_PRESCALER_8;
				break;
				
				case TIMER_PRESCALER_64:
				gu8_T0PrescaleMask = T0_PRESCALER_64;
				break;
				
				case TIMER_PRESCALER_256:
				gu8_T0PrescaleMask = T0_PRESCALER_256;
				break;
				
				case TIMER_PRESCALER_1024:
				gu8_T0PrescaleMask = T0_PRESCALER_1024;
				break;
				
				default:
					return E_INVALID_PARAMETER;
				break;
			}
			
			// Configure the interrupt status interrupt or polling 
			if(Timer_cfg->Timer_Polling_Or_Interrupt == TIMER_POLLING_MODE){
				TIMSK |=T0_POLLING_MASK;
			}
			else if(Timer_cfg->Timer_Polling_Or_Interrupt == TIMER_INTERRUPT_MODE){
				TIMSK |=T0_INTERRUPT_MASK;
				EN_GLOBAL_INT;
			}			
			else{
				return E_INVALID_PARAMETER;
			}
			
			break;//end of timer 1 configurations
			
			
			/*Timer 1 configurations*/
			case TIMER_CH1:
			TCCR1 |= T1_WGMODE_MASK | T1_OC1_MASK;
			#if TIMER1_OVF_WMODE == ENABLE
			OVF1_CallBack_Fun = ( volatile void*)Timer_cfg->Timer_Cbk_ptr;
			#endif
			//Configure the prescale
			switch(Timer_cfg->Timer_Prescaler){
				case TIMER_PRESCALER_NO:
				gu8_T1PrescaleMask = T1_PRESCALER_NO;
				break;
				
				case TIMER_PRESCALER_8:
				gu8_T1PrescaleMask = T1_PRESCALER_8;
				break;
				
				case TIMER_PRESCALER_64:
				gu8_T1PrescaleMask = T1_PRESCALER_64;
				break;
				
				case TIMER_PRESCALER_256:
				gu8_T1PrescaleMask = T1_PRESCALER_256;
				break;
				
				case TIMER_PRESCALER_1024:
				gu8_T1PrescaleMask = T1_PRESCALER_1024;
				break;
				
				default:
				return E_INVALID_PARAMETER;
				break;
			}
			
			// Configure the interrupt status interrupt or polling
			if(Timer_cfg->Timer_Polling_Or_Interrupt == TIMER_POLLING_MODE){
				TIMSK |=T1_POLLING_MASK;
			}
			else if(Timer_cfg->Timer_Polling_Or_Interrupt == TIMER_INTERRUPT_MODE){
				TIMSK |=T1_INTERRUPT_MASK;
				EN_GLOBAL_INT;
				
			}
			else{
				return E_INVALID_PARAMETER;
			}
			
			break;
			
			
			/*Timer 2 configurations*/
			case TIMER_CH2:
			TCCR2 |= T2_WGMODE_MASK | T2_OC2_MASK;
			
			#if TIMER2_CTC_WMODE == ENABLE
				CTC2_CallBack_Fun = ( volatile void*)Timer_cfg->Timer_Cbk_ptr;
			#endif
			
			//Configure the prescale
			switch(Timer_cfg->Timer_Prescaler){
				case TIMER_PRESCALER_NO:
				gu8_T2PrescaleMask = T2_PRESCALER_NO;
				break;
				
				case TIMER_PRESCALER_8:
				gu8_T2PrescaleMask = T2_PRESCALER_8;
				break;
				
				case TIMER_PRESCALER_32:
				gu8_T2PrescaleMask = T2_PRESCALER_32;
				break;
				
				case TIMER_PRESCALER_64:
				gu8_T2PrescaleMask = T2_PRESCALER_64;
				break;
				
				case TIMER_PRESCALER_128:
				gu8_T2PrescaleMask = T2_PRESCALER_128;
				break;
				
				case TIMER_PRESCALER_256:
				gu8_T2PrescaleMask = T2_PRESCALER_256;
				break;
				
				case TIMER_PRESCALER_1024:
				gu8_T2PrescaleMask = T2_PRESCALER_1024;
				break;
				
				default:
				return E_INVALID_PARAMETER;
				break;
			}
			
			// Configure the interrupt status interrupt or polling
			if(Timer_cfg->Timer_Polling_Or_Interrupt == TIMER_POLLING_MODE){
				TIMSK |=T2_POLLING_MASK;
			}
			else if(Timer_cfg->Timer_Polling_Or_Interrupt == TIMER_INTERRUPT_MODE){
				TIMSK |=T2_INTERRUPT_MASK;
				EN_GLOBAL_INT;
			}
			else{
				return E_INVALID_PARAMETER;
			}
			break;
			
			
			/*Invalid channel number*/
			default:
			return E_INVALID_PARAMETER;
			break;
		}
		return E_OK;
	}
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to be started.
 *	Timer_Count: The start value of the timer.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function starts the needed timer.
 * 							
 */
ERROR_STATUS Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count){
	switch(Timer_CH_NO){
		//TIMER 0 START
		case TIMER_CH0:
		if(Timer_Count >255){
			return E_INVALID_PARAMETER;
		}
		else{
			#if TIMER0_OVF_WMODE == ENABLE
				TCNT0 =Timer_Count;
			#elif TIMER0_CTC_WMODE == ENABLE
				TCNT0 = 0;
				OCR0 = Timer_Count;
			#endif
			
			TCCR0 |= gu8_T0PrescaleMask;
		}
		break;
		
		
		
		//TIMER 1 START
		case TIMER_CH1:
	
		#if TIMER1_OVF_WMODE == ENABLE
			TCNT1 =65536-Timer_Count;
		#elif TIMER1_CTC_WMODE == ENABLE
			TCNT1 = 0;
			OCR1A = Timer_Count;
		#endif
			
		TCCR1 |= gu8_T1PrescaleMask;
		
		break;
		
		
		
		//TIMER 2 START
		case TIMER_CH2:
		if(Timer_Count >255){
			return E_INVALID_PARAMETER;
		}
		else{
			#if TIMER2_OVF_WMODE == ENABLE
				TCNT2 =256-Timer_Count;
			#elif TIMER2_CTC_WMODE == ENABLE
				TCNT2 = 0;
				OCR2 = Timer_Count;
			#endif
			TCCR2 |= gu8_T2PrescaleMask;
		}
		break;
		
		//Not timer 0 or 1 or 2
		default:
		return E_INVALID_PARAMETER;
		break;
	}
	return E_OK;
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to be stopped.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function stops the needed timer.
 * 							
 */
ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO){
	switch(Timer_CH_NO){
		//TIMER 0 STOP
		case TIMER_CH0:
		TCCR0 &= T0_NO_CLOCK;
		break;
		
		
		
		//TIMER 1 STOP
		case TIMER_CH1:
		TCCR1 &= T1_NO_CLOCK;
		break;
		
		
		
		//TIMER 2 STOP
		case TIMER_CH2:
		TCCR2 &= T2_NO_CLOCK;
		break;
		
		//Not timer 0 or 1 or 2
		default:
		return E_INVALID_PARAMETER;
		break;
	}
	return E_OK;
}

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
ERROR_STATUS Timer_GetStatus(uint8_t Timer_CH_NO, uint8_t* Data){
	switch(Timer_CH_NO){
		case TIMER_CH0:
		if(GET_BIT(TIFR,T0_INT_FLAG)==0)
			(*Data) =0;
		else{
			(*Data) =1;
		}
		RESET_INT_TIMER0_FLAG;
		break;
		
		
		case TIMER_CH1:
		if(GET_BIT(TIFR,T1_INT_FLAG)==0){
			(*Data) =0;
		}
		else{
			(*Data) =1;
		}
		RESET_INT_TIMER1_FLAG;
		break;
		
		
		case TIMER_CH2:
	    if(GET_BIT(TIFR,T2_INT_FLAG)==0){
			(*Data) =0;
		}
		else{
			(*Data) =1;
		}
		RESET_INT_TIMER2_FLAG;
		break;
		
		
		default:
		return E_INVALID_PARAMETER;
		break;
	}
	return E_OK;
}


/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 	Data: This is the output variable of the function which holds the no of overflows of the timer.
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to return the value of the overflows.
 * 							
 */
ERROR_STATUS Timer_GetNoOfOVFS(uint8_t Timer_CH_NO, uint32_t* Data){
	if (Data != NULL)
	{
		switch(Timer_CH_NO){
			case TIMER_CH0:
			(*Data) =gu32_NoOfOvfs0;
			break;
/*
			case TIMER_CH1:
			break;
			case TIMER_CH2:
			break;*/
			default:
			return E_INVALID_PARAMETER;
			break;
		}
		return E_OK;
	}
	
	return E_NULL_PTR;
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to reset the value of the overflows.
 * 							
 */
ERROR_STATUS Timer_resetNoOfOVFS(uint8_t Timer_CH_NO){
	switch(Timer_CH_NO){
		case TIMER_CH0:
		gu32_NoOfOvfs0 = 0;
		break;
	/*	case TIMER_CH1:
		break;
		case TIMER_CH2:
		break;*/
		default:
		return E_INVALID_PARAMETER;
		break;
	}
	return E_OK;
	
}

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
ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO, uint16_t* Data){
	if(Data == NULL){
		return E_NULL_PTR;
	}
	else{
		switch(Timer_CH_NO){
			case TIMER_CH0:
			(*Data) = TCNT0;
			break;
			
			case TIMER_CH1:
			(*Data) = TCNT1;
			break;
			
			case TIMER_CH2:
			(*Data) = TCNT2;
			break;
			
			default:
			return E_INVALID_PARAMETER;
			break;
			
		}
		return E_OK;
	}
}
