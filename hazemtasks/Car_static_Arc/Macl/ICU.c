/*
* ICU.c
*
* Created: 2/18/2020 10:27:51 AM
*  Author: Hazem
*/
/************************************************************************/
/*				 INCLUDES			        							*/
/************************************************************************/
#include "icu.h"

/***********************************************/
/***************Golbal static variable*********/
volatile static uint8_t  gu8_Flag;
volatile static uint16_t gu8_risetofall;
volatile static uint16_t gu8_falltorise;
volatile static uint16_t gu8_risetorise;

/************************************************************************/
/*				            API Implementation                         */
/************************************************************************/


/**************************************************************************
 * Function 	: Icu_Init                                                *
 * Input 		: Icu_cfg : pointer to structure of type Icu_cfg_s        *
 * Return 		: value of type ERROR_STATUS							  *
 * 				  which is one of the following values:					  *
 * 				  - E_OK  : initialized successfully					  *
 *				  - E_NOK : not initialized successfully				  *
 * Description  : Initializes the ICU by initializing the timer			  *
 * 				  and enabling the global interrupt						  *
 **************************************************************************/
ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg)
{ERROR_STATUS ERROR=E_OK;	
	if(NULL != Icu_Cfg)
	{
		uint8_t dummyFlag;
		switch(Icu_Cfg->ICU_Ch_Timer)
		{
		case (ICU_TIMER_CH0):
			if(Timer_GetStatus(TIMER_0, &dummyFlag) == E_NOK)
			{
				Timer_cfg_s ST_Timer0 = {
				ST_Timer0.Timer_CH = TIMER_0,
				ST_Timer0.Timer_Mode = TIMER_MODE,
				ST_Timer0.Timer_Int_MODE = TIMER_INTERRUPT_MODE,
				ST_Timer0.Timer_Prescaler = TIMER_PRESCALER_1024};
				if(Timer_Init(&ST_Timer0) == E_OK)
				{
					if(Icu_Cfg->ICU_Ch_No == ICU_CH2)
					{
						/*Global INT ENABLE*/
						sei();
						/*rising edge*/
                  Set_BIT(MCUCSR,ISC2);
											
					}
				}
				else
				{
					ERROR=E_NOK;
				}
			}
			else
			{
				ERROR=E_NOK;
			}
			break;
		case (ICU_TIMER_CH1):
			break;
		case (ICU_TIMER_CH2):
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


/***************************************************************************
 * Function		: Icu_ReadTime
 * Input		: 
 *				Icu_Channel --> ICU timer channel
 *									- ICU_TIMER_CH0
 *									- ICU_TIMER_CH1
 *									- ICU_TIMER_CH2
 *				Icu_EdgeToEdge -- > edges to calculate pusle time between:
 *									- ICU_RISE_TO_RISE
 *									- ICU_RISE_TO_FALL
 *									- ICU_FALE_TO_RISE					   *
 * Output 		: Icu_Time : pointer to uint32 variable to give the time   *
 * 				  from falling edge to rising edge						   *
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : uccessful									   *
 *				  - E_NOK : not successful								   *
 * Description	: calculates the time between 2 edges				       *
 ***************************************************************************/
 ERROR_STATUS Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint32_t * Icu_Time)
 {
	 ERROR_STATUS ERROR=E_OK;
	 switch(Icu_Channel)
	 {
		 case ICU_CH0:
		 		 	ERROR=E_NOK;
					break;  				  	 
		 case ICU_CH1:
		            ERROR=E_NOK;
					break;
		 case ICU_CH2:
		           GICR|=(1<<INT2);
		           break;
		default:
		       ERROR=E_NOK;
			   break;		   
	 }
 
   
	 switch(Icu_EdgeToEdge)
	 {
		 case ICU_RISE_TO_RISE:
		       *Icu_Time=gu8_risetorise;
			   break;
		 case ICU_RISE_TO_FALL:
		      *Icu_Time=gu8_risetofall;
		       break;
		 case ICU_FALE_TO_RISE:
		      *Icu_Time=gu8_falltorise;
		      break;
		 default:
		      ERROR=E_NOK;
			  break;
	 }
	 
	 
	 
	 return ERROR;
 }
 
 
 
 
 ISR(INT2_vect)
{

	 if(gu8_Flag==0)
	  { 
		 Timer_Start(TIMER_0,INIT_TINMER);	
       TOGGEL_BIT(MCUCSR,ISC2);
		 gu8_Flag++;	 
	 }
	 else
	 {
		 Timer_Stop(TIMER_0);
       Timer_GetValue(TIMER_0,&gu8_risetofall);
		 Timer_SetValue(TIMER_0,INIT_TINMER);
       gu8_Flag=INIT_TINMER;
       TOGGEL_BIT(MCUCSR,ISC2);	 
	 }
	 
	 
	 
 }