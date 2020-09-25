/*
 * car_sm.c
 *
 * Created: 2020-02-19 9:20:53 AM
 *  Author: EbrahimOseif
 */

/************************************************************************/
/*				 INCLUDES										        */
/************************************************************************/

#include <stdlib.h>
#include "car_sm.h"

/************************************************************************/
/*				 Global / Static Variables						       */
/************************************************************************/

static uint8_t gu8_State = STOP;
static uint8_t gu8_Speed = 100;
volatile uint16_t gu16_US_Distance ;

/************************************************************************/
/*		         TIMER FUNCTIONS' implementation				        */
/************************************************************************/


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
ERROR_STATUS Car_SM_Update(void)
{
	ERROR_STATUS u8_status = E_OK;
	/* get the distance and switch to the corresponding state */
	if(gu16_US_Distance < RESOLUTION)
		gu8_State = BACK;
	else if((gu16_US_Distance >= RESOLUTION) && (gu16_US_Distance <= RESOLUTION + MARGIN))
		gu8_State = RIGHT;
	else if(gu16_US_Distance >= RESOLUTION + MARGIN)
		gu8_State = MOVE;
	else
		gu8_State = MOVE;

	/* switch on the state calculated by distance */
	switch(gu8_State)
	{
		case MOVE:
			Steering_SteerCar(CAR_FORWARD, gu8_Speed);
			break;
		case BACK:
			Steering_SteerCar(CAR_BACKWARD, gu8_Speed);
			break;
		case RIGHT:
			Steering_SteerCar(CAR_RIGHT, gu8_Speed);
			break;
		case LEFT:
			Steering_SteerCar(CAR_LEFT, gu8_Speed);
			break;
		default:
			Steering_SteerCar(CAR_STOP, gu8_Speed);
			break;
	}

	return u8_status;
}
