/*
 * ICU.c
 *
 * Created: 2/17/2020 2:19:05 PM
 *  Author: Ema
 */ 

#include "ICU (1).h"

void SWICU_CBK(void)
{
	if(ICU_Edge == EdgeRisiging)     						//check if interrupt from rising edge
	{
		Error = Timer_Start(ICU_TIMER_CH0,0);				//TCNT0=0;	reset timer0 counter
		ICU_Edge = EdgeFalling;
		
		External_INT_Enable(ICU_CH2,ICU_Edge);				//trigger INT2 with falling edge
	}
	else
	{
		Error = Timer_Stop(ICU_TIMER_CH0);					//stop timer0
		read_flag = 1;										//set flag to read timer
									
	}
}

ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg)
{	
	ERROR_STATUS ERROR = E_OK;
	
	/*DIO_Cfg_s DIO_cfg_B2 = {GPIOB,BIT2,INPUT};*/
	ICU_Edge = EdgeRisiging;
	
	/*DIO_Cfg_s DIO_cfg_LEDS = {GPIOB,UPPER_NIBBLE,OUTPUT};
	DIO_init(&DIO_cfg_LEDS);*/
	
	Timer_cfg_s Timer_cfg_T0 ={TIMER_CH0,TIMER_MODE,TIMER_POLLING_MODE,TIMER_PRESCALER_1024};
	
	ENABLE_GINT;											//Enable global interrupt
	
	External_INT_Init(ICU_CH2,EdgeRisiging,SWICU_CBK);			    //Initialize INT2 with rising edge
	
	switch(Icu_Cfg->ICU_Ch_No)
	{
		case ICU_CH0:
		ERROR = E_NOK;
		break;
		case ICU_CH1:
		ERROR = E_NOK;
		break;
		case ICU_CH2:
		/*ERROR = DIO_init(&DIO_cfg_B2);*/
		break;
		default:
		ERROR = E_NOK;
		break;
	}	

	switch(Icu_Cfg->ICU_Ch_Timer)
	{
		case ICU_TIMER_CH0:
		ERROR = Timer_Init(&Timer_cfg_T0);
		break;
		case ICU_TIMER_CH1:
		ERROR = E_NOK;
		break;
		case ICU_TIMER_CH2:
		ERROR = E_NOK;
		break;
		default:
		ERROR = E_NOK;
		break;
	}

	return ERROR;
}

ERROR_STATUS Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint32_t * Icu_Time)
{
	ERROR_STATUS ERROR = E_OK;
	uint16_t Timer_read = 0;
	
	ICU_Edge = EdgeRisiging;
	
	switch(Icu_Channel)
	{
		case ICU_CH0:
		break;
		case ICU_CH1:
		ERROR = E_NOK;
		break;
		case ICU_CH2:
		{			
			switch(Icu_EdgeToEdge)
			{
				case ICU_RISE_TO_FALL:
				{
					External_INT_Enable(ICU_CH2,ICU_Edge);				//Enable INT2 with rising edge at first time 
					while (read_flag == 0)								//wait until a falling edge come and set the read_flag
					{
						if ((TIFR & 0x01))
						{
							//DIO_Write(GPIOB,BIT6,1);
							OVR_Flow_Counter++;
							TIFR = TIFR |0x01;
						}
					}							
					
					ERROR = Timer_GetValue(ICU_TIMER_CH0, &Timer_read);	// read the timer value
					read_flag = 0;
															//reset the read_flag to be able to read another (HIGH) time
				}
				break;
				case ICU_FALL_TO_RISE:
				ERROR = E_NOK;
				break;
				default:
				ERROR = E_NOK;
				break;
			}
		}
		break;
		default:
		ERROR = E_NOK;
		break;
	}
	
	*Icu_Time = (OVR_Flow_Counter*255)+Timer_read;
	OVR_Flow_Counter = 0;
	return ERROR;
}