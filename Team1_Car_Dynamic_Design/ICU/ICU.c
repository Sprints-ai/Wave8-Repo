/************************************************************************/
/*                               Includes                               */
/************************************************************************/

#include "std_types.h"
#include "registers.h"
#include "interrupts.h"
#include "ICU.h"

/************************************************************************/
/*                              General macros			                */
/************************************************************************/

/*EXTI's ports and pins*/
#define  INT0_PORT					(PORTD_DIR)
#define  INT0_PIN					(2)
#define  INT1_PORT					(PORTD_DIR)
#define  INT1_PIN					(3)
#define  INT2_PORT					(PORTB_DIR)
#define  INT2_PIN					(2)

/*External interrupts control register*/
#define EXTI_REG					(GICR)

/*ICU Modes*/
#define ICU_PULSE_MODE				(0)
#define ICU_CAPTURE_MODE			(1)
	
/*EXTI's operation flags*/
#define INT0_START_OPERATION		(1)
#define INT0_END_OPERATION			(2)

#define INT1_START_OPERATION		(1)
#define INT1_END_OPERATION			(2)

#define INT2_START_OPERATION		(1)
#define INT2_END_OPERATION			(2)

/*Selection of timer channels*/
#define	TIMER0_SELECTED				(0)
#define	TIMER1_SELECTED				(1)
#define	TIMER2_SELECTED				(2)

/************************************************************************/
/*                           Important register bits                    */
/************************************************************************/

/*Global interrupts enable/disable bit*/
#define  GENERAL_INT_ENABLE_BIT		(7)

/*Interrupt control bits*/
#define MCUCR_ISC00					(0)
#define MCUCR_ISC01					(1)

#define MCUCR_ISC10					(2)
#define MCUCR_ISC11					(3)

#define MCUCSR_ISC2					(6)
    
#define GICR_INT0_EN				(6)
#define GICR_INT1_EN				(7)
#define GICR_INT2_EN				(5)

/*Interrupt pre-scaler*/
#define TIMER0_PRESCALER_1024		(0x05)
#define TIMER1_PRESCALER_1024		(0x0005)
#define TIMER2_PRESCALER_1024		(0x07)

/*Timer tick time definition*/
#define TIMER_TICK_TIME				(64)

/************************************************************************/
/*                       ICU global variables                           */
/************************************************************************/

/*Global variable indicates the selected timer*/
static volatile uint8_t gu8_timer_select  = ZERO;

/*Global variable works as a flag for ICU operation*/
static volatile uint8_t gu8_icu_operation = ZERO;

/*global variable selecting ICU mode*/
static volatile uint8_t gu8_icu_mode = ZERO;

/*Time calculated by the timer register*/
static volatile uint32_t gu32_icu_time = ZERO;
  
/************************************************************************/
/*                            ICU functions                             */
/************************************************************************/

ERROR_STATUS Icu_Init(uint8_t au8_ICU_Ch_No, uint8_t au8_ICU_Ch_Timer)
{
	/*Variable used in error reporting*/
	ERROR_STATUS err_var = E_OK;

	/*Enable global interrupts*/
	SET_BIT(SREG,GENERAL_INT_ENABLE_BIT);
	
	/*Selecting ICU channel [EXTI0 - EXTI1 - EXTI2]*/		
	switch(au8_ICU_Ch_No)
	{
		case ICU_CH0:
			/*Enabling INT0 and making its pin as input*/
			CLEAR_BIT(INT0_PORT , INT0_PIN);
			SET_BIT(EXTI_REG , GICR_INT0_EN);
			break;

		case ICU_CH1:
			/*Enabling INT1 and making its pin as input*/
			CLEAR_BIT(INT1_PORT, INT1_PIN);
			SET_BIT(EXTI_REG , GICR_INT1_EN);
			break;

		case ICU_CH2:
			/*Enabling INT2 and making its pin as input*/
			CLEAR_BIT(INT2_PORT,INT2_PIN);
			SET_BIT(EXTI_REG , GICR_INT2_EN);
			break;
		
		default: err_var = E_NOK;	
	}
	
	/*Select ICU timer channel and resetting its counter*/
	switch(au8_ICU_Ch_Timer)
	{
		case ICU_TIMER_CH0:
			TCNT0 = ZERO;
			gu8_timer_select = TIMER0_SELECTED;
			break;
			
		case ICU_TIMER_CH1:
			TCNT1 = ZERO;
			gu8_timer_select = TIMER1_SELECTED;
			break;

		case ICU_TIMER_CH2:
			TCNT2 = ZERO;
			gu8_timer_select = TIMER2_SELECTED;
			break;
		
		default: err_var = E_NOK;		
	}
	
	return err_var;
}

