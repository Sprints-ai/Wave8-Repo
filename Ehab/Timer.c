/*
 * Timer.c
 *
 * Created: 2/17/2020 12:55:03 AM
 *  Author: Ehab & Reem
 */ 
#include "Timer.h"



static uint8_t gu8_Prescaler;
static uint8_t gu8_Timer0InitFlag = FALSE;
static uint8_t gu8_Timer1InitFlag = FALSE;
static uint8_t gu8_Timer2InitFlag = FALSE;
static uint8_t gu8_Timer0StartFlag = FALSE;
static uint8_t gu8_Timer1StartFlag = FALSE;
static uint8_t gu8_Timer2StartFlag = FALSE;

static void (*ga_Timers_CBKs[NUMBER_OF_TIMER_CHANNELS])(void)={NULL,NULL,NULL};


/**
 * Description: Initializes the timer peripheral based on a pre-configured struct
 * @param Timer_cfg : Pointer to the configuration struct 
 * @return function status :
 *							- 0 -> E_NOK
 *							- 1 -> E_OK
 */
ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg)
{
	ERROR_STATUS ERR = E_OK;
	
	if (Timer_cfg == NULL)
	{
		ERR = ERROR_TIMER_MODULE_ID + ERROR_NULL_POINTER;
	}
	
	else 
	{
		gu8_Prescaler = Timer_cfg->Timer_Prescaler;
		
		if ((Timer_cfg->Timer_Mode == COUNTER_RISING_MODE) && (gu8_Prescaler != EXTERNAL_CLOCK_RISING))
		{ERR = ERROR_TIMER_MODULE_ID + ERROR_INVALID_PARAMETER;}
		
		if ((Timer_cfg->Timer_Mode == COUNTER_FALLING_MODE) && (gu8_Prescaler != EXTERNAL_CLOCK_FALLING))
		{ERR = ERROR_TIMER_MODULE_ID + ERROR_INVALID_PARAMETER;}
		
		switch (Timer_cfg->Timer_CH_NO)
		{
			case TIMER_CH0:
			{
				gu8_Timer0InitFlag = TRUE;
				
				switch(Timer_cfg->Timer_Polling_Or_Interrupt)
				{
					case TIMER_POLLING_MODE :
					TIMSK &= ~TOIE0;
					break;
					
					case TIMER_INTERRUPT_MODE :
					TIMSK |= TOIE0;
					ga_Timers_CBKs[TIMER_CH0] = Timer_cfg->Timer_Cbk_ptr; 
					ENABLE_GINT;
					break;
					
					default:
					ERR =ERROR_TIMER_MODULE_ID + ERROR_INVALID_PARAMETER;
					break;
				}
			}
			break;
			
			case TIMER_CH1:
			{
				gu8_Timer1InitFlag = TRUE;
				
				switch(Timer_cfg->Timer_Polling_Or_Interrupt)
				{
					case TIMER_POLLING_MODE :
					TIMSK &= ~TOIE1;
					break;
					
					case TIMER_INTERRUPT_MODE :
					TIMSK |=TOIE1;
					ga_Timers_CBKs[TIMER_CH1] = Timer_cfg->Timer_Cbk_ptr;
					ENABLE_GINT;
					break;
					
					default:
					ERR = ERROR_TIMER_MODULE_ID + ERROR_INVALID_PARAMETER;
					break;
				}
			}
			break;
			
			case TIMER_CH2:
			{
				gu8_Timer2InitFlag = TRUE;
				
				switch(Timer_cfg->Timer_Polling_Or_Interrupt)
				{
					case TIMER_POLLING_MODE :
					TIMSK &= ~TOIE2;
					break;
					
					case TIMER_INTERRUPT_MODE :
					ga_Timers_CBKs[TIMER_CH2] = Timer_cfg->Timer_Cbk_ptr;
					TIMSK |=TOIE2;
					ENABLE_GINT;
					break;
					
					default:
					ERR = ERROR_TIMER_MODULE_ID + ERROR_INVALID_PARAMETER;
					break;
				}
			}
			break;
			
			default:
			ERR = ERROR_TIMER_MODULE_ID + ERROR_INVALID_PARAMETER;
			break;
		}
	}
	
	
	return ERR;
}

