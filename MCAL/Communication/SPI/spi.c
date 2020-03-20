#include "spi.h"


/* SPSR */
#define SPIF    0x80
#define WCOL    0x40
/* bits 5-1 reserved */
#define SPI2X   0

/* SPCR */
#define SPIE    0x80
#define SPE     0x40
#define DORD    0x20
#define MSTR    0x10
#define CPOL    0x08
#define CPHA    0x04
#define SPR1    0x02
#define SPR0    0x01
static SPI_CBF  spi_cbf;

MY_ISR(SPI_STC_vect)
{
	spi_cbf();
}

u8_ERROR_STATUS_t SPI_init(gstrSPI_spi_satus_t * spi_cfg){
	u8_ERROR_STATUS_t u8_fun_status = E_OK;
	/************************************************************************
	*                     SPI INITIATION STEPS                            
	*	1-SET PINS DIRECTION DEPENDING ON MASTER OR SLAVE
	*	2-SET PRESCALER VALUE
	*	3-SET OPERATION MODE [INT NORMAL]
	*	4-SET SPEED MOD [NORMAL DOUBLE]
	*	5-SET SAMPLING AND SETUP MOD
	*	6-SET DATA DIRECTION
	*	7-ENABLE SPI 
	************************************************************************/

	switch(spi_cfg->spi_mod)
	{
	case SPI_MASTER_MOD:
	  /******** Configure SPI Master Pins *********
	 * SS(PB4)   --> Output
	 * MOSI(PB5) --> Output 
	 * MISO(PB6) --> Input
	 * SCK(PB7) --> Output
	 ********************************************/
		 SET_BIT(SPI_DIR_PORT,SPI_SS);
		 SET_BIT(SPI_DIR_PORT,SPI_MOSI);
		 SET_BIT(SPI_DIR_PORT,SPI_SCK);
		 CLEAR_BIT(SPI_DIR_PORT,SPI_MISO);
		 
		 
		 /*set ss to zero*/
		 CLEAR_BIT(SPI_DATA_PORT,SPI_SS);

	break;
	case SPI_SLAVE_MOD:
	/******** Configure SPI Slave Pins *********
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7) --> Input
	 ********************************************/
		 CLEAR_BIT(SPI_DIR_PORT,SPI_SS);
		 CLEAR_BIT(SPI_DIR_PORT,SPI_MOSI);
		 CLEAR_BIT(SPI_DIR_PORT,SPI_SCK);
		 SET_BIT(SPI_DIR_PORT,SPI_MISO);
	
	break;
	}
	SET_MASK(SPCR,spi_cfg->spi_prescaler);
	SET_MASK(SPCR,spi_cfg->spi_sampling_mod);
	SET_MASK(SPCR,spi_cfg->spi_mod);
	SET_MASK(SPCR,spi_cfg->spi_data_order);
	SET_MASK(SPCR,spi_cfg->spi_opration_mod);
	SET_MASK(SPSR,spi_cfg->spi_speed_mod);
	spi_cbf =   (spi_cfg->spi_cbf);

	return u8_fun_status;
}


u8_ERROR_STATUS_t SPI_sendData(const uint8_t data) 
{
	u8_ERROR_STATUS_t u8_fun_status = E_OK;
	SPDR = data; //send data by SPI  
   	return u8_fun_status;
}

u8_ERROR_STATUS_t SPI_getData(uint8_t * value)
{
	u8_ERROR_STATUS_t u8_fun_status = E_OK;
	
	//return the received byte from SPI data register
	*value =  SPDR; 
	return u8_fun_status;
}

u8_ERROR_STATUS_t spi_enable()
{
	SET_BIT(SPCR,SPE);
}

u8_ERROR_STATUS_t spi_disable(){
	CLEAR_BIT(SPCR,SPE);
}