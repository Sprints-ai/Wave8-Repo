/*
 * BCM.c
 *
 * Created: 3/4/2020 7:11:43 PM
 *  Author: Az
 */
/*- INCLUDES -------------------------------------------------------------------------------------------------------*/
#include "BCM.h"
#include "../../MCAL/SPI/SPI.h"
#include "../../MCAL/SPI/SPI_Cfg.h"
#include "../../registers.h"
//#include "../../interrupt.h"
#include "../../ECUAL/SwDelay/SwDelay.h"
#include "../../MCAL/USART/usart.h"
#include "../../MCAL/USART/usart_Cfg.h"

/*- GLOBAL VARIABLES -----------------------------------------------------------------------------------------------*/
/*---- state of TX/RX state machines ----*/
uint8_t gu8_RxState = (uint8_t)IDLE;
uint8_t gu8_TxState = (uint8_t)IDLE;

/*---- TX/RX notifications ----*/
static uint8_t gu8_RxNotification = 0;
static uint8_t gu8_TxNotification = 0;

/*---- TX/RX Buffer config instance ----*/
StrBuffer_t gstr_txBufferCfg;
StrBuffer_t gstr_rxBufferCfg;

/*---- Transmitted/Received bytes counters ----*/
static uint16_t gu16_txByteCounter = 0;
static uint16_t gu16_rxByteCounter = 0;


static uint8_t gu8_protocol = 0;

/*- FUNCTIONS DEFINITIONS ------------------------------------------------------------------------------------------*/

/*---- Start STATIC FUNCTIONS DEFINITIONS ----*/
/* 1 - Notifications Setters/Getters */
/*
* Description : Sets notification of transmission. 
*
*  @param uint8_t state
*  @return void
*/
static void BCM_SetTXNotification(uint8_t state)
{
   gu8_TxNotification = state;
}
/*
*  Description : Gets notification of transmission.
* 
*  @param uint8_t * state  (output param)
*  @return void
*/
static void BCM_GetTXNotification(uint8_t * state)
{
   *state = gu8_TxNotification;  
}
/*
* Description : Sets notification of reception.
* @param uint8_t state
* @return void
*/
static void BCM_SetRXNotification(uint8_t state)
{
   gu8_RxNotification = state;
}
/*
*  Description : Gets notification of reception.
*  @param uint8_t * state (output param)
*  @return void
*/
static void BCM_GetRXNotification(uint8_t * state)
{
   *state = gu8_RxNotification; 
}

/* 2 - SPI Call Backs */
/*
*  Description : Represents the call back function that fires on SPI interrupt -in Transmit case-.
*
*  @param void
*
*  @return void
*/
static void BCM_SPI_TX_CallBack(void)
{
   /* Fires when packet receive interrupt comes it checks if it is coming from BCM(if it is the firs packet so, it checks BCM ID):
    (if yes) then store data into buffer directly  */
        
   /* When this interrupt fires , that means successful transmission, so
   each time we check if it is the last byte to be transmitted or not */
   if(gstr_txBufferCfg.bufferSize == gu16_txByteCounter)
   {     
      /* Report Success Transmission */
      BCM_SetTXNotification(BCM_TRANSMIT_COMPLETE);
      /* Send a last byte */
      //SPI_WriteByte(gstr_txBufferCfg.bufferAddress[gu16_txByteCounter]);     
   }
   else
   {
      /* Report byte transmit success */
      BCM_SetTXNotification(BCM_BYTE_TRANSMIT_SUCCESS);
      /* Increment sent bytes counter */
      gu16_txByteCounter++;
      /* Send a new byte */
      SPI_WriteByte(gstr_txBufferCfg.bufferAddress[gu16_txByteCounter]);      
   }  
}

/*
*  Description : Represents the call back function that fires on SPI interrupt -in Receive case-.
*
*  @param void
*
*  @return void
*/
static void BCM_SPI_RX_CallBack(void)
{
   /* Fires when packet receive interrupt comes it checks if it is coming from BCM(if it is the firs packet so, it checks BCM ID):
    (if yes) then store data into buffer directly  */  
   /* report success read */
   /*  when this fires -on behalf of the slave side : that means byte has been successfully transmitted by master
       so you can read the transmitted byte- */
   if(((gstr_rxBufferCfg.bufferSize)-1) == gu16_rxByteCounter)
   {     
      /* Report Success Reception */
      BCM_SetRXNotification(BCM_RECIEVE_COMPLETE); 
      /* Read the last byte */
      SPI_ReadByte(&(gstr_rxBufferCfg.bufferAddress[gu16_rxByteCounter]));    
   }
   else
   {
      /* Read the byte */
      SPI_ReadByte(&(gstr_rxBufferCfg.bufferAddress[gu16_rxByteCounter]));                  
      /* Increment sent bytes counter */
      gu16_rxByteCounter++;      
      /* Report byte Reception success */
      BCM_SetRXNotification(BCM_BYTE_RECIEVE_SUCCESS);            
   }
}
/*---- END STATIC FUNCTIONS DEFINITIONS ----*/

