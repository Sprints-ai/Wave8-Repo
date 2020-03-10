/*
 * BCM_cfg.h
 *
 * Created: 3/2/2020 7:32:00 PM
 *  Author: mahmo
 */ 


#ifndef BCM_CFG_H_
#define BCM_CFG_H_

/*define your chanals here*/
#define BCM_UART_CHANAL		0
#define BCM_SPI_CHANAL		1
#define BCM_I2C_CHANAL		2

#define BCM_MAX_CHANALS		3 /*hardware available chanales*/

/*use these values for mod in bcmTask_cfg*/
#define BCM_SENDER			0
#define BCM_RECIVER			1
/*#define BCM_SEND_RECIVE   2 */
#define BCM_MAX_MODES       2 /*sender or receiver adding more modes will require change this value*/

#define MAX_USER_BUFFER_SIZE 40


#define BCM_MODULE_ERR	-200
#define BCM_SPI_ID		20
#endif /* BCM_CFG_H_ */