ERROR_STATUS Icu_ReadTime(uint8_t au8_ICU_Channel, uint8_t au8_ICU_EdgeToEdge, uint32_t* pu32_ICU_Time)
{
	/*Variable used in error reporting*/	
	ERROR_STATUS err_var = E_OK;
	
	if(pu32_ICU_Time != NULL)
	{
		if(gu8_timer_select == TIMER0_SELECTED)
		{
			/*Setting timer0 tick time to 64us*/
			TCCR0 = TIMER0_PRESCALER_1024;
		}
		else if(gu8_timer_select == TIMER1_SELECTED)
		{
			/*Setting timer1 tick time to 64us*/
			TCCR1 = TIMER1_PRESCALER_1024;
		}
		else
		{
			/*Setting timer2 tick time to 64us*/
			TCCR2 = TIMER2_PRESCALER_1024;
		}
				
		switch(au8_ICU_Channel)
		{
			case ICU_CH0:
				switch(au8_ICU_EdgeToEdge)
				{
					case ICU_RISE_TO_RISE:
						/*Setting INT0 on rising edge*/
						SET_BIT(MCUCR , MCUCR_ISC00);
						SET_BIT(MCUCR , MCUCR_ISC01);
						/*Setting ICU Mode*/
						gu8_icu_mode = ICU_PULSE_MODE;
						/*Waiting for starting operation*/
						while(gu8_icu_operation != INT0_START_OPERATION);
						/*Waiting for the operation end*/
						while(gu8_icu_operation != INT0_END_OPERATION);
						/*Passing time calculated*/
						*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
						/*Resetting the operation flag*/
						gu8_icu_operation = ZERO;
						break; 

					case ICU_RISE_TO_FALL:
						/*Setting INT0 on rising edge*/
						SET_BIT(MCUCR , MCUCR_ISC00);
						SET_BIT(MCUCR , MCUCR_ISC01);
						/*Setting ICU Mode*/
						gu8_icu_mode = ICU_PULSE_MODE;
						/*Waiting for starting operation*/
						while(gu8_icu_operation != INT0_START_OPERATION);
						/*Setting INT0 on falling edge*/
						CLEAR_BIT(MCUCR , MCUCR_ISC00);
						SET_BIT(MCUCR , MCUCR_ISC01);
						/*Waiting for the operation end*/
						while(gu8_icu_operation != INT0_END_OPERATION);
						/*Passing time calculated*/
						*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
						/*Resetting the operation flag*/
						gu8_icu_operation = ZERO;
						break;

					case ICU_FALL_TO_RISE:
						/*Setting INT0 on falling edge*/
						CLEAR_BIT(MCUCR , MCUCR_ISC00);
						SET_BIT(MCUCR , MCUCR_ISC01);
						/*Setting ICU Mode*/
						gu8_icu_mode = ICU_PULSE_MODE;
						/*Waiting for starting operation*/
						while(gu8_icu_operation != INT0_START_OPERATION);
						/*Setting INT0 on rising edge*/
						SET_BIT(MCUCR , MCUCR_ISC00);
						SET_BIT(MCUCR , MCUCR_ISC01);
						/*Waiting for the operation end*/
						while(gu8_icu_operation != INT0_END_OPERATION);
						/*Passing time calculated*/
						*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
						/*Resetting the operation flag*/
						gu8_icu_operation = ZERO;
						break;

					case ICU_COUNT_CAPT_RISING:						
						if(gu8_icu_operation == ZERO)
						{
							/*Setting INT0 on rising edge*/
							SET_BIT(MCUCR , MCUCR_ISC00);
							SET_BIT(MCUCR , MCUCR_ISC01);

							/*Setting ICU Mode*/
							gu8_icu_mode = ICU_CAPTURE_MODE;	
													
							/*Starting ICU operation*/
							gu8_icu_operation = INT0_START_OPERATION;						
						}
						/*Pass time when the interrupt happens only*/
						else if(gu8_icu_operation == INT0_END_OPERATION)
						{
							/*Passing time calculated*/
							*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
							/*Starting ICU operation*/
							gu8_icu_operation = INT0_START_OPERATION;	
						} 
						else
						{
							/*DO nothing*/
						}
						break;

					case ICU_COUNT_CAPT_FALLING:				
						if(gu8_icu_operation == ZERO)
						{
							/*Setting INT0 on falling edge*/
							CLEAR_BIT(MCUCR , MCUCR_ISC00);
							SET_BIT(MCUCR , MCUCR_ISC01);	

							/*Setting ICU Mode*/
							gu8_icu_mode = ICU_CAPTURE_MODE;												

							/*Starting ICU operation*/
							gu8_icu_operation = INT0_START_OPERATION;						
						}
						/*Pass time when the interrupt happens only*/
						else if(gu8_icu_operation == INT0_END_OPERATION)
						{
							/*Passing time calculated*/
							*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
							/*Resetting the operation flag*/
							gu8_icu_operation = INT0_START_OPERATION;	
						} 
						else
						{
							/*DO nothing*/
						}
						break;
				
					default: err_var = E_NOK;
				}
				break;

			case ICU_CH1:			
				switch(au8_ICU_EdgeToEdge)
				{
					case ICU_RISE_TO_RISE:
						/*Setting INT1 on rising edge*/
						SET_BIT(MCUCR , MCUCR_ISC10);
						SET_BIT(MCUCR , MCUCR_ISC11);
						/*Setting ICU Mode*/
						gu8_icu_mode = ICU_PULSE_MODE;
						/*Waiting for starting operation*/
						while(gu8_icu_operation != INT1_START_OPERATION);
						/*Waiting for the operation end*/
						while(gu8_icu_operation != INT1_END_OPERATION);
						/*Passing time calculated*/
						*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
						/*Resetting the operation flag*/
						gu8_icu_operation = ZERO;
						break; 

					case ICU_RISE_TO_FALL:
						/*Setting INT1 on rising edge*/
						SET_BIT(MCUCR , MCUCR_ISC10);
						SET_BIT(MCUCR , MCUCR_ISC11);
						/*Setting ICU Mode*/
						gu8_icu_mode = ICU_PULSE_MODE;
						/*Waiting for starting operation*/
						while(gu8_icu_operation != INT1_START_OPERATION);
						/*Setting INT1 on falling edge*/
						CLEAR_BIT(MCUCR , MCUCR_ISC10);
						SET_BIT(MCUCR , MCUCR_ISC11);
						/*Waiting for the operation end*/
						while(gu8_icu_operation != INT1_END_OPERATION);
						/*Passing time calculated*/
						*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
						/*Resetting the operation flag*/
						gu8_icu_operation = ZERO;
						break;

					case ICU_FALL_TO_RISE:
						/*Setting INT1 on falling edge*/
						CLEAR_BIT(MCUCR , MCUCR_ISC10);
						SET_BIT(MCUCR , MCUCR_ISC11);
						/*Setting ICU Mode*/
						gu8_icu_mode = ICU_PULSE_MODE;
						/*Waiting for starting operation*/
						while(gu8_icu_operation != INT1_START_OPERATION);
						/*Setting INT1 on rising edge*/
						SET_BIT(MCUCR , MCUCR_ISC10);
						SET_BIT(MCUCR , MCUCR_ISC11);
						/*Waiting for the operation end*/
						while(gu8_icu_operation != INT1_END_OPERATION);
						/*Passing time calculated*/
						*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
						/*Resetting the operation flag*/
						gu8_icu_operation = ZERO;
						break;

					case ICU_COUNT_CAPT_RISING:						
						if(gu8_icu_operation == ZERO)
						{
							/*Setting INT1 on rising edge*/
							SET_BIT(MCUCR , MCUCR_ISC10);
							SET_BIT(MCUCR , MCUCR_ISC11);
						
							/*Setting ICU Mode*/
							gu8_icu_mode = ICU_CAPTURE_MODE;							
						
							/*Starting ICU operation*/
							gu8_icu_operation = INT1_START_OPERATION;						
						}
						/*Pass time when the interrupt happens only*/
						else if(gu8_icu_operation == INT1_END_OPERATION)
						{
							/*Passing time calculated*/
							*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
							/*Resetting the operation flag*/
							gu8_icu_operation = INT1_START_OPERATION;	
						} 
						else
						{
							/*DO nothing*/
						}
						break;

					case ICU_COUNT_CAPT_FALLING:				
						if(gu8_icu_operation == ZERO)
						{
							/*Setting INT1 on falling edge*/
							CLEAR_BIT(MCUCR , MCUCR_ISC10);
							SET_BIT(MCUCR , MCUCR_ISC11);	

							/*Setting ICU Mode*/
							gu8_icu_mode = ICU_CAPTURE_MODE;													

							/*Starting ICU operation*/
							gu8_icu_operation = INT1_START_OPERATION;						
						}
						/*Pass time when the interrupt happens only*/
						else if(gu8_icu_operation == INT1_END_OPERATION)
						{
							/*Passing time calculated*/
							*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
							/*Resetting the operation flag*/
							gu8_icu_operation = INT1_START_OPERATION;	
						} 
						else
						{
							/*DO nothing*/
						}
						break;
				
					default: err_var = E_NOK;
				}
				break;

			case ICU_CH2:
				switch(au8_ICU_EdgeToEdge)
				{
					case ICU_RISE_TO_RISE:
						/*Setting INT2 on rising edge*/
						SET_BIT(MCUCSR , MCUCSR_ISC2);
						/*Setting ICU Mode*/
						gu8_icu_mode = ICU_PULSE_MODE;
						/*Waiting for starting operation*/
						while(gu8_icu_operation != INT2_START_OPERATION);
						/*Waiting for the operation end*/
						while(gu8_icu_operation != INT2_END_OPERATION);
						/*Passing time calculated*/
						*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
						/*Resetting the operation flag*/
						gu8_icu_operation = ZERO;
						break; 

					case ICU_RISE_TO_FALL:
						/*Setting INT2 on rising edge*/
						SET_BIT(MCUCSR , MCUCSR_ISC2);
						/*Setting ICU Mode*/
						gu8_icu_mode = ICU_PULSE_MODE;
						/*Waiting for starting operation*/
						while(gu8_icu_operation != INT2_START_OPERATION);
						/*Setting INT2 on falling edge*/
						CLEAR_BIT(MCUCSR , MCUCSR_ISC2);
						/*Waiting for the operation end*/
						while(gu8_icu_operation != INT2_END_OPERATION);
						/*Passing time calculated*/
						*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
						/*Resetting the operation flag*/
						gu8_icu_operation = ZERO;
						break;

					case ICU_FALL_TO_RISE:
						/*Setting INT2 on rising edge*/
						SET_BIT(MCUCSR , MCUCSR_ISC2);
						/*Setting ICU Mode*/
						gu8_icu_mode = ICU_PULSE_MODE;
						/*Waiting for starting operation*/
						while(gu8_icu_operation != INT2_START_OPERATION);
						/*Setting INT2 on falling edge*/
						CLEAR_BIT(MCUCSR , MCUCSR_ISC2);
						/*Waiting for the operation end*/
						while(gu8_icu_operation != INT2_END_OPERATION);
						/*Passing time calculated*/
						*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
						/*Resetting the operation flag*/
						gu8_icu_operation = ZERO;
						break;

					case ICU_COUNT_CAPT_RISING:						
						if(gu8_icu_operation == ZERO)
						{
							/*Setting INT2 on rising edge*/
							SET_BIT(MCUCSR , MCUCSR_ISC2);
	
							/*Setting ICU Mode*/
							gu8_icu_mode = ICU_CAPTURE_MODE;						
	
							/*Starting ICU operation*/
							gu8_icu_operation = INT2_START_OPERATION;						
						}
						/*Pass time when the interrupt happens only*/
						else if(gu8_icu_operation == INT2_END_OPERATION)
						{
							/*Passing time calculated*/
							*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
							/*Resetting the operation flag*/
							gu8_icu_operation = INT2_START_OPERATION;	
						} 
						else
						{
							/*DO nothing*/
						}
						break;

					case ICU_COUNT_CAPT_FALLING:				
						if(gu8_icu_operation == ZERO)
						{
							/*Setting INT2 on falling edge*/
							CLEAR_BIT(MCUCSR , MCUCSR_ISC2);
	
							/*Setting ICU Mode*/
							gu8_icu_mode = ICU_CAPTURE_MODE;												
	
							/*Starting ICU operation*/
							gu8_icu_operation = INT2_START_OPERATION;						
						}
						/*Pass time when the interrupt happens only*/
						else if(gu8_icu_operation == INT2_END_OPERATION)
						{
							/*Passing time calculated*/
							*pu32_ICU_Time = ( gu32_icu_time * TIMER_TICK_TIME );
							/*Resetting the operation flag*/
							gu8_icu_operation = INT2_START_OPERATION;	
						} 
						else
						{
							/*DO nothing*/
						}
						break;
				
					default: err_var = E_NOK;
				}
				break;
		
			default: err_var = E_NOK;	
		}
		
	}
	else
	{
		err_var = E_NOK;
	}
	
	return err_var;
}

