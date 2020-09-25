/*
 ============================================================================
 Name        : SwICU.c
 Author      : Muhammed Gamal
 Description : this file include the implementation of the SW ICU driver
 ============================================================================
 */


/*********************************includes**********************************/
#include "ICU.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define NULL_Ptr ((void*)0)
#define TIMER_TICK 64
#define CLEAR 0
#define FIRST_ENTRY 1
#define SECOND_ENTRY 2
#define THIRD_ENTRY 3
#define FORTH_ENTRY 4
/***************************************************************************/


/******************************global variables*****************************/


volatile uint8_t g8_SwICU_value;
uint8_t g8_edgeCount;
uint16_t g16_timeHigh;
uint16_t g16_timePeriod;
uint16_t g16_timePeriodPlusHigh;
/***************************************************************************/



/************************************************************************************
* Function Name: Icu_Init
* Parameters (in): Icu_cfg : pointer to structure of type Icu_cfg_s
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: Initializes the ICU by initializing the timer
* and enabling the global interrupt
************************************************************************************/
ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg)
{
	ERROR_STATUS u8_status;
	if(Icu_Cfg == NULL_Ptr)
	{
		u8_status |= E_NOk;
	}
	else
	{
		St_TimerCfg timer2_stru_init=
			{
				timer2_stru_init.Timer_CH_NO=Timer_2,
				timer2_stru_init.Timer_Mode=TIMER_MODE,
				timer2_stru_init.Timer_Polling_Or_Interrupt=T2_POLLING,
				timer2_stru_init.Timer_Prescaler=T2_PRESCALER_1024,
			};

		switch(Icu_Cfg->ICU_Ch_No)
		{
		case ICU_CH0:
			u8_status |= INT0_Init(RISIGING_EDGE);
			break;

		case ICU_CH1:
			u8_status |= INT1_Init(RISIGING_EDGE);
			break;

		case ICU_CH2:
			u8_status |= INT2_Init(RISIGING_EDGE);
			break;

		default:
			u8_status|= E_NOk;
			break;
		}

		switch(Icu_Cfg->ICU_Ch_Timer)
		{
		case Timer_0:
			/*cauldn't use timer0 since it used to perform another functionality*/
			u8_status |= E_NOk;
			break;

		case Timer_1:
			/*cauldn't use timer1 since it used to perform another functionality*/
			u8_status |= E_NOk;
			break;

		case Timer_2:
			u8_status |= Timer_Init(&timer2_stru_init);
			break;

		default:
			u8_status |= E_NOk;
			break;
		}

		if(u8_status == E_ok)
		{
			u8_status = E_ok;
		}
		else
		{
			u8_status = E_NOk;
		}
	}
	return u8_status;
}



/************************************************************************************
* Function Name: Icu_ReadTime
* Parameters (in): Icu_cfg : Icu_Channel- ICU timer channel
*                            Icu_EdgeToEdge- edges type to calculate pusle
* Parameters (inout): None
* Parameters (out): Icu_Time : pointer to uint32 variable to give the time
* from falling edge to rising edge
* Return value: u8_error- variable that describe the error status
* Description: calculates the time between 2 edges
************************************************************************************/
ERROR_STATUS Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint32_t * Icu_Time)
{
	ERROR_STATUS u8_status;
	switch(Icu_Channel)
	{
	case Timer_0:
		switch(Icu_EdgeToEdge)
		{
		case ICU_RISE_TO_RISE:
			Icu_setCallBack(Rising_EdgeFunc);
			*Icu_Time=(g16_timePeriod)*TIMER_TICK;
			break;

		case ICU_RISE_TO_FALL:
			Icu_setCallBack(Rising_EdgeFunc);
			*Icu_Time=(g16_timeHigh)*TIMER_TICK;
			break;

		case ICU_FALE_TO_RISE:
			Icu_setCallBack(Rising_EdgeFunc);
			*Icu_Time=(g16_timePeriod-g16_timeHigh)*TIMER_TICK;
			break;

		default:
			u8_status |= E_NOk;
			break;
		}
	break;

	case Timer_1:
		/*no need to handle timer1 for ICU since it is used to perform another functionality*/
		u8_status |= E_NOk;
	break;

	case Timer_2:
		switch(Icu_EdgeToEdge)
		{
		case ICU_RISE_TO_RISE:
			//u8_status |= Icu_setCallBack(Rising_EdgeFunc);
			Icu_setCallBack(Rising_EdgeFunc);
			*Icu_Time=(g16_timePeriod)*TIMER_TICK;
			break;

		case ICU_RISE_TO_FALL:
			//u8_status |= Icu_setCallBack(Rising_EdgeFunc);
			Icu_setCallBack(Rising_EdgeFunc);
			*Icu_Time=(g16_timeHigh)*TIMER_TICK;
			break;

		case ICU_FALE_TO_RISE:
			//u8_status |= Icu_setCallBack(Rising_EdgeFunc);
			Icu_setCallBack(Rising_EdgeFunc);
			*Icu_Time=(g16_timePeriod-g16_timeHigh)*TIMER_TICK;
			break;

		default:
			u8_status |= E_NOk;
			break;
		}
	break;

	default:
		u8_status |= E_NOk;
	}

	if(u8_status == E_ok)
	{
		u8_status = E_ok;
	}
	else
	{
		u8_status = E_NOk;
	}

	return u8_status;
}



