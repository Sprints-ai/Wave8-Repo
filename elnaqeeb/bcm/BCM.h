/*
 * BCM.h
 *
 * Created: 3/3/2020 10:58:24 AM
 *  Author: Ahmed
 */ 


#ifndef __BCM_H__
#define __BCM_H__

/************************************************************************/
/*                       BCM general macros                             */
/************************************************************************/

#define USART_PROTOCOL	(1)
#define SPI_PROTOCOL	(2)

/************************************************************************/
/*                        BCM Data types                                */
/************************************************************************/

/*BCM Configuration structure*/
typedef struct  
{
	uint8_t	 bcm_id;
	uint8_t  bcm_protocol;
	uint8_t* bcm_buffer;
	uint8_t  bcm_check_sum;	
	uint16_t bcm_buffer_length;
}BCM_ConfigType;

/*BCM Error status*/
typedef sint8_t	EnmBCMError_t;
#define BCM_NULL_PTR_ERROR		(-1)
#define BCM_OPERATION_SUCCESS	(-2)
#define BCM_OPERATION_FAILED	(-3)
#define BCM_INVALID_PROTOCOL	(-4)
#define BCM_CHECKSUM_ERROR		(-5)

/************************************************************************/
/*                    BCM Functions' prototypes			                */
/************************************************************************/

/*
 * Description: Initializes the Basic Communication Module (BCM).
 * @param(IN) : N/A
 * @param(OUT):	N/A
 * @param(I/O): N/A
 * @ret BCM Error status  
 */
EnmBCMError_t BCM_Init(void); 

/*
 * Description: De-Initializes the Basic Communication Module (BCM).
 * @param(IN) : N/A
 * @param(OUT):	N/A
 * @param(I/O): N/A
 * @ret BCM Error status  
 */
EnmBCMError_t BCM_DeInit(void);

/*
 * Description: This function manages the BCM sending operation.
 * @param(IN) : N/A
 * @param(OUT):	N/A
 * @param(I/O): N/A
 * @ret BCM Error status  
 */
EnmBCMError_t BCM_TxDispatch(void);

/*
 * Description: This function manages the BCM receiving operation.
 * @param(IN) : N/A
 * @param(OUT):	N/A
 * @param(I/O): N/A
 * @ret BCM Error status  
 */
EnmBCMError_t BCM_RxDispatch(void);

/*
 * Description: This function sends a block of data.
 * @param(IN) : Pointer to the data that will be sent
				Size of the data
 * @param(OUT):	N/A
 * @param(I/O): N/A
 * @ret BCM Error status  
 */
EnmBCMError_t BCM_Send(uint8_t* pu8_dataPtr , uint16_t au16_dataSize);

/*
 * Description: This function receives a block of data.
 * @param(IN) : N/A
 * @param(OUT):	Pointer to the data received
 * @param(I/O): N/A
 * @ret BCM Error status  
 */
EnmBCMError_t BCM_Receive(uint8_t* pu8_dataPtr);
  
#endif /* BCM_H_ */