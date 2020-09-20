/*
* Us.c
*
* Created: 2/18/2020 3:24:26 PM
*  Author: hazem
*/

#include "Us.h"
/****************************************************************************************************
 * Function Name   : Us_Init.                                                                       *
 * Input Parameters : None.                                                                         *                                                                   *                                                                                                *
 * Output Parameters: None.                                                                         *
 * In_Out Parameters: None.                                                                         *
 * Return           : ERROR_STATUS.                                                                 *
 * Description      : This function initiate the UltraSonic by set the value of the Dio_Dirction of *
 *                    the pin trigger as an  then initiate the ICU to use it to calculate the *
 *                    On time of the ECHO signal.                                                   *
 *                                                                                                  *
 *                                                                                                  *
 ***************************************************************************************************/


ERROR_STATUS Us_Init(void)
{
	ERROR_STATUS ERROR=E_OK;
   DIO_Cfg_s u8_instance={GPIOB,BIT3,OUTPUT};
	DIO_init(&u8_instance);
   u8_instance.pins=BIT2;
   u8_instance.dir=INPUT;
	 DIO_init(&u8_instance);
	Icu_cfg_s US_INST_CFG={ICU_CH2,ICU_TIMER_CH0};
	
	if(Icu_Init(&US_INST_CFG)==E_OK)
	{
		ERROR=E_OK;
	}
	else
	{
		ERROR=E_NOK;
	}

	return ERROR;
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
ERROR_STATUS Us_Trigger(void)
{ERROR_STATUS ERROR=E_OK;
	if(DIO_Write(GPIOB,BIT3,HIGH)==E_NOK)
	ERROR=E_NOK;
softwareDelayUS(1);
	if(DIO_Write(GPIOB,BIT3,LOW)==E_NOK)
	ERROR=E_NOK;
softwareDelayUS(1);	
	
	return ERROR;
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


ERROR_STATUS Us_GetDistance(uint16_t *Distance)
{ 
	ERROR_STATUS ERROR=E_OK;
	uint32_t TIME=0;
	if(Icu_ReadTime(ICU_CH2,ICU_RISE_TO_FALL,&TIME)==E_NOK)
	ERROR=E_NOK;
   *Distance=TIME;	
return ERROR;	
}

void Us_mainfunc(void)
{
	uint16_t distance;
	Us_Trigger();
	Us_GetDistance(&distance);
	SharedRes_setDistanceVal(distance);
	
}