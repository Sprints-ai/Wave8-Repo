/*
 * PWM.c
 *
 * Created: 2/17/2020 11:30:31 AM
 *  Author: Khaled
 */ 


#include "PWM.h"



#define OC1A    BIT5
#define OC1B    BIT4
/*TCCR1A register bits*/
#define COM1A1  BIT7
#define COM1A0  BIT6
#define COM1B1  BIT5
#define COM1B0  BIT4
// #define FOC1A   BIT3
// #define FOC1B   BIT2
#define WGM11   BIT1
#define WGM10   BIT0

/*TCCR1B register bits*/
#define WGM13   BIT4
#define WGM12   BIT3
// #define CS12    BIT2
// #define CS11    BIT1
// #define CS10    BIT0

/*TIMSK register bits*/
// #define OCIE2   BIT7
// #define TOIE2   BIT6
// #define TICIE1  BIT5
// #define OCIE1A  BIT4
// #define OCIE1B  BIT3
// #define TOIE1   BIT2
// #define OCIE0   BIT1
// #define TOIE0   BIT0
#define  T1_PRESCALER_NO                0x01
#define  T1_PRESCALER_8                 0x02
#define  T1_PRESCALER_64                0x03
#define  T1_PRESCALER_256               0x04
#define  T1_PRESCALER_1024              0x05
#define FREQ_100_ICR1H_VALUE 0x27
#define FREQ_100_ICR1L_VALUE 0x10
#define TCCR1B_VALUE_TO_STOP_PWM1     0xF8


#define DUTY_MIN_VALUE 0
#define DUTY_MAX_VALUE 100


/*static uint8_t gu8_PreScaler_T0       = ZERO;*/
static uint8_t gu8_PreScaler_T1       = ZERO;
/* static uint8_t gu8_PreScaler_T2       = ZERO;*/

static uint8_t gu8_ModuleInit = ZERO;
static uint8_t gu8_ModuleStart = ZERO;


ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg)
{
	/*variable to store errors*/
	uint8_t Error = E_OK;

	/*check if the given pointer is null return error*/
	if (NULL == Pwm_Cfg)
	{
		Error_Push(PWM_MODULE,ERROR_NULL_POINTER);
		Error |=  E_NOK;
	}
	else
	{
		switch (Pwm_Cfg->Channel)
		{
		case PWM_CH0:
			Error_Push(PWM_MODULE,ERROR_NOT_IMPLEMENTED);
			Error |= E_NOK;
			break;
			/****************************************************************************************************************************/
		case PWM_CH1A:
			if ((GET_BIT(gu8_ModuleInit,BIT1)) == FALSE)
			{


				/* Set OC1A OUTPUT direction*/
				SET_BIT (PORTD_DIR,OC1A);

				/* set OCR1A bit in mode clear up-counting and set down counting*/
				SET_BIT(TCCR1A,COM1A1);
				CLEAR_BIT(TCCR1A,COM1A0);

				/*choose phase correct PWM mode with ICR register top of counting */
				CLEAR_BIT(TCCR1A,WGM10);
				SET_BIT(TCCR1A,WGM11);
				CLEAR_BIT(TCCR1B,WGM12);
				SET_BIT(TCCR1B,WGM13);

				/*store pre-scaler value in global value to use it in start function*/
				switch (Pwm_Cfg->Prescaler)
				{
				case PRESCALER_1:
					gu8_PreScaler_T1 = T1_PRESCALER_NO;
					break;

				case PRESCALER_8:
					gu8_PreScaler_T1 = T1_PRESCALER_8;
					break;

				case PRESCALER_64:
					gu8_PreScaler_T1 = T1_PRESCALER_64;
					break;

				case PRESCALER_256:
					gu8_PreScaler_T1 = T1_PRESCALER_256;
					break;

				case PRESCALER_1024:
					gu8_PreScaler_T1 = T1_PRESCALER_1024;
					break;

				default:
					Error_Push(PWM_MODULE,ERROR_INVALID_PARAMETER);
					Error |=  E_NOK;
					break;
				}
				if (E_OK == Error)
				{
					SET_BIT(gu8_ModuleInit,BIT1);
				}

			}
			else
			{
				Error_Push(PWM_MODULE,ERROR_ALREADY_INITIALIZED);
				Error |=  E_NOK;
			}
			break;
			/**************************************************************************************/
		case PWM_CH1B:
			if ((GET_BIT(gu8_ModuleInit,BIT2)) == FALSE)
			{


				/* Set OC1B OUTPUT direction*/
				SET_BIT (PORTD_DIR,OC1B);

				/* set OCR1B bit in mode clear up-counting and set down counting*/
				SET_BIT(TCCR1A,COM1B1);
				CLEAR_BIT(TCCR1A,COM1B0);

				/*choose phase correct PWM mode with ICR register top of counting */
				CLEAR_BIT(TCCR1A,WGM10);
				SET_BIT(TCCR1A,WGM11);
				CLEAR_BIT(TCCR1B,WGM12);
				SET_BIT(TCCR1B,WGM13);

				/*store pre-scaler value in global value to use it in start function*/
				switch (Pwm_Cfg->Prescaler)
				{
				case PRESCALER_1:
					gu8_PreScaler_T1 = T1_PRESCALER_NO;
					break;

				case PRESCALER_8:
					gu8_PreScaler_T1 = T1_PRESCALER_8;
					break;

				case PRESCALER_64:
					gu8_PreScaler_T1 = T1_PRESCALER_64;
					break;

				case PRESCALER_256:
					gu8_PreScaler_T1 = T1_PRESCALER_256;
					break;

				case PRESCALER_1024:
					gu8_PreScaler_T1 = T1_PRESCALER_1024;
					break;

				default:
					Error_Push(PWM_MODULE,ERROR_INVALID_PARAMETER);
					Error |=  E_NOK;
					break;
				}
				if (E_OK == Error)
				{
					SET_BIT(gu8_ModuleInit,BIT2);
				}

			}
			else
			{
				Error_Push(PWM_MODULE,ERROR_ALREADY_INITIALIZED);
				Error |=  E_NOK;
			}

			break;
			/*****************************************************************************************************************************************/
		case PWM_CH2:
			Error_Push(PWM_MODULE,ERROR_NOT_IMPLEMENTED);
			Error |= E_NOK;
			break;

		default:
			/*given channel is not exist*/
			Error_Push(PWM_MODULE,ERROR_INVALID_PARAMETER);
			Error |=  E_NOK;
			break;
		}
	}
	return Error ;
}

