/*
*	File name: main.c
*	Author : Ema
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "DIO.h"


signed char Testing__DIO_init(DIO_Cfg_s *DIO_info);
signed char Testing__DIO_Write(uint8_t GPIO, uint8_t pins, sint8_t value);
signed char Testing__DIO_Read(uint8_t GPIO,uint8_t pins, uint8_t *data);
signed char Testing__DIO_Toggle(uint8_t GPIO, uint8_t pins);

DIO_Cfg_s init_valid_test[3]={{GPIOA,PIN0,OUTPUT},{GPIOB,PIN5,INPUT}};
DIO_Cfg_s init_invalid_test[3]={{GPIOB,PIN1,3},{6,PIN2,INPUT},{8,PIN1,4}};

DIO_Cfg_s *NULL_Pointer_Check = NULL;

uint8_t *NULL_Ptr_check = NULL;
uint8_t data;

int main()
{
    signed char Check_Test=0;

    printf("/***********************************DIO_NOINIT***********************************/\n");
    Check_Test = Testing__DIO_Write(GPIOC, PIN0, 1);
    printf("DIO_Write Status for NO_INIT PORT ---> %d \n",Check_Test);

    Check_Test = Testing__DIO_Read(GPIOC, PIN0, &data);
    printf("DIO_Read Status for NO_INIT PORT ---> %d \n",Check_Test);

    Check_Test = Testing__DIO_Toggle(GPIOC, PIN0);
    printf("DIO_Toggle Status for NO_INIT PORT ---> %d \n",Check_Test);


    printf("/***********************************DIO_INIT***********************************/\n");
    for(int i=0; i<3; i++)
    {
       Check_Test = Testing__DIO_init(&init_valid_test[i]);
       printf("DIO_INIT Status for Valid_PARAM ---> %d \n",Check_Test);
    }

    for(int i=0; i<3; i++)
    {
       Check_Test = Testing__DIO_init(&init_invalid_test[i]);
       printf("DIO_INIT Status for INValid_PARAM ---> %d \n",Check_Test);
    }

    Check_Test = Testing__DIO_init(NULL_Pointer_Check);
    printf("DIO_INIT Status for NULL_PTR ---> %d \n",Check_Test);


    printf("/***********************************DIO_Write***********************************/\n");
    Check_Test = Testing__DIO_Write(GPIOA, PIN0, 0);
    printf("DIO_Write Status for Valid_PARAM ---> %d \n",Check_Test);

    Check_Test = Testing__DIO_Write(GPIOA, PIN0, -1);
    printf("DIO_Write Status for InValid_value ---> %d \n",Check_Test);

    Check_Test = Testing__DIO_Write(7, PIN0, 1);
    printf("DIO_Write Status for InValid_port ---> %d \n",Check_Test);

    Check_Test = Testing__DIO_Write(8, PIN0, -2);
    printf("DIO_Write Status for InValid_port & InValid_value ---> %d \n",Check_Test);


    printf("/***********************************DIO_Read***********************************/\n");
    Check_Test = Testing__DIO_Read(GPIOA, PIN0, &data);
    printf("DIO_Read Status for Valid_PARAM ---> %d \n",Check_Test);

    Check_Test = Testing__DIO_Read(7, PIN0, &data);
    printf("DIO_Read Status for InValid_port ---> %d \n",Check_Test);

    Check_Test = Testing__DIO_Read(GPIOA, PIN0,NULL_Pointer_Check);
    printf("DIO_Read Status for NULL_PTR ---> %d \n",Check_Test);


    printf("/***********************************DIO_Toggle***********************************/\n");
    Check_Test = Testing__DIO_Toggle(GPIOA, PIN0);
    printf("DIO_Toggle Status for Valid_PARAM ---> %d \n",Check_Test);

    Check_Test = Testing__DIO_Toggle(7, PIN0);
    printf("DIO_Toggle Status for InValid_port ---> %d \n",Check_Test);



    return 0;
}

signed char Testing__DIO_init(DIO_Cfg_s *DIO_info){
    signed char Test_API_1=E_OK;
    DIO_Cfg_s *config;
    config=DIO_info;
    Test_API_1=DIO_init(config);
return Test_API_1;
}

signed char Testing__DIO_Write(uint8_t GPIO, uint8_t pins, sint8_t value){
    signed char Test_API_2=E_OK;
    Test_API_2=DIO_Write(GPIO,pins,value);
return Test_API_2;
}

signed char Testing__DIO_Read(uint8_t GPIO,uint8_t pins, uint8_t *data){
    signed char Test_API_3=E_OK;
    uint8_t *read_data;
    read_data = data;
    Test_API_3=DIO_Read(GPIO,pins,read_data);
return Test_API_3;
}

signed char Testing__DIO_Toggle(uint8_t GPIO, uint8_t pins){
    signed char Test_API_4=E_OK;
    Test_API_4=DIO_Toggle(GPIO,pins);
return Test_API_4;
}