/*
*  Description : Get Rx State machine's state.
*
*  @param uint8_t * state  (output param)
*
*  @return EnmBCMError_t
*/
EnmBCMError_t  BCM_GetRxState(uint8_t * state)
{
   uint8_t au8_errorState = 0;
   if(NULL != state)
   {
      *state = gu8_RxState;
      /* Report Success*/
      au8_errorState = BCM_READ_STATE_SUCCESS;
   }
   else
   {
      /* Report fail */
      au8_errorState = BCM_INVALID_INPUT_PARAMS;
   }
   return au8_errorState;
   
}

/*
*  Description : Get Tx State machine's state.
*
*  @param uint8_t * state  (output param)
*
*  @return EnmBCMError_t
*/
EnmBCMError_t  BCM_GetTxState(uint8_t * state)
{
   uint8_t au8_errorState = 0;
   if(NULL != state)
   {
      *state = gu8_TxState;
      /* Report Success*/
      au8_errorState = BCM_READ_STATE_SUCCESS;
   }
   else
   {
      /* Report fail */
      au8_errorState = BCM_INVALID_INPUT_PARAMS;
   }
   return au8_errorState;
   
}

/*
*  Description : Gets BCM TX buffer status - whether locked or unlocked -
*
*  @param uint8_t * getStatus
*
*  @return EnmBCMError_t
*/
EnmBCMError_t BCM_GetTxBufferStatus(uint8_t * getStatus)
{
   /* Define error state */
   uint8_t au8_errorState = 0;
   /* check against invalid input arguments */
   if(NULL != getStatus)
   {
      /* Report BCM Tx Buffer Status*/
      *getStatus = gstr_txBufferCfg.buffer_state;
      /* Report Success */
      au8_errorState = BCM_READ_TX_BUFFER_STATUS_SUCCESS;
   }
   else
   {
      /* report fail */
      au8_errorState = BCM_READ_TX_BUFFER_STATUS_FAIL;
   }
   return au8_errorState;
}

/*
*  Description : Gets BCM Rx buffer status - whether locked or unlocked -
*
*  @param uint8_t * getStatus
*
*  @return EnmBCMError_t
*/
EnmBCMError_t BCM_GetRxBufferStatus(uint8_t * getStatus)
{
   /* Define error state */
   uint8_t au8_errorState = 0;
   /* check against invalid input arguments */
   if(NULL != getStatus)
   {
      /* Report BCM Rx Buffer Status*/
      *getStatus = gstr_rxBufferCfg.buffer_state;
      /* Report Success */
      au8_errorState = BCM_READ_RX_BUFFER_STATUS_SUCCESS;
   }
   else
   {
      /* report fail */
      au8_errorState = BCM_READ_RX_BUFFER_STATUS_FAIL;
   }
   return au8_errorState;
}

/*
*  Description : Setups External Buffer -provided by the application- for receiving data
*
*  @param uint8_t * rxBuffer
*  @param uint16_t rxBufferSize
*
*  @return EnmBCMError_t
*/
EnmBCMError_t BCM_SetupRxBuffer(uint8_t * rxBuffer, uint16_t rxBufferSize)
{
   /*Define error state */
   uint8_t au8_errorState = 0;
   /* Validating rxBuffer pointer*/
   if(NULL != rxBuffer)
   {
      /* Validate rxBufferSize */
      if((MAX_BUFFER_SIZE >= rxBufferSize))
      {
         /* Initialize Rx buffer configuration */
         gstr_rxBufferCfg.bufferAddress = rxBuffer;
         gstr_rxBufferCfg.bufferSize    = rxBufferSize;
         gstr_rxBufferCfg.buffer_state  = BUFFER_UNLOCKED;
         gstr_rxBufferCfg.check_sum     = 0;
         /* Return success */
         au8_errorState = BCM_SETUP_RX_BUFFER_SUCCESS;
      }
      else
      {
         /* Report fail */
         au8_errorState = BCM_INVALID_BUFFER_SIZE;
      }
   }
   else
   {
      /* Report Fail */
      au8_errorState = BCM_INVALID_INPUT_PARAMS;
   }
   return au8_errorState;
}