ERROR_STATUS Pwm_Start(uint8_t Channel,uint8_t Duty,uint8_t Frequncy)
{
	/*variable to store errors*/
	uint8_t Error = E_OK;
	uint16_t au16_OCR_Value = ZERO;
	uint8_t au8_Temp_For_Low_Bit   = ZERO;
	uint8_t au8_Temp_For_Hight_Bit = ZERO;

	switch(Channel)
	{
	case PWM_CH0:
		Error_Push(PWM_MODULE,ERROR_NOT_IMPLEMENTED);
		Error = E_NOK;
		break;

	case PWM_CH1A:
		if ((GET_BIT(gu8_ModuleInit,BIT1)) != FALSE)
		{
			if ((GET_BIT(gu8_ModuleStart,BIT1)) == FALSE)
			{
				/*set ICR reg to achieve desired freq*/
				switch (Frequncy)
				{
				case PWM_FREQUENCY_100:
					ICR1H = FREQ_100_ICR1H_VALUE;
					ICR1L = FREQ_100_ICR1L_VALUE;
					break;
					/************************************************************************/
				default:
					Error_Push(PWM_MODULE,ERROR_INVALID_PARAMETER);
					Error |=  E_NOK;
					break;
				}
				if ((DUTY_MIN_VALUE <= Duty) && (DUTY_MAX_VALUE >= Duty))
				{
					/*calculate the OCR value that referee to Duty Cycle*/
					au16_OCR_Value = ((((uint32_t)Duty * ICR1)) / 100);
					au8_Temp_For_Low_Bit   = au16_OCR_Value;
					au8_Temp_For_Hight_Bit = (au16_OCR_Value SHIFT_8_BIT_RIGHT);

					/*set OCR1A reg to achieve desired Duty Cycle*/
					OCR1AH = au8_Temp_For_Hight_Bit;
					OCR1AL = au8_Temp_For_Low_Bit;

					/*start the PWM using Prescaler that initialized in init function*/
					TCCR1B |= gu8_PreScaler_T1;
				}
				else
				{
					Error_Push(PWM_MODULE,ERROR_INVALID_PARAMETER);
					Error |=  E_NOK;
				}
				if (E_OK == Error)
				{
					SET_BIT(gu8_ModuleStart,BIT1);
				}
			}
			else
			{
				Error_Push(PWM_MODULE,ERROR_ALREADY_STARTED);
				Error |=  E_NOK;
			}

		}
		else
		{
			Error_Push(PWM_MODULE,ERROR_NOT_INITIALIZED);
			Error |=  E_NOK;
		}

		break;
		/***************************************************************************************************************************/
	case PWM_CH1B:
		if ((GET_BIT(gu8_ModuleInit,BIT2)) != FALSE)
		{
			if ((GET_BIT(gu8_ModuleStart,BIT2)) == FALSE)
			{
				/*set ICR reg to achieve desired freq*/
				switch (Frequncy)
				{
				case PWM_FREQUENCY_100:
					ICR1H = FREQ_100_ICR1H_VALUE;
					ICR1L = FREQ_100_ICR1L_VALUE;
					break;
					/*****************************************/
				default:
					Error_Push(PWM_MODULE,ERROR_INVALID_PARAMETER);
					Error |=  E_NOK;
					break;
				}

				if ((DUTY_MIN_VALUE <= Duty) && (DUTY_MAX_VALUE >= Duty))
				{
					/*calculate the OCR value that referee to Duty Cycle*/
					au16_OCR_Value = ((((uint32_t)Duty * ICR1)) / 100);
					au8_Temp_For_Low_Bit   = au16_OCR_Value;
					au8_Temp_For_Hight_Bit = (au16_OCR_Value SHIFT_8_BIT_RIGHT);

					/*set OCR1B reg to achieve desired Duty Cycle*/
					OCR1BH = au8_Temp_For_Hight_Bit;
					OCR1BL = au8_Temp_For_Low_Bit;

					/*start the PWM using Prescaler that initialized in init function*/
					TCCR1B |= gu8_PreScaler_T1;
				}
				else
				{
					Error_Push(PWM_MODULE,ERROR_INVALID_PARAMETER);
					Error |=  E_NOK;
				}
				if (E_OK == Error)
				{
					SET_BIT(gu8_ModuleStart,BIT2);
				}
			}

		}
		else
		{
			Error_Push(PWM_MODULE,ERROR_NOT_INITIALIZED);
			Error |=  E_NOK;
		}
		break;
		/********************************************************************************************************/
	case PWM_CH2:
		Error_Push(PWM_MODULE,ERROR_NOT_IMPLEMENTED);
		Error = E_NOK;
		break;

	default:
		Error_Push(PWM_MODULE,ERROR_INVALID_PARAMETER);
		Error |=  E_NOK;
		break;
	}
	return Error ;
}


