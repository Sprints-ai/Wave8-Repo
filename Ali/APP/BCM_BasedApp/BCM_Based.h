/*
 * BCM_Based.h
 *
 * Created: 3/13/2020 2:33:27 PM
 *  Author: Az
 */ 


#ifndef BCM_BASED_H_
#define BCM_BASED_H_
/*- DEFINES ----------------------------------------------------------------------------------------------------------*/
#define CHUNK_SIZE 100

#define USART_CHUNK_RECEIVE_COMPLETE 1
#define USART_CHUNK_RECEIVING        2

#define USART_CHUNK_TRANSMIT_COMPLETE 3
#define USART_CHUNK_TRANSMITTING      4

#define USART_CHUNK_IDLE               5
/*- FUNCTION PROTOTYPES ---------------------------------------------------------------------------------------------*/
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
 extern void BCM_Transmit(void);

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
 extern void BCM_Receive(void);




#endif /* BCM_BASED_H_ */