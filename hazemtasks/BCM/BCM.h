/*
 * BCM.h
 *
 * Created: 3/3/2020 1:45:44 AM
 *  Author: Ema
 */


#ifndef BCM_H_
#define BCM_H_

#include "BCM_cfg.h"
#include "spi_mock.h"
#include "USART_mock.h"
#include "mock_std_types.h"
#include "common_macros.h"

#define BCMError_t sint8_t


typedef void (*BCM_SEND_CBKFUNCOMP)(void);
typedef void (*BCM_recieve_cbk)(void);

extern BCMError_t BCM_init(Bcm_Cfg_ST *Bcm_cfg_ST);
extern BCMError_t BCM_recieve(uint8_t *Buffer_ptr,BCM_recieve_cbk CBKFUN);
extern void BCM_RX_dispatcher(void);
extern BCMError_t BCM_Send(BCM_SEND_CBKFUNCOMP CBKFUN,uint8_t* BUFFER,uint16_t size);
extern void BCM_TX_dispatcher(void);
extern BCMError_t BCM_DINIT(void);


#endif /* BCM_H_ */
