/*
 * BCM_Based.c
 *
 * Created: 3/13/2020 2:33:47 PM
 *  Author: Az
 */
 /*- INCLUDES ---------------------------------------------------------------------------------------------------------*/ 
 #include "BCM_Based.h"
 #include "../../MCAL/USART/usart.h"
 #include "../../MCAL/USART/usart_Cfg.h"
 #include "../../SL/BCM/BCM.h"
 #include "../../SL/BCM/BCM_LK_Cfg.h"
 /*- GLOBALS ----------------------------------------------------------------------------------------------------------*/
 /* USART TX / RX chunks */
 static uint8_t ga_rxUsartChunk[CHUNK_SIZE] = {0};  /* Chunk received by usart */
 static uint8_t ga_txUsartChunk[CHUNK_SIZE] = {0};  /* Chunk transmitted by usart */
 /* BCM TX / RX Usart byte counters */
 static uint8_t gu8_rxUsartByteCount = 0;
 static uint8_t gu8_txUsartByteCount = 0;
 /* USART TX/RX chunk states */
 static uint8_t gu8_chunkReceiveState;
 static uint8_t gu8_chunkTransmitState;

 static volatile uint8_t * redundant_ptr = NULL; /*useless*/
 /*- FUNCTION DEFINITIONS ---------------------------------------------------------------------------*/
 /*
 * Description : Represents a Call Back for TX of USART - that is responsible transmitting 
 *               data to user after it has been received at BCM-Receiver side -
 *
 * @param void
 *
 * @return void
 */
 static void UART_TxCallBack(void)
 {
    /* Check if it the last byte to transmit or not */
    if((uint8_t)CHUNK_SIZE == gu8_txUsartByteCount)
    {
       /* Report finish transmitting chunk*/
       gu8_chunkTransmitState = USART_CHUNK_TRANSMIT_COMPLETE;
    }
    /* Write next byte to UDR */
    UsartWriteTx(&ga_txUsartChunk[gu8_txUsartByteCount++]);
 }

 /*
 * Description : Represents a Call Back for RX of USART - that is responsible Receiving 
 *               data from user and store it in RX-chunk-buffer at BCM-Transmitter side -
 *
 * @param void
 *
 * @return void
 */
 static void UART_RxCallBack(void)
 {
    /* Read from UDR */
    UsartReadRx(&ga_rxUsartChunk[gu8_rxUsartByteCount]);
    /* increment rx counter*/
    gu8_rxUsartByteCount++;    
 }

 /*
 * Description : Represents the logic of the BCM-Transmitter side at which the following happens:
 *               1 - USART receives data-chunks from user and store it into a rx_chunk_buffer
 *               2 - BCM-Transmitter starts to consume the data stored in rx_chunk_buffer and 
 *                   transmit chunk to the BCM-Receiver side.  
 *
 *
 * @param void
 *
 * @return void
 */
 void BCM_Transmit(void)
 {
    uint8_t au8_BCM_txState = 0;
    /*------ 1 - BCM INIT ---------*/
    /* Initialize BCM -transmit- */
    BCM_Init(&gstr_BCM_Transmit_Init);
    /* Setup Your Buffer/chunk size and address */
    BCM_SetupTxBuffer(ga_rxUsartChunk,CHUNK_SIZE);
    /*------ 2 - USART INIT ---------*/
    /* Usart setup call back */
    USART_SetRxCallBack(UART_RxCallBack);
    /* Initialize UART : to receive the chunk of data */
    Usart_Init(&usart_init_config_receive);
    UCSRB = 0x90;  /* ---> Forcing UCSRB configuration for Debugging purpose */
    /* Initiate Usart chunk receiving state */
    gu8_chunkReceiveState = USART_CHUNK_RECEIVING;
    
    while (1)
    {
       /* Check States */
       switch (gu8_chunkReceiveState)
       {
          case USART_CHUNK_RECEIVING:
          /* Wait until receiving is finished */
          while( gu8_rxUsartByteCount < (uint8_t)CHUNK_SIZE && 0x0D != ga_rxUsartChunk[gu8_rxUsartByteCount])
          {             
              *redundant_ptr = USART_CHUNK_RECEIVING; /* Redundant*/             
          };
          /* Move to Chunk receiving complete */
          gu8_chunkReceiveState = USART_CHUNK_RECEIVE_COMPLETE;
          case USART_CHUNK_RECEIVE_COMPLETE:
          /* Reset Counter */
          gu8_rxUsartByteCount = 0;
          /* Trigger BCM */
          BCM_Send();
          /* Call dispatcher */
          BCM_TxDispatcher();
          /* check BCM Tx state */
          BCM_GetTxState(&au8_BCM_txState);
          while(SENDING_COMPLETE != au8_BCM_txState)
          {
             /* Check Status again and see if BCM has finished or not */
             BCM_GetTxState(&au8_BCM_txState);
          }
          /* if BCM sending is done : Receive the new Usart new chunk */
          gu8_chunkReceiveState = USART_CHUNK_IDLE;
          case USART_CHUNK_IDLE:
          break;
       }
    }
 }

 /*
 * Description : Represents the logic of the BCM-Receiver side at which the following happens:
 *               1 - BCM-Receiver receives the data chunk from BCM-Transmitter and stored in 
 *                   tx_chunk_buffer.                    
 *               2 - USART Transmits the data-chunk -stored in tx_chunk_buffer- to user at the other side.
 *
 * @param void
 *
 * @return void
 */
 void BCM_Receive(void)
 {
    uint8_t au8_BCM_rxState = 0;
    /*------ 1 - BCM INIT ---------*/
    /* Initialize BCM -Receive- */
    BCM_Init(&gstr_BCM_Receive_Init);
    /* Setup Your Buffer/chunk size and address */
    BCM_SetupRxBuffer(ga_txUsartChunk,CHUNK_SIZE);
    /* ------  (USART INIT) -------- */
    /* Usart setup call back */
    USART_SetTxCallBack(UART_TxCallBack);
    /* Initialize UART : to transmit the chunk of data */
    Usart_Init(&usart_init_config_transmit);
    UCSRB = 0x48;        /* ---> Forcing UCSRB configuration for Debugging purpose */
    /* Initiate Usart chunk Transmitting state */
    gu8_chunkTransmitState =  USART_CHUNK_IDLE;
    /* Initiate BCM Receive process */
    BCM_Read();
    while(1)
    {
       /*get BCM Rx state */
       BCM_GetRxState(&au8_BCM_rxState);
       switch(au8_BCM_rxState)
       {
          case IDLE:
          /* Initiate BCM read Again and Move to RECEUVUNG_BYTE State to start again*/
          break;
          case RECIEVING_BYTES:
          /* Wait until receiving - from BCM transmitter - is complete */
          while(RECIEVING_BYTES == au8_BCM_rxState)
          {
             BCM_RxDispatcher();
             BCM_GetRxState(&au8_BCM_rxState);
          }
          /* Initiate Usart chunk Transmit */
          gu8_chunkTransmitState = USART_CHUNK_TRANSMITTING;
          break;
          case RECIEVING_COMPLETE:
          switch(gu8_chunkTransmitState)
          {
             case USART_CHUNK_TRANSMITTING:
             /* Trigger transmit process through writing the first byte */
             UsartWriteTx(&ga_txUsartChunk[gu8_txUsartByteCount++]);
             /* Wait Until chunk transmitting is complete */
             while (USART_CHUNK_TRANSMITTING == gu8_chunkTransmitState);
             break;
             case USART_CHUNK_TRANSMIT_COMPLETE:
             /* reset counter */
             gu8_txUsartByteCount = 0;
             /* Move BCM rx state system to idle */
             au8_BCM_rxState = IDLE;
             break;             
          };
          break;
       }
    }
 }
 /*-------------------------------------------- ( END BCM APPLICATION ) --------------------------------------------*/