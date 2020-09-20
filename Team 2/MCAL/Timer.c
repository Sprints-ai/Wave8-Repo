	/*
 ============================================================================
 Name        : Timer.c
 Author      : Muhammed Gamal
 Description :this file contains the timer driver
 ============================================================================
 */


/*********************************includes**********************************/
#include "Timer.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define TIMER_ICR1_TOP_VALUE 2499
#define NULL_Ptr ((void*)0)
#define TIMER0_MAX_COUNT 256
#define TIMER2_MAX_COUNT 256
#define TIMER1_MAX_COUNT 65536
#define FLAG_RAISED 1
#define FLAG_DOWN   0
#define CLEAR 0
#define ONE 1
#define MASK_HIGH_BYTE 0xFF00
#define MASK_LOW_BYTE 0x00FF
#define ONE_BYTE 8
/***************************************************************************/


/******************************global variables*****************************/
uint8_t g8_TCNT0_value_Swpwm_ISR;
static uint16_t T0_PrescallerValue;
static uint16_t T1_PrescallerValue;
static uint16_t T2_PrescallerValue;
/***************************************************************************/




/************************************************************************************
* Function Name: Timer_Init
* Parameters (in): Timer_cfg- Pointer to a structure of type St_TimerCfg contains the information
* needed to initialize the timer
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: Initiates the module
************************************************************************************/
ERROR_STATUS Timer_Init(St_TimerCfg* Timer_cfg)
{
	uint8_t u8_status;
	if(Timer_cfg == NULL_Ptr)
	{
		u8_status=E_NOk;
	}
	else
	{
		TIMSK = Timer_cfg->Timer_Polling_Or_Interrupt;
		switch(Timer_cfg->Timer_CH_NO)
		{
			case Timer_0:
				TCCR0 = Timer_cfg->Timer_Mode | (ONE<<FOC0);
				T0_PrescallerValue=Timer_cfg->Timer_Prescaler;
				TIMSK=Timer_cfg->Timer_Polling_Or_Interrupt;
				u8_status=E_ok;
				break;
			case Timer_1:
				TCCR1A =Timer_cfg->Timer_Mode | (ONE<<FOC1A) | (ONE<<FOC1B);
				T1_PrescallerValue=Timer_cfg->Timer_Prescaler;
				TIMSK=Timer_cfg->Timer_Polling_Or_Interrupt;
				u8_status=E_ok;
				break;
			case Timer_2:
				TCCR2 =Timer_cfg->Timer_Mode | (ONE<<FOC0);
				T2_PrescallerValue=Timer_cfg->Timer_Prescaler;
				TIMSK=Timer_cfg->Timer_Polling_Or_Interrupt;
				u8_status=E_ok;
				break;
			default:
				u8_status=E_NOk;
		}
	}
	return u8_status;
}





/************************************************************************************
* Function Name: Timer_Start
* Parameters (in): Timer_CH_NO: The channel number of the timer needed to be started
*                  Timer_Count: The start value of the timer
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: This function starts the needed timer
************************************************************************************/
ERROR_STATUS Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count)
{
	uint8_t u8_status;
	switch(Timer_CH_NO)
	{
		case Timer_0:
			if(Timer_Count<=TIMER0_MAX_COUNT)
			{
				TCNT0 = (TIMER0_MAX_COUNT-Timer_Count);
				TCCR0 |= T0_PrescallerValue;
				u8_status=E_ok;
			}
			else
			{
				u8_status=E_NOk;
			}
			break;

		case Timer_1:
			if(Timer_Count<=TIMER1_MAX_COUNT)
			{
				TCNT1H = (((TIMER1_MAX_COUNT-Timer_Count) & MASK_HIGH_BYTE)>>ONE_BYTE);
				TCNT1L = ((TIMER1_MAX_COUNT-Timer_Count) & MASK_LOW_BYTE);
				TCCR1B = T1_PrescallerValue;
				u8_status=E_ok;
			}
			else
			{
				u8_status=E_NOk;
			}
			break;

		case Timer_2:
			if(Timer_Count<=TIMER0_MAX_COUNT)
			{
				TCNT2 = (TIMER2_MAX_COUNT-Timer_Count);
				TCCR2 |= T2_PrescallerValue;
				u8_status=E_ok;
			}
			else
			{
				u8_status=E_NOk;
			}

			break;

		default:
			u8_status=E_NOk;
	}
	return u8_status;
}




