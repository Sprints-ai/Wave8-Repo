/*
*	File name: main.c
*	Author : Ema
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "PWM.h"


signed char Testing__Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);
signed char Testing__Pwm_Start(uint8_t Channel,uint8_t Duty,uint32_t Frequncy);
signed char Testing__Pwm_Update(uint8_t Channel,uint8_t Duty,uint32_t Frequncy);
signed char Testing__Pwm_Stop(uint8_t Channel);

Pwm_Cfg_s init_valid_test={PWM_CH1A,256};
Pwm_Cfg_s init_invalid_test={7,256};

Pwm_Cfg_s *NULL_Pointer_Check = NULL;

uint8_t *NULL_Ptr_check = NULL;

int main()
{
    signed char Check_Test=0;

    printf("/***********************************PWM_NOINIT/START***********************************/\n");
    Check_Test = Testing__Pwm_Start(TIMER_CH0,60,40);
    printf("Pwm_Start Status for NO_INIT  ---> %d \n",Check_Test);

    Check_Test = Testing__Pwm_Update(TIMER_CH0,60,40);
    printf("Pwm_Update Status for NO_INIT  ---> %d \n",Check_Test);

    Check_Test = Testing__Pwm_Stop(TIMER_CH0);
    printf("Pwm_Stop Status for NO_INIT  ---> %d \n",Check_Test);


    printf("/***********************************PWM_INIT***********************************/\n");
    Check_Test = Testing__Pwm_Init(&init_invalid_test);
    printf("PWM_INIT Status for INValid_PARAM ---> %d \n",Check_Test);

    Check_Test = Testing__Pwm_Init(NULL_Pointer_Check);
    printf("PWM_INIT Status for NULL_PTR ---> %d \n",Check_Test);

    Check_Test = Testing__Pwm_Init(&init_valid_test);
    printf("PWM_INIT Status for Valid_PARAM ---> %d \n",Check_Test);


    printf("/***********************************PWM_START***********************************/\n");
    Check_Test = Testing__Pwm_Start(PWM_CH1A,60,40);
    printf("PWM_Start Status for Valid_PARAM ---> %d \n",Check_Test);

    Check_Test = Testing__Pwm_Start(7,60,40);
    printf("PWM_Start Status for INValid_PARAM ---> %d \n",Check_Test);


    printf("/***********************************PWM_UPDATE***********************************/\n");
    Check_Test = Testing__Pwm_Update(PWM_CH1A,60,40);
    printf("PWM_Update Status for Valid_PARAM ---> %d \n",Check_Test);

    Check_Test = Testing__Pwm_Update(7,60,40);
    printf("PWM_Update Status for INValid_PARAM ---> %d \n",Check_Test);


    printf("/***********************************PWM_STOP***********************************/\n");
    Check_Test = Testing__Pwm_Stop(7);
    printf("PWM_Stop Status for INValid_PARAM ---> %d \n",Check_Test);

    Check_Test = Testing__Pwm_Stop(PWM_CH1A);
    printf("PWM_Stop Status for Valid_PARAM ---> %d \n",Check_Test);


    return 0;
}

signed char Testing__Pwm_Init(Pwm_Cfg_s *Pwm_Cfg){
    signed char Test_API_1=E_OK;
    Pwm_Cfg_s *config;
    config=Pwm_Cfg;
    Test_API_1=Pwm_Init(config);
return Test_API_1;
}

signed char Testing__Pwm_Start(uint8_t Channel,uint8_t Duty,uint32_t Frequncy){
    signed char Test_API_2=E_OK;
    Test_API_2=Pwm_Start(Channel,Duty,Frequncy);
return Test_API_2;
}

signed char Testing__Pwm_Update(uint8_t Channel,uint8_t Duty,uint32_t Frequncy){
    signed char Test_API_3=E_OK;
    Test_API_3=Pwm_Update(Channel,Duty,Frequncy);
return Test_API_3;
}

signed char Testing__Pwm_Stop(uint8_t Channel){
    signed char Test_API_4=E_OK;
    Test_API_4=Pwm_Stop(Channel);
return Test_API_4;
}
