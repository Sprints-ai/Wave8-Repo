/*
 * BCM.h
 *
 * Created: 3/2/2020 7:31:36 PM
 *  Author: mahmo
 */ 


#ifndef BCM_H_
#define BCM_H_

#include "BCM_cfg.h"
#include "../../MCAL/Communication/SPI/spi.h"
#include "../../MCAL/Communication/UART/uart.h"
typedef void(*BCM_UserNotifier)(ERROR_STATUS status);


#define BCM_FRAM_HEADER_OVERHEAD	4 /*4 bytes added to user data buffer*/
#define BCM_FRAME_SIZE              4
#define ONE_BYTE					1
#define TWO_BYTE                    2
#define BUFFER_SIZE_ELEM			2
/*USE THESE VALUES FOR gas8_init_cbanals_staus ARRAY*/
#define BCM_CHANAL_UNINTALIZED		-1
#define BCM_CHANAL_NO_TASKS			 0

#define BCM_RECIVING_ID					0
#define BCM_RECIVING_DATA_SIZE			2
#define BCM_MAX_RECIVING_BUFFER_SIZE	(MAX_USER_BUFFER_SIZE+BCM_FRAM_HEADER_OVERHEAD)

typedef struct gstr_BCM_cfg{
	uint8_t chanal;		/*BCM_UART_CHANAL ,BCM_SPI_CHANAL,BCM_I2C_CHANAL*/
	uint8_t mode;		/*BCM_SENDER,BCM_RECIVER,BCM_SEND_RECIVE*/
}gstr_BCM_cfg_t;

typedef struct bcmTask_cfg{
	uint8_t *buffer;			/*data buffer to receive or send data*/
	uint8_t *lock;				/*lock variable on buffer*/
	BCM_UserNotifier bcm_cbf;	/*notify function*/
	uint16_t size;				/*size of buffer*/
	uint8_t chanal;				/*uart spi i2c*/
	uint8_t mode;				/*send || recive*/
}gstr_BCM_Task_cfg_t;

typedef struct bcm_taskControlBlock{
	gstr_BCM_Task_cfg_t* bcmTask;/*user configuration*/
	uint8_t  u8_taskStatus;/*idle,sending,complete_sending*/
	uint8_t  u8_counter; /*counter to point to BCM_FRAM_POINTER to send 0 ,1 ,2 ,3 */
	uint8_t  u8_byteCounter; /*for each fram loop on its bytes*/
	uint8_t  u8_checkSum;/*hold sum of the bytes*/
	uint16_t u8_BCM_framSize;/*data size +2 bytes for numOfBytes + 1byte for BCM_ID +1 byte for checksum*/
	uint8_t* apu8_BCM_Frame[BCM_FRAME_SIZE];
}bcm_taskControlBlock_t;
/*
*
*
*
*/
ERROR_STATUS BCM_init(gstr_BCM_cfg_t* bcm_cfg );
/*
*
*
*
*/
ERROR_STATUS BCM_setup(gstr_BCM_Task_cfg_t* str_BCM_TaskCfg);
/*
*
*
*
*/
ERROR_STATUS BCM_RX_dispatcher();
/*
*
*
*
*/
ERROR_STATUS BCM_TX_dispatcher();

#endif /* BCM_H_ */