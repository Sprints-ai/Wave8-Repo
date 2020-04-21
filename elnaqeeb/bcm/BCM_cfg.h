/*
 * BCM_config.h
 *
 * Created: 3/3/2020 10:58:39 AM
 *  Author: ahmed
 */ 


#ifndef __BCM_CFG_H__
#define __BCM_CFG_H__

#define BCM_ID_CFG			(0xAA)
#define BCM_PROTOCOL_CFG	(SPI_PROTOCOL)
#define BCM_BUFFER_CFG		(NULL)
#define BCM_CHECK_SUM_CFG	(0)
#define BCM_BUFFER_SIZE_CFG	(0)


#define BCM_CFG_DATA {BCM_ID_CFG ,BCM_PROTOCOL_CFG, BCM_BUFFER_CFG , BCM_CHECK_SUM_CFG , BCM_BUFFER_SIZE_CFG}



#endif /* BCM_CONFIG_H_ */