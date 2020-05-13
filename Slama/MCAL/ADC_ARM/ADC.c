/*
 * ADC.c
 *
 *  Created on: Apr 25, 2020
 *      Author: ahmed
 */

/*Includes*/
#include "./SERVICES/Error_table.h"
#include "ADC.h"
#include "ADClcfg.h"

/*Defines*/
#define ADC_CONFIG_ARR ADC_Conf[au8_Modules_loop]

/*ADC Macros*/
#define MAX_ADC_CHNLS (3)
#define MAX_CONV_LENGTH (16)
#define LAST_CHANNEL_BIT (29)
#define CHANNEL_BITS_WIDTH (5)
#define REGISTER_MAX_CHANNELS_NO (6)
#define REGISTERS_SQR_NUM (2)

/*init Macros*/
#define MODULE_NOT_INIT (0)
#define MODULE_INIT (1)

/*Global Variables*/
static uint8_t gu8_AdcInit_Status = MODULE_NOT_INIT;

/*Init Status Variable*/

/*Init Function*/
ERROR_STATUS ADC_Link_Init(void)
{
	/*Create Error Status*/
	ERROR_STATUS ERR_STATE = E_OK;


	/*Check for user Input*/
	if(ADC_USED > MAX_ADC_CHNLS)
	{
		ERR_STATE = ERROR_TOO_MANY_CHANNELS;
	}

	else
	{
		uint8_t au8_Modules_loop = ZERO;

		/*Channels Loop Variables*/
		uint8_t au8_Length = ZERO;
		uint8_t au8_Channels_loop = ZERO;

		for(au8_Modules_loop = 0 ; au8_Modules_loop < ADC_USED ; au8_Modules_loop++)
		{
			/*First Enable Module CK*/
			switch(ADC_CONFIG_ARR.ADC_Module_Used_CK)
			{
				case ADC1_CK:

					/*Enable ADC1 Clock*/
					RCC->APB2ENR |= RCC_APB2ENR_ADC1CK_EN;

				break;

				case ADC2_CK:

					/*Enable ADC2 CLock*/
					RCC->APB2ENR |= RCC_APB2ENR_ADC2CK_EN;

				break;

				case ADC3_CK:

					/*Enable ADC3 Clock*/
					RCC->APB2ENR |= RCC_APB2ENR_ADC3CK_EN;

				break;

				default:

					/*Save error wrong module config*/
					ERR_STATE = ERROR_WRONG_MODULE;
				break;
			}

			/*Check for num of conversion inserted*/
			if((ADC_CONFIG_ARR.CHnl_Len) > MAX_CONV_LENGTH)
			{
				ERR_STATE = ERROR_TOO_MUCH_CONVERSIONS;
			}

			else;

			/*Check if Module was correct*/
			if(ERR_STATE == E_OK)
			{
				uint8_t current_Pos = 0;

				/*Save init state*/
				gu8_AdcInit_Status = MODULE_INIT;

				/*Adding 1 cause Channel length "1" = Zero in bits allocation value*/
				au8_Length += (ADC_CONFIG_ARR.CHnl_Len + 1 );

				/*choose scan mode or regular mode*/
				ADC_CONFIG_ARR.ADC_Module->CR1 |= (ADC_CONFIG_ARR.Scan_Mode) << ADC_CR1_SCAN_SHIFT;
				ADC_CONFIG_ARR.ADC_Module->CR1 |= (ADC_CONFIG_ARR.Disc_Mode) << ADC_CR1_DISC_REGULAR_SHIFT;

				/*Config Resolution*/
				ADC_CONFIG_ARR.ADC_Module->CR1 |= (ADC_CONFIG_ARR.Resolution) << ADC_CR1_RESOLUTION_SHIFT;

				/*Alignment*/
				ADC_CONFIG_ARR.ADC_Module->CR2 |= (ADC_CONFIG_ARR.Bit_Alignment) << ADC_CR2_ALIGN_SHIFT;

				/*Set Trigger*/
				ADC_CONFIG_ARR.ADC_Module->CR2 |= (ADC_CONFIG_ARR.Trigger_Polarity) << ADC_CR2_POLARITY_SHIFT;
				ADC_CONFIG_ARR.ADC_Module->CR2 |= (ADC_CONFIG_ARR.Conv_Trigger) << ADC_CR2_EXSEL_SHIFT;

				/*Set Regular Interrupt*/
				ADC_CONFIG_ARR.ADC_Module->CR1 |= (ADC_CONFIG_ARR.Irq_State) << ADC_CR1_IRQ_SHIFT;

				/*Set Channel Length*/
				ADC_CONFIG_ARR.ADC_Module->SQR[SQR1] |= (ADC_CONFIG_ARR.CHnl_Len) << ADC_LENGTH_SHIFT;

				/*Check For Continous Or Single Mode*/
				ADC_CONFIG_ARR.ADC_Module->CR2 |= (ADC_CONFIG_ARR.Continous_Mode) << ADC_CONTINOUS_SHIFT;

				ADC_CONFIG_ARR.ADC_Module->CR2 |= (ADC_CR2_ON) << ADC_CR2_ON_SHIFT;



				/*ADD Channels To list*/
				for( ; au8_Channels_loop < au8_Length ; au8_Channels_loop++)
				{
					current_Pos = (CHANNEL_BITS_WIDTH * au8_Channels_loop);

					if(current_Pos >= LAST_CHANNEL_BIT)
						current_Pos = 0;

					ADC_CONFIG_ARR.ADC_Module->SQR[REGISTERS_SQR_NUM - (au8_Channels_loop / REGISTER_MAX_CHANNELS_NO)]
										|= (ADC_CONFIG_ARR.Chnl_Used[au8_Channels_loop]) <<(current_Pos);
				}

				/*Configure Software Trigger*/
				ADC_CONFIG_ARR.ADC_Module->CR2 |= (ADC_CONFIG_ARR.Software_Trig) << ADC_CR2_SOFTWARE_SHIFT;
			}

			else;
		}
	}

	return ERR_STATE;
}

ERROR_STATUS ADC_Read(uint16_t *Ptr_ADC_Val , uint8_t ADC_Module)
{
	/*Create Error state Var*/
	ERROR_STATUS ERR_STATE = E_OK;

	/*Check if module init or NOT*/
	if(gu8_AdcInit_Status == MODULE_INIT)
	{
		/*Check For NULL Ptr*/
		if(Ptr_ADC_Val == NULL)
		{
			/*Save Null Error*/
			ERR_STATE = ERROR_ADC_BASE + ERROR_NULL_PTR_INIT;
		}

		else
		{
			/*Check which adc to read from*/
			switch(ADC_Module)
			{
				case ADC_MODULE_1:

					*Ptr_ADC_Val = ADC1->DR;

				break;

				case ADC_MODULE_2:

					*Ptr_ADC_Val = ADC2->DR;

				break;

				case ADC_MODULE_3:

					*Ptr_ADC_Val = ADC3->DR;

				break;

				default:

					/*Save Error wrong module*/
					ERR_STATE = ERROR_ADC_BASE + ERROR_WRONG_MODULE;

				break;
			}
		}
	}

	else
	{
		ERR_STATE = ERROR_ADC_BASE + ERROR_MODULE_NOT_INIT;
	}

	/*Return Error*/
	return ERR_STATE;
}
