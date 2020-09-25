/*
 *      ICU.h
 *
 *      Author: Ahmed Ashraf
 *      Version: 1.0
 */

#ifndef __ICU_H__
#define __ICU_H__

/************************************************************************/
/*				               Constants                                */
/************************************************************************/

#define ICU_CH0					(0)			/* defines External Interrupt 0 */
#define ICU_CH1					(1)       	/* defines External Interrupt 1 */
#define ICU_CH2					(2)			/* defines External Interrupt 2 */

#define ICU_TIMER_CH0			(0)			/* defines Timer 0 */
#define ICU_TIMER_CH1			(1)			/* defines Timer 1 */
#define ICU_TIMER_CH2			(2)			/* defines Timer 2 */

/*ICU Time measurement modes*/
#define ICU_RISE_TO_RISE		(0)
#define ICU_RISE_TO_FALL		(1)
#define ICU_FALL_TO_RISE		(2)
#define ICU_COUNT_CAPT_RISING	(3)
#define ICU_COUNT_CAPT_FALLING	(4)

/*Error definition status*/
#define E_OK					(1)
#define E_NOK		            (-1)

/************************************************************************/
/*						User typedef defines                          	*/
/************************************************************************/

typedef sint8_t ERROR_STATUS;

/************************************************************************/
/*				          Functions' Prototypes                         */
/************************************************************************/

/**************************************************************************
 * Function 	: Icu_Init                                                *
 * Input 		: @param ICU_Ch_No (channel number)						  *
 *				  @param ICU_Ch_Timer (Timer used in ICU)				  *
 * Return 		: value of type ERROR_STATUS							  *
 * 				  which is one of the following values:					  *
 * 				  - E_OK  : initialized successfully					  *
 *				  - E_NOK : not initialized successfully				  *
 * Description  : Initializes the ICU by initializing the timer			  *
 * 				  and enabling the global interrupt						  *
 **************************************************************************/
ERROR_STATUS Icu_Init(uint8_t ICU_Ch_No, uint8_t ICU_Ch_Timer);

/***************************************************************************
 * Function		: ICU_ReadTime                                             *
 * Input		:														   *
 *				ICU_Channel --> ICU timer channel						   *
 *									- ICU_TIMER_CH0						   *
 *									- ICU_TIMER_CH1						   *
 *									- ICU_TIMER_CH2						   *
 *				ICU_EdgeToEdge -- > edges to calculate pusle time between: *
 *									- ICU_RISE_TO_RISE					   *
 *									- ICU_RISE_TO_FALL                     *
 *									- ICU_FALL_TO_RISE					   *
 *									- ICU_COUNT_CAPT_RISING				   *
 *									- ICU_COUNT_CAPT_FALLING			   *
 * Output 		: ICU_Time : pointer to uint32 variable to give the time   *
 * 				  from falling edge to rising edge						   *
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful								   *
 * Description	: calculates the time between 2 edges				       *
 ***************************************************************************/
ERROR_STATUS Icu_ReadTime(uint8_t ICU_Channel, uint8_t ICU_EdgeToEdge, uint32_t * ICU_Time);

#endif /*__ICU_H__*/