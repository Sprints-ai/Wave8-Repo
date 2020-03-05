
#include"../SL/BCM.h"

#define INVALID_PARAMETER 9


void test_function(enum_BcmStatus x){}





void Test_BCM_init(void)
{

    sint16_t state_error = E_OK ;

    printf("Testing BCM Init Function\n");
    printf("_____________\n");

    /************************************************************************************
    * Target Function: BCM Init Function
    * Test Case: test null pointer.
    * Expected OUTPUT: TNULL_PTR + BCM_ERROR
    ************************************************************************************/

    BCM_cfg_s * a_ptr_BCM1;
    a_ptr_BCM1 = NULL ;

    state_error = BCM_Init(a_ptr_BCM1) ;

    printf("Test case 1 : ");

    if(state_error == NULL_PTR + BCM_ERROR)
        printf("passed \n");
    else
        printf("failed \n");



        BCM_cfg_s a_BCM1;

    /************************************************************************************
    * Target Function: BCM Init Function
    * Test Case: valid parameters .
    * Expected OUTPUT: E_OK + BCM_ERROR
    ************************************************************************************/


    a_BCM1.BCM_CH_ID = 1 ;
    a_BCM1.Mode = BCM_Rx_Mode ;
    a_BCM1.Protocol = SPI_Protocol ;

    state_error = BCM_Init(&a_BCM1) ;

    printf("Test case 2 : ");

    if(state_error == BCM_ERROR + E_OK)
        printf("passed \n");
    else
        printf("failed \n");



    /************************************************************************************
    * Target Function: BCM Init Function
    * Test Case: re-init .
    * Expected OUTPUT: BCM_ERROR + ALREADY_INIT
    ************************************************************************************/


    a_BCM1.BCM_CH_ID = 3 ;
    a_BCM1.Mode = BCM_Rx_Mode ;
    a_BCM1.Protocol = SPI_Protocol ;

    state_error = BCM_Init(&a_BCM1) ;

    printf("Test case 3 : ");

    if(state_error == BCM_ERROR + ALREADY_INIT)
        printf("passed \n");
    else
        printf("failed \n");

    BCM_DeInit(&a_BCM1);
    /************************************************************************************
    * Target Function: BCM Init Function
    * Test Case: INVALID parameters(invalid mode) .
    * Expected OUTPUT: TNULL_PTR + BCM_ERROR
    ************************************************************************************/

    a_BCM1.BCM_CH_ID = 4 ;
    a_BCM1.Mode = INVALID_PARAMETER ;
    a_BCM1.Protocol = SPI_Protocol;

    state_error = BCM_Init(&a_BCM1) ;

    printf("Test case 4 : ");

    if(state_error == INVALID_IN + BCM_ERROR)
        printf("passed \n");
    else
        printf("failed \n");


    /************************************************************************************
    * Target Function: BCM Init Function
    * Test Case: INVALID parameters(invalid protocol) .
    * Expected OUTPUT: TNULL_PTR + BCM_ERROR
    ************************************************************************************/


    a_BCM1.BCM_CH_ID = 5 ;
    a_BCM1.Mode = BCM_Rx_Mode ;
    a_BCM1.Protocol = INVALID_PARAMETER ;

    state_error = BCM_Init(&a_BCM1) ;

    printf("Test case 5 : ");

    if(state_error == INVALID_IN + BCM_ERROR)
        printf("passed \n");
    else
        printf("failed \n");


}



