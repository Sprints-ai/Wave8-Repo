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


	
             printf("*****This is Unit Test for PWM INIT  LIKE DIO INIT  ***********\n\n");

	    printf("*****This is Unit Test for PWM START  VALID CHANNEL , DUTY, FREQUENCY ***********\n");

    for(uint8_t i=0; i < 2; i++){


	     Actual= Testing_Pwm_Start( PWM_CHANNEL_Valid_Data[i], DUTY_Valid_Data[i], FREQ_Valid_Data[i] );
             
	     Expected = E_OK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	
		    printf("*****This is Unit Test for PWM START  INVALID CHANNEL , VALID DUTY, FREQUENCY ***********\n");

    for(uint8_t i=0; i < 2; i++){

	     Actual= Testing_Pwm_Start( PWM_CHANNEL_IN_Valid_Data[i], DUTY_Valid_Data[i], FREQ_Valid_Data[i] );
             
	     Expected = E_NOK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	
		    printf("*****This is Unit Test for PWM START  VALID CHANNEL , INVALID DUTY, FREQUENCY ***********\n");

    for(uint8_t i=0; i < 2; i++){

	     Actual= Testing_Pwm_Start( PWM_CHANNEL_Valid_Data[i], DUTY_IN_Valid_Data[i], FREQ_Valid_Data[i] );
             
	     Expected = E_NOK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
				    printf("*****This is Unit Test for PWM START  VALID CHANNEL , DUTY, INVALID FREQUENCY ***********\n");

    for(uint8_t i=0; i < 2; i++){

	     Actual= Testing_Pwm_Start( PWM_CHANNEL_Valid_Data[i], DUTY_Valid_Data[i], FREQ_IN_Valid_Data[i] );
             
	     Expected = E_NOK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	
	    printf("*****This is Unit Test for PWM UPDATE  LIKE START ***********\n");

		
        printf("*****This is Unit Test for PWM STOP  VALID DATA ***********\n");

    for(uint8_t i=0; i < 2; i++){

	     Actual= Testing_Pwm_Stop( PWM_CHANNEL_Valid_Data[i]);
             
	     Expected = E_OK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	  printf("*****This is Unit Test for PWM STOP  INVALID DATA ***********\n");

    for(uint8_t i=0; i < 2; i++){

	     Actual= Testing_Pwm_Stop( PWM_CHANNEL_IN_Valid_Data[i]);
             
	     Expected = E_NOK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	

	printf("*****THE END OF PWM MODULE  ***********\n");

    return 0;
}

