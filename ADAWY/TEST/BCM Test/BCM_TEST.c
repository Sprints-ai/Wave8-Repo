/*
 * BCM_TEST.c
 *
 *  Created on: Mar 5, 2020
 *      Author: Khaled
 */

#include "SERVICE/std_types.h"
#include <stdio.h>
#include "SERVICE/BCM/BCM.h"

#define RESULT_INITIAL_VALUE 5
#define ZERO 0;


uint8_t gu8_UartTransmitNotification;
uint8_t gu8_UartReceiveData;

void BCM_Init_Test (void);

void BCM_Send_Test (void);
void BCM_SetupRxBuffer_Test (void);
void BCM_RxUnlock_Test (void);
void BCM_GetTxBuffer_Test (void);
void BCM_GetRxBufferLockState_Test (void);



int main (void)
{
	uint8_t au8_Test_Func_Number = ZERO;
	//line to correct error in IDE related to printf and scanf functions
	setvbuf(stdout,NULL,_IONBF,0);

	printf("choose 1 for BCM_Init \n");
	printf("choose 2 for BCM_Send \n");
	printf("choose 3 for BCM_SetupRxBuffer \n");
	printf("choose 4 for BCM_RxUnlock \n");
	printf("choose 5 for BCM_GetTxBuffer \n");

	printf("The number of the desired function to test is ");
	scanf("%d",&au8_Test_Func_Number);

	switch (au8_Test_Func_Number)
	{
	case 1:
		BCM_Init_Test();
		break;

	case 2:
        BCM_Send_Test();
		break;

	case 3:
        BCM_SetupRxBuffer_Test();
		break;

	case 4:
        BCM_RxUnlock_Test();
		break;

    case 5:
        BCM_GetTxBuffer_Test();
        break;

	default:
		printf("Invalid function number");
		break;
	}



	return 0;
}

/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
void Test_Consumer (void)
{
	printf("\n Hello \n");
}


