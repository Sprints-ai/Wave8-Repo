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
void SEND_APP  (void);


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

	
}












 /******************************************************/
 /******************* TMU TEST*************************/
 /****************************************************/
/*
#include "SERVICE/TMU/TMU.h"
#include "MCAL/DIO/DIO.h"

void Test3 (void);
void Test2 (void);
void Test1 (void);
void consumer1 (void);
void consumer2 (void);
void consumer3 (void);
void consumer4 (void);


extern str_TMU_InitConfig_t init;
int main(void)
{
    DIO_Cfg_s DIO_Init;
	 DIO_Init.dir = OUTPUT;
	 DIO_Init.GPIO = GPIOA;
	 DIO_Init.pins = LOWER_NIBBLE;

	 DIO_init (&DIO_Init);
	 TMU_Init(&init);
	 
	 Test3();
	 while(1)
	 {
	    TMU_Dispatch();
	 }
	 
}

//call creator more(4) that buffer size(3)
void Test1 (void)
{
   TMU_Start(2,1,PERIODIC,consumer1);
	TMU_Start(3,2,PERIODIC,consumer2);
	TMU_Start(4,3,PERIODIC,consumer3);
	TMU_Start(5,4,PERIODIC,consumer4);

}

void Test2 (void)
{
   TMU_Stop(1,consumer1);
}


//call and stop during run time 
void Test3 (void)
{
   static uint8_t au8_Counter = ZERO;
	if (ZERO == au8_Counter)
	{
	   TMU_Start(100,1,PERIODIC,Test3);
	}

	au8_Counter++;
	if (10 == au8_Counter)
	{
	   TMU_Start(2,2,PERIODIC,consumer1);
	}

	if (15 == au8_Counter)
	{
		TMU_Start(3,3,PERIODIC,consumer2);
	}

	if (20 == au8_Counter)
	{
		TMU_Start(6,4,PERIODIC,consumer3);
	}

	if (35 == au8_Counter)
	{
		TMU_Stop(2,consumer1);
	}

	if (40 == au8_Counter)
	{
		TMU_Stop(3,consumer2);
	}

	if (50 == au8_Counter)
	{
		TMU_Start(3,4,PERIODIC,consumer4);
	}

	if (60 == au8_Counter)
	{
		TMU_Stop(4,consumer3);
	}

	if (70 == au8_Counter)
	{
		TMU_Stop(4,consumer4);
	}

	if (100 == au8_Counter)
	{
		TMU_Stop(1,Test3);
	}
}

void consumer1 (void)
{
   DIO_Toggle(GPIOA, BIT0);
}
void consumer2 (void)
{
	DIO_Toggle(GPIOA,BIT1);
}
void consumer3 (void)
{
	DIO_Toggle(GPIOA,BIT2);
}
void consumer4 (void)
{
	DIO_Toggle(GPIOA,BIT3);
}*/