/************************************************************************************
* Function Name: Timer_Start
* Parameters (in): Timer_CH_NO: The channel number of the timer needed to be stopped
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: This function stops the needed timer
************************************************************************************/
ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO)
{
	uint8_t u8_status;
	switch(Timer_CH_NO)
	{
		case Timer_0:
			TCCR0 = T0_NO_CLOCK;
			u8_status=E_ok;
			break;
		case Timer_1:
			TCCR1 = T1_NO_CLOCK;
			u8_status=E_ok;
			break;
		case Timer_2:
			TCCR2 = T2_NO_CLOCK;
			u8_status=E_ok;
			break;
		default:
			u8_status=E_NOk;
			break;
	}
	return u8_status;
}




/************************************************************************************
* Function Name: Timer_GetStatus
* Parameters (in): Timer_CH_NO- The channel number of the timer needed to get its status
* Parameters (inout): None
* Parameters (out): Data- A variable of type bool returns if the flag of the timer is raised or not
* Return value: u8_error- variable that describe the error status
* Description: This function is used to return if the flag of the timer is raised or not
************************************************************************************/
ERROR_STATUS Timer_GetStatus(uint8_t Timer_CH_NO, bool_t* Data)
{
	uint8_t u8_status;
	switch(Timer_CH_NO)
	{
		case Timer_0:
			if(TIFR & (ONE<<TOV0))
			{
				*Data=FLAG_RAISED;
			}
			else
			{
				*Data=FLAG_DOWN;
			}
			u8_status=E_ok;
			break;

		case Timer_1:
			if(TIFR & (ONE<<TOV1))
			{
				*Data=FLAG_RAISED;
			}
			else
			{
				*Data=FLAG_DOWN;
			}
			u8_status=E_ok;
			break;

		case Timer_2:
			if(TIFR & (ONE<<TOV2))
			{
				*Data=FLAG_RAISED;
			}
			else
			{
				*Data=FLAG_DOWN;
			}
			u8_status=E_ok;
			break;

		default:
			u8_status=E_NOk;
	}
	return u8_status;
}




/************************************************************************************
* Function Name: Timer_GetValue
* Parameters (in): Timer_CH_NO- The channel number of the timer needed to get its status
* Parameters (inout): None
* Parameters (out): Data- A variable of type bool returns if the flag of the timer is raised or not
* Return value: u8_error- variable that describe the error status
* Description: This function is used to return the value of the timer
************************************************************************************/
ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO,uint16_t* Data)
{
	uint8_t u8_status;
	switch(Timer_CH_NO)
	{
		case Timer_0:
			*Data = TCNT0;
			u8_status=E_ok;
			break;
		case Timer_1:
			*Data = TCNT1;
			u8_status=E_ok;
			break;
		case Timer_2:
			*Data = TCNT2;
			u8_status=E_ok;
			break;
		default:
			u8_status=E_NOk;
	}
	return u8_status;
}




/************************************************************************************
* Function Name: Timer_Clear
* Parameters (in): Timer_CH_NO: The channel number of the timer needed to get its value
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: This function is used to reset the TCNTX register value
************************************************************************************/
ERROR_STATUS Timer_Clear(uint8_t Timer_CH_NO)
{
	uint8_t u8_status;
	switch(Timer_CH_NO)
	{
		case Timer_0:
			TCNT0= CLEAR;
			u8_status=E_ok;
			break;
		case Timer_1:
			TCNT1 = CLEAR;
			u8_status=E_ok;
			break;
		case Timer_2:
			TCNT2 = CLEAR;
			u8_status=E_ok;
			break;
		default:
			u8_status=E_NOk;
			break;
	}
	return u8_status;
}



/************************************************************************************
* Function Name: Timer_DeInit
* Parameters (in): Timer_CH_NO: The channel number of the timer needed to get its value
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: This function is used to de-initialize TIMERX
************************************************************************************/
ERROR_STATUS Timer_DeInit(uint8_t Timer_CH_NO)
{
	uint8_t u8_status;
	switch(Timer_CH_NO)
	{
		case Timer_0:
			TCNT0 = CLEAR;
			TIMSK &= ~(1<<TOIE0) & ~(1<<OCIE0);
			TCCR0 = CLEAR;
			u8_status=E_ok;
			break;
		case Timer_1:
			TCNT1 = CLEAR;
			TIMSK &= ~(1<<TOIE1) & ~(1<<OCIE1B) & ~(1<<OCIE1A) & ~(1<<TICIE1);
			TCCR1 = CLEAR;
			u8_status=E_ok;
			break;
		case Timer_2:
			TCNT2 = CLEAR;
			TIMSK &= ~(1<<TOIE2) & ~(1<<OCIE2);
			TCCR2 = CLEAR;
			u8_status=E_ok;
			break;
		default:
			u8_status=E_NOk;
			break;
	}
	return u8_status;
}




/**************************************************************************************
                                 TIMERS ISRs
**************************************************************************************/


