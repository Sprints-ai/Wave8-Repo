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


	
             printf("*****This is Unit Test for MOTOR INIT  VALID DATA ***********\n");

    for(uint8_t i=0; i < 2; i++){


	     Actual= Testing_Motor_Init( MOTORS_Valid_Data[i]);
             
	     Expected = E_OK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
		
               printf("*****This is Unit Test for MOTOR INIT  INVALID DATA ***********\n");

    for(uint8_t i=0; i < 2; i++){


	     Actual= Testing_Motor_Init( MOTORS_IN_Valid_Data[i]);
             
	     Expected = E_NOK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	
	

      printf("*****This is Unit Test for Motor_Direction valid DATA ***********\n");

       for(uint8_t i=0; i < 3; i++){

    Actual = Testing_Motor_Direction(MOTORS_Valid_Data[0], Direction_Valid_Data[i] );
             
		Expected=E_OK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

	   printf("*****This is Unit Test for Motor_Direction INvalid DATA ***********\n");

       for(uint8_t i=0; i < 3; i++){

    Actual = Testing_Motor_Direction(MOTORS_Valid_Data[0], Direction_IN_Valid_Data[i] );
             
		Expected = E_NOK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
     printf("*****This is Unit Test for Motor_Direction INvalid MOTOR ***********\n");

       for(uint8_t i=0; i < 2; i++){

    Actual = Testing_Motor_Direction(MOTORS_IN_Valid_Data[i], Direction_Valid_Data[i] );
             
		Expected = E_NOK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

	    printf("*****This is Unit Test for Motor_Start valid DATA ***********\n");

       for(uint8_t i=0; i < 3; i++){

    Actual = Testing_Motor_Start(MOTORS_Valid_Data[0], Speed_Valid_Data[i] );
             
		Expected=E_OK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

	   printf("*****This is Unit Test for Motor_Start INvalid DATA ***********\n");

       for(uint8_t i=0; i < 2; i++){

    Actual = Testing_Motor_Start(MOTORS_Valid_Data[0], Speed_IN_Valid_Data[i] );
             
		Expected = E_NOK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
     printf("*****This is Unit Test for Motor_Start INvalid MOTOR ***********\n");

       for(uint8_t i=0; i < 2; i++){

    Actual = Testing_Motor_Start(MOTORS_IN_Valid_Data[i], Speed_IN_Valid_Data[i] );
             
		Expected = E_NOK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	
	            printf("*****This is Unit Test for MOTOR stop  VALID DATA ***********\n");

    for(uint8_t i=0; i < 2; i++){


	     Actual= Testing_Motor_Stop( MOTORS_Valid_Data[i]);
             
	     Expected = E_OK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
		
               printf("*****This is Unit Test for MOTOR stop  INVALID DATA ***********\n");

    for(uint8_t i=0; i < 2; i++){


	     Actual= Testing_Motor_Stop( MOTORS_IN_Valid_Data[i]);
             
	     Expected = E_NOK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	
	
      printf("*****This is Unit Test for Motor_ get status valid DATA ***********\n");

       for(uint8_t i=0; i < 2; i++){

    Actual = Testing_Motor_GetStatus(MOTORS_Valid_Data[i], &data );
             
		Expected=E_OK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

	   printf("*****This is Unit Test for Motor_get status INvalid DATA ***********\n");

       for(uint8_t i=0; i < 2; i++){

    Actual = Testing_Motor_GetStatus(MOTORS_IN_Valid_Data[i], &data );
             
		Expected = E_NOK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
     printf("*****This is Unit Test for Motor_get status NULL POINTER ***********\n");


    Actual = Testing_Motor_GetStatus(MOTORS_IN_Valid_Data[0], NULL );
             
		Expected = E_NOK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

	printf("*****THE END OF MOTOR MODULE  ***********\n");

    return 0;
}

