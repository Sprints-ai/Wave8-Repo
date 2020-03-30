/*
 * ICU.c
 *
 * Created: 2/16/2020 4:22:38 PM
 *  Author: Reem
 */ 
#include "../../MCAL/includes/interrupts.h"
#include "../../MCAL/includes/DEI.h"
#include "../includes/SWICU.h"


/*************************************************************************/
/*                     Globals Declaration                               */
/*************************************************************************/
/*
static volatile uint8_t gu8_ReadingFlag;

static uint8_t gu8_ICU_ReadingMode;*/

static uint16_t gu16_no_of_counts;
static uint32_t gu32_no_of_ovf;
static volatile uint8_t gu8_no_of_ISR_Entrance;
static volatile uint8_t gu8_EdgeFlag;
static Icu_cfg_s gstr_IcuCfg;
static uint8_t gu8_ICU_InitFlag = FALSE;

/*************************************************************************
 *                  Static Function Prototypes                           *
 *************************************************************************/
static void SWICU_INT_CBK(void);
/*************************************************************************
 *                   Function implementation                             * 
 *************************************************************************/
/* 
 * Function 	: Icu_Init                                                *
 * Input 		: Icu_cfg : pointer to structure of type Icu_cfg_s        *
 * Return 		: value of type ERROR_STATUS							  *
 * 				  which is one of the following values:					  *
 * 				  - E_OK  : initialized successfully					  *
 *				  - E_NOK : not initialized successfully				  *
 * Description  : Initializes the ICU by initializing the timer			  *
 * 				  and initializing the interrupt pin	         		  *
 */
ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg){
	ERROR_STATUS ERR = E_OK;
	if (gu8_ICU_InitFlag == FALSE)
	{
		if (Icu_Cfg == NULL)
		{
			ERR = E_NULL_PTR;
		}
		else{
			DIO_Cfg_s astr_dio_Cfg;
			DIO_Cfg_s astr_dio_Debug;
			Timer_cfg_s astr_timer_cfg;
			switch(Icu_Cfg->ICU_Ch_No){
				case ICU_CH2:
				//define the interrupt pin as INPUT
				astr_dio_Cfg.GPIO =DEI_ICU_PORT;
				astr_dio_Cfg.dir =INPUT;
				astr_dio_Cfg.pins=DEI_ICU_PIN;
				
				ERR = DIO_init(&astr_dio_Cfg);
				
				astr_dio_Debug.GPIO = GPIOA;
				astr_dio_Debug.pins =(BIT0 | BIT1|BIT2);
				astr_dio_Debug.dir = OUTPUT;
				DIO_init(&astr_dio_Debug);
				
				if (ERR == E_OK)
				{
					ERR = DEI_Init(ICU_CH2);
					if (ERR == E_OK)
					{
						switch(Icu_Cfg->ICU_Ch_Timer){
							//Timer channel 0
							case ICU_TIMER_CH0:
							//initializing the timer
							astr_timer_cfg.Timer_CH_NO = ICU_TIMER_CH0;
							astr_timer_cfg.Timer_Mode =TIMER_MODE;
							astr_timer_cfg.Timer_Polling_Or_Interrupt =TIMER_POLLING_MODE;
							astr_timer_cfg.Timer_Prescaler= ICU_Prescale_No
							ERR = Timer_Init(&astr_timer_cfg);
							
							if(ERR == E_OK)
							{
								//Initialize globals
								/*

								gu8_ReadingFlag = FALSE;
								
								*/
								gu32_no_of_ovf=0;
								gu16_no_of_counts=0;
								gu8_no_of_ISR_Entrance=0;
								gu8_EdgeFlag = FALSE;
								gu8_ICU_InitFlag =TRUE;
								gstr_IcuCfg = *Icu_Cfg;
								
							}
							
							break;
							
							//Invalid timer channel
							default:
							return E_INVALID_PARAMETER;
							break;
						}
					}
				}
				break;
				
				//Invalid DEI Channel
				default:
				return E_INVALID_PARAMETER;
				break;
			}
		}
	}
	else
	{
		ERR = E_MULTIPLE_INITIALIZION;
	}
	return ERR;
}

/*
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
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful								   *
 * Description	: Enable the Digital external interrupt and global interrupt
 *                calculates the time between 2 edges				       *
 */
ERROR_STATUS Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint32_t * Icu_Time){
	ERROR_STATUS ERR = E_NOK;
	float af_tickTimeInMicros = 0.0;
	if(gu8_ICU_InitFlag)
	{
		ERR =E_OK;
		if (Icu_Channel == gstr_IcuCfg.ICU_Ch_Timer)
		{
			if (Icu_Time == NULL)
			{
				ERR = E_NULL_PTR;
			}
			else
			{
				switch(Icu_EdgeToEdge)
				{
					case ICU_RISE_TO_FALL:
					gu8_EdgeFlag = TRUE;
					gu8_no_of_ISR_Entrance=0;
					if (gu8_no_of_ISR_Entrance == 0)
					{
						ERR = DEI_setMode(gstr_IcuCfg.ICU_Ch_No,DEI_MODE_RISING,SWICU_INT_CBK);
					}
					if (ERR == E_OK)
					{
						
						while(gu8_no_of_ISR_Entrance == 0);
						ERR = DEI_setMode(gstr_IcuCfg.ICU_Ch_No,DEI_MODE_FALLING,SWICU_INT_CBK);
						if (ERR == E_OK)
						{
							while(gu8_no_of_ISR_Entrance != 2);
							af_tickTimeInMicros =(ICU_Prescale/FCPU_HZ);
							//(*Icu_Time) =  (gu16_no_of_counts*af_tickTimeInMicros);
							(*Icu_Time) =  (gu16_no_of_counts*af_tickTimeInMicros)+(gu32_no_of_ovf*_8BIT_RESOLUTION_*af_tickTimeInMicros);
						}
					}
					break;
					
					default:
					ERR = E_INVALID_PARAMETER;
					break;
				}
				
				ERR = E_OK;
			}
		}
		else
		{
			ERR = E_INVALID_PARAMETER;
		}
	}
	else
	{
		ERR = E_UNINITIALIZED_MODULE;
	}
	return ERR;
}

static void SWICU_INT_CBK(void)
{
	
	if(gu8_EdgeFlag == TRUE)
	{
		gu8_EdgeFlag = FALSE;
		gu8_no_of_ISR_Entrance  =1;
		Timer_Start(gstr_IcuCfg.ICU_Ch_Timer,0);
	}
	else
	{
		Timer_Stop(gstr_IcuCfg.ICU_Ch_Timer);
		gu8_no_of_ISR_Entrance  =2;
		Timer_GetValue(gstr_IcuCfg.ICU_Ch_Timer, &gu16_no_of_counts);
		Timer_GetNoOfOVFS(gstr_IcuCfg.ICU_Ch_Timer, &gu32_no_of_ovf);
	}
		
}