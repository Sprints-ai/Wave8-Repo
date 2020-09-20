/*
 * SPI.h
 *
 * Created: 3/1/2020 8:45:27 PM
 *  Author: ahmed
 */ 

#include "std_types.h"
#include "registers.h"
#include "interrupt.h"

#define SPIE						(0x80)
#define SPE							(0x40)
#define DORD						(0x20)
#define MSTR						(0x10)
#define SPI2X						(0x01)
#define SPIF						(0x80)
#define WCOL						(0x40)

#define MODE_NUMBER0				(0x00)
#define MODE_NUMBER1				(0x04)
#define	MODE_NUMBER2				(0x08)
#define	MODE_NUMBER3				(0x0C)

#define SPI_FREQUENCY_DIVIDER_4		(0x00)
#define SPI_FREQUENCY_DIVIDER_16	(0x01) 
#define SPI_FREQUENCY_DIVIDER_64	(0x02)
#define SPI_FREQUENCY_DIVIDER_128	(0x03)

#define SPI_MASTER_MODE				(1)
#define SPI_SLAVE_MODE				(0)
									
#define SPI_INTERRUPT				(1)	
#define SPI_POLLING					(0)
									
#define SPI_LSB_FIRST				(1)
#define SPI_MSB_FIRST				(0)
									
#define SPI_NORMAL_SPEED			(0)
#define SPI_2X_SPEED				(1)

#define TRANSMISSION_NOT_COMPLETE	(!(SPSR & SPIF))

#define	MASTER_PORT_MASK			(0xB0)
#define SLAVE_PORT_MASK				(0x40)

typedef struct strSPI_Config_t{
	uint8_t u8_MasterSlaveSelect;
	uint8_t u8_InterruptPollingMode;
	uint8_t u8_DataOrder;
	uint8_t u8_ModeNumber;
	uint8_t u8_ClockRate;
	uint8_t u8_Speed;
	void(*SPI_CBK)(void);
	
}strSPI_Config_t;

ERROR_STATUS SPI_Init(strSPI_Config_t* SPI_Config);

ERROR_STATUS SPI_SendChar(uint8_t u8_Data);

ERROR_STATUS SPI_ReceiveChar(uint8_t* pu8_Data);

