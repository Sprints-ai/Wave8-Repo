#include "TMU.h"
#include "TMU_cfg.h"


TMUError_t TMU_Init (const TMU_ConfigType * ConfigPtr)
{
	TMUError_t retVal = E_OK;


	if(ConfigPtr != NULL)
	{
	//	cli();										//disable the interrupts as this system is time trigger system so we use interrupts only with timer

		guTMU_TIMER = ConfigPtr->Timer_CH;			// save TMU_Timer channel

		switch(ConfigPtr->Timer_CH)
		{
			case TIMER_CH0:
			{
				Timer_cfg_s Timer_cfg = {TIMER_CH0,T0_COMP_MODE,TIMER_PRESCALER_64,T0_INTERRUPT_CMP,TMU_Set_Tick_Flag};
				retVal&=Timer_Init(&Timer_cfg);
				retVal&=Timer_Start(ConfigPtr->Timer_CH,COMP_VALUE);
			}
			break;
			case TIMER_CH1:
			{
				Timer_cfg_s Timer_cfg = {TIMER_CH1,T1_COMP_MODE_OCR1A_TOP,TIMER_PRESCALER_64,T1_INTERRUPT_CMP_1A,TMU_Set_Tick_Flag};
				retVal&=Timer_Init(&Timer_cfg);
				retVal&=Timer_Start(ConfigPtr->Timer_CH,COMP_VALUE);
			}
			break;
			case TIMER_CH2:
			{
				Timer_cfg_s Timer_cfg = {TIMER_CH2,T2_COMP_MODE,TIMER_PRESCALER_64,T2_INTERRUPT_CMP,TMU_Set_Tick_Flag};
				retVal&=Timer_Init(&Timer_cfg);
				retVal&=Timer_Start(ConfigPtr->Timer_CH,COMP_VALUE);
			}
			break;
			default:
			retVal = E_NOK;
			break;
		}
	}
	else
	{
		retVal = NULL_PTR;
	}

	return retVal;
}

TMUError_t TMU_DeInit (void)
{
	TMUError_t retVal = E_OK;


	if (guTMU_TIMER >= 0)
	{
		//cli();			// disable global interrupt so TMU functionality will stop
		Timer_Stop(guTMU_TIMER);
	}
	else
	{
		retVal = NO_INIT;

	}

	return retVal;
}

TMUError_t TMU_Start_Timer(const TMU_SW_Timer * SW_Timer)
{
	TMUError_t retVal = E_OK;

	if (SW_Timer != NULL)			//check null pointer error
	{
	    if(SW_Timer->Task_delay>0)
        {
            switch (SW_Timer->Delay_type)
		{
			case ONESHOOT:
			{
				if (Oneshoot_tasks_counter < BUFFER_SIZE)		//check oneshoot full buffer
				{
					Tasks_buffer[ONESHOOT][SW_Timer->TaskID] = SW_Timer->Task_delay;
					Oneshoot_tasks_counter++;
				}
				else
				{
					retVal = FULL_BUFFER;
				}
			}
			break;
			case PERIODIC:
			{
				if (Periodic_tasks_counter < BUFFER_SIZE)		//check periodic full buffer
				{
					Tasks_buffer[PERIODIC][SW_Timer->TaskID] = SW_Timer->Task_delay;
					Periodic_tasks_counter++;
				}
				else
				{
					retVal = FULL_BUFFER;
				}
			}
			break;
			default:
			retVal = E_NOK;
			break;
		}
        }
        else
        {
            retVal = E_NOK;
        }


		if(retVal == E_OK)				//check if no error occurs set call back function
		{
			/*set the call back function*/
			arrTask_CallBackfun[SW_Timer->Delay_type][SW_Timer->TaskID] = SW_Timer->Task_CallBackfun;

			//sei();			//enable interrupts to start getting the ISR after the first start
		}

	}
	else
	{
		retVal = NULL_PTR;
	}

	return retVal;
}

TMUError_t TMU_Stop_Timer(const TMU_SW_Timer * SW_Timer)
{
	TMUError_t retVal = E_OK;

	if( SW_Timer != NULL)
	{
		switch (SW_Timer->Delay_type)
		{
			case ONESHOOT:
			{
				if ((Oneshoot_tasks_counter > 0) && ((Tasks_buffer[ONESHOOT][SW_Timer->TaskID]) !=0))
				{
					Oneshoot_tasks_counter--;
					Tasks_buffer[ONESHOOT][SW_Timer->TaskID] = -1;
				}
				else
				{
					retVal = STOP_NO_START;
				}
			}
			break;
			case PERIODIC:
			{

				if ((Periodic_tasks_counter > 0) && ((Tasks_buffer[PERIODIC][SW_Timer->TaskID]) !=0))
				{
					Periodic_tasks_counter--;
					Tasks_buffer[PERIODIC][SW_Timer->TaskID] = -1;
				}
				else
				{
					retVal = STOP_NO_START;
				}

			}
			break;
			default:
			retVal = E_NOK;
			break;
		}

		if (retVal == E_OK)
		{
			arrTask_CallBackfun[SW_Timer->Delay_type][SW_Timer->TaskID] = NULL;
		}

	}
	else
	{
		retVal = NULL_PTR;
	}
	return retVal;
}

TMUError_t TMU_Dispatch(void)
{
	TMUError_t retVal = E_OK;

	uint8_t index =0;

	if(TMU_flag)
	{
		TMU_flag = 0;
		Tick_count++;

		/*Oneshoot*/

		while(Tasks_buffer[ONESHOOT][index])
		{
			if ((Tick_count % Tasks_buffer[ONESHOOT][index] == 0) && (Tick_count / Tasks_buffer[ONESHOOT][index] > 0))
			{
				arrTask_CallBackfun[ONESHOOT][index]();			//call back function call
				arrTask_CallBackfun[ONESHOOT][index]= NULL;		//reset call back function in the array of pointers to function
				Tasks_buffer[ONESHOOT][index] = -1;				//reset the delay in the TMU buffer
			}
			index++;
		}

		index = 0;
		/*periodic*/
		while((Tasks_buffer[PERIODIC][index] != 0)&&(index < BUFFER_SIZE))
		{
			if ((Tick_count % Tasks_buffer[PERIODIC][index] == 0))
			{
				arrTask_CallBackfun[PERIODIC][index]();			//call back function call
			}
			index++;
		}

	}


	return retVal;
}

void TMU_Set_Tick_Flag(void)
{
	TMU_flag = 1;
}
