
/*
 * PWM.c
 *
 * Created: 2/17/2020 8:05:11 PM
 *  Author: Ehab , Ramadan , Reem , Eman
 */ 

#include "PWM.h"
#include "../Infrastructure/Errors.h"

static uint8_t gu8_PWM_InitFlag = FALSE ;
static uint8_t gu8_PWM0_StartFlag = FALSE;
static uint8_t gu8_PWM1A_StartFlag = FALSE;
static uint8_t gu8_PWM1B_StartFlag = FALSE;
static uint8_t gu8_PWM2_StartFlag = FALSE;
 
 /**
 * Description: Initializes the hardware PWM based on a pre-configured struct
 * @param Timer_cfg : Pointer to the configuration struct 
 * @return function status 
 */
ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg)
{
	ERROR_STATUS ERR = E_OK;
	gu8_PWM_InitFlag = TRUE;
	
	if(Pwm_Cfg == NULL)
	{
		ERR = ERROR_NULL_POINTER;
	}
	else
	{
		switch(Pwm_Cfg->Channel)
		{
			case PWM_CH0:
			TCCR0 |= (WGM00 | COM01 | COM00);
			PORTB_DIR |= OC0 ;
			break;
			
			case PWM_CH1A:
			TCCR1 |= (WGM10 | COM1A1);
			PORTD_DIR |= OC1A;
			break;
			
			case PWM_CH1B:
			TCCR1 |= (WGM10 | COM1B1);
			PORTD_DIR |= OC1B;
			break;
			
			case PWM_CH2:
			TCCR2 |= (WGM20 | COM21);
			PORTD_DIR |= OC2;
			break;
			
			default:
			ERR = ERROR_INVALID_PARAMETER;
			break;
			
		}
	}
	
	return ERR;
}

/**
 * Description: Starts generating the PWM signal on the corresponding pins
 * Note: Phase Correct PWM only 
 * @param Channel : The channel to generate the PWM signal on
 *							- 0 -> PWM_CH0
 *							- 1 -> PWM_CH1A
 *							- 2 -> PWM_CH1B
 *							- 3 -> PWM_CH2 
 * @param Duty : The duty cycle of the PWM signal takes values from (0~100)
 * @param Frequency : The Frequency of the PWM signal
 * for PWM_CH0 & PWM_CH1A:1B : takes the following values :
 *						- 31370 -> F_31370 and gives (31,372 Hz)
 *						- 4000  -> F_4000  and gives (3921   Hz)
 *						- 500   -> F_500   and gives (490    Hz)
 *						- 120   -> F_120   and gives (122    Hz)
 *						- 30    -> F_30    and gives (31     Hz)
 * for PWM_CH2 : takes the following values :
 *						- 31370 -> F_31370 and gives (31,372 Hz)
 *						- 4000  -> F_4000  and gives (3921   Hz)
 *						- 1000  -> F_1000  and gives (980    Hz)
 *						- 500   -> F_500   and gives (490    Hz)
 *						- 245   -> F_245   and gives (245    Hz)
 *						- 120   -> F_120   and gives (122    Hz)
 *						- 30    -> F_30    and gives (31     Hz)
 * @return function status
 */