ISR(INT0_vect)
{
	/*Selecting ICU operation mode*/
	switch(gu8_icu_mode)
	{
		case ICU_PULSE_MODE:
			if(gu8_icu_operation == ZERO)
			{
				/*Starting ICU operation*/
				gu8_icu_operation = INT0_START_OPERATION;
		
				/*Resetting specified timer counter*/
				switch(gu8_timer_select)
				{
					case TIMER0_SELECTED:
						TCNT0 = ZERO;
						break;

					case TIMER1_SELECTED:
						TCNT1 = ZERO;
						break;

					case TIMER2_SELECTED:
						TCNT2 = ZERO;
						break;
			
					default: /*Do nothing*/
						break;	
				}
			}
			else
			{
				/*Ending ICU operation*/
				gu8_icu_operation = INT0_END_OPERATION;
		
				/*Getting specified timer counts and stopping it*/
				switch(gu8_timer_select)
				{
					case TIMER0_SELECTED:
						gu32_icu_time = ((uint32_t) TCNT0);
						TCCR0 = ZERO;
						break;

					case TIMER1_SELECTED:
						gu32_icu_time = ((uint32_t) TCNT1);
						TCCR1 = ZERO;
						break;

					case TIMER2_SELECTED:
						gu32_icu_time = ((uint32_t) TCNT2);
						TCCR2 = ZERO;
						break;	
			
					default: /*Do nothing*/	
						break;				
				}
			}	
			break;

		case ICU_CAPTURE_MODE:
			/*Ending ICU operation*/
			gu8_icu_operation = INT0_END_OPERATION;
		
			/*Getting specified timer counts and stopping it*/
			switch(gu8_timer_select)
			{
				case TIMER0_SELECTED:
					gu32_icu_time = ((uint32_t) TCNT0);
					TCCR0 = ZERO;
					break;

				case TIMER1_SELECTED:
					gu32_icu_time = ((uint32_t) TCNT1);
					TCCR1 = ZERO;
					break;

				case TIMER2_SELECTED:
					gu32_icu_time = ((uint32_t) TCNT2);
					TCCR2 = ZERO;
					break;	
			
				default: /*Do nothing*/	
					break;				
			}
			break;
	
		default: break;		
	}
}

