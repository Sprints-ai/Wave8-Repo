
/************************************************************************/
/*				 INCLUDES			        							*/
/************************************************************************/

#include "timer.h"

/************************************************************************/
/*				 DEFINES			        							*/
/************************************************************************/
#define NOT_INITIALIZED		0
#define INITIALIZED			1
#define MAX_TIMER_CHANNELS	3


/************************************************************************/
/*				 GLOBAL  VARIABLES			        			*/
/************************************************************************/

uint32_t gu_timer_count2;
uint32_t gu_timer_count3;
static timer_Cbk gpf_timercbk;



/************************************************************************/
/*				 GLOBAL STATIC VARIABLES			        			*/
/************************************************************************/

static uint8_t gsau8_mode[MAX_TIMER_CHANNELS] = {TIMER_MODE, TIMER_MODE, TIMER_MODE};
static uint8_t gsau8_preScaler[MAX_TIMER_CHANNELS] = {TIMER_NO_CLOCK, TIMER_NO_CLOCK, TIMER_NO_CLOCK};
static uint8_t gsau8_initState[MAX_TIMER_CHANNELS] = {NOT_INITIALIZED, NOT_INITIALIZED, NOT_INITIALIZED};


/*- APIs IMPLEMENTATION -----------------------------------*/


/**
 * Input: Pointer to a structure contains the information needed to initialize the timer.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Initiates the module.
 */