ERROR_STATUS Pwm_Start(uint8_t Channel,uint8_t Duty,uint32_t Frequency)
{
	ERROR_STATUS ERR = E_OK;
	
	if (gu8_PWM_InitFlag)
	{
		switch (Channel)
		{
			case PWM_CH0:
			{
				gu8_PWM0_StartFlag = TRUE;
				OCR0 = (Duty*BITS_8_RESOLUTION)/PERCENT;
				switch (Frequency)
				{
					case F_31370:
					TCCR0 |= (PWM_CS00);
					break;
					
					case F_4000:
					TCCR0 |= (PWM_CS01);
					break;
					
					case F_500:
					TCCR0 |= (PWM_CS01 | PWM_CS00);
					break;
					
					case F_120:
					TCCR0 |= (PWM_CS02);
					break;
					
					case F_30:
					TCCR0 |= (PWM_CS02 | PWM_CS00);
					break;
					
					default:
					ERR = ERROR_INVALID_PARAMETER;
					break;
				}
			}
			break;
			
			case PWM_CH1A:
			{
				gu8_PWM1A_StartFlag = TRUE;
				OCR1A = (Duty*BITS_8_RESOLUTION)/PERCENT;
				switch (Frequency)
				{
					case F_31370:
					TCCR1B |= (PWM_CS10);
					break;
					
					case F_4000:
					TCCR1B |= (PWM_CS11);
					break;
					
					case F_500:
					TCCR1B |= (PWM_CS11 | PWM_CS10);
					break;
					
					case F_120:
					TCCR1B |= (PWM_CS12);
					break;
					
					case F_30:
					TCCR1B |= (PWM_CS12 | PWM_CS10);
					break;
					
					default:
					ERR = ERROR_INVALID_PARAMETER;
					break;
				}
			}
			break;
			
			case PWM_CH1B:
			{
				gu8_PWM1B_StartFlag = TRUE;
				OCR1B = (Duty*BITS_8_RESOLUTION)/PERCENT;
				switch (Frequency)
				{
					case F_31370:
					TCCR1B |= (PWM_CS10);
					break;
					
					case F_4000:
					TCCR1B |= (PWM_CS11);
					break;
					
					case F_500:
					TCCR1B |= (PWM_CS11 | PWM_CS10);
					break;
					
					case F_120:
					TCCR1B |= (PWM_CS12);
					break;
					
					case F_30:
					TCCR1B |= (PWM_CS12 | PWM_CS10);
					break;
					
					default:
					ERR = ERROR_INVALID_PARAMETER;
					break;
				}
			}
			break;
			
			case PWM_CH2:
			{
				gu8_PWM2_StartFlag = TRUE;
				OCR2 = (Duty*BITS_8_RESOLUTION)/PERCENT;
				switch (Frequency)
				{
					case F_31370:
					TCCR2 |= (PWM_CS20);
					break;
					
					case F_4000:
					TCCR2 |= (PWM_CS21);
					break;
					
					case F_1000:
					TCCR2 |= (PWM_CS21 | PWM_CS20);
					break;
					
					case F_500:
					TCCR2 |= (PWM_CS22);
					break;
					
					case F_245:
					TCCR2 |= (PWM_CS22 | PWM_CS20);
					break;
					
					case F_120:
					TCCR2 |= (PWM_CS22 | PWM_CS21);
					break;
					
					case F_30:
					TCCR2 |= (PWM_CS22 | PWM_CS21 | PWM_CS20);
					break;
					
					default:
					ERR = ERROR_INVALID_PARAMETER;
					break;
					
				}
			}
			break;
			
			default:
			ERR = ERROR_INVALID_PARAMETER;
			break;
			
		}
	}
	else
	{
		ERR = ERROR_MODULE_NOT_INITIALIZED;
	}
	
	return ERR;
}

/**
 * Description: Updates the parameters of a previously started PWM signal
 * @param Timer_cfg : Pointer to the configuration struct 
 * @param Channel : The channel to generate the PWM signal on
 *							- 0 -> PWM_CH0
 *							- 1 -> PWM_CH1A
 *							- 2 -> PWM_CH1B
 *							- 3 -> PWM_CH2
 * @param Duty : The duty cycle of the PWM signal takes values from (0~100)
 * @param Frequency : The Frequency of the PWM signal
 * for PWM_CH0 & PWM_CH1A:1B : takes the following values :
 *						- 31370 -> F_31370 and gives (31,372 Hz)
 *						- 4000  -> F_4000  and gives (3921   Hz)
 *						- 500   -> F_500   and gives (490    Hz)
 *						- 120   -> F_120   and gives (122    Hz)
 *						- 30    -> F_30    and gives (31     Hz)
 * for PWM_CH2 : takes the following values :
 *						- 31370 -> F_31370 and gives (31,372 Hz)
 *						- 4000  -> F_4000  and gives (3921   Hz)
 *						- 1000  -> F_1000  and gives (980    Hz)
 *						- 500   -> F_500   and gives (490    Hz)
 *						- 245   -> F_245   and gives (245    Hz)
 *						- 120   -> F_120   and gives (122    Hz)
 *						- 30    -> F_30    and gives (31     Hz)
 * @return function status
 */