/************************************************************************************
* Function Name: Icu_setCallBack
* Parameters (in): a_ptr- pointer that points to function that will be called when the interrupt occurs
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: this function sets the pointer to the callbacked function
************************************************************************************/
ERROR_STATUS Icu_setCallBack(void(*a_ptr)(void))
{
	ERROR_STATUS u8_status;
	if(a_ptr == NULL_Ptr)
	{
		u8_status |= E_NOk;
	}
	else
	{
		/* Save the address of the Call back function in a global variable */
		g_callBackPtr_INT2 = a_ptr;
		u8_status |= E_ok;
	}

	if(u8_status == E_ok)
	{
		u8_status = E_ok;
	}
	else
	{
		u8_status = E_NOk;
	}

	return u8_status;
}



/************************************************************************************
* Function Name: Rising_EdgeFunc
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: u8_error- variable that describe the error status
* Description: this function will be called when the interrupt occurs
************************************************************************************/
void Rising_EdgeFunc(void)
{
	ERROR_STATUS u8_status;
	g8_edgeCount++;
	if(g8_edgeCount == FIRST_ENTRY)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		u8_status |= Timer_Clear(Timer_2);
		u8_status |= Timer_Start(Timer_2,TIMER2_NUMBER_OF_TICKS);
		/* Detect falling edge */
		u8_status |= INT2_SetEdge(FALLING_EDGE);
	}
	else if(g8_edgeCount == SECOND_ENTRY)
	{
		/* Store the High time value */
		u8_status |= Timer_GetValue(Timer_2,&g16_timeHigh);
		/* Detect rising edge */
		u8_status |= INT2_SetEdge(RISIGING_EDGE);
	}
	else if(g8_edgeCount == THIRD_ENTRY)
	{
		/* Store the Period time value */
		u8_status |= Timer_GetValue(Timer_2,&g16_timePeriod);
		/* Detect falling edge */
		u8_status |= INT2_SetEdge(FALLING_EDGE);
	}
	else if(g8_edgeCount == FORTH_ENTRY)
	{
		/* Store the Period time value + High time value */
		g16_timePeriodPlusHigh = TCNT2;
		u8_status |= Timer_GetValue(Timer_2,&g16_timePeriodPlusHigh);
		/* Clear the timer counter register to start measurements again */
		u8_status |= Timer_Clear(Timer_2);
		/* Detect rising edge */
		u8_status |= INT2_SetEdge(RISIGING_EDGE);
		g8_edgeCount=CLEAR;
	}

	if(u8_status == E_ok)
	{
		u8_status = E_ok;
	}
	else
	{
		u8_status = E_NOk;
	}

	/*this line will be hashed tell the coming modification*/
	/*return u8_status;*/
}

