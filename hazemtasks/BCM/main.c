/*
*	File name: main.c
*	Author : Amin
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "BCM.h"

void RX_cb(void);
void TX_cb(void);

signed char Testing__BCM_init(Bcm_Cfg_ST *Bcm_cfg_ST);
signed char Testing__BCM_recieve(uint8_t *Buffer_ptr,BCM_recieve_cbk CBKFUN);
signed char Testing__BCM_Send(BCM_SEND_CBKFUNCOMP CBKFUN,uint8_t* BUFFER,uint16_t size);
signed char Testing__BCM_DINIT(void);

Bcm_Cfg_ST init_valid_test[3]={{USART_MODE,USART_NODE},{BCM_SPI_MODE,BCM_SPI_MASTER},{BCM_SPI_MODE,BCM_SPI_SLAVE}};
Bcm_Cfg_ST init_invalid_test[3]={{3,5},{-1,5},{BCM_SPI_MODE,5}};

Bcm_Cfg_ST *NULL_Pointer_Check = NULL;
uint8_t BCM_Buffer[10];
uint8_t *NULL_Ptr_check = NULL;

int main()
{
     signed char Check_Test=0;

    printf("****************************This is Unit Test for BCM MODULE***************************************\n*******************************************_API_NO#_4_**************************************************\n*****************************************TEST_CASE_NO#_1***********************************************\n-FUNCTION NAME: BCM_Deinit\n-EXPECTED OUTPUT:NO_INIT\n");
    Check_Test=Testing__BCM_DINIT();
      if(Check_Test==NO_INIT){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d!\n\n",Check_Test);
    }

  for(unsigned i=0;i<3;i++){
    printf("****************************This is Unit Test for BCM MODULE***************************************\n*******************************************_API_NO#_1_VALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: BCM_Init\n-INPUT: BCM_MODE:=%d---- SPI_MODE=%d\n-EXPECTED OUTPUT:OK\n",i+1,init_valid_test[i].BCM_Mode,init_valid_test[i].SPI_Mode);
    Check_Test=Testing__BCM_init(&init_valid_test[i]);
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d !\n\n",Check_Test);
    }

    }



    printf("****************************This is Unit Test for BCM MODULE***************************************\n*******************************************_API_NO#_1_(NULL_PTR)**************************************************\n*****************************************TEST_CASE_NO#_4***********************************************\n-FUNCTION NAME: BCM_Init\n-INPUT:NULL_PTR \n-EXPECTED OUTPUT:NULL_PTR\n");
    Check_Test=Testing__BCM_init(NULL_Pointer_Check);
      if(Check_Test==NULL_PTR){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d!\n\n",Check_Test);
    }


     for(unsigned i=0;i<3;i++){
    printf("****************************This is Unit Test for BCM MODULE***************************************\n*******************************************_API_NO#_1_INVALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: BCM_Init\n-INPUT: BCM_MODE:=%d---- SPI_MODE=%d\n-EXPECTED OUTPUT:OK\n",i+1,init_invalid_test[i].BCM_Mode,init_invalid_test[i].SPI_Mode);
    Check_Test=Testing__BCM_init(&init_invalid_test[i]);
      if(Check_Test==INVALID_PARAM){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d !\n\n",Check_Test);
    }
    }



    printf("****************************This is Unit Test for BCM MODULE***************************************\n*******************************************_API_NO#_2_VALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_1***********************************************\n-FUNCTION NAME: BCM_Receive\n-INPUT: Buffer\n-EXPECTED OUTPUT:OK\n");
    Check_Test=Testing__BCM_recieve(BCM_Buffer,RX_cb);
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d !\n\n",Check_Test);
    }

    printf("****************************This is Unit Test for BCM MODULE***************************************\n*******************************************_API_NO#_2_(NULL_PTR)**************************************************\n*****************************************TEST_CASE_NO#_2***********************************************\n-FUNCTION NAME: BCM_Receive\n-INPUT:NULL_PTR \n-EXPECTED OUTPUT:NULL_PTR\n");
    Check_Test=Testing__BCM_recieve(NULL_Pointer_Check,RX_cb);
      if(Check_Test==NULL_PTR){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d!\n\n",Check_Test);
    }



    printf("****************************This is Unit Test for BCM MODULE***************************************\n*******************************************_API_NO#_3_VALID_PARAMS**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n-FUNCTION NAME: BCM_Send\n-INPUT: Buffer\n-EXPECTED OUTPUT:OK\n");
    Check_Test=Testing__BCM_Send(TX_cb,BCM_Buffer,10);
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d !\n\n",Check_Test);
    }




    printf("****************************This is Unit Test for BCM MODULE***************************************\n*******************************************_API_NO#_3_(NULL_PTR)**************************************************\n*****************************************TEST_CASE_NO#_3***********************************************\n-FUNCTION NAME: BCM_Send\n-INPUT:NULL_PTR \n-EXPECTED OUTPUT:NULL_PTR\n");
    Check_Test=Testing__BCM_Send(TX_cb,NULL_Pointer_Check,10);
      if(Check_Test==NULL_PTR){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d!\n\n",Check_Test);
    }


    printf("****************************This is Unit Test for BCM MODULE***************************************\n*******************************************_API_NO#_4_**************************************************\n*****************************************TEST_CASE_NO#_1***********************************************\n-FUNCTION NAME: BCM_Deinit\n-EXPECTED OUTPUT:OK\n");
    Check_Test=Testing__BCM_DINIT();
      if(Check_Test==E_OK){
      printf("TEST CASE PASSED !\n\n");
    }
    else{
        printf("TEST CASE FAILED %d!\n\n",Check_Test);
    }

    return 0;
}

signed char Testing__BCM_init(Bcm_Cfg_ST *Bcm_cfg_ST){
    signed char Test_API_1=E_OK;
    Bcm_Cfg_ST *config;
    config=Bcm_cfg_ST;
    Test_API_1=BCM_init(config);
return Test_API_1;
}

signed char Testing__BCM_DINIT(void){
    signed char Test_API_1=E_OK;
    Test_API_1=BCM_DINIT();
return Test_API_1;
}

signed char Testing__BCM_recieve(uint8_t *Buffer_ptr,BCM_recieve_cbk CBKFUN){
    signed char Test_API_2 =E_OK;
    BCM_recieve_cbk Call_back;
    uint8_t *buffer;
    buffer=Buffer_ptr;
    Test_API_2=BCM_recieve(buffer,Call_back);
return Test_API_2;

}

signed char Testing__BCM_Send(BCM_SEND_CBKFUNCOMP CBKFUN,uint8_t* BUFFER,uint16_t size){
    signed char Test_API_3=E_OK;
    BCM_SEND_CBKFUNCOMP Call_bck;
    uint8_t *buffer;
    uint16_t B_size;
    buffer=BUFFER;
    Call_bck = CBKFUN;
    Test_API_3=BCM_Send(Call_bck,buffer,B_size);
return Test_API_3;
}

void TX_cb(void)
{}

void RX_cb(void)
{}
