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

#include "../Infrastructure/std_types.h"

#define FORWARD_STATE				0
#define BACK_STATE					1
#define RIGHT_STATE					2

#define INITIAL_DISTANCE			0
#define MOTORS_SPEED				10
#define COUNTER_START_VALUE			0
#define OS_RESOLUTION				50
#define ACTION_DELAY				100

#define ERROR_CAR_SM_MODULE_ID		-100		
/*************************************************************/
/*                     FUNCTIONS DECLARATION                 */
/*************************************************************/

/**
 * Description: Initializes the Car State Machine 
 *
 * @return function status :
 *				- 0 -> E_NOK
 *				- 1 -> E_OK
 */
extern ERROR_STATUS Car_SM_Init(void);

/**
 * Description: updates the car status according to the distance between the car
 *				and the obstacle
 *
 * @return function status :
 *				- 0 -> E_NOK
 *				- 1 -> E_OK
 */
extern ERROR_STATUS Car_SM_Update(uint16_t u16_Distance);

#endif /* CAR_SM_H_ */