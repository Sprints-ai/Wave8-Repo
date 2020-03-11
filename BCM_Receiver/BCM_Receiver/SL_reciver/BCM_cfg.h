/*
 * BCM_cfg.h
 *
 *  Created on: Mar 2, 2020
 *      Author: Mohamed Ramadan
 */
/**Last Edition**/

#ifndef BCM_CFG_H_
#define BCM_CFG_H_


typedef enum{
	BCM_SENDER_IDLE,
	BCM_SENDING_BYTE,
	BCM_SENDING_COMPLETE
}BCM_SENDING_SM;

typedef enum{
	BCM_RECEIVER_IDLE,
	BCM_RECEIVING_BYTE,
	BCM_RECEIVING_COMPLETE
}BCM_RECEIVING_SM;

typedef enum{
	BCM_BUFFER_UNLOCKED,
	BCM_BUFFER_LOCKED
}BCM_BUFFER_STATE;

#endif /* BCM_CFG_H_ */