/**
* Description: Deinitializes the timer peripheral based on the pre-initialization
* @return function status :
*							- 0 -> E_NOK
*							- 1 -> E_OK
*/
ERROR_STATUS Timer_DeInit(uint8_t Timer_CH_NO)
{
	ERROR_STATUS ERR = E_OK;
	switch (Timer_CH_NO)
	{
		case TIMER_CH0:
		if (gu8_Timer0InitFlag)
		{
			Timer_Stop(TIMER_CH0);
			TCNT0 = LOW;
			TIMSK &= ~TOIE0;
			gu8_Timer0InitFlag = FALSE;
		}
		else
		{
			ERR = ERROR_TIMER_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
		}
		break;
		
		case TIMER_CH1:
		if (gu8_Timer1InitFlag)
		{
			Timer_Stop(TIMER_CH1);
			TCNT1H = LOW;
			TCNT1L = LOW;
			TIMSK &= ~TOIE1;
			gu8_Timer1InitFlag = FALSE;
		}
		else
		{
			ERR = ERROR_TIMER_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
		}
		break;
		
		case TIMER_CH2:
		if (gu8_Timer2InitFlag)
		{
			Timer_Stop(TIMER_CH0);
			TCNT2 = LOW;
			TIMSK &= ~TOIE0;
			gu8_Timer2InitFlag = FALSE;
		}
		else
		{
			ERR = ERROR_TIMER_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
		}
		break;
		
		default:
		ERR = ERROR_TIMER_MODULE_ID + ERROR_INVALID_PARAMETER;
		break;
	}
	
	return ERR;
}
/**
 * Description: Starts the timer/counter
 * @param Timer_CH_NO : Channel's number :
 *										  - 0 -> TIMER_CH0
 *										  - 1 -> TIMER_CH1
 *										  - 2 -> TIMER_CH2
 * @param Timer_Count : TCNT (Timer/Counter Register) Value : for TIMER_CH0 & TIMER_CH2 
 *																takes values from (0~255)
 *															  for TIMER_CH1 
 *																takes values from (0~65,535)
 * @return function status :
 *							- 0 -> E_NOK
 *							- 1 -> E_OK
 */
