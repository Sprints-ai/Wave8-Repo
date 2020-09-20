#include "spi.h"


/* SPSR */
#define SPIF    7
#define WCOL    6
/* bits 5-1 reserved */
#define SPI2X   0

/* SPCR */
#define SPIE    7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1
#define SPR0    0
STATIC SPI_CBF  spi_cbf;
STATIC uint8_t gu8_SPI_InitFlag= FALSE;
STATIC uint8_t gu8_SPI_EnableFlag;
ISR(SPI_STC_vect)
{
	spi_cbf();
}
ERROR_STATUS SPI_init(gstrSPI_spi_satus_t * spi_cfg){
	ERROR_STATUS u8_fun_status = OK;
	
	if (gu8_SPI_InitFlag == TRUE)
	{
		u8_fun_status = (SPI_MODULE_ERR+MULTIPLE_INITALIZATION);
	}
	else if (spi_cfg == NULL)
	{
		u8_fun_status = (SPI_MODULE_ERR+NULL_PTR_ERROR);
	}
	else if (  (spi_cfg->spi_mod != SPI_SLAVE_MOD && spi_cfg->spi_mod != SPI_MASTER_MOD) 
			|| (spi_cfg->spi_opration_mod != SPI_NORMAL_MOD && spi_cfg->spi_opration_mod != SPI_INT_MOD)
			|| (spi_cfg->spi_data_order != SPI_DATA_ORDER_MSB && spi_cfg->spi_data_order != SPI_DATA_ORDER_LSB)
			|| (spi_cfg->spi_prescaler > SPI_PRESCALER_128)
			|| (spi_cfg->spi_sampling_mod != SPI_SAMPLING_MOD_0 && spi_cfg->spi_sampling_mod != SPI_SAMPLING_MOD_2 
				&& spi_cfg->spi_sampling_mod != SPI_SAMPLING_MOD_1 && spi_cfg->spi_sampling_mod != SPI_SAMPLING_MOD_3)
			|| (spi_cfg->spi_speed_mod != SPI_NORMAL_SPEED && spi_cfg->spi_speed_mod != SPI_DOBULE_SPEED))
	{
			u8_fun_status = (SPI_MODULE_ERR+INVALAD_PARAMETER);
	}
	else
	{
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
		
		gu8_SPI_InitFlag = TRUE;
		/*init enbale flag as false*/
		gu8_SPI_EnableFlag = FALSE;
	}

	return u8_fun_status;
}


ERROR_STATUS SPI_sendData(const uint8_t data) 
{
	ERROR_STATUS u8_fun_status = OK;
	
	if (gu8_SPI_InitFlag == FALSE)
	{
		u8_fun_status = (SPI_MODULE_ERR+MODULE_NOT_INITALIZED);
	}
	else if (gu8_SPI_EnableFlag == FALSE)
	{
		u8_fun_status = (SPI_MODULE_ERR+MODULE_NOT_EN);
	}
	else
	{
		SPDR = data; //send data by SPI
	}
   	return u8_fun_status;
}


ERROR_STATUS SPI_getData(uint8_t * value)
{
	ERROR_STATUS u8_fun_status = OK;
	if (gu8_SPI_InitFlag == FALSE)
	{
		u8_fun_status = (SPI_MODULE_ERR+MODULE_NOT_INITALIZED);
	}
	else if (gu8_SPI_EnableFlag == FALSE)
	{
		u8_fun_status = (SPI_MODULE_ERR+MODULE_NOT_EN);
	}
	else
	{
		//return the received byte from SPI data register
		*value =  SPDR;
	}
	
	return u8_fun_status;
}

ERROR_STATUS spi_enable()
{
	ERROR_STATUS u8_funStatus = OK;
	if (gu8_SPI_InitFlag == FALSE)
	{
		u8_funStatus = (SPI_MODULE_ERR+MODULE_NOT_INITALIZED);
	}
	else if (gu8_SPI_EnableFlag == TRUE)
	{
		u8_funStatus = (SPI_MODULE_ERR+MULTIPLE_EN);
	}
	else
	{
		SET_BIT(SPCR,SPE);
		gu8_SPI_EnableFlag = TRUE;
	}
	return u8_funStatus;
}


ERROR_STATUS spi_Deinit()
{
	ERROR_STATUS u8_funStatus = OK;
	if (gu8_SPI_InitFlag == FALSE)
	{
		u8_funStatus = (SPI_MODULE_ERR+MODULE_NOT_INITALIZED);
	}
	else
	{
		CLEAR_MASK(SPCR,ZERO);
		CLEAR_MASK(SPDR,ZERO);
		CLEAR_MASK(SPI_DIR_PORT,UPPER_NIBBLE);
		CLEAR_MASK(SPI_DATA_PORT,UPPER_NIBBLE);
		gu8_SPI_EnableFlag = FALSE;
		gu8_SPI_InitFlag = FALSE;
	}
	return u8_funStatus;
}