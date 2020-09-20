/*
* PWM.c
*
* Created: 2/17/2020 7:39:24 PM
*  Author: Hazem
*/

/************************************************************************/
/*				 INCLUDES			        							*/
/************************************************************************/
#include "pwm.h"

/************************************************************************/
/*				 DEFINES			        							*/
/************************************************************************/
#define	TIMER_CH0			0
#define	TIMER_CH1			1
#define	TIMER_CH2			2

#define NOT_INITIALIZED		0
#define INITIALIZED			1

#define MAX_PWM_CHANNELS	4

/************************************************************************/
/*				 GLOBAL STATIC VARIABLES			        			*/
/************************************************************************/

static uint8_t  gsau8_preScaler[MAX_PWM_CHANNELS] = {PWM_PRESCALER_NO, PWM_PRESCALER_NO, PWM_PRESCALER_NO, PWM_PRESCALER_NO};
static uint8_t  gsau8_initState[MAX_PWM_CHANNELS] = {NOT_INITIALIZED, NOT_INITIALIZED, NOT_INITIALIZED, NOT_INITIALIZED};
static uint16_t gsau8_prescaler_calc_LUT[] = {1, 8, 32, 64, 128, 256, 1024};
static uint8_t  gsau8_prescaler_0_1_LUT[] = {0x01, 0x02, 0x00, 0x03, 0x00, 0x04, 0x05};
static uint8_t  gsau8_prescaler_2_LUT[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

/*********************************************************************************/
/* Function: Error_State Pwm_Init(Pwm_Cfg_s_t *Pwm_Cfg);                         */
/* Type: public                                                                  */
/* Input parameters: Pwm_Cfg Structure (channel number, Prescaler)               */
/* Return type : void                                                            */
/*                                                                               */
/* Description: initialize the PWM configuration                                 */
/*********************************************************************************/
ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg)
{   
ERROR_STATUS ERROR=E_OK;
	if(Pwm_Cfg!=NULL)
	{		
		switch (Pwm_Cfg->Channel)
		{
			case (PWM_CH0):
					/* Set Mode 1 (Phase correct) */
					TCCR0 |= WGM00;
					TCCR0 &= ~WGM01;
					/* Non-inverting */
					TCCR0 |= COM01;
					TCCR0 &= ~COM00;
					/* Set OC0 as digital output */
					DIO_Cfg_s ST_OC0_dio = {0};
					ST_OC0_dio.GPIO = GPIOB;
					ST_OC0_dio.dir = OUTPUT;
					ST_OC0_dio.pins = PIN3;
					if(DIO_init(&ST_OC0_dio) == E_OK)
					{
						/* DIO initialized successfully */
					}
					else
					{
						ERROR=E_NOK;
					}
					gsau8_preScaler[Pwm_Cfg->Channel] = Pwm_Cfg->Prescaler;
					gsau8_initState[Pwm_Cfg->Channel] = INITIALIZED;
					break;
			case (PWM_CH1A):
					/* Set Mode 8 (Phase and frequency correct) */
					TCCR1A &= ~(WGM11 | WGM10);
					TCCR1B |= WGM13;
					TCCR1B &= ~WGM12;
					/* Non-inverting */
					TCCR1A |= COM1A1;
					TCCR1A &= ~COM1A0;
					/* Set OC0 as digital output */
					DIO_Cfg_s ST_OC1A_dio = {0};
					ST_OC1A_dio.GPIO = GPIOD;
					ST_OC1A_dio.dir = OUTPUT;
					ST_OC1A_dio.pins = PIN5;
					if(DIO_init(&ST_OC1A_dio) == E_OK)
					{
						/* DIO initialized successfully */
					}
					else
					{
						ERROR=E_NOK;
					}
					/* Store Prescaler for the Pwm_Start function */
					gsau8_preScaler[Pwm_Cfg->Channel] = Pwm_Cfg->Prescaler;
					gsau8_initState[Pwm_Cfg->Channel] = INITIALIZED;
					break;
			case (PWM_CH1B):
					/* Set Mode 8 (Phase and frequency correct) */
					TCCR1A &= ~(WGM11 | WGM10);
					TCCR1B |= WGM13;
					TCCR1B &= ~WGM12;
					/* Non-inverting */
					TCCR1A |= COM1B1;
					TCCR1A &= ~COM1B0;
					/* Set OC0 as digital output */
					DIO_Cfg_s ST_OC1B_DIO;
					ST_OC1B_DIO.GPIO = GPIOD;
					ST_OC1B_DIO.dir = OUTPUT;
					ST_OC1B_DIO.pins = PIN4;
					if(DIO_init(&ST_OC1B_DIO) == E_OK)
					{
						/* DIO initialized successfully */
					}
					else
					{
						ERROR=E_NOK;
					}

					/* Store Prescaler for the Pwm_Start function */
					gsau8_preScaler[Pwm_Cfg->Channel] = Pwm_Cfg->Prescaler;
					gsau8_initState[Pwm_Cfg->Channel] = INITIALIZED;
					break;
			case (PWM_CH2):
					/* Set Mode 1 (Phase correct) */
					TCCR2 |= WGM20;
					TCCR2 &= ~WGM21;
					/* Non-inverting */
					TCCR2 |= COM21;
					TCCR2 &= ~COM20;
					/* Set OC0 as digital output */
					DIO_Cfg_s ST_OC2_dio = {0};
					ST_OC2_dio.GPIO = GPIOD;
					ST_OC2_dio.dir = OUTPUT;
					ST_OC2_dio.pins = PIN7;
					if(DIO_init(&ST_OC2_dio) == E_OK)
					{
						/* DIO initialized successfully */
					}
					else
					{
						ERROR=E_NOK;
					}
					/* Store Prescaler for the Pwm_Start function */
					gsau8_preScaler[Pwm_Cfg->Channel] = Pwm_Cfg->Prescaler;
					gsau8_initState[Pwm_Cfg->Channel] = INITIALIZED;				
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

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: starts the PWM on the dedicated channel with the required duty   */
/*				cycle and frequency                                              */
/*-------------------------------------------------------                        */
/*(IN timer 0) there are only 5 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ                                          */
/*Frequency (Prescaler 8) --> 3,921HZ                                            */
/*Frequency (Prescaler 64) --> 490HZ                                             */
/*Frequency (Prescaler 256) --> 122HZ                                            */
/*Frequency (Prescaler 1024) --> 31HZ                                            */
/*--------------------------------------------------------                       */
/*(IN timer 2) there are only 7 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ                                          */
/*Frequency (Prescaler 8) --> 3,921HZ                                            */
/*Frequency (Prescaler 32) --> 980HZ                                             */
/*Frequency (Prescaler 64) --> 490HZ                                             */
/*Frequency (Prescaler 128) --> 245HZ                                            */
/*Frequency (Prescaler 256) --> 122HZ                                            */
/*Frequency (Prescaler 1024) --> 31HZ                                            */
/*-------------------------------------------------------                        */
/*((all this calculations are for phase correct mode))                           */
/*all this calculation for F_CPU 16MHz                                           */
/*********************************************************************************/
ERROR_STATUS Pwm_Start(uint8_t channel,uint8_t Duty,uint32_t Frequncy)
{
ERROR_STATUS ERROR=E_OK;	
	switch (channel)
	{
		case (PWM_CH0):
		      /* Check if PWM channel is initialized or not */
		      if(gsau8_initState[channel] == INITIALIZED)
		      {
			      /* Equation of Duty cycle */
			      uint32_t u32_F_Calculated = (F_CPU / (gsau8_prescaler_calc_LUT[gsau8_preScaler[channel]] * 510));
			      if(u32_F_Calculated!=Frequncy)
			       ERROR=E_NOK;
			      /* Calculating duty ratio */		
			      OCR0 = (Duty * 0xFF) / 100;
			      /* Starting PWM channel */
			      TCCR0 |= gsau8_prescaler_0_1_LUT[gsau8_preScaler[channel]];
		      }
		      else
		      {
			      ERROR=E_NOK;
		      }
		      break;
		case (PWM_CH1A):
				/* Check if PWM channel is initialized or not */
				if(gsau8_initState[channel] == INITIALIZED)
				{
					/* Non-inverting */
					TCCR1A |= COM1A1;
					TCCR1A &= ~COM1A0;
					/* Equation of Duty cycle */
					uint16_t u16_F_Calculated = (F_CPU / (2 * gsau8_prescaler_calc_LUT[gsau8_preScaler[channel]] * Frequncy));
					ICR1 = u16_F_Calculated;

					/* Calculating duty ratio */
					uint32_t DutyRatio = (((uint32_t)Duty * (uint32_t)ICR1) / 100);
					OCR1A = (uint16_t) DutyRatio;

					/* Starting PWM channel */
					TCCR1B |= gsau8_prescaler_0_1_LUT[gsau8_preScaler[channel]];
				}
				else
				{
					ERROR=E_NOK;
				}
				break;
		case (PWM_CH1B):
				/* Check if PWM channel is initialized or not */
				if(gsau8_initState[channel] == INITIALIZED)
				{
					/* Non-inverting */
					TCCR1A |= COM1B1;
					TCCR1A &= ~COM1B0;
					/* Equation from data sheet of ATmega32 */
					uint16_t u16_F_Calculated = (F_CPU / (2 * gsau8_prescaler_calc_LUT[gsau8_preScaler[channel]] * Frequncy));
					ICR1 = u16_F_Calculated;

					/* Calculating duty ratio */
					uint32_t DutyRatio = (((uint32_t)Duty * (uint32_t)ICR1) / 100);
					OCR1B = (uint16_t) DutyRatio;

					/* Starting PWM channel */
					TCCR1B |= gsau8_prescaler_0_1_LUT[gsau8_preScaler[channel]];
				}
				else
				{
					ERROR=E_NOK;
				}
				break;
		case (PWM_CH2):
				/* Check if PWM channel is initialized or not */
				if(gsau8_initState[channel] == INITIALIZED)
				{
					/* Calculating duty ratio */
					OCR2 = (Duty * 0xFF) / 100;

					/* Starting PWM channel */
					TCCR2 |= gsau8_prescaler_2_LUT[gsau8_preScaler[channel]];
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

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: updates the duty cycle and frequency of the dedicated channel    */
/*********************************************************************************/
ERROR_STATUS Pwm_Update(uint8_t channel,uint8_t Duty,uint32_t Frequncy)
{
ERROR_STATUS ERROR=E_OK;	
	switch (channel)
	{
		case (PWM_CH0):
				/* Check if PWM channel is initialized or not */
				if(gsau8_initState[channel] == INITIALIZED)
				{
					/* Calculating duty ratio */
					OCR0 = (Duty * 0xFF) / 100;
				}
				else
				{
					ERROR=E_NOK;
				}
				break;
		case (PWM_CH1A):
					/* Check if PWM channel is initialized or not */
					if(gsau8_initState[channel] == INITIALIZED)
					{
						/* Calculating frequency */
						/* Equation from datasheet of ATmega32 P.108 */
						uint16_t u16_F_Calculated = (F_CPU / (2 * gsau8_prescaler_calc_LUT[gsau8_preScaler[channel]] * Frequncy));
						ICR1 = u16_F_Calculated;

						/* Calculating duty ratio */
						uint32_t DutyRatio = (((uint32_t)Duty * (uint32_t)ICR1) / 100);
						OCR1A = (uint16_t) DutyRatio;
					}
					else
					{
						ERROR=E_NOK;
					}
					break;
		case (PWM_CH1B):
				/* Check if PWM channel is initialized or not */
				if(gsau8_initState[channel] == INITIALIZED)
				{
					/* Equation from datasheet of ATmega32 P.108 */
					uint16_t u16_F_Calculated = (F_CPU / (2 * gsau8_prescaler_calc_LUT[gsau8_preScaler[channel]] * Frequncy));
					ICR1 = u16_F_Calculated;

					/* Calculating duty ratio */
					uint32_t DutyRatio = (((uint32_t)Duty * (uint32_t)ICR1) / 100);
					OCR1B = (uint16_t) DutyRatio;
				}
				else
				{
					ERROR=E_NOK;
				}
				break;
		case (PWM_CH2):
				/* Check if PWM channel is initialized or not */
				if(gsau8_initState[channel] == INITIALIZED)
				{
					/* Calculating duty ratio */
					OCR2 = (Duty * 0xFF) / 100;
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

/*********************************************************************************/
/* Function: Error_State Pwm_Stop(uint8_t channel);                              */
/* Type: public                                                                  */
/* Input parameters: channel ID                                                  */
/* Return type : Error state                                                     */
/*                                                                               */
/* Description: responsible of Stopping the PWM by clearing the prescaler		 */
/*				of the corresponding channel                                     */
/*********************************************************************************/
ERROR_STATUS Pwm_Stop(uint8_t channel)
{
ERROR_STATUS ERROR=E_OK;	
	switch (channel)
	{
		case (PWM_CH0):
				/* Check if PWM channel is initialized or not */
				if(gsau8_initState[channel] == INITIALIZED)
				{
					TCCR0 &= ~(CS02 | CS01 | CS00);
				}
				else
				{
					ERROR=E_NOK;
				}
				break;
		case (PWM_CH1A):
				/* Check if PWM channel is initialized or not */
				if(gsau8_initState[channel] == INITIALIZED)
				{
					if(gsau8_initState[PWM_CH1B] == INITIALIZED)
					{
						/* Disconnect OC1A only */
						TCCR1A &= ~(COM1A1 | COM1A0);
					}
					else
					{
						/* Stop timer */
						TCCR1B &= ~(CS12 | CS11 | CS10);
					}
				}
				else
				{
					ERROR=E_NOK;
				}
				break;
		case (PWM_CH1B):
				/* Check if PWM channel is initialized or not */
				if(gsau8_initState[channel] == INITIALIZED)
				{
					if(gsau8_initState[PWM_CH1A] == INITIALIZED)
					{
						/* Disconnect OC1B only */
						TCCR1A &= ~(COM1B1 | COM1B0);
					}
					else
					{
						/* Stop timer */
						TCCR1B &= ~(CS12 | CS11 | CS10);
					}
				}
				else
				{
					ERROR=E_NOK;
				}
				break;
	}
	return ERROR;
}
