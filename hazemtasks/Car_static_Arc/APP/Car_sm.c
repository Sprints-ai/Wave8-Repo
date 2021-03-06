/*
 * Car_sm.c
 *
 * Created: 2/18/2020 9:13:56 PM
 *  Author: hazem
 */ 
/*************************************************************/
/*                     INCLUDES                              */
/*************************************************************/
#include "car_sm.h"
/*************************************************************/
/*                     API implementation                    */
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
ERROR_STATUS Car_SM_Init(void)
{
ERROR_STATUS ERROR=E_OK;

if(Us_Init()!=E_OK)
ERROR=E_NOK;
if(Steering_Init()!=E_OK)
ERROR=E_NOK;


return ERROR;
}

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
ERROR_STATUS ERROR=E_OK;
Us_Trigger();
uint16_t distance;
Us_GetDistance(&distance);
if(distance>=MAX_SPEED)
{
Steering_SteerCar(CAR_BACKWARD,INTERMEDIATE_SPEED);
}
else if((distance<MAX_SPEED)&&(distance>INTERMEDIATE_SPEED))
{
Steering_SteerCar(CAR_RIGHT,INTERMEDIATE_SPEED);
}
else if(distance<INTERMEDIATE_SPEED)
{
Steering_SteerCar(CAR_FORWARD,INTERMEDIATE_SPEED);
}

return ERROR;
}