ERROR_STATUS Pwm_Update(uint8_t Channel,uint8_t Duty,uint8_t Frequncy)
{
	/*variable to store errors*/
	uint8_t Error = E_OK;
	uint16_t au16_OCR_Value = ZERO;
	uint8_t au8_Temp_For_Low_Bit   = ZERO;
	uint8_t au8_Temp_For_Hight_Bit = ZERO;

	switch (Channel)
	{
	case PWM_CH0:
		Error_Push(PWM_MODULE,ERROR_NOT_IMPLEMENTED);
		Error = E_NOK;
		break;

	case PWM_CH1A:
		if ((GET_BIT(gu8_ModuleStart,BIT1)) != FALSE)
		{
			/*set ICR reg to achieve desired freq*/
			switch (Frequncy)
			{
			case PWM_FREQUENCY_100:
				ICR1H = FREQ_100_ICR1H_VALUE;
				ICR1L = FREQ_100_ICR1L_VALUE;
				break;
				/************************************************************************/
			default:
				Error_Push(PWM_MODULE,ERROR_INVALID_PARAMETER);
				Error |=  E_NOK;
				break;
			}
			if ((DUTY_MIN_VALUE <= Duty) && (DUTY_MAX_VALUE >= Duty))
			{
				/*calculate the OCR value that referee to Duty Cycle*/
				au16_OCR_Value = ((((uint32_t)Duty * ICR1)) / 100);
				au8_Temp_For_Low_Bit   = au16_OCR_Value;
				au8_Temp_For_Hight_Bit = (au16_OCR_Value SHIFT_8_BIT_RIGHT);

				/*set OCR1A reg to achieve desired Duty Cycle*/
				OCR1AH = au8_Temp_For_Hight_Bit;
				OCR1AL = au8_Temp_For_Low_Bit;

			}
			else
			{
				Error_Push(PWM_MODULE,ERROR_INVALID_PARAMETER);
				Error |=  E_NOK;
			}
		}
		else
		{
			Error_Push(PWM_MODULE,ERROR_NO_START);
			Error |=  E_NOK;
		}
		break;
		/***********************************************************************************************************************/
	case PWM_CH1B:
		if ((GET_BIT(gu8_ModuleStart,BIT2)) != FALSE)
		{
			/*set ICR reg to achieve desired freq*/
			switch (Frequncy)
			{
			case PWM_FREQUENCY_100:
				ICR1H = FREQ_100_ICR1H_VALUE;
				ICR1L = FREQ_100_ICR1L_VALUE;
				break;
				/*****************************************/
			default:
				Error_Push(PWM_MODULE,ERROR_INVALID_PARAMETER);
				Error |=  E_NOK;
				break;
			}

			if ((DUTY_MIN_VALUE <= Duty) && (DUTY_MAX_VALUE >= Duty))
			{
				/*calculate the OCR value that referee to Duty Cycle*/
				au16_OCR_Value = ((((uint32_t)Duty * ICR1)) / 100);
				au8_Temp_For_Low_Bit   = au16_OCR_Value;
				au8_Temp_For_Hight_Bit = (au16_OCR_Value SHIFT_8_BIT_RIGHT);

				/*set OCR1B reg to achieve desired Duty Cycle*/
				OCR1BH = au8_Temp_For_Hight_Bit;
				OCR1BL = au8_Temp_For_Low_Bit;


			}
			else
			{
				Error_Push(PWM_MODULE,ERROR_INVALID_PARAMETER);
				Error |=  E_NOK;
			}

		}
		else
		{
			Error_Push(PWM_MODULE,ERROR_NO_START);
			Error |=  E_NOK;
		}


		break;
		/***********************************************************************************************************************/
	case PWM_CH2:
		Error_Push(PWM_MODULE,ERROR_NOT_IMPLEMENTED);
		Error = E_NOK;
		break;

	default:
		Error_Push(TIMERS_MODULE,ERROR_INVALID_PARAMETER);
		Error |=  E_NOK;
		break;
	}

	return Error;
}



