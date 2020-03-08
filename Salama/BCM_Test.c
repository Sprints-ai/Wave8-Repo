/*
 * SEND.c
 *
 *
 * Created: 2020-03-01 9:49:13 PM
 * Author : EbrahimOseif
 */

#include "bcm.h"
#include "ERROR.h"

/**
*Small Description of Test
All test are commented and it's double spaces down the comments
descriping it so you can easily access any test case by removing it's
code comment, all MOK files are Attached

*/


uint8_t arr[30];

void test_mok()
{

}
/*Test Scenarios*/
void test_BCMInit(void)
{
    /*
    happy Scenario : everything sent as expected
    Expected output : NO_ERROR
    Test State : test Passed
    */

    /*
    printf("%d",BCM_Init(&BCM_Cfg));
    */

    /*first test case sending null pointer to it
    Expected output : ERROR_NULL_POINTER
    Test State : TEST PASSED, NULL POINTER DETECTED
    */

    /*
    printf("%d",BCM_Init(0));
    */

    /*second test case sending wrong protocol to it
    expected output : ERROR_OUTPUT
    Test State : Test failed, no error detected
    Solution : Case Handled
    */


    /*
    BCM_Cfg.u8_Protocol = 3;
    printf("%d",BCM_Init(&BCM_Cfg));
    */

    /*third case : multiple uart_bcm_config
    expected output : ERROR_OUTPUT
    Test State : TEST PASSED, ERROR_OUTPUT
    */


   /* BCM_Cfg.u8_Protocol = UART_PROTOCOL;
    BCM_Cfg.Recieve_Cbk = test_mok;
    BCM_Cfg.Transmit_Cbk = test_mok;
    printf("%d\n",BCM_Init(&BCM_Cfg));
    printf("%d",BCM_Init(&BCM_Cfg));*/

    /*4th case : multiple SPI_bcm_config
    expected output : ERROR_OUTPUT
    Test State : TEST PASSED, ERROR_OUTPUT
    */

    /*
    BCM_Cfg.u8_Protocol = SPI_PROTOCOL;
    BCM_Cfg.Recieve_Cbk = test_mok;
    BCM_Cfg.Transmit_Cbk = test_mok;
    printf("%d\n",BCM_Init(&BCM_Cfg));
    printf("%d",BCM_Init(&BCM_Cfg));
    */

    /*5th case : sending null pointers to user's notification
    expected output : ERROR_OUTPUT
    Test State : PASSED WITH UART , FAILED with SPI
    Solution : Case Handled
    */

    /*
    BCM_Cfg.u8_Protocol = UART_PROTOCOL;
    printf("%d\n",BCM_Init(&BCM_Cfg));
    */
}

void test_BCMSend(){
    /*
    happy Scenario : sending everything as expected
    expected output : no error
    Test state : passed
    */

    /*
    BCM_Cfg.u8_Protocol = UART_PROTOCOL;
    BCM_Cfg.Recieve_Cbk = test_mok;
    BCM_Cfg.Transmit_Cbk = test_mok;
    BCM_Init(&BCM_Cfg);
    printf("%d",BCM_Send(arr,10));
    */

    /*
    first test case : sending null pointer instead of array address
    expected output : ERROR_OUTPUT
    Test State : Passed
    */

    /*
    printf("%d",BCM_Send(0,15));
    */

    /*
    second test case : using bcm_send before init
    expected output : ERROR_OUTPUT
    Test State : Failed
    Solution : case Handled
    */

    /*
    printf("%d",BCM_Send(arr,10));
    */

    /*
    third test case : using BCM_Send Twice
    expected output : ERROR_LOCKED_Buffer
    Test state : failed
    Solution : Case Handled
    */


   /*
    BCM_Cfg.u8_Protocol = UART_PROTOCOL;
    BCM_Cfg.Recieve_Cbk = test_mok;
    BCM_Cfg.Transmit_Cbk = test_mok;
    BCM_Init(&BCM_Cfg);
    printf("%d",BCM_Send(arr,10));
    printf("%d",BCM_Send(arr,10));
    */

    /*
    4th test case : sending large data number which bcm can't handle
    expected output : Error_output
    Test State : failed
    Solution : Case Handled
    */

    /*
    BCM_Cfg.u8_Protocol = UART_PROTOCOL;
    BCM_Cfg.Recieve_Cbk = test_mok;
    BCM_Cfg.Transmit_Cbk = test_mok;
    BCM_Init(&BCM_Cfg);
    printf("%d",BCM_Send(arr,10000));
    */
}

void test_BCMSetupReceive(void)
{
    /*
    happy scenario everything done as expected
    expected output : No_Error
    Test State : passed
    */


    /*
    BCM_Cfg.u8_Protocol = UART_PROTOCOL;
    BCM_Cfg.Recieve_Cbk = test_mok;
    BCM_Cfg.Transmit_Cbk = test_mok;
    BCM_Init(&BCM_Cfg);
    printf("%d",BCM_SetupReceive(arr,16));
    */

    /*
    first test case : No init before it
    Expected output : ERRPR_NO_INIT
    Test State : failed
    Solution : case Handled
    */


    /*
    printf("%d",BCM_SetupReceive(arr,16));
    */

    /*
    second test case : Null pointer
    Expected Output : ERROR_NULL_POINTER
    Test state : test Passed
    */

    /*
    printf("%d",BCM_SetupReceive(0,16));
    */
}

test_BCMDeInit()
{
        /*
        best Scenario : everything happens as expected
        Expected Output  : no error
        Test State : PASSED
        */

        /*
        BCM_Cfg.u8_Protocol = UART_PROTOCOL;
        BCM_Cfg.Recieve_Cbk = test_mok;
        BCM_Cfg.Transmit_Cbk = test_mok;
        BCM_Init(&BCM_Cfg);
        BCM_Send(arr,10);
        printf("%d",BCM_DeInit());
        */

        /*
        Test Case 1 : No BCM_Send before it
        Expected OUTPUT : ERROR_OUTPUT
        Test State : Paseed
        */


        /*
        BCM_Cfg.u8_Protocol = UART_PROTOCOL;
        BCM_Cfg.Recieve_Cbk = test_mok;
        BCM_Cfg.Transmit_Cbk = test_mok;
        BCM_Init(&BCM_Cfg);
        printf("%d",BCM_DeInit());
        */

        /*
        Test Case 1 : No BCM_Send before it
        Expected OUTPUT : ERROR_OUTPUT
        Test State : Passed
        */


        /*
        BCM_Cfg.u8_Protocol = UART_PROTOCOL;
        BCM_Send(arr,10);
        printf("%d",BCM_DeInit());
        */
}

int main(void)
{
    test_BCMInit();
    test_BCMSend();
    test_BCMSetupReceive();
    test_BCMDeInit();
}

