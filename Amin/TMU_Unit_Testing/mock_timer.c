#include "mock_timer.h"


static volatile uint8_t Timer_ch;
static volatile uint8_t Timer_Mode;
static volatile uint8_t Timer_Prescaler;
static volatile uint8_t Timer_Interrupt_mode;
static void (*guTimer_Cbk_ptr)(void);

/*
uint8_t Timer_Ch;
	uint8_t Timer_Mode;
	uint8_t Timer_PreScaler;
	uint8_t Timer_Interrupt_Mode;
	void (*Timer_Cbk_ptr)(void);*/

ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg)
{
	ERROR_STATUS ERROR = E_OK;
	Timer_ch=Timer_cfg->Timer_Ch;
	switch(Timer_ch)
	{
		case TIMER_CH0:
		return E_OK;
		break;
		case TIMER_CH1:
		return E_OK;
		break;
		case TIMER_CH2:
		return E_OK;
		break;
		default:
		return E_NOK;
		break;
	}

	return E_NOK;
}


ERROR_STATUS Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count)
{
	ERROR_STATUS ERROR = E_OK;

	/*Start the timer according to the channel by setting the prescaler value, plus initializing the timer to get the desired number of ticks*/
	switch(Timer_CH_NO)
	{
		case TIMER_CH0:
		{
			if(Timer_Count>=0&&Timer_Count<=255)
			{
				return E_OK;
			}
			break;
		}

		case TIMER_CH1:
		{
			if(Timer_Count>=0&&Timer_Count<=65535)
			{
				return E_OK;
			}
			break;

		}
		break;
		case TIMER_CH2:
		{
			if(Timer_Count>=0&&Timer_Count<=255)
			{
				return E_OK;
			}
			break;
		}
		break;
		default:
		ERROR = E_NOK;
		break;
	}
	return ERROR;
}

ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO)
{
switch(Timer_CH_NO)
	{
		case TIMER_CH0:
		return E_OK;
		break;

		case TIMER_CH1:
		return E_OK;
		break;

		case TIMER_CH2:
		return E_OK;
		break;

		default:
		return E_NOK;
		break;

	}

	return E_NOK;

}