ERROR_STATUS Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count)
{
	ERROR_STATUS ERR = E_OK;
	
	switch (Timer_CH_NO)
	{
		case TIMER_CH0:
		{
			if (!gu8_Timer0InitFlag)
			{ERR =ERROR_TIMER_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;}
	
			else
			{
				gu8_Timer0StartFlag = TRUE;
				
				if (Timer_Count>TCNT0_2_MAX_COUNT)
				{ERR=ERROR_TIMER_MODULE_ID + ERROR_INVALID_PARAMETER;}
				
				TCNT0 = Timer_Count;
				switch (gu8_Prescaler)
				{
					case TIMER_PRESCALER_NO:
					TCCR0 |= (CS00);
					break;
					
					case TIMER_PRESCALER_8:
					TCCR0 |= (CS01);
					break;
					
					case TIMER_PRESCALER_64:
					TCCR0 |= (CS01 | CS00);
					break;
					
					case TIMER_PRESCALER_256:
					TCCR0 |= (CS02);
					break;
					
					case TIMER_PRESCALER_1024:
					TCCR0 |= (CS02 | CS00);
					break;
					
					case EXTERNAL_CLOCK_FALLING:
					TCCR0 |= (CS02 | CS01);
					break;
					
					case EXTERNAL_CLOCK_RISING:
					TCCR0 |= (CS02 | CS01 | CS00);
					break;
					
					default:
					ERR = ERROR_TIMER_MODULE_ID + ERROR_INVALID_PARAMETER;
					break;
				}
			}
		}
		break;
		
		case TIMER_CH1:
		{
			if (!gu8_Timer1InitFlag)
			{ERR = ERROR_TIMER_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;}
				
			else
			{
				gu8_Timer1StartFlag = TRUE;
				TCNT1 = Timer_Count;
				
				switch (gu8_Prescaler)
				{
					case TIMER_PRESCALER_NO:
					TCCR1B |= (CS10);
					break;
					
					case TIMER_PRESCALER_8:
					TCCR1B |= (CS11);
					break;
					
					case TIMER_PRESCALER_64:
					TCCR1B |= (CS11 | CS10);
					break;
					
					case TIMER_PRESCALER_256:
					TCCR1B |= (CS12);
					break;
					
					case TIMER_PRESCALER_1024:
					TCCR1B |= (CS12 | CS10);
					break;
					
					case EXTERNAL_CLOCK_FALLING:
					TCCR1B |= (CS12 | CS11);
					break;
					
					case EXTERNAL_CLOCK_RISING:
					TCCR1B |= (CS12 | CS11 | CS10);
					break;
					
					default:
					ERR = ERROR_TIMER_MODULE_ID + ERROR_INVALID_PARAMETER;
					break;
				}
			}
		}
		break;
		
		case TIMER_CH2:
		{
			if (!gu8_Timer2InitFlag)
			{ERR = ERROR_TIMER_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;}
				
			else
			{
				gu8_Timer2StartFlag = TRUE;
				
				if (Timer_Count>TCNT0_2_MAX_COUNT)
				{ERR=E_NOK;}
				
				TCNT2 = Timer_Count;
				
				switch (gu8_Prescaler)
				{
					case TIMER_PRESCALER_NO:
					TCCR2 |= (CS20);
					break;
					
					case TIMER_PRESCALER_8:
					TCCR2 |= (CS21);
					break;
					
					case TIMER_PRESCALER_32:
					TCCR2 |= (CS21 | CS20);
					break;
					
					case TIMER_PRESCALER_64:
					TCCR2 |= (CS22);
					break;
					
					case TIMER_PRESCALER_128:
					TCCR2 |= (CS22 | CS20);
					break;
					
					case TIMER_PRESCALER_256:
					TCCR2 |= (CS22 | CS21);
					break;
					
					case TIMER_PRESCALER_1024:
					TCCR2 |= (CS22 | CS21 | CS20);
					break;
					
					default:
					ERR = ERROR_TIMER_MODULE_ID + ERROR_INVALID_PARAMETER;
					break;
				}
			}
		}
		break;
		
		default:
		ERR = ERROR_TIMER_MODULE_ID + ERROR_INVALID_PARAMETER;
		break;
	}
	return ERR;
}

/**
 * Description: Stops the timer/counter
 * @param Timer_CH_NO : Channel's number :
 *										  - 0 -> TIMER_CH0
 *										  - 1 -> TIMER_CH1
 *										  - 2 -> TIMER_CH2
 * @return function status :
 *							- 0 -> E_NOK
 *							- 1 -> E_OK
 */
ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO)
{
	ERROR_STATUS ERR = E_OK;
	
	switch(Timer_CH_NO)
	{
		case TIMER_CH0:
		if (!gu8_Timer0StartFlag)
		{ERR = ERROR_TIMER_MODULE_ID + ERROR_STOP_WITHOUT_START;}
			
		else
		{
			gu8_Timer0StartFlag = FALSE;
			TIMER0_STOP;	
		}
		break;
		
		case TIMER_CH1:
		if (!gu8_Timer1StartFlag)
		{ERR = ERROR_TIMER_MODULE_ID + ERROR_STOP_WITHOUT_START;}
		
		else
		{
			gu8_Timer1StartFlag = FALSE;
			TIMER1_STOP;
		}
		break;
		
		case TIMER_CH2:
		if (!gu8_Timer2StartFlag)
		{ERR = ERROR_TIMER_MODULE_ID + ERROR_STOP_WITHOUT_START;}
		
		else
		{
			gu8_Timer2StartFlag = FALSE;
			TIMER2_STOP;
		}
		break;
		
		default:
		ERR = ERROR_TIMER_MODULE_ID + ERROR_INVALID_PARAMETER;
		break;
	}
	return ERR;
}

