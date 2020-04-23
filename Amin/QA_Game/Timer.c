#include "Timer.h"
#include "Interrupt.h"


static volatile void (*g_TIMER0_OVF_callBackPtr)(void);
static volatile void (*g_TIMER0_CMP_callBackPtr)(void);
static volatile void (*g_TIMER1_OVF_callBackPtr)(void);
static volatile void (*g_TIMER1_CMPA_callBackPtr)(void);
static volatile void (*g_TIMER1_CMPB_callBackPtr)(void);
static volatile void (*g_TIMER2_OVF_callBackPtr)(void);
static volatile void (*g_TIMER2_CMP_callBackPtr)(void);

/*********************************************************
 *					Timer0 COMP Interrupt				 *
 *********************************************************/
void __vector_10 (void)
{
	if(g_TIMER0_CMP_callBackPtr != NULL)
	{
		g_TIMER0_CMP_callBackPtr();
	}
}

/*********************************************************
 *					Timer0 OVF Interrupt				 *
 *********************************************************/
void __vector_11 (void)
{
	if(g_TIMER0_OVF_callBackPtr != NULL)
	{
		g_TIMER0_OVF_callBackPtr();
	}
}

/*********************************************************
 *					Timer1 OVF Interrupt				 *
 *********************************************************/
void __vector_9 (void)
{
	if(g_TIMER1_OVF_callBackPtr != NULL)
	{
		g_TIMER1_OVF_callBackPtr();
	}

}

/*********************************************************
 *					Timer1 COMPB Interrupt				 *
 *********************************************************/
void __vector_8 (void)
{
	if(g_TIMER1_CMPB_callBackPtr != NULL)
	{
		g_TIMER1_CMPB_callBackPtr();
	}

}

/*********************************************************
 *					Timer1 COMPA Interrupt				 *
 *********************************************************/
void __vector_7 (void)
{
	if(g_TIMER1_CMPA_callBackPtr != NULL)
	{
		g_TIMER1_CMPA_callBackPtr();
	}

}



/*********************************************************
 *					Timer2 OVF Interrupt				 *
 *********************************************************/
void __vector_5 (void)
{
	if(g_TIMER2_OVF_callBackPtr != NULL)
	{
		g_TIMER2_OVF_callBackPtr();
	}
}

/*********************************************************
 *					Timer2 CMP Interrupt				 *
 *********************************************************/
void __vector_4 (void)
{
	if(g_TIMER2_CMP_callBackPtr != NULL)
	{
		g_TIMER2_CMP_callBackPtr();
	}
}


static uint8  gu8_timer0PreScaler=0;
static uint8  gu8_timer1PreScaler=0;
static uint8  gu8_timer2PreScaler=0;

/*Describtion: this function init the timer with user configs timer 0,1,2 and timer mode and prescaler   */
ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg){
	switch(Timer_cfg->Timer_CH_NO){
		case TIMER_CH0:
		TCCR0 = (TCCR0 & 0xB7) |(Timer_cfg->Timer_Mode);
		switch(Timer_cfg->Timer_Polling_Or_Interrupt){
			case TIMER_POLLING_MODE	:
			TIMSK = (TIMSK & 0xFC) | (T0_POLLING);
			break;
			case TIMER_INTERRUPT_MODE:
			TIMSK = (TIMSK & 0xFC) | (T0_INTERRUPT_NORMAL);
			break;
		}
		switch (Timer_cfg->Timer_Prescaler){
			case TIMER_NO_CLOCK:
			gu8_timer0PreScaler=T0_NO_CLOCK;
			break;
			case TIMER_PRESCALER_NO:
			gu8_timer0PreScaler=T0_PRESCALER_NO;
			break;
			case TIMER_PRESCALER_8:
			gu8_timer0PreScaler=T0_PRESCALER_8;
			break;
			case TIMER_PRESCALER_32:
			return ERROR;
			break;
			case TIMER_PRESCALER_64:
			gu8_timer0PreScaler=T0_PRESCALER_64;
			break;
			case TIMER_PRESCALER_128:
			return ERROR;
			break;
			case TIMER_PRESCALER_256:
			gu8_timer0PreScaler=T0_PRESCALER_256;
			break;
			case TIMER_PRESCALER_1024:
			gu8_timer0PreScaler=T0_PRESCALER_1024;
			break;
		}
		return NO_ERROR;
		break;


		case TIMER_CH1:
		TCCR1|=(Timer_cfg->Timer_Mode);
		switch(Timer_cfg->Timer_Polling_Or_Interrupt){
			case TIMER_POLLING_MODE	:
			TIMSK = (TIMSK & 0xC3) | (T1_POLLING);
			break;
			case TIMER_INTERRUPT_MODE:
			TIMSK = (TIMSK & 0xC3) | (T1_INTERRUPT_CMP_1A);
			break;
		}
		switch (Timer_cfg->Timer_Prescaler){
			case TIMER_NO_CLOCK:
			gu8_timer1PreScaler=T1_NO_CLOCK;
			break;
			case TIMER_PRESCALER_NO:
			gu8_timer1PreScaler=T1_PRESCALER_NO;
			break;
			case TIMER_PRESCALER_8:
			gu8_timer1PreScaler=T1_PRESCALER_8;
			break;
			case TIMER_PRESCALER_32:
			return ERROR;
			break;
			case TIMER_PRESCALER_64:
			gu8_timer1PreScaler=T1_PRESCALER_64;
			break;
			case TIMER_PRESCALER_128:
			return ERROR;
			break;
			case TIMER_PRESCALER_256:
			gu8_timer1PreScaler=T1_PRESCALER_256;
			break;
			case TIMER_PRESCALER_1024:
			gu8_timer1PreScaler=T1_PRESCALER_1024;
			break;
		}
		return NO_ERROR;
		break;


		case TIMER_CH2:
		TCCR2 = (TCCR2 & 0xB7) |(Timer_cfg->Timer_Mode);
		switch(Timer_cfg->Timer_Polling_Or_Interrupt){
			case TIMER_POLLING_MODE	:
			TIMSK = (TIMSK & 0x3F) | (T2_POLLING);
			break;
			case TIMER_INTERRUPT_MODE:
			TIMSK = (TIMSK & 0x3F) | (T2_INTERRUPT_NORMAL);
			break;
		}
		switch (Timer_cfg->Timer_Prescaler){
			case TIMER_NO_CLOCK:
			gu8_timer2PreScaler=T2_NO_CLOCK;
			break;
			case TIMER_PRESCALER_NO:
			gu8_timer2PreScaler=T2_PRESCALER_NO;
			break;
			case TIMER_PRESCALER_8:
			gu8_timer2PreScaler=T2_PRESCALER_8;
			break;
			case TIMER_PRESCALER_32:
			gu8_timer2PreScaler=T2_PRESCALER_32;
			break;
			case TIMER_PRESCALER_64:
			gu8_timer2PreScaler=T2_PRESCALER_64;
			break;
			case TIMER_PRESCALER_128:
			gu8_timer2PreScaler=T2_PRESCALER_128;
			break;
			case TIMER_PRESCALER_256:
			gu8_timer2PreScaler=T2_PRESCALER_256;
			break;
			case TIMER_PRESCALER_1024:
			gu8_timer2PreScaler=T2_PRESCALER_1024;
			break;
		}
		return NO_ERROR;
		break;
	}


	return ERROR;
}