ISR(INT1_vect)
{
	/*Selecting ICU operation mode*/
	switch(gu8_icu_mode)
	{
		case ICU_PULSE_MODE:
			if(gu8_icu_operation == ZERO)
			{
				/*Starting ICU operation*/
				gu8_icu_operation = INT1_START_OPERATION;
		
				/*Resetting specified timer counter*/
				switch(gu8_timer_select)
				{
					case TIMER0_SELECTED:
						TCNT0 = ZERO;
						break;

					case TIMER1_SELECTED:
						TCNT1 = ZERO;
						break;

					case TIMER2_SELECTED:
						TCNT2 = ZERO;
						break;
			
					default: /*Do nothing*/	
						break;
				}
			}
			else
			{
				/*Ending ICU operation*/
				gu8_icu_operation = INT1_END_OPERATION;
		
				/*Getting specified timer counts and stopping it*/
				switch(gu8_timer_select)
				{
					case TIMER0_SELECTED:
						gu32_icu_time = ((uint32_t) TCNT0);
						TCCR0 = ZERO;
						break;

					case TIMER1_SELECTED:
						gu32_icu_time = ((uint32_t) TCNT1);
						TCCR1 = ZERO;
						break;

					case TIMER2_SELECTED:
						gu32_icu_time = ((uint32_t) TCNT2);
						TCCR2 = ZERO;
						break;	
			
					default: /*Do nothing*/
						break;					
				}
			}	
			break;
			
		case ICU_CAPTURE_MODE:
			/*Ending ICU operation*/
			gu8_icu_operation = INT1_END_OPERATION;
		
			/*Getting specified timer counts and stopping it*/
			switch(gu8_timer_select)
			{
				case TIMER0_SELECTED:
					gu32_icu_time = ((uint32_t) TCNT0);
					TCCR0 = ZERO;
					break;

				case TIMER1_SELECTED:
					gu32_icu_time = ((uint32_t) TCNT1);
					TCCR1 = ZERO;
					break;

				case TIMER2_SELECTED:
					gu32_icu_time = ((uint32_t) TCNT2);
					TCCR2 = ZERO;
					break;	
			
				default: /*Do nothing*/
					break;					
			}		
			break;
		
		default: break;		
	}	
}

