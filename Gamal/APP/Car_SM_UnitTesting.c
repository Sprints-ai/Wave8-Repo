/*
 ============================================================================
 Name        : Testing.c
 Author      : Muhammed Gamal
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "car_sm.h"


extern uint8_t a_u8_error_state_Us_init;
extern uint8_t a_u8_error_stateUs_trigger;
extern uint8_t a_u8_error_stateUs_GetDistance;
extern uint8_t a_u8_error_state_Steering_Init;
extern uint8_t a_u8_error_state_Steering_SteerCar;

extern uint8_t g_test_distance ;


int main(void)
{
    uint8_t state_error = E_OK ;

    /************************************************************************************
    * Target Function: car_sm_init
    * Test Case: the function us_init and Steering_Init  returns E_OK
    * data type) to "Icu_ReadTime"
    * Expected OUTPUT: E_OK
    ************************************************************************************/

    a_u8_error_state_Us_init = E_OK ;
    a_u8_error_state_Steering_Init = E_OK ;

    state_error = Car_SM_Init();

    printf("test case 1 :");

    if(state_error==E_OK)
        printf("passed \n");
    else
        printf("failed \n");



    /************************************************************************************
    * Target Function: car_sm_init
    * Test Case: the function us_init returns E_NOK and Steering_Init  returns E_OK
    * data type:
    * Expected OUTPUT: E_NOK
    ************************************************************************************/

    a_u8_error_state_Us_init = E_NOK ;
    a_u8_error_state_Steering_Init = E_OK ;

    state_error = Car_SM_Init();

    printf("test case 2 :");

    if(state_error==E_NOK)
        printf("passed \n");
    else
        printf("failed \n");




    /************************************************************************************
    * Target Function: car_sm_init
    * Test Case: the function us_init returns E_NOK and Steering_Init  returns E_OK
    * data type:
    * Expected OUTPUT: E_NOK
    ************************************************************************************/


    a_u8_error_state_Us_init = E_OK ;
    a_u8_error_state_Steering_Init = E_NOK ;

    state_error = Car_SM_Init();

    printf("test case 3 :");

    if(state_error==E_NOK)
        printf("passed \n");
    else
        printf("failed \n");

/***************************************************************************************/

    state_error = E_OK ;


    /************************************************************************************
    * Target Function: car_sm_Update
    * Test Case: the function Us_trigger and Us_GetDistance and Steering_SteerCar return E_OK
    * data type :
    * Expected OUTPUT: E_OK
    ************************************************************************************/


    a_u8_error_stateUs_trigger = E_OK ;
    a_u8_error_stateUs_GetDistance = E_OK ;
    a_u8_error_state_Steering_SteerCar = E_OK ;

    state_error= Car_SM_Update();

    printf("test case 4 :");

    if(state_error==E_OK)
        printf("passed \n");
    else
        printf("failed \n");



    /************************************************************************************
    * Target Function: car_sm_Update
    * Test Case: the function  Us_GetDistance and Steering_SteerCar return E_OK  , and Us_trigger returns E_NOK
    * data type :
    * Expected OUTPUT: E_NOK
    ************************************************************************************/


    a_u8_error_stateUs_trigger = E_NOK ;
    a_u8_error_stateUs_GetDistance = E_OK ;
    a_u8_error_state_Steering_SteerCar = E_OK ;

    state_error= Car_SM_Update();

    printf("test case 5 :");

    if(state_error==E_NOK)
        printf("passed \n");
    else
        printf("failed \n");



    /************************************************************************************
    * Target Function: car_sm_Update
    * Test Case: the function  Us_trigger and Steering_SteerCar return E_OK  , and  Us_GetDistance returns E_NOK
    * data type :
    * Expected OUTPUT: E_NOK
    ************************************************************************************/

    a_u8_error_stateUs_trigger = E_NOK ;
    a_u8_error_state_Steering_SteerCar = E_OK ;
    a_u8_error_stateUs_GetDistance = E_NOK ;

    state_error= Car_SM_Update();

    printf("test case 6 :");

    if(state_error==E_NOK)
        printf("passed \n");
    else
        printf("failed \n");



    /************************************************************************************
    * Target Function: car_sm_Update
    * Test Case: the function  Us_trigger and  Us_GetDistance return E_OK  , and Steering_SteerCar returns E_NOK
    * data type :
    * Expected OUTPUT: E_NOK
    ************************************************************************************/


    a_u8_error_stateUs_trigger = E_NOK ;
    a_u8_error_stateUs_GetDistance = E_OK ;
    a_u8_error_state_Steering_SteerCar = E_NOK ;

    state_error= Car_SM_Update();

    printf("test case 7 :");

    if(state_error==E_NOK)
        printf("passed \n");
    else
        printf("failed \n");



    /************************************************************************************
    * Target Function: car_sm_Update
    * Test Case: get distance from the us_read less than 20
    * data type :
    * Expected OUTPUT: E_OK
    ************************************************************************************/


    g_test_distance = 10 ;
    a_u8_error_stateUs_trigger = E_OK ;
    a_u8_error_stateUs_GetDistance = E_OK ;
    a_u8_error_state_Steering_SteerCar = E_OK ;
    state_error= Car_SM_Update();

    printf("test case 8 :");

    if(state_error==E_OK)
        printf("passed \n");
    else
        printf("failed \n");


    /************************************************************************************
    * Target Function: car_sm_Update
    * Test Case: get distance from the us_read between 20 and 40
    * data type :
    * Expected OUTPUT: E_OK
    ************************************************************************************/


    g_test_distance = 30 ;
    a_u8_error_stateUs_trigger = E_OK ;
    a_u8_error_stateUs_GetDistance = E_OK ;
    a_u8_error_state_Steering_SteerCar = E_OK ;

    state_error= Car_SM_Update();

    printf("test case 9 :");

    if(state_error==E_OK)
        printf("passed \n");
    else
        printf("failed \n");



    /************************************************************************************
    * Target Function: car_sm_Update
    * Test Case: get distance from the us_read more than 40
    * data type :
    * Expected OUTPUT: E_OK
    ************************************************************************************/


    g_test_distance = 50 ;
    a_u8_error_stateUs_trigger = E_OK ;
    a_u8_error_stateUs_GetDistance = E_OK ;
    a_u8_error_state_Steering_SteerCar = E_OK ;

    state_error= Car_SM_Update();

    printf("test case 10 :");

    if(state_error == E_OK)
        printf("passed \n");
    else
        printf("failed \n");

    return 0;
}

