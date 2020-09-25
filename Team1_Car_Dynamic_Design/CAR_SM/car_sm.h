/*
 * File		: car_sm.h
 * Author	: Ahmed Ashraf
 * Version	: v1.0
 */

#ifndef __CAR_SM_H__
#define __CAR_SM_H__

/************************************************************************/
/*                         General macros                               */
/************************************************************************/

#define		E_OK			(1)
#define		E_NOK			(-1)

/************************************************************************/
/*                        USer defined data types                       */
/************************************************************************/

typedef sint8_t	ERROR_STATUS;

/*************************************************************/
/*                     FUNCTIONS DECLARATION                 */
/*************************************************************/

/*
 * Fun----------: ERROR_STATUS Car_SM_Init(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: Initiate the car state machine with state"forward at speed 80%",
 * -------------- And initiate steering and ultrasonic functions
*/
ERROR_STATUS Car_SM_Init(void);

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
ERROR_STATUS Car_SM_Update(void);

#endif /* CAR_SM_H_ */