/*Describtion: this function start the  timer by appling clock to it   */
ERROR_STATUS Timer_Start(uint8 Timer_CH_NO){

	switch(Timer_CH_NO){
		case TIMER_CH0:
		TCCR0 = (TCCR0 & 0xF8) | (gu8_timer0PreScaler);
		//TCNT0=Timer_Count;
		return NO_ERROR;
		break;

		case TIMER_CH1:
		TCCR1B = (TCCR1B & 0xF8) | (gu8_timer1PreScaler);
	//	TCNT1 = Timer_Count;
		return NO_ERROR;
		break;

		case TIMER_CH2:
		TCCR2 = (TCCR2 & 0xF8) | (gu8_timer2PreScaler);
	//	TCNT2 =Timer_Count ;
		return NO_ERROR;
		break;
	}
	return ERROR;
}

ERROR_STATUS Timer_GetValue(uint8 Timer_CH_NO, uint16* Data){
	switch(Timer_CH_NO){
		case TIMER_CH0:
		*Data=TCNT0;
		return NO_ERROR;
		break;

		case TIMER_CH1:
		*Data=TCNT1;
		return NO_ERROR;
		break;

		case TIMER_CH2:
		*Data=TCNT2;
		return NO_ERROR;
		break;
	}
	return ERROR;
}

/*Describtion: this function set value for timer in case of compare match mode  */
ERROR_STATUS Timer_SetValue(uint8 Timer_CH_NO, uint16 Data){
	switch(Timer_CH_NO){
		case TIMER_CH0:
		OCR0 = Data;
		return NO_ERROR;
		break;

		case TIMER_CH1:
		OCR1A = Data;
		return NO_ERROR;
		break;

		case TIMER_CH2:
		OCR2= Data;
		return NO_ERROR;
		break;
	}
	return ERROR;
}

/*Describtion: this function stop timer fby applying no clock  */
ERROR_STATUS Timer_Stop(uint8 Timer_CH_NO){
	switch(Timer_CH_NO){
		case TIMER_CH0:
		TCCR0&= ~((1 << CS00) | (1 << CS01) | (1 << CS02));
		return NO_ERROR;
		break;

		case TIMER_CH1:
		TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));
		return NO_ERROR;
		break;

		case TIMER_CH2:
		TCCR2 &= ~((1 << CS20) | (1 << CS21) | (1 << CS22));
		return NO_ERROR;
		break;
	}
	return ERROR;
}

void TIMER0_OVF_setCallBack(void (*COPY_TIMER0_OVF_callBackPtr)(void))
{
	g_TIMER0_OVF_callBackPtr = COPY_TIMER0_OVF_callBackPtr;
}

void TIMER0_CMP_setCallBack(void (*COPY_TIMER0_CMP_callBackPtr)(void))
{
	g_TIMER0_CMP_callBackPtr = COPY_TIMER0_CMP_callBackPtr;
}

void TIMER1_OVF_setCallBack(void (*COPY_TIMER1_OVF_callBackPtr)(void))
{
	g_TIMER1_OVF_callBackPtr = COPY_TIMER1_OVF_callBackPtr;
}

void TIMER1_CMPA_setCallBack(void (*COPY_TIMER1_CMPA_callBackPtr)(void))
{
	g_TIMER1_CMPA_callBackPtr = COPY_TIMER1_CMPA_callBackPtr;
}

void TIMER1_CMPB_setCallBack(void (*COPY_TIMER1_CMPB_callBackPtr)(void))
{
	g_TIMER1_CMPB_callBackPtr = COPY_TIMER1_CMPB_callBackPtr;
}

void TIMER2_OVF_setCallBack(void (*COPY_TIMER2_OVF_callBackPtr)(void))
{
	g_TIMER2_OVF_callBackPtr = COPY_TIMER2_OVF_callBackPtr;
}

void TIMER2_CMP_setCallBack(void (*COPY_TIMER2_CMP_callBackPtr)(void))
{
	g_TIMER2_CMP_callBackPtr = COPY_TIMER2_CMP_callBackPtr;
}
