/*
 * BCM.h
 *
 * Created: 3/2/2020 1:17:48 AM
 *  Author: A_ayman
 */ 


#ifndef BCM_H_
#define BCM_H_

/* inclusions */
#include "../Utilis/std_types.h"
#include "../Utilis/module_retval.h "
#include "../Error_Handeller/ERROR_STORE_CFG.h"
#include "../Error_Handeller/ERROR-STORE.h "
#include "../Error_Handeller/Errors.h"
#include "../../MCAL/UART/UART.h"

/* Constants */


/*SPI_Channels*/
#define SPI_NO_Channel    0x00
#define SPI_Channel_1     0x10
#define SPI_Channel_2     0x20

/*UART_Channels*/
#define UART_NO_Channel   0x00
#define UART_Channel_1    0x01
#define UART_Channel_2    0x02

/*I2C_Channels*/
#define I2C_NO_Channel    0x00
#define I2C_Channel_1     0x01
#define I2C_Channel_2     0x02

/*Buffer Status*/
#define BUFFER_LOCKED      0
#define BUFFER_UNLOCKED    1

/*BCM States*/
#define BCM_IDLE                        0
#define BCM_SENDING_BYTE                1
#define BCM_SENDING_BYTE_COMPLETE       2
#define BCM_RECEIVING_BYTE              3
#define BCM_RECEIVING_BYTE_COMPLETE     4

/* Status of user Required Task*/
#define PASSED     1
#define NOT_PASSED 0


extern uint8_t gu8_UART_CH1_RX_Notification ;
extern uint8_t  gu8_SPI_CH1_RX_Notification ;
extern uint8_t  gu8_SPI_Rx_CH1_Buffer_Status ; //to give the user the right of lock or un lock the buffer after Receiving

typedef void (* BCM_Rx_Call_Back_ptr) (uint8_t );

/*primitive types*/
typedef struct  
{
	uint8_t UART_Channel;
	uint8_t SPI_Channel;
	uint8_t I2C_Channel;
}gstr_BCM_Config_t;

/* function declarations*/

/*
* Function        : ERROR_STATUS BCM_Init (gstr_BCM_Config_t * ConfigPtr );
* Type            : public
* Input parameters: gstr_BCM_Config Structure (UART_Channel, SPI_Channel,I2C_Channel )
* Return type     : ERROR_STATUS
* Re_entrancy	   : Non Reentrant
* Description: initialize the BCM configuration
*/
extern ERROR_STATUS BCM_Init (gstr_BCM_Config_t * ConfigPtr );

/*
* Function        : ERROR_STATUS BCM_Send (uint8_t* ptr_Buffer, uint16_t u16_Size, uint8_t u8_Channel);
* Type            : public
* Input parameters: uint8_t* ptr_Buffer, uint16_t u16_Size, uint8_t u8_Channel
* Return type     : ERROR_STATUS
* Re_entrancy	   : Reentrant
* Description: initialize the BCM sending configuration
*/
extern ERROR_STATUS BCM_Send (uint8_t* ptr_Buffer, uint16_t u16_Size, uint8_t u8_Channel);

/*
* Function        : ERROR_STATUS BCM_Receive (uint8_t* ptr_Buffer, uint16_t u16_Size, uint8_t u8_Channel,BCM_Rx_Call_Back_ptr Func_ptr );
* Type            : public
* Input parameters: uint8_t* ptr_Buffer, uint16_t u16_Size, uint8_t u8_Channel,BCM_Rx_Call_Back_ptr Func_ptr
* Return type     : ERROR_STATUS
* Re_entrancy	   : Reentrant
* Description: initialize the BCM Receiving configuration
*/
extern ERROR_STATUS BCM_Receive (uint8_t* ptr_Buffer, uint16_t u16_Size, uint8_t u8_Channel,BCM_Rx_Call_Back_ptr Func_ptr );


/* Function       : void BCM_TxDispatch(void);
* Type            : public
* Input parameters: none
* Return type     : none
* Re_entrancy	   : Reentrant
* Description: Tracking the status of sending.
*/
extern void BCM_TxDispatch(void);

/* Function       : void BCM_RxDispatch(void);
* Type            : public
* Input parameters: none
* Return type     : none
* Re_entrancy	   : Reentrant
* Description: Tracking the status of Receiving to serve the consumer function.
*/
extern void BCM_RxDispatch(void);

/* Function       : void BCM_UART_Tx_Call_Back(void);
* Type            : public
* Input parameters: none
* Return type     : none
* Re_entrancy	   : Reentrant
* Description: responsible for sending using UART
*/
extern void BCM_UART_Tx_Call_Back(void);


/* Function       : void BCM_UART_Tx_Call_Back(void);
* Type            : public
* Input parameters: none
* Return type     : none
* Re_entrancy	   : Reentrant
* Description: responsible for receiving using UART
*/
extern void BCM_UART_Rx_Call_Back(void);


/* Function       : void BCM_SPI_Tx_Call_Back(void);
* Type            : public
* Input parameters: none
* Return type     : none
* Re_entrancy	   : Reentrant
* Description: responsible for sending using SPI
*/
extern void BCM_SPI_Tx_Call_Back(void);


/* Function       : void BCM_SPI_Rx_Call_Back(void);
* Type            : public
* Input parameters: none
* Return type     : none
* Re_entrancy	   : Reentrant
* Description: responsible for receiving using SPI
*/
extern void BCM_SPI_Rx_Call_Back(void);

#endif /* BCM_H_ */