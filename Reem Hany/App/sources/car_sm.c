/*
 * car_sm.c
 *
 * Created: 2/16/2020 4:21:29 PM
 *  Author: Reem
 */ 
#include "../includes/car_sm.h"
#include "../../RTE/includes/SharedResources.h"
#include "../../ECUAL/includes/LCD.h"

/*Globals*/
static uint8_t gu8_CurrentState;

static void convertIntToStr(uint16_t N,uint8_t * str,uint8_t * size)
{
	uint8_t data[10],i=0,j;
	while (N>0)
	{
		data[i]=(N%10)+48;
		N/=10;
		i++;
	}
	for(j=0;j<i;j++){
		str[j]=data[j];
	}
	(*size) = i;
}

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
ERROR_STATUS Car_SM_Init(void){
	ERROR_STATUS ERR;
	ERR =Steering_Init();
	if(ERR ==E_OK){
		Steering_SteerCar(CAR_STOP,0);
		gu8_CurrentState =FORWARD_STATE;
		
	}
	return ERR;
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
	
	ERROR_STATUS ERR;
	uint16_t Distance=0,numSize,i=0,j=0;
	char distanceStr[20],FullStr[50],str[20]="Distance=";
	//Read the distance
	SharedRes_getDistanceVal(&Distance);
	convertIntToStr(Distance,distanceStr,&numSize);
	while (str[i]!='\0')
	{
		FullStr[i]=str[i];
		i++;
	}
	UDR = 3;
	j=numSize;
	while(TRUE)
	{
		j--;
		FullStr[i]=distanceStr[j];
		if(j==ZERO)
			break;
		i++;
	}
	
	DisplayData(FullStr);
	//in case status is error stop the car
	if(ERR != E_OK || Distance<5){
		gu8_CurrentState =STOP_STATE;
	}
		
	//In case the distance is greater than 30 cm the car will move forward
	else if(Distance >= 50){
		gu8_CurrentState =FORWARD_STATE;
	}
		
	//In case the distance is in range 25| 30 cm the car will turn
	else if(Distance >=27  && Distance <50){
		gu8_CurrentState = TURN_STATE;
	}
		
	//In case the distance is smaller than 25 cm the car will move backwards then turn
	else{
		gu8_CurrentState = BACKWARD_STATE;
	}
		
	//Switch the states
	switch(gu8_CurrentState)
	{
		/*************************************************/
		case FORWARD_STATE:
		ERR = Steering_SteerCar(CAR_FORWARD,25);
		break;
			
		/*************************************************/
		case TURN_STATE:
		ERR = Steering_SteerCar(CAR_LEFT,25);
	    break;
			
			
		/*************************************************/
		case BACKWARD_STATE:
			
		//Go backwards until the distance increases to be greater than or equal 25
		ERR = Steering_SteerCar(CAR_BACKWARD,25);
		break;
			
		/*************************************************/
			
		//In case there is an error the car will stop 
		case STOP_STATE:
		ERR = Steering_SteerCar(CAR_STOP,0);
		break;
			
		/*************************************************/
		default:
		ERR = E_INVALID_PARAMETER;
		break;
	}
	return ERR;
}