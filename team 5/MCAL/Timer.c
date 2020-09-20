/*
 * Timer.c
 *
 * Created: 2/17/2020 1:06:31 PM
 *  Author: MENA
 */ 

#include "Timer.h"
#include "Timerconfig.h"
#include "avr/interrupt.h"


#define NORMAL_MODE
//#define  COMPARE_MODE

uint8_t g_prescaleTimer0 = 0 ;
uint8_t g_prescaleTimer1 = 0 ;
uint8_t g_prescaleTimer2 = 0 ;

uint8_t g_ModeTimer0 = 0 ;
uint8_t g_ModeTimer1 = 0 ;
uint8_t g_ModeTimer2 = 0 ;

 volatile static void (* g_ptr_callback_function)(void) = NULL ;


/*
 * Input: Pointer to a structure contains the information needed to initialize the timer. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */




ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg){
	
	uint8_t a_u8_error_state = E_OK ;
	
	g_ptr_callback_function = (volatile void *)Timer_cfg->Timer_Cbk_ptr;
	
	switch(Timer_cfg->Timer_CH_NO){
		
/******************** TIMER 0 ***************************/
		case TIMER_CH0 :
			TCCR0 = ZERO_VALUE ;
	
			/*set the PreScale config*/
		
			g_prescaleTimer0 = Timer_cfg->Timer_Prescaler ;
			g_ModeTimer0 = Timer_cfg->Timer_Mode ;
		
			#ifdef NORMAL_MODE
	
				/*set normal or compare mode*/
				
				TCCR0 |= T0_NORMAL_MODE_MASK ;
				
				/* set polling or interrupt config*/
				if (Timer_cfg->Timer_Polling_Or_Interrupt==TIMER_POLLING_MODE)
				{
					TIMSK |=TIMER0_POLLING_MODE_MASK ;
				}else if(Timer_cfg->Timer_Polling_Or_Interrupt==TIMER_INTERRUPT_MODE){
					TIMSK |=TIMER0_INTERRUPT_NORMAL_MASK;
				}
			
			
			#endif
		
			#ifdef COMPARE_MODE
			/*mode*/
			/*OC*/
			/*output compare*/
			/*interrupt*/
			/**/
	
			#endif
		
		
		break; 
		
/**************************** TIMER 1 ********************************/

		case TIMER_CH1 :
		
			TCCR1 = ZERO_VALUE;
			
			/*set the PreScale config*/
			
			g_prescaleTimer1 = Timer_cfg->Timer_Prescaler ;
			g_ModeTimer1 = Timer_cfg->Timer_Mode ;

		
			#ifdef NORMAL_MODE
			
				/*set normal or compare mode*/
				
				TCCR1 |= T1_NORMAL_MODE_MASK ;
				
				/* set polling or interrupt config*/
				if (Timer_cfg->Timer_Polling_Or_Interrupt==TIMER_POLLING_MODE)
				{
					TIMSK |=TIMER1_POLLING_MODE_MASK ;
					}else if(Timer_cfg->Timer_Polling_Or_Interrupt==TIMER_INTERRUPT_MODE){
					TIMSK |=TIMER1_INTERRUPT_NORMAL_MASK;
				}
				
		
		
			#endif // NORMAL_MODE
		
			#ifdef COMPARE_MODE
			/*mode*/
			/*OC*/
			/*output compare*/
			/*interrupt*/
			/**/
		
			#endif // NORMAL_MODE		
		
		
		break;
///////////////////////TIMER 2 //////////////////////////

		case TIMER_CH2 :
		
			TCCR2 = ZERO_VALUE;
			
			/*set synchronous or asynchronous */
			
			ASSR &= 0xF0 ;

			/*set the PreScale config*/
			
			g_prescaleTimer2 = Timer_cfg->Timer_Prescaler ;
			g_ModeTimer2 = Timer_cfg->Timer_Mode ;

			
			
			#ifdef NORMAL_MODE
			
			/*set normal or compare mode*/
			
			TCCR2 |= T2_NORMAL_MODE_MASK ;
			
			/* set polling or interrupt config*/
			if (Timer_cfg->Timer_Polling_Or_Interrupt==TIMER_POLLING_MODE)
			{
				TIMSK |=TIMER2_POLLING_MODE_MASK ;
				}else if(Timer_cfg->Timer_Polling_Or_Interrupt==TIMER_INTERRUPT_MODE){
					
				TIMSK |=TIMER2_INTERRUPT_NORMAL_MASK;
			}
			
			
			
			#endif // NORMAL_MODE
			
			#ifdef COMPARE_MODE
			/*mode*/
			TCCR2 |= T2_COMP_MODE_MASK ;

			/*OC*/
			//disconnect
			TCCR2 |= T2_OC2_DIS ;
			
			/*output compare*/
			//in start too
			
			/* set polling or interrupt config*/
			if (Timer_cfg->Timer_Polling_Or_Interrupt==TIMER_POLLING_MODE)
			{
				TIMSK |=TIMER2_POLLING_MODE_MASK ;
				}else if(Timer_cfg->Timer_Polling_Or_Interrupt==TIMER_INTERRUPT_MODE){
				TIMSK |=TIMER2_INTERRUPT_COMPARE_MASK;
				
			}
			/**/
			
			#endif // NORMAL_MODE
			
		
		
		
		break;
///////////////////////ERROR //////////////////////////

		default :
		a_u8_error_state |= E_NOK ;
		break;
		
		
	}//// end switch of channel type
	return a_u8_error_state  ;
}



