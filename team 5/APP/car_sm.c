/*
 * car_sm.c
 *
 * Created: 2/18/2020 8:02:47 PM
 *  Author: MENA
 */ 

#include "car_sm.h"
#include "Steering.h"
#include "TimerDelay.h"
#include "Us.h"
/*******************       States of state machine       *********/

#define FORWARD_STATE 0
#define BACKWARD_STATE 1
#define TURNING_STATE 2
#define STOP_STATE 3

#define	CAR_SPEED 30

#define DISTANCE_TURNNING 40
#define DISTANCE_BACKWARDING 20


uint8_t g_state ;

/*
 * Fun----------: ERROR_STATUS Car_SM_Init(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: Initiate the car state machine with state"stop_state",
 * -------------- And initiate steering and ultrasonic functions
*/


ERROR_STATUS Car_SM_Init(void){
	
	ERROR_STATUS state_error = E_OK ;
	
	state_error |= Steering_Init();
	
	state_error |= Us_Init();
	
	g_state=STOP_STATE ;
	
	return state_error ;
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


ERROR_STATUS Car_SM_Update(void){
	
	uint16_t distance;
	ERROR_STATUS state_error = E_OK ;
	
	state_error |= Us_Trigger();
	state_error |= Us_GetDistance(&distance);
	
	switch(g_state){
		
		case STOP_STATE :
			if (distance<DISTANCE_BACKWARDING){
				
				g_state = BACKWARD_STATE ;
			}
			else if ((distance <= DISTANCE_TURNNING) && ( distance >= DISTANCE_BACKWARDING)){
				
				g_state =TURNING_STATE ;
			}else
				g_state = FORWARD_STATE ;
			break;
			
		case FORWARD_STATE :
		
			if (distance<DISTANCE_BACKWARDING){
				g_state = BACKWARD_STATE;
			}else if ( distance<=DISTANCE_TURNNING && distance >= DISTANCE_BACKWARDING )
			{
				g_state=TURNING_STATE;
			}
			else
				state_error |= Steering_SteerCar(CAR_FORWARD,CAR_SPEED);
			break;
				
		case BACKWARD_STATE:
		
			if (distance<DISTANCE_BACKWARDING){
				state_error |= Steering_SteerCar(CAR_BACKWARD,CAR_SPEED);
			}else if (distance <= DISTANCE_TURNNING && distance>=DISTANCE_BACKWARDING )
			{
				g_state=TURNING_STATE;
			}
			 else{
				g_state = FORWARD_STATE ;
			}
			break;
			
		case TURNING_STATE :
		
			if (distance <= DISTANCE_TURNNING && distance >= DISTANCE_BACKWARDING )
			{
				state_error |= Steering_SteerCar(CAR_LEFT,CAR_SPEED);
			}else if (distance <DISTANCE_BACKWARDING){
				g_state = BACKWARD_STATE ;
			}
			else
			g_state = FORWARD_STATE ;
			
			break;
			
		default: 
		
		state_error |= E_NOK ;
		
	}
	
	
	return state_error ;
	
}