ERROR_STATUS Timer_Init(Timer_cfg_s* info)
{ERROR_STATUS ERROR=E_OK;
	if(info!=NULL)
	{
		gsau8_preScaler[info->Timer_CH] = info->Timer_Prescaler;
		/* Pass pointer to callback function */
		switch(info->Timer_Mode)
		{
		case(TIMER_MODE):
			switch(info->Timer_CH)
			{
			case (TIMER_0):
				/* Normal mode */
				TCCR0 &= ~(WGM01 | WGM00);

				if(info->Timer_Int_MODE == TIMER_INTERRUPT_MODE)
				{  
					Set_BIT(TIMSK,TOIE0);			
				}
				else
				{  
               Clear_BIT(TIMSK,TOIE0);
					
				}
				break;
			case (TIMER_1):
				/* Normal mode */
            Clear_BIT(TCCR1A,WGM11);
            Clear_BIT(TCCR1A,WGM10);
            Clear_BIT(TCCR1B,WGM12);
            Clear_BIT(TCCR1B,WGM13);
				if(info->Timer_Int_MODE == TIMER_POLLING_MODE)
				{  
               Clear_BIT(TIMSK,TOIE1);
				}
				else
				{     
               Set_BIT(TIMSK,TOIE1);
				}
				break;
			case (TIMER_2):
				/* Normal mode */
            Clear_BIT(TCCR2,WGM21);
            Clear_BIT(TCCR2,WGM20);
				if(info->Timer_Int_MODE == TIMER_POLLING_MODE)
				{     
               Clear_BIT(TIMSK,TOIE2);
				}
				else
				{     
               Set_BIT(TIMSK,TOIE2);
				}
				break;
			default:
				ERROR=E_NOK;
				break;
			}
			gsau8_mode[info->Timer_CH] = TIMER_MODE;
			break;
		case(COUNTER_RISING_MODE):
			gsau8_mode[info->Timer_CH] = COUNTER_RISING_MODE;
			break;
		case(COUNTER_FALLING_MODE):
			gsau8_mode[info->Timer_CH] = COUNTER_FALLING_MODE;
			break;
		default:
			ERROR=E_NOK;
			break;
		}
		gsau8_initState[info->Timer_CH] = INITIALIZED;
		ERROR=E_OK;
	}
	else
	{
		ERROR=E_NOK;
	}
	return ERROR;
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
ERROR_STATUS Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count)
{ERROR_STATUS ERROR=E_OK;
	switch(Timer_CH_NO)
	{
	case(TIMER_0):
		if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
		{
			//TCNT0 = (0xFF - (uint8)Timer_Count); /* pre-load timer */
			TCNT0 = (uint8_t)Timer_Count; /* preload timer */
			switch (gsau8_mode[Timer_CH_NO])
			{
			case (TIMER_MODE):
				/* set pres-caller */
				switch (gsau8_preScaler[Timer_CH_NO])
				{
				case (TIMER_PRESCALER_NO):
					/* 1 */
               Clear_BIT(TCCR0,CS02);
               Clear_BIT(TCCR0,CS01);
               Set_BIT(TCCR0,CS00);
					break;
				case (TIMER_PRESCALER_8):
					/* 2 */
               Clear_BIT(TCCR0,CS02);
               Clear_BIT(TCCR0,CS00);
                Set_BIT(TCCR0,CS01);
					break;
				case (TIMER_PRESCALER_64):
					/* 3 */
               Clear_BIT(TCCR0,CS02);
               Set_BIT(TCCR0,CS01);
               Set_BIT(TCCR0,CS00);
					break;
				case (TIMER_PRESCALER_256):
					/* 4 */
               Clear_BIT(TCCR0,CS00);
               Clear_BIT(TCCR0,CS01);
               Set_BIT(TCCR0,CS02);
					break;
				case (TIMER_PRESCALER_1024):
					/* 5 */
                Set_BIT(TCCR0,CS00);
                Clear_BIT(TCCR0,CS01);
                Set_BIT(TCCR0,CS02);
					TCCR0 &= ~CS01;
					TCCR0 |= (CS02 | CS00);
					break;
				default:
					ERROR=E_NOK;
					break;
				}
			break;
			case (COUNTER_RISING_MODE):
				/* 7 */
              Set_BIT(TCCR0,CS02);
              Set_BIT(TCCR0,CS01);
              Set_BIT(TCCR0,CS00);
				break;
			case (COUNTER_FALLING_MODE):
				/* 6 */
            Set_BIT(TCCR0,CS02);
            Clear_BIT(TCCR0,CS00);
            Set_BIT(TCCR0,CS00);
				break;
			default:
				ERROR=E_NOK;
				break;
			}
		}
		else
		{
			ERROR=E_NOK;
		}
		break;
	case(TIMER_1):
		if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
		{
			TCNT1 = (0xFFFF - Timer_Count); /* pre-load timer */
			switch (gsau8_mode[Timer_CH_NO])
			{
			case (TIMER_MODE):
				/* set prescaler */
				switch (gsau8_preScaler[Timer_CH_NO])
				{
				case (TIMER_PRESCALER_NO):
					/* 1 */
               Clear_BIT(TCCR1B,CS12);
               Clear_BIT(TCCR1B,CS11);
               Set_BIT(TCCR1B,CS10);
					break;
				case (TIMER_PRESCALER_8):
					/* 2 */
               Clear_BIT(TCCR1B,CS12);
               Clear_BIT(TCCR1B,CS10);
               Set_BIT(TCCR1B,CS11);
					break;
				case (TIMER_PRESCALER_64):
					/* 3 */
               Clear_BIT(TCCR1B,CS12);
               Set_BIT(TCCR1B,CS10);
               Set_BIT(TCCR1B,CS11);
					break;
				case (TIMER_PRESCALER_256):
					/* 4 */
               Clear_BIT(TCCR1B,CS11);
               Clear_BIT(TCCR1B,CS10);
               Set_BIT(TCCR1B,CS12);
					break;
				case (TIMER_PRESCALER_1024):
					/* 5 */
               Clear_BIT(TCCR1B,CS11);
               Set_BIT(TCCR1B,CS10);
               Set_BIT(TCCR1B,CS12);
					break;
					default:
						ERROR=E_NOK;
						break;
				}
				break;
			case(COUNTER_RISING_MODE):
				/* 7 */
             Set_BIT(TCCR1B,CS11);
             Set_BIT(TCCR1B,CS10);
             Set_BIT(TCCR1B,CS12);
				break;
			case(COUNTER_FALLING_MODE):
				/* 6 */
             Set_BIT(TCCR1B,CS11);
             Set_BIT(TCCR1B,CS12);
             Clear_BIT(TCCR1B,CS10);
				break;
			default:
				ERROR=E_NOK;
				break;
			}
		}
		else
		{
			ERROR=E_NOK;
		}
		break;
	case(TIMER_2):
		if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
		{
			TCNT2 = (0xFF - (uint8_t)Timer_Count); /* pre-load timer */
			switch (gsau8_mode[Timer_CH_NO])
			{
			case (TIMER_MODE):
				/* set pre-scaler */
				switch (gsau8_preScaler[Timer_CH_NO])
				{
				case (TIMER_PRESCALER_NO):
					/* 1 */
                Set_BIT(TCCR2,CS22);
                Set_BIT(TCCR2,CS21);
                Set_BIT(TCCR2,CS20);
					break;
				case (TIMER_PRESCALER_8):
					/* 2 */
                Clear_BIT(TCCR2,CS20);
                Clear_BIT(TCCR2,CS22);
                Set_BIT(TCCR2,CS21);
					break;
				case (TIMER_PRESCALER_32):
					/* 3 */
               Clear_BIT(TCCR2,CS22);
               Set_BIT(TCCR2,CS20);
               Set_BIT(TCCR2,CS21);
					break;
				case (TIMER_PRESCALER_64):
					/* 4 */
               Set_BIT(TCCR2,CS22);
               Clear_BIT(TCCR2,CS20);
               Clear_BIT(TCCR2,CS21);
					break;
				case (TIMER_PRESCALER_128):
					/* 5 */
               Set_BIT(TCCR2,CS22);
               Set_BIT(TCCR2,CS20);
               Clear_BIT(TCCR2,CS21);
					break;
				case (TIMER_PRESCALER_256):
					/* 6 */
               Set_BIT(TCCR2,CS22);
               Set_BIT(TCCR2,CS21);
               Clear_BIT(TCCR2,CS20);
					break;
				case (TIMER_PRESCALER_1024):
					/* 7 */
                Set_BIT(TCCR2,CS22);
                Set_BIT(TCCR2,CS21);
                Set_BIT(TCCR2,CS20);
					 break;
				default:
					ERROR=E_NOK;
					break;
				}
				break;
			case(COUNTER_RISING_MODE):
				/* Implement your algorithm */
				break;
			case(COUNTER_FALLING_MODE):
				/* Implement your algorithm */
				break;
			default:
				ERROR=E_NOK;
			}
		}
		else
		{
			ERROR=E_NOK;
		}
		break;
	default:
		ERROR=E_NOK;
		break;
	}
	return ERROR;
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
ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO)
{ERROR_STATUS ERROR=E_OK;
	switch(Timer_CH_NO)
	{
	case(TIMER_0):
		if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
		{  Set_BIT(TCCR0,CS02);
   		Set_BIT(TCCR0,CS01);
   		Set_BIT(TCCR0,CS00);
		}
		else
		{
			ERROR=E_NOK;
		}
		break;
	case(TIMER_1):
		if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
		{  Clear_BIT(TCCR0,CS12);
   		Clear_BIT(TCCR0,CS11);
   		Clear_BIT(TCCR0,CS10);
		}
		else
		{
			ERROR=E_NOK;
		}
		break;
	case(TIMER_2):
		if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
		{   Clear_BIT(TCCR2,CS20);
   		Clear_BIT(TCCR2,CS22);
   		Clear_BIT(TCCR2,CS21);
		}
		else
		{
			ERROR=E_NOK;
		}
		break;
	default:
		ERROR=E_NOK;
		break;
	}
	return ERROR;
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
{ERROR_STATUS ERROR=E_OK;
	if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
	{
		*Data = not_rasied;
		switch (Timer_CH_NO) 
{
		case (TIMER_0):
			if((BIT_IS_SET(TIFR,TOV0)))
			{
				*Data = Rasied;
			}
			else
			{
				*Data = not_rasied;
			}
			break;
		case (TIMER_1):
			if((BIT_IS_SET(TIFR,TOV1)))
			{
				*Data = Rasied;
			}
			else
			{
				*Data = not_rasied;
			}
			break;
		case (TIMER_2):
			if((BIT_IS_SET(TIFR,TOV2)))
			{
				*Data = Rasied;
			}
			else
			{
				*Data = not_rasied;
			}
			break;
		default:
			ERROR=E_NOK;
			break;
		}
	}
	else
	{
		ERROR=E_NOK;
	}
	return ERROR;
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
ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO,volatile uint16_t* Data)
{ERROR_STATUS ERROR=E_OK;
	if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
	{
		*Data = 0;
		switch (Timer_CH_NO)
		{
		case (TIMER_0):
			*Data = TCNT0;
			break;
		case (TIMER_1):
			*Data = TCNT1;
			break;
		case (TIMER_2):
			*Data = TCNT2;
			break;
		default:
			ERROR=E_NOK;
			break;
		}
	}
	else
	{
		ERROR=E_NOK;
	}
	return ERROR;
}


ERROR_STATUS Timer_SetValue(uint8_t Timer_CH, uint8_t* Data)
{ERROR_STATUS ERROR=E_OK;
	switch(Timer_CH)
	{
		case TIMER_0:
		          TCNT0=*Data;
				  break; 
		case TIMER_1:
		           TCNT1=*Data;
		           break;
		case TIMER_2:
		           TCNT2=*Data;
		           break;
		default:
		       ERROR=E_NOK;
			   break;
	}
	
	return ERROR;
}

ERROR_STATUS Timer_Setcallback(timer_Cbk pf)
{
	ERROR_STATUS au8_timererror=E_OK;
	if(pf==NULL)
	{
		au8_timererror=E_NOK;
	}
	gpf_timercbk =pf;
	return au8_timererror;
}


ISR(TIMER0_OVF_vect)
{
	
gpf_timercbk();

}