/*
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
	
		uint8_t a_u8_error_state = E_OK ;
	
		#ifdef NORMAL_MODE 
			  if(Timer_CH_NO==TIMER_CH1)
			  Timer_SetValue(Timer_CH_NO,65535-Timer_Count);
			  else
		      Timer_SetValue(Timer_CH_NO,256-Timer_Count)	;
			  
		#endif
		
        #ifdef  COMPARE_MODE
			switch (Timer_CH_NO)
			{
				case TIMER_CH0 :
				 OCR0 = Timer_Count ;
				break;
				case TIMER_CH1 :
				 OCR1A = Timer_Count;
				 OCR1B = Timer_Count;
				break;
				case TIMER_CH2 :
				 OCR2 = Timer_Count;
				break;
				default:
				a_u8_error_state |= E_NOK ;
				break;
			}
		
			
		#endif
	
		switch (Timer_CH_NO)
		{
			case TIMER_CH0 :
			if (g_ModeTimer0 ==TIMER_MODE)
			{
				switch (g_prescaleTimer0)
				{
					case TIMER_NO_CLOCK :
					TCCR0 |=TIMER0_NO_CLOCK_MASK;
					break;
					case TIMER_PRESCALER_NO:
					TCCR0 |=TIMER0_PRESCALER_NO_MASK;
					break;
					case TIMER_PRESCALER_8 :
					TCCR0 |= TIMER0_PRESCALER_8_MASK ;
					break;
					case TIMER_PRESCALER_64:
					TCCR0 |= TIMER0_PRESCALER_64_MASK ;
					break;
					case TIMER_PRESCALER_256:
					TCCR0 |= TIMER0_PRESCALER_256_MASK ;

					break;
					case TIMER_PRESCALER_1024:
					TCCR0 |= TIMER0_PRESCALER_1024_MASK ;

					break;
					default:
					a_u8_error_state |= E_NOK ;
					
					
				}
				
			}else if (g_ModeTimer0 == COUNTER_RISING_MODE){
				
				TCCR0|= COUNTER_RISING_MODE_MASK ;
				
			}else if (g_ModeTimer0 == COUNTER_FALLING_MODE){
				
				TCCR0 |= COUNTER_FALLING_MODE_MASK ;
				
			}else
				a_u8_error_state |= E_NOK ;
			
			break;
			
////////////// channel one /////////////////////

			case TIMER_CH1 :
			
			
			if (g_ModeTimer1 ==TIMER_MODE)
			{
				switch (g_prescaleTimer1)
				{
					case TIMER_NO_CLOCK :
					TCCR1 |=TIMER1_NO_CLOCK_MASK;
					break;
					case TIMER_PRESCALER_NO:
					TCCR1 |=TIMER1_PRESCALER_NO_MASK;
					break;
					case TIMER_PRESCALER_8 :
					TCCR1 |= TIMER1_PRESCALER_8_MASK ;
					break;
					case TIMER_PRESCALER_64:
					TCCR1 |= TIMER1_PRESCALER_64_MASK ;
					break;
					case TIMER_PRESCALER_256:
					TCCR1 |= TIMER1_PRESCALER_256_MASK ;

					break;
					case TIMER_PRESCALER_1024:
					TCCR1 |= TIMER1_PRESCALER_1024_MASK ;

					break;
					default:
					a_u8_error_state |= E_NOK;
					break;
					
					
				}
				
				}else if (g_ModeTimer1 == COUNTER_RISING_MODE){
				
				TCCR1|= COUNTER_RISING_MODE_MASK ;
				
				}else if (g_ModeTimer1 == COUNTER_FALLING_MODE){
				
				TCCR1 |= COUNTER_FALLING_MODE_MASK ;
				
				}else 
				a_u8_error_state |= E_NOK ; 
			
			
			break;
			
//////////////// channel two /////////////////////
			case TIMER_CH2 :
			
			if (g_ModeTimer2 ==TIMER_MODE)
			{
				switch (g_prescaleTimer2)
				{
					case TIMER_NO_CLOCK :
					TCCR2 |=TIMER2_NO_CLOCK_MASK;
					break;
					
					case TIMER_PRESCALER_NO:
					TCCR2 |=TIMER2_PRESCALER_NO_MASK;
					break;
					
					case TIMER_PRESCALER_8 :
					TCCR2 |= TIMER2_PRESCALER_8_MASK ;
					break;
					
					case TIMER_PRESCALER_64:
					TCCR2 |= TIMER2_PRESCALER_64_MASK ;
					break;
					
					case TIMER_PRESCALER_256:
					TCCR2 |= TIMER2_PRESCALER_256_MASK ;
					break;
					
					case TIMER_PRESCALER_1024:
					TCCR2 |= TIMER2_PRESCALER_1024_MASK ;
					break;
					
					default: 
					a_u8_error_state |= E_NOK ;
					break;	
					
				}///end switch case prescale
				
			}else
			return E_NOK ;
			// end if 
			break;	
			
			default: 
			return E_NOK ;
			break;
		}/// end switch case channels
		
	return a_u8_error_state ;
	
}



/*
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to get its status.
 * Output:
 * 	Data: A variable of type bool returns if the flag of the timer is raised or not.
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to return if the flag of the timer is raised or not.
 * 							
 */


ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO){
	
	uint8_t a_u8_error_state = E_OK ;
	
	switch (Timer_CH_NO)
	{
		case TIMER_CH0 :
		TCCR0 &=TIMER0_NO_CLOCK_MASK;
		break;
		case TIMER_CH1 :
		TCCR1 &=TIMER1_NO_CLOCK_MASK;
		break;
		case TIMER_CH2 :
		TCCR2 &=TIMER2_NO_CLOCK_MASK;
		break;
		default:
		a_u8_error_state |=  E_NOK ;
		break;
	}
	return a_u8_error_state ;
	
	
}


