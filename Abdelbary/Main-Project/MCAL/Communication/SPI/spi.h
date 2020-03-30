#ifndef SPI_H_
#define SPI_H_

#include "..\..\..\std_types.h"
#include "..\..\..\MCAL\registers.h"
#include "..\..\..\common_macros.h"
#include "..\..\..\MCAL\DIO\DIO.h"
#include "..\..\..\interrupt.h"
#define SPI_DIR_PORT		PORTB_DIR
#define SPI_DATA_PORT		PORTB_DATA
#define SPI_SS				4
#define SPI_MOSI			5
#define SPI_MISO			6
#define SPI_SCK				7

#define SPI_MODULE_ERR		-600

typedef enum En_spi_mod{
	SPI_MASTER_MOD = 0X10,
	SPI_SLAVE_MOD  = 0X00
}En_spi_mod_t;

typedef enum En_spi_operation_mod{
	SPI_INT_MOD     = 0X80,
	SPI_NORMAL_MOD  = 0X00
}En_spi_operation_mod_t;

typedef enum En_spi_prescaler{
	SPI_PRESCALER_4		= 0X00,
	SPI_PRESCALER_16	= 0X01,
	SPI_PRESCALER_64	= 0X02,
	SPI_PRESCALER_128	= 0X03 
}En_spi_prescaler_t;

typedef enum En_spi_speed_mod{
	SPI_DOBULE_SPEED  = 0X01,
	SPI_NORMAL_SPEED  = 0X00
}En_spi_speed_mod_t;

typedef enum En_spi_sampling_mod{
	SPI_SAMPLING_MOD_0	= 0X00,
	SPI_SAMPLING_MOD_1	= 0X04,
	SPI_SAMPLING_MOD_2	= 0X08,
	SPI_SAMPLING_MOD_3	= 0X0C
}En_spi_sampling_mod_t;

typedef enum En_spi_data_order{
	SPI_DATA_ORDER_MSB  = 0X20,
	SPI_DATA_ORDER_LSB  = 0X00
}En_spi_data_order_t;

typedef void(*SPI_CBF)(void);

typedef struct gstr_spi_status{
En_spi_mod_t				spi_mod;
En_spi_operation_mod_t		spi_opration_mod;
En_spi_prescaler_t			spi_prescaler;
En_spi_speed_mod_t			spi_speed_mod;
En_spi_sampling_mod_t		spi_sampling_mod;
En_spi_data_order_t			spi_data_order;
SPI_CBF						spi_cbf;
}gstrSPI_spi_satus_t;	


ERROR_STATUS SPI_init(gstrSPI_spi_satus_t * spi_status);
ERROR_STATUS spi_enable();
ERROR_STATUS SPI_sendData(const uint8_t data);
ERROR_STATUS SPI_getData(uint8_t* value);
ERROR_STATUS spi_Deinit(void);
#endif
