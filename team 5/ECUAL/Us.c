/*
 * Us.c
 *
 * Created: 2/18/2020 4:09:24 PM
 *  Author: MENA
 */ 

#include "Us.h"
#include "TimerDelay.h"
#include "ICU.h"


/****************************************************************************************************
 * Function Name   : Us_Init.                                                                       *
 * Input Parameters : None.                                                                         *                                                                   *                                                                                                *
 * Output Parameters: None.                                                                         *
 * In_Out Parameters: None.                                                                         *
 * Return           : ERROR_STATUS.                                                                 *
 * Description      : This function initiate the UltraSonic by initiate the ICU to use it to calculate the *
 *                    On time of the ECHO signal.                                                   *
 *                                                                                                  *
 *                                                                                                  *
 ***************************************************************************************************/


ERROR_STATUS Us_Init(void){
	
		Icu_cfg_s icuCfg;
		icuCfg.ICU_Ch_Timer = ICU_TIMER_CH0;
		icuCfg.ICU_Ch_No = ICU_CH2;
		Icu_Init(&icuCfg);
		return E_OK ;
}




/**************************************************************************************************
 * Function Name    : Us_Trigger.                                                                 *
 * Input Parameters : None.                                                                       *                                                                              *                                                                                                *
 * Output Parameters: None.                                                                       *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS                                                                *
 * Description      : This function initialize the trigger by set the value of the Dio_Dirction of *
 *                    the pin trigger as an output then send the  pulse, to trigger pin of the UltraSonic to enhance  *
 *                    the  EChO signal                                                            *
 *************************************************************************************************/




ERROR_STATUS Us_Trigger(void){
	
	uint8_t a_u8_error_state = E_OK ;
	
	DIO_Cfg_s dioCfgtrig;
	
	/*initialize trigger pin */
	
	dioCfgtrig.GPIO = GPIOC;
	dioCfgtrig.pins = BIT7;
	dioCfgtrig.dir =OUTPUT;
	a_u8_error_state |= DIO_init(&dioCfgtrig);
	
	/*send trigger*/
	
	a_u8_error_state |=DIO_Write(GPIOC,BIT7,HIGH)	;
	
	a_u8_error_state |=timerDelayMs(10);
	
	a_u8_error_state |=DIO_Write(GPIOC,BIT7,LOW)	;
	
	return a_u8_error_state;
	
}



/**************************************************************************************************
 * Function Name    : Us_GetDistance.                                                             *
 * Input Parameters : pointer to uint16 that will return the distance on it.                      *                                                                                              *                                                                                                *
 * Output Parameters: Distance.                                                                   *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS.                                                               *
 * Description      : This function get the time of high signal of ECUO pulse, then               *
 *                    use it to calculate the distance, then return the value in the              *
 *                    Distance parameter.                                                         *
 *************************************************************************************************/



ERROR_STATUS Us_GetDistance(uint16_t *Distance){
	
		uint8_t a_u8_error_state = E_OK ;
		uint32_t a_u32_timeOfTicks_Us  ;
		
		if (Distance==NULL)
		{
			a_u8_error_state |= E_NOK ;
		}else{
			
			// read timer from ICU
			
			a_u8_error_state |= Icu_ReadTime(ICU_TIMER_CH0,ICU_RISE_TO_FALL,&a_u32_timeOfTicks_Us);
			
			
			/* timeofticks is  time in microsecond returned from ICU (pulse time)*/
			
			
			*Distance = a_u32_timeOfTicks_Us/58 ;
		}
		
		return a_u8_error_state ;
	
}