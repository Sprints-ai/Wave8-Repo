/*
 * bcm_cfg.h
 *
 * Created: 2020-03-01 10:17:16 PM
 *  Author: Ahmed_Salama
 */ 


#ifndef BCM_CFG_H_
#define BCM_CFG_H_

#include "std_types.h"

#define MAX_BUFFER_SIZE   (1000)

/* TODO: Add support for SPI and I2C */
/* UART configuration parameters */
#define UART_BAUD_RATE    (9600)

/* UART module states */
#define TX_ONLY           (0)
#define RX_ONLY           (1)
#define TX_RX             (2)

/* Configure UART module state to be used to initialize UART module */
#define UART_TX_RX_CONFIG TX_RX

/* Protocols of macros to chose which to work at*/
#define UART_PROTOCOL			0
#define SPI_PROTOCOL			1

typedef void (*ptr_Function) (void);


typedef struct st_BCM_Cfg_t {
	
	uint8_t u8_Protocol;
	ptr_Function Transmit_Cbk;
	ptr_Function Recieve_Cbk;
	
	}st_BCM_Cfg_t;


extern st_BCM_Cfg_t BCM_Cfg;

#endif /* BCM_CFG_H_ */
