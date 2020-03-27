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


	
            printf("*****This is Unit Test for ICU INIT  ***********\n\n");

	    printf("*****This is Unit Test for ICU READ  -  valid CHANNEL, valid edge  ***********\n");

    for(uint8_t i=0; i < 3; i++){


	     Actual= Testing_Icu_ReadTime( CHANNEL_Valid_Data[i], EDGE_Valid_Data[i], &data );
             
	     Expected = E_OK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	
	    printf("*****This is Unit Test for ICU READ  -  invalid CHANNEL, valid edge  ***********\n");

    for(uint8_t i=0; i < 3; i++){


	     Actual= Testing_Icu_ReadTime( CHANNEL_IN_Valid_Data[i], EDGE_Valid_Data[i], &data );
             
	     Expected = E_NOK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	
	    printf("*****This is Unit Test for ICU READ  -  valid CHANNEL, INvalid edge  ***********\n");

    for(uint8_t i=0; i < 3; i++){

	     Actual= Testing_Icu_ReadTime( CHANNEL_Valid_Data[i], EDGE_IN_Valid_Data[i], &data );
             
	     Expected = E_NOK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	
	   printf("*****This is Unit Test for ICU READ  -  NULL POINTER  ***********\n");

    for(uint8_t i=0; i < 3; i++){

	     Actual= Testing_Icu_ReadTime( CHANNEL_Valid_Data[i], EDGE_IN_Valid_Data[i], NULL );
             
	     Expected = E_NOK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	

	printf("*****THE END OF ICU MODULE  ***********\n");

    return 0;
}