/**
 * Description: Gets the value of the TCNT (Timer/Counter Register)
 * @param Timer_CH_NO : Channel's number :
 *										  - 0 -> TIMER_CH0
 *										  - 1 -> TIMER_CH1
 *										  - 2 -> TIMER_CH2
 * @param Data : output parameter returns : TCNT Value
 * @return function status :
 *							- 0 -> E_NOK 
 *							- 1 -> E_OK	
 */
ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO, uint16_t* Data)
{
	ERROR_STATUS ERR = E_OK;
	
	if (Data == NULL)
	{
		ERR = E_NOK;
	}
	switch (Timer_CH_NO)
	{
		case TIMER_CH0:
		*Data = TCNT0;
		break;
		
		case TIMER_CH1:
		*Data = TCNT1;
		break;
		
		case TIMER_CH2:
		*Data = TCNT2;
		break;
		
		default:
		ERR = E_NOK;
		break;
	}
	return ERR;
}

/**
* Description: Checks if the timer overflowed or not
* @param Timer_CH_NO : Channel's number :
*										  - 0 -> TIMER_CH0
*										  - 1 -> TIMER_CH1
*										  - 2 -> TIMER_CH2
* @param Data : output parameter returns :
*										   - 0 -> FALSE
*										   - 1 -> TRUE
* @return function status :
*							- 0 -> E_NOK
*							- 1 -> E_OK
*/
ERROR_STATUS Timer_GetStatus(uint8_t Timer_CH_NO, uint8_t* Data)
{
	ERROR_STATUS ERR = E_OK;
	
	if (Data == NULL)
	{
		ERR = E_NOK;
	}
	
	switch (Timer_CH_NO)
	{
		case TIMER_CH0:
		
		if (!gu8_Timer0InitFlag)
		{ERR = E_NOK;}
		
		else
		{
			
			*Data = GetBit(TIFR, TOV0);
			
			if (*Data)
			SetBit(TIFR,TOV0);
		}
		break;
		
		case TIMER_CH1:
		
		if (!gu8_Timer1InitFlag)
		{ERR = E_NOK;}
		
		else
		{
			*Data = GetBit(TIFR, TOV1);
			
			if (*Data)
			SetBit(TIFR,TOV1);
		}
		break;
		
		case TIMER_CH2:
		
		if (!gu8_Timer0InitFlag)
		{ERR = E_NOK;}
		
		else
		{
			*Data = GetBit(TIFR, TOV2);
			
			if (*Data)
			SetBit(TIFR,TOV2);
		}
		break;
		
		default:
		ERR = E_NOK;
		break;
	}
	
	return ERR;
}

ERROR_STATUS Timer_SetValue(uint8_t Timer_CH_NO , uint16_t Value)
{
	ERROR_STATUS ERR = E_OK;
	
	
	switch (Timer_CH_NO)
	{
		case TIMER_CH0:
			if (gu8_Timer0InitFlag)
			{
				TCNT0 = Value;
			}
			else
			{
				ERR = ERROR_TIMER_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
			}
			break;
			
		case TIMER_CH1:
			if (gu8_Timer1InitFlag)
			{
				TCNT1 = Value;
			}
			else
			{
				ERR = ERROR_TIMER_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
			}
			break;
			
		case TIMER_CH2:
			if (gu8_Timer2InitFlag)
			{
				TCNT2 = Value;
			}
			else
			{
				ERR = ERROR_TIMER_MODULE_ID + ERROR_MODULE_NOT_INITIALIZED;
			}
			break;
		
		default:
			ERR = ERROR_TIMER_MODULE_ID + ERROR_INVALID_PARAMETER;
	}
	return ERR;
}

InterruptServiceRoutine(TIMER0_OVF_vect)
{
	if (ga_Timers_CBKs[TIMER_CH0]!=NULL)
	{
		ga_Timers_CBKs[TIMER_CH0]();
	}
}

InterruptServiceRoutine(TIMER1_OVF_vect)
{
	if (ga_Timers_CBKs[TIMER_CH1]!=NULL)
	{
		ga_Timers_CBKs[TIMER_CH1]();
	}
}

InterruptServiceRoutine(TIMER2_OVF_vect)
{
	if (ga_Timers_CBKs[TIMER_CH2]!=NULL)
	{
		ga_Timers_CBKs[TIMER_CH2]();
	}
}