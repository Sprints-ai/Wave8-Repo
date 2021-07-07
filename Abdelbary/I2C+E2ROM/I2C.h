/*
* I2C.h
*
* Created: 28/04/2020 23:16:43
*  Author: sony
*/


#ifndef I2C_H_
#define I2C_H_
#include "macros.h"
/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start 
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave
#define DATA				3
#define ADDRESS				4

extern uint8_t TWI_data_type;

typedef enum {I2C_OK, I2C_NOK}I2C_CheckType;
typedef void (*I2C_CbkPftype)(void);
typedef struct 
{
	unsigned long int CPUFreq;
	unsigned short int PreScaler;
	unsigned long int TargerRate;
	I2C_CbkPftype ActionDoneCbkPtr;
}I2C_ConfigType;


void I2C_Init(void);
I2C_CheckType I2C_ReqWrite(uint8_t SlaveAddress, const unsigned char* DataPtr, unsigned char DataLen);
I2C_CheckType I2C_ReqRead(uint8_t SlaveAddress, unsigned char* DataPtr, unsigned char DataLen);
void I2C_Stop(void);
void I2C_Start(void);


#endif /* I2C_H_ */