/*
*  Description : Setups External Buffer -provided by the application- for Transmitting data
*
*  @param uint8_t * txBuffer
*  @param uint16_t txBufferSize
*
*  @return EnmBCMError_t
*/
EnmBCMError_t BCM_SetupTxBuffer(uint8_t * txBuffer, uint16_t txBufferSize)
{
   /*Define error state */
   uint8_t au8_errorState = 0;
   /* Validating txBuffer pointer*/
   if(NULL != txBuffer)
   {
      /* Validate txBufferSize */
      if(MAX_BUFFER_SIZE >= txBufferSize)
      {
         /* Initialize Tx buffer configuration */
         gstr_txBufferCfg.bufferAddress = txBuffer;
         gstr_txBufferCfg.bufferSize    = txBufferSize;
         gstr_txBufferCfg.buffer_state  = BUFFER_UNLOCKED;
         gstr_txBufferCfg.check_sum     = 0;         
         /* Return success */
         au8_errorState = BCM_SETUP_TX_BUFFER_SUCCESS;
      }
      else
      {
         /* Report fail */
         au8_errorState = BCM_INVALID_BUFFER_SIZE;
      }
   }
   else
   {
      /* Report Fail */
      au8_errorState = BCM_INVALID_INPUT_PARAMS;
   }
   return au8_errorState;
}

/*
*  Description : Responsible for initialization process of BCM.
*
*  @param str_BCM_Cfg_t * strBCM_Init
*
*  @return EnmBCMError_t
*/
EnmBCMError_t BCM_Init(str_BCM_Cfg_t * strBCM_Init)
{
   /* Define error state */
   uint8_t au8_errorState = 0;
   /* Validate config struct not null */
   if(NULL != strBCM_Init)
   {
      /* Initialize Data Direction */
      switch (strBCM_Init->dataDirection)
      {
         case TRANSMIT:
            /* 1.A Initialize State of Transmission state machine */
            gu8_TxState = IDLE;
            /* 1.B Initialize the chosen protocol */
            gu8_protocol = strBCM_Init->protocol;
            switch (strBCM_Init->protocol)
            {
               case SPI:                  
                  /* Initialize Master */
                  SPI_Init(&gstr_MasterCfg);
                  /* Set callback */
                  SPI_Set_ISR_CallBack(BCM_SPI_TX_CallBack);                                  
               break;
               case I2C:
                  /* Not used currently */
               break;          
            }            
         break;
         case RECIEVE:            
            /* 1.A Initialize State of Reception state machine */
            gu8_RxState = IDLE;
            /* 1.B Initialize the chosen protocol */
            gu8_protocol = strBCM_Init->protocol;
            switch (strBCM_Init->protocol)
            {
               case SPI:               
                  /* Initialize Slave */
                  SPI_Init(&gstr_SlaveCfg);
                  /* Set Call back*/
                  SPI_Set_ISR_CallBack(BCM_SPI_RX_CallBack);               
               break;
               case I2C:;
                  /* Not used currently*/
               break;
            }            
         break;
      }
      /* Initialize USART Module */
      Usart_Init(&usart_init_config);                    
   }
   else
   {
      /* Report Fail */
      au8_errorState = BCM_INVALID_INPUT_PARAMS; 
   }
   /* Return error state*/
   return au8_errorState;  
}

/*
*  Description : Starts or triggers Tx state machines , Locks Tx buffer in order to start the process , Sends the first byte which is (BCM_ID,Data length)
*
*  @param void
*
*  @return void
*/
void BCM_Send(void)
{
   /* 1 - Lock Tx/Rx buffer ahead of any further coming actions */
   gstr_txBufferCfg.buffer_state = BUFFER_LOCKED;   
   /* 2 - Triggers Tx/Rx state machines */   
   gu8_TxState = SENDING_BYTES;
   /* 3 - Start Communication protocol */
   switch (gu8_protocol)
   {
      case SPI:
         SPI_Enable();
      break;
      case I2C:
         /* Not used currently*/
      break;
   };
      
   /* 2 - send BCM_ID */
   //SPI_WriteByte(BCM_ID);   
}