ERROR_STATUS Pwm_Update(uint8_t Channel,uint8_t Duty,uint32_t Frequency)
{
	ERROR_STATUS ERR = E_OK;
	
	if (gu8_PWM_InitFlag)
	{
		switch (Channel)
		{
			case PWM_CH0:
			if (gu8_PWM0_StartFlag)
			{
				OCR0 = (Duty*BITS_8_RESOLUTION)/PERCENT;
				PWM0_STOP;
				switch (Frequency)
				{
					case F_31370:
					TCCR0 |= (PWM_CS00);
					break;
					
					case F_4000:
					TCCR0 |= (PWM_CS01);
					break;
					
					case F_500:
					TCCR0 |= (PWM_CS01 | PWM_CS00);
					break;
					
					case F_120:
					TCCR0 |= (PWM_CS02);
					break;
					
					case F_30:
					TCCR0 |= (PWM_CS02 | PWM_CS00);
					break;
					
					default:
					ERR = ERROR_INVALID_PARAMETER;
					break;
				}
			}
			else
			{
				ERR = ERROR_MODULE_NOT_INITIALIZED;
			}
			break;
			
			case PWM_CH1A:
			if (gu8_PWM1A_StartFlag)
			{
				OCR1A = (Duty*BITS_8_RESOLUTION)/PERCENT;
				PWM1_STOP;
				switch (Frequency)
				{
					case F_31370:
					TCCR1B |= (PWM_CS10);
					break;
					
					case F_4000:
					TCCR1B |= (PWM_CS11);
					break;
					
					case F_500:
					TCCR1B |= (PWM_CS11 | PWM_CS10);
					break;
					
					case F_120:
					TCCR1B |= (PWM_CS12);
					break;
					
					case F_30:
					TCCR1B |= (PWM_CS12 | PWM_CS10);
					break;
					
					default:
					ERR = ERROR_INVALID_PARAMETER;
					break;
				}
			}
			else
			{
				ERR = ERROR_MODULE_NOT_INITIALIZED;
			}
			break;
			
			case PWM_CH1B:
			if(gu8_PWM1B_StartFlag)
			{
				OCR1B = (Duty*BITS_8_RESOLUTION)/PERCENT;
				PWM1_STOP;
				switch (Frequency)
				{
					case F_31370:
					TCCR1B |= (PWM_CS10);
					break;
					
					case F_4000:
					TCCR1B |= (PWM_CS11);
					break;
					
					case F_500:
					TCCR1B |= (PWM_CS11 | PWM_CS10);
					break;
					
					case F_120:
					TCCR1B |= (PWM_CS12);
					break;
					
					case F_30:
					TCCR1B |= (PWM_CS12 | PWM_CS10);
					break;
					
					default:
					ERR = ERROR_INVALID_PARAMETER;
					break;
				}
			}
			else
			{
				ERR = ERROR_MODULE_NOT_INITIALIZED;
			}
			break;
			
			case PWM_CH2:
			if (gu8_PWM2_StartFlag)
			{
				OCR2 = (Duty*BITS_8_RESOLUTION)/PERCENT;
				PWM2_STOP;
				switch (Frequency)
				{
					case F_31370:
					TCCR2 |= (PWM_CS20);
					break;
					
					case F_4000:
					TCCR2 |= (PWM_CS21);
					break;
					
					case F_1000:
					TCCR2 |= (PWM_CS21 | PWM_CS20);
					break;
					
					case F_500:
					TCCR2 |= (PWM_CS22);
					break;
					
					case F_245:
					TCCR2 |= (PWM_CS22 | PWM_CS20);
					break;
					
					case F_120:
					TCCR2 |= (PWM_CS22 | PWM_CS21);
					break;
					
					case F_30:
					TCCR2 |= (PWM_CS22 | PWM_CS21 | PWM_CS20);
					break;
					
					default:
					ERR = ERROR_INVALID_PARAMETER;
					break;
					
				}
			}
			else
			{
				ERR = ERROR_MODULE_NOT_INITIALIZED;
			}
			break;
			
			default:
			ERR = ERROR_INVALID_PARAMETER;
			break;
			
		}
	}
	else
	{
		ERR = ERROR_MODULE_NOT_INITIALIZED;
	}
	
	return ERR;
}

/**
 * Description: Stops a previously started PWM signal
* @param Channel : The channel to generate the PWM signal on
*							- 0 -> PWM_CH0
*							- 1 -> PWM_CH1A
*							- 2 -> PWM_CH1B
*							- 3 -> PWM_CH2
 * @return function status 
 */
ERROR_STATUS Pwm_Stop(uint8_t Channel)
{
	ERROR_STATUS ERR = E_OK;
	
	if (gu8_PWM_InitFlag)
	{
		switch(Channel)
		{
			case PWM_CH0:
			if (gu8_PWM0_StartFlag)
			{
				PWM0_STOP;
			}
			else
			{
				ERR = ERROR_STOP_WITHOUT_START;
			}
			break;
			
			case PWM_CH1A:
			if (gu8_PWM1A_StartFlag)
			{
				PWM1_STOP;
			}
			else
			{
				ERR = ERROR_STOP_WITHOUT_START;
			}
			break;
			
			case PWM_CH1B:
			if (gu8_PWM1B_StartFlag)
			{
				PWM1_STOP;
			}
			else
			{
				ERR = ERROR_STOP_WITHOUT_START;
			}
			break;
			
			case PWM_CH2:
			if (gu8_PWM2_StartFlag)
			{
				PWM2_STOP;
			}
			else
			{
				ERR = ERROR_STOP_WITHOUT_START;
			}
			break;
			
			default:
			ERR = ERROR_INVALID_PARAMETER;
			break;
		}
	}
	else
	{
		ERR = ERROR_MODULE_NOT_INITIALIZED;
	}
	
	return ERR;
}