ISR(INT2_vect)
{
	/*Selecting ICU operation mode*/
	switch(gu8_icu_mode)
	{
		case ICU_PULSE_MODE:
			if(gu8_icu_operation == ZERO)
			{
				/*Starting ICU operation*/
				gu8_icu_operation = INT2_START_OPERATION;
		
				/*Resetting specified timer counter*/
				switch(gu8_timer_select)
				{
					case TIMER0_SELECTED:
						TCNT0 = ZERO;
						break;

					case TIMER1_SELECTED:
						TCNT1 = ZERO;
						break;

					case TIMER2_SELECTED:
						TCNT2 = ZERO;
						break;
			
					default: /*Do nothing*/
						break;	
				}
			}
			else
			{
				/*Ending ICU operation*/
				gu8_icu_operation = INT2_END_OPERATION;
		
				/*Getting specified timer counts and stopping it*/
				switch(gu8_timer_select)
				{
					case TIMER0_SELECTED:
						gu32_icu_time = ((uint32_t) TCNT0);
						TCCR0 = ZERO;
						break;

					case TIMER1_SELECTED:
						gu32_icu_time = ((uint32_t) TCNT1);
						TCCR1 = ZERO;
						break;

					case TIMER2_SELECTED:
						gu32_icu_time = ((uint32_t) TCNT2);
						TCCR2 = ZERO;
						break;	
			
					default: /*Do nothing*/	
						break;				
				}
			}	
			break;
			
		case ICU_CAPTURE_MODE:
			/*Ending ICU operation*/
			gu8_icu_operation = INT2_END_OPERATION;
		
			/*Getting specified timer counts and stopping it*/
			switch(gu8_timer_select)
			{
				case TIMER0_SELECTED:
					gu32_icu_time = ((uint32_t) TCNT0);
					TCCR0 = ZERO;
					break;

				case TIMER1_SELECTED:
					gu32_icu_time = ((uint32_t) TCNT1);
					TCCR1 = ZERO;
					break;

				case TIMER2_SELECTED:
					gu32_icu_time = ((uint32_t) TCNT2);
					TCCR2 = ZERO;
					break;	
			
				default: /*Do nothing*/	
					break;				
			}		
			break;
		
		default: break;		
	}	
}