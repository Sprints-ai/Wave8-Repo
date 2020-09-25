/*
 * File		: car_sm.h
 * Created	: 12/21/2019 5:56:37 PM
 * Author	: Amr, Abdo
 * Version	: v1.0
 */

/*************************************************************/
/*                     INCLUDES                              */
/*************************************************************/
#ifndef CAR_SM_H_
#define CAR_SM_H_

#include "../Service/std_types.h"
#include "steering.h"
#include "../ECUAL/us.h"

/************************************************************************/
/*				 DEFINES			        */
/************************************************************************/
#define		STOP			0
#define		MOVE			1
#define		RIGHT			2
#define		LEFT			3
#define		BACK			4


#define     RESOLUTION		50
#define		MARGIN 			20

extern volatile uint16_t  gu16_US_Distance ;

/*
 * Fun----------: ERROR_STATUS Car_SM_Update(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: changes car state according to the ultrasonic input
 * -------------- And represents the motors output for each state
*/
extern ERROR_STATUS Car_SM_Update(void);

#endif /* CAR_SM_H_ */
