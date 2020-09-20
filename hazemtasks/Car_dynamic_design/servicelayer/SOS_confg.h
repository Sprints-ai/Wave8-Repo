/*
 * TMU_confg.h
 *
 * Created: 2/24/2020 6:27:12 PM
 *  Author: hazem
 */ 
#ifndef TMU_CONFG_H_
#define TMU_CONFG_H_
/*- INCLUDES -----------------------------------------------*/

#include "..\common\Error_handling.h"

/*- CONSTANTS ----------------------------------------------*/


#define   BUFFER_SIZE    5 /*you can choose how many tasks wanted to add to scheduler*/
#define   RESOLUTION     1  /*you can choose resulotion of 1msec to multiple of 1 */
#define   SOS_TIMER_ID TIMER_2/*you can choose any of the 3 timer_sos note the timer you choose must be exculice to os */



#endif /* TMU_CONFG_H_ */