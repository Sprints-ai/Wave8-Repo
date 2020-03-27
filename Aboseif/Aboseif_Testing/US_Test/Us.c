/*
 * Us.c
 *
 * Created: 2020-02-19 12:20:42 AM
 *  Author: EbrahimOseif
 */ 

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/


#include "Us.h"
#include "util/delay.h"


/************************************************************************/
/*				   functions' prototypes	                            */
/************************************************************************/

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

/* each var should has the type defined first event its user defined */

ERROR_STATUS Us_Init(void)
{
	ERROR_STATUS u8_status = E_OK;
	
	/* initialize pin3 TRIGGER  as output */
	DIO_Cfg_s str_Dio = {
		GPIOB,
		PIN3,
		OUTPUT
	};
	
	u8_status = DIO_init(&str_Dio);
	

	/* initialize icu on EXT INT2 and timer0 */
	Icu_cfg_s str_Icu = {
	ICU_CH2,
	ICU_TIMER_CH0
	};
	u8_status = Icu_Init(&str_Icu);
	
	return u8_status;
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
{
	ERROR_STATUS status = E_OK;
	/* Trigger pulse */
	
	status =  DIO_Write(GPIOB, PIN3, HIGH);
		_delay_ms(1); /* use timers delay */ 
		
	status =  DIO_Write(GPIOB, PIN3, LOW);
	
	/*PORTB_DATA |= (1<<3);
	_delay_ms(1);
	PORTB_DATA &= ~(1<<3);
	*/
	return status;
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


ERROR_STATUS Us_GetDistance(uint8_t *Distance)
{
	ERROR_STATUS u8_status = E_OK;
	uint16_t u16_timecount = 0;
	u8_status =  Icu_ReadTime(ICU_TIMER_CH0, ICU_RISE_TO_FALL , &u16_timecount);
		
		
		/*58 to map time to distance */
/* turn into multiplication
		*Distance = u16_timecount / 58;
*/
		/* magic numbers  */
		*Distance = u16_timecount * 0.0172 ;

		
	//PORTD_DATA = *Distance;
	
	return u8_status;
}
