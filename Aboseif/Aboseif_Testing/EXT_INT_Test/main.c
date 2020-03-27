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


	
             printf("*****This is Unit Test for SET EDGE- VALID DATA ***********\n");

    for(uint8_t i=0; i < 3; i++){


	     Actual= Testing_EXT_INT_SetEdge( EXT_INT_Valid_Data[i]);
             
	     Expected = E_OK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
		
             printf("*****This is Unit Test for SET EDGE- INVALID DATA ***********\n");

    for(uint8_t i=0; i < 3; i++){

	     Actual= Testing_EXT_INT_SetEdge( EXT_INT_IN_Valid_Data[i]);
             
	     Expected = E_NOK;
             
	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	
	

      printf("*****This is Unit Test for EXT INT Enable  valid DATA ***********\n");

       for(uint8_t i=0; i < 3; i++){

    Actual = Testing_EXT_INT_Enable(EXT_INT_Valid_Data[i]);
             
		Expected=E_OK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

	printf("*****This is Unit Test for EXT INT Enable  invalid DATA ***********\n");

       for(uint8_t i=0; i < 2; i++){

    Actual = Testing_EXT_INT_Enable(EXT_INT_IN_Valid_Data[i]);
             
		Expected=E_NOK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

     printf("*****This is Unit Test for EXT INT Disable  valid DATA ***********\n");

       for(uint8_t i=0; i < 3; i++){

    Actual = Testing_EXT_INT_Disable(EXT_INT_Valid_Data[i]);
             
		Expected=E_OK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

	printf("*****This is Unit Test for EXT INT Disable  invalid DATA ***********\n");

       for(uint8_t i=0; i < 2; i++){

    Actual = Testing_EXT_INT_Disable(EXT_INT_IN_Valid_Data[i]);
             
		Expected=E_NOK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	
   printf("*****This is Unit Test for EXT INT istriggered  valid DATA ***********\n");

       for(uint8_t i=0; i < 3; i++){

    Actual = Testing_EXT_INT_IsTriggered(EXT_INT_Valid_Data[i], &data);
             
		Expected=E_OK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

	printf("*****This is Unit Test for EXT INT istriggered  invalid DATA ***********\n");

       for(uint8_t i=0; i < 2; i++){

    Actual = Testing_EXT_INT_IsTriggered(EXT_INT_IN_Valid_Data[i], &data);
             
		Expected=E_NOK;
             
             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

	printf("*****Null pointer for is triggered  ***********\n");

      for(uint8_t i=0; i<4; i++){
             
			 Actual = Testing_EXT_INT_IsTriggered(EXT_INT_Valid_Data[i], NULL);
             Expected = E_OK;
            
			if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
	
		printf("***** The End of EXT INT MODULE ***********\n");

    return 0;
}

