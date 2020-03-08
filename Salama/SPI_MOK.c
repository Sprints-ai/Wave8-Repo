/*
 * SPI.c
 *
 * Created: 10-Feb-20 6:11:46 PM
 *  Author: ahmed
 */
#include "SPI.h"
#include "SPI_CONFIG.h"
#include "interrupt.h"
volatile uint8_t spi_myflag =0;
volatile uint8_t data=0;

volatile ptr_fun set_callback_spi = NULL;

ERROR_STATUS spi_init(config_spi *sp_inits){//uint8_t spi_irq,uint8_t spi_en,uint8_t bit_first,uint8_t master_slave,uint8_t smp,uint8_t spi_prescal){

	/*create error flag*/
	ERROR_STATUS error_flag = E_OK;

	//SPCR = 0xC3;//((sp_inits->spi_irq) | (sp_inits->bit_first) | (sp_inits->smp) | (sp_inits->spi_prescal) );

	//if((sp_inits->master_slave) == MASTER_SELECT)



	/*return error status*/
	return error_flag;
}

uint8_t spi_receiver(void){

	/*write spdr at spi*/
	return 0;
}

ERROR_STATUS spi_transmitter(uint8_t u8_spi_sender)
{
	/*create error flag*/
	ERROR_STATUS error_flag = E_NOK;


	return error_flag;
}


ISR(SPI_STC_vect)
{
	//set_callback_spi();

}
