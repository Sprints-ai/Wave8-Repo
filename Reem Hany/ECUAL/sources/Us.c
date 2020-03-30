/*
 * Us.c
 *
 * Created: 2/16/2020 4:32:03 PM
 *  Author: Reem
 */ 
#include "../includes/SWICU.h"
#include "../includes/Us.h"
#include "../../Services/includes/softwareDelay.h"

/****************************************************************************************************
 * Function Name   : Us_Init.                                                                       *
 * Input Parameters : None.                                                                         *                                                                   *                                                                                                *
 * Output Parameters: None.                                                                         *
 * In_Out Parameters: None.                                                                         *
 * Return           : ERROR_STATUS.                                                                 *
 * Description      : This function initiate the UltraSonic by set the value of the Dio_Dirction of *
 *                    the pin trigger as an output then initiate the ICU to use it to calculate the *
 *                    On time of the ECHO signal.                                                   *
 *                                                                                                  *
 *                                                                                                  *
 ***************************************************************************************************/



ERROR_STATUS Us_Init(void)
{
	Icu_cfg_s astr_icuCfg;
	DIO_Cfg_s astr_dioCfg;
	ERROR_STATUS ERR;
	
	astr_icuCfg.ICU_Ch_Timer = ICU_TIMER_CH0;
	astr_icuCfg.ICU_Ch_No =ICU_CH2;
	
	ERR = Icu_Init(&astr_icuCfg);
	if( ERR== E_OK)
	{
		
		astr_dioCfg.GPIO =TRIGGER_PORT;
		astr_dioCfg.pins =TRIGGER_PIN;
		astr_dioCfg.dir  =OUTPUT;
		
		ERR = DIO_init(&astr_dioCfg);	
	}
	return ERR;
}




/**************************************************************************************************
 * Function Name    : Us_Trigger.                                                                 *
 * Input Parameters : None.                                                                       *                                                                              *                                                                                                *
 * Output Parameters: None.                                                                       *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS                                                                *
 * Description      : This function send the  pulse, to trigger pin of the UltraSonic to enhance  *
 *                    the  ECUO signal                                                            *
 *************************************************************************************************/


ERROR_STATUS Us_Trigger(void){
	ERROR_STATUS ERR;
	ERR = DIO_Write(TRIGGER_PORT,TRIGGER_PIN,HIGH);
	if( ERR== E_OK)
	{
		softwareDelayUS(1);
		ERR = DIO_Write(TRIGGER_PORT,TRIGGER_PIN,LOW);
	}
	return ERR;
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

ERROR_STATUS Us_GetDistance(void){
	ERROR_STATUS ERR;
	uint16_t Distance;
	/*if(Distance != NULL)
	{*/
		uint32_t au32_timeInMicros;
	//	uint16_t val;
		ERR = Icu_ReadTime(ICU_TIMER_CH0,ICU_RISE_TO_FALL,&au32_timeInMicros);
		if( ERR == E_OK)
		{	
			(Distance) = (uint16_t)(au32_timeInMicros / 58);
			SharedRes_setDistanceVal(Distance);
			//UDR = Distance;
			
		}
	/*}
	else
	{
		ERR = E_NULL_PTR;
	}*/
	
}