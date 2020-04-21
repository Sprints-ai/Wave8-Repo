/*
 * External_INT.h
 *
 * Created: 2/18/2020 12:41:38 PM
 *  Author: Ema
 */ 


#ifndef EXTERNAL_INT_H_
#define EXTERNAL_INT_H_

/************************************************************************/
/*				               Includes                                 */
/************************************************************************/
#include "../Infrastructure/std_types.h"
#include "../Infrastructure/registers.h"
#include "../MCAL/DIO.h"

/************************************************************************/
/*				               Constants                                */
/************************************************************************/

#define EXTERNAL_INT_CH0			(0)			/* defines External Interrupt 0 */
#define EXTERNAL_INT_CH1			(1)       	/* defines External Interrupt 1 */
#define EXTERNAL_INT_CH2			(2)			/* defines External Interrupt 2 */

#define EdgeRisiging				(3)			/* defines External Interrupt to work with risingEdge */
#define EdgeFalling					(2)			/* defines External Interrupt to work with fallingEdge */

/************************************************************************/
/*				          Functions' Prototypes                         */
/************************************************************************/

/**************************************************************************
 * Function 	: External_INT_Enable                                     *
 * Input 		: INT_CH : Interrupt channel					          *
 *				  -EXTERNAL_INT_CH0										  *
 *				  -EXTERNAL_INT_CH1										  *
 *				  -EXTERNAL_INT_CH2										  *
 *				: EDGE  : The edge to trigger the interrupt				  *
 *				  -EdgeRising											  *
 *				  -EdgeFalling											  *
 * Return 		: No output												  *
 * Description  : Initializes the External interrupt by initializing the  *
 * 				   pin and enabling the global interrupt				  *
 **************************************************************************/
extern void External_INT_Init(uint8_t INT_CH,uint8_t EDGE,void(*CBK_FN)(void));

/**************************************************************************
 * Function 	: External_INT_Enable                                     *
 * Input 		: INT_CH : Interrupt channel					          *
 *				  -EXTERNAL_INT_CH0										  *
 *				  -EXTERNAL_INT_CH1										  *
 *				  -EXTERNAL_INT_CH2										  *
 *				: EDGE  : The edge to trigger the interrupt				  *
 *				  -EdgeRising											  *
 *				  -EdgeFalling											  *
 * Return 		: No output												  *
 * Description  : Enable the External interrupt and set the edge to		  *
 * 				   trigger the interrupt								  *
 **************************************************************************/
extern void External_INT_Enable(uint8_t INT_CH,uint8_t EDGE);


#endif /* EXTERNAL_INT_H_ */