/*
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
	
	uint8_t a_u8_error_state = E_OK ;
	
	if (Data == NULL)
	{
		a_u8_error_state |= E_NOK ;
	}
	
	
	switch (Timer_CH_NO )
	{
		case TIMER_CH0 :
			if((TIFR&T0_OVF_FLAG_MASK) > ZERO_VALUE)
			{
				(*Data) = TRUE ;
				TIFR |=T0_OVF_FLAG_MASK ;
			}else
			(*Data) = FALSE ;
			break;
		
		case TIMER_CH1 :
			if((TIFR&T1_OVF_FLAG_MASK) > ZERO_VALUE)
			{
				(*Data) = TRUE ;
				TIFR |=T1_OVF_FLAG_MASK ;
			}else
			(*Data) = FALSE ;
			break;
			
		case TIMER_CH2 :
			if((TIFR&T2_OVF_FLAG_MASK) > ZERO_VALUE)
			{
				(*Data) = TRUE ;
				TIFR |=T2_OVF_FLAG_MASK ;
			}else
			(*Data) = FALSE ;
			break;
		
		default: 
		a_u8_error_state |= E_NOK ;	
		
	}
	
	return a_u8_error_state  ;
	
}



/*
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
	
	uint8_t a_u8_error_state = E_OK ;
	
	if (Data == NULL)
	{
		a_u8_error_state |= E_NOK ;
	}
	
		switch (Timer_CH_NO)
		{
			case TIMER_CH0 :
			(*Data) = TCNT0 ;
			break;
			case TIMER_CH1 :
			(*Data) = TCNT1 ;
			break;
			case TIMER_CH2 :
			(*Data) = TCNT2 ;
			break;
			default:
			a_u8_error_state |= E_NOK ;
			break;
		}
		return a_u8_error_state  ;
	
}


/*
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 	Data: This is the output variable of the function which holds the value of the timer.
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to set the value of the TCNT.
 * 							
 */


ERROR_STATUS Timer_SetValue(uint8_t Timer_CH_NO, uint16_t Data){
	
		uint8_t a_u8_error_state = E_OK ;
	
		switch (Timer_CH_NO)
		{
			case TIMER_CH0 :
			 TCNT0 =(Data)  ;
			break;
			case TIMER_CH1 :
			 TCNT1 =(Data) ;
			break;
			case TIMER_CH2 :
			 TCNT2 =(Data) ;
			break;
			default:
			a_u8_error_state |= E_NOK ;
			break;
		}
		return a_u8_error_state ;
		
}


ISR(TIMER2_OVF_vect){
	
	 g_ptr_callback_function() ;
	
		

	
}