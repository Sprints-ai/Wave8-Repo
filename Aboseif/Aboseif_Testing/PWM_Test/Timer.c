/*
 * Timer.c
 *
 * Created: 2020-02-17 11:02:45 AM
 *  Author: EbrahimOseif
 */ 


/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "Timer.h"


/************************************************************************/
/*				 Global / Static Variables						       */
/************************************************************************/


uint8_t gu8_Prescaler;
uint8_t gu8_Timer0initFlag = NOT_INITIALIZED;
uint8_t gu8_Timer1initFlag = NOT_INITIALIZED;
uint8_t gu8_Timer2initFlag = NOT_INITIALIZED;

/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/


/* the initialized struct*/
struct Timer_cfg_s st_Timer_cfg={
	TIMER_CH0,
	TIMER_MODE,
	TIMER_INTERRUPT_MODE,
	TIMER_PRESCALER_1024
};


/************************************************************************/
/*		         TIMER FUNCTIONS' implementation				        */
/************************************************************************/


/**
 * Input: Pointer to a structure contains the information needed to initialize the timer. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */


ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg)
{
	
	ERROR_STATUS u8_status = E_OK;
	
	if (Timer_cfg == NULL)
	{
		u8_status =  E_NOK;
	}else 
	{
		/* start the initialization process */ 
		/* if (Timer_cfg->Timer_CH_NO > TIMER_CHANNEL_NUMBER)
		 {
			 u8_status = E_NOK;
		 }else
		 { */
		switch(Timer_cfg->Timer_CH_NO){
			
			case TIMER_CH0:
			
				switch(Timer_cfg->Timer_Mode){
					
					case COUNTER_RISING_MODE:
							gu8_Prescaler = TIMER0_COUNTER_RISING;
							 break;
						 
				    case COUNTER_FALLING_MODE:
							gu8_Prescaler = TIMER0_COUNTER_FALLING;
						 break;
						 
					case TIMER_MODE:
							gu8_Prescaler = Timer_cfg->Timer_Prescaler; 
					     break;
						 
					default:
							u8_status = E_NOK;
				}
				
				switch(Timer_cfg->Timer_Polling_Or_Interrupt){
					
					case TIMER_POLLING_MODE:
						TIMSK &= ~(TOIE0);
						break;
						
					case TIMER_INTERRUPT_MODE:
						TIMSK |= (TOIE0);
						break;
						
					default:
						u8_status = E_NOK;
				}
				
				gu8_Timer0initFlag = INITIALIZED;
				
				break;
			
			case TIMER_CH1:
			
			switch(Timer_cfg->Timer_Mode){
				
				case COUNTER_RISING_MODE:
						gu8_Prescaler = TIMER1_COUNTER_RISING;
						break;
				
				case COUNTER_FALLING_MODE:
						gu8_Prescaler = TIMER1_COUNTER_FALLING;
						break;
				
				case TIMER_MODE:
						gu8_Prescaler = Timer_cfg->Timer_Prescaler;
						break;
				default:
						u8_status = E_NOK;
			}
			
			switch(Timer_cfg->Timer_Polling_Or_Interrupt){
				
				case TIMER_POLLING_MODE:
				TIMSK &= ~(TOIE1);
				break;
				
				case TIMER_INTERRUPT_MODE:
				TIMSK |= (TOIE1);
				break;
				
				default:
					u8_status = E_NOK;
			}
			
				gu8_Timer1initFlag = INITIALIZED;
			
				break;
				
			case TIMER_CH2:
				
				switch(Timer_cfg->Timer_Mode){
					
					case COUNTER_RISING_MODE:
							gu8_Prescaler = TIMER0_COUNTER_RISING;
							break;
					
					case COUNTER_FALLING_MODE:
							gu8_Prescaler = TIMER0_COUNTER_FALLING;
							break;
					
					case TIMER_MODE:
							gu8_Prescaler = Timer_cfg->Timer_Prescaler;
							break;
					
					default:
							u8_status = E_NOK;
				}
				
				switch(Timer_cfg->Timer_Polling_Or_Interrupt){
					
					case TIMER_POLLING_MODE:
							TIMSK &= ~(TOIE2);
							break;
					
					case TIMER_INTERRUPT_MODE:
							TIMSK |= (TOIE2);
							break;
					
					default:
							u8_status = E_NOK;
					}
				
					gu8_Timer2initFlag = INITIALIZED;
				
					break;
					
				default:
						u8_status = E_NOK;
				} /*end of switch */
	     	//} /* end of else */
	} /* end of outer else */ 
	return u8_status;
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
	
	ERROR_STATUS u8_status = E_OK;
	
	/*	if (Timer_CH_NO > TIMER_CHANNEL_NUMBER)
		{
			u8_status = E_NOK;
		}else
		{
			*/
	switch(Timer_CH_NO){
		
		case TIMER_CH0:
				
				if (gu8_Timer0initFlag == NOT_INITIALIZED)
				{
					u8_status = E_NOK;
				}
				else{
			
			switch(gu8_Prescaler){
		
				case TIMER_NO_CLOCK:
						TCCR0 |= TIMER_NO_CLOCK; 
						break;
		
				case TIMER_PRESCALER_NO:
						TCCR0 |= TIMER_PRESCALER_NO;
						break;
				
				case TIMER_PRESCALER_8:
						TCCR0 |= TIMER_PRESCALER_8;
						break;
				
				case TIMER_PRESCALER_64:
					/* prescaler64 is mapped to 3 which is 32 in our defines*/
						TCCR0 |=TIMER_PRESCALER_32;
						break;
				
				case TIMER_PRESCALER_256:
					/* prescaler256 is mapped to 4 which is 64 in our defines*/
						TCCR0 |=TIMER_PRESCALER_64;
						break;
				
				case TIMER_PRESCALER_1024:
					/* prescaler1024 is mapped to 5 which is 32 in our defines*/
						TCCR0 |=TIMER_PRESCALER_128;
						break;
				default:
					u8_status = E_NOK;
			}
		TCNT0 = Timer_Count;
		}/* end of else */
				
			break;
		
		case TIMER_CH1:
				if (gu8_Timer1initFlag == NOT_INITIALIZED)
				{
				 	u8_status = E_NOK;
				  }
				  else{
           	
			  	switch(gu8_Prescaler){
           		
           			case TIMER_NO_CLOCK:
           				TCCR1B |= TIMER_NO_CLOCK;
           				break;
           		
           			case TIMER_PRESCALER_NO:
           				TCCR1B |= TIMER_PRESCALER_NO;
           				break;
           		
           			case TIMER_PRESCALER_8:
           				TCCR1B |= TIMER_PRESCALER_8;
           				break;
           		
           			case TIMER_PRESCALER_64:
           			/* prescaler64 is mapped to 3 which is 32 in our defines*/
           				TCCR1B |=TIMER_PRESCALER_32;
           				break;
           		
           		case TIMER_PRESCALER_256:
           			/* prescaler256 is mapped to 4 which is 64 in our defines*/
           				TCCR1B |=TIMER_PRESCALER_64;
           				break;
           		
           		case TIMER_PRESCALER_1024:
           			/* prescaler1024 is mapped to 5 which is 32 in our defines*/
           				TCCR1B |=TIMER_PRESCALER_128;
           				break;
				default:
						u8_status = E_NOK;
           		}
           TCNT1H = (Timer_Count>>8);
           TCNT1L = Timer_Count;
		   	}/* end of else */
           	
           	break;
			   	
		case TIMER_CH2:
				if (gu8_Timer2initFlag == NOT_INITIALIZED)
				{
					u8_status = E_NOK;
				}
				else{
					
					switch(gu8_Prescaler){
						
						case TIMER_NO_CLOCK:
							TCCR2 |= TIMER_NO_CLOCK;
							break;
						
						case TIMER_PRESCALER_NO:
							TCCR2 |= TIMER_PRESCALER_NO;
							break;
						
						case TIMER_PRESCALER_8:
							TCCR2 |= TIMER_PRESCALER_8;
							break;
						
						case TIMER_PRESCALER_32:
							TCCR2 |= TIMER_PRESCALER_32;
							break;
						
						case TIMER_PRESCALER_64:
							TCCR2 |= TIMER_PRESCALER_64;
							break;
						
						case TIMER_PRESCALER_128:
							TCCR2 |= TIMER_PRESCALER_128;
							break;
						
						case TIMER_PRESCALER_256:
							TCCR2 |= TIMER_PRESCALER_256;
							break;
						
						case TIMER_PRESCALER_1024:
							TCCR2 |= TIMER_PRESCALER_1024;
							break;
						
						default: 
								u8_status = E_NOK;
					}
				TCNT2 = Timer_Count;

				}/* end of else */
					
				break;	
		default:
			u8_status = E_NOK;
	} /* end of channel switch */
  // }/*end of outer else */	
 return u8_status;
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
	
	ERROR_STATUS u8_status = E_OK;
	
	/*if (Timer_CH_NO > TIMER_CHANNEL_NUMBER)
	{
		u8_status = E_NOK;
	}
	else{*/
		switch(Timer_CH_NO){
			
			case TIMER_CH0:
			
			         if (gu8_Timer0initFlag == NOT_INITIALIZED)
			         {
			         	u8_status = E_NOK;
			         }
			         else{
			         	
			         	TCCR0 &= TIMER_NO_CLOCK;
			         	TIFR |= (TOV0);
			         	gu8_Timer0initFlag = NOT_INITIALIZED;
			         }
					 
			         break;
			
			case TIMER_CH1:
			
			            if (gu8_Timer1initFlag == NOT_INITIALIZED)
			            {
			            	u8_status = E_NOK;
			            }
			            else{
			            	
			            	TCCR1B &= TIMER_NO_CLOCK;
			            	TIFR |= (TOV1);
			            	gu8_Timer1initFlag = NOT_INITIALIZED;
			            }
						
			            break;
			
			case TIMER_CH2:
			
			       if (gu8_Timer2initFlag == NOT_INITIALIZED)
			       {
			       	u8_status = E_NOK;
			       }
			       else{
			       	
			       	TCCR2 &= TIMER_NO_CLOCK;
			       	TIFR |= (TOV2);
			       	gu8_Timer2initFlag = NOT_INITIALIZED;
			       }
				   
			       break;
			
			default:
					u8_status = E_NOK;
			} /* end of channel switch */
		//}
		return u8_status;
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

ERROR_STATUS Timer_GetStatus(uint8_t Timer_CH_NO, uint8_t* Data)	 
{
	
	ERROR_STATUS u8_status = E_OK;
	
		if (Timer_CH_NO > TIMER_CHANNEL_NUMBER)
		{
			u8_status = E_NOK;
		}
		else{
	
	switch(Timer_CH_NO){
		
		case TIMER_CH0:
				if (gu8_Timer0initFlag == NOT_INITIALIZED)
				{
					u8_status = E_NOK;
				}
				else{
					*Data = TIFR & (TOV0);
					}
				break;
		
		case TIMER_CH1:
				if (gu8_Timer1initFlag == NOT_INITIALIZED)
				{
					u8_status = E_NOK;
				}
				else{
					*Data = TIFR & (TOV1);
				}
				break;
				
		case TIMER_CH2:
				if (gu8_Timer2initFlag == NOT_INITIALIZED)
				{
					u8_status = E_NOK;
				}
				else{
					*Data = TIFR & (TOV2);
				}
				break;
		default:
				u8_status = E_NOK;
		}
	} /*end of else */
	return u8_status;
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
ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO, uint16_t* Data)
{
	
	ERROR_STATUS u8_status = E_OK;
	
		if (Timer_CH_NO > TIMER_CHANNEL_NUMBER)
		{
			u8_status = E_NOK;
		}
		else{
	         switch(Timer_CH_NO){
	         	
	         	case TIMER_CH0:
	         			if (gu8_Timer0initFlag == NOT_INITIALIZED)
	         			{
	         				u8_status = E_NOK;
	         			}
	         			else{
	         				*Data = TCNT0;
	         			}
	         			break;
	         	
	         	case TIMER_CH1:
	         	       if (gu8_Timer1initFlag == NOT_INITIALIZED)
	         	       {
	         	       	u8_status = E_NOK;
	         	       }
	         	       else{
	         	       		*Data = (TCNT1H <<8 ) | TCNT1L;
	         	       }
	         	       	break;
	         			   
	         	case TIMER_CH2:
                        if (gu8_Timer2initFlag == NOT_INITIALIZED)
                        {
                        	u8_status = E_NOK;
                        }
                        else{
                        	*Data = TCNT2;
                        }			
	                 	break;
	         	default:
	         			u8_status = E_NOK;
	         }
		}/*end of else */
		
	return u8_status;
}