void BCM_Init_Test (void)
{
	uint8_t au8_TestNumber = ZERO;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	uint8_t au8_repeat = ZERO;
	strBCMCfg_t BcmCfg;

	while (TRUE)
	{

		printf("Please enter test number: ");

		scanf("%d",&(au8_TestNumber));

		switch (au8_TestNumber)
		{
		case 1:
		    /*Happy scenario*/
            BcmCfg.Direction = READING;
            BcmCfg.Protocol = SPI_BCM;
			au8_Result = BCM_Init(&BcmCfg);
			printf("The expected output is 0  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
        case 2:
            BcmCfg.Direction = READING;
            BcmCfg.Protocol = UART_BCM;
            au8_Result = BCM_Init(&BcmCfg);
			printf("The expected output is 0  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
         case 3:
            BcmCfg.Direction = READING;
            BcmCfg.Protocol = 3;
            au8_Result = BCM_Init(&BcmCfg);
			printf("The expected output is 1  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
        case 4:
            BcmCfg.Direction = SENDING;
            BcmCfg.Protocol = UART_BCM;
            au8_Result = BCM_Init(&BcmCfg);
			printf("The expected output is 0  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
         case 5:
            BcmCfg.Direction = SENDING;
            BcmCfg.Protocol = SPI_BCM;
            au8_Result = BCM_Init(&BcmCfg);
			printf("The expected output is 0  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
        case 6:
            BcmCfg.Direction = 3;
            BcmCfg.Protocol = SPI_BCM;
            au8_Result = BCM_Init(&BcmCfg);
			printf("The expected output is 1  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
        case 7:
            au8_Result = BCM_Init(NULL);
			printf("The expected output is 1  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;

		default:
			printf("invalid test number");
			break;
		}

		printf("\nTo exit BCM test press E or any char to continue ");
				scanf("%c", &au8_repeat);

				printf(" ");
				scanf("%c", &au8_repeat);

				if ('E'  == au8_repeat)
				{

					break;
				}

				printf(" ");
				scanf("%c", &au8_repeat);
			}

}

void BCM_Send_Test (void){
    uint8_t au8_TestNumber = ZERO;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	uint8_t au8_repeat = ZERO;
	strTxBuffer_t BcmTxBuffer;
    uint8_t Txbuffer[10]={0};
	while (TRUE)
	{

		printf("Please enter test number: ");

		scanf("%d",&(au8_TestNumber));

		switch (au8_TestNumber)
		{
		case 1:
		    /*Happy scenario*/
            BcmTxBuffer.ptrTxBuffer = Txbuffer;
            BcmTxBuffer.Lock = TX_BUFFER_READY_TO_SEND;
            BcmTxBuffer.Size = 8;
			au8_Result = BCM_Send(&BcmTxBuffer);
			printf("The expected output is 0  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;

        case 2:
            au8_Result = BCM_Send(NULL);
			printf("The expected output is 1  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
         case 3:
            BcmTxBuffer.ptrTxBuffer = NULL;
            BcmTxBuffer.Lock = TX_BUFFER_READY_TO_SEND;
            BcmTxBuffer.Size = 8;
            au8_Result = BCM_Send(&BcmTxBuffer);
			printf("The expected output is 1  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
        case 4:
            BcmTxBuffer.ptrTxBuffer = Txbuffer;
            BcmTxBuffer.Lock = 5;
            BcmTxBuffer.Size = 8;
			au8_Result = BCM_Send(&BcmTxBuffer);
			printf("The expected output is 1 and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
        case 5:
		    BcmTxBuffer.ptrTxBuffer = Txbuffer;
            BcmTxBuffer.Lock = TX_BUFFER_READY_TO_SEND;
            BcmTxBuffer.Size = 0;
			au8_Result = BCM_Send(&BcmTxBuffer);
			printf("The expected output is 0  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;

		default:
			printf("invalid test number");
			break;
		}

		printf("\nTo exit BCM test press E or any char to continue ");
				scanf("%c", &au8_repeat);

				printf(" ");
				scanf("%c", &au8_repeat);

				if ('E'  == au8_repeat)
				{

					break;
				}

				printf(" ");
				scanf("%c", &au8_repeat);
			}
}


void NotificationMockPtrFunction(uint8_t x){
    /*do nothing*/
}

void BCM_SetupRxBuffer_Test (void){
     uint8_t au8_TestNumber = ZERO;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	uint8_t au8_repeat = ZERO;
	strTxBuffer_t BcmTxBuffer;
    uint8_t Rxbuffer[10]={0};
   void (*Notification)(uint8_t);

	while (TRUE)
	{

		printf("Please enter test number: ");

		scanf("%d",&(au8_TestNumber));

		switch (au8_TestNumber)
		{
		case 1:
		    /*Happy scenario*/
			au8_Result = BCM_SetupRxBuffer(Rxbuffer,10,NotificationMockPtrFunction);
			printf("The expected output is 0  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;

        case 2:
            au8_Result = BCM_SetupRxBuffer(NULL,10,NotificationMockPtrFunction);
			printf("The expected output is 1  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
         case 3:
            au8_Result = BCM_SetupRxBuffer(Rxbuffer,10,NULL);
            printf("The expected output is 1  and the actual output is %d\n", au8_Result);
            Error_Print();
			break;
        case 4:
            au8_Result = BCM_SetupRxBuffer(NULL,10,NULL);
			printf("The expected output is 1  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
		default:
			printf("invalid test number");
			break;
		}

		printf("\nTo exit BCM test press E or any char to continue ");
				scanf("%c", &au8_repeat);

				printf(" ");
				scanf("%c", &au8_repeat);

				if ('E'  == au8_repeat)
				{

					break;
				}

				printf(" ");
				scanf("%c", &au8_repeat);
			}
}

void BCM_RxUnlock_Test (void){
    uint8_t au8_TestNumber = ZERO;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	uint8_t au8_repeat = ZERO;
	strTxBuffer_t BcmTxBuffer;
    uint8_t Rxbuffer[10]={0};
   void (*Notification)(uint8_t);

	while (TRUE)
	{

		printf("Please enter test number: ");

		scanf("%d",&(au8_TestNumber));

		switch (au8_TestNumber)
		{
		case 1:
		    /*Happy scenario*/
			au8_Result = BCM_RxUnlock(RX_UNLOCK);
			printf("The expected output is 0  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;

        case 2:
            au8_Result = BCM_RxUnlock(5);
			printf("The expected output is  1 and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
		default:
			printf("invalid test number");
			break;
		}

		printf("\nTo exit BCM test press E or any char to continue ");
				scanf("%c", &au8_repeat);

				printf(" ");
				scanf("%c", &au8_repeat);

				if ('E'  == au8_repeat)
				{

					break;
				}

				printf(" ");
				scanf("%c", &au8_repeat);
			}
}

void BCM_GetTxBuffer_Test (void){
    uint8_t au8_TestNumber = ZERO;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	uint8_t au8_repeat = ZERO;
	strTxBuffer_t BcmTxBuffer;
    uint8_t Txbuffer[10]={0};
    uint8_t lockState;
	while (TRUE)
	{

		printf("Please enter test number: ");

		scanf("%d",&(au8_TestNumber));

		switch (au8_TestNumber)
		{
		case 1:
		    /*Happy scenario*/
            BcmTxBuffer.ptrTxBuffer = Txbuffer;
            BcmTxBuffer.Lock = TX_BUFFER_READY_TO_SEND;
            BcmTxBuffer.Size = 8;
			au8_Result = BCM_GetTxBuffer(&BcmTxBuffer,&lockState);
			printf("The expected output is 0  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;

        case 2:
            au8_Result = BCM_GetTxBuffer(NULL,NULL);
			printf("The expected output is 1  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
         case 3:
            BcmTxBuffer.ptrTxBuffer = Txbuffer;
            BcmTxBuffer.Lock = TX_BUFFER_READY_TO_SEND;
            BcmTxBuffer.Size = 8;
			au8_Result = BCM_GetTxBuffer(&BcmTxBuffer,NULL);
			printf("The expected output is 1  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
        case 4:
            au8_Result = BCM_GetTxBuffer(NULL,&lockState);
			printf("The expected output is 1  and the actual output is %d\n", au8_Result);
			Error_Print();
			break;
		default:
			printf("invalid test number");
			break;
		}

		printf("\nTo exit BCM test press E or any char to continue ");
				scanf("%c", &au8_repeat);

				printf(" ");
				scanf("%c", &au8_repeat);

				if ('E'  == au8_repeat)
				{

					break;
				}

				printf(" ");
				scanf("%c", &au8_repeat);
			}
}

