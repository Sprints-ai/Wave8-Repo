/*
 * Dynamic Design.c
 *
 * Created: 2/24/2020 9:35:01 AM
 * Author : Khaled
 */ 

 #include "SERVICE/BCM/BCM.h"
 #include "MCAL/DIO/DIO.h"

/*******************************************************/
/***************** BCM TEST****************************/
/*****************************************************/


void Consumer(uint8_t Status);
void REC_App (void);
uint8_t Data[80];
extern  strTxBuffer_t Tx_RequestBuffer[];


int main (void)
{
     SEND_APP();
	  return 0;
}
void REC_App (void)
{
	strBCMCfg_t bcm;

	
	bcm.Protocol = SPI_BCM;
	bcm.Direction =READING;
	
	UART_INIT(Uart_Parity_no,Uart_Stop_Bit_One,Uart_Data_8_Bit,Uart_Baud_Rate_9600,Uart_Async_Normal_Speed,Uart_Multi_Processor_Communication_Disable,Uart_Polling,NULL);
	BCM_Init(&bcm);
	BCM_SetupRxBuffer(Data,80,Consumer);
	
	while(1)
    {
       
		BCM_RxDispatcher(); 
    }
	
}
void Consumer(uint8_t Status){
	
	if(Status == E_OK){
		

		UART_TRANSMIT_String(Data);
		BCM_RxUnlock(RX_UNLOCK);
	}
}
	







void SEND_APP  (void)
{
	strBCMCfg_t BCM_Info;
	DIO_Cfg_s diocfg;
	//uint8_t Data[10]={'0','1','2','3','4','5','6','7','8','9'};
	
	BCM_Info.Direction = SENDING;
	BCM_Info.Protocol = SPI_BCM;
	
		
	diocfg.GPIO =GPIOB;
	diocfg.pins=BIT0|BIT1|BIT3;
	diocfg.dir=OUTPUT;
		
	DIO_init(&diocfg);
	
	
	UART_INIT(Uart_Parity_no,Uart_Stop_Bit_One,Uart_Data_8_Bit,Uart_Baud_Rate_9600,Uart_Async_Normal_Speed,Uart_Multi_Processor_Communication_Disable,Uart_Polling,NULL);
	DIO_Write(GPIOA,BIT3,HIGH);
	
	
	
	
	
	uint8_t D[100];
	UART_RECEIVE_String(D);
	
	BCM_Init(&BCM_Info);
	//_SPITrancevier('c',D);
	Tx_RequestBuffer[0].Lock = TX_BUFFER_READY_TO_SEND;
	Tx_RequestBuffer[0].ptrTxBuffer = D;
	Tx_RequestBuffer[0].Size = 10;

	BCM_Send(Tx_RequestBuffer);
	while (1)
	{
		BCM_TxDispatcher();
	}

	return 0;
}