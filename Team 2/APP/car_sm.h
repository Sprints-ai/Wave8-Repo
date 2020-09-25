/*
 ============================================================================
 Name        : car_sm.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef CAR_SM_H_
#define CAR_SM_H_


/*************************************************************/
/*                     INCLUDES                              */
/*************************************************************/

#include "../Common/std_types.h"
#include "../Common/common_macros.h"
#include "Steering.h"
#include "../HAL/Us.h"
#include "../Common/softwareDelay.h"


/*************************************************************/
/*                     DEFINITIONS                              */
/*************************************************************/
#define NEAR                           0
#define INTERMEDIATE                   1
#define FAR                            2

#define  NEAR_DISTANCE                 0
#define  INTERMEDIATE_DISTANCE         25
#define  FAR_DISTANCE                  35
#define  INITIAL_SPEED                 80
#define  FULL_SPEED                    100
#define  MEDIUM_SPEED                  50
#define  LOW_SPEED                     30
#define  DELAY_FOR_TURN                500
#define  DELAY_FOR_GET_NEW_READING     100

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
