/*
 * main.c
 *
 * Created: 2020-03-26 11:05:40 AM
 *  Author: EbrahimOseif
 */ 

#include <stdio.h>
#include <stdlib.h>

#include "testing.h"



int main()
{
    signed char Expected = E_OK;
    signed char Actual = E_OK;
	char data = 0;


	
             printf("*****This is Unit Test for steering INIT  ***********\n\n");

	    printf("*****This is Unit Test for steering car  -  valid direction ***********\n");

    for(uint8_t i=0; i < 5; i++){


	     Actual= Testing_Steering_SteerCar( Direction_Valid_Data[i], DUTY_Valid_Data[1] );
             
	     Expected = E_OK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	
	   printf("*****This is Unit Test for steering car  -  invalid direction ***********\n");

    for(uint8_t i=0; i < 2; i++){


	     Actual= Testing_Steering_SteerCar( Direction_IN_Valid_Data[i], DUTY_Valid_Data[1] );
             
	     Expected = E_NOK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	
	 printf("*****This is Unit Test for steering car  -  invalid SPEED ***********\n");

    for(uint8_t i=0; i < 2; i++){


	     Actual= Testing_Steering_SteerCar( Direction_Valid_Data[1], DUTY_IN_Valid_Data[i] );
             
	     Expected = E_NOK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	

	printf("*****THE END OF Steering MODULE  ***********\n");

    return 0;
}