void Test_BCM_send(void){

 sint16_t state_error = E_OK ;

    printf("Testing BCM_send Function\n");
    printf("_____________\n");


    BCM_cfg_s BCM1 ;
    BCM1.BCM_CH_ID = 1;
	BCM1.Mode = BCM_Tx_Mode;
	BCM1.Protocol = SPI_Protocol;
	BCM_Init(&BCM1);

	uint8_t * Buffer = NULL ;
	uint8_t buffer_value = 8 ;
    uint8_t index ;
    Notify_FunPtr ptr_func = NULL ;

    /************************************************************************************
    * Target Function: BCM_send Function
    * Test Case: test null pointer (Buffer).
    * Expected OUTPUT: NULL_PTR + BCM_ERROR
    ************************************************************************************/
    index = 5 ;
    ptr_func = test_function ;
    Buffer = &buffer_value ;

    state_error = BCM_Send(NULL ,index ,&BCM1 , ptr_func) ;

    printf("Test case 1 : ");

    if(state_error == NULL_PTR + BCM_ERROR)
        printf("passed \n");
    else
        printf("failed \n");


    /************************************************************************************
    * Target Function: BCM_send Function
    * Test Case: test null pointer (structure).
    * Expected OUTPUT: NULL_PTR + BCM_ERROR
    ************************************************************************************/


    state_error = BCM_Send(Buffer ,index ,NULL , ptr_func) ;

    printf("Test case 2 : ");

    if(state_error == NULL_PTR + BCM_ERROR)
        printf("passed \n");
    else
        printf("failed \n");



    /************************************************************************************
    * Target Function: BCM_send Function
    * Test Case: test null pointer (pointer to function).
    * Expected OUTPUT: NULL_PTR + BCM_ERROR
    ************************************************************************************/


    state_error = BCM_Send(Buffer ,index ,&BCM1 , NULL) ;

    printf("Test case 3 : ");

    if(state_error == NULL_PTR + BCM_ERROR)
        printf("passed \n");
    else
        printf("failed \n");




    /************************************************************************************
    * Target Function: BCM_send Function
    * Test Case: send invalid parameters (mode).
    * Expected OUTPUT: INVALID_IN + BCM_ERROR
    ************************************************************************************/
    BCM1.BCM_CH_ID = 1;
	BCM1.Mode = INVALID_PARAMETER;
	BCM1.Protocol = SPI_Protocol;

    state_error = BCM_Send(Buffer ,index ,&BCM1 , ptr_func) ;

    printf("Test case 4 : ");

    if(state_error == INVALID_IN + BCM_ERROR)
        printf("passed \n");
    else
        printf("failed \n");

    /************************************************************************************
    * Target Function: BCM_send Function
    * Test Case: send invalid parameters (protocol).
    * Expected OUTPUT: INVALID_IN + BCM_ERROR
    ************************************************************************************/
    BCM1.BCM_CH_ID = 1;
	BCM1.Mode = BCM_Tx_Mode;
	BCM1.Protocol = INVALID_PARAMETER;

    state_error = BCM_Send(Buffer ,index ,&BCM1 , ptr_func) ;

    printf("Test case 5 : ");

    if(state_error == INVALID_IN + BCM_ERROR)
        printf("passed \n");
    else
        printf("failed \n");


    BCM1.BCM_CH_ID = 1;
	BCM1.Mode = BCM_Tx_Mode;
	BCM1.Protocol = SPI_Protocol;

    BCM_DeInit(&BCM1);


    /************************************************************************************
    * Target Function: BCM_send Function
    * Test Case: use bcm_send without init.
    * Expected OUTPUT: INVALID_IN + BCM_ERROR
    ************************************************************************************/
    BCM1.BCM_CH_ID = 1;
	BCM1.Mode = BCM_Tx_Mode;
	BCM1.Protocol = SPI_Protocol;

    state_error = BCM_Send(Buffer ,index ,&BCM1 , ptr_func) ;

    printf("Test case 6 : ");

    if(state_error == NOT_INIT + BCM_ERROR)
        printf("passed \n");
    else
        printf("failed \n");



    /************************************************************************************
    * Target Function: BCM_send Function
    * Test Case: call send from different mode.
    * Expected OUTPUT: FUNC_IN_DIF_CFG + BCM_ERROR
    ************************************************************************************/
    BCM1.BCM_CH_ID = 1;
	BCM1.Mode = BCM_Rx_Mode;
	BCM1.Protocol = SPI_Protocol;

	BCM_Init(&BCM1) ;
    state_error = BCM_Send(Buffer ,index ,&BCM1 , ptr_func) ;

    printf("Test case 7 : ");

    if(state_error == FUNC_IN_DIF_CFG + BCM_ERROR)
        printf("passed \n");
    else
        printf("failed \n");






}






