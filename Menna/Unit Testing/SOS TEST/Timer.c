/*
 ============================================================================
 Name        : Timer.c
 Author      : Muhammed Gamal
 Description :
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




/**
 * Input: Pointer to a structure contains the information needed to initialize the timer.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Initiates the module.
 *
 */
ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg)
{
	uint8_t u8_status;
	if(Timer_cfg == NULL_Ptr)
	{
		u8_status=E_NOk;
	}
	else
	{
		//TIMSK = Timer_cfg->Timer_Polling_Or_Interrupt;
		switch(Timer_cfg->Timer_CH_NO)
		{
			case Timer_0:

				u8_status=E_ok;
				break;
			case Timer_1:

				u8_status=E_ok;
				break;
			case Timer_2:

				u8_status=E_ok;
				break;
			default:
				u8_status=E_NOk;
		}
	}
	return u8_status;
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
{
	uint8_t u8_status;
	switch(Timer_CH_NO)
	{
		case Timer_0:
			if(Timer_Count<=TIMER0_MAX_COUNT)
			{

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
{
	uint8_t u8_status;
	switch(Timer_CH_NO)
	{
		case Timer_0:

			u8_status=E_ok;
			break;
		case Timer_1:

			u8_status=E_ok;
			break;
		case Timer_2:

			u8_status=E_ok;
			break;
		default:
			u8_status=E_NOk;
			break;
	}
	return u8_status;
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
{
	uint8_t u8_status;
	switch(Timer_CH_NO)
	{
		case Timer_0:

			u8_status=E_ok;
			break;

		case Timer_1:

			u8_status=E_ok;
			break;

		case Timer_2:

			u8_status=E_ok;
			break;

		default:
			u8_status=E_NOk;
	}
	return u8_status;
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
ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO,uint16_t* Data)
{
	uint8_t u8_status;
	switch(Timer_CH_NO)
	{
		case Timer_0:

			u8_status = E_ok;
			break;
		case Timer_1:

			u8_status=E_ok;
			break;
		case Timer_2:

			u8_status=E_ok;
			break;
		default:
			u8_status=E_NOk;
	}
	return u8_status;
}




/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to reset the TCNTX register value.
 *
 */
ERROR_STATUS Timer_Clear(uint8_t Timer_CH_NO)
{
	uint8_t u8_status;
	switch(Timer_CH_NO)
	{
		case Timer_0:

			u8_status = E_ok;
			break;
		case Timer_1:

			u8_status=E_ok;
			break;
		case Timer_2:

			u8_status=E_ok;
			break;
		default:
			u8_status=E_NOk;
			break;
	}
	return u8_status;
}
/***************************************************************************************/


/**************************************************************************************
                                 TIMERS ISRs
**************************************************************************************/