ERROR_STATUS Pwm_Stop(uint8_t Channel)
{
	/*variable to store errors*/
	uint8_t Error = E_OK;
	switch (Channel)
	{
	case PWM_CH0:
		Error_Push(PWM_MODULE,ERROR_NOT_IMPLEMENTED);
		Error = E_NOK;
		break;
		/************************************************************************************/
	case PWM_CH1A:
		if ((GET_BIT(gu8_ModuleStart,BIT1)) != FALSE)
		{
			TCCR1B &= TCCR1B_VALUE_TO_STOP_PWM1 ;
			CLEAR_BIT(gu8_ModuleStart,BIT1);
		}
		else
		{
			Error_Push(PWM_MODULE,ERROR_NO_START);
			Error |=  E_NOK;
		}

		break;
		/**************************************************************************************/
	case PWM_CH1B:
		if ((GET_BIT(gu8_ModuleStart,BIT2)) != FALSE)
		{
			TCCR1B &= TCCR1B_VALUE_TO_STOP_PWM1 ;
			CLEAR_BIT(gu8_ModuleStart,BIT2);
		}
		else
		{
			Error_Push(PWM_MODULE,ERROR_NO_START);
			Error |=  E_NOK;
		}

		break;
		/**************************************************************************************/
	case PWM_CH2:
		Error_Push(PWM_MODULE,ERROR_NOT_IMPLEMENTED);
		Error = E_NOK;
		break;
		/*****************************************************************************************/
	default:
		Error_Push(TIMERS_MODULE,ERROR_INVALID_PARAMETER);
		Error |=  E_NOK;
		break;
	}

	return Error;
}