/*
*  Description : Starts or triggers Rx state machines , Locks Rx buffer in order to start the process , Receives the first byte which is (BCM_ID,Data length)
*
*  @param void
*
*  @return void
*/
void BCM_Read(void)
{
   /* 1 - Lock Rx buffer ahead of any further coming actions */   
   gstr_rxBufferCfg.buffer_state = BUFFER_LOCKED;
   /* 2 - Triggers Rx state machines */
   gu8_RxState = RECIEVING_BYTES;
   /* 3 - Start Communication protocol */
   switch (gu8_protocol)
   {
      case SPI:
         SPI_Enable();
      break;
      case I2C:
         /* Not used currently*/
      break;
   };   
   /* 2 - receive BCM_ID */
   //SPI_ReadByte(BCM_ID);
}

/*
*  Description : Receives Data packets
*
*  @param void
*
*  @return void
*/
void BCM_RxDispatcher(void)
{
   /* Switching on system states to take action */
   switch(gu8_RxState)
   {
      case IDLE:
         /* Wait for the trigger : which is the action token by BCM_send() */
         if((BUFFER_LOCKED != gstr_rxBufferCfg.buffer_state) && (RECIEVING_BYTES != gu8_RxState));
      break;
      case RECIEVING_BYTES:         
         /* 1 - wait for the notification fired by ISR -on successful transmission : which mean that you can read -*/
         if(RECIEVING_BYTES == gu8_RxState)
         {
            switch(gu8_RxNotification)
            {                                              
               case BCM_RECIEVE_COMPLETE:
                  /* 1 - Reset Received bytes counter */
                  gu16_rxByteCounter = 0;
                  /* 2 - Unlock RX Buffer */
                  gstr_rxBufferCfg.buffer_state = (uint8_t)BUFFER_UNLOCKED;
                  /* 3 - Set RX state to IDLE */
                  gu8_RxState = RECIEVING_COMPLETE;
                  /* 4 - Initialize Rx Buffer Address to NUll*/
                  //gstr_rxBufferCfg.bufferAddress = NULL;
                  /*disable spi or I2c*/
                  /* 5 - Stop Communication protocol */
                  switch (gu8_protocol)
                  {
                     case SPI:
                        SPI_Disable();
                     break;
                     case I2C:
                        /* Not used currently*/
                     break;
                  };
               break;
            }
         }         
      break;
      case RECIEVING_COMPLETE:
         /* Report receive complete to the upper layer : now we just break from the loop */         
      break;    
   }
   
   
}

/*
*  Description : Navigates between the states of BCM packets Transmission state machine.
*                (IDLE , SENDING_BYTES) 
*
*  @param void
*  @return void
*/
void BCM_TxDispatcher(void)
{
   /* Switching on system states to take action */
   switch(gu8_TxState)
   {
      case IDLE:
         /* Wait for the trigger : which is the action token by BCM_send() */
         if((BUFFER_LOCKED != gstr_txBufferCfg.buffer_state) && (SENDING_BYTES != gu8_TxState));                         
      break;
      case SENDING_BYTES:            
            /* 1 - Send the first byte & increment the counter */
            SPI_WriteByte(*(gstr_txBufferCfg.bufferAddress));
            gu16_txByteCounter++;                                                           
            /* 2 - wait for the notification fired by ISR -on successful transmission -*/
            while(SENDING_BYTES == gu8_TxState)
            {
               switch(gu8_TxNotification)
               {                  
                  case BCM_TRANSMIT_COMPLETE:
                     /* 1 - Reset transmit bytes counter */
                     gu16_txByteCounter = 0;
                     /* 2 - Unlock TX Buffer */
                     gstr_txBufferCfg.buffer_state = (uint8_t)BUFFER_UNLOCKED;
                     /* 3 - Set TX state to IDLE */
                     gu8_TxState = SENDING_COMPLETE;
                     /* 4 - Initialize Tx Buffer Address to NUll*/
                     //gstr_txBufferCfg.bufferAddress = NULL;
                     /* 5 - Stop Communication protocol */
                     switch (gu8_protocol)
                     {
                        case SPI:
                           SPI_Disable();
                        break;
                        case I2C:
                           /* Not used currently*/
                        break;
                     };
                  break;
               }
            };           
      break;
      case SENDING_COMPLETE:
         /* Report sending complete to the upper layer : now we just break from the loop */
      break;          
   }   
}



