/*
 *      file name  : "Us.h"
 *      Author: AMAYM  & GABER
 *      version : 1
 *
 */

#ifndef US_H_
#define US_H_


/************************************************************************/
/*				   MACROS	                            */
/************************************************************************/
#include "../Infrastructure/std_types.h"
/************************************************************************/
/*				   Defines	                            */
/************************************************************************/
#define NULL_PTR1					-1
#define MODULES_UNITIALIZED			-2
#define MULTIPLES_INIYIALIZATION	-3
#define INVALID_PARAMETERS			-4


/********** define error of the return functions inSICU module**********/
typedef sint8_t EnmUSError_t;
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



EnmUSError_t Us_Init(void);




/**************************************************************************************************
 * Function Name    : Us_Trigger.                                                                 *
 * Input Parameters : None.                                                                       *                                                                              *                                                                                                *
 * Output Parameters: None.                                                                       *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS                                                                *
 * Description      : This function send the  pulse, to trigger pin of the UltraSonic to enhance  *
 *                    the  ECUO signal                                                            *
 *************************************************************************************************/


EnmUSError_t Us_Trigger(void);





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


EnmUSError_t Us_GetDistance(uint16_t *Distance);


#endif /* US_H_ */