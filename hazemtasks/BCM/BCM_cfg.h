

#ifndef BCM_CFG_H_
#define BCM_CFG_H_

#include "mock_std_types.h"



#define USART_MODE	            1
#define USART_NODE	            5
#define BCM_SPI_MODE	        2
#define BCM_SPI_MASTER	        3
#define BCM_SPI_SLAVE	        4

#define BCM_ID_	                5
#define BCM_BUFFER_LOCK			1
#define BCM_BUFFER_UNLOCK		0
#define CHECK_SUM_INDEX			1
#define BCM_IDLE				0
#define BCM_RECEIVE				1
#define BCM_RECIEVE_COMPLETE	2
#define RX_COMPLETE				3
#define RX_ERROR			    4
#define BCM_TXSEND              5
#define BCM_TXSENDING           8
#define BCM_TXSEND_COMPLETE     6
#define BCM_TXCOMPLETE          7
#define BCM_INIT_DONE           1
#define BCM_NO_INIT             0


typedef struct Bcm_Cfg_ST{
	uint8_t BCM_Mode;
	uint8_t	SPI_Mode;
}Bcm_Cfg_ST;



#endif /* BCM_CFG_H_ */
