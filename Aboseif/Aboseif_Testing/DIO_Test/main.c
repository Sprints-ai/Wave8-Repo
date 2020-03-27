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



             printf("*****This is Unit Test for DIO init- VALID DATA ***********\n");

    for(uinT8_t i=0; i < 4; i++){


	     Actual= Testing_DIO_init( &DIO_init_Valid_Data[i]);

	     Expected = E_OK;

	   if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

          printf("*****This is Unit Test for DIO init- INVALID DATA ***********\n");

      for(uint8 i=0; i < 3; i++){

           Actual = Testing_DIO_init(&DIO_init_IN_valid_Data[i]);

             Expected=E_NOK;

             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

      printf("*****This is Unit Test for DIO init- null ptr DATA ***********\n");

    Actual = Testing_DIO_init(null_ptr);

	  Expected = E_NOK;

             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }


	printf("*****This is Unit Test for DIO write - VALID DATA ***********\n");

       for(uint8 i=0; i < 4; i++){

           Actual = Testing_DIO_Write(DIO_Write_Valid_Data[i].GPIO,DIO_Write_Valid_Data[i].pins,DIO_Write_Valid_Data[i].dir);

		Expected=E_OK;

             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

	printf("*****This is Unit Test for DIO write - INVALID DATA ***********\n");

       for(uint8 i=0;i<3;i++){

		Actual= Testing_DIO_Write(DIO_Write_IN_valid_Data[i].GPIO, DIO_Write_IN_valid_Data[i].pins, DIO_Write_IN_valid_Data[i].dir);
             Expected=E_NOK;

             if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

printf("*****This is Unit Test for DIO read - null ptr DATA ***********\n");

	Actual = Testing_DIO_Read(GPIOA,BIT2,null_ptr);
     Expected=E_NOK;

     if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }

printf("*****This is Unit Test for DIO read - Valid DATA ***********\n");

      for(uint8 i=0; i<4; i++){

			 Actual = Testing_DIO_Read(DIO_Read_Valid_Data[i].GPIO,DIO_Read_Valid_Data[i].pins,&data);
             Expected=E_OK;

			if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

	printf("*****This is Unit Test for DIO read - INValid DATA ***********\n");

       for(uint8 i=0;i < 3;i++){

			 Actual = Testing_DIO_Read(DIO_Write_IN_valid_Data[i].GPIO, DIO_Write_IN_valid_Data[i].pins, &data);
             Expected=E_NOK;

			if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

printf("*****This is Unit Test for DIO TOGGLE - Valid DATA ***********\n");

      for(uint8 i=0; i<4; i++){

			 Actual = Testing_DIO_Toggle(DIO_Toggle_Valid_Data[i].GPIO,DIO_Toggle_Valid_Data[i].pins );
             Expected = E_OK;

			if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }

	printf("*****This is Unit Test for DIO TOGGLE - INValid DATA ***********\n");

       for(uint8 i=0;i < 3;i++){

			 Actual = Testing_DIO_Toggle(DIO_Toggle_IN_valid_Data[i].GPIO, DIO_Toggle_IN_valid_Data[i].pins);
             Expected = E_NOK;

			if(Expected == Actual){
                printf("TEST CASE# %d PASSED\n", i);
             }
             else{

                printf("TEST CASE# %d FAILED\n", i);
             }
    }
		printf("***** The End of DIO MODULE ***********\n");